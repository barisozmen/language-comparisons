# Conway's Game of Life - Ruby implementation
require 'set'

def neighbors(cell)
  x, y = cell
  (-1..1).flat_map { |dx| (-1..1).map { |dy| [x+dx, y+dy] if dx != 0 || dy != 0 } }.compact.to_set
end


def neighbor_count(cell, cells)
  neighbors(cell).count { |n| cells.include?(n) }
end


def step(cells)
  candidates = cells | cells.flat_map { |cell| neighbors(cell) }
  candidates.select do |cell|
    count = neighbor_count(cell, cells)
    (cells.include?(cell) && (count == 2 || count == 3)) || (!cells.include?(cell) && count == 3)
  end.to_set
end


def life(cells, generations)
  generations.times { cells = step(cells) }
  cells
end
