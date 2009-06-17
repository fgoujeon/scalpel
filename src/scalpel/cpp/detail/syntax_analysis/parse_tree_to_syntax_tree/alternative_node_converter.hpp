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

#ifndef SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_PARSE_TREE_TO_SYNTAX_TREE_ALTERNATIVE_NODE_CONVERTER_HPP
#define SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_PARSE_TREE_TO_SYNTAX_TREE_ALTERNATIVE_NODE_CONVERTER_HPP

#include <string>
#include <stdexcept>
#include <scalpel/cpp/syntax_nodes/simple_text_node.hpp>
#include "node_converter.hpp"
#include "node_checker.hpp"
#include "basic_functions.hpp"

namespace scalpel { namespace cpp { namespace detail { namespace syntax_analysis { namespace parse_tree_to_syntax_tree
{

/**
 * Converts a parse tree node to a syntax alternative node.
 */
//The only purpose of HeadNodeT is to allow the writing of a specialization
//for the ending tail alternative which isn't tied to any particular
//implementation of the AlternativeNode Concept.
template<class T, class AlternativeNodeT, typename HeadNodeT>
struct alternative_node_converter
{
	typedef typename AlternativeNodeT::head_node_t head_node_t;
	typedef typename AlternativeNodeT::tail_alternative_node_t tail_alternative_node_t;

	static
	T
	convert(const tree_node_t& node)
	{
		if(check_node<head_node_t>(node))
			return convert_node<head_node_t>(node);
		else
			return alternative_node_converter<T, tail_alternative_node_t, typename tail_alternative_node_t::head_node_t>::convert(node);
	}
};

//specialization for the ending tail alternative
template<class T, class AlternativeNodeT>
struct alternative_node_converter<T, AlternativeNodeT, void>
{
	static
	T
	convert(const tree_node_t& node)
	{
		std::ostringstream error_message;
		error_message << "alternative_node_converter error : unexpected parser id = ";
	   	error_message << get_id(node);
		throw std::runtime_error(error_message.str());
	}
};



template<class AlternativeNodeT>
AlternativeNodeT
convert_alternative_node(const tree_node_t& node)
{
	assert(node.children.size() == 1);
	return alternative_node_converter<AlternativeNodeT, AlternativeNodeT, typename AlternativeNodeT::head_node_t>::convert(node.children.front());
}

}}}}} //namespace scalpel::cpp::detail::syntax_analysis::parse_tree_to_syntax_tree

#endif
