#include "tree.h"

namespace stibbons {

	Tree::Tree(int token,Values* val): node(token,val),sons(new vector<Tree>()) {}

	Tree::~Tree() {
		delete std::get<1>(node);
		delete sons;
	}

	bool Tree::isLeaf() const {
		return sons->empty();
	}

	pair<int,Values*> Tree::getNode() const {
		return node;
	}

	void Tree::addSon(Tree* t) {
		sons->push_back(*t);
	}

	void Tree::addSon(int token,Values* val) {
		sons->push_back({token,val});
	}

	Tree& Tree::getSon(size_t pos) const {
		return sons->at(pos);
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
