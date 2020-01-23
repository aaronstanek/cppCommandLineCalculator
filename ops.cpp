#include "ops.h"

#include <math.h>

// basic functions

double equals(VarBox & vb, string & s, double a) {
    vb.save(s,a);
    return a;
}

double paren(double a) {
    return a;
}

double my_plus(double a) {
    return a;
}

double my_minus(double a) {
    return -a;
}

double add(double a, double b) {
    return a + b;
}

double sub(double a, double b) {
    return a - b;
}

double mul(double a, double b) {
    return a * b;
}

double div(double a, double b) {
    if (b == 0) {
        throw DivideByZeroError();
    }
    return a / b;
}

double mod(double a, double b) {
    long c = round(a);
    long d = round(b);
    if (d == 0) {
        throw DivideByZeroError();
    }
    return c % d;
}

double my_pow(double a, double b) {
    return pow(a,b);
}

double sci(double a, double b) {
    return a * pow(10,b);
}

// comparison

double equ(double a, double b) {
    if (a == b) {
        return 1;
    }
    else {
        return 0;
    }
}

double neq(double a, double b) {
    if (a != b) {
        return 1;
    }
    else {
        return 0;
    }
}

double gtr(double a, double b) {
    if (a > b) {
        return 1;
    }
    else {
        return 0;
    }
}

double geq(double a, double b) {
    if (a >= b) {
        return 1;
    }
    else {
        return 0;
    }
}

double lss(double a, double b) {
    if (a < b) {
        return 1;
    }
    else {
        return 0;
    }
}

double leq(double a, double b) {
    if (a <= b) {
        return 1;
    }
    else {
        return 0;
    }
}

// logic

double my_bin(double a) {
    if (round(a) == 0) {
        return 0;
    }
    else {
        return 1;
    }
}

double my_not(double a) {
    if (round(a) == 0) {
        return 1;
    }
    else {
        return 0;
    }
}

double my_or(double a, double b) {
    a = my_bin(a);
    b = my_bin(b);
    if (a+b == 0) {
        return 0;
    }
    else {
        return 1;
    }
}

double my_nor(double a, double b) {
    a = my_bin(a);
    b = my_bin(b);
    if (a+b == 0) {
        return 1;
    }
    else {
        return 0;
    }
}

double my_xor(double a, double b) {
    a = my_bin(a);
    b = my_bin(b);
    if (a+b == 1) {
        return 1;
    }
    else {
        return 0;
    }
}

double my_xnor(double a, double b) {
    a = my_bin(a);
    b = my_bin(b);
    if (a+b == 1) {
        return 0;
    }
    else {
        return 1;
    }
}

double my_and(double a, double b) {
    a = my_bin(a);
    b = my_bin(b);
    if (a+b == 2) {
        return 1;
    }
    else {
        return 0;
    }
}

double my_nand(double a, double b) {
    a = my_bin(a);
    b = my_bin(b);
    if (a+b == 2) {
        return 0;
    }
    else {
        return 1;
    }
}

// advanced

double sign(double a) {
    if (a == 0) {
        return 0;
    }
    if (a > 0) {
        return 1;
    }
    else {
        return -1;
    }
}

double my_abs(double a) {
    return abs(a);
}

double my_round(double a) {
    return round(a);
}

double my_floor(double a) {
    return floor(a);
}

double my_ceil(double a) {
    return ceil(a);
}

double my_min(double a, double b) {
    if (a < b) {
        return a;
    }
    else {
        return b;
    }
}

double my_max(double a, double b) {
    if (a > b) {
        return a;
    }
    else {
        return b;
    }
}

double my_log(double a) {
    if (a <= 0) {
        throw DomainError();
    }
    return log(a);
}

double my_log2(double a) {
    if (a <= 0) {
        throw DomainError();
    }
    return log(a) / log(2);
}

double my_log10(double a) {
    if (a <= 0) {
        throw DomainError();
    }
    return log10(a);
}

double my_exp(double a) {
    return exp(a);
}

double my_sqrt(double a) {
    if (a < 0) {
        throw DomainError();
    }
    return sqrt(a);
}

