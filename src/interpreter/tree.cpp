/*
 * This file is part of Stibbons.

 * Stibbons is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * Stibbons is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public License
 * along with Stibbons.  If not, see <http://www.gnu.org/licenses/>.
 */

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
