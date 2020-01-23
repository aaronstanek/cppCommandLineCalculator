#include "validateStatement.h"

void validateStatementChars(string & statement) {
    // we will permit only
    // a-z
    // 0-9
    // . ,
    // ( )
    // + - * / % ^
    // =
    // > < !
    for (long i = 0; i < statement.size(); i++) {
        char c = statement[i];
        if (c >= 'a' && c <= 'z') {
            continue;
        }
        if (c >= '0' && c <= '9') {
            continue;
        }
        switch (c) {
            case '.' : break;
            case ',' : break;
            case '(' : break;
            case ')' : break;
            case '+' : break;
            case '-' : break;
            case '*' : break;
            case '/' : break;
            case '%' : break;
            case '^' : break;
            case '=' : break;
            case '>' : break;
            case '<' : break;
            case '!' : break;
            default:
                throw InvalidCharacterError();
        }
    }
}

void validdateStatementParens(string & statement) {
    long count = 0;
    for (long i = 0; i < statement.size(); i++) {
        char c = statement[i];
        switch (c) {
            case '(' :
                count++;
                break;
            case ')' :
                count--;
                break;
            default:
                break;
        }
        if (count < 0) {
            throw ParenthesisMismatchError();
        }
    }
    if (count != 0) {
        throw ParenthesisMismatchError();
    }
}

void validateStatement(string & statement) {
    validateStatementChars(statement);
    validdateStatementParens(statement);
}