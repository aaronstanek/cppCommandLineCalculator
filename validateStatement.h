#ifndef _VALIDATESTATEMENT_
#define _VALIDATESTATEMENT_

#include <string>
#include <exception>

using namespace std;

struct InvalidCharacterError : public exception {
   const char * what () const throw () {
      return "Invalid Character Error";
   }
};

struct ParenthesisMismatchError : public exception {
   const char * what () const throw () {
      return "Parenthesis Mismatch Error";
   }
};

void validateStatement(string & statement);

#endif