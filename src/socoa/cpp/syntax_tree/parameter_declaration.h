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

#ifndef SOCOA_CPP_SYNTAX_TREE_PARAMETER_DECLARATION_H
#define SOCOA_CPP_SYNTAX_TREE_PARAMETER_DECLARATION_H

#include <memory>
#include "../../util/sequence.h"

namespace socoa { namespace cpp { namespace syntax_tree
{

class declarator;
class decl_specifier;

class parameter_declaration
{
	public:
		parameter_declaration
		(
			util::sequence<decl_specifier> a_decl_specifier_seq,
			std::shared_ptr<declarator> a_declarator,
			bool equal
		);

		inline
		const util::sequence<decl_specifier>
		get_decl_specifier_seq() const;

		inline
		const std::shared_ptr<const declarator>
		get_declarator() const;

		inline
		bool
		has_equal() const;

	private:
		util::sequence<decl_specifier> decl_specifier_seq_;
		std::shared_ptr<declarator> declarator_;
		bool equal_;
};

inline
const util::sequence<decl_specifier>
parameter_declaration::get_decl_specifier_seq() const
{
	return decl_specifier_seq_;
}

inline
const std::shared_ptr<const declarator>
parameter_declaration::get_declarator() const
{
	return declarator_;
}

inline
bool
parameter_declaration::has_equal() const
{
	return equal_;
}

}}} //namespace socoa::cpp::syntax_tree

#endif
