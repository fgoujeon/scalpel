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

#ifndef SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_PARSE_TREE_TO_SYNTAX_TREE_SPECIAL_CONVERT_FUNCTIONS_HPP
#define SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_PARSE_TREE_TO_SYNTAX_TREE_SPECIAL_CONVERT_FUNCTIONS_HPP

#include <string>
#include <vector>
#include "typedefs.hpp"
#include "node_converter.hpp"
#include "node_finder.hpp"

namespace scalpel { namespace cpp { namespace detail { namespace syntax_analysis { namespace parse_tree_to_syntax_tree
{

template<class ContainerT>
ContainerT
convert_list_node(const tree_node_t& node)
{
	ContainerT list;

	if(ContainerT::separator_node.raw_code() == syntax_nodes::common_nodes::empty.raw_code()) //if the list separator is empty
	{
		syntax_nodes::optional_node<syntax_nodes::space> space_node;
		for(tree_node_iterator_t i = node.children.begin(); i != node.children.end(); ++i) //for each child node
		{
			const tree_node_t& child_node = *i;
			const std::string child_value = get_value(child_node);

			if(child_node.value.id() == id_t::SPACE)
			{
				space_node = convert_node<syntax_nodes::space>(child_node);
			}
			else
			{
				typename ContainerT::item item
				(
					space_node,
					syntax_nodes::optional_node<syntax_nodes::space>(),
					convert_node<typename ContainerT::type>(child_node)
				);
				list.push_back(item);

				//clear space node
				space_node = syntax_nodes::optional_node<syntax_nodes::space>();
			}
		}
	}
	else
	{
		syntax_nodes::optional_node<syntax_nodes::space> pre_separator_space;
		syntax_nodes::optional_node<syntax_nodes::space> post_separator_space;
		bool will_read_post_separator_space = false;
		for(tree_node_iterator_t i = node.children.begin(); i != node.children.end(); ++i) //for each child node
		{
			const tree_node_t& child_node = *i;
			const std::string child_value = get_value(child_node);

			if(child_value == ContainerT::separator_node.raw_code()) //if the node is a separator
			{
				will_read_post_separator_space = true;
			}
			else if(child_node.value.id() == id_t::SPACE) //the node is a space
			{
				if(!will_read_post_separator_space)
				{
					pre_separator_space = convert_node<syntax_nodes::space>(child_node);
					will_read_post_separator_space = true;
				}
				else
				{
					post_separator_space = convert_node<syntax_nodes::space>(child_node);
					will_read_post_separator_space = false;
				}
			}
			else //the node is the main node
			{
				typename ContainerT::item item
				(
					pre_separator_space,
					post_separator_space,
					convert_node<typename ContainerT::type>(child_node)
				);
				list.push_back(item);

				pre_separator_space = syntax_nodes::optional_node<syntax_nodes::space>();
				post_separator_space = syntax_nodes::optional_node<syntax_nodes::space>();
				will_read_post_separator_space = false;
			}
		}
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
struct simple_text_node_converter;

template<const std::string& Text>
struct simple_text_node_converter<syntax_nodes::simple_text_node<Text>>
{
	static
	syntax_nodes::simple_text_node<Text>
	convert()
	{
		return syntax_nodes::simple_text_node<Text>();
	}
};

template<class T>
T
convert_simple_text_node(const tree_node_t&)
{
	return simple_text_node_converter<T>::convert();
}

}}}}} //namespace scalpel::cpp::detail::syntax_analysis::parse_tree_to_syntax_tree

#endif
