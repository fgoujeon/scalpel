/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2010  Florian Goujeon

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

#include "node_converter.hpp"
#include "node_checker.hpp"
#include <scalpel/cpp/syntax_nodes/predefined_text_node.hpp>
#include <string>

namespace scalpel { namespace cpp { namespace detail { namespace syntax_analysis { namespace parse_tree_to_syntax_tree
{

/**
 * Converts a node of a sequence node
 */
template<class NodeT>
struct sequence_node_node_converter
{
	static
	NodeT
	convert(const tree_node_t& node, tree_node_iterator_t& it)
	{
		assert(it != node.children.end());

		NodeT syntax_node = convert_node<NodeT>(*it);

		if(it != node.children.end())
			++it;

		return syntax_node;
	}
};

//specialization for optional nodes
template<class NodeT>
struct sequence_node_node_converter<syntax_nodes::optional_node<NodeT>>
{
	static
	syntax_nodes::optional_node<NodeT>
	convert(const tree_node_t& node, tree_node_iterator_t& it)
	{
		syntax_nodes::optional_node<NodeT> syntax_node;
		if(it != node.children.end() && check_node<NodeT>(*it))
		{
			syntax_node = convert_node<NodeT>(*it);
			++it;
		}

		return syntax_node;
	}
};



/**
 * Converts a parse tree node to a syntax sequence node.
 */
//The only purpose of HeadNodeT is to allow the writing of a specialization
//for the ending tail sequence which isn't tied to any particular
//implementation of the SequenceNode Concept.
template<class SequenceNodeT, typename HeadNodeT>
struct sequence_node_converter
{
	typedef typename SequenceNodeT::head_node_t head_node_t;
	typedef typename SequenceNodeT::tail_sequence_node_t tail_sequence_node_t;

	static
	SequenceNodeT
	convert(const tree_node_t& node, tree_node_iterator_t it)
	{
		head_node_t syntax_node = sequence_node_node_converter<head_node_t>::convert(node, it);
		return SequenceNodeT
		(
			syntax_node,
			sequence_node_converter<tail_sequence_node_t, typename tail_sequence_node_t::head_node_t>::convert(node, it)
		);
	}
};

//specialization for the ending tail sequence
template<class SequenceNodeT>
struct sequence_node_converter<SequenceNodeT, void>
{
	static
	SequenceNodeT
	convert(const tree_node_t&, tree_node_iterator_t)
	{
		return SequenceNodeT();
	}
};



template<class SequenceNodeT>
SequenceNodeT
convert_sequence_node(const tree_node_t& node)
{
	return sequence_node_converter<SequenceNodeT, typename SequenceNodeT::head_node_t>::convert(node, node.children.begin());
}

}}}}} //namespace scalpel::cpp::detail::syntax_analysis::parse_tree_to_syntax_tree

#endif
