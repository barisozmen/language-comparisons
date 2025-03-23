# Setting Up and Using the LOC Tool

This guide explains how to install and use the [loc](https://github.com/cgag/loc) tool for counting lines of code in our language comparison project.

## What is loc?

`loc` is a fast line counting tool with support for many languages. We use it to analyze the size and complexity of implementations across different programming languages.

## Installation

### From Prebuilt Binaries

1. Go to [https://github.com/cgag/loc/releases](https://github.com/cgag/loc/releases)
2. Download the appropriate binary for your operating system
3. Extract the archive and place the binary in a directory that's in your PATH

### Using Cargo (Rust Package Manager)

If you have Rust installed:

```bash
cargo install loc
```

### Building from Source

1. Clone the repository:
   ```bash
   git clone https://github.com/cgag/loc
   cd loc
   ```

2. Build with Cargo:
   ```bash
   cargo build --release
   ```

3. The binary will be in `target/release/loc`

## Basic Usage

Count lines of code in a specific directory:

```bash
loc algorithms/fibonacci
```

Count lines of code in a specific file:

```bash
loc algorithms/fibonacci/fibonacci.py
```

## Project-Specific Usage

### Generating Line Count Reports

For our project, we'll use `loc` to generate standard reports. The script below can be used:

```bash
# Count lines for a specific algorithm across all languages
loc algorithms/fibonacci > reports/fibonacci_loc.md

# Count lines for a specific design pattern across all languages
loc design_patterns/observer > reports/observer_pattern_loc.md

# Count lines for a specific language across all implementations
loc --include='*.py' . > reports/python_implementations_loc.md
```

### Interpreting the Results

The `loc` tool provides information on:
- Total lines of code
- Code lines (not including comments or blanks)
- Comment lines
- Blank lines
- Files analyzed

These metrics help us compare the verbosity and complexity of different language implementations.

## Configuration for CI/CD

To integrate `loc` into continuous integration, add the following to your CI workflow:

```yaml
- name: Install loc
  run: cargo install loc

- name: Run line count analysis
  run: |
    loc algorithms > reports/algorithms_loc.md
    loc design_patterns > reports/design_patterns_loc.md
```

## Advanced Usage

### Filtering by Language

```bash
loc --include='*.py' --include='*.js' .
```

### Excluding Directories

```bash
loc --exclude-dir=node_modules --exclude-dir=venv .
```

### JSON Output

```bash
loc --format=json . > loc_stats.json
```

## Troubleshooting

If you encounter issues with `loc`:

1. Ensure you're using the latest version
2. Check that the binary is properly installed and in your PATH
3. For permission issues on Unix systems, make the binary executable: `chmod +x loc`

## Additional Resources

- [loc GitHub Repository](https://github.com/cgag/loc)
- [Documentation](https://github.com/cgag/loc/blob/master/README.md)

For further assistance, please open an issue in our project repository. 