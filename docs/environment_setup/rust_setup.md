# Rust Development Environment Setup

This guide will help you set up a Rust development environment for contributing to the Programming Language Comparison Project.

## Requirements

- A computer running Windows, macOS, or Linux
- Internet connection
- Approximately 500MB of free disk space
- Basic familiarity with command-line interfaces

## Installation Instructions

### Windows

1. **Install Rust using rustup (recommended)**
   - Download the rustup installer from [rustup.rs](https://rustup.rs/)
   - Run the downloaded executable and follow the on-screen instructions
   - Choose the default installation options when prompted
   - After installation, open a new command prompt to ensure the PATH is updated

2. **Verify installation**
   ```
   rustc --version
   cargo --version
   ```

3. **Visual C++ Build Tools (required for compilation)**
   - Install the [Visual Studio Build Tools](https://visualstudio.microsoft.com/visual-cpp-build-tools/)
   - During installation, select "C++ build tools" and ensure the Windows 10 SDK is included

### macOS

1. **Install Rust using rustup**
   ```bash
   curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
   ```

2. **Follow the on-screen instructions**
   - Choose the default installation option (1) when prompted
   - After installation, run the following to configure your current shell:
   ```bash
   source "$HOME/.cargo/env"
   ```

3. **Verify installation**
   ```bash
   rustc --version
   cargo --version
   ```

4. **Install Xcode Command Line Tools (if not already installed)**
   ```bash
   xcode-select --install
   ```

### Linux

1. **Install required dependencies**
   
   For Debian/Ubuntu:
   ```bash
   sudo apt update
   sudo apt install build-essential curl
   ```
   
   For Fedora:
   ```bash
   sudo dnf install gcc curl
   ```
   
   For Arch Linux:
   ```bash
   sudo pacman -S base-devel curl
   ```

2. **Install Rust using rustup**
   ```bash
   curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
   ```

3. **Follow the on-screen instructions**
   - Choose the default installation option (1) when prompted
   - After installation, run the following to configure your current shell:
   ```bash
   source "$HOME/.cargo/env"
   ```

4. **Verify installation**
   ```bash
   rustc --version
   cargo --version
   ```

## IDE Recommendations

1. **Visual Studio Code**
   - Install [VS Code](https://code.visualstudio.com/)
   - Install the [rust-analyzer](https://marketplace.visualstudio.com/items?itemName=rust-lang.rust-analyzer) extension
   - Optional: Install [CodeLLDB](https://marketplace.visualstudio.com/items?itemName=vadimcn.vscode-lldb) for debugging

2. **JetBrains IntelliJ IDEA**
   - Install [IntelliJ IDEA](https://www.jetbrains.com/idea/) (Community Edition is free)
   - Install the [Rust plugin](https://plugins.jetbrains.com/plugin/8182-rust)

3. **Vim/Neovim**
   - Install [rust-analyzer](https://rust-analyzer.github.io/) for your system
   - Configure with a plugin like [coc.nvim](https://github.com/neoclide/coc.nvim) or native LSP support

## Code Style

1. **Use rustfmt for consistent formatting**
   - rustfmt is installed by default with rustup
   - Format your code with:
   ```bash
   cargo fmt
   ```

2. **Use clippy for linting**
   - Install clippy if not already installed:
   ```bash
   rustup component add clippy
   ```
   - Run clippy on your code:
   ```bash
   cargo clippy
   ```

3. **Follow the Rust API Guidelines**
   - Refer to the [Rust API Guidelines](https://rust-lang.github.io/api-guidelines/) for best practices

## Running Tests

1. **Run all tests**
   ```bash
   cargo test
   ```

2. **Run specific tests**
   ```bash
   cargo test test_name
   ```

3. **Run tests with output**
   ```bash
   cargo test -- --nocapture
   ```

4. **Run tests with specific features**
   ```bash
   cargo test --features "feature1 feature2"
   ```

## Troubleshooting

1. **Rust not found after installation**
   - Ensure `~/.cargo/bin` is in your PATH
   - For Windows, restart your command prompt
   - For macOS/Linux, run `source "$HOME/.cargo/env"` or restart your terminal

2. **Compilation errors on Windows**
   - Ensure Visual C++ Build Tools are properly installed
   - Try running `rustup update` to ensure you have the latest toolchain

3. **Permission errors during installation**
   - On Linux/macOS, try running the installation command with sudo
   - Ensure you have write permissions to the installation directory

4. **Slow compilation times**
   - Consider using `cargo check` instead of `cargo build` for quick syntax verification
   - Enable incremental compilation in your `Cargo.toml`:
     ```toml
     [build]
     incremental = true
     ```

5. **Getting help**
   - Visit the [Rust User Forums](https://users.rust-lang.org/)
   - Join the [Rust Discord server](https://discord.gg/rust-lang)
   - Check the [Rust documentation](https://doc.rust-lang.org/)
