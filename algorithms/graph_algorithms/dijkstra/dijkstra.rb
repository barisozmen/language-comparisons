# Dijkstra's Algorithm: Shortest path in weighted graphs
require 'set'


def dijkstra_heap(graph, start, goal)
  pq = [[0, start, [start]]]
  visited = Set.new
  
  until pq.empty?
    cost, node, path = pq.min_by { |c, _, _| c }
    pq.delete([cost, node, path])
    
    next if visited.include?(node)
    return [path, cost] if node == goal
    
    visited.add(node)
    (graph[node] || []).each do |neighbor, weight|
      unless visited.include?(neighbor)
        pq << [cost + weight, neighbor, path + [neighbor]]
      end
    end
  end
  
  [nil, Float::INFINITY]
end


def dijkstra_array(graph, start, goal)
  distances = Hash.new(Float::INFINITY)
  graph.keys.each { |n| distances[n] = Float::INFINITY }
  distances[start] = 0
  previous = {}
  unvisited = graph.keys.to_set
  
  until unvisited.empty?
    current = unvisited.min_by { |n| distances[n] }
    
    break if distances[current] == Float::INFINITY
    
    if current == goal
      path = []
      node = current
      while node
        path.unshift(node)
        node = previous[node]
      end
      return [path, distances[goal]]
    end
    
    unvisited.delete(current)
    
    (graph[current] || []).each do |neighbor, weight|
      new_dist = distances[current] + weight
      if new_dist < distances[neighbor]
        distances[neighbor] = new_dist
        previous[neighbor] = current
      end
    end
  end
  
  [nil, Float::INFINITY]
end


def dijkstra_all_paths(graph, start)
  distances = Hash.new(Float::INFINITY)
  graph.keys.each { |n| distances[n] = Float::INFINITY }
  distances[start] = 0
  pq = [[0, start]]
  visited = Set.new
  
  until pq.empty?
    cost, node = pq.min_by { |c, _| c }
    pq.delete([cost, node])
    
    next if visited.include?(node)
    visited.add(node)
    
    (graph[node] || []).each do |neighbor, weight|
      new_dist = cost + weight
      if new_dist < distances[neighbor]
        distances[neighbor] = new_dist
        pq << [new_dist, neighbor]
      end
    end
  end
  
  distances
end

