# Lisp Interpreter

A collection of minimal Lisp interpreters across multiple languages, inspired by Peter Norvig's legendary implementation philosophy: *"Programs must be written for people to read, and only incidentally for machines to execute."*

## Overview

This directory showcases how a Lisp (Scheme) interpreter can be elegantly implemented in C, C++, JavaScript, Python, Ruby, Rust, and Scheme itself. Each implementation follows the same architectural pattern pioneered by Peter Norvig in his famous essay ["(How to Write a (Lisp) Interpreter (in Python))"](http://norvig.com/lispy.html):

1. **Tokenize**: Convert input string to tokens
2. **Parse**: Build abstract syntax tree from tokens  
3. **Eval**: Execute the AST in an environment
4. **Environment**: Symbol table with lexical scoping

## Language Comparison

### Python (`lisp.py`)

**Lines of Code**: ~120  
**Key Features**: Most elegant and minimal, closest to Norvig's original  
**Highlights**:
- Python's dynamic typing makes it natural for implementing Lisp
- Dictionary-based environment with inheritance via `outer` reference
- Lambda creates proper closures automatically
- Type annotations for clarity without sacrificing simplicity

```python
def eval(x: Exp, env=global_env) -> Any:
    if isinstance(x, Symbol):
        return env.find(x)[x]
    elif not isinstance(x, list):
        return x
    op, *args = x
    if op == 'quote':
        return args[0]
    # ... special forms ...
```

**Why it's elegant**: Pattern matching through `isinstance`, unpacking with `*args`, and natural recursion make the eval function read like a specification.

---

### JavaScript (`lisp.js`)

**Lines of Code**: ~155  
**Key Features**: Functional programming with first-class functions  
**Highlights**:
- Class-based Environment with prototype chain mimicking Lisp's scope
- Array methods (`map`, `reduce`, `flat`) for natural list processing
- Arrow functions create closures for lambda
- Built-in REPL using Node.js readline

```javascript
function evaluate(x, env = globalEnv) {
    if (typeof x === 'string') return env.get(x);
    if (!Array.isArray(x)) return x;
    const [op, ...args] = x;
    // ... special forms ...
}
```

**Why it's elegant**: JavaScript's functional nature and dynamic typing make it feel close to Lisp itself. Destructuring and spread operators keep code minimal.

---

### Ruby (`lisp.rb`)

**Lines of Code**: ~166  
**Key Features**: Expressive syntax with powerful blocks and procs  
**Highlights**:
- Symbols as first-class values (perfect for Lisp!)
- Flexible hash-based environment with natural syntax
- Procs/lambdas with `->` syntax for closures
- Pattern matching through case statements
- Ruby's expressiveness makes code read naturally

```ruby
def lisp_eval(x, env = $global_env)
  if x.is_a?(Symbol)
    env[x] || (raise "undefined symbol: #{x}")
  elsif !x.is_a?(Array)
    x
  else
    op, *args = x
    case op
    when :quote then args[0]
    when :lambda
      params, body = args
      ->(*vals) { lisp_eval(body, Env.new(params, vals, env)) }
    # ... more special forms ...
    end
  end
end
```

**Why it's elegant**: Ruby's symbols are a natural fit for Lisp symbols, and the `->` lambda syntax plus splat operators make the code remarkably clean. Ruby's flexibility lets us write code that feels like a DSL.

---

### Rust (`lisp.rs`)

**Lines of Code**: ~270  
**Key Features**: Type-safe with zero-cost abstractions  
**Highlights**:
- Enum-based expression type (sum types)
- `Rc<Env>` for shared ownership of environments
- Pattern matching on expression types
- Result type for error handling
- First-class functions via closures

```rust
fn eval(x: &Exp, env: &Rc<Env>) -> Result<Exp, String> {
    match x {
        Exp::Symbol(var) => env.find(var).ok_or(...),
        Exp::Number(_) => Ok(x.clone()),
        Exp::List(list) => { /* ... */ }
        _ => Ok(x.clone()),
    }
}
```

**Why it's notable**: Despite Rust's strict type system, the interpreter remains elegant through pattern matching and zero-cost abstractions. Reference counting handles memory without garbage collection.

---

### C++ (`lisp.cpp`)

**Lines of Code**: ~245  
**Key Features**: Object-oriented with STL  
**Highlights**:
- Shared pointers for automatic memory management
- `std::function` for representing procedures
- `std::map` for environments
- `std::vector` for lists
- Static factory methods for expression creation

```cpp
ExpPtr eval(ExpPtr x, EnvPtr env) {
    if (x->type == Exp::Symbol) {
        return env->find(x->symbol);
    }
    // ... type checking and evaluation ...
}
```

**Why it's notable**: Modern C++ features (smart pointers, STL containers) bring it close to high-level languages while maintaining performance. Object-oriented design keeps the code organized.

---

### C (`lisp.c`)

**Lines of Code**: ~365  
**Key Features**: Manual memory management, explicit everything  
**Highlights**:
- Tagged union for expression types
- Manual linked list implementation (cons cells)
- Explicit environment lookup
- Raw pointer manipulation
- No dependencies beyond stdlib

```c
Exp* eval(Exp* exp, Env* env) {
    if (exp->type == T_SYMBOL) {
        return envFind(env, exp->val.symbol);
    }
    // ... explicit type checking ...
}
```

**Why it's notable**: Shows the fundamental data structures (cons cells, symbol tables) that all Lisps are built on. Every abstraction is explicit, making it educational.

---

### Scheme (`lisp.scm`)

**Lines of Code**: ~140  
**Key Features**: Meta-circular evaluator - Lisp implementing Lisp!  
**Highlights**:
- The most conceptually elegant: Lisp interpreting Lisp
- Association lists for environments
- Native Scheme features for implementation
- Demonstrates the homoiconicity of Lisp

```scheme
(define (lisp-eval exp env)
  (cond
    ((number? exp) exp)
    ((symbol? exp) (lookup exp env))
    ((pair? exp)
     (case (car exp)
       ((quote) (cadr exp))
       ((lambda) ...)
       (else (apply (lisp-eval (car exp) env)
                   (map (lambda (arg) (lisp-eval arg env))
                        (cdr exp))))))))
```

**Why it's the most elegant**: When the implementation language *is* Lisp, the interpreter becomes a simple mapping between syntax and semantics. This is the Platonic ideal that all other implementations approximate.

## Feature Comparison

| Feature | Python | JavaScript | Ruby | Rust | C++ | C | Scheme |
|---------|--------|------------|------|------|-----|---|--------|
| LOC | 127 | 170 | 166 | 284 | 310 | 390 | 192 |
| Memory | GC | GC | GC | Rc | shared_ptr | Manual | GC |
| Type System | Dynamic | Dynamic | Dynamic | Static | Static | Static | Dynamic |
| Closures | Native | Native | Native | Native | std::function | Manual | Native |
| Pattern Match | isinstance | typeof | is_a?/case | match | if/else | if/else | cond/case |
| Error Handling | Exception | Exception | Exception | Result | Exception | Return NULL | Exception |
| Readability | ⭐⭐⭐⭐⭐ | ⭐⭐⭐⭐⭐ | ⭐⭐⭐⭐⭐ | ⭐⭐⭐⭐ | ⭐⭐⭐⭐ | ⭐⭐⭐ | ⭐⭐⭐⭐⭐ |

## Common Features Implemented

All interpreters support:

- **Arithmetic**: `+`, `-`, `*`, `/`, `<`, `>`, `=`
- **Special forms**: `quote`, `if`, `define`, `lambda`
- **List operations**: `car`, `cdr`, `cons`, `list`
- **Lexical scoping**: Proper closure creation
- **REPL**: Interactive read-eval-print loop

## Example Usage

All interpreters can run the same Scheme code:

```scheme
;; Define a variable
(define x 10)

;; Lambda and application
((lambda (n) (* n n)) 5)  ; => 25

;; Recursion: factorial
(define fact 
  (lambda (n)
    (if (< n 2)
        1
        (* n (fact (- n 1))))))
(fact 5)  ; => 120

;; Higher-order functions
(define twice
  (lambda (f x)
    (f (f x))))
(twice (lambda (x) (* x 2)) 3)  ; => 12
```

## Running the Interpreters

### Python
```bash
python3 lisp.py
```

### JavaScript
```bash
node lisp.js
```

### Ruby
```bash
ruby lisp.rb
```

### Rust
```bash
rustc lisp.rs && ./lisp
```

### C++
```bash
g++ -std=c++17 lisp.cpp -o lisp && ./lisp
```

### C
```bash
gcc lisp.c -o lisp && ./lisp
```

### Scheme
```bash
# Requires a Scheme implementation (e.g., Guile, Racket, Chicken)
guile lisp.scm
# Or start in the REPL and load it:
# (load "lisp.scm")
# (lisp-repl)
```

## Design Philosophy: The Norvig Way

Peter Norvig's implementation philosophy emphasizes:

1. **Minimalism**: Include only what's necessary
2. **Clarity**: Code should be readable as specification
3. **Elegance**: The simplest solution is often the best
4. **Pedagogy**: Code should teach while it works

Each implementation here strives to embody these principles while respecting the idioms of its host language.

## What's Missing (Intentionally)

To maintain elegance and focus, these interpreters omit:

- Macros (though adding them would be straightforward)
- Tail call optimization (except in languages with native support)
- Full numeric tower
- Continuations
- Module system
- Error recovery

These features, while important for production Lisps, would obscure the core ideas. The goal is education and elegance, not completeness.

## Key Insights

### Why Python, Ruby, JavaScript, and Scheme Are Shortest

The dynamic language implementations are the most concise because:
- All have garbage collection (no manual memory management)
- All have first-class functions (lambdas work naturally)
- All have flexible typing (easy to represent heterogeneous expressions)
- Ruby's symbols are a perfect match for Lisp symbols
- JavaScript's functional features make list processing natural
- Python's clean syntax eliminates boilerplate
- Scheme gets bonus points for being a Lisp (meta-circular = conceptually simple)

### Why C Is Longest

C requires explicit:
- Memory allocation and deallocation
- Type tagging (union + enum)
- Data structure implementation (linked lists from scratch)
- Error handling (no exceptions)
- String manipulation (no built-in string type)

This verbosity is pedagogically valuable: it shows exactly what higher-level languages abstract away.

### Why Rust Is Surprisingly Elegant

Despite static typing and ownership rules, Rust achieves elegance through:
- Pattern matching (cleaner than if/else chains)
- Enums as sum types (perfect for AST nodes)
- `Result<T, E>` for explicit error handling
- Zero-cost abstractions (high-level code, low-level performance)

## Further Reading

- [Peter Norvig: (How to Write a (Lisp) Interpreter (in Python))](http://norvig.com/lispy.html)
- [Peter Norvig: (An ((Even Better) Lisp) Interpreter (in Python))](http://norvig.com/lispy2.html)
- [Structure and Interpretation of Computer Programs](https://mitpress.mit.edu/sites/default/files/sicp/index.html) - The classic text on interpreters
- [Lisp in Small Pieces](https://www.cambridge.org/core/books/lisp-in-small-pieces/66FD2BE3EDDDC68CA87E1F7FC60F765C) - Deep dive into Lisp implementation

## Credits

Inspired by Peter Norvig's legendary minimalist approach to programming. Each implementation attempts to capture the essence of his philosophy: write code that is so clear it serves as its own documentation.

> "Everyone knows that debugging is twice as hard as writing a program in the first place. So if you're as clever as you can be when you write it, how will you ever debug it?" - Brian Kernighan

Keep it simple. Keep it elegant. That's the Norvig way.

