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

#ifndef SCALPEL_CPP_SYNTAX_NODES_UTIL_VALUE_GETTER_HPP
#define SCALPEL_CPP_SYNTAX_NODES_UTIL_VALUE_GETTER_HPP

#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_same.hpp>
#include "node_type_traits.hpp"
#include "../alternative_node.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes { namespace util
{

//overload for sequence nodes
template<class SyntaxNodeT>
const std::string
get_value
(
	const SyntaxNodeT& node,
	typename boost::enable_if<syntax_nodes::util::is_sequence_node<SyntaxNodeT>>::type* = 0,
	typename boost::disable_if<boost::is_same<typename SyntaxNodeT::head_node_t, void>>::type* = 0
);

//overload for alternative nodes
template<class SyntaxNodeT>
const std::string
get_value
(
	const SyntaxNodeT& node,
	typename boost::enable_if<syntax_nodes::util::is_alternative_node<SyntaxNodeT>>::type* = 0,
	typename boost::disable_if<boost::is_same<typename SyntaxNodeT::head_node_t, void>>::type* = 0
);

//overload for list nodes
template<class SyntaxNodeT>
const std::string
get_value
(
	const SyntaxNodeT& node,
	typename boost::enable_if<syntax_nodes::util::is_list_node<SyntaxNodeT>>::type* = 0
);

//overload for optional nodes
template<class SyntaxNodeT>
const std::string
get_value
(
	const SyntaxNodeT& node,
	typename boost::enable_if<syntax_nodes::util::is_optional_node<SyntaxNodeT>>::type* = 0
);

//overload for predefined_text nodes
template<class SyntaxNodeT>
const std::string
get_value
(
	const SyntaxNodeT& node,
	typename boost::enable_if<syntax_nodes::util::is_predefined_text_node<SyntaxNodeT>>::type* = 0
);

//overload for leaf nodes
template<class SyntaxNodeT>
const std::string
get_value
(
	const SyntaxNodeT& node,
	typename boost::enable_if<syntax_nodes::util::is_leaf_node<SyntaxNodeT>>::type* = 0
);

//overload for empty nodes (sequence and alternative tail nodes)
template<class SyntaxNodeT>
const std::string
get_value
(
	const SyntaxNodeT&,
	typename boost::enable_if<boost::is_same<typename SyntaxNodeT::head_node_t, void>>::type* = 0
);



//overload for sequence nodes
template<class SyntaxNodeT>
const std::string
get_value
(
	const SyntaxNodeT& node,
	typename boost::enable_if<syntax_nodes::util::is_sequence_node<SyntaxNodeT>>::type* = 0,
	typename boost::disable_if<boost::is_same<typename SyntaxNodeT::head_node_t, void>>::type* = 0
)
{
	return get_value(node.head()) + get_value(node.tail());
}

//overload for alternative nodes
template<class SyntaxNodeT>
const std::string
get_value
(
	const SyntaxNodeT& node,
	typename boost::enable_if<syntax_nodes::util::is_alternative_node<SyntaxNodeT>>::type* = 0,
	typename boost::disable_if<boost::is_same<typename SyntaxNodeT::head_node_t, void>>::type* = 0
)
{
	auto opt_node = get<typename SyntaxNodeT::head_node_t>(&node);
	if(opt_node)
	{
		return get_value(*opt_node);
	}
	else
	{
		return get_value(node.tail());
	}
}

//overload for list nodes
template<class SyntaxNodeT>
const std::string
get_value
(
	const SyntaxNodeT& node,
	typename boost::enable_if<syntax_nodes::util::is_list_node<SyntaxNodeT>>::type* = 0
)
{
	std::string value;
	bool first = true;
	for(auto i = node.begin(); i != node.end(); ++i) //for each node of the list
	{
		const typename SyntaxNodeT::item& item = *i;

		if(!first)
		{
			value += get_value(item.pre_separator_space_node());
			value += get_value(SyntaxNodeT::separator_node);
			value += get_value(item.post_separator_space_node());
		}
		value += get_value(item.main_node());
		first = false;
	}
	return value;
}

//overload for optional nodes
template<class SyntaxNodeT>
const std::string
get_value
(
	const SyntaxNodeT& node,
	typename boost::enable_if<syntax_nodes::util::is_optional_node<SyntaxNodeT>>::type* = 0
)
{
	if(node)
		return get_value(*node);
	else
		return "";
}

//overload for predefined_text nodes
template<class SyntaxNodeT>
const std::string
get_value
(
	const SyntaxNodeT& node,
	typename boost::enable_if<syntax_nodes::util::is_predefined_text_node<SyntaxNodeT>>::type* = 0
)
{
	return node.text();
}

//overload for leaf nodes
template<class SyntaxNodeT>
const std::string
get_value
(
	const SyntaxNodeT& node,
	typename boost::enable_if<syntax_nodes::util::is_leaf_node<SyntaxNodeT>>::type* = 0
)
{
	return node.value();
}

//overload for empty nodes (sequence and alternative tail nodes)
template<class SyntaxNodeT>
const std::string
get_value
(
	const SyntaxNodeT&,
	typename boost::enable_if<boost::is_same<typename SyntaxNodeT::head_node_t, void>>::type* = 0
)
{
	return "";
}

}}}} //namespace scalpel::cpp::syntax_nodes::util

#endif
