# Breadth-First Search: Level-by-level exploration
from collections import deque


def bfs_iterative(graph, start, goal):
    """Standard BFS with queue - finds shortest path."""
    if start == goal:
        return [start]
    
    queue = deque([(start, [start])])
    visited = {start}
    
    while queue:
        node, path = queue.popleft()
        for neighbor in graph.get(node, []):
            if neighbor in visited:
                continue
            if neighbor == goal:
                return path + [neighbor]
            visited.add(neighbor)
            queue.append((neighbor, path + [neighbor]))
    
    return None


def bfs_level_order(graph, start):
    """BFS that returns nodes level by level."""
    levels = []
    queue = deque([start])
    visited = {start}
    
    while queue:
        level_size = len(queue)
        level = []
        for _ in range(level_size):
            node = queue.popleft()
            level.append(node)
            for neighbor in graph.get(node, []):
                if neighbor not in visited:
                    visited.add(neighbor)
                    queue.append(neighbor)
        levels.append(level)
    
    return levels


def bfs_bidirectional(graph, start, goal):
    """BFS from both ends - requires reverse graph for directed graphs."""
    if start == goal:
        return [start]
    
    # Build reverse graph for backward search
    reverse_graph = {}
    for node in graph:
        for neighbor in graph[node]:
            if neighbor not in reverse_graph:
                reverse_graph[neighbor] = []
            reverse_graph[neighbor].append(node)
    
    queue_front = [(start, [start])]
    queue_back = [(goal, [goal])]
    visited_front = {start: [start]}
    visited_back = {goal: [goal]}
    
    while queue_front and queue_back:
        # Forward step
        if queue_front:
            node, path = queue_front.pop(0)
            for neighbor in graph.get(node, []):
                if neighbor in visited_back:
                    return path + list(reversed(visited_back[neighbor]))
                if neighbor not in visited_front:
                    new_path = path + [neighbor]
                    visited_front[neighbor] = new_path
                    queue_front.append((neighbor, new_path))
        
        # Backward step (using reverse graph)
        if queue_back:
            node, path = queue_back.pop(0)
            for neighbor in reverse_graph.get(node, []):
                if neighbor in visited_front:
                    return visited_front[neighbor] + list(reversed(path))
                if neighbor not in visited_back:
                    new_path = path + [neighbor]
                    visited_back[neighbor] = new_path
                    queue_back.append((neighbor, new_path))
    
    return None
