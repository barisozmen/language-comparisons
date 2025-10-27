// Conway's Game of Life - C implementation
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 1024

typedef struct Cell {
    int x, y;
    struct Cell* next;
} Cell;

typedef struct {
    Cell* buckets[HASH_SIZE];
    int count;
} CellSet;

unsigned int hash_cell(int x, int y) {
    return (unsigned int)(x * 73856093 ^ y * 19349663) % HASH_SIZE;
}

CellSet* create_set() {
    CellSet* set = (CellSet*)calloc(1, sizeof(CellSet));
    return set;
}

int contains(CellSet* set, int x, int y) {
    unsigned int h = hash_cell(x, y);
    Cell* curr = set->buckets[h];
    while (curr) {
        if (curr->x == x && curr->y == y) return 1;
        curr = curr->next;
    }
    return 0;
}

void insert(CellSet* set, int x, int y) {
    if (contains(set, x, y)) return;
    
    unsigned int h = hash_cell(x, y);
    Cell* cell = (Cell*)malloc(sizeof(Cell));
    cell->x = x;
    cell->y = y;
    cell->next = set->buckets[h];
    set->buckets[h] = cell;
    set->count++;
}

int neighbor_count(int x, int y, CellSet* cells) {
    int count = 0;
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if ((dx != 0 || dy != 0) && contains(cells, x + dx, y + dy)) {
                count++;
            }
        }
    }
    return count;
}

CellSet* step(CellSet* cells) {
    CellSet* candidates = create_set();
    
    // Add all live cells and their neighbors
    for (int i = 0; i < HASH_SIZE; i++) {
        Cell* curr = cells->buckets[i];
        while (curr) {
            insert(candidates, curr->x, curr->y);
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    if (dx != 0 || dy != 0) {
                        insert(candidates, curr->x + dx, curr->y + dy);
                    }
                }
            }
            curr = curr->next;
        }
    }
    
    CellSet* next_gen = create_set();
    for (int i = 0; i < HASH_SIZE; i++) {
        Cell* curr = candidates->buckets[i];
        while (curr) {
            int count = neighbor_count(curr->x, curr->y, cells);
            int alive = contains(cells, curr->x, curr->y);
            if ((alive && (count == 2 || count == 3)) || (!alive && count == 3)) {
                insert(next_gen, curr->x, curr->y);
            }
            curr = curr->next;
        }
    }
    
    // Free candidates
    for (int i = 0; i < HASH_SIZE; i++) {
        Cell* curr = candidates->buckets[i];
        while (curr) {
            Cell* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    free(candidates);
    
    return next_gen;
}

void free_set(CellSet* set) {
    for (int i = 0; i < HASH_SIZE; i++) {
        Cell* curr = set->buckets[i];
        while (curr) {
            Cell* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    free(set);
}

