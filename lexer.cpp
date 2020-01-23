#include "lexer.h"

void lexerPunctuation(string & statement, vector <char> & tokens) {
    for (long i = 0; i < statement.size(); i++) {
        char c = statement[i];
        switch (c) {
            case '(' :
            case ')' :
            case ',' :
                tokens[i] = 'p';
                break;
            default:
                break;
        }
    }
}

void lexerVarsNums(string & statement, vector <char> & tokens) {
    for (long i = 0; i < statement.size(); i++) {
        char prevToken;
        if (i == 0) {
            prevToken = 0;
        }
        else {
            prevToken = tokens[i-1];
        }
        char c = statement[i];
        // nums have 0-9 . e
        // vars have a-z 0-9
        if (c >= 'a' && c <= 'z') {
            // probably a var
            if (c == 'e' && prevToken == 'n') {
                tokens[i] = 'b';
            }
            else {
                tokens[i] = 'v';
            }
            continue;
        }
        if (c == '.') {
            tokens[i] = 'n';
            continue;
        }
        if (c >= '0' && c <= '9') {
            // probably a number
            if (prevToken == 'v') {
                tokens[i] = 'v';
            }
            else {
                tokens[i] = 'n';
            }
        }
    }
}

void lexerUnitary(string & statement, vector <char> & tokens) {
    for (long i = 0; i < statement.size()-1; i++) {
        char c = statement[i];
        if (c != '+' && c != '-') {
            continue;
        }
        char prevToken;
        if (i == 0) {
            prevToken = 0;
        }
        else {
            prevToken = tokens[i-1];
        }
        if (prevToken == 'n' || prevToken == 'v') {
            continue;
        }
        if (prevToken == 'p') {
            if (statement[i-1] == ')') {
                continue;
            }
        }
        tokens[i] = 'u';
    }
}

void lexerBinary(vector <char> & tokens) {
    for (long i = 0; i < tokens.size(); i++) {
        if (tokens[i] == 0) {
            tokens[i] = 'b';
        }
    }
}

void lexerFunction(string & statement, vector <char> & tokens) {
    for (long i = tokens.size()-2; i >= 0; i--) {
        if (tokens[i] != 'v') {
            continue;
        }
        if (tokens[i+1] != 'f' && statement[i+1] != '(') {
            continue;
        }
        tokens[i] = 'f';
    }
}

void lexer(string & statement, vector <char> & tokens) {
    tokens.resize(statement.size());
    for (long i = 0; i < tokens.size(); i++) {
        tokens[i] = 0;
    }
    lexerPunctuation(statement,tokens);
    lexerVarsNums(statement,tokens);
    lexerUnitary(statement,tokens);
    lexerBinary(tokens);
    lexerFunction(statement,tokens);
}