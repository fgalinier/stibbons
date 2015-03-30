#include "tree.h"

namespace stibbons {

	Tree::Tree(int token,Value* val): node(token,val),sons(new std::vector<Tree*>()) {}

	Tree::~Tree() {
		if(std::get<1>(node) != nullptr) delete std::get<1>(node);
		for(auto t : *sons) {
			delete t;
		}
		delete sons;
	}

	bool Tree::isLeaf() const {
		return sons->empty();
	}

	std::pair<int,Value*> Tree::getNode() const {
		return node;
	}

	void Tree::addSon(Tree* t) {
		if(t) {
			sons->push_back(t);
		}
	}

	void Tree::addSon(int token,Value* val) {
		sons->push_back(new Tree(token,val));
	}

	std::vector<Tree*>* Tree::getSons() const {
		return sons;
	}

	Tree* Tree::getSon(size_t pos) const {
		return sons->at(pos);
	}


	void Tree::setPosition(std::pair<int,int> pos) {
		position = pos;
	}

	std::pair<int,int> Tree::getPosition() const {
		return position;
	}

	void Tree::output(std::ostream& os,std::string dec) const {
		os<<dec<<" "<<std::get<0>(node)<<std::endl;
		for(auto t : *sons) {
			t->output(os, dec+"-");
		}
	}
}

/*
 * Editor modelines  -  http://www.wireshark.org/tools/modelines.html
 *
 * Local variables:
 * c-basic-offset: 4
 * tab-width: 4
 * indent-tabs-mode: t
 * truncate-lines: 1
 * End:
 *
 * vim:set ft=cpp ts=4 sw=4 sts=4
 */
