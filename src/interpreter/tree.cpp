#include "tree.h"

using namespace stibbons;

Tree::Tree(yy::parser::token_type token,Values* val): node(token,val),sons(new vector<Tree>()) {}

Tree::~Tree() {
	delete std::get<1>(node);
	delete sons;
}

bool Tree::isLeaf() const {
	return sons->empty();
}

pair<yy::parser::token_type,Values*> Tree::getNode() const {
	return node;
}
void Tree::addSon(yy::parser::token_type token,Values* val) {
	sons->push_back({token,val});
}

Tree& Tree::getSon(size_t pos) const {
	return sons->at(pos);
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
