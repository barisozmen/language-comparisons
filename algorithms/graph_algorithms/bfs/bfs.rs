// Breadth-First Search: Level-by-level exploration
use std::collections::{HashMap, HashSet, VecDeque};


fn bfs_iterative(graph: &HashMap<&str, Vec<&str>>, start: &str, goal: &str) -> Option<Vec<String>> {
    if start == goal {
        return Some(vec![start.to_string()]);
    }

    let mut queue = VecDeque::new();
    let mut visited = HashSet::new();
    
    queue.push_back((start, vec![start.to_string()]));
    visited.insert(start);

    while let Some((node, path)) = queue.pop_front() {
        for &neighbor in graph.get(node).unwrap_or(&vec![]) {
            if visited.contains(neighbor) {
                continue;
            }
            if neighbor == goal {
                let mut result = path.clone();
                result.push(neighbor.to_string());
                return Some(result);
            }
            visited.insert(neighbor);
            let mut new_path = path.clone();
            new_path.push(neighbor.to_string());
            queue.push_back((neighbor, new_path));
        }
    }

    None
}


fn bfs_level_order(graph: &HashMap<&str, Vec<&str>>, start: &str) -> Vec<Vec<String>> {
    let mut levels = Vec::new();
    let mut queue = VecDeque::from([start]);
    let mut visited = HashSet::from([start]);

    while !queue.is_empty() {
        let level_size = queue.len();
        let mut level = Vec::new();
        for _ in 0..level_size {
            let node = queue.pop_front().unwrap();
            level.push(node.to_string());

            for &neighbor in graph.get(node).unwrap_or(&vec![]) {
                if !visited.contains(neighbor) {
                    visited.insert(neighbor);
                    queue.push_back(neighbor);
                }
            }
        }
        levels.push(level);
    }

    levels
}


fn bfs_bidirectional(graph: &HashMap<&str, Vec<&str>>, start: &str, goal: &str) -> Option<Vec<String>> {
    // Bidirectional BFS: Search from both start and goal simultaneously
    // Note: For directed graphs, we need a reverse graph for backward search
    if start == goal {
        return Some(vec![start.to_string()]);
    }

    // Build reverse graph for backward traversal
    let mut reverse_graph: HashMap<&str, Vec<&str>> = HashMap::new();
    for (&node, neighbors) in graph {
        for &neighbor in neighbors {
            reverse_graph.entry(neighbor).or_insert_with(Vec::new).push(node);
        }
    }

    let mut queue_front = VecDeque::from([(start, vec![start.to_string()])]);
    let mut queue_back = VecDeque::from([(goal, vec![goal.to_string()])]);
    let mut visited_front: HashMap<&str, Vec<String>> = HashMap::new();
    let mut visited_back: HashMap<&str, Vec<String>> = HashMap::new();
    
    visited_front.insert(start, vec![start.to_string()]);
    visited_back.insert(goal, vec![goal.to_string()]);

    while !queue_front.is_empty() && !queue_back.is_empty() {
        // Forward step
        if let Some((node, path)) = queue_front.pop_front() {
            for &neighbor in graph.get(node).unwrap_or(&vec![]) {
                if let Some(back_path) = visited_back.get(neighbor) {
                    let mut result = path.clone();
                    result.extend(back_path.iter().rev().cloned());
                    return Some(result);
                }
                if !visited_front.contains_key(neighbor) {
                    let mut new_path = path.clone();
                    new_path.push(neighbor.to_string());
                    visited_front.insert(neighbor, new_path.clone());
                    queue_front.push_back((neighbor, new_path));
                }
            }
        }

        // Backward step (using reverse graph)
        if let Some((node, path)) = queue_back.pop_front() {
            for &neighbor in reverse_graph.get(node).unwrap_or(&vec![]) {
                if let Some(front_path) = visited_front.get(neighbor) {
                    let mut result = front_path.clone();
                    result.extend(path.iter().rev().cloned());
                    return Some(result);
                }
                if !visited_back.contains_key(neighbor) {
                    let mut new_path = path.clone();
                    new_path.push(neighbor.to_string());
                    visited_back.insert(neighbor, new_path.clone());
                    queue_back.push_back((neighbor, new_path));
                }
            }
        }
    }

    None
}


fn main() {
    let mut graph = HashMap::new();
    graph.insert("A", vec!["B", "C"]);
    graph.insert("B", vec!["D", "E"]);
    graph.insert("C", vec!["F"]);
    graph.insert("D", vec![]);
    graph.insert("E", vec!["F"]);
    graph.insert("F", vec![]);
    
    println!("{:?}", bfs_iterative(&graph, "A", "F"));
    println!("{:?}", bfs_level_order(&graph, "A"));
    println!("{:?}", bfs_bidirectional(&graph, "A", "F"));
}
