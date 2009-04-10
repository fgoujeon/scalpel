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

#ifndef SOCOA_CPP_SYNTAX_TREE_DESTRUCTOR_NAME_HPP
#define SOCOA_CPP_SYNTAX_TREE_DESTRUCTOR_NAME_HPP

#include "composite_node.hpp"
#include "identifier.hpp"

namespace socoa { namespace cpp { namespace syntax_tree
{

class destructor_name: public composite_node
{
	public:
		explicit
		destructor_name(identifier&& an_identifier);

		destructor_name(const destructor_name& o);

		destructor_name(destructor_name&& o);

		const destructor_name&
		operator=(const destructor_name& o);

		inline
		const identifier&
		get_identifier() const;

	private:
		void
		update_node_list();

		identifier identifier_;
};

inline
const identifier&
destructor_name::get_identifier() const
{
	return identifier_;
}

}}} //namespace socoa::cpp::syntax_tree

#endif
