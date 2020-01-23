#ifndef _OPS_
#define _OPS_

#include <string>

using namespace std;

#include "varbox.h"

struct UnknownFunctionName : public exception {
   const char * what () const throw () {
      return "Unknown Function Name";
   }
};

struct DivideByZeroError : public exception {
   const char * what () const throw () {
      return "Divide By Zero Error";
   }
};

struct DomainError : public exception {
   const char * what () const throw () {
      return "Domain Error";
   }
};

typedef double (*MonoFunc)(double);

typedef double (*DuoFunc)(double,double);

typedef double (*SaveFunc)(VarBox&,string&,double);

union PolyFunc {
    MonoFunc m; // 1
    DuoFunc d; // 2
    SaveFunc s; // 3
};

struct FuncHolder {
    PolyFunc f;
    char t;
};

FuncHolder functionLookup(string & name);

#endif