# C++ Development Environment Setup

This guide will help you set up a C++ development environment for contributing to the Programming Language Comparison Project.

## Requirements

- C++ compiler with C++14 support (GCC 5+, Clang 3.4+, MSVC 2017+)
- Build system (CMake 3.10+)
- Git
- IDE or text editor
- Debugger (GDB, LLDB, or Visual Studio Debugger)

## Installation Instructions

### Windows

1. **Install Visual Studio** (recommended for Windows):
   - Download [Visual Studio Community](https://visualstudio.microsoft.com/vs/community/)
   - During installation, select "Desktop development with C++"
   - This includes the MSVC compiler, debugger, and necessary tools

2. **Alternative: MinGW-w64**:
   - Download [MinGW-w64](https://www.mingw-w64.org/downloads/) or use [MSYS2](https://www.msys2.org/)
   - Using MSYS2:
     ```
     pacman -S mingw-w64-x86_64-gcc
     pacman -S mingw-w64-x86_64-gdb
     pacman -S mingw-w64-x86_64-cmake
     ```
   - Add the bin directory to your PATH
   - Verify installation:
     ```
     g++ --version
     cmake --version
     ```

3. **Install CMake** (if not already installed):
   - Download from [cmake.org](https://cmake.org/download/)
   - Ensure "Add CMake to the system PATH" is selected during installation

### macOS

1. **Install Xcode Command Line Tools**:
   ```bash
   xcode-select --install
   ```

2. **Install Homebrew**:
   ```bash
   /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
   ```

3. **Install required tools**:
   ```bash
   brew install cmake
   brew install llvm  # For latest clang (optional)
   ```

4. **Verify installation**:
   ```bash
   g++ --version    # Or clang++ --version
   cmake --version
   ```

### Linux

1. **Install C++ development tools**:
   - Ubuntu/Debian:
     ```bash
     sudo apt update
     sudo apt install build-essential cmake gdb
     ```
   - Fedora:
     ```bash
     sudo dnf install gcc-c++ cmake gdb
     ```
   - Arch Linux:
     ```bash
     sudo pacman -S base-devel cmake gdb
     ```

2. **Verify installation**:
   ```bash
   g++ --version
   cmake --version
   gdb --version
   ```

## IDE Recommendations

1. **Visual Studio Code**:
   - Install from [code.visualstudio.com](https://code.visualstudio.com/)
   - Install the C/C++ extension by Microsoft
   - Install the CMake Tools extension
   - Configure IntelliSense, formatting, and debugging in settings.json

2. **CLion** (paid, with free trial):
   - Install from [jetbrains.com](https://www.jetbrains.com/clion/)
   - Excellent CMake integration
   - Powerful refactoring tools and debugger

3. **Visual Studio** (Windows):
   - If already installed with C++ workload
   - Comprehensive debugging and development experience

4. **Qt Creator** (cross-platform, free):
   - Good for C++ even without Qt development
   - Install from [qt.io](https://www.qt.io/download)

## Code Style

This project follows the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html) with some modifications:

1. **Naming**:
   - Classes/Structs: `CamelCase`
   - Functions/Methods: `CamelCase`
   - Variables: `snake_case`
   - Constants/Enums: `kCamelCase`
   - Macros: `UPPER_CASE`

2. **Formatting**:
   - Indentation: 2 spaces (no tabs)
   - Line length: max 80 characters
   - Opening braces on the same line
   - Spaces around operators and after commas

3. **Use modern C++ features** (C++14):
   - Smart pointers instead of raw pointers
   - Range-based for loops
   - Auto type deduction where appropriate
   - Lambda expressions

4. **Code organization**:
   - One class per file when practical
   - Use namespaces
   - Group related functions and classes

Here's a formatting example:

```cpp
#include <iostream>
#include <vector>
#include <memory>

namespace language_comparison {

class Fibonacci {
 public:
  // Calculates the nth Fibonacci number iteratively
  static int CalculateIterative(int n) {
    if (n <= 1) {
      return n;
    }
    
    int a = 0;
    int b = 1;
    int result = 0;
    
    for (int i = 2; i <= n; ++i) {
      result = a + b;
      a = b;
      b = result;
    }
    
    return result;
  }
  
  // Calculates the nth Fibonacci number recursively
  static int CalculateRecursive(int n) {
    if (n <= 1) {
      return n;
    }
    return CalculateRecursive(n - 1) + CalculateRecursive(n - 2);
  }
};

}  // namespace language_comparison
```

## Running Tests

We use [Google Test](https://github.com/google/googletest) for C++ unit testing:

1. **Install Google Test**:
   - It will be automatically downloaded and built by CMake in our setup

2. **Write tests** in a file named `test_your_algorithm.cpp`:
   ```cpp
   #include "gtest/gtest.h"
   #include "your_algorithm.h"

   TEST(YourAlgorithmTest, TestCase1) {
     EXPECT_EQ(language_comparison::YourClass::YourFunction(input), expected_output);
   }
   ```

3. **Build and run tests**:
   ```bash
   mkdir -p build && cd build
   cmake ..
   make
   ./test_your_algorithm
   ```

## Troubleshooting

1. **Compiler errors**:
   - Check you're using the right C++ standard: `-std=c++14`
   - Verify include paths and dependencies
   - Look for missing namespace qualifiers

2. **Linker errors**:
   - Ensure all functions are implemented
   - Check for circular dependencies
   - Verify library linking order

3. **CMake errors**:
   - Ensure minimum required version is set correctly
   - Check paths to source files
   - Verify target names in add_executable() and target_link_libraries()

4. **Debugging tips**:
   - Use debugger breakpoints instead of print statements
   - Check for memory issues with sanitizers:
     ```bash
     g++ -fsanitize=address -g file.cpp
     ```
   - Use Valgrind for memory leak detection

5. **IDE-specific issues**:
   - For VS Code: Regenerate intellisense configuration with Ctrl+Shift+P > "C/C++: Edit Configurations"
   - For Visual Studio: Clean solution and rebuild
   - For CLion: Invalidate caches and restart

For more help, consult the C++ reference documentation or open an issue in the project repository.

