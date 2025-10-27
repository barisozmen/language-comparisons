# Conway's Game of Life - Norvig-inspired implementation

def neighbors(cell):
    """Return the 8 neighbors of a cell."""
    x, y = cell
    return {(x+dx, y+dy) for dx in [-1, 0, 1] for dy in [-1, 0, 1] if dx or dy}


def step(cells):
    """Compute next generation of live cells."""
    candidates = cells | {n for cell in cells for n in neighbors(cell)}
    return {cell for cell in candidates if (cell in cells and neighbor_count(cell, cells) in (2, 3)) or 
            (cell not in cells and neighbor_count(cell, cells) == 3)}


def neighbor_count(cell, cells):
    """Count live neighbors of a cell."""
    return sum(n in cells for n in neighbors(cell))


def life(cells, generations):
    """Run Game of Life for given number of generations."""
    for _ in range(generations):
        cells = step(cells)
    return cells

