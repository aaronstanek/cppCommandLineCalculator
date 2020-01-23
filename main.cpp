#include <iostream>
#include <string>

using namespace std;

#include "validateStatement.h"
#include "lexer.h"
#include "varbox.h"
#include "domath.h"
#include "ops.h"

void getSingleStatement(string & output, int argc, char ** argv) {
    for (int i = 1; i < argc; i++) {
        output += argv[i];
    }
}

struct OverflowError : public exception {
   const char * what () const throw () {
      return "Overflow Error";
   }
};

void removeWhitespace(string & output, char * buffer) {
    for (long i = 0; true; i++) {
        if (i == 1024) {
            throw OverflowError();
        }
        char c = buffer[i];
        if (c == 0) {
            return;
        }
        if (c == 32 || c == 9) {
            continue;
        }
        output.push_back(c);
    }
}

int main(int argc, char ** argv) {
    VarBox varbox;
    if (argc > 1) {
        // single use mode
        try {
            string statement;
            getSingleStatement(statement,argc,argv);
            validateStatement(statement);
            vector <char> tokens;
            lexer(statement,tokens);
            cout << domath(varbox, statement, tokens) << endl;
        }
        catch (...) {
            cout << "ERR" << endl;
        }
    }
    else {
        // interface mode
        char * buffer;
        buffer = new char[1024];
        while (true) {
            try {
                cout << "IN > ";
                cin.getline(buffer,1024);
                string statement;
                removeWhitespace(statement,buffer);
                if (statement == "exit") {
                    break;
                }
                if (statement.size() == 0) {
                    continue;
                }
                validateStatement(statement);
                statement = "ans=" + statement;
                vector <char> tokens;
                lexer(statement,tokens);
                cout << "OUT> " << domath(varbox, statement, tokens) << endl << endl;
            }
            catch (OverflowError & e) {
                cout << "ERR> Buffer Overflow" << endl << endl;
            }
            catch (InvalidCharacterError & e) {
                cout << "ERR> Invalid Character" << endl << endl;
            }
            catch (ParenthesisMismatchError & e) {
                cout << "ERR> Parenthesis Mismatch" << endl << endl;
            }
            catch (SyntaxError & e) {
                cout << "ERR> Syntax Error" << endl << endl;
            }
            catch (ArgNumError & e) {
                cout << "ERR> Wrong Number of Function Arguments" << endl << endl;
            }
            catch (UnknownVariableName & e) {
                cout << "ERR> Undefined Variable" << endl << endl;
            }
            catch (UnknownFunctionName & e) {
                cout << "ERR> Undefined Function" << endl << endl;
            }
            catch (DivideByZeroError & e) {
                cout << "ERR> Division by Zero" << endl << endl;
            }
            catch (DomainError & e) {
                cout << "ERR> Domain Error" << endl << endl;
            }
            catch (...) {
                cout << "ERR> Unknown Error" << endl << endl;
            }
        }
    }
    return 0;
}