#!/usr/bin/env ruby
# A minimal Lisp interpreter in Ruby
# Inspired by Peter Norvig's legendary implementation

# Tokenize
def tokenize(chars)
  chars.gsub('(', ' ( ').gsub(')', ' ) ').split
end

# Parse
def parse(program)
  read_from_tokens(tokenize(program))
end

def read_from_tokens(tokens)
  raise SyntaxError, 'unexpected EOF' if tokens.empty?
  
  token = tokens.shift
  
  if token == '('
    list = []
    list << read_from_tokens(tokens) while tokens[0] != ')'
    tokens.shift # pop off ')'
    list
  elsif token == ')'
    raise SyntaxError, 'unexpected )'
  else
    atom(token)
  end
end

def atom(token)
  # Try integer
  return token.to_i if token =~ /^-?\d+$/
  # Try float
  return token.to_f if token =~ /^-?\d+\.\d+$/
  # Symbol
  token.to_sym
end

# Environment
class Env
  attr_reader :data, :outer
  
  def initialize(params = [], args = [], outer = nil)
    @data = Hash[params.zip(args)]
    @outer = outer
  end
  
  def find(var)
    @data.key?(var) ? self : @outer&.find(var)
  end
  
  def [](var)
    find(var)&.data&.[](var)
  end
  
  def []=(var, val)
    @data[var] = val
  end
end

def standard_env
  env = Env.new
  env.data.merge!({
    :+ => ->(* args) { args.reduce(0, :+) },
    :- => ->(*args) { args.size == 1 ? -args[0] : args.reduce(:-) },
    :* => ->(*args) { args.reduce(1, :*) },
    :/ => ->(*args) { args.reduce(:/) },
    :< => ->(a, b) { a < b },
    :> => ->(a, b) { a > b },
    :<= => ->(a, b) { a <= b },
    :>= => ->(a, b) { a >= b },
    :'=' => ->(a, b) { a == b },
    :abs => ->(x) { x.abs },
    :append => ->(*args) { args.flatten(1) },
    :apply => ->(proc, args) { proc.call(*args) },
    :begin => ->(*args) { args.last },
    :car => ->(x) { x.first },
    :cdr => ->(x) { x.drop(1) },
    :cons => ->(x, y) { [x] + y },
    :'eq?' => ->(a, b) { a.equal?(b) },
    :'equal?' => ->(a, b) { a == b },
    :length => ->(x) { x.length },
    :list => ->(*args) { args },
    :'list?' => ->(x) { x.is_a?(Array) },
    :map => ->(fn, arr) { arr.map { |x| fn.call(x) } },
    :max => ->(*args) { args.max },
    :min => ->(*args) { args.min },
    :not => ->(x) { !x },
    :'null?' => ->(x) { x.is_a?(Array) && x.empty? },
    :'number?' => ->(x) { x.is_a?(Numeric) },
    :print => ->(*args) { puts args.join(' ') },
    :'procedure?' => ->(x) { x.respond_to?(:call) },
    :round => ->(x) { x.round },
    :'symbol?' => ->(x) { x.is_a?(Symbol) },
  })
  env
end

$global_env = standard_env

# Eval
def lisp_eval(x, env = $global_env)
  if x.is_a?(Symbol)                    # variable reference
    env[x] || (raise "undefined symbol: #{x}")
  elsif !x.is_a?(Array)                 # constant
    x
  else
    op, *args = x
    
    case op
    when :quote                         # quotation
      args[0]
    when :if                            # conditional
      test, conseq, alt = args
      exp = lisp_eval(test, env) ? conseq : alt
      lisp_eval(exp, env)
    when :define                        # definition
      var, exp = args
      env[var] = lisp_eval(exp, env)
    when :lambda                        # procedure
      params, body = args
      ->(*vals) { lisp_eval(body, Env.new(params, vals, env)) }
    else                                # procedure call
      proc = lisp_eval(op, env)
      vals = args.map { |arg| lisp_eval(arg, env) }
      proc.call(*vals)
    end
  end
end

def schemestr(exp)
  if exp.is_a?(Array)
    '(' + exp.map { |e| schemestr(e) }.join(' ') + ')'
  else
    exp.to_s
  end
end

# REPL
def repl(prompt = 'lisp> ')
  loop do
    print prompt
    input = gets
    break unless input
    
    input = input.strip
    next if input.empty?
    
    begin
      val = lisp_eval(parse(input))
      puts schemestr(val) unless val.nil?
    rescue Interrupt, SystemExit
      puts "\nBye!"
      break
    rescue => e
      puts "Error: #{e.message}"
    end
  end
  
  puts "\nBye!" if $stdin.tty?
end

# Run REPL if this is the main script
repl if __FILE__ == $PROGRAM_NAME

