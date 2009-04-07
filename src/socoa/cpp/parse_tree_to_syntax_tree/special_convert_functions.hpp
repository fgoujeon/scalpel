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

#ifndef SOCOA_CPP_PARSE_TREE_TO_SYNTAX_TREE_SPECIAL_CONVERT_FUNCTIONS_HPP
#define SOCOA_CPP_PARSE_TREE_TO_SYNTAX_TREE_SPECIAL_CONVERT_FUNCTIONS_HPP

#include <string>
#include <vector>
#include "../../util/sequence.hpp"
#include "../../util/string_enumeration.hpp"
#include "typedefs.hpp"
#include "convert_function_callers.hpp"

namespace socoa { namespace cpp { namespace parse_tree_to_syntax_tree
{

template<class T>
T
convert_sequence(const tree_node_t& node)
{
	return T
	(
		convert_separated_nodes<typename T::type>
		(
			node,
			T::separator
		)
	);
}

template<class T>
T
convert_string_enumeration(const tree_node_t& node)
{
	return T
	(
		get_only_child_value(node)
	);
}

template <class T>
std::vector<T>
convert_separated_nodes
(
	const tree_node_t& parent_node,
	const std::string& separator
)
{
	std::vector<T> seq;
	for(tree_node_iterator_t i = parent_node.children.begin(); i != parent_node.children.end(); ++i) //for each child
	{
		const tree_node_t& child_node = *i;
		const std::string child_value = get_value(child_node);

		if(child_value != separator) //if the current node is not a separator
		{
			seq.push_back(convert_function_caller_from_type<T>::convert(child_node));
		}
	}

	return seq;
}

}}} //namespace socoa::cpp::parse_tree_to_syntax_tree

#endif
