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

#ifndef SOCOA_CPP_SYNTAX_NODES_STRING_LITERAL_HPP
#define SOCOA_CPP_SYNTAX_NODES_STRING_LITERAL_HPP

#include "composite_node.hpp"
#include "leaf_node.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
{

/**
\verbatim
string_literal
	= ["L"], ´"´, string_value, ´"´
;
\endverbatim
*/
class string_literal: public composite_node
{
	public:
		string_literal
		(
			bool wide,
			std::string&& value
		);

		string_literal(const string_literal& o);

		string_literal(string_literal&& o);

		const string_literal&
		operator=(const string_literal& o);

	private:
		void
		update_node_list();

		bool wide_;
		leaf_node value_;
};

}}} //namespace socoa::cpp::syntax_nodes

#endif
