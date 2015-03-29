#include "function.h"

#include <cstring>

namespace stibbons {

Function::Function (vector<Value*> l, Tree arbre){
	arguments=l;
	setValue(arbre);
}

void Function::setArg (Value* r){
	arguments.push_back(r);
}

vector<Value*> Function::getArg (){
	return arguments;
}

void Function::reset(){
}

}
