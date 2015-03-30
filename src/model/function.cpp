#include "function.h"

#include <cstring>

namespace stibbons {

Function::Function (Tree arbre, vector<string> l){
	arguments=l;
	setValue(arbre);
}

void Function::setArg (string r){
	lock_guard<mutex> lock(value_m);
	arguments.push_back(r);
}

vector<string> Function::getArg (){
	lock_guard<mutex> lock(value_m);
	return arguments;
}

void Function::reset(){
}

}
