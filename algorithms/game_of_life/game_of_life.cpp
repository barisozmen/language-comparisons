// Conway's Game of Life - C++ implementation
#include <iostream>
#include <unordered_set>
#include <vector>

namespace std {
  template<>
  struct hash<pair<int, int>> {
    size_t operator()(const pair<int, int>& p) const {
      return hash<int>()(p.first) ^ (hash<int>()(p.second) << 1);
    }
  };
}

using Cell = std::pair<int, int>;
using CellSet = std::unordered_set<Cell>;

std::vector<Cell> neighbors(const Cell& cell) {
  std::vector<Cell> result;
  for (int dx = -1; dx <= 1; ++dx) {
    for (int dy = -1; dy <= 1; ++dy) {
      if (dx != 0 || dy != 0) {
        result.push_back({cell.first + dx, cell.second + dy});
      }
    }
  }
  return result;
}

int neighbor_count(const Cell& cell, const CellSet& cells) {
  int count = 0;
  for (const auto& n : neighbors(cell)) {
    if (cells.count(n)) ++count;
  }
  return count;
}

CellSet step(const CellSet& cells) {
  CellSet candidates;
  
  // Add all live cells and their neighbors
  for (const auto& cell : cells) {
    candidates.insert(cell);
    for (const auto& n : neighbors(cell)) {
      candidates.insert(n);
    }
  }
  
  CellSet next_gen;
  for (const auto& cell : candidates) {
    int count = neighbor_count(cell, cells);
    bool alive = cells.count(cell) > 0;
    if ((alive && (count == 2 || count == 3)) || (!alive && count == 3)) {
      next_gen.insert(cell);
    }
  }
  
  return next_gen;
}

CellSet life(CellSet cells, int generations) {
  for (int i = 0; i < generations; ++i) {
    cells = step(cells);
  }
  return cells;
}
