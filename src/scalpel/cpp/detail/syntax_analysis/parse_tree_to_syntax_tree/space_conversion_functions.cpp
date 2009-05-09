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

#include "space_conversion_functions.hpp"

#include "basic_functions.hpp"
#include "generic_node_converters.hpp"

namespace scalpel { namespace cpp { namespace detail { namespace syntax_analysis { namespace parse_tree_to_syntax_tree
{

boost::optional<syntax_nodes::space>
convert_previous_space(const tree_node_t& parent_node, tree_node_iterator_t i)
{
	if(i != parent_node.children.end())
	{
		--i;
		if(get_id(*i) == id_t::SPACE)
			return convert_node<syntax_nodes::space>(*i);
	}
	return boost::optional<syntax_nodes::space>();
}

boost::optional<syntax_nodes::space>
convert_next_space(const tree_node_t& parent_node, tree_node_iterator_t i)
{
	if(i != parent_node.children.end())
	{
		++i;
		if(get_id(*i) == id_t::SPACE)
			return convert_node<syntax_nodes::space>(*i);
	}
	return boost::optional<syntax_nodes::space>();
}

}}}}} //namespace scalpel::cpp::detail::syntax_analysis::parse_tree_to_syntax_tree

