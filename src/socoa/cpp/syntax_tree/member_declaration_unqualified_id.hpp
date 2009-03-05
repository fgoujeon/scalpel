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

#ifndef SOCOA_CPP_SYNTAX_TREE_MEMBER_DECLARATION_UNQUALIFIED_ID_HPP
#define SOCOA_CPP_SYNTAX_TREE_MEMBER_DECLARATION_UNQUALIFIED_ID_HPP

#include "nested_name_specifier.hpp"
#include "unqualified_id.hpp"

namespace socoa { namespace cpp { namespace syntax_tree
{

class member_declaration_unqualified_id
{
	public:
		member_declaration_unqualified_id
		(
			bool leading_double_colon,
			nested_name_specifier&& a_nested_name_specifier,
			bool template_keyword,
			unqualified_id&& an_unqualified_id
		);

		inline
		bool
		has_leading_double_colon() const;

		inline
		const nested_name_specifier&
		get_nested_name_specifier() const;

		inline
		bool
		has_template_keyword() const;

		inline
		const unqualified_id&
		get_unqualified_id() const;

	private:
		bool leading_double_colon_;
		nested_name_specifier nested_name_specifier_;
		bool template_keyword_;
		unqualified_id unqualified_id_;
};

inline
bool
member_declaration_unqualified_id::has_leading_double_colon() const
{
	return leading_double_colon_;
}

inline
const nested_name_specifier&
member_declaration_unqualified_id::get_nested_name_specifier() const
{
	return nested_name_specifier_;
}

inline
bool
member_declaration_unqualified_id::has_template_keyword() const
{
	return template_keyword_;
}

inline
const unqualified_id&
member_declaration_unqualified_id::get_unqualified_id() const
{
	return unqualified_id_;
}

}}} //namespace socoa::cpp::syntax_tree

#endif
