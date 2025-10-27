// Dijkstra's Algorithm: Shortest path in weighted graphs


function dijkstra_heap(graph, start, goal) {
    const pq = [[0, start, [start]]];
    const visited = new Set();
    
    while (pq.length > 0) {
        pq.sort((a, b) => a[0] - b[0]);
        const [cost, node, path] = pq.shift();
        
        if (visited.has(node)) continue;
        if (node === goal) return [path, cost];
        
        visited.add(node);
        for (const [neighbor, weight] of (graph[node] || [])) {
            if (!visited.has(neighbor)) {
                pq.push([cost + weight, neighbor, [...path, neighbor]]);
            }
        }
    }
    
    return [null, Infinity];
}


function dijkstra_array(graph, start, goal) {
    const distances = {};
    const previous = {};
    const unvisited = new Set();
    
    for (const node in graph) {
        distances[node] = Infinity;
        unvisited.add(node);
    }
    distances[start] = 0;
    
    while (unvisited.size > 0) {
        let current = null;
        let minDist = Infinity;
        for (const node of unvisited) {
            if (distances[node] < minDist) {
                minDist = distances[node];
                current = node;
            }
        }
        
        if (minDist === Infinity) break;
        
        if (current === goal) {
            const path = [];
            let node = current;
            while (node) {
                path.unshift(node);
                node = previous[node];
            }
            return [path, distances[goal]];
        }
        
        unvisited.delete(current);
        
        for (const [neighbor, weight] of (graph[current] || [])) {
            const newDist = distances[current] + weight;
            if (newDist < distances[neighbor]) {
                distances[neighbor] = newDist;
                previous[neighbor] = current;
            }
        }
    }
    
    return [null, Infinity];
}


function dijkstra_all_paths(graph, start) {
    const distances = {};
    for (const node in graph) {
        distances[node] = Infinity;
    }
    distances[start] = 0;
    
    const pq = [[0, start]];
    const visited = new Set();
    
    while (pq.length > 0) {
        pq.sort((a, b) => a[0] - b[0]);
        const [cost, node] = pq.shift();
        
        if (visited.has(node)) continue;
        visited.add(node);
        
        for (const [neighbor, weight] of (graph[node] || [])) {
            const newDist = cost + weight;
            if (newDist < distances[neighbor]) {
                distances[neighbor] = newDist;
                pq.push([newDist, neighbor]);
            }
        }
    }
    
    return distances;
}


module.exports = { dijkstra_heap, dijkstra_array, dijkstra_all_paths };

