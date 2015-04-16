#include "tree.h"

using namespace std;

namespace stibbons {

	Tree::Tree(int token,ValuePtr val): node(token,val),sons(std::vector<TreePtr >()) {}

	bool Tree::isLeaf() const {
		return sons.empty();
	}

	std::pair<int,ValuePtr> Tree::getNode() const {
		return node;
	}

	void Tree::mergeTree(TreePtr  t) {
		if(t == nullptr || std::get<0>(t->getNode()) != std::get<0>(this->getNode())) {
			throw std::exception(); 
		}
		sons.insert(sons.end(),t->getSons().begin(),t->getSons().end());
	}

	void Tree::appendSons(TreePtr  t) {
		if(t != nullptr) {
			sons.insert(sons.end(),t->getSons().begin(),t->getSons().end());
		}
	}

	void Tree::addSon(TreePtr  t) {
		if(t) {
			sons.push_back(t);
		}
	}

	void Tree::addSon(int token,ValuePtr val) {
		sons.push_back(make_shared<Tree>(token,val));
	}

	const std::vector<TreePtr >& Tree::getSons() const {
		return sons;
	}

	TreePtr  Tree::getSon(size_t pos) const {
		return sons.at(pos);
	}


	void Tree::setPosition(std::pair<int,int> pos) {
		position = pos;
	}

	std::pair<int,int> Tree::getPosition() const {
		return position;
	}

	void Tree::output(std::ostream& os,std::string dec) const {
		os<<dec<<" "<<std::get<0>(node)<<std::endl;
		for(auto t : sons) {
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
