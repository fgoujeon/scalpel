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

#ifndef SCALPEL_CPP_SYNTAX_NODES_PREDEFINED_TEXT_NODE_HPP
#define SCALPEL_CPP_SYNTAX_NODES_PREDEFINED_TEXT_NODE_HPP

#include "node.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

template<const std::string& Text>
class predefined_text_node: public node
{
	public:
		predefined_text_node();

		inline
		const std::string
		value() const;

		child_const_iterator_range
		children() const;

	private:
		static const std::string& text_;
		static const children_t children_; //always empty
};

template<const std::string& Text>
predefined_text_node<Text>::predefined_text_node()
{
}

template<const std::string& Text>
const std::string
predefined_text_node<Text>::value() const
{
	return text_;
}

template<const std::string& Text>
node::child_const_iterator_range
predefined_text_node<Text>::children() const
{
	child_const_iterator first = children_.begin();
	child_const_iterator last = children_.end();

	child_const_indirect_iterator const_indirect_first(first), const_indirect_last(last);

	return child_const_iterator_range(const_indirect_first, const_indirect_last);
}

template<const std::string& Text>
const std::string& predefined_text_node<Text>::text_ = Text;

template<const std::string& Text>
const node::children_t predefined_text_node<Text>::children_;

}}} //namespace scalpel::cpp::syntax_nodes

#endif
