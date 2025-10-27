#!/usr/bin/env ruby
require 'json'
require 'set'
require_relative '../dijkstra'

data = JSON.parse(File.read(File.join(__dir__, 'test_cases.json')))

# Convert graph format
graph = {}
data['graph'].each do |k, v|
  graph[k] = v.map { |neighbor, weight| [neighbor, weight] }
end

data['tests'].each do |test|
  path, cost = dijkstra_heap(graph, test['start'], test['goal'])
  puts "Dijkstra Heap #{test['start']}->#{test['goal']}: #{path} (cost: #{cost})"
end

data['tests'].each do |test|
  path, cost = dijkstra_array(graph, test['start'], test['goal'])
  puts "Dijkstra Array #{test['start']}->#{test['goal']}: #{path} (cost: #{cost})"
end

