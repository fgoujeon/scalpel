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

#ifndef SOCOA_CPP_SYNTAX_TREE_MEMBER_DECLARATION_MEMBER_DECLARATOR_LIST_H
#define SOCOA_CPP_SYNTAX_TREE_MEMBER_DECLARATION_MEMBER_DECLARATOR_LIST_H

#include <memory>
#include <boost/optional.hpp>
#include "visitor.h"
#include "member_declaration.h"
#include "member_declarator_list.h"
#include "decl_specifier.h"
#include "member_declarator.h"
#include "../../util/sequence.h"

namespace socoa { namespace cpp { namespace syntax_tree
{

class member_declaration_member_declarator_list: public member_declaration
{
	public:
		member_declaration_member_declarator_list
		(
			std::shared_ptr<util::sequence<decl_specifier>> a_decl_specifier_seq,
			std::shared_ptr<member_declarator_list_t> a_member_declarator_list
		);

		inline
		const boost::optional<const util::sequence<decl_specifier>&>
		get_decl_specifier_seq() const;

		inline
		const boost::optional<const util::sequence<member_declarator, util::extern_strings::comma>&>
		get_member_declarator_list() const;

		SOCOA_CPP_DEFINE_VISITABLE()

	private:
		boost::optional<util::sequence<decl_specifier>> decl_specifier_seq_;
		boost::optional<member_declarator_list_t> member_declarator_list_;
};

inline
const boost::optional<const util::sequence<decl_specifier>&>
member_declaration_member_declarator_list::get_decl_specifier_seq() const
{
	return boost::optional<const util::sequence<decl_specifier>&>(decl_specifier_seq_);
}

inline
const boost::optional<const member_declarator_list_t&>
member_declaration_member_declarator_list::get_member_declarator_list() const
{
	return boost::optional<const member_declarator_list_t&>(member_declarator_list_);
}

}}} //namespace socoa::cpp::syntax_tree

#endif
