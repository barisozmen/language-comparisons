#!/usr/bin/env ruby
require 'json'
require 'set'
require_relative '../bfs'

data = JSON.parse(File.read(File.join(__dir__, 'test_cases.json')))
graph = data['graph'].transform_keys(&:to_s)

data['tests'].each do |test|
  result = bfs_iterative(graph, test['start'], test['goal'])
  puts "BFS #{test['start']}->#{test['goal']}: #{result}"
end

data['tests'].each do |test|
  result = bfs_bidirectional(graph, test['start'], test['goal'])
  puts "Bidirectional #{test['start']}->#{test['goal']}: #{result}"
end

