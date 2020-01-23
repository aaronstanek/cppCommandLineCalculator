#include "varbox.h"

#include <math.h>

VarElem::VarElem(string & n, double v) {
    name = n;
    value = v;
    nextElem = nullptr;
}

VarBox::VarBox() {
    // build variables
    string name;
    name = "ans";
    VarElem * var_ans = new VarElem(name,0);
    name = "pi";
    VarElem * var_pi = new VarElem(name,M_PI);
    name = "e";
    VarElem * var_e = new VarElem(name,M_E);
    // link them
    elems = var_ans;
    var_ans->nextElem = var_pi;
    var_pi->nextElem = var_e;
}

void VarBox::save(string & name, double value) {
    VarElem * p = elems;
    while (true) {
        if (name == p->name) {
            p->value = value;
            return;
        }
        if (p->nextElem == nullptr) {
            p->nextElem = new VarElem(name,value);
        }
        else {
            p = p->nextElem;
        }
    }
}

double VarBox::load(string & name) {
    VarElem * p = elems;
    while (p != nullptr) {
        if (name == p->name) {
            return p->value;
        }
        else {
            p = p->nextElem;
        }
    }
    throw UnknownVariableName();
}