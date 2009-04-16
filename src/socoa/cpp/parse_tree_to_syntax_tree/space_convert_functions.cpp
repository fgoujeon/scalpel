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

#include "space_convert_functions.hpp"

#include "basic_functions.hpp"
#include "node_converter.hpp"

namespace socoa { namespace cpp { namespace parse_tree_to_syntax_tree
{

boost::optional<syntax_tree::space>
convert_previous_space(const tree_node_iterator_t& i)
{
	tree_node_iterator_t it = i;
	--it;
	if(get_id(*it) == id_t::SPACE)
		return convert_node<syntax_tree::space, id_t::SPACE>(*it);
	else
		return boost::optional<syntax_tree::space>();
}

boost::optional<syntax_tree::space>
convert_next_space(const tree_node_iterator_t& i)
{
	tree_node_iterator_t it = i;
	++it;
	if(get_id(*it) == id_t::SPACE)
		return convert_node<syntax_tree::space, id_t::SPACE>(*it);
	else
		return boost::optional<syntax_tree::space>();
}

}}} //namespace socoa::cpp::parse_tree_to_syntax_tree

