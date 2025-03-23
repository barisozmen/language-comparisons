# Scheme Development Environment Setup

This guide will help you set up a Scheme development environment for contributing to the Programming Language Comparison Project.

## Requirements

- A Scheme interpreter or compiler (we'll use Guile or Racket)
- Text editor with Scheme support
- Git
- Basic familiarity with command-line tools

## Installation Instructions

### Windows

1. **Install Racket** (recommended for Windows):
   - Download the installer from [racket-lang.org](https://racket-lang.org/download/)
   - Run the installer and follow the prompts
   - Add Racket to your PATH
   - Verify installation:
     ```
     racket --version
     ```

2. **Alternative: Install Guile using MSYS2**:
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

1. **Install Racket using Homebrew**:
   ```bash
   brew install --cask racket
   ```

2. **Alternative: Install Guile using Homebrew**:
   ```bash
   brew install guile
   ```

3. **Verify installation**:
   ```bash
   racket --version  # or
   guile --version
   ```

### Linux

1. **Install Guile**:
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

2. **Alternative: Install Racket**:
   - Ubuntu/Debian:
     ```bash
     sudo apt install racket
     ```
   - Fedora:
     ```bash
     sudo dnf install racket
     ```
   - Arch Linux:
     ```bash
     sudo pacman -S racket
     ```

3. **Verify installation**:
   ```bash
   guile --version
   # or
   racket --version
   ```

## IDE Recommendations

1. **Visual Studio Code**:
   - Install from [code.visualstudio.com](https://code.visualstudio.com/)
   - Install the "Magic Racket" extension for Racket support
   - Or install "vscode-scheme" for general Scheme support

2. **Emacs** (traditional choice for Scheme development):
   - Install Emacs from your package manager or [gnu.org/software/emacs](https://www.gnu.org/software/emacs/)
   - Install Geiser mode:
     ```
     M-x package-install RET geiser RET
     ```
   - Configure in your .emacs file:
     ```elisp
     (require 'geiser)
     (setq geiser-active-implementations '(guile racket))
     ```

3. **DrRacket** (comes with Racket):
   - Integrated development environment specific to Racket
   - Includes debugger, documentation, and REPL

4. **Vim/Neovim**:
   - Install vim-lisp-syntax or similar plugin
   - Consider rainbow parentheses plugins for better readability

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

2. **Using Racket's rackunit**:
   ```scheme
   #lang racket
   (require rackunit)
   (require "fibonacci.rkt")
   
   (check-equal? (fibonacci-iterative 10) 55 "fibonacci of 10")
   ```

3. **Run tests**:
   - For basic Scheme:
     ```bash
     guile test-fibonacci.scm
     ```
   - For Racket:
     ```bash
     racket test-fibonacci.rkt
     ```

## Troubleshooting

1. **Installation issues**:
   - Ensure your package manager has the latest repositories
   - Check system requirements for each implementation
   - On Windows, try installing in a directory without spaces

2. **Library/module loading errors**:
   - Check your load paths are correctly set
   - Verify file extensions match the implementation (.scm for Guile, .rkt for Racket)
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
   - Guile: [Guile Manual](https://www.gnu.org/software/guile/manual/)
   - Racket: [Racket Documentation](https://docs.racket-lang.org/)
   - Community: [Scheme Reddit](https://www.reddit.com/r/scheme/)

If you encounter persistent issues, please open an issue in the project repository with details about your environment and the problem you're facing.

