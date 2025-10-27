#!/usr/bin/env node
const fs = require('fs');
const path = require('path');
const { dfs_recursive, dfs_iterative } = require('../dfs');

const data = JSON.parse(fs.readFileSync(path.join(__dirname, 'test_cases.json'), 'utf8'));
const graph = data.graph;

data.tests.forEach(test => {
    const result = dfs_recursive(graph, test.start, test.goal);
    console.log(`DFS Recursive ${test.start}->${test.goal}: ${JSON.stringify(result)}`);
});

data.tests.forEach(test => {
    const result = dfs_iterative(graph, test.start, test.goal);
    console.log(`DFS Iterative ${test.start}->${test.goal}: ${JSON.stringify(result)}`);
});