double my_root(double a, double b) {
    if (a < 0 || b <= 0) {
        throw DomainError();
    }
    return pow(a,1/b);
}

// trig

double my_cos(double a) {
    return cos(a);
}

double my_sin(double a) {
    return sin(a);
}

double my_tan(double a) {
    return tan(a);
}

double my_cosd(double a) {
    a /= 180;
    a *= M_PI;
    return cos(a);
}

double my_sind(double a) {
    a /= 180;
    a *= M_PI;
    return sin(a);
}

double my_tand(double a) {
    a /= 180;
    a *= M_PI;
    return tan(a);
}

double my_acos(double a) {
    try {
        return acos(a);
    }
    catch(...) {
        throw DomainError();
    }
}

double my_asin(double a) {
    try {
        return asin(a);
    }
    catch(...) {
        throw DomainError();
    }
}

double my_atan(double a) {
    try {
        return atan(a);
    }
    catch(...) {
        throw DomainError();
    }
}

double my_acosd(double a) {
    try {
        a = acos(a);
        a /= M_PI;
        a *= 180;
        return a;
    }
    catch(...) {
        throw DomainError();
    }
}

double my_asind(double a) {
    try {
        a = asin(a);
        a /= M_PI;
        a *= 180;
        return a;
    }
    catch(...) {
        throw DomainError();
    }
}

double my_atand(double a) {
    try {
        a = atan(a);
        a /= M_PI;
        a *= 180;
        return a;
    }
    catch(...) {
        throw DomainError();
    }
}

double my_cosh(double a) {
    try {
        return cosh(a);
    }
    catch(...) {
        throw DomainError();
    }
}

double my_sinh(double a) {
    try {
        return sinh(a);
    }
    catch(...) {
        throw DomainError();
    }
}

double my_tanh(double a) {
    try {
        return tanh(a);
    }
    catch(...) {
        throw DomainError();
    }
}

double my_acosh(double a) {
    try {
        return acosh(a);
    }
    catch(...) {
        throw DomainError();
    }
}

double my_asinh(double a) {
    try {
        return asinh(a);
    }
    catch(...) {
        throw DomainError();
    }
}

double my_atanh(double a) {
    try {
        return atanh(a);
    }
    catch(...) {
        throw DomainError();
    }
}

// lookup functions

void functionLookupSmall(FuncHolder & output, string & name) {
    if (name == "=") {
        output.f.s = &equals;
        output.t = 3;
        return;
    }
    if (name == "+") {
        output.f.d = &add;
        output.t = 2;
        return;
    }
    if (name == "-") {
        output.f.d = &sub;
        output.t = 2;
        return;
    }
    if (name == "*") {
        output.f.d = &mul;
        output.t = 2;
        return;
    }
    if (name == "/") {
        output.f.d = &div;
        output.t = 2;
        return;
    }
    if (name == "%") {
        output.f.d = &mod;
        output.t = 2;
        return;
    }
    if (name == "^") {
        output.f.d = &my_pow;
        output.t = 2;
        return;
    }
    if (name == "==") {
        output.f.d = &equ;
        output.t = 2;
        return;
    }
    if (name == "!=") {
        output.f.d = &neq;
        output.t = 2;
        return;
    }
    if (name == ">") {
        output.f.d = &gtr;
        output.t = 2;
        return;
    }
    if (name == ">=") {
        output.f.d = &geq;
        output.t = 2;
        return;
    }
    if (name == "<") {
        output.f.d = &lss;
        output.t = 2;
        return;
    }
    if (name == "<=") {
        output.f.d = &leq;
        output.t = 2;
        return;
    }
    throw UnknownFunctionName();
}

