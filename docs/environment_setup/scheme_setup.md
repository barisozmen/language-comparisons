# Scheme Development Environment Setup

This guide will help you set up a Scheme development environment for contributing to the Programming Language Comparison Project.

## Requirements

- A Scheme interpreter or compiler (we'll use MIT Scheme, Guile, or Chicken Scheme)
- Text editor with Scheme support
- Git
- Basic familiarity with command-line tools

## Installation Instructions

### Windows

1. **Install MIT Scheme**:
   - Download the installer from [MIT Scheme](https://www.gnu.org/software/mit-scheme/)
   - Run the installer and follow the prompts
   - Add MIT Scheme to your PATH
   - Verify installation:
     ```
     scheme --version
     ```

2. **Alternative: Install Chicken Scheme**:
   - Download the installer from [Chicken Scheme](https://www.call-cc.org/download.html)
   - Run the installer and follow the prompts
   - Verify installation:
     ```
     csi -version
     ```

3. **Alternative: Install Guile using MSYS2**:
   - Install [MSYS2](https://www.msys2.org/)
   - Open MSYS2 shell and run:
     ```
     pacman -S mingw-w64-x86_64-guile
     ```
   - Add the MSYS2 bin directory to your PATH
   - Verify installation:
     ```
     guile --version
     ```

### macOS

1. **Install MIT Scheme using Homebrew**:
   ```bash
   brew install mit-scheme
   ```

2. **Install Chicken Scheme using Homebrew**:
   ```bash
   brew install chicken
   ```

3. **Install Guile using Homebrew**:
   ```bash
   brew install guile
   ```

4. **Verify installation**:
   ```bash
   scheme --version  # MIT Scheme
   csi -version      # Chicken Scheme
   guile --version   # Guile
   ```

### Linux

1. **Install MIT Scheme**:
   - Ubuntu/Debian:
     ```bash
     sudo apt update
     sudo apt install mit-scheme
     ```
   - Fedora:
     ```bash
     sudo dnf install mit-scheme
     ```
   - Arch Linux:
     ```bash
     sudo pacman -S mit-scheme
     ```

2. **Install Guile**:
   - Ubuntu/Debian:
     ```bash
     sudo apt update
     sudo apt install guile-3.0  # or available version
     ```
   - Fedora:
     ```bash
     sudo dnf install guile
     ```
   - Arch Linux:
     ```bash
     sudo pacman -S guile
     ```

3. **Install Chicken Scheme**:
   - Ubuntu/Debian:
     ```bash
     sudo apt install chicken-bin
     ```
   - Fedora:
     ```bash
     sudo dnf install chicken
     ```
   - Arch Linux:
     ```bash
     sudo pacman -S chicken
     ```

4. **Verify installation**:
   ```bash
   scheme --version  # MIT Scheme
   csi -version      # Chicken Scheme
   guile --version   # Guile
   ```

## IDE Recommendations

1. **Visual Studio Code**:
   - Install from [code.visualstudio.com](https://code.visualstudio.com/)
   - Install the "vscode-scheme" extension for Scheme support

2. **Emacs** (traditional choice for Scheme development):
   - Install Emacs from your package manager or [gnu.org/software/emacs](https://www.gnu.org/software/emacs/)
   - Install Geiser mode:
     ```
     M-x package-install RET geiser RET
     ```
   - Configure in your .emacs file:
     ```elisp
     (require 'geiser)
     (setq geiser-active-implementations '(mit guile chicken))
     ```

3. **Vim/Neovim**:
   - Install vim-lisp-syntax or similar plugin
   - Consider rainbow parentheses plugins for better readability

4. **Atom**:
   - Install the "language-scheme" package
   - Consider "lisp-paredit" for structural editing

## Code Style

Scheme code should follow these style guidelines:

1. **Indentation**:
   - Use 2 spaces for indentation
   - Align nested expressions vertically when it improves readability

2. **Naming conventions**:
   - Use kebab-case (hyphen-separated words) for identifiers
   - Predicates should end with `?` (e.g., `null?`, `prime?`)
   - Mutators should end with `!` (e.g., `set!`, `vector-set!`)

3. **Parentheses style**:
   - Closing parentheses should be on the same line as the last expression
   - No extra spaces after opening or before closing parentheses

4. **Comments**:
   - Use `;` for single-line comments
   - Use `#|` and `|#` for multi-line comments
   - Document functions with purpose, parameters, and return values

Example:

```scheme
;;; fibonacci.scm -- Fibonacci sequence implementations

;; Calculates the nth Fibonacci number recursively
;; n: a non-negative integer
;; Returns: the nth Fibonacci number
(define (fibonacci-recursive n)
  (cond ((= n 0) 0)
        ((= n 1) 1)
        (else (+ (fibonacci-recursive (- n 1))
                 (fibonacci-recursive (- n 2))))))

;; Calculates the nth Fibonacci number iteratively
;; n: a non-negative integer
;; Returns: the nth Fibonacci number
(define (fibonacci-iterative n)
  (if (< n 2)
      n
      (let loop ((a 0) (b 1) (count 2))
        (if (> count n)
            b
            (loop b (+ a b) (+ count 1))))))
```

## Running Tests

For testing Scheme code, we recommend using a simple testing framework or built-in facilities:

1. **Simple test function**:
   ```scheme
   (define (test-equal name expected actual)
     (if (equal? expected actual)
         (display (string-append "PASS: " name "\n"))
         (display (string-append "FAIL: " name 
                                 " (expected " (display-to-string expected)
                                 ", got " (display-to-string actual) ")\n"))))
   
   ;; Example usage
   (test-equal "fibonacci of 10" 55 (fibonacci-iterative 10))
   ```

2. **Using SRFI-64 (included in many Scheme implementations)**:
   ```scheme
   (import (srfi 64))
   
   (test-begin "fibonacci-tests")
   (test-equal "fibonacci of 10" 55 (fibonacci-iterative 10))
   (test-end)
   ```

3. **Run tests**:
   ```bash
   scheme < test-fibonacci.scm  # MIT Scheme
   csi test-fibonacci.scm       # Chicken Scheme
   guile test-fibonacci.scm     # Guile
   ```

## Troubleshooting

1. **Installation issues**:
   - Ensure your package manager has the latest repositories
   - Check system requirements for each implementation
   - On Windows, try installing in a directory without spaces

2. **Library/module loading errors**:
   - Check your load paths are correctly set
   - Verify file extensions match the implementation (.scm is standard)
   - Use absolute paths if relative paths aren't working

3. **Parentheses matching**:
   - Use an editor with parentheses highlighting
   - Consider using editor features like rainbow parentheses
   - Count opening and closing parentheses manually if needed

4. **Common errors**:
   - "Unbound variable" usually means a typo or missing definition
   - "Wrong number of arguments" check your function calls
   - "Wrong type argument" usually means passing incorrect data types

5. **Finding help**:
   - MIT Scheme: [MIT Scheme Documentation](https://www.gnu.org/software/mit-scheme/documentation/stable/mit-scheme-ref.pdf)
   - Guile: [Guile Manual](https://www.gnu.org/software/guile/manual/)
   - Chicken Scheme: [Chicken Wiki](https://wiki.call-cc.org/)
   - Community: [Scheme Reddit](https://www.reddit.com/r/scheme/)

If you encounter persistent issues, please open an issue in the project repository with details about your environment and the problem you're facing.
