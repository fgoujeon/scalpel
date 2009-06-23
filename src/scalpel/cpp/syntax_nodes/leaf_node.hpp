/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008, 2009  Florian Goujeon

This file is part of Scalpel.

Scalpel is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Scalpel is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Scalpel.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SCALPEL_CPP_SYNTAX_NODES_LEAF_NODE_HPP
#define SCALPEL_CPP_SYNTAX_NODES_LEAF_NODE_HPP

#include <string>
#include "node.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

class leaf_node: public node
{
	public:
		explicit
		leaf_node(const std::string& value);

		explicit
		leaf_node(std::string&& value);

		leaf_node(const leaf_node& n);

		leaf_node(leaf_node&& n);

		virtual
		~leaf_node();

		const std::string
		value() const;

		void
		value(const std::string& code);

		void
		value(std::string&& code);

	private:
		std::string value_;
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
