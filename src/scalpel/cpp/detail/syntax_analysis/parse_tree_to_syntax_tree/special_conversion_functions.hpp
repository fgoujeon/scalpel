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
#include "generic_node_converters.hpp"
#include "node_finder.hpp"
#include "space_conversion_functions.hpp"

namespace scalpel { namespace cpp { namespace detail { namespace syntax_analysis { namespace parse_tree_to_syntax_tree
{

template<class T>
T
convert_string_enumeration(const tree_node_t& node)
{
	return T
	(
		get_only_child_value(node)
	);
}


template<class ContainerT>
ContainerT
convert_sequence(const tree_node_t& node)
{
	ContainerT seq;

	if(ContainerT::separator_node.raw_code() == syntax_nodes::global_nodes::empty.raw_code())
	{
		boost::optional<syntax_nodes::space> space_node;
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
					boost::optional<syntax_nodes::space>(),
					convert_node<typename ContainerT::type>(child_node)
				);
				seq.push_back(item);

				//clear space node
				space_node = boost::optional<syntax_nodes::space>();
			}
		}
	}
	else
	{
		boost::optional<syntax_nodes::space> pre_separator_space;
		boost::optional<syntax_nodes::space> post_separator_space;
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
				seq.push_back(item);

				pre_separator_space = boost::optional<syntax_nodes::space>();
				post_separator_space = boost::optional<syntax_nodes::space>();
				will_read_post_separator_space = false;
			}
		}
	}

	return seq;
}


template<class SyntaxNodeT, int... Ids>
struct alternative_node_converter;

template<class SyntaxNodeT>
struct alternative_node_converter<SyntaxNodeT>
{
	static
	SyntaxNodeT
	convert(const tree_node_t&)
	{
		assert(false);
	}
};

template<class SyntaxNodeT, int Id, int... Ids>
struct alternative_node_converter<SyntaxNodeT, Id, Ids...>
{
	static
	SyntaxNodeT
	convert(const tree_node_t& node)
	{
		const int node_id = get_id(node);
		if(node_id == Id)
		{
			return SyntaxNodeT(node_converter_from_id<SyntaxNodeT, Id>::convert(node));
		}
		else
		{
			return alternative_node_converter<SyntaxNodeT, Ids...>::convert(node);
		}
	}
};

template<class SyntaxNodeT, int... Ids>
inline
SyntaxNodeT
convert_alternative(const tree_node_t& node)
{
	return alternative_node_converter<SyntaxNodeT, Ids...>::convert
	(
		get_only_child_node(node)
	);
}


template<class T>
boost::optional<T>
convert_optional(const tree_node_t& parent_node, const tree_node_iterator_t& it)
{
	if(it != parent_node.children.end())
		return convert_node<T>(*it);
	else
		return boost::optional<T>();
}


template<const std::string&& Text>
syntax_nodes::simple_text_node<Text>
convert_simple_text(const tree_node_t&)
{
	return syntax_nodes::simple_text_node<Text>();
}


template<class CastExpressionT>
CastExpressionT
convert_cast_expression_template(const tree_node_t& node)
{
	tree_node_iterator_t cast_keyword_it = node.children.begin();
	tree_node_iterator_t left_angle_bracket_it = find_node(node, "<");
	tree_node_iterator_t type_id_it = find_node<id_t::TYPE_ID>(node);
	tree_node_iterator_t right_angle_bracket_it = find_node(node, ">");
	tree_node_iterator_t opening_round_bracket_it = find_node(node, "(");
	tree_node_iterator_t expression_it = find_node<id_t::EXPRESSION>(node);

	return CastExpressionT
	(
		convert_next_space(node, cast_keyword_it),
		convert_next_space(node, left_angle_bracket_it),
		convert_node<syntax_nodes::type_id>(*type_id_it),
		convert_next_space(node, type_id_it),
		convert_next_space(node, right_angle_bracket_it),
		convert_next_space(node, opening_round_bracket_it),
		convert_node<syntax_nodes::expression>(*expression_it),
		convert_next_space(node, expression_it)
	);
}

}}}}} //namespace scalpel::cpp::detail::syntax_analysis::parse_tree_to_syntax_tree

#endif
