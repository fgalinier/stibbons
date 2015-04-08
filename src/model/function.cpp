#include "function.h"

#include <cstring>
#include <sstream>

namespace stibbons {

Function::Function (Tree* arbre, vector<string> l){
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

string Function::toString () {
	std::ostringstream oss;

	oss << "function(" << getValue() << ")";

	return oss.str();
}

}
