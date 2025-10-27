// Dijkstra's Algorithm: Shortest path in weighted graphs
use std::collections::{HashMap, HashSet, BinaryHeap};
use std::cmp::Ordering;

#[derive(Eq, PartialEq)]
struct State {
    cost: i32,
    node: String,
    path: Vec<String>,
}

impl Ord for State {
    fn cmp(&self, other: &Self) -> Ordering {
        other.cost.cmp(&self.cost)
    }
}

impl PartialOrd for State {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        Some(self.cmp(other))
    }
}


fn dijkstra_heap(graph: &HashMap<&str, Vec<(&str, i32)>>, 
                 start: &str, goal: &str) -> (Option<Vec<String>>, i32) {
    let mut heap = BinaryHeap::new();
    let mut visited = HashSet::new();
    
    heap.push(State {
        cost: 0,
        node: start.to_string(),
        path: vec![start.to_string()],
    });
    
    while let Some(State { cost, node, path }) = heap.pop() {
        if visited.contains(&node) {
            continue;
        }
        
        if node == goal {
            return (Some(path), cost);
        }
        
        visited.insert(node.clone());
        
        if let Some(neighbors) = graph.get(node.as_str()) {
            for &(neighbor, weight) in neighbors {
                if !visited.contains(neighbor) {
                    let mut new_path = path.clone();
                    new_path.push(neighbor.to_string());
                    heap.push(State {
                        cost: cost + weight,
                        node: neighbor.to_string(),
                        path: new_path,
                    });
                }
            }
        }
    }
    
    (None, i32::MAX)
}


fn dijkstra_all_paths(graph: &HashMap<&str, Vec<(&str, i32)>>, 
                      start: &str) -> HashMap<String, i32> {
    let mut distances = HashMap::new();
    let mut heap = BinaryHeap::new();
    let mut visited = HashSet::new();
    
    for &node in graph.keys() {
        distances.insert(node.to_string(), i32::MAX);
    }
    distances.insert(start.to_string(), 0);
    
    heap.push((0i32, start.to_string()));
    
    while let Some((cost, node)) = heap.pop() {
        let cost = -cost; // Negate to use max-heap as min-heap
        
        if visited.contains(&node) {
            continue;
        }
        
        visited.insert(node.clone());
        
        if let Some(neighbors) = graph.get(node.as_str()) {
            for &(neighbor, weight) in neighbors {
                let new_dist = cost + weight;
                if new_dist < *distances.get(neighbor).unwrap_or(&i32::MAX) {
                    distances.insert(neighbor.to_string(), new_dist);
                    heap.push((-new_dist, neighbor.to_string()));
                }
            }
        }
    }
    
    distances
}


fn main() {
    let mut graph = HashMap::new();
    graph.insert("A", vec![("B", 1), ("C", 4)]);
    graph.insert("B", vec![("C", 2), ("D", 5)]);
    graph.insert("C", vec![("D", 1)]);
    graph.insert("D", vec![]);
    
    let (path, cost) = dijkstra_heap(&graph, "A", "D");
    println!("{:?} with cost {}", path, cost);
}

