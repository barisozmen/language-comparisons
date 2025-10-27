#!/usr/bin/env python3
import json
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent.parent))
from dijkstra import dijkstra_heap, dijkstra_array

with open(Path(__file__).parent / 'test_cases.json') as f:
    data = json.load(f)

# Convert graph format
graph = {k: [(n, w) for n, w in v] for k, v in data['graph'].items()}

for test in data['tests']:
    path, cost = dijkstra_heap(graph, test['start'], test['goal'])
    print(f"Dijkstra Heap {test['start']}->{test['goal']}: {path} (cost: {cost})")

for test in data['tests']:
    path, cost = dijkstra_array(graph, test['start'], test['goal'])
    print(f"Dijkstra Array {test['start']}->{test['goal']}: {path} (cost: {cost})")

