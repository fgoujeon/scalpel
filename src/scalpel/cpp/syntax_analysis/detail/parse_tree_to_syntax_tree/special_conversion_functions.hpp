/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2011  Florian Goujeon

This file is part of Scalpel.

Scalpel is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Scalpel is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Scalpel.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SCALPEL_CPP_SYNTAX_ANALYSIS_DETAIL_PARSE_TREE_TO_SYNTAX_TREE_SPECIAL_CONVERT_FUNCTIONS_HPP
#define SCALPEL_CPP_SYNTAX_ANALYSIS_DETAIL_PARSE_TREE_TO_SYNTAX_TREE_SPECIAL_CONVERT_FUNCTIONS_HPP

#include "node_converter.hpp"
#include "typedefs.hpp"
#include <string>
#include <vector>

namespace scalpel { namespace cpp { namespace syntax_analysis { namespace detail { namespace parse_tree_to_syntax_tree
{

template<class ContainerT>
ContainerT
convert_list_node(const tree_node_t& node)
{
	ContainerT list;

	for(tree_node_iterator_t i = node.children.begin(); i != node.children.end(); ++i) //for each child node
	{
		list.push_back(convert_node<typename ContainerT::type>(*i));
	}

	return list;
}



template<class T>
syntax_nodes::optional_node<T>
convert_optional_node(const tree_node_t& parent_node, const tree_node_iterator_t& it)
{
	if(it != parent_node.children.end())
		return convert_node<T>(*it);
	else
		return syntax_nodes::optional_node<T>();
}



template<class T>
struct predefined_text_node_converter;

template<const std::string& Text>
struct predefined_text_node_converter<syntax_nodes::predefined_text_node<Text>>
{
	static
	syntax_nodes::predefined_text_node<Text>
	convert()
	{
		return syntax_nodes::predefined_text_node<Text>();
	}
};

template<class T>
T
convert_predefined_text_node(const tree_node_t&)
{
	return predefined_text_node_converter<T>::convert();
}

}}}}} //namespace scalpel::cpp::syntax_analysis::detail::parse_tree_to_syntax_tree

#endif

