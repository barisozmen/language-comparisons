pub fn fibonacci_recursive(n: u32) -> u64 {
    match n {
        0 => 0,
        1 => 1,
        _ => fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2),
    }
}

pub fn fibonacci_iterative(n: u32) -> u64 {
    match n {
        0 => 0,
        1 => 1,
        _ => {
            let mut a = 0;
            let mut b = 1;
            
            for _ in 2..=n {
                let temp = a + b;
                a = b;
                b = temp;
            }
            
            b
        }
    }
}

pub fn fibonacci_memoized(n: u32) -> u64 {
    fn fib_memo(n: u32, memo: &mut std::collections::HashMap<u32, u64>) -> u64 {
        if let Some(&result) = memo.get(&n) {
            return result;
        }
        
        let result = match n {
            0 => 0,
            1 => 1,
            _ => fib_memo(n - 1, memo) + fib_memo(n - 2, memo),
        };
        
        memo.insert(n, result);
        result
    }
    
    fib_memo(n, &mut std::collections::HashMap::new())
}