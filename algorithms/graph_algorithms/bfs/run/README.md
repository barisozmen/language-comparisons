# BFS Test Suite

Test runners for all language implementations. All use identical test cases from `test_cases.json`.

## Running Tests

```bash
# Individual languages
python3 run.py
ruby run.rb
node run.js

# Full benchmark with timing
./benchmark.sh
```

## Test Cases

Shared graph structure:
```
A → B → D
↓   ↓
C   E
↓   ↓
F ← F
```

Tests validate both iterative and bidirectional BFS implementations.
