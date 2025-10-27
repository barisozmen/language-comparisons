// Breadth-First Search: Level-by-level exploration


function bfs_iterative(graph, start, goal) {
    if (start === goal) return [start];
    
    const queue = [[start, [start]]];
    const visited = new Set([start]);
    
    while (queue.length > 0) {
        const [node, path] = queue.shift();
        
        for (const neighbor of (graph[node] || [])) {
            if (visited.has(neighbor)) continue;
            if (neighbor === goal) return [...path, neighbor];
            visited.add(neighbor);
            queue.push([neighbor, [...path, neighbor]]);
        }
    }
    
    return null;
}


function bfs_level_order(graph, start) {
    const levels = [];
    const queue = [start];
    const visited = new Set([start]);
    
    while (queue.length > 0) {
        const levelSize = queue.length;
        const level = [];
        
        for (let i = 0; i < levelSize; i++) {
            const node = queue.shift();
            level.push(node);
            
            for (const neighbor of (graph[node] || [])) {
                if (!visited.has(neighbor)) {
                    visited.add(neighbor);
                    queue.push(neighbor);
                }
            }
        }
        levels.push(level);
    }
    
    return levels;
}


function bfs_bidirectional(graph, start, goal) {
    if (start === goal) return [start];
    
    let front = new Map([[start, [start]]]);
    let back = new Map([[goal, [goal]]]);
    let visitedFront = new Set([start]);
    let visitedBack = new Set([goal]);
    
    while (front.size > 0 && back.size > 0) {
        if (front.size > back.size) {
            [front, back] = [back, front];
            [visitedFront, visitedBack] = [visitedBack, visitedFront];
        }
        
        const nextFront = new Map();
        for (const [node, path] of front) {
            for (const neighbor of (graph[node] || [])) {
                if (visitedBack.has(neighbor)) {
                    return [...path, ...back.get(neighbor).reverse()];
                }
                if (!visitedFront.has(neighbor)) {
                    visitedFront.add(neighbor);
                    nextFront.set(neighbor, [...path, neighbor]);
                }
            }
        }
        
        front = nextFront;
    }
    
    return null;
}


module.exports = { bfs_iterative, bfs_level_order, bfs_bidirectional };
