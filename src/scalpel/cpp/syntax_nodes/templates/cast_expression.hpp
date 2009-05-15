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

#ifndef SCALPEL_CPP_SYNTAX_NODES_TEMPLATES_CAST_EXPRESSION_HPP
#define SCALPEL_CPP_SYNTAX_NODES_TEMPLATES_CAST_EXPRESSION_HPP

#include <boost/optional.hpp>
#include "../composite_node.hpp"
#include "../bracketed_node.hpp"
#include "../type_id.hpp"
#include "../expression.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes { namespace templates
{

/**
XXX_cast_expression
	= "XXX" >> !s >> '<' >> !s >> type_id >> !s >> '>' >> !s >> '(' >> !s >> expression >> !s >> ')'
;
*/
template<const leaf_node& CastKeywordNode>
class cast_expression: public composite_node
{
	public:
		cast_expression
		(
			boost::optional<space>&& post_cast_keyword_space_node,
			angle_bracketed_node<type_id>::type&& bracketed_type_id_node,
			boost::optional<space>&& post_right_angle_bracket_space_node,
			round_bracketed_node<expression>::type&& bracketed_expression_node
		);

		cast_expression(const cast_expression& o);

		cast_expression(cast_expression&& o);

		const cast_expression&
		operator=(const cast_expression& o);

	private:
		void
		update_node_list();

		boost::optional<space> post_cast_keyword_space_;
		angle_bracketed_node<type_id>::type bracketed_type_id_;
		boost::optional<space> post_right_angle_bracket_space_;
		round_bracketed_node<expression>::type bracketed_expression_;
};

}}}} //namespace scalpel::cpp::syntax_nodes::templates

#include "cast_expression.ipp"

#endif
