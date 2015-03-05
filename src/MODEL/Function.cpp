#include "Function.h"

// Constructors/Destructors
//  

Function::Function () {
initAttributes();
}

Function::Function (string n, int arg, string c) {
   name=n;
   nbarg=arg;
   code=c;
}

Function::~Function () { }

//  
// Methods
//  


// Accessor methods
//  


// Other methods
//  

void Function::initAttributes () {
    name="";
    nbarg=0;
    code="";
}

