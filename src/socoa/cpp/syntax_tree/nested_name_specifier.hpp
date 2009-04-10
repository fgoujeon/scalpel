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

#ifndef SOCOA_CPP_SYNTAX_TREE_NESTED_NAME_SPECIFIER_HPP
#define SOCOA_CPP_SYNTAX_TREE_NESTED_NAME_SPECIFIER_HPP

#include <vector>
#include <boost/range/iterator_range.hpp>
#include "composite_node.hpp"
#include "identifier_or_template_id.hpp"

namespace socoa { namespace cpp { namespace syntax_tree
{

class nested_name_specifier: public composite_node
{
	public:
		class second_part;

		typedef std::vector<second_part> second_parts_t;
		typedef second_parts_t::const_iterator second_part_const_iterator;
		typedef boost::iterator_range<second_part_const_iterator> second_part_const_iterator_range;

		nested_name_specifier
		(
			identifier_or_template_id&& an_identifier_or_template_id,
			second_parts_t&& parts
		);

		nested_name_specifier(const nested_name_specifier&) = delete;

		nested_name_specifier(nested_name_specifier&& o);

		inline
		const identifier_or_template_id&
		get_identifier_or_template_id() const;

		inline
		second_part_const_iterator_range
		get_parts() const;

	private:
		identifier_or_template_id identifier_or_template_id_;
		second_parts_t parts_;
};

class nested_name_specifier::second_part: public composite_node
{
	public:
		second_part
		(
			bool template_keyword,
			identifier_or_template_id&& an_identifier_or_template_id
		);

		second_part(const second_part& o) = delete;

		second_part(second_part&& o);

		inline
		bool
		has_template_keyword() const;

		inline
		const identifier_or_template_id&
		get_identifier_or_template_id() const;

	private:
		bool template_keyword_;
		identifier_or_template_id identifier_or_template_id_;
};

inline
bool
nested_name_specifier::second_part::has_template_keyword() const
{
	return template_keyword_;
}

inline
const identifier_or_template_id&
nested_name_specifier::second_part::get_identifier_or_template_id() const
{
	return identifier_or_template_id_;
}

inline
const identifier_or_template_id&
nested_name_specifier::get_identifier_or_template_id() const
{
	return identifier_or_template_id_;
}

inline
nested_name_specifier::second_part_const_iterator_range
nested_name_specifier::get_parts() const
{
	return boost::iterator_range<second_part_const_iterator>(parts_.begin(), parts_.end());
}

}}} //namespace socoa::cpp::syntax_tree

#endif
