// A minimal Lisp interpreter in Rust
// Inspired by Peter Norvig's legendary implementation

use std::collections::HashMap;
use std::io::{self, Write};
use std::rc::Rc;

#[derive(Clone, Debug, PartialEq)]
enum Exp {
    Symbol(String),
    Number(f64),
    List(Vec<Exp>),
    Proc(fn(&[Exp]) -> Result<Exp, String>),
    Lambda(Vec<String>, Box<Exp>, Rc<Env>),
}

impl std::fmt::Display for Exp {
    fn fmt(&self, f: &mut std::fmt::Formatter) -> std::fmt::Result {
        match self {
            Exp::Symbol(s) => write!(f, "{}", s),
            Exp::Number(n) => write!(f, "{}", n),
            Exp::List(list) => {
                write!(f, "(")?;
                for (i, exp) in list.iter().enumerate() {
                    if i > 0 { write!(f, " ")?; }
                    write!(f, "{}", exp)?;
                }
                write!(f, ")")
            }
            Exp::Proc(_) => write!(f, "<procedure>"),
            Exp::Lambda(_, _, _) => write!(f, "<lambda>"),
        }
    }
}

#[derive(Clone)]
struct Env {
    data: HashMap<String, Exp>,
    outer: Option<Rc<Env>>,
}

impl Env {
    fn new() -> Self {
        Env { data: HashMap::new(), outer: None }
    }
    
    fn with_outer(outer: Rc<Env>) -> Self {
        Env { data: HashMap::new(), outer: Some(outer) }
    }
    
    fn find(&self, var: &str) -> Option<Exp> {
        match self.data.get(var) {
            Some(exp) => Some(exp.clone()),
            None => self.outer.as_ref()?.find(var),
        }
    }
    
    fn set(&mut self, var: String, val: Exp) {
        self.data.insert(var, val);
    }
}

fn tokenize(chars: &str) -> Vec<String> {
    chars.replace("(", " ( ")
         .replace(")", " ) ")
         .split_whitespace()
         .map(String::from)
         .collect()
}

fn parse(program: &str) -> Result<Exp, String> {
    let tokens = tokenize(program);
    let mut tokens = tokens.into_iter().peekable();
    read_from_tokens(&mut tokens)
}

fn read_from_tokens(tokens: &mut std::iter::Peekable<std::vec::IntoIter<String>>) -> Result<Exp, String> {
    let token = tokens.next().ok_or("unexpected EOF")?;
    
    if token == "(" {
        let mut list = Vec::new();
        while let Some(t) = tokens.peek() {
            if t == ")" {
                tokens.next();
                return Ok(Exp::List(list));
            }
            list.push(read_from_tokens(tokens)?);
        }
        Err("expected ')'".to_string())
    } else if token == ")" {
        Err("unexpected ')'".to_string())
    } else {
        Ok(atom(&token))
    }
}

fn atom(token: &str) -> Exp {
    match token.parse::<f64>() {
        Ok(n) => Exp::Number(n),
        Err(_) => Exp::Symbol(token.to_string()),
    }
}

fn standard_env() -> Rc<Env> {
    let mut env = Env::new();
    
    env.set("+".to_string(), Exp::Proc(|args| {
        let sum = args.iter().try_fold(0.0, |acc, x| match x {
            Exp::Number(n) => Ok(acc + n),
            _ => Err("+ requires numbers".to_string()),
        })?;
        Ok(Exp::Number(sum))
    }));
    
    env.set("-".to_string(), Exp::Proc(|args| {
        if args.is_empty() { return Err("- requires arguments".to_string()); }
        let first = match &args[0] { Exp::Number(n) => n, _ => return Err("- requires numbers".to_string()) };
        if args.len() == 1 { return Ok(Exp::Number(-first)); }
        let result = args[1..].iter().try_fold(*first, |acc, x| match x {
            Exp::Number(n) => Ok(acc - n),
            _ => Err("- requires numbers".to_string()),
        })?;
        Ok(Exp::Number(result))
    }));
    
    env.set("*".to_string(), Exp::Proc(|args| {
        let product = args.iter().try_fold(1.0, |acc, x| match x {
            Exp::Number(n) => Ok(acc * n),
            _ => Err("* requires numbers".to_string()),
        })?;
        Ok(Exp::Number(product))
    }));
    
    env.set("/".to_string(), Exp::Proc(|args| {
        if args.is_empty() { return Err("/ requires arguments".to_string()); }
        let first = match &args[0] { Exp::Number(n) => n, _ => return Err("/ requires numbers".to_string()) };
        let result = args[1..].iter().try_fold(*first, |acc, x| match x {
            Exp::Number(n) => Ok(acc / n),
            _ => Err("/ requires numbers".to_string()),
        })?;
        Ok(Exp::Number(result))
    }));
    
    env.set("<".to_string(), Exp::Proc(|args| {
        if args.len() != 2 { return Err("< requires 2 arguments".to_string()); }
        match (&args[0], &args[1]) {
            (Exp::Number(a), Exp::Number(b)) => Ok(Exp::Number(if a < b { 1.0 } else { 0.0 })),
            _ => Err("< requires numbers".to_string()),
        }
    }));
    
    env.set(">".to_string(), Exp::Proc(|args| {
        if args.len() != 2 { return Err("> requires 2 arguments".to_string()); }
        match (&args[0], &args[1]) {
            (Exp::Number(a), Exp::Number(b)) => Ok(Exp::Number(if a > b { 1.0 } else { 0.0 })),
            _ => Err("> requires numbers".to_string()),
        }
    }));
    
    env.set("=".to_string(), Exp::Proc(|args| {
        if args.len() != 2 { return Err("= requires 2 arguments".to_string()); }
        Ok(Exp::Number(if args[0] == args[1] { 1.0 } else { 0.0 }))
    }));
    
    env.set("list".to_string(), Exp::Proc(|args| {
        Ok(Exp::List(args.to_vec()))
    }));
    
    env.set("car".to_string(), Exp::Proc(|args| {
        match &args[0] {
            Exp::List(list) if !list.is_empty() => Ok(list[0].clone()),
            _ => Err("car requires non-empty list".to_string()),
        }
    }));
    
    env.set("cdr".to_string(), Exp::Proc(|args| {
        match &args[0] {
            Exp::List(list) if !list.is_empty() => Ok(Exp::List(list[1..].to_vec())),
            _ => Err("cdr requires non-empty list".to_string()),
        }
    }));
    
    Rc::new(env)
}

