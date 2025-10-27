/* A minimal Lisp interpreter in C
 * Inspired by Peter Norvig's legendary implementation
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKENS 256
#define MAX_ENV 256

// Expression types
typedef enum { T_SYMBOL, T_NUMBER, T_LIST, T_PROC, T_NIL } ExpType;

struct Exp;
struct Env;

typedef struct Exp* (*ProcFn)(struct Exp*, struct Env*);

typedef struct Exp {
    ExpType type;
    union {
        char* symbol;
        double number;
        struct {
            struct Exp* car;
            struct Exp* cdr;
        } pair;
        ProcFn proc;
    } val;
} Exp;

typedef struct EnvEntry {
    char* key;
    Exp* val;
} EnvEntry;

typedef struct Env {
    EnvEntry entries[MAX_ENV];
    int size;
    struct Env* outer;
} Env;

// Memory management helpers
Exp* makeSymbol(const char* s) {
    Exp* exp = malloc(sizeof(Exp));
    exp->type = T_SYMBOL;
    exp->val.symbol = strdup(s);
    return exp;
}

Exp* makeNumber(double n) {
    Exp* exp = malloc(sizeof(Exp));
    exp->type = T_NUMBER;
    exp->val.number = n;
    return exp;
}

Exp* makePair(Exp* car, Exp* cdr) {
    Exp* exp = malloc(sizeof(Exp));
    exp->type = T_LIST;
    exp->val.pair.car = car;
    exp->val.pair.cdr = cdr;
    return exp;
}

Exp* makeProc(ProcFn proc) {
    Exp* exp = malloc(sizeof(Exp));
    exp->type = T_PROC;
    exp->val.proc = proc;
    return exp;
}

Exp* makeNil() {
    Exp* exp = malloc(sizeof(Exp));
    exp->type = T_NIL;
    return exp;
}

// List helpers
Exp* cons(Exp* car, Exp* cdr) {
    return makePair(car, cdr);
}

Exp* car(Exp* exp) {
    return exp->type == T_LIST ? exp->val.pair.car : NULL;
}

Exp* cdr(Exp* exp) {
    return exp->type == T_LIST ? exp->val.pair.cdr : NULL;
}

int isNil(Exp* exp) {
    return exp->type == T_NIL;
}

// Environment
Env* makeEnv(Env* outer) {
    Env* env = malloc(sizeof(Env));
    env->size = 0;
    env->outer = outer;
    return env;
}

void envSet(Env* env, const char* key, Exp* val) {
    for (int i = 0; i < env->size; i++) {
        if (strcmp(env->entries[i].key, key) == 0) {
            env->entries[i].val = val;
            return;
        }
    }
    env->entries[env->size].key = strdup(key);
    env->entries[env->size].val = val;
    env->size++;
}

Exp* envFind(Env* env, const char* key) {
    for (int i = 0; i < env->size; i++) {
        if (strcmp(env->entries[i].key, key) == 0) {
            return env->entries[i].val;
        }
    }
    return env->outer ? envFind(env->outer, key) : NULL;
}

// Primitives
Exp* primAdd(Exp* args, Env* env) {
    double sum = 0;
    while (!isNil(args)) {
        sum += car(args)->val.number;
        args = cdr(args);
    }
    return makeNumber(sum);
}

Exp* primSub(Exp* args, Env* env) {
    double result = car(args)->val.number;
    args = cdr(args);
    if (isNil(args)) return makeNumber(-result);
    while (!isNil(args)) {
        result -= car(args)->val.number;
        args = cdr(args);
    }
    return makeNumber(result);
}

Exp* primMul(Exp* args, Env* env) {
    double product = 1;
    while (!isNil(args)) {
        product *= car(args)->val.number;
        args = cdr(args);
    }
    return makeNumber(product);
}

Exp* primDiv(Exp* args, Env* env) {
    double result = car(args)->val.number;
    args = cdr(args);
    while (!isNil(args)) {
        result /= car(args)->val.number;
        args = cdr(args);
    }
    return makeNumber(result);
}

Exp* primLt(Exp* args, Env* env) {
    double a = car(args)->val.number;
    double b = car(cdr(args))->val.number;
    return makeNumber(a < b ? 1 : 0);
}

Exp* primGt(Exp* args, Env* env) {
    double a = car(args)->val.number;
    double b = car(cdr(args))->val.number;
    return makeNumber(a > b ? 1 : 0);
}

Exp* primCar(Exp* args, Env* env) {
    return car(car(args));
}

Exp* primCdr(Exp* args, Env* env) {
    return cdr(car(args));
}

Exp* primCons(Exp* args, Env* env) {
    return cons(car(args), car(cdr(args)));
}

Exp* primList(Exp* args, Env* env) {
    return args;
}

// Tokenize
int tokenize(const char* input, char tokens[][64]) {
    char buffer[1024];
    strcpy(buffer, input);
    
    // Add spaces around parens
    char spaced[2048] = "";
    for (int i = 0; buffer[i]; i++) {
        if (buffer[i] == '(' || buffer[i] == ')') {
            strcat(spaced, " ");
            strncat(spaced, &buffer[i], 1);
            strcat(spaced, " ");
        } else {
            strncat(spaced, &buffer[i], 1);
        }
    }
    
    // Split by whitespace
    int count = 0;
    char* token = strtok(spaced, " \t\n");
    while (token && count < MAX_TOKENS) {
        strcpy(tokens[count++], token);
        token = strtok(NULL, " \t\n");
    }
    return count;
}

// Parse
int tokenIndex = 0;

Exp* readFromTokens(char tokens[][64], int count) {
    if (tokenIndex >= count) return NULL;
    
    char* token = tokens[tokenIndex++];
    
    if (strcmp(token, "(") == 0) {
        Exp* list = makeNil();
        Exp* tail = NULL;
        
        while (strcmp(tokens[tokenIndex], ")") != 0) {
            Exp* elem = readFromTokens(tokens, count);
            Exp* newPair = cons(elem, makeNil());
            
            if (isNil(list)) {
                list = newPair;
                tail = newPair;
            } else {
                tail->val.pair.cdr = newPair;
                tail = newPair;
            }
        }
        tokenIndex++; // skip ')'
        return list;
    } else {
        // Try to parse as number
        char* endptr;
        double num = strtod(token, &endptr);
        if (*endptr == '\0') {
            return makeNumber(num);
        }
        return makeSymbol(token);
    }
}

Exp* parse(const char* input) {
    char tokens[MAX_TOKENS][64];
    int count = tokenize(input, tokens);
    tokenIndex = 0;
    return readFromTokens(tokens, count);
}

// Forward declaration
Exp* eval(Exp* exp, Env* env);

// Eval
Exp* eval(Exp* exp, Env* env) {
    if (exp->type == T_SYMBOL) {
        Exp* val = envFind(env, exp->val.symbol);
        return val ? val : exp;
    } else if (exp->type == T_NUMBER) {
        return exp;
    } else if (exp->type == T_NIL) {
        return exp;
    } else if (exp->type == T_LIST) {
        Exp* op = car(exp);
        Exp* args = cdr(exp);
        
        if (op->type == T_SYMBOL) {
            if (strcmp(op->val.symbol, "quote") == 0) {
                return car(args);
            } else if (strcmp(op->val.symbol, "if") == 0) {
                Exp* test = eval(car(args), env);
                int isTrue = (test->type == T_NUMBER && test->val.number != 0) ||
                            (test->type == T_LIST);
                return eval(car(isTrue ? cdr(args) : cdr(cdr(args))), env);
            } else if (strcmp(op->val.symbol, "define") == 0) {
                Exp* sym = car(args);
                Exp* val = eval(car(cdr(args)), env);
                envSet(env, sym->val.symbol, val);
                return val;
            }
        }
        
        Exp* proc = eval(op, env);
        
        // Eval arguments
        Exp* evaledArgs = makeNil();
        Exp* tail = NULL;
        Exp* arg = args;
        while (!isNil(arg)) {
            Exp* evaledArg = eval(car(arg), env);
            Exp* newPair = cons(evaledArg, makeNil());
            if (isNil(evaledArgs)) {
                evaledArgs = newPair;
                tail = newPair;
            } else {
                tail->val.pair.cdr = newPair;
                tail = newPair;
            }
            arg = cdr(arg);
        }
        
        if (proc->type == T_PROC) {
            return proc->val.proc(evaledArgs, env);
        }
    }
    
    return exp;
}

// Print
void printExp(Exp* exp) {
    if (exp->type == T_SYMBOL) {
        printf("%s", exp->val.symbol);
    } else if (exp->type == T_NUMBER) {
        printf("%.15g", exp->val.number);
    } else if (exp->type == T_LIST) {
        printf("(");
        int first = 1;
        while (!isNil(exp)) {
            if (!first) printf(" ");
            printExp(car(exp));
            exp = cdr(exp);
            first = 0;
        }
        printf(")");
    } else if (exp->type == T_NIL) {
        printf("()");
    } else if (exp->type == T_PROC) {
        printf("<procedure>");
    }
}

// Standard environment
Env* standardEnv() {
    Env* env = makeEnv(NULL);
    envSet(env, "+", makeProc(primAdd));
    envSet(env, "-", makeProc(primSub));
    envSet(env, "*", makeProc(primMul));
    envSet(env, "/", makeProc(primDiv));
    envSet(env, "<", makeProc(primLt));
    envSet(env, ">", makeProc(primGt));
    envSet(env, "car", makeProc(primCar));
    envSet(env, "cdr", makeProc(primCdr));
    envSet(env, "cons", makeProc(primCons));
    envSet(env, "list", makeProc(primList));
    return env;
}

// REPL
void repl() {
    Env* env = standardEnv();
    char line[1024];
    
    while (1) {
        printf("lisp> ");
        if (!fgets(line, sizeof(line), stdin)) break;
        
        line[strcspn(line, "\n")] = 0;
        if (strlen(line) == 0) continue;
        
        Exp* exp = parse(line);
        if (exp) {
            Exp* val = eval(exp, env);
            printExp(val);
            printf("\n");
        }
    }
    
    printf("\nBye!\n");
}

int main() {
    repl();
    return 0;
}
