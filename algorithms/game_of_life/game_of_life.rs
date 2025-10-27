// Conway's Game of Life - Rust implementation
use std::collections::HashSet;

type Cell = (i32, i32);

fn neighbors(cell: Cell) -> Vec<Cell> {
    let (x, y) = cell;
    let mut result = Vec::new();
    for dx in -1..=1 {
        for dy in -1..=1 {
            if dx != 0 || dy != 0 {
                result.push((x + dx, y + dy));
            }
        }
    }
    result
}

fn neighbor_count(cell: Cell, cells: &HashSet<Cell>) -> usize {
    neighbors(cell).iter().filter(|n| cells.contains(n)).count()
}

pub fn step(cells: &HashSet<Cell>) -> HashSet<Cell> {
    let mut candidates = HashSet::new();
    
    // Add all live cells and their neighbors
    for &cell in cells {
        candidates.insert(cell);
        for neighbor in neighbors(cell) {
            candidates.insert(neighbor);
        }
    }
    
    candidates
        .into_iter()
        .filter(|&cell| {
            let count = neighbor_count(cell, cells);
            (cells.contains(&cell) && (count == 2 || count == 3)) || 
            (!cells.contains(&cell) && count == 3)
        })
        .collect()
}

pub fn life(mut cells: HashSet<Cell>, generations: usize) -> HashSet<Cell> {
    for _ in 0..generations {
        cells = step(&cells);
    }
    cells
}
