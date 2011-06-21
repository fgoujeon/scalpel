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

#ifndef SCALPEL_CPP_SEMANTIC_ANALYSIS_DETAIL_EXPRESSION_CONSTRUCTION_IPP
#define SCALPEL_CPP_SEMANTIC_ANALYSIS_DETAIL_EXPRESSION_CONSTRUCTION_IPP

namespace scalpel { namespace cpp { namespace semantic_analysis { namespace detail
{

template<class DeclarativeRegion>
semantic_entities::expression_t
create_expression
(
	const syntax_nodes::assignment_expression& assignment_expression_node,
	DeclarativeRegion& declarative_region
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	if(/*const optional_node<assignment_expression_first_part_seq>& first_part_seq_node =*/ get_first_part_seq(assignment_expression_node))
	{
		assert(false); //TODO
	}

	const assignment_expression_last_part& last_part_node = get_last_part(assignment_expression_node);
	if(const boost::optional<const conditional_expression&>& opt_conditional_expression_node = get<conditional_expression>(&last_part_node))
	{
		return create_expression(*opt_conditional_expression_node, declarative_region);
	}
	else if(/*const boost::optional<const throw_expression&>& opt_throw_expression_node =*/ get<throw_expression>(&last_part_node))
	{
		assert(false); //TODO
	}
	else
	{
		assert(false);
	}
}

template<class DeclarativeRegion>
semantic_entities::expression_t
create_expression
(
	const syntax_nodes::conditional_expression& conditional_expression_node,
	DeclarativeRegion& declarative_region
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	const logical_or_expression& logical_or_expression_node = get_logical_or_expression(conditional_expression_node);
	return create_expression(logical_or_expression_node, declarative_region);
}

template<class DeclarativeRegion>
semantic_entities::expression_t
create_expression
(
	const syntax_nodes::logical_or_expression& logical_or_expression_node,
	DeclarativeRegion& declarative_region
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	return create_expression(get_left_operand(logical_or_expression_node), declarative_region);
}

template<class DeclarativeRegion>
semantic_entities::expression_t
create_expression
(
	const syntax_nodes::logical_and_expression& logical_and_expression_node,
	DeclarativeRegion& declarative_region
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	return create_expression(get_left_operand(logical_and_expression_node), declarative_region);
}

template<class DeclarativeRegion>
semantic_entities::expression_t
create_expression
(
	const syntax_nodes::inclusive_or_expression& inclusive_or_expression_node,
	DeclarativeRegion& declarative_region
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	return create_expression(get_left_operand(inclusive_or_expression_node), declarative_region);
}

template<class DeclarativeRegion>
semantic_entities::expression_t
create_expression
(
	const syntax_nodes::exclusive_or_expression& exclusive_or_expression_node,
	DeclarativeRegion& declarative_region
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	return create_expression(get_left_operand(exclusive_or_expression_node), declarative_region);
}

template<class DeclarativeRegion>
semantic_entities::expression_t
create_expression
(
	const syntax_nodes::and_expression& and_expression_node,
	DeclarativeRegion& declarative_region
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	return create_expression(get_left_operand(and_expression_node), declarative_region);
}

template<class DeclarativeRegion>
semantic_entities::expression_t
create_expression
(
	const syntax_nodes::equality_expression& equality_expression_node,
	DeclarativeRegion& declarative_region
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	return create_expression(get_left_operand(equality_expression_node), declarative_region);
}

template<class DeclarativeRegion>
semantic_entities::expression_t
create_expression
(
	const syntax_nodes::relational_expression& relational_expression_node,
	DeclarativeRegion& declarative_region
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	return create_expression(get_left_operand(relational_expression_node), declarative_region);
}

template<class DeclarativeRegion>
semantic_entities::expression_t
create_expression
(
	const syntax_nodes::shift_expression& shift_expression_node,
	DeclarativeRegion& declarative_region
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	return create_expression(get_left_operand(shift_expression_node), declarative_region);
}

template<class DeclarativeRegion>
semantic_entities::expression_t
create_expression
(
	const syntax_nodes::additive_expression& additive_expression_node,
	DeclarativeRegion& declarative_region
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	const multiplicative_expression& left_operand_node = get_left_operand(additive_expression_node);
	const optional_node<additive_operator>& opt_operator_node = get_operator(additive_expression_node);
	const optional_node<additive_expression>& opt_right_operand_node = get_right_operand(additive_expression_node);

	if(opt_right_operand_node)
	{
		const additive_operator& operator_node = *opt_operator_node;
		const additive_expression& right_operand_node = *opt_right_operand_node;

		if(get<predefined_text_node<str::plus>>(&operator_node))
			return addition
			(
				create_expression(left_operand_node, declarative_region),
				create_expression(right_operand_node, declarative_region)
			);
		else if(get<predefined_text_node<str::minus>>(&operator_node))
			return subtraction
			(
				create_expression(left_operand_node, declarative_region),
				create_expression(right_operand_node, declarative_region)
			);
		else
			assert(false);
	}
	else
		return create_expression(left_operand_node, declarative_region);
}

template<class DeclarativeRegion>
semantic_entities::expression_t
create_expression
(
	const syntax_nodes::multiplicative_expression& multiplicative_expression_node,
	DeclarativeRegion& declarative_region
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	const pm_expression& left_operand_node = get_left_operand(multiplicative_expression_node);
	const optional_node<multiplicative_operator>& opt_operator_node = get_operator(multiplicative_expression_node);
	const optional_node<multiplicative_expression>& opt_right_operand_node = get_right_operand(multiplicative_expression_node);

	if(opt_right_operand_node)
	{
		const multiplicative_operator& operator_node = *opt_operator_node;
		const multiplicative_expression& right_operand_node = *opt_right_operand_node;

		if(get<predefined_text_node<str::asterisk>>(&operator_node))
			return multiplication
			(
				create_expression(left_operand_node, declarative_region),
				create_expression(right_operand_node, declarative_region)
			);
		else if(get<predefined_text_node<str::slash>>(&operator_node))
			return division
			(
				create_expression(left_operand_node, declarative_region),
				create_expression(right_operand_node, declarative_region)
			);
		else if(get<predefined_text_node<str::percent>>(&operator_node))
			return modulo
			(
				create_expression(left_operand_node, declarative_region),
				create_expression(right_operand_node, declarative_region)
			);
		else
			assert(false);
	}
	else
		return create_expression(left_operand_node, declarative_region);
}

template<class DeclarativeRegion>
semantic_entities::expression_t
create_expression
(
	const syntax_nodes::pm_expression& pm_expression_node,
	DeclarativeRegion& declarative_region
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	return create_expression(get_left_operand(pm_expression_node), declarative_region);
}

template<class DeclarativeRegion>
semantic_entities::expression_t
create_expression
(
	const syntax_nodes::cast_expression& cast_expression_node,
	DeclarativeRegion& declarative_region
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	return create_expression(get_operand(cast_expression_node), declarative_region);
}

template<class DeclarativeRegion>
semantic_entities::expression_t
create_expression
(
	const syntax_nodes::unary_expression& unary_expression_node,
	DeclarativeRegion& declarative_region
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	if(const boost::optional<const postfix_expression&>& opt_postfix_expression_node = get<postfix_expression>(&unary_expression_node))
	{
		return create_expression(*opt_postfix_expression_node, declarative_region);
	}
	else
	{
		assert(false); //TODO
	}
}

template<class DeclarativeRegion>
semantic_entities::expression_t
create_expression
(
	const syntax_nodes::postfix_expression& postfix_expression_node,
	DeclarativeRegion& declarative_region
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	const postfix_expression_first_part& first_part_node = get_first_part(postfix_expression_node);

	if(const boost::optional<const primary_expression&>& opt_primary_expression_node = get<primary_expression>(&first_part_node))
	{
		return create_expression(*opt_primary_expression_node, declarative_region);
	}
	else
	{
		assert(false); //TODO
	}
}

template<class DeclarativeRegion>
semantic_entities::expression_t
create_expression
(
	const syntax_nodes::primary_expression& primary_expression_node,
	DeclarativeRegion& /*declarative_region*/
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	if(const boost::optional<const literal&>& opt_literal_node = get<literal>(&primary_expression_node))
	{
		return create_expression(*opt_literal_node);
	}
	else
	{
		assert(false); //TODO
	}
}

}}}} //namespace scalpel::cpp::semantic_analysis::detail

#endif

