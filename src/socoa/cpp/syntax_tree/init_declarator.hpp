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

#ifndef SOCOA_CPP_SYNTAX_TREE_INIT_DECLARATOR_HPP
#define SOCOA_CPP_SYNTAX_TREE_INIT_DECLARATOR_HPP

#include <memory>
#include "composite_node.hpp"
#include "declarator.hpp"

namespace socoa { namespace cpp { namespace syntax_tree
{

class init_declarator: public composite_node
{
	public:
		init_declarator(declarator&& a_declarator);

		init_declarator(init_declarator&& o);

		inline
		const declarator&
		get_declarator() const;

	private:
		declarator declarator_;
		//const std::shared_ptr<initializer> initializer_;
};

inline
const declarator&
init_declarator::get_declarator() const
{
	return declarator_;
}

}}} //namespace socoa::cpp::syntax_tree

#endif
