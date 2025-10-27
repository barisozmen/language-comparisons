// Depth-First Search: Explore deep before backtracking


function dfs_recursive(graph, start, goal, visited = new Set()) {
    if (start === goal) return [start];
    
    visited.add(start);
    for (const neighbor of (graph[start] || [])) {
        if (!visited.has(neighbor)) {
            const path = dfs_recursive(graph, neighbor, goal, visited);
            if (path) return [start, ...path];
        }
    }
    
    return null;
}


function dfs_iterative(graph, start, goal) {
    const stack = [[start, [start]]];
    const visited = new Set();
    
    while (stack.length > 0) {
        const [node, path] = stack.pop();
        
        if (visited.has(node)) continue;
        if (node === goal) return path;
        
        visited.add(node);
        const neighbors = graph[node] || [];
        for (let i = neighbors.length - 1; i >= 0; i--) {
            if (!visited.has(neighbors[i])) {
                stack.push([neighbors[i], [...path, neighbors[i]]]);
            }
        }
    }
    
    return null;
}


function dfs_postorder(graph, start, visited = new Set()) {
    if (visited.has(start)) return [];
    
    visited.add(start);
    const result = [];
    
    for (const neighbor of (graph[start] || [])) {
        result.push(...dfs_postorder(graph, neighbor, visited));
    }
    
    result.push(start);
    return result;
}


module.exports = { dfs_recursive, dfs_iterative, dfs_postorder };

