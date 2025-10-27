// Conway's Game of Life - JavaScript implementation

function neighbors(cell) {
  const [x, y] = cell;
  const result = [];
  for (let dx = -1; dx <= 1; dx++) {
    for (let dy = -1; dy <= 1; dy++) {
      if (dx !== 0 || dy !== 0) {
        result.push([x + dx, y + dy]);
      }
    }
  }
  return result;
}


function neighborCount(cell, cells) {
  return neighbors(cell).filter(([x, y]) => cells.has(`${x},${y}`)).length;
}


function step(cells) {
  const candidates = new Set();
  
  // Add all live cells and their neighbors to candidates
  for (const key of cells) {
    candidates.add(key);
    const [x, y] = key.split(',').map(Number);
    neighbors([x, y]).forEach(([nx, ny]) => candidates.add(`${nx},${ny}`));
  }
  
  const nextGen = new Set();
  for (const key of candidates) {
    const [x, y] = key.split(',').map(Number);
    const count = neighborCount([x, y], cells);
    if ((cells.has(key) && (count === 2 || count === 3)) || 
        (!cells.has(key) && count === 3)) {
      nextGen.add(key);
    }
  }
  
  return nextGen;
}


function life(cells, generations) {
  for (let i = 0; i < generations; i++) {
    cells = step(cells);
  }
  return cells;
}


// Export for Node.js
if (typeof module !== 'undefined' && module.exports) {
  module.exports = { neighbors, neighborCount, step, life };
}
