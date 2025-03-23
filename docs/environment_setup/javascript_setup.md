# JavaScript Development Environment Setup

This guide will help you set up a JavaScript development environment for contributing to the Programming Language Comparison Project.

## Requirements

- Node.js (LTS version recommended, 16.x or newer)
- npm (comes with Node.js)
- Git

## Installation Instructions

### Windows

1. **Install Node.js**:
   - Download the installer from [nodejs.org](https://nodejs.org/)
   - Run the installer and follow the prompts
   - Verify installation by opening a command prompt and typing:
     ```
     node --version
     npm --version
     ```

2. **Set up Project**:
   ```cmd
   cd path\to\language-comparisons
   npm init -y
   ```

### macOS

1. **Install Node.js using Homebrew**:
   ```bash
   brew install node
   ```
   Or download from [nodejs.org](https://nodejs.org/)

2. **Verify installation**:
   ```bash
   node --version
   npm --version
   ```

3. **Set up Project**:
   ```bash
   cd path/to/language-comparisons
   npm init -y
   ```

### Linux

1. **Install Node.js**:
   - Ubuntu/Debian (using NodeSource):
     ```bash
     curl -fsSL https://deb.nodesource.com/setup_16.x | sudo -E bash -
     sudo apt install -y nodejs
     ```
   - Fedora:
     ```bash
     sudo dnf install nodejs
     ```

2. **Verify installation**:
   ```bash
   node --version
   npm --version
   ```

3. **Set up Project**:
   ```bash
   cd path/to/language-comparisons
   npm init -y
   ```

## Required Packages

For testing and other functionality, install these packages:

```bash
npm install --save-dev jest mocha chai benchmark
```

## IDE Recommendations

We recommend using one of the following IDEs for JavaScript development:

1. **Visual Studio Code**:
   - Install from [code.visualstudio.com](https://code.visualstudio.com/)
   - Useful extensions:
     - ESLint
     - Prettier
     - JavaScript (ES6) code snippets
     - Node.js Extension Pack

2. **WebStorm**:
   - Install from [jetbrains.com](https://www.jetbrains.com/webstorm/)
   - Paid IDE but has a 30-day trial and free for students

## Code Style

This project follows the [Airbnb JavaScript Style Guide](https://github.com/airbnb/javascript). To enforce this style:

1. Install ESLint and the Airbnb configuration:
   ```bash
   npm install --save-dev eslint eslint-config-airbnb-base eslint-plugin-import
   ```

2. Create an `.eslintrc.js` file in your project root:
   ```javascript
   module.exports = {
     extends: 'airbnb-base',
     env: {
       node: true,
       jest: true,
     },
   };
   ```

3. Add a lint script to your package.json:
   ```json
   "scripts": {
     "lint": "eslint ."
   }
   ```

## Running Tests

We use Jest for testing. Add test scripts to your package.json:

```json
"scripts": {
  "test": "jest",
  "test:watch": "jest --watch"
}
```

Run tests with:

```bash
npm test
```

## Troubleshooting

1. **Node.js installation issues**:
   - Try using [nvm](https://github.com/nvm-sh/nvm) (Node Version Manager) to install and manage Node.js versions
   - For Windows, use [nvm-windows](https://github.com/coreybutler/nvm-windows)

2. **npm permission errors**:
   - On Linux/macOS, see [npm's guide on fixing permissions](https://docs.npmjs.com/resolving-eacces-permissions-errors-when-installing-packages-globally)

3. **Package installation failure**:
   - Try clearing the npm cache: `npm cache clean --force`
   - Delete node_modules folder and package-lock.json, then run `npm install` again

4. **JavaScript runtime errors**:
   - Use Chrome DevTools or Node.js debugger to identify issues
   - Add proper error handling with try/catch blocks

5. **Getting help**:
   - Visit [Stack Overflow](https://stackoverflow.com/questions/tagged/javascript)
   - Check the [Node.js documentation](https://nodejs.org/en/docs/)
   - Check the [npm documentation](https://docs.npmjs.com/)

