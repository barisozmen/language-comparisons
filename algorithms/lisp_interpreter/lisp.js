#!/usr/bin/env node
/**
 * A minimal Lisp interpreter in JavaScript
 * Inspired by Peter Norvig's legendary implementation
 */

const readline = require('readline');

// Tokenize
function tokenize(chars) {
    return chars.replace(/\(/g, ' ( ').replace(/\)/g, ' ) ').trim().split(/\s+/);
}

// Parse
function parse(program) {
    return readFromTokens(tokenize(program));
}

function readFromTokens(tokens) {
    if (tokens.length === 0) throw new SyntaxError('unexpected EOF');
    const token = tokens.shift();
    if (token === '(') {
        const L = [];
        while (tokens[0] !== ')') {
            L.push(readFromTokens(tokens));
        }
        tokens.shift(); // pop off ')'
        return L;
    } else if (token === ')') {
        throw new SyntaxError('unexpected )');
    } else {
        return atom(token);
    }
}

function atom(token) {
    const num = Number(token);
    return isNaN(num) ? token : num;
}

// Environment
class Env {
    constructor(parms = [], args = [], outer = null) {
        this.dict = {};
        for (let i = 0; i < parms.length; i++) {
            this.dict[parms[i]] = args[i];
        }
        this.outer = outer;
    }
    
    find(varName) {
        return (varName in this.dict) ? this : this.outer.find(varName);
    }
    
    get(varName) {
        return this.find(varName).dict[varName];
    }
    
    set(varName, value) {
        this.dict[varName] = value;
    }
}

function standardEnv() {
    const env = new Env();
    env.dict = {
        '+': (...args) => args.reduce((a, b) => a + b, 0),
        '-': (...args) => args.length === 1 ? -args[0] : args.reduce((a, b) => a - b),
        '*': (...args) => args.reduce((a, b) => a * b, 1),
        '/': (...args) => args.reduce((a, b) => a / b),
        '>': (a, b) => a > b,
        '<': (a, b) => a < b,
        '>=': (a, b) => a >= b,
        '<=': (a, b) => a <= b,
        '=': (a, b) => a === b,
        'abs': Math.abs,
        'append': (...args) => args.flat(),
        'apply': (proc, args) => proc(...args),
        'begin': (...args) => args[args.length - 1],
        'car': (x) => x[0],
        'cdr': (x) => x.slice(1),
        'cons': (x, y) => [x, ...y],
        'eq?': (a, b) => a === b,
        'equal?': (a, b) => JSON.stringify(a) === JSON.stringify(b),
        'length': (x) => x.length,
        'list': (...args) => args,
        'list?': (x) => Array.isArray(x),
        'map': (fn, arr) => arr.map(fn),
        'max': Math.max,
        'min': Math.min,
        'not': (x) => !x,
        'null?': (x) => Array.isArray(x) && x.length === 0,
        'number?': (x) => typeof x === 'number',
        'print': (...args) => console.log(...args),
        'procedure?': (x) => typeof x === 'function',
        'round': Math.round,
        'symbol?': (x) => typeof x === 'string',
    };
    return env;
}

const globalEnv = standardEnv();

// Eval
function evaluate(x, env = globalEnv) {
    if (typeof x === 'string') {         // variable reference
        return env.get(x);
    } else if (!Array.isArray(x)) {      // constant
        return x;
    }
    const [op, ...args] = x;
    if (op === 'quote') {                // quotation
        return args[0];
    } else if (op === 'if') {            // conditional
        const [test, conseq, alt] = args;
        const exp = evaluate(test, env) ? conseq : alt;
        return evaluate(exp, env);
    } else if (op === 'define') {        // definition
        const [symbol, exp] = args;
        env.set(symbol, evaluate(exp, env));
    } else if (op === 'lambda') {        // procedure
        const [parms, body] = args;
        return (...args) => evaluate(body, new Env(parms, args, env));
    } else {                             // procedure call
        const proc = evaluate(op, env);
        const vals = args.map(arg => evaluate(arg, env));
        return proc(...vals);
    }
}

function schemestr(exp) {
    if (Array.isArray(exp)) {
        return '(' + exp.map(schemestr).join(' ') + ')';
    }
    return String(exp);
}

// REPL
function repl() {
    const rl = readline.createInterface({
        input: process.stdin,
        output: process.stdout,
        prompt: 'lisp> '
    });
    
    rl.prompt();
    
    rl.on('line', (line) => {
        try {
            const val = evaluate(parse(line));
            if (val !== undefined) {
                console.log(schemestr(val));
            }
        } catch (e) {
            console.log('Error:', e.message);
        }
        rl.prompt();
    });
    
    rl.on('close', () => {
        console.log('\nBye!');
        process.exit(0);
    });
}

if (require.main === module) {
    repl();
}

module.exports = { tokenize, parse, evaluate, Env, standardEnv };

