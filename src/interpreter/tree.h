#pragma once

#include <vector>
#include <utility>
#include <tuple>
#include "y.tab.h"
#include "../model/values.h"

namespace stibbons {

	class Tree {
	private:
		pair<yy::parser::token_type,Values*> node;
		vector<Tree>* sons;
	public:
		Tree(yy::parser::token_type,Values*);
		virtual ~Tree();
		virtual bool isLeaf() const;
		virtual pair<yy::parser::token_type,Values*> getNode() const;
		virtual void addSon(yy::parser::token_type,Values*);
		virtual Tree& getSon(size_t pos=0) const;
	};

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
