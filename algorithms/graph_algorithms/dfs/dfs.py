# Depth-First Search: Explore deep before backtracking


def dfs_recursive(graph, start, goal, visited=None):
    """Classic recursive DFS - elegant but stack-limited."""
    if visited is None:
        visited = set()
    
    if start == goal:
        return [start]
    
    visited.add(start)
    for neighbor in graph.get(start, []):
        if neighbor not in visited:
            path = dfs_recursive(graph, neighbor, goal, visited)
            if path:
                return [start] + path
    
    return None


def dfs_iterative(graph, start, goal):
    """Iterative DFS using explicit stack - no recursion limit."""
    stack = [(start, [start])]
    visited = set()
    
    while stack:
        node, path = stack.pop()
        
        if node in visited:
            continue
        
        if node == goal:
            return path
        
        visited.add(node)
        for neighbor in reversed(graph.get(node, [])):
            if neighbor not in visited:
                stack.append((neighbor, path + [neighbor]))
    
    return None


def dfs_postorder(graph, start, visited=None):
    """DFS that returns nodes in postorder (children before parents)."""
    if visited is None:
        visited = set()
    
    if start in visited:
        return []
    
    visited.add(start)
    result = []
    
    for neighbor in graph.get(start, []):
        result.extend(dfs_postorder(graph, neighbor, visited))
    
    result.append(start)
    return result

