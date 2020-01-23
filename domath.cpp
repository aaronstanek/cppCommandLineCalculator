#include "domath.h"

#include "ops.h"

DoMathObject::DoMathObject(long si, long ei, double * ra) {
    startIndex = si;
    endIndex = ei;
    returnAddress = ra;
}

long findBin(string & statement, vector <char> & tokens, long startIndex, long endIndex) {
    // levels
    // 0 =
    // 1 + -
    // 2 * / %
    // 3 ^ e
    for (long level = 0; level <= 3; level++) {
        long count = 0;
        for (long i = startIndex; i <= endIndex; i++) {
            char c = statement[i];
            switch (c) {
                case '(':
                    count++;
                    break;
                case ')':
                    count--;
                    break;
                default:
                    break;
            }
            if (count != 0 || tokens[i] != 'b') {
                continue;
            }
            switch (level) {
                case 0:
                    if (c == '=' || c == '>' || c == '<' || c == '!') {
                        return i;
                    }
                    break;
                case 1:
                    if (c == '+' || c == '-') {
                        return i;
                    }
                    break;
                case 2:
                    if (c == '*' || c == '/' || c == '%') {
                        return i;
                    }
                    break;
                default:
                    if (c == '^' || c == 'e') {
                        return i;
                    }
            }
        }
    }
    return -1;
}

void validateEqualsLeft(vector <char> & tokens, long startIndex, long endIndex) {
    for (long i = startIndex; i <= endIndex; i++) {
        if (tokens[i] != 'v') {
            throw SyntaxError();
        }
    }
}

void DoMathObject::process(DoMathHolder & holder, VarBox & varbox, string & statement, vector <char> & tokens) {
    if (endIndex < startIndex) {
        throw SyntaxError();
    }
    // first determine if there are any binary operators at the top level
    long binIndex = findBin(statement, tokens, startIndex, endIndex);
    if (binIndex != -1) {
        if (binIndex+1 < statement.size()) {
            if (statement[binIndex+1] == '=') {
                funcName.push_back(statement[binIndex]);
                funcName.push_back('=');
                holder.add(new DoMathObject(startIndex,binIndex-1,&valueA));
                holder.add(new DoMathObject(binIndex+2,endIndex,&valueB));
                return;
            }
        }
        funcName.push_back(statement[binIndex]);
        if (statement[binIndex] != '=') {
            holder.add(new DoMathObject(startIndex,binIndex-1,&valueA));
            holder.add(new DoMathObject(binIndex+1,endIndex,&valueB));
        }
        else {
            holder.add(new DoMathObject(binIndex+1,endIndex,&valueA));
            endIndex = binIndex-1;
            validateEqualsLeft(tokens,startIndex,endIndex);
        }
        return;
    }
    if (tokens[startIndex] == 'p' || tokens[startIndex] == 'u') {
        if (statement[startIndex] == '(') {
            funcName = "paren";
            holder.add(new DoMathObject(startIndex+1,endIndex-1,&valueA));
            return;
        }
        if (statement[startIndex] == '+') {
            funcName = "plus";
            holder.add(new DoMathObject(startIndex+1,endIndex,&valueA));
            return;
        }
        if (statement[startIndex] == '-') {
            funcName = "minus";
            holder.add(new DoMathObject(startIndex+1,endIndex,&valueA));
            return;
        }
        throw SyntaxError();
    }
    // there are only functions, variables, and numbers
    if (tokens[startIndex] == 'n') {
        try {
            string copied(&statement[startIndex],endIndex-startIndex+1);
            valueA = stod(copied);
            funcName = "plus";
            return;
        }
        catch (...) {
            throw SyntaxError();
        }
    }
    if (tokens[startIndex] == 'v') {
        string copied(&statement[startIndex],endIndex-startIndex+1);
        valueA = varbox.load(copied);
        funcName = "plus";
        return;
    }
    // it must be a function
    if (tokens[startIndex] != 'f') {
        throw SyntaxError();
    }
    long spot = startIndex;
    long count = 0;
    long argNumber = 0;
    long equSpecialA;
    long equSpecialB;
    FuncHolder fh;
    for (long i = startIndex; i <= endIndex; i++) {
        char c = statement[i];
        if (c == '(') {
            count++;
        }
        if (count == 1 && tokens[i] == 'p') {
            switch (argNumber) {
                case 0:
                    funcName = string(&statement[spot],i-spot);
                    fh = functionLookup(funcName);
                    break;
                case 1:
                    if (fh.t != 3) {
                        holder.add(new DoMathObject(spot,i-1,&valueA));
                    }
                    else {
                        equSpecialA = spot;
                        equSpecialB = i-1;
                    }
                    break;
                case 2:
                    if (fh.t != 3) {
                        holder.add(new DoMathObject(spot,i-1,&valueB));
                    }
                    else {
                        holder.add(new DoMathObject(spot,i-1,&valueA));
                    }
                    break;
                default:
                    throw ArgNumError();
            }
            spot = i + 1;
            argNumber++;
        }
        if (c == ')') {
            count--;
        }
    }
    // we should check that we have the right number of arguments
    if (fh.t == 3) {
        startIndex = equSpecialA;
        endIndex = equSpecialB;
        if (argNumber != 3) {
            throw ArgNumError();
        }
        validateEqualsLeft(tokens,startIndex,endIndex);
        return;
    }
    if (fh.t == 1) {
        if (argNumber != 2) {
            throw ArgNumError();
        }
    }
    else {
        if (argNumber != 3) {
            throw ArgNumError();
        }
    }
}

void DoMathObject::domath(VarBox & varbox, string & statement) {
    FuncHolder fh = functionLookup(funcName);
    if (fh.t == 3) {
        string copied(&statement[startIndex],endIndex-startIndex+1);
        *returnAddress = fh.f.s(varbox,copied,valueA);
        return;
    }
    if (fh.t == 1) {
        *returnAddress = fh.f.m(valueA);
    }
    else {
        *returnAddress = fh.f.d(valueA,valueB);
    }
}

DoMathHolder::~DoMathHolder() {
    for (long i = 0; i < arr.size(); i++) {
        delete arr[i];
    }
}

void DoMathHolder::add(DoMathObject * obj) {
    arr.push_back(obj);
}

long DoMathHolder::size() {
    return arr.size();
}

DoMathObject * DoMathHolder::get(long index) {
    return arr[index];
}

double domath(VarBox & varbox, string & statement, vector <char> & tokens) {
    double output;
    DoMathHolder holder;
    holder.add(new DoMathObject(0,statement.size()-1,&output));
    for (long i = 0; i < holder.size(); i++) {
        holder.get(i)->process(holder, varbox, statement, tokens);
    }
    for (long i = holder.size() - 1; i >= 0; i--) {
        holder.get(i)->domath(varbox, statement);
    }
    return output;
}