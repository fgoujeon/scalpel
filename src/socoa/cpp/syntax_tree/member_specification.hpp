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

#ifndef SOCOA_CPP_SYNTAX_TREE_MEMBER_SPECIFICATION_HPP
#define SOCOA_CPP_SYNTAX_TREE_MEMBER_SPECIFICATION_HPP

#include <vector>
#include "member_specification_part.hpp"

namespace socoa { namespace cpp { namespace syntax_tree
{

class member_specification
{
	public:
		typedef std::vector<member_specification_part> parts_t;
		typedef parts_t::const_iterator part_const_iterator;
		typedef boost::iterator_range<part_const_iterator> part_const_iterator_range;

	public:
		explicit
		member_specification
		(
			parts_t&& parts
		);

		inline
		part_const_iterator_range
		get_parts() const;

	private:
		parts_t parts_;
};

inline
member_specification::part_const_iterator_range
member_specification::get_parts() const
{
	return part_const_iterator_range(parts_.begin(), parts_.end());
}

}}} //namespace socoa::cpp::syntax_tree

#endif
