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

#ifndef SOCOA_CPP_SYNTAX_TREE_MEM_INITIALIZER_HPP
#define SOCOA_CPP_SYNTAX_TREE_MEM_INITIALIZER_HPP

#include "composite_node.hpp"
#include "mem_initializer_id.hpp"

namespace socoa { namespace cpp { namespace syntax_tree
{

class mem_initializer: public composite_node
{
	public:
		explicit
		mem_initializer
		(
			mem_initializer_id&& a_mem_initializer_id
		);

		inline
		const mem_initializer_id&
		get_mem_initializer_id() const;

	private:
		mem_initializer_id mem_initializer_id_;
		//const std::shared_ptr<util::sequence<assignment_expression, util::extern_strings::comma>> expression_list_;
};

inline
const mem_initializer_id&
mem_initializer::get_mem_initializer_id() const
{
	return mem_initializer_id_;
}

}}} //namespace socoa::cpp::syntax_tree

#endif
