#ifndef _VARBOX_
#define _VARBOX_

#include <string>

using namespace std;

struct UnknownVariableName : public exception {
   const char * what () const throw () {
      return "Unknown Variable Name";
   }
};

class VarElem {
    public:
    string name;
    double value;
    VarElem * nextElem;
    VarElem(string & n, double v);
};

class VarBox {
    private:
    VarElem * elems;
    public:
    VarBox();
    void save(string & name, double value);
    double load(string & name);
};

#endif