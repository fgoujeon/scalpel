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

#ifndef SOCOA_CPP_SYNTAX_TREE_USING_DIRECTIVE_H
#define SOCOA_CPP_SYNTAX_TREE_USING_DIRECTIVE_H

#include <memory>
#include "visitor.h"
#include "block_declaration.h"
#include "identifier.h"

namespace socoa { namespace cpp { namespace syntax_tree
{

class nested_name_specifier;

class using_directive: public block_declaration
{
	public:
		using_directive
		(
			bool leading_double_colon,
			std::shared_ptr<nested_name_specifier> a_nested_name_specifier,
			identifier&& an_identifier
		);

		inline
		bool
		has_leading_double_colon() const;

		inline
		const std::shared_ptr<const nested_name_specifier>
		get_nested_name_specifier() const;

		inline
		const identifier&
	   	get_identifier() const;

		SOCOA_CPP_DEFINE_VISITABLE()

	private:
		bool leading_double_colon_;
		std::shared_ptr<nested_name_specifier> nested_name_specifier_;
		identifier identifier_;
};

inline
bool
using_directive::has_leading_double_colon() const
{
	return leading_double_colon_;
}

inline
const std::shared_ptr<const nested_name_specifier>
using_directive::get_nested_name_specifier() const
{
	return nested_name_specifier_;
}

inline
const identifier&
using_directive::get_identifier() const
{
	return identifier_;
}

}}} //namespace socoa::cpp::syntax_tree

#endif
