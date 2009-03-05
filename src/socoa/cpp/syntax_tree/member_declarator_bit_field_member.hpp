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

#ifndef SOCOA_CPP_SYNTAX_TREE_MEMBER_DECLARATOR_BIT_FIELD_MEMBER_HPP
#define SOCOA_CPP_SYNTAX_TREE_MEMBER_DECLARATOR_BIT_FIELD_MEMBER_HPP

#include <boost/optional.hpp>
#include "identifier.hpp"

namespace socoa { namespace cpp { namespace syntax_tree
{

class member_declarator_bit_field_member
{
	public:
		member_declarator_bit_field_member
		(
			boost::optional<identifier> an_identifier
		);

		inline
		const boost::optional<const identifier&>
		get_identifier() const;

	private:
		boost::optional<identifier> identifier_;
};

inline
const boost::optional<const identifier&>
member_declarator_bit_field_member::get_identifier() const
{
	return boost::optional<const identifier&>(identifier_);
}

}}} //namespace socoa::cpp::syntax_tree

#endif
