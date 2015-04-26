#include "parser.h"
#include "tree.h"
#include <fstream>

// Entry Point
int main(int argc, char * argv[]) {
  std::string filename;
  std::cin>>filename;
  auto tree = std::make_shared<stibbons::Tree>(0,nullptr);
  std::ifstream ifs (filename, std::ifstream::in);
  if(ifs.good()) std::cout<<"Ok !"<<std::endl;
  stibbons::Parser parser(tree,&ifs);
  parser.parse();
}

