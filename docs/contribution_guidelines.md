# Contribution Guidelines

Thank you for your interest in contributing to the Programming Language Comparison Project! This document provides guidelines and instructions for contributing to the project.

## Table of Contents

1. [Code of Conduct](#code-of-conduct)
2. [Getting Started](#getting-started)
3. [How to Contribute](#how-to-contribute)
4. [Development Process](#development-process)
5. [Coding Standards](#coding-standards)
6. [Pull Request Guidelines](#pull-request-guidelines)
7. [Language-Specific Guidelines](#language-specific-guidelines)
8. [Documentation](#documentation)
9. [Benchmark Considerations](#benchmark-considerations)

## Code of Conduct

This project is committed to providing a welcoming and inclusive environment for all contributors. Please be respectful and considerate of others' viewpoints and experiences.

## Getting Started

1. **Fork the repository** to your GitHub account
2. **Clone your fork** to your local machine
3. **Set up your development environment** by following the guides in `/docs/environment_setup/`
4. **Create a new branch** for your contribution:
   ```bash
   git checkout -b feature/your-feature-name
   ```

## How to Contribute

There are several ways to contribute to this project:

1. **Implement a new algorithm** in one of the supported languages
2. **Implement a design pattern** in one of the supported languages
3. **Improve existing implementations** for better performance or clarity
4. **Add benchmarking features** or improve existing ones
5. **Improve documentation** or add language-specific notes
6. **Fix bugs** in existing implementations or tools
7. **Add a new language** to the comparison set

## Development Process

1. **Check existing issues and PRs** to avoid duplicate work
2. **Claim an issue** by commenting on it, or create a new one
3. **Implement your changes** following the coding standards
4. **Test your implementation** to ensure correctness
5. **Submit a pull request**

## Coding Standards

### General Guidelines

- Write clean, readable code with meaningful variable and function names
- Include comments explaining complex logic or language-specific techniques
- Follow established patterns in the repository for consistency
- Keep implementations comparable across languages (avoid language-specific optimizations unless noted)

### File Structure

- Place implementations in the appropriate directory:
  ```
  algorithms/<algorithm_name>/<algorithm_name>.<language_extension>
  design_patterns/<pattern_category>/<pattern_name>/<pattern_name>.<language_extension>
  ```
- Include a README.md file if adding a new algorithm or pattern
- Add appropriate test cases

## Pull Request Guidelines

1. **Create a descriptive title** for your PR
2. **Reference any related issues** using the syntax `Fixes #123` or `Related to #123`
3. **Provide a clear description** of the changes made
4. **Include benchmark results** if applicable
5. **Make sure all tests pass** before submitting
6. **Keep PRs focused** on a single feature or fix

## Language-Specific Guidelines

### Python
- Follow [PEP 8](https://www.python.org/dev/peps/pep-0008/) style guide
- Use type hints when practical
- Target Python 3.8+ compatibility

### JavaScript
- Follow [Airbnb JavaScript Style Guide](https://github.com/airbnb/javascript)
- Use ES6+ features where appropriate
- Avoid jQuery or framework dependencies

### C
- Follow the [Linux kernel coding style](https://www.kernel.org/doc/html/v4.10/process/coding-style.html)
- Target C99 or later
- Include proper error handling

### C++
- Follow the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)
- Target C++14 or later
- Use STL where appropriate

### Rust
- Follow the [Rust Style Guide](https://doc.rust-lang.org/1.0.0/style/README.html)
- Use idiomatic Rust practices
- Avoid unsafe code when possible

### Scheme
- Follow the [Racket Style Guide](https://docs.racket-lang.org/style/index.html)
- Prefer functional programming patterns
- Document any non-obvious code

## Documentation

- Update or add documentation when necessary
- Include explanations of language-specific features or limitations
- Document any non-standard dependencies or setup requirements
- Add comments explaining the approach taken for each implementation

## Benchmark Considerations

When implementing algorithms that will be benchmarked:

1. Ensure the implementation is correct first, then optimize
2. Make sure the algorithm performs the same work across languages
3. Include appropriate warm-up runs for JIT-compiled languages
4. Document any optimization techniques used
5. Report consistent input sizes and conditions

---

Thank you for contributing to the Programming Language Comparison Project! Your efforts help make this a valuable resource for the programming community. 