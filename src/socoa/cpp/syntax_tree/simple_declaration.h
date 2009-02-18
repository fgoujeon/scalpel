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

#ifndef SOCOA_CPP_SYNTAX_TREE_SIMPLE_DECLARATION_H
#define SOCOA_CPP_SYNTAX_TREE_SIMPLE_DECLARATION_H

#include <memory>
#include <boost/optional.hpp>
#include "init_declarator_list.h"
#include "decl_specifier_seq.h"
#include "../../util/sequence.h"
#include "../../util/extern_strings.h"

namespace socoa { namespace cpp { namespace syntax_tree
{

class simple_declaration
{
	public:
		simple_declaration
		(
			boost::optional<decl_specifier_seq> a_decl_specifier_seq,
			boost::optional<init_declarator_list> an_init_declarator_list
		);

		inline
		const boost::optional<const decl_specifier_seq&>
		get_decl_specifier_seq() const;

		inline
		const boost::optional<const init_declarator_list&>
		get_init_declarator_list() const;

	private:
		boost::optional<decl_specifier_seq> decl_specifier_seq_;
		boost::optional<init_declarator_list> init_declarator_list_;
};

inline
const boost::optional<const decl_specifier_seq&>
simple_declaration::get_decl_specifier_seq() const
{
	return boost::optional<const decl_specifier_seq&>(decl_specifier_seq_);
}

inline
const boost::optional<const init_declarator_list&>
simple_declaration::get_init_declarator_list() const
{
	return boost::optional<const init_declarator_list&>(init_declarator_list_);
}

}}} //namespace socoa::cpp::syntax_tree

#endif
