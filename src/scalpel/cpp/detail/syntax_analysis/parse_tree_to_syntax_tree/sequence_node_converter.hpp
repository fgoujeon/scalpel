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

#ifndef SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_PARSE_TREE_TO_SYNTAX_TREE_SEQUENCE_NODE_CONVERTER_HPP
#define SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_PARSE_TREE_TO_SYNTAX_TREE_SEQUENCE_NODE_CONVERTER_HPP

#include <string>
#include <iostream>
#include <scalpel/cpp/syntax_nodes/sequence_node.hpp>
#include "generic_node_converters.hpp"

namespace scalpel { namespace cpp { namespace detail { namespace syntax_analysis { namespace parse_tree_to_syntax_tree
{

template<class NodeT>
struct node_checker
{
	static
	bool
	check(const tree_node_t& node)
	{
		return check_id<NodeT>(node.value.id());
	}
};

template<const std::string& Text>
struct node_checker<syntax_nodes::simple_text_node<Text>>
{
	static
	bool
	check(const tree_node_t& node)
	{
		return get_value(node) == Text;
	}
};

template<class NodeT>
bool
check_node(const tree_node_t& node)
{
	return node_checker<NodeT>::check(node);
}



template<class... NodesT>
struct sequence_node_converter;

template<>
struct sequence_node_converter<>
{
	static
	syntax_nodes::sequence_node<>
	convert(const tree_node_t&, tree_node_iterator_t)
	{
		return syntax_nodes::sequence_node<>();
	}
};

template<class HeadNodeT, class... TailNodesT>
struct sequence_node_converter<HeadNodeT, TailNodesT...>
{
	static
	syntax_nodes::sequence_node<HeadNodeT, TailNodesT...>
	convert(const tree_node_t& node, tree_node_iterator_t it)
	{
		assert(it != node.children.end());

		HeadNodeT head_node = convert_node<HeadNodeT>(*it);

		if(it != node.children.end())
			++it;

		return syntax_nodes::sequence_node<HeadNodeT, TailNodesT...>
		(
			head_node,
			sequence_node_converter<TailNodesT...>::convert(node, it)
		);
	}
};

//specialization for optional nodes
template<class HeadNodeT, class... TailNodesT>
struct sequence_node_converter<syntax_nodes::optional_node<HeadNodeT>, TailNodesT...>
{
	static
	syntax_nodes::sequence_node<syntax_nodes::optional_node<HeadNodeT>, TailNodesT...>
	convert(const tree_node_t& node, tree_node_iterator_t it)
	{
		syntax_nodes::optional_node<HeadNodeT> head_node;
		if(it != node.children.end() && check_node<HeadNodeT>(*it))
		{
			head_node = convert_node<HeadNodeT>(*it);
			++it;
		}

		return syntax_nodes::sequence_node<syntax_nodes::optional_node<HeadNodeT>, TailNodesT...>
		(
			head_node,
			sequence_node_converter<TailNodesT...>::convert(node, it)
		);
	}
};




template<class SequenceNodeT>
struct aaa;

template<class... NodesT>
struct aaa<syntax_nodes::sequence_node<NodesT...>>
{
	static
	syntax_nodes::sequence_node<NodesT...>
	convert(const tree_node_t& node, tree_node_iterator_t it)
	{
		return sequence_node_converter<NodesT...>::convert(node, it);
	}
};

template<class SequenceNodeT>
struct aaa
{
	static
	SequenceNodeT
	convert(const tree_node_t& node, tree_node_iterator_t it)
	{
		return aaa<typename SequenceNodeT::type>::convert(node, it);
	}
};

template<class SequenceNodeT>
SequenceNodeT
convert_sequence_node(const tree_node_t& node)
{
	return aaa<SequenceNodeT>::convert(node, node.children.begin());
}

}}}}} //namespace scalpel::cpp::detail::syntax_analysis::parse_tree_to_syntax_tree

#endif
