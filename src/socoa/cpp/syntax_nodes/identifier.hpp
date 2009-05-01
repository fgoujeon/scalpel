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

#ifndef SOCOA_CPP_SYNTAX_NODES_IDENTIFIER_HPP
#define SOCOA_CPP_SYNTAX_NODES_IDENTIFIER_HPP

#include <string>
#include "leaf_node.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
{

class identifier: public leaf_node
{
	public:
		explicit
		identifier(std::string&& value);

		identifier(const identifier& i);

		identifier(identifier&& i);

		const identifier&
		operator=(const identifier& i);

		const identifier&
		operator=(identifier&& i);

		inline
		const std::string
		value() const;
};

inline
const std::string
identifier::value() const
{
	return raw_code();
}

}}} //namespace socoa::cpp::syntax_nodes

#endif
