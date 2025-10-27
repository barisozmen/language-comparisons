#!/usr/bin/env node
const fs = require('fs');
const path = require('path');
const { bfs_iterative, bfs_bidirectional } = require('../bfs');

const data = JSON.parse(fs.readFileSync(path.join(__dirname, 'test_cases.json'), 'utf8'));
const graph = data.graph;

data.tests.forEach(test => {
    const result = bfs_iterative(graph, test.start, test.goal);
    console.log(`BFS ${test.start}->${test.goal}: ${JSON.stringify(result)}`);
});

data.tests.forEach(test => {
    const result = bfs_bidirectional(graph, test.start, test.goal);
    console.log(`Bidirectional ${test.start}->${test.goal}: ${JSON.stringify(result)}`);
});

