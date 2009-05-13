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

#ifndef SCALPEL_CPP_SYNTAX_NODES_TEMPLATES_CAST_EXPRESSION_IPP
#define SCALPEL_CPP_SYNTAX_NODES_TEMPLATES_CAST_EXPRESSION_IPP

#include "cast_expression.hpp"

#include "../common_nodes.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes { namespace templates
{

template<const leaf_node& CastKeywordNode>
cast_expression<CastKeywordNode>::cast_expression
(
	boost::optional<space>&& post_cast_keyword_space_node,
	boost::optional<space>&& post_left_angle_bracket_space_node,
	type_id&& type_id_node,
	boost::optional<space>&& post_type_id_space_node,
	boost::optional<space>&& post_right_angle_bracket_space_node,
	boost::optional<space>&& post_opening_round_bracket_space_node,
	expression&& expression_node,
	boost::optional<space>&& post_expression_space_node
):
	post_cast_keyword_space_(post_cast_keyword_space_node),
	post_left_angle_bracket_space_(post_left_angle_bracket_space_node),
	type_id_(type_id_node),
	post_type_id_space_(post_type_id_space_node),
	post_right_angle_bracket_space_(post_right_angle_bracket_space_node),
	post_opening_round_bracket_space_(post_opening_round_bracket_space_node),
	//expression_(expression_node),
	post_expression_space_(post_expression_space_node)
{
	update_node_list();
}

template<const leaf_node& CastKeywordNode>
cast_expression<CastKeywordNode>::cast_expression(const cast_expression& o):
	composite_node(),
	post_cast_keyword_space_(o.post_cast_keyword_space_),
	post_left_angle_bracket_space_(o.post_left_angle_bracket_space_),
	type_id_(o.type_id_),
	post_type_id_space_(o.post_type_id_space_),
	post_right_angle_bracket_space_(o.post_right_angle_bracket_space_),
	post_opening_round_bracket_space_(o.post_opening_round_bracket_space_),
	//expression_(o.expression_),
	post_expression_space_(o.post_expression_space_)
{
	update_node_list();
}

template<const leaf_node& CastKeywordNode>
cast_expression<CastKeywordNode>::cast_expression(cast_expression&& o):
	composite_node(),
	post_cast_keyword_space_(std::move(o.post_cast_keyword_space_)),
	post_left_angle_bracket_space_(std::move(o.post_left_angle_bracket_space_)),
	type_id_(std::move(o.type_id_)),
	post_type_id_space_(std::move(o.post_type_id_space_)),
	post_right_angle_bracket_space_(std::move(o.post_right_angle_bracket_space_)),
	post_opening_round_bracket_space_(std::move(o.post_opening_round_bracket_space_)),
	//expression_(std::move(o.expression_)),
	post_expression_space_(std::move(o.post_expression_space_))
{
	update_node_list();
}

template<const leaf_node& CastKeywordNode>
const cast_expression<CastKeywordNode>&
cast_expression<CastKeywordNode>::operator=(const cast_expression<CastKeywordNode>& o)
{
	cast_expression<CastKeywordNode> copy(o);
	//std::move(copy, *this);
	return *this;
}

template<const leaf_node& CastKeywordNode>
void
cast_expression<CastKeywordNode>::update_node_list()
{
	clear();
	add(CastKeywordNode);
	if(post_cast_keyword_space_) add(*post_cast_keyword_space_);
	add(global_nodes::left_angle_bracket);
	if(post_left_angle_bracket_space_) add(*post_left_angle_bracket_space_);
	add(type_id_);
	if(post_type_id_space_) add(*post_type_id_space_);
	add(global_nodes::right_angle_bracket);
	if(post_right_angle_bracket_space_) add(*post_right_angle_bracket_space_);
	add(global_nodes::opening_bracket);
	if(post_opening_round_bracket_space_) add(*post_opening_round_bracket_space_);
	//add(expression_);
	if(post_expression_space_) add(*post_expression_space_);
	add(global_nodes::closing_bracket);
}

}}}} //namespace scalpel::cpp::syntax_nodes::templates

#endif

