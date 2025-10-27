#!/usr/bin/env node
const fs = require('fs');
const path = require('path');
const { dijkstra_heap, dijkstra_array } = require('../dijkstra');

const data = JSON.parse(fs.readFileSync(path.join(__dirname, 'test_cases.json'), 'utf8'));

// Convert graph format
const graph = {};
for (const [node, edges] of Object.entries(data.graph)) {
    graph[node] = edges;
}

data.tests.forEach(test => {
    const [path, cost] = dijkstra_heap(graph, test.start, test.goal);
    console.log(`Dijkstra Heap ${test.start}->${test.goal}: ${JSON.stringify(path)} (cost: ${cost})`);
});

data.tests.forEach(test => {
    const [path, cost] = dijkstra_array(graph, test.start, test.goal);
    console.log(`Dijkstra Array ${test.start}->${test.goal}: ${JSON.stringify(path)} (cost: ${cost})`);
});

