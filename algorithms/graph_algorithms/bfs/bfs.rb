# Breadth-First Search: Level-by-level exploration
require 'set'


def bfs_iterative(graph, start, goal)
  return [start] if start == goal
  
  queue = [[start, [start]]]
  visited = Set[start]
  
  until queue.empty?
    node, path = queue.shift
    (graph[node] || []).each do |neighbor|
      next if visited.include?(neighbor)
      return path + [neighbor] if neighbor == goal
      visited.add(neighbor)
      queue << [neighbor, path + [neighbor]]
    end
  end
  
  nil
end


def bfs_level_order(graph, start)
  levels = []
  queue = [start]
  visited = Set[start]
  
  until queue.empty?
    level_size = queue.size
    level = []
    level_size.times do
      node = queue.shift
      level << node
      (graph[node] || []).each do |neighbor|
        unless visited.include?(neighbor)
          visited.add(neighbor)
          queue << neighbor
        end
      end
    end
    levels << level
  end
  
  levels
end


def bfs_bidirectional(graph, start, goal)
  return [start] if start == goal
  
  front = { start => [start] }
  back = { goal => [goal] }
  visited_front = Set[start]
  visited_back = Set[goal]
  
  until front.empty? || back.empty?
    front, back = back, front if front.size > back.size
    visited_front, visited_back = visited_back, visited_front if front.size > back.size
    
    next_front = {}
    front.each do |node, path|
      (graph[node] || []).each do |neighbor|
        return path + back[neighbor].reverse if visited_back.include?(neighbor)
        unless visited_front.include?(neighbor)
          visited_front.add(neighbor)
          next_front[neighbor] = path + [neighbor]
        end
      end
    end
    
    front = next_front
  end
  
  nil
end
