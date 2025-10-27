// A minimal Lisp interpreter in C++
// Inspired by Peter Norvig's legendary implementation

#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <memory>
#include <functional>
#include <cmath>
#include <algorithm>

using namespace std;

// Forward declarations
class Env;
class Exp;

using ExpPtr = shared_ptr<Exp>;
using EnvPtr = shared_ptr<Env>;

// Expression types
class Exp {
public:
    enum Type { Symbol, Number, List, Proc, Lambda };
    Type type;
    string symbol;
    double number;
    vector<ExpPtr> list;
    function<ExpPtr(const vector<ExpPtr>&)> proc;
    vector<string> params;
    ExpPtr body;
    EnvPtr env;
    
    Exp(Type t) : type(t), number(0.0) {}
    
    static ExpPtr makeSymbol(const string& s) {
        auto exp = make_shared<Exp>(Symbol);
        exp->symbol = s;
        return exp;
    }
    
    static ExpPtr makeNumber(double n) {
        auto exp = make_shared<Exp>(Number);
        exp->number = n;
        return exp;
    }
    
    static ExpPtr makeList(const vector<ExpPtr>& l) {
        auto exp = make_shared<Exp>(List);
        exp->list = l;
        return exp;
    }
    
    static ExpPtr makeProc(function<ExpPtr(const vector<ExpPtr>&)> p) {
        auto exp = make_shared<Exp>(Proc);
        exp->proc = p;
        return exp;
    }
    
    static ExpPtr makeLambda(const vector<string>& parms, ExpPtr b, EnvPtr e) {
        auto exp = make_shared<Exp>(Lambda);
        exp->params = parms;
        exp->body = b;
        exp->env = e;
        return exp;
    }
    
    string toString() const {
        switch (type) {
            case Symbol: return symbol;
            case Number: return to_string(number);
            case List: {
                string result = "(";
                for (size_t i = 0; i < list.size(); i++) {
                    if (i > 0) result += " ";
                    result += list[i]->toString();
                }
                return result + ")";
            }
            case Proc: return "<procedure>";
            case Lambda: return "<lambda>";
        }
        return "";
    }
};

// Environment
class Env {
public:
    map<string, ExpPtr> data;
    EnvPtr outer;
    
    Env(EnvPtr o = nullptr) : outer(o) {}
    
    ExpPtr find(const string& var) {
        if (data.count(var)) return data[var];
        if (outer) return outer->find(var);
        return nullptr;
    }
    
    void set(const string& var, ExpPtr val) {
        data[var] = val;
    }
};

// Tokenize
vector<string> tokenize(const string& str) {
    vector<string> tokens;
    string s = str;
    
    // Replace parens with spaces
    for (size_t i = 0; i < s.length(); i++) {
        if (s[i] == '(' || s[i] == ')') {
            s.insert(i, " ");
            s.insert(i + 2, " ");
            i += 2;
        }
    }
    
    // Split by whitespace
    istringstream iss(s);
    string token;
    while (iss >> token) {
        tokens.push_back(token);
    }
    
    return tokens;
}

// Parse
ExpPtr readFromTokens(vector<string>& tokens) {
    if (tokens.empty()) throw runtime_error("unexpected EOF");
    
    string token = tokens[0];
    tokens.erase(tokens.begin());
    
    if (token == "(") {
        vector<ExpPtr> L;
        while (tokens[0] != ")") {
            L.push_back(readFromTokens(tokens));
        }
        tokens.erase(tokens.begin()); // pop ')'
        return Exp::makeList(L);
    } else if (token == ")") {
        throw runtime_error("unexpected )");
    } else {
        // Try to parse as number
        try {
            size_t pos;
            double num = stod(token, &pos);
            if (pos == token.length()) {
                return Exp::makeNumber(num);
            }
        } catch (...) {}
        return Exp::makeSymbol(token);
    }
}

ExpPtr parse(const string& program) {
    auto tokens = tokenize(program);
    return readFromTokens(tokens);
}

