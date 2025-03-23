# C Development Environment Setup

This guide will help you set up a C development environment for contributing to the Programming Language Comparison Project.

## Requirements

- C compiler (GCC, Clang, or MSVC)
- Build system (Make, CMake)
- Git
- Text editor or IDE
- Debugger (GDB or LLDB)

## Installation Instructions

### Windows

1. **Install MinGW (Minimalist GNU for Windows)**:
   - Download [MinGW-w64](https://www.mingw-w64.org/downloads/) or use [MSYS2](https://www.msys2.org/)
   - Using MSYS2 (recommended):
     ```
     pacman -S mingw-w64-x86_64-gcc
     pacman -S mingw-w64-x86_64-gdb
     pacman -S mingw-w64-x86_64-make
     ```
   - Add the bin directory to your PATH
   - Verify installation:
     ```
     gcc --version
     make --version
     ```

2. **Alternative: Install Visual Studio with C/C++ tools**:
   - Download [Visual Studio Community](https://visualstudio.microsoft.com/vs/community/)
   - During installation, select "Desktop development with C++"
   - This includes the MSVC compiler and necessary tools

3. **Install CMake**:
   - Download from [cmake.org](https://cmake.org/download/)
   - Add to PATH during installation

### macOS

1. **Install Xcode Command Line Tools**:
   ```bash
   xcode-select --install
   ```

2. **Install Homebrew (optional but recommended)**:
   ```bash
   /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
   ```

3. **Install additional tools**:
   ```bash
   brew install cmake
   ```

4. **Verify installation**:
   ```bash
   gcc --version
   clang --version
   make --version
   cmake --version
   ```

### Linux

1. **Install C development tools**:
   - Ubuntu/Debian:
     ```bash
     sudo apt update
     sudo apt install build-essential gdb cmake
     ```
   - Fedora:
     ```bash
     sudo dnf install gcc gcc-c++ gdb make cmake
     ```
   - Arch Linux:
     ```bash
     sudo pacman -S base-devel gdb cmake
     ```

2. **Verify installation**:
   ```bash
   gcc --version
   make --version
   cmake --version
   gdb --version
   ```

## IDE Recommendations

1. **Visual Studio Code**:
   - Install from [code.visualstudio.com](https://code.visualstudio.com/)
   - Install the C/C++ extension by Microsoft
   - Install the CMake Tools extension
   - Configure IntelliSense and debugging in settings.json

2. **CLion** (paid, with free trial):
   - Install from [jetbrains.com](https://www.jetbrains.com/clion/)
   - Includes built-in support for CMake
   - Powerful debugger integration

3. **Visual Studio** (Windows):
   - Use the IDE that comes with the C++ workload
   - Full-featured debugging and IntelliSense

4. **Code::Blocks** (free, cross-platform):
   - Install from [codeblocks.org](http://www.codeblocks.org/)
   - Choose the version with MinGW for Windows

## Code Style

This project follows a style based on the [Linux kernel coding style](https://www.kernel.org/doc/html/v4.10/process/coding-style.html) with modifications:

1. **Indentation**: Use 4 spaces (not tabs)
2. **Line length**: Max 80 characters
3. **Braces**: Opening brace on the same line, closing brace on its own line
4. **Naming**:
   - Use snake_case for variables and functions
   - Use UPPER_CASE for macros and constants
5. **Comments**: Use /* */ for block comments and // for line comments

Example:
```c
/*
 * Function: calculate_fibonacci
 * ----------------------------
 * Calculates the nth Fibonacci number
 *
 * n: position in the Fibonacci sequence
 *
 * returns: the nth Fibonacci number
 */
int calculate_fibonacci(int n) {
    if (n <= 1) {
        return n;
    }
    
    int a = 0, b = 1, temp;
    for (int i = 2; i <= n; i++) {
        temp = a + b;
        a = b;
        b = temp;
    }
    
    return b;
}
```

## Running Tests

For this project, we use a simple testing framework with these steps:

1. **Compile your code with tests**:
   ```bash
   gcc -o test_algorithm algorithms/your_algorithm/your_algorithm.c tests/test_your_algorithm.c -lm
   ```

2. **Run the tests**:
   ```bash
   ./test_algorithm
   ```

3. **Using Make (if provided)**:
   ```bash
   make test
   ```

## Troubleshooting

1. **Compiler errors**:
   - Check your include paths
   - Verify library linkage with `-l` flags
   - Ensure you're using C99 or C11 with `-std=c99` or `-std=c11`

2. **Undefined references**:
   - Make sure all functions are properly declared and defined
   - Check library linkage order (dependent libraries should come last)

3. **Segmentation faults**:
   - Use a debugger: `gdb ./your_program`
   - Add debugging printfs to identify the issue

4. **Memory leaks**:
   - Use Valgrind: `valgrind --leak-check=full ./your_program`

5. **Build system issues**:
   - Ensure proper paths in Makefiles or CMakeLists.txt
   - Check environment variables (PATH, C_INCLUDE_PATH)

For more help, check the GCC documentation or open an issue in the project repository.

