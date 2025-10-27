# Dijkstra's Algorithm: Shortest path in weighted graphs
from heapq import heappush, heappop


def dijkstra_heap(graph, start, goal):
    """Dijkstra with min-heap - O((V + E) log V)."""
    pq = [(0, start, [start])]
    visited = set()
    
    while pq:
        cost, node, path = heappop(pq)
        
        if node in visited:
            continue
        
        if node == goal:
            return path, cost
        
        visited.add(node)
        for neighbor, weight in graph.get(node, []):
            if neighbor not in visited:
                heappush(pq, (cost + weight, neighbor, path + [neighbor]))
    
    return None, float('inf')


def dijkstra_array(graph, start, goal):
    """Dijkstra with array - O(V²), simple but slower."""
    distances = {node: float('inf') for node in graph}
    distances[start] = 0
    previous = {}
    unvisited = set(graph.keys())
    
    while unvisited:
        # Find min distance node
        current = min(unvisited, key=lambda n: distances[n])
        
        if distances[current] == float('inf'):
            break
        
        if current == goal:
            path = []
            while current:
                path.insert(0, current)
                current = previous.get(current)
            return path, distances[goal]
        
        unvisited.remove(current)
        
        for neighbor, weight in graph.get(current, []):
            new_dist = distances[current] + weight
            if new_dist < distances[neighbor]:
                distances[neighbor] = new_dist
                previous[neighbor] = current
    
    return None, float('inf')


def dijkstra_all_paths(graph, start):
    """Dijkstra from single source to all nodes."""
    distances = {node: float('inf') for node in graph}
    distances[start] = 0
    pq = [(0, start)]
    visited = set()
    
    while pq:
        cost, node = heappop(pq)
        
        if node in visited:
            continue
        
        visited.add(node)
        
        for neighbor, weight in graph.get(node, []):
            new_dist = cost + weight
            if new_dist < distances[neighbor]:
                distances[neighbor] = new_dist
                heappush(pq, (new_dist, neighbor))
    
    return distances

