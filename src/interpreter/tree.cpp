#include "tree.h"
#include "y.tab.h"

using namespace std;

namespace stibbons {

	Tree::Tree(int token,ValuePtr val): node(token,val),children(std::vector<TreePtr >()) {}

	bool Tree::isLeaf() const {
		return children.empty();
	}

	std::pair<int,ValuePtr> Tree::getNode() const {
		return node;
	}

	void Tree::mergeTree(TreePtr  t) {
		if(t == nullptr || std::get<0>(t->getNode()) != std::get<0>(this->getNode())) {
			throw std::exception(); 
		}
		children.insert(children.end(),t->getChildren().begin(),t->getChildren().end());
	}

	void Tree::appendChildren(TreePtr  t) {
		if(t != nullptr) {
			children.insert(children.end(),t->getChildren().begin(),t->getChildren().end());
		}
	}

	void Tree::addChild(TreePtr  t) {
		if(t) {
			children.push_back(t);
		}
	}

	void Tree::addChild(int token,ValuePtr val) {
		children.push_back(make_shared<Tree>(token,val));
	}

	const std::vector<TreePtr >& Tree::getChildren() const {
		return children;
	}

	TreePtr  Tree::getChild(size_t pos) const {
		return children.at(pos);
	}


	void Tree::setPosition(std::pair<int,int> pos) {
		position = pos;
	}

	std::pair<int,int> Tree::getPosition() const {
		return position;
	}

	void Tree::output(std::ostream& os,std::string dec) const {
		os<<dec<<" "<<::toString(std::get<0>(node))<<std::endl;
		for(auto t : children) {
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