// Standard environment
EnvPtr standardEnv() {
    auto env = make_shared<Env>();
    
    env->set("+", Exp::makeProc([](const vector<ExpPtr>& args) {
        double sum = 0;
        for (auto& arg : args) sum += arg->number;
        return Exp::makeNumber(sum);
    }));
    
    env->set("-", Exp::makeProc([](const vector<ExpPtr>& args) {
        if (args.size() == 1) return Exp::makeNumber(-args[0]->number);
        double result = args[0]->number;
        for (size_t i = 1; i < args.size(); i++) result -= args[i]->number;
        return Exp::makeNumber(result);
    }));
    
    env->set("*", Exp::makeProc([](const vector<ExpPtr>& args) {
        double product = 1;
        for (auto& arg : args) product *= arg->number;
        return Exp::makeNumber(product);
    }));
    
    env->set("/", Exp::makeProc([](const vector<ExpPtr>& args) {
        double result = args[0]->number;
        for (size_t i = 1; i < args.size(); i++) result /= args[i]->number;
        return Exp::makeNumber(result);
    }));
    
    env->set("<", Exp::makeProc([](const vector<ExpPtr>& args) {
        return Exp::makeNumber(args[0]->number < args[1]->number ? 1 : 0);
    }));
    
    env->set(">", Exp::makeProc([](const vector<ExpPtr>& args) {
        return Exp::makeNumber(args[0]->number > args[1]->number ? 1 : 0);
    }));
    
    env->set("=", Exp::makeProc([](const vector<ExpPtr>& args) {
        return Exp::makeNumber(args[0]->number == args[1]->number ? 1 : 0);
    }));
    
    env->set("list", Exp::makeProc([](const vector<ExpPtr>& args) {
        return Exp::makeList(args);
    }));
    
    env->set("car", Exp::makeProc([](const vector<ExpPtr>& args) {
        return args[0]->list[0];
    }));
    
    env->set("cdr", Exp::makeProc([](const vector<ExpPtr>& args) {
        vector<ExpPtr> tail(args[0]->list.begin() + 1, args[0]->list.end());
        return Exp::makeList(tail);
    }));
    
    env->set("cons", Exp::makeProc([](const vector<ExpPtr>& args) {
        vector<ExpPtr> result = {args[0]};
        result.insert(result.end(), args[1]->list.begin(), args[1]->list.end());
        return Exp::makeList(result);
    }));
    
    return env;
}

// Eval
ExpPtr eval(ExpPtr x, EnvPtr env);

ExpPtr eval(ExpPtr x, EnvPtr env) {
    if (x->type == Exp::Symbol) {
        auto val = env->find(x->symbol);
        if (!val) throw runtime_error("undefined symbol: " + x->symbol);
        return val;
    } else if (x->type == Exp::Number) {
        return x;
    } else if (x->type == Exp::List) {
        if (x->list.empty()) return x;
        
        auto& op = x->list[0];
        
        if (op->type == Exp::Symbol) {
            if (op->symbol == "quote") {
                return x->list[1];
            } else if (op->symbol == "if") {
                auto test = eval(x->list[1], env);
                bool isTrue = (test->type == Exp::Number && test->number != 0) ||
                             (test->type == Exp::List && !test->list.empty());
                return eval(x->list[isTrue ? 2 : 3], env);
            } else if (op->symbol == "define") {
                auto val = eval(x->list[2], env);
                env->set(x->list[1]->symbol, val);
                return val;
            } else if (op->symbol == "lambda") {
                vector<string> params;
                for (auto& p : x->list[1]->list) {
                    params.push_back(p->symbol);
                }
                return Exp::makeLambda(params, x->list[2], env);
            }
        }
        
        auto proc = eval(op, env);
        vector<ExpPtr> args;
        for (size_t i = 1; i < x->list.size(); i++) {
            args.push_back(eval(x->list[i], env));
        }
        
        if (proc->type == Exp::Proc) {
            return proc->proc(args);
        } else if (proc->type == Exp::Lambda) {
            auto newEnv = make_shared<Env>(proc->env);
            for (size_t i = 0; i < proc->params.size(); i++) {
                newEnv->set(proc->params[i], args[i]);
            }
            return eval(proc->body, newEnv);
        }
    }
    
    return x;
}

// REPL
void repl() {
    auto env = standardEnv();
    string line;
    
    while (true) {
        cout << "lisp> ";
        if (!getline(cin, line)) break;
        
        if (line.empty()) continue;
        
        try {
            auto exp = parse(line);
            auto val = eval(exp, env);
            cout << val->toString() << endl;
        } catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }
    }
    
    cout << "\nBye!" << endl;
}

int main() {
    repl();
    return 0;
}

