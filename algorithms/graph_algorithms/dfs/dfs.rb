# Depth-First Search: Explore deep before backtracking
require 'set'


def dfs_recursive(graph, start, goal, visited = Set.new)
  return [start] if start == goal
  
  visited.add(start)
  (graph[start] || []).each do |neighbor|
    next if visited.include?(neighbor)
    path = dfs_recursive(graph, neighbor, goal, visited)
    return [start] + path if path
  end
  
  nil
end


def dfs_iterative(graph, start, goal)
  stack = [[start, [start]]]
  visited = Set.new
  
  until stack.empty?
    node, path = stack.pop
    
    next if visited.include?(node)
    return path if node == goal
    
    visited.add(node)
    (graph[node] || []).reverse_each do |neighbor|
      stack << [neighbor, path + [neighbor]] unless visited.include?(neighbor)
    end
  end
  
  nil
end


def dfs_postorder(graph, start, visited = Set.new)
  return [] if visited.include?(start)
  
  visited.add(start)
  result = []
  
  (graph[start] || []).each do |neighbor|
    result.concat(dfs_postorder(graph, neighbor, visited))
  end
  
  result << start
end