void functionLookupA(FuncHolder & output, string & name) {
    if (name == "add") {
        output.f.d = &add;
        output.t = 2;
        return;
    }
    if (name == "and") {
        output.f.d = &my_and;
        output.t = 2;
        return;
    }
    if (name == "abs") {
        output.f.m = &my_abs;
        output.t = 1;
        return;
    }
    if (name == "acos") {
        output.f.m = &my_acos;
        output.t = 1;
        return;
    }
    if (name == "asin") {
        output.f.m = &my_asin;
        output.t = 1;
        return;
    }
    if (name == "atan") {
        output.f.m = &my_atan;
        output.t = 1;
        return;
    }
    if (name == "acosd") {
        output.f.m = &my_acosd;
        output.t = 1;
        return;
    }
    if (name == "asind") {
        output.f.m = &my_asind;
        output.t = 1;
        return;
    }
    if (name == "atand") {
        output.f.m = &my_atand;
        output.t = 1;
        return;
    }
    if (name == "acosh") {
        output.f.m = &my_acosh;
        output.t = 1;
        return;
    }
    if (name == "asinh") {
        output.f.m = &my_asinh;
        output.t = 1;
        return;
    }
    if (name == "atanh") {
        output.f.m = &my_atanh;
        output.t = 1;
        return;
    }
    throw UnknownFunctionName();
}

void functionLookupB(FuncHolder & output, string & name) {
    if (name == "bin") {
        output.f.m = &my_bin;
        output.t = 1;
        return;
    }
    throw UnknownFunctionName();
}

void functionLookupC(FuncHolder & output, string & name) {
    if (name == "ceil") {
        output.f.m = &my_ceil;
        output.t = 1;
        return;
    }
    if (name == "cos") {
        output.f.m = &my_cos;
        output.t = 1;
        return;
    }
    if (name == "cosd") {
        output.f.m = &my_cosd;
        output.t = 1;
        return;
    }
    if (name == "cosh") {
        output.f.m = &my_cosh;
        output.t = 1;
        return;
    }
    throw UnknownFunctionName();
}

void functionLookupD(FuncHolder & output, string & name) {
    if (name == "div") {
        output.f.d = &div;
        output.t = 2;
        return;
    }
    throw UnknownFunctionName();
}

void functionLookupE(FuncHolder & output, string & name) {
    if (name == "e") {
        output.f.d = &sci;
        output.t = 2;
        return;
    }
    if (name == "equals") {
        output.f.s = &equals;
        output.t = 3;
        return;
    }
    if (name == "equ") {
        output.f.d = &equ;
        output.t = 2;
        return;
    }
    if (name == "exp") {
        output.f.m = &my_exp;
        output.t = 1;
        return;
    }
    throw UnknownFunctionName();
}

void functionLookupF(FuncHolder & output, string & name) {
    if (name == "floor") {
        output.f.m = &my_floor;
        output.t = 1;
        return;
    }
    throw UnknownFunctionName();
}

void functionLookupG(FuncHolder & output, string & name) {
    if (name == "gtr") {
        output.f.d = &gtr;
        output.t = 2;
        return;
    }
    if (name == "geq") {
        output.f.d = &geq;
        output.t = 2;
        return;
    }
    throw UnknownFunctionName();
}

void functionLookupL(FuncHolder & output, string & name) {
    if (name == "lss") {
        output.f.d = &lss;
        output.t = 2;
        return;
    }
    if (name == "leq") {
        output.f.d = &leq;
        output.t = 2;
        return;
    }
    if (name == "log") {
        output.f.m = &my_log;
        output.t = 1;
        return;
    }
    if (name == "log2") {
        output.f.m = &my_log2;
        output.t = 1;
        return;
    }
    if (name == "log10") {
        output.f.m = &my_log10;
        output.t = 1;
        return;
    }
    throw UnknownFunctionName();
}

void functionLookupM(FuncHolder & output, string & name) {
    if (name == "minus") {
        output.f.m = &my_minus;
        output.t = 1;
        return;
    }
    if (name == "mul") {
        output.f.d = &mul;
        output.t = 2;
        return;
    }
    if (name == "mod") {
        output.f.d = &mod;
        output.t = 2;
        return;
    }
    if (name == "min") {
        output.f.d = &my_min;
        output.t = 2;
        return;
    }
    if (name == "max") {
        output.f.d = &my_max;
        output.t = 2;
        return;
    }
    throw UnknownFunctionName();
}

