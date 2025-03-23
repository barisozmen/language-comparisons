# Python Development Environment Setup

This guide will help you set up a Python development environment for contributing to the Programming Language Comparison Project.

## Requirements

- Python 3.8 or newer
- pip (Python package installer)
- virtualenv or venv (for creating isolated environments)
- Git

## Installation Instructions

### Windows

1. **Install Python**:
   - Download the installer from [python.org](https://www.python.org/downloads/)
   - Run the installer, ensuring you check "Add Python to PATH"
   - Verify installation by opening a command prompt and typing:
     ```
     python --version
     pip --version
     ```

2. **Set up Virtual Environment**:
   ```cmd
   cd path\to\language-comparisons
   python -m venv venv
   venv\Scripts\activate
   ```

### macOS

1. **Install Python using Homebrew**:
   ```bash
   brew install python
   ```
   Or download from [python.org](https://www.python.org/downloads/)

2. **Set up Virtual Environment**:
   ```bash
   cd path/to/language-comparisons
   python3 -m venv venv
   source venv/bin/activate
   ```

### Linux

1. **Install Python**:
   - Ubuntu/Debian:
     ```bash
     sudo apt update
     sudo apt install python3 python3-pip python3-venv
     ```
   - Fedora:
     ```bash
     sudo dnf install python3 python3-pip
     ```

2. **Set up Virtual Environment**:
   ```bash
   cd path/to/language-comparisons
   python3 -m venv venv
   source venv/bin/activate
   ```

## Required Packages

Once your virtual environment is activated, install the required packages:

```bash
pip install pytest numpy matplotlib pandas
```

## IDE Recommendations

We recommend using one of the following IDEs for Python development:

1. **Visual Studio Code**:
   - Install from [code.visualstudio.com](https://code.visualstudio.com/)
   - Install the Python extension from the marketplace
   - Configure to use your virtual environment

2. **PyCharm**:
   - Install from [jetbrains.com](https://www.jetbrains.com/pycharm/)
   - The Community Edition is free and sufficient for this project
   - Set up your project to use the virtual environment

## Code Style

This project follows the [PEP 8](https://www.python.org/dev/peps/pep-0008/) style guide. Consider installing and using:

```bash
pip install flake8 black
```

- Use `flake8` to check your code for style issues
- Use `black` to automatically format your code

## Running Tests

```bash
pytest algorithms/your_algorithm/test_your_algorithm.py
```

## Troubleshooting

If you encounter any issues with your Python setup, please check the following:

1. Python version compatibility
2. PATH environment variable settings
3. Virtual environment activation
4. Package installation errors

For more help, consult the [Python documentation](https://docs.python.org/) or open an issue in the project repository.

