use std::collections::HashMap;
use std::fs;

include!("../bfs.rs");

fn main() {
    let data: serde_json::Value = serde_json::from_str(
        &fs::read_to_string("test_cases.json").expect("Failed to read test_cases.json")
    ).expect("Failed to parse JSON");

    // Build graph
    let mut graph = HashMap::new();
    let graph_obj = data["graph"].as_object().unwrap();
    for (key, val) in graph_obj {
        let neighbors: Vec<&str> = val.as_array().unwrap()
            .iter()
            .map(|v| v.as_str().unwrap())
            .collect();
        graph.insert(key.as_str(), neighbors);
    }

    // Run tests
    for test in data["tests"].as_array().unwrap() {
        let start = test["start"].as_str().unwrap();
        let goal = test["goal"].as_str().unwrap();
        
        let result = bfs_iterative(&graph, start, goal);
        println!("BFS {}->{}: {:?}", start, goal, result);
    }

    for test in data["tests"].as_array().unwrap() {
        let start = test["start"].as_str().unwrap();
        let goal = test["goal"].as_str().unwrap();
        
        let result = bfs_bidirectional(&graph, start, goal);
        println!("Bidirectional {}->{}: {:?}", start, goal, result);
    }
}

