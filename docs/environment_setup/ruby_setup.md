# Ruby Setup Guide

## Installation

### Linux (Ubuntu/Debian)
```bash
# Using apt
sudo apt update
sudo apt install ruby-full

# Or using rbenv (recommended for multiple versions)
curl -fsSL https://github.com/rbenv/rbenv-installer/raw/main/bin/rbenv-installer | bash
rbenv install 3.2.0
rbenv global 3.2.0
```

### macOS
```bash
# Using Homebrew
brew install ruby

# Or using rbenv
brew install rbenv ruby-build
rbenv install 3.2.0
rbenv global 3.2.0
```

### Windows
Download and install from [RubyInstaller](https://rubyinstaller.org/)

## Verify Installation
```bash
ruby --version
```

## Running Ruby Programs

### Execute directly
```bash
ruby fibonacci.rb
```

### Interactive shell
```bash
irb
```

## Benchmarking Ruby Code
```bash
ruby -e "require 'benchmark'; require_relative 'fibonacci'; puts Benchmark.measure { fibonacci_iterative(35) }"
```

## Common Performance Tips
- Use iterative approaches over recursion for better performance
- Ruby has built-in memoization with Hash objects
- Consider using JRuby for performance-critical applications
