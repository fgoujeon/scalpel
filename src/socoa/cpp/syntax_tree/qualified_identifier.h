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

#ifndef SOCOA_CPP_SYNTAX_TREE_QUALIFIED_IDENTIFIER_H
#define SOCOA_CPP_SYNTAX_TREE_QUALIFIED_IDENTIFIER_H

#include "identifier.h"

namespace socoa { namespace cpp { namespace syntax_tree
{

class qualified_identifier
{
	public:
		explicit
		qualified_identifier
		(
			identifier&& an_identifier
		);

		inline
		const identifier&
	   	get_identifier() const;

	private:
		identifier identifier_;
};

inline
const identifier&
qualified_identifier::get_identifier() const
{
	return identifier_;
}

}}} //namespace socoa::cpp::syntax_tree

#endif