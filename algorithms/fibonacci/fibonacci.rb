def fibonacci_recursive(n)
  return n if n <= 1
  fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2)
end


def fibonacci_iterative(n)
  return n if n <= 1
  
  a, b = 0, 1
  (2..n).each do
    a, b = b, a + b
  end
  
  b
end


def fibonacci_memoized(n, memo = {})
  return memo[n] if memo.key?(n)
  return n if n <= 1
  
  memo[n] = fibonacci_memoized(n - 1, memo) + fibonacci_memoized(n - 2, memo)
end
