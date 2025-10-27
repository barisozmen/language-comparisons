#!/usr/bin/env ruby
require 'json'
require 'set'
require_relative '../dfs'

data = JSON.parse(File.read(File.join(__dir__, 'test_cases.json')))
graph = data['graph'].transform_keys(&:to_s)

data['tests'].each do |test|
  result = dfs_recursive(graph, test['start'], test['goal'])
  puts "DFS Recursive #{test['start']}->#{test['goal']}: #{result}"
end

data['tests'].each do |test|
  result = dfs_iterative(graph, test['start'], test['goal'])
  puts "DFS Iterative #{test['start']}->#{test['goal']}: #{result}"
end

