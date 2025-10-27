#!/usr/bin/env python3
import json
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent.parent))
from dfs import dfs_recursive, dfs_iterative

with open(Path(__file__).parent / 'test_cases.json') as f:
    data = json.load(f)

graph = data['graph']
for test in data['tests']:
    result = dfs_recursive(graph, test['start'], test['goal'])
    print(f"DFS Recursive {test['start']}->{test['goal']}: {result}")

for test in data['tests']:
    result = dfs_iterative(graph, test['start'], test['goal'])
    print(f"DFS Iterative {test['start']}->{test['goal']}: {result}")

