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

#ifndef SOCOA_CPP_SYNTAX_NODES_NESTED_NAME_SPECIFIER_HPP
#define SOCOA_CPP_SYNTAX_NODES_NESTED_NAME_SPECIFIER_HPP

#include <vector>
#include <boost/range/iterator_range.hpp>
#include "composite_node.hpp"
#include "identifier_or_template_id.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
{

class nested_name_specifier: public composite_node
{
	public:
		class next_part;

		typedef sequence_node<next_part> next_part_seq;

		nested_name_specifier
		(
			identifier_or_template_id&& an_identifier_or_template_id,
			boost::optional<space>&& post_identifier_or_template_id_space_node,
			boost::optional<space>&& pre_next_part_seq_space_node,
			boost::optional<next_part_seq>&& a_next_part_seq
		);

		nested_name_specifier(const nested_name_specifier& o);

		nested_name_specifier(nested_name_specifier&& o);

		const nested_name_specifier&
		operator=(const nested_name_specifier& o);

		inline
		const identifier_or_template_id&
		identifier_or_template_id_node() const;

		inline
		const boost::optional<const next_part_seq&>
		next_part_seq_node() const;

	private:
		void
		update_node_list();

		identifier_or_template_id identifier_or_template_id_;
		boost::optional<space> post_identifier_or_template_id_space_;
		boost::optional<space> pre_next_part_seq_space_;
		boost::optional<next_part_seq> next_part_seq_;
};

class nested_name_specifier::next_part: public composite_node
{
	public:
		next_part
		(
			bool template_keyword,
			identifier_or_template_id&& an_identifier_or_template_id
		);

		next_part(const next_part& o);

		next_part(next_part&& o);

		const next_part&
		operator=(const next_part& o);

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
nested_name_specifier::next_part::has_template_keyword() const
{
	return template_keyword_;
}

inline
const identifier_or_template_id&
nested_name_specifier::next_part::identifier_or_template_id_node() const
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
const boost::optional<const nested_name_specifier::next_part_seq&>
nested_name_specifier::next_part_seq_node() const
{
	return boost::optional<const nested_name_specifier::next_part_seq&>(next_part_seq_);
}

}}} //namespace socoa::cpp::syntax_nodes

#endif
