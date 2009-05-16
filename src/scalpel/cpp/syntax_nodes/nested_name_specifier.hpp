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

#include <vector>
#include <boost/range/iterator_range.hpp>
#include "composite_node.hpp"
#include "identifier_or_template_id.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

class nested_name_specifier: public composite_node
{
	public:
		class last_part;

		typedef list_node<last_part> last_part_seq;

		nested_name_specifier
		(
			identifier_or_template_id&& an_identifier_or_template_id,
			optional_node<space>&& post_identifier_or_template_id_space_node,
			optional_node<space>&& pre_last_part_seq_space_node,
			optional_node<last_part_seq>&& a_last_part_seq
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
		void
		update_node_list();

		identifier_or_template_id identifier_or_template_id_;
		optional_node<space> post_identifier_or_template_id_space_;
		optional_node<space> pre_last_part_seq_space_;
		optional_node<last_part_seq> last_part_seq_;
};

class nested_name_specifier::last_part: public composite_node
{
	public:
		last_part
		(
			bool template_keyword,
			identifier_or_template_id&& an_identifier_or_template_id
		);

		last_part(const last_part& o);

		last_part(last_part&& o);

		const last_part&
		operator=(const last_part& o);

		inline
		bool
		has_template_keyword() const;

		inline
		const identifier_or_template_id&
		identifier_or_template_id_node() const;

	private:
		void
		update_node_list();

		bool template_keyword_;
		identifier_or_template_id identifier_or_template_id_;
};

inline
bool
nested_name_specifier::last_part::has_template_keyword() const
{
	return template_keyword_;
}

inline
const identifier_or_template_id&
nested_name_specifier::last_part::identifier_or_template_id_node() const
{
	return identifier_or_template_id_;
}

inline
const identifier_or_template_id&
nested_name_specifier::identifier_or_template_id_node() const
{
	return identifier_or_template_id_;
}

inline
const optional_node<nested_name_specifier::last_part_seq>&
nested_name_specifier::last_part_seq_node() const
{
	return last_part_seq_;
}

}}} //namespace scalpel::cpp::syntax_nodes

#endif
