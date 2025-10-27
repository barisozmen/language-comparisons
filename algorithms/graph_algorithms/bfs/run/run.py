#!/usr/bin/env python3
import json
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent.parent))
from bfs import bfs_iterative, bfs_bidirectional

with open(Path(__file__).parent / 'test_cases.json') as f:
    data = json.load(f)

graph = data['graph']
for test in data['tests']:
    result = bfs_iterative(graph, test['start'], test['goal'])
    print(f"BFS {test['start']}->{test['goal']}: {result}")

for test in data['tests']:
    result = bfs_bidirectional(graph, test['start'], test['goal'])
    print(f"Bidirectional {test['start']}->{test['goal']}: {result}")

