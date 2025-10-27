#!/usr/bin/env python3
"""
A minimal Lisp interpreter in Python
Inspired by Peter Norvig's legendary implementation
"""

import math
import operator as op
from typing import Any, List

# Types
Symbol = str
Number = (int, float)
Atom = (Symbol, Number)
Exp = (Atom, list)

def tokenize(chars: str) -> List[str]:
    """Convert a string into a list of tokens."""
    return chars.replace('(', ' ( ').replace(')', ' ) ').split()

def parse(program: str) -> Exp:
    """Read a Scheme expression from a string."""
    return read_from_tokens(tokenize(program))

def read_from_tokens(tokens: List[str]) -> Exp:
    """Read an expression from a sequence of tokens."""
    if len(tokens) == 0:
        raise SyntaxError('unexpected EOF')
    token = tokens.pop(0)
    if token == '(':
        L = []
        while tokens[0] != ')':
            L.append(read_from_tokens(tokens))
        tokens.pop(0)  # pop off ')'
        return L
    elif token == ')':
        raise SyntaxError('unexpected )')
    else:
        return atom(token)

def atom(token: str) -> Atom:
    """Numbers become numbers; every other token is a symbol."""
    try: return int(token)
    except ValueError:
        try: return float(token)
        except ValueError:
            return Symbol(token)

class Env(dict):
    """An environment: a dict of {'var': val} pairs, with an outer Env."""
    def __init__(self, parms=(), args=(), outer=None):
        self.update(zip(parms, args))
        self.outer = outer
    
    def find(self, var):
        """Find the innermost Env where var appears."""
        return self if (var in self) else self.outer.find(var)

def standard_env() -> Env:
    """An environment with some Scheme standard procedures."""
    env = Env()
    env.update({
        '+': lambda *args: sum(args),
        '-': lambda *args: -args[0] if len(args) == 1 else args[0] - sum(args[1:]),
        '*': lambda *args: __import__('functools').reduce(op.mul, args, 1),
        '/': lambda *args: __import__('functools').reduce(op.truediv, args),
        '>': op.gt, '<': op.lt, '>=': op.ge, '<=': op.le, '=': op.eq,
        'abs': abs, 'append': op.add, 'apply': lambda proc, args: proc(*args),
        'begin': lambda *x: x[-1], 'car': lambda x: x[0],
        'cdr': lambda x: x[1:], 'cons': lambda x, y: [x] + y,
        'eq?': op.is_, 'equal?': op.eq, 'length': len,
        'list': lambda *x: list(x), 'list?': lambda x: isinstance(x, list),
        'map': lambda *args: list(map(*args)), 'max': max, 'min': min,
        'not': op.not_, 'null?': lambda x: x == [], 'number?': lambda x: isinstance(x, Number),
        'print': print, 'procedure?': callable, 'round': round,
        'symbol?': lambda x: isinstance(x, Symbol),
    })
    return env

global_env = standard_env()

def eval(x: Exp, env=global_env) -> Any:
    """Evaluate an expression in an environment."""
    if isinstance(x, Symbol):      # variable reference
        return env.find(x)[x]
    elif not isinstance(x, list):  # constant
        return x
    op, *args = x
    if op == 'quote':              # quotation
        return args[0]
    elif op == 'if':               # conditional
        (test, conseq, alt) = args
        exp = (conseq if eval(test, env) else alt)
        return eval(exp, env)
    elif op == 'define':           # definition
        (symbol, exp) = args
        env[symbol] = eval(exp, env)
    elif op == 'lambda':           # procedure
        (parms, body) = args
        return lambda *args: eval(body, Env(parms, args, env))
    else:                          # procedure call
        proc = eval(op, env)
        vals = [eval(arg, env) for arg in args]
        return proc(*vals)

def repl(prompt='lisp> '):
    """A prompt-read-eval-print loop."""
    while True:
        try:
            val = eval(parse(input(prompt)))
            if val is not None:
                print(schemestr(val))
        except (KeyboardInterrupt, EOFError):
            print('\nBye!')
            break
        except Exception as e:
            print(f'Error: {e}')

def schemestr(exp):
    """Convert a Python object back into a Scheme-readable string."""
    if isinstance(exp, list):
        return '(' + ' '.join(map(schemestr, exp)) + ')'
    else:
        return str(exp)

if __name__ == '__main__':
    repl()

