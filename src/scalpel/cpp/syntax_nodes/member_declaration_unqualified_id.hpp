/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008, 2009  Florian Goujeon

This file is part of Scalpel.

Scalpel is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Scalpel is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Scalpel.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SCALPEL_CPP_SYNTAX_NODES_MEMBER_DECLARATION_UNQUALIFIED_ID_HPP
#define SCALPEL_CPP_SYNTAX_NODES_MEMBER_DECLARATION_UNQUALIFIED_ID_HPP

#include "composite_node.hpp"
#include "nested_name_specifier.hpp"
#include "unqualified_id.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
\verbatim
member_declaration_unqualified_id
	= !(str_p("::") >> !s) >> nested_name_specifier >> !s >> !(str_p("template") >> !s) >> unqualified_id >> !s >> ch_p(';')
;
\endverbatim
*/
class member_declaration_unqualified_id: public composite_node
{
	public:
		member_declaration_unqualified_id
		(
			bool leading_double_colon,
			optional_node<space>&& post_double_colon_space_node,
			nested_name_specifier&& nested_name_specifier_node,
			optional_node<space>&& post_nested_name_specifier_space_node,
			bool template_keyword,
			optional_node<space>&& post_template_keyword_space_node,
			unqualified_id&& unqualified_id_node,
			optional_node<space>&& post_unqualified_id_space_node
		);

		member_declaration_unqualified_id(const member_declaration_unqualified_id& o);

		member_declaration_unqualified_id(member_declaration_unqualified_id&& o);

		const member_declaration_unqualified_id&
		operator=(const member_declaration_unqualified_id& o);

		inline
		bool
		has_leading_double_colon() const;

		inline
		const nested_name_specifier&
		nested_name_specifier_node() const;

		inline
		bool
		has_template_keyword() const;

		inline
		const unqualified_id&
		unqualified_id_node() const;

	private:
		void
		update_node_list();

		bool leading_double_colon_;
		optional_node<space> post_double_colon_space_;
		nested_name_specifier nested_name_specifier_;
		optional_node<space> post_nested_name_specifier_space_;
		bool template_keyword_;
		optional_node<space> post_template_keyword_space_;
		unqualified_id unqualified_id_;
		optional_node<space> post_unqualified_id_space_;
};

inline
bool
member_declaration_unqualified_id::has_leading_double_colon() const
{
	return leading_double_colon_;
}

inline
const nested_name_specifier&
member_declaration_unqualified_id::nested_name_specifier_node() const
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
member_declaration_unqualified_id::unqualified_id_node() const
{
	return unqualified_id_;
}

}}} //namespace scalpel::cpp::syntax_nodes

#endif
