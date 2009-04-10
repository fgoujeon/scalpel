/*
Socoa - Source Code Analysis Library
Copyright © 2008, 2009  Florian Goujeon

This file is part of Socoa.

Socoa is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Socoa is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Socoa.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SOCOA_CPP_SYNTAX_TREE_COMPOSITE_NODE_HPP
#define SOCOA_CPP_SYNTAX_TREE_COMPOSITE_NODE_HPP

#include <vector>
#include <string>
#include "node.hpp"

namespace socoa { namespace cpp { namespace syntax_tree
{

class composite_node: public node
{
	public:
		typedef std::vector<const node*> nodes_t;

		composite_node();

		composite_node(const composite_node&) = delete;

		composite_node(composite_node&&) = delete;

		const composite_node&
		operator=(const composite_node&) = delete;

		virtual
		~composite_node();

		const std::string
		raw_code() const;

	protected:
		void
		add(const node& a_node);

		void
		clear();

	private:
		nodes_t nodes_;
};

}}} //namespace socoa::cpp::syntax_tree

#endif
