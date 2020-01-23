#ifndef _DOMATH_
#define _DOMATH_

#include <string>
#include <vector>

using namespace std;

#include "varbox.h"

struct SyntaxError : public exception {
   const char * what () const throw () {
      return "Syntax Error";
   }
};

struct ArgNumError : public exception {
   const char * what () const throw () {
      return "ArgNum Error";
   }
};

class DoMathHolder;

class DoMathObject {
    public:
    long startIndex;
    long endIndex;
    double * returnAddress;
    string funcName;
    double valueA;
    double valueB;
    DoMathObject(long si, long ei, double * ra);
    void process(DoMathHolder & holder, VarBox & varbox, string & statement, vector <char> & tokens);
    void domath(VarBox & varbox, string & statement);
};

class DoMathHolder {
    private:
    vector <DoMathObject*> arr;
    public:
    ~DoMathHolder();
    void add(DoMathObject * obj);
    long size();
    DoMathObject * get(long index);
};

double domath(VarBox & varbox, string & statement, vector <char> & tokens);

#endif