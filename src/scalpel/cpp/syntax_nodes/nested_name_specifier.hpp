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

#ifndef SCALPEL_CPP_SYNTAX_NODES_NESTED_NAME_SPECIFIER_HPP
#define SCALPEL_CPP_SYNTAX_NODES_NESTED_NAME_SPECIFIER_HPP

#include "common.hpp"
#include "identifier_or_template_id.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

typedef
	sequence_node
	<
		optional_node<simple_text_node<str::template_>>,
		optional_node<space>,
		identifier_or_template_id,
		optional_node<space>,
		simple_text_node<str::double_colon>
	>
	nested_name_specifier_last_part_t
;
class nested_name_specifier_last_part;

typedef
	list_node<nested_name_specifier_last_part>
	nested_name_specifier_last_part_seq
;

typedef
	sequence_node
	<
		identifier_or_template_id,
		optional_node<space>,
		simple_text_node<str::double_colon>,
		optional_node<space>,
		optional_node<nested_name_specifier_last_part_seq>
	>
	nested_name_specifier_t
;

/**
nested_name_specifier
	= identifier_or_template_id >> !s >> "::" >> !(!s >> nested_name_specifier_last_part_seq)
;
nested_name_specifier_last_part_seq
	= nested_name_specifier_last_part % !s
;
nested_name_specifier_last_part
	= !(str_p("template") >> !s) >> identifier_or_template_id >> !s >> "::"
;
*/

class nested_name_specifier: public composite_node
{
	public:
		typedef nested_name_specifier_t type;
		typedef type::head_node_t head_node_t;
		typedef type::tail_sequence_node_t tail_sequence_node_t;

		typedef nested_name_specifier_last_part last_part;
		typedef nested_name_specifier_last_part_seq last_part_seq;

		nested_name_specifier
		(
			identifier_or_template_id&& o0,
			optional_node<space>&& o1,
			simple_text_node<str::double_colon>&& o2,
			optional_node<space>&& o3,
			optional_node<nested_name_specifier_last_part_seq>&& o4
		);

		nested_name_specifier
		(
			head_node_t&& head,
			tail_sequence_node_t&& tail
		);

		nested_name_specifier(const nested_name_specifier& o);

		nested_name_specifier(nested_name_specifier&& o);

		const nested_name_specifier&
		operator=(const nested_name_specifier& o);

		inline
		const identifier_or_template_id&
		identifier_or_template_id_node() const;

		inline
		const optional_node<last_part_seq>&
		last_part_seq_node() const;

	private:
		type impl_;
};

const identifier_or_template_id&
nested_name_specifier::identifier_or_template_id_node() const
{
	return get<0>(impl_);
}

const optional_node<nested_name_specifier::last_part_seq>&
nested_name_specifier::last_part_seq_node() const
{
	return get<4>(impl_);
}



class nested_name_specifier_last_part: public composite_node
{
	public:
		typedef nested_name_specifier_last_part_t type;
		typedef type::head_node_t head_node_t;
		typedef type::tail_sequence_node_t tail_sequence_node_t;

		nested_name_specifier_last_part
		(
			optional_node<simple_text_node<str::template_>>&& o0,
			optional_node<space>&& o1,
			identifier_or_template_id&& o2,
			optional_node<space>&& o3,
			simple_text_node<str::double_colon>&& o4
		);

		nested_name_specifier_last_part
		(
			head_node_t&& head,
			tail_sequence_node_t&& tail
		);

		nested_name_specifier_last_part(const nested_name_specifier_last_part& o);

		nested_name_specifier_last_part(nested_name_specifier_last_part&& o);

		const nested_name_specifier_last_part&
		operator=(const nested_name_specifier_last_part& o);

		inline
		const identifier_or_template_id&
		identifier_or_template_id_node() const;

	private:
		type impl_;
};

const identifier_or_template_id&
nested_name_specifier_last_part::identifier_or_template_id_node() const
{
	return get<2>(impl_);
}

}}} //namespace scalpel::cpp::syntax_nodes

#endif