fn eval(x: &Exp, env: &Rc<Env>) -> Result<Exp, String> {
    match x {
        Exp::Symbol(var) => env.find(var).ok_or(format!("undefined symbol: {}", var)),
        Exp::Number(_) => Ok(x.clone()),
        Exp::List(list) if list.is_empty() => Ok(x.clone()),
        Exp::List(list) => {
            let op = &list[0];
            let args = &list[1..];
            
            if let Exp::Symbol(s) = op {
                match s.as_str() {
                    "quote" => return Ok(args[0].clone()),
                    "if" => {
                        let test = eval(&args[0], env)?;
                        let is_true = match test {
                            Exp::Number(n) => n != 0.0,
                            Exp::List(ref l) => !l.is_empty(),
                            _ => true,
                        };
                        return eval(&args[if is_true { 1 } else { 2 }], env);
                    }
                    "define" => {
                        if let Exp::Symbol(var) = &args[0] {
                            let val = eval(&args[1], env)?;
                            let mut new_env = (**env).clone();
                            new_env.set(var.clone(), val.clone());
                            return Ok(val);
                        }
                        return Err("define requires symbol".to_string());
                    }
                    "lambda" => {
                        if let Exp::List(parms) = &args[0] {
                            let parm_names: Vec<String> = parms.iter()
                                .map(|p| match p {
                                    Exp::Symbol(s) => Ok(s.clone()),
                                    _ => Err("lambda parameters must be symbols".to_string()),
                                })
                                .collect::<Result<Vec<_>, _>>()?;
                            return Ok(Exp::Lambda(parm_names, Box::new(args[1].clone()), env.clone()));
                        }
                        return Err("lambda requires parameter list".to_string());
                    }
                    _ => {}
                }
            }
            
            let proc = eval(op, env)?;
            let vals: Result<Vec<Exp>, String> = args.iter().map(|arg| eval(arg, env)).collect();
            let vals = vals?;
            
            match proc {
                Exp::Proc(f) => f(&vals),
                Exp::Lambda(parms, body, closure_env) => {
                    let mut new_env = Env::with_outer(closure_env);
                    for (parm, val) in parms.iter().zip(vals.iter()) {
                        new_env.set(parm.clone(), val.clone());
                    }
                    eval(&body, &Rc::new(new_env))
                }
                _ => Err("not a procedure".to_string()),
            }
        }
        _ => Ok(x.clone()),
    }
}

fn repl() {
    let env = standard_env();
    let stdin = io::stdin();
    
    loop {
        print!("lisp> ");
        io::stdout().flush().unwrap();
        
        let mut input = String::new();
        if stdin.read_line(&mut input).is_err() {
            break;
        }
        
        let input = input.trim();
        if input.is_empty() {
            continue;
        }
        
        match parse(input) {
            Ok(exp) => match eval(&exp, &env) {
                Ok(val) => println!("{}", val),
                Err(e) => println!("Error: {}", e),
            },
            Err(e) => println!("Parse error: {}", e),
        }
    }
    
    println!("\nBye!");
}

fn main() {
    repl();
}