void functionLookupN(FuncHolder & output, string & name) {
    if (name == "neq") {
        output.f.d = &neq;
        output.t = 2;
        return;
    }
    if (name == "not") {
        output.f.m = &my_not;
        output.t = 1;
        return;
    }
    if (name == "nor") {
        output.f.d = &my_nor;
        output.t = 2;
        return;
    }
    if (name == "nand") {
        output.f.d = &my_nand;
        output.t = 2;
        return;
    }
    throw UnknownFunctionName();
}

void functionLookupO(FuncHolder & output, string & name) {
    if (name == "or") {
        output.f.d = &my_or;
        output.t = 2;
        return;
    }
    throw UnknownFunctionName();
}

void functionLookupP(FuncHolder & output, string & name) {
    if (name == "paren") {
        output.f.m = &paren;
        output.t = 1;
        return;
    }
    if (name == "plus") {
        output.f.m = &my_plus;
        output.t = 1;
        return;
    }
    if (name == "pow") {
        output.f.d = &my_pow;
        output.t = 2;
        return;
    }
    throw UnknownFunctionName();
}

void functionLookupR(FuncHolder & output, string & name) {
    if (name == "round") {
        output.f.m = &my_round;
        output.t = 1;
        return;
    }
    if (name == "root") {
        output.f.d = &my_root;
        output.t = 2;
        return;
    }
    throw UnknownFunctionName();
}

void functionLookupS(FuncHolder & output, string & name) {
    if (name == "sub") {
        output.f.d = &sub;
        output.t = 2;
        return;
    }
    if (name == "sci") {
        output.f.d = &sci;
        output.t = 2;
        return;
    }
    if (name == "sign") {
        output.f.m = &sign;
        output.t = 1;
        return;
    }
    if (name == "sqrt") {
        output.f.m = &my_sqrt;
        output.t = 1;
        return;
    }
    if (name == "sin") {
        output.f.m = &my_sin;
        output.t = 1;
        return;
    }
    if (name == "sind") {
        output.f.m = &my_sind;
        output.t = 1;
        return;
    }
    if (name == "sinh") {
        output.f.m = &my_sinh;
        output.t = 1;
        return;
    }
    throw UnknownFunctionName();
}

void functionLookupT(FuncHolder & output, string & name) {
    if (name == "tan") {
        output.f.m = &my_tan;
        output.t = 1;
        return;
    }
    if (name == "tand") {
        output.f.m = &my_tand;
        output.t = 1;
        return;
    }
    if (name == "tanh") {
        output.f.m = &my_tanh;
        output.t = 1;
        return;
    }
    throw UnknownFunctionName();
}

void functionLookupX(FuncHolder & output, string & name) {
    if (name == "xor") {
        output.f.d = &my_xor;
        output.t = 2;
        return;
    }
    if (name == "xnor") {
        output.f.d = &my_xnor;
        output.t = 2;
        return;
    }
    throw UnknownFunctionName();
}

FuncHolder functionLookup(string & name) {
    if (name.size() == 0) {
        throw UnknownFunctionName();
    }
    FuncHolder fh;
    if (name[0] < 'a') {
        functionLookupSmall(fh,name);
        return fh;
    }
    switch (name[0]) {
        case 'a':
            functionLookupA(fh,name);
            return fh;
        case 'b':
            functionLookupB(fh,name);
            return fh;
        case 'c':
            functionLookupC(fh,name);
            return fh;
        case 'd':
            functionLookupD(fh,name);
            return fh;
        case 'e':
            functionLookupE(fh,name);
            return fh;
        case 'f':
            functionLookupF(fh,name);
            return fh;
        case 'g':
            functionLookupG(fh,name);
            return fh;
        case 'l':
            functionLookupL(fh,name);
            return fh;
        case 'm':
            functionLookupM(fh,name);
            return fh;
        case 'n':
            functionLookupN(fh,name);
            return fh;
        case 'o':
            functionLookupO(fh,name);
            return fh;
        case 'p':
            functionLookupP(fh,name);
            return fh;
        case 'r':
            functionLookupR(fh,name);
            return fh;
        case 's':
            functionLookupS(fh,name);
            return fh;
        case 't':
            functionLookupT(fh,name);
            return fh;
        case 'x':
            functionLookupX(fh,name);
            return fh;
        default:
            break;
    }
    throw UnknownFunctionName();
}
