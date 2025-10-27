// Depth-First Search: Explore deep before backtracking
use std::collections::{HashMap, HashSet};


fn dfs_recursive(
    graph: &HashMap<&str, Vec<&str>>,
    start: &str,
    goal: &str,
    visited: &mut HashSet<&str>
) -> Option<Vec<String>> {
    if start == goal {
        return Some(vec![start.to_string()]);
    }

    visited.insert(start);
    
    for &neighbor in graph.get(start).unwrap_or(&vec![]) {
        if !visited.contains(neighbor) {
            if let Some(mut path) = dfs_recursive(graph, neighbor, goal, visited) {
                path.insert(0, start.to_string());
                return Some(path);
            }
        }
    }

    None
}


fn dfs_iterative(graph: &HashMap<&str, Vec<&str>>, start: &str, goal: &str) -> Option<Vec<String>> {
    let mut stack = vec![(start, vec![start.to_string()])];
    let mut visited = HashSet::new();

    while let Some((node, path)) = stack.pop() {
        if visited.contains(node) {
            continue;
        }
        
        if node == goal {
            return Some(path);
        }

        visited.insert(node);
        
        if let Some(neighbors) = graph.get(node) {
            for &neighbor in neighbors.iter().rev() {
                if !visited.contains(neighbor) {
                    let mut new_path = path.clone();
                    new_path.push(neighbor.to_string());
                    stack.push((neighbor, new_path));
                }
            }
        }
    }

    None
}


fn dfs_postorder(
    graph: &HashMap<&str, Vec<&str>>,
    start: &str,
    visited: &mut HashSet<&str>
) -> Vec<String> {
    if visited.contains(start) {
        return vec![];
    }

    visited.insert(start);
    let mut result = Vec::new();

    if let Some(neighbors) = graph.get(start) {
        for &neighbor in neighbors {
            result.extend(dfs_postorder(graph, neighbor, visited));
        }
    }

    result.push(start.to_string());
    result
}


fn main() {
    let mut graph = HashMap::new();
    graph.insert("A", vec!["B", "C"]);
    graph.insert("B", vec!["D", "E"]);
    graph.insert("C", vec!["F"]);
    graph.insert("D", vec![]);
    graph.insert("E", vec!["F"]);
    graph.insert("F", vec![]);
    
    let mut visited = HashSet::new();
    println!("{:?}", dfs_recursive(&graph, "A", "F", &mut visited));
    println!("{:?}", dfs_iterative(&graph, "A", "F"));
}

