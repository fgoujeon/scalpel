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

#include "name_lookup.hpp"
#include "semantic_entity_analysis/identification_policies.hpp"

namespace scalpel { namespace cpp { namespace semantic_analysis { namespace detail
{

template<class DeclarativeRegion>
semantic_entities::expression_t
create_expression
(
	const syntax_nodes::expression& expression_node,
	DeclarativeRegion& declarative_region
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	return create_expression_from_assignment_expression(expression_node.front(), declarative_region);
}

template<class DeclarativeRegion>
semantic_entities::expression_t
create_expression_from_assignment_expression
(
	const syntax_nodes::assignment_expression& assignment_expression_node,
	DeclarativeRegion& declarative_region
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	if(const boost::optional<const assignment_assignment_expression&>& opt_assignment_assignment_expression_node = get<assignment_assignment_expression>(&assignment_expression_node))
	{
		const assignment_assignment_expression& assignment_assignment_expression_node = *opt_assignment_assignment_expression_node;
		return create_expression_from_assignment_assignment_expression(assignment_assignment_expression_node, declarative_region);
	}
	else if(const boost::optional<const syntax_nodes::conditional_expression&>& opt_conditional_expression_node = get<syntax_nodes::conditional_expression>(&assignment_expression_node))
	{
		const syntax_nodes::conditional_expression& conditional_expression_node = *opt_conditional_expression_node;
		return create_expression_from_conditional_expression(conditional_expression_node, declarative_region);
	}
	else if(/*const boost::optional<const syntax_nodes::throw_expression&>& opt_throw_expression_node =*/ get<syntax_nodes::throw_expression>(&assignment_expression_node))
	{
		//const throw_expression& throw_expression_node = *opt_throw_expression_node;
		assert(false); //TODO
	}
	else
	{
		assert(false);
	}
}

template<class DeclarativeRegion>
semantic_entities::expression_t
create_expression_from_assignment_assignment_expression
(
	const syntax_nodes::assignment_assignment_expression& assignment_assignment_expression_node,
	DeclarativeRegion& declarative_region
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	const syntax_nodes::logical_or_expression& left_operand_node = get_left_operand(assignment_assignment_expression_node);
	const syntax_nodes::assignment_expression& right_operand_node = get_right_operand(assignment_assignment_expression_node);

	const semantic_entities::expression_t left_operand = create_expression_from_logical_or_expression(left_operand_node, declarative_region);
	const semantic_entities::expression_t right_operand = create_expression_from_assignment_expression(right_operand_node, declarative_region);
	const assignment_operator& operator_node = get_operator(assignment_assignment_expression_node);

	if(get<predefined_text_node<str::equal>>(&operator_node))
		return semantic_entities::assignment_expression
		(
			left_operand,
			right_operand
		);
	else if(get<predefined_text_node<str::asterisk_equal>>(&operator_node))
		return semantic_entities::multiplication_assignment_expression
		(
			left_operand,
			right_operand
		);
	else if(get<predefined_text_node<str::slash_equal>>(&operator_node))
		return semantic_entities::division_assignment_expression
		(
			left_operand,
			right_operand
		);
	else if(get<predefined_text_node<str::percent_equal>>(&operator_node))
		return semantic_entities::modulo_assignment_expression
		(
			left_operand,
			right_operand
		);
	else if(get<predefined_text_node<str::plus_equal>>(&operator_node))
		return semantic_entities::addition_assignment_expression
		(
			left_operand,
			right_operand
		);
	else if(get<predefined_text_node<str::minus_equal>>(&operator_node))
		return semantic_entities::subtraction_assignment_expression
		(
			left_operand,
			right_operand
		);
	else if(get<predefined_text_node<str::double_right_angle_bracket_equal>>(&operator_node))
		return semantic_entities::right_shift_assignment_expression
		(
			left_operand,
			right_operand
		);
	else if(get<predefined_text_node<str::double_left_angle_bracket_equal>>(&operator_node))
		return semantic_entities::left_shift_assignment_expression
		(
			left_operand,
			right_operand
		);
	else if(get<predefined_text_node<str::ampersand_equal>>(&operator_node))
		return semantic_entities::bitwise_and_assignment_expression
		(
			left_operand,
			right_operand
		);
	else if(get<predefined_text_node<str::circumflex_equal>>(&operator_node))
		return semantic_entities::bitwise_exclusive_or_assignment_expression
		(
			left_operand,
			right_operand
		);
	else if(get<predefined_text_node<str::pipe_equal>>(&operator_node))
		return semantic_entities::bitwise_inclusive_or_assignment_expression
		(
			left_operand,
			right_operand
		);
	else
		assert(false);
}

template<class DeclarativeRegion>
semantic_entities::expression_t
create_expression_from_conditional_expression
(
	const syntax_nodes::conditional_expression& conditional_expression_node,
	DeclarativeRegion& declarative_region
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	const syntax_nodes::logical_or_expression& condition_operand_node = get_condition_operand(conditional_expression_node);
	const optional_node<syntax_nodes::expression>& opt_true_operand_node = get_true_operand(conditional_expression_node);
	const optional_node<syntax_nodes::assignment_expression>& opt_false_operand_node = get_false_operand(conditional_expression_node);

	if(opt_true_operand_node)
	{
		assert(opt_false_operand_node);
		return semantic_entities::conditional_expression
		(
			create_expression_from_logical_or_expression(condition_operand_node, declarative_region),
			create_expression(*opt_true_operand_node, declarative_region),
			create_expression_from_assignment_expression(*opt_false_operand_node, declarative_region)
		);
	}
	else
		return create_expression_from_logical_or_expression(condition_operand_node, declarative_region);
}

template<class DeclarativeRegion>
semantic_entities::expression_t
create_expression_from_logical_or_expression
(
	const syntax_nodes::logical_or_expression& logical_or_expression_node,
	DeclarativeRegion& declarative_region
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	const syntax_nodes::logical_and_expression& left_operand_node = get_left_operand(logical_or_expression_node);
	const optional_node<syntax_nodes::logical_or_expression>& opt_right_operand_node = get_right_operand(logical_or_expression_node);

	if(opt_right_operand_node)
	{
		const syntax_nodes::logical_or_expression& right_operand_node = *opt_right_operand_node;
		return semantic_entities::logical_or_expression
		(
			create_expression_from_logical_and_expression(left_operand_node, declarative_region),
			create_expression_from_logical_or_expression(right_operand_node, declarative_region)
		);
	}
	else
		return create_expression_from_logical_and_expression(left_operand_node, declarative_region);
}

template<class DeclarativeRegion>
semantic_entities::expression_t
create_expression_from_logical_and_expression
(
	const syntax_nodes::logical_and_expression& logical_and_expression_node,
	DeclarativeRegion& declarative_region
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	const syntax_nodes::inclusive_or_expression& left_operand_node = get_left_operand(logical_and_expression_node);
	const optional_node<syntax_nodes::logical_and_expression>& opt_right_operand_node = get_right_operand(logical_and_expression_node);

	if(opt_right_operand_node)
	{
		const syntax_nodes::logical_and_expression& right_operand_node = *opt_right_operand_node;
		return semantic_entities::logical_and_expression
		(
			create_expression_from_inclusive_or_expression(left_operand_node, declarative_region),
			create_expression_from_logical_and_expression(right_operand_node, declarative_region)
		);
	}
	else
		return create_expression_from_inclusive_or_expression(left_operand_node, declarative_region);
}

template<class DeclarativeRegion>
semantic_entities::expression_t
create_expression_from_inclusive_or_expression
(
	const syntax_nodes::inclusive_or_expression& inclusive_or_expression_node,
	DeclarativeRegion& declarative_region
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	const syntax_nodes::exclusive_or_expression& left_operand_node = get_left_operand(inclusive_or_expression_node);
	const optional_node<syntax_nodes::inclusive_or_expression>& opt_right_operand_node = get_right_operand(inclusive_or_expression_node);

	if(opt_right_operand_node)
	{
		const syntax_nodes::inclusive_or_expression& right_operand_node = *opt_right_operand_node;
		return semantic_entities::bitwise_inclusive_or_expression
		(
			create_expression_from_exclusive_or_expression(left_operand_node, declarative_region),
			create_expression_from_inclusive_or_expression(right_operand_node, declarative_region)
		);
	}
	else
		return create_expression_from_exclusive_or_expression(left_operand_node, declarative_region);
}

template<class DeclarativeRegion>
semantic_entities::expression_t
create_expression_from_exclusive_or_expression
(
	const syntax_nodes::exclusive_or_expression& exclusive_or_expression_node,
	DeclarativeRegion& declarative_region
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	const syntax_nodes::and_expression& left_operand_node = get_left_operand(exclusive_or_expression_node);
	const optional_node<syntax_nodes::exclusive_or_expression>& opt_right_operand_node = get_right_operand(exclusive_or_expression_node);

	if(opt_right_operand_node)
	{
		const syntax_nodes::exclusive_or_expression& right_operand_node = *opt_right_operand_node;
		return semantic_entities::bitwise_exclusive_or_expression
		(
			create_expression_from_and_expression(left_operand_node, declarative_region),
			create_expression_from_exclusive_or_expression(right_operand_node, declarative_region)
		);
	}
	else
		return create_expression_from_and_expression(left_operand_node, declarative_region);
}

template<class DeclarativeRegion>
semantic_entities::expression_t
create_expression_from_and_expression
(
	const syntax_nodes::and_expression& and_expression_node,
	DeclarativeRegion& declarative_region
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	const syntax_nodes::equality_expression& left_operand_node = get_left_operand(and_expression_node);
	const optional_node<syntax_nodes::and_expression>& opt_right_operand_node = get_right_operand(and_expression_node);

	if(opt_right_operand_node)
	{
		const syntax_nodes::and_expression& right_operand_node = *opt_right_operand_node;
		return semantic_entities::bitwise_and_expression
		(
			create_expression_from_equality_expression(left_operand_node, declarative_region),
			create_expression_from_and_expression(right_operand_node, declarative_region)
		);
	}
	else
		return create_expression_from_equality_expression(left_operand_node, declarative_region);
}

template<class DeclarativeRegion>
semantic_entities::expression_t
create_expression_from_equality_expression
(
	const syntax_nodes::equality_expression& equality_expression_node,
	DeclarativeRegion& declarative_region
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	const syntax_nodes::relational_expression& left_operand_node = get_left_operand(equality_expression_node);
	const optional_node<syntax_nodes::equality_operator>& opt_operator_node = get_operator(equality_expression_node);
	const optional_node<syntax_nodes::equality_expression>& opt_right_operand_node = get_right_operand(equality_expression_node);

	if(opt_right_operand_node)
	{
		const syntax_nodes::equality_operator& operator_node = *opt_operator_node;
		const syntax_nodes::equality_expression& right_operand_node = *opt_right_operand_node;

		if(get<predefined_text_node<str::double_equal>>(&operator_node))
			return semantic_entities::equal_to_expression
			(
				create_expression_from_relational_expression(left_operand_node, declarative_region),
				create_expression_from_equality_expression(right_operand_node, declarative_region)
			);
		else if(get<predefined_text_node<str::exclamation_equal>>(&operator_node))
			return semantic_entities::not_equal_to_expression
			(
				create_expression_from_relational_expression(left_operand_node, declarative_region),
				create_expression_from_equality_expression(right_operand_node, declarative_region)
			);
		else
			assert(false);
	}
	else
		return create_expression_from_relational_expression(left_operand_node, declarative_region);
}

template<class DeclarativeRegion>
semantic_entities::expression_t
create_expression_from_relational_expression
(
	const syntax_nodes::relational_expression& relational_expression_node,
	DeclarativeRegion& declarative_region
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	const syntax_nodes::shift_expression& left_operand_node = get_left_operand(relational_expression_node);
	const optional_node<syntax_nodes::relational_operator>& opt_operator_node = get_operator(relational_expression_node);
	const optional_node<syntax_nodes::relational_expression>& opt_right_operand_node = get_right_operand(relational_expression_node);

	const semantic_entities::expression_t left_operand = create_expression_from_shift_expression(left_operand_node, declarative_region);

	if(opt_right_operand_node)
	{
		const syntax_nodes::relational_operator& operator_node = *opt_operator_node;
		const syntax_nodes::relational_expression& right_operand_node = *opt_right_operand_node;

		const semantic_entities::expression_t right_operand = create_expression_from_relational_expression(right_operand_node, declarative_region);

		if(get<predefined_text_node<str::left_angle_bracket>>(&operator_node))
			return semantic_entities::less_than_expression
			(
				left_operand,
				right_operand
			);
		else if(get<predefined_text_node<str::left_angle_bracket_equal>>(&operator_node))
			return semantic_entities::less_than_or_equal_to_expression
			(
				left_operand,
				right_operand
			);
		else if(get<predefined_text_node<str::right_angle_bracket>>(&operator_node))
			return semantic_entities::greater_than_expression
			(
				left_operand,
				right_operand
			);
		else if(get<predefined_text_node<str::right_angle_bracket_equal>>(&operator_node))
			return semantic_entities::greater_than_or_equal_to_expression
			(
				left_operand,
				right_operand
			);
		else
			assert(false);
	}
	else
		return left_operand;
}

template<class DeclarativeRegion>
semantic_entities::expression_t
create_expression_from_shift_expression
(
	const syntax_nodes::shift_expression& shift_expression_node,
	DeclarativeRegion& declarative_region
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	const syntax_nodes::additive_expression& left_operand_node = get_left_operand(shift_expression_node);
	const optional_node<syntax_nodes::shift_operator>& opt_operator_node = get_operator(shift_expression_node);
	const optional_node<syntax_nodes::shift_expression>& opt_right_operand_node = get_right_operand(shift_expression_node);

	const semantic_entities::expression_t left_operand = create_expression_from_additive_expression(left_operand_node, declarative_region);

	if(opt_right_operand_node)
	{
		const syntax_nodes::shift_operator& operator_node = *opt_operator_node;
		const syntax_nodes::shift_expression& right_operand_node = *opt_right_operand_node;

		const semantic_entities::expression_t right_operand = create_expression_from_shift_expression(right_operand_node, declarative_region);

		if(get<predefined_text_node<str::double_left_angle_bracket>>(&operator_node))
			return semantic_entities::left_shift_expression
			(
				left_operand,
				right_operand
			);
		else if(get<predefined_text_node<str::double_right_angle_bracket>>(&operator_node))
			return semantic_entities::right_shift_expression
			(
				left_operand,
				right_operand
			);
		else
			assert(false);
	}
	else
		return left_operand;
}

template<class DeclarativeRegion>
semantic_entities::expression_t
create_expression_from_additive_expression
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

	const semantic_entities::expression_t left_operand = create_expression_from_multiplicative_expression(left_operand_node, declarative_region);

	if(opt_right_operand_node)
	{
		const additive_operator& operator_node = *opt_operator_node;
		const additive_expression& right_operand_node = *opt_right_operand_node;

		const semantic_entities::expression_t right_operand = create_expression_from_additive_expression(right_operand_node, declarative_region);

		if(get<predefined_text_node<str::plus>>(&operator_node))
			return create_addition_expression
			(
				left_operand,
				right_operand
			);
		else if(get<predefined_text_node<str::minus>>(&operator_node))
			return semantic_entities::subtraction_expression
			(
				left_operand,
				right_operand
			);
		else
			assert(false);
	}
	else
		return left_operand;
}

template<class DeclarativeRegion>
semantic_entities::expression_t
create_expression_from_multiplicative_expression
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

	const semantic_entities::expression_t left_operand = create_expression_from_pm_expression(left_operand_node, declarative_region);

	if(opt_right_operand_node)
	{
		const multiplicative_operator& operator_node = *opt_operator_node;
		const multiplicative_expression& right_operand_node = *opt_right_operand_node;

		const semantic_entities::expression_t right_operand = create_expression_from_multiplicative_expression(right_operand_node, declarative_region);

		if(get<predefined_text_node<str::asterisk>>(&operator_node))
			return semantic_entities::multiplication_expression
			(
				left_operand,
				right_operand
			);
		else if(get<predefined_text_node<str::slash>>(&operator_node))
			return semantic_entities::division_expression
			(
				left_operand,
				right_operand
			);
		else if(get<predefined_text_node<str::percent>>(&operator_node))
			return semantic_entities::modulo_expression
			(
				left_operand,
				right_operand
			);
		else
			assert(false);
	}
	else
		return left_operand;
}

template<class DeclarativeRegion>
semantic_entities::expression_t
create_expression_from_pm_expression
(
	const syntax_nodes::pm_expression& pm_expression_node,
	DeclarativeRegion& declarative_region
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	return create_expression_from_cast_expression(get_left_operand(pm_expression_node), declarative_region);
}

template<class DeclarativeRegion>
semantic_entities::expression_t
create_expression_from_cast_expression
(
	const syntax_nodes::cast_expression& cast_expression_node,
	DeclarativeRegion& declarative_region
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	return create_expression_from_unary_expression(get_operand(cast_expression_node), declarative_region);
}

template<class DeclarativeRegion>
semantic_entities::expression_t
create_expression_from_unary_expression
(
	const syntax_nodes::unary_expression& unary_expression_node,
	DeclarativeRegion& declarative_region
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	if(const boost::optional<const unary_operator_expression&>& opt_unary_operator_expression_node = get<unary_operator_expression>(&unary_expression_node))
		return create_expression_from_unary_operator_expression(*opt_unary_operator_expression_node, declarative_region);
	else if(const boost::optional<const type_id_sizeof_expression&>& opt_type_sizeof_expression_node = get<type_id_sizeof_expression>(&unary_expression_node))
		return create_expression_from_type_sizeof_expression(*opt_type_sizeof_expression_node, declarative_region);
	else if(const boost::optional<const unary_sizeof_expression&>& opt_expression_sizeof_expression_node = get<unary_sizeof_expression>(&unary_expression_node))
		return create_expression_from_expression_sizeof_expression(*opt_expression_sizeof_expression_node, declarative_region);
	else if(const boost::optional<const postfix_expression&>& opt_postfix_expression_node = get<postfix_expression>(&unary_expression_node))
		return create_expression_from_postfix_expression(*opt_postfix_expression_node, declarative_region);
	else if(/*const boost::optional<const new_expression&>& opt_new_expression_node = */get<new_expression>(&unary_expression_node))
		assert(false); //TODO
	else if(/*const boost::optional<const delete_expression&>& opt_delete_expression_node = */get<delete_expression>(&unary_expression_node))
		assert(false); //TODO
	else
		assert(false);
}

template<class DeclarativeRegion>
semantic_entities::expression_t
create_expression_from_unary_operator_expression
(
	const syntax_nodes::unary_operator_expression& unary_operator_expression_node,
	DeclarativeRegion& declarative_region
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	const unary_operator& operator_node = get_operator(unary_operator_expression_node);
	const cast_expression& operand_node = get_operand(unary_operator_expression_node);
	const semantic_entities::expression_t operand = create_expression_from_cast_expression(operand_node, declarative_region);

	if(get<predefined_text_node<str::double_plus>>(&operator_node))
		return semantic_entities::prefix_increment_expression
		(
			operand
		);
	else if(get<predefined_text_node<str::double_minus>>(&operator_node))
		return semantic_entities::prefix_decrement_expression
		(
			operand
		);
	else if(get<predefined_text_node<str::asterisk>>(&operator_node))
		return semantic_entities::indirection_expression
		(
			operand
		);
	else if(get<predefined_text_node<str::ampersand>>(&operator_node))
		return semantic_entities::pointer_expression
		(
			operand
		);
	else if(get<predefined_text_node<str::plus>>(&operator_node))
		return operand;
	else if(get<predefined_text_node<str::minus>>(&operator_node))
		return semantic_entities::negation_expression
		(
			operand
		);
	else if(get<predefined_text_node<str::exclamation>>(&operator_node))
		return semantic_entities::logical_negation_expression
		(
			operand
		);
	else if(get<predefined_text_node<str::tilde>>(&operator_node))
		return semantic_entities::complement_expression
		(
			operand
		);
	else
		assert(false);
}

template<class DeclarativeRegion>
semantic_entities::expression_t
create_expression_from_type_sizeof_expression
(
	const syntax_nodes::type_id_sizeof_expression& type_sizeof_expression_node,
	DeclarativeRegion& declarative_region
)
{
	const syntax_nodes::type_id& type_id_node = syntax_nodes::get_type_id(type_sizeof_expression_node);
	semantic_entities::type_t type = create_type(type_id_node, declarative_region);
	return semantic_entity_analysis::get_type_size(type);
}

template<class DeclarativeRegion>
semantic_entities::expression_t
create_expression_from_expression_sizeof_expression
(
	const syntax_nodes::unary_sizeof_expression& expression_sizeof_expression_node,
	DeclarativeRegion& declarative_region
)
{
	const syntax_nodes::unary_expression& unary_expression_node = syntax_nodes::get_unary_expression(expression_sizeof_expression_node);
	semantic_entities::expression_t expr = create_expression_from_unary_expression(unary_expression_node, declarative_region);
	semantic_entities::type_t type = semantic_entities::get_type(expr);
	return semantic_entity_analysis::get_type_size(type);
}

struct: utility::static_visitor<semantic_entities::function_call<semantic_entities::simple_function>>
{
	semantic_entities::function_call<semantic_entities::simple_function>
	operator()(semantic_entities::variable* const) const
	{
		assert(false); //TODO
	}

	semantic_entities::function_call<semantic_entities::simple_function>
	operator()(semantic_entities::simple_function* const entity) const
	{
		return semantic_entities::function_call<semantic_entities::simple_function>(*entity, std::vector<semantic_entities::expression_t>());
	}
} create_function_call_visitor;

template<class DeclarativeRegion>
semantic_entities::expression_t
create_expression_from_postfix_expression
(
	const syntax_nodes::postfix_expression& postfix_expression_node,
	DeclarativeRegion& declarative_region
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	const postfix_expression_first_part& first_part_node = get_first_part(postfix_expression_node);

	//if the expression is a function call...
	if
	(
		const optional_node<postfix_expression_last_part_seq>& opt_postfix_expression_last_part_seq_node =
			get_last_part_seq(postfix_expression_node)
	)
	{
		const syntax_nodes::postfix_expression_last_part& last_part_node = opt_postfix_expression_last_part_seq_node->front();
		if(get<round_bracketed_optional_expression>(&last_part_node))
		{
			//find the function
			if(const boost::optional<const primary_expression&>& opt_primary_expression_node = get<primary_expression>(&first_part_node))
			{
				if(const boost::optional<const id_expression&>& opt_id_expression_node = get<id_expression>(&*opt_primary_expression_node))
				{
					if(const boost::optional<const unqualified_id&>& opt_unqualified_id_node = get<unqualified_id>(&*opt_id_expression_node))
					{
						if(const boost::optional<const identifier&>& opt_identifier_node = get<identifier>(&*opt_unqualified_id_node))
						{
							auto found_entity =
								name_lookup::find
								<
									semantic_entity_analysis::identification_policies::by_name,
									false,
									false,
									simple_function,
									variable
								>
								(
									(*opt_identifier_node).value(),
									&declarative_region
								)
							;

							return apply_visitor(create_function_call_visitor, found_entity);
						}
					}
					else if(/*const boost::optional<const qualified_id&>& opt_qualified_id_node =*/ get<qualified_id>(&*opt_id_expression_node))
					{
						assert(false); //TODO
						//return create_expression_from_qualified_id(*opt_qualified_id_node, declarative_region);
					}
				}
			}
		}
	}

	semantic_entities::expression_t expr = create_expression_from_postfix_expression_first_part(first_part_node, declarative_region);

	const optional_node<postfix_expression_last_part_seq>& opt_postfix_expression_last_part_seq_node = get_last_part_seq(postfix_expression_node);
	if(opt_postfix_expression_last_part_seq_node)
		return
			create_expression_from_postfix_expression_last_part_seq
			(
				*opt_postfix_expression_last_part_seq_node,
				expr,
				declarative_region
			)
		;
	else
		return expr;
}

template<class DeclarativeRegion>
semantic_entities::expression_t
create_expression_from_postfix_expression_first_part
(
	const syntax_nodes::postfix_expression_first_part& postfix_expression_first_part_node,
	DeclarativeRegion& declarative_region
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	if(const boost::optional<const primary_expression&>& opt_primary_expression_node = get<primary_expression>(&postfix_expression_first_part_node))
	{
		return create_expression_from_primary_expression(*opt_primary_expression_node, declarative_region);
	}
	else
	{
		assert(false); //TODO
	}
}

template<class DeclarativeRegion>
semantic_entities::expression_t
create_expression_from_postfix_expression_last_part_seq
(
	const syntax_nodes::postfix_expression_last_part_seq& postfix_expression_last_part_seq_node,
	semantic_entities::expression_t expr,
	DeclarativeRegion& declarative_region
)
{
	for(const syntax_nodes::postfix_expression_last_part& node: postfix_expression_last_part_seq_node)
		expr = create_expression_from_postfix_expression_last_part(node, expr, declarative_region);

	return expr;
}

template<class DeclarativeRegion>
semantic_entities::expression_t
create_expression_from_postfix_expression_last_part
(
	const syntax_nodes::postfix_expression_last_part& postfix_expression_last_part_node,
	const semantic_entities::expression_t& expr,
	DeclarativeRegion& /*declarative_region*/
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	//square_bracketed_expression,
	//round_bracketed_optional_expression,
	//dot_id_expression,
	//arrow_id_expression,
	//dot_pseudo_destructor_name,
	//arrow_pseudo_destructor_name,
	//predefined_text_node<str::double_plus>,
	//predefined_text_node<str::double_minus>

	if(get<predefined_text_node<str::double_plus>>(&postfix_expression_last_part_node))
		return semantic_entities::postfix_increment_expression
		(
			expr
		);
	else if(get<predefined_text_node<str::double_minus>>(&postfix_expression_last_part_node))
		return semantic_entities::postfix_decrement_expression
		(
			expr
		);
	else
		assert(false); //TODO
}

template<class DeclarativeRegion>
semantic_entities::expression_t
create_expression_from_primary_expression
(
	const syntax_nodes::primary_expression& primary_expression_node,
	DeclarativeRegion& declarative_region
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	if(const boost::optional<const literal&>& opt_literal_node = get<literal>(&primary_expression_node))
		return create_expression_from_literal(*opt_literal_node);
	else if(const boost::optional<const round_bracketed_expression&>& opt_round_bracketed_expression_node = get<round_bracketed_expression>(&primary_expression_node))
		return create_expression(get_expression(*opt_round_bracketed_expression_node), declarative_region);
	else if(const boost::optional<const id_expression&>& opt_id_expression_node = get<id_expression>(&primary_expression_node))
		return create_expression_from_id_expression(*opt_id_expression_node, declarative_region);
	else
		assert(false); //TODO
}

template<class DeclarativeRegion>
semantic_entities::expression_t
create_expression_from_id_expression
(
	const syntax_nodes::id_expression& id_expression_node,
	DeclarativeRegion& declarative_region
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	if(const boost::optional<const unqualified_id&>& opt_unqualified_id_node = get<unqualified_id>(&id_expression_node))
		return create_expression_from_unqualified_id(*opt_unqualified_id_node, declarative_region);
	else if(const boost::optional<const qualified_id&>& opt_qualified_id_node = get<qualified_id>(&id_expression_node))
		return create_expression_from_qualified_id(*opt_qualified_id_node, declarative_region);
	else
		assert(false);
}

template<class DeclarativeRegion>
semantic_entities::expression_t
create_expression_from_unqualified_id
(
	const syntax_nodes::unqualified_id& unqualified_id_node,
	DeclarativeRegion& declarative_region,
	const bool local_name_lookup
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	//if(const boost::optional<const operator_function_id&>& opt_operator_function_id_node = get<operator_function_id>(&unqualified_id_node))
	//	return create_expression(*opt_operator_function_id_node, declarative_region);
	//else if(const boost::optional<const conversion_function_id&>& opt_conversion_function_id_node = get<conversion_function_id>(&unqualified_id_node))
	//	return create_expression(*opt_conversion_function_id_node, declarative_region);
	//else if(const boost::optional<const destructor_name&>& opt_destructor_name_node = get<destructor_name>(&unqualified_id_node))
	//	return create_expression(*opt_destructor_name_node, declarative_region);
	//else if(const boost::optional<const template_id&>& opt_template_id_node = get<template_id>(&unqualified_id_node))
	//	return create_expression(*opt_template_id_node, declarative_region);
	/*else*/ if(const boost::optional<const identifier&>& opt_identifier_node = get<identifier>(&unqualified_id_node))
		return create_expression_from_identifier(*opt_identifier_node, declarative_region, local_name_lookup);
	else
		assert(false);
}

template<class DeclarativeRegion>
semantic_entities::expression_t
create_expression_from_qualified_id
(
	const syntax_nodes::qualified_id& qualified_id_node,
	DeclarativeRegion& declarative_region
)
{
	using namespace syntax_nodes;

	if(const boost::optional<const qualified_identifier&>& opt_qualified_identifier_node = get<qualified_identifier>(&qualified_id_node))
		return create_expression_from_qualified_identifier(*opt_qualified_identifier_node, declarative_region);
	else if(const boost::optional<const qualified_nested_id&>& opt_qualified_nested_id_node = get<qualified_nested_id>(&qualified_id_node))
		return create_expression_from_qualified_nested_id(*opt_qualified_nested_id_node, declarative_region);
//	else if(const boost::optional<const qualified_operator_function_id&>& opt_qualified_operator_function_id_node = get<qualified_operator_function_id>(&qualified_id_node))
//		return create_expression(*opt_qualified_operator_function_id_node, declarative_region);
//	else if(const boost::optional<const qualified_template_id&>& opt_qualified_template_id_node = get<qualified_template_id>(&qualified_id_node))
//		return create_expression(*opt_qualified_template_id_node, declarative_region);
	else
		assert(false);
}

class create_expression_from_unqualified_id_visitor: public utility::static_visitor<semantic_entities::expression_t>
{
	public:
		create_expression_from_unqualified_id_visitor(const syntax_nodes::unqualified_id& unqualified_id_node):
			unqualified_id_node_(unqualified_id_node)
		{
		}

		template<class DeclarativeRegion>
		semantic_entities::expression_t
		operator()(DeclarativeRegion* const declarative_region) const
		{
			return
				create_expression_from_unqualified_id
				(
					unqualified_id_node_,
					*declarative_region,
					true
				)
			;
		}

	private:
		const syntax_nodes::unqualified_id& unqualified_id_node_;
};

template<class DeclarativeRegion>
semantic_entities::expression_t
create_expression_from_qualified_nested_id
(
	const syntax_nodes::qualified_nested_id& qualified_nested_id_node,
	DeclarativeRegion& declarative_region
)
{
	using namespace syntax_nodes;

	if(has_template_keyword(qualified_nested_id_node))
		assert(false); //TODO

	semantic_entities::open_declarative_region_t unqualified_id_declarative_region =
		name_lookup::find_declarative_region
		(
			has_leading_double_colon(qualified_nested_id_node),
			get_nested_name_specifier(qualified_nested_id_node),
			&declarative_region
		)
	;

	const syntax_nodes::unqualified_id& unqualified_id_node = get_unqualified_id(qualified_nested_id_node);

	const create_expression_from_unqualified_id_visitor visitor(unqualified_id_node);

	return apply_visitor(visitor, unqualified_id_declarative_region);
}

struct: utility::static_visitor<semantic_entities::expression_t>
{
	template<class Entity>
	semantic_entities::expression_t
	operator()(Entity* const entity) const
	{
		return entity;
	}

	semantic_entities::expression_t
	operator()(semantic_entities::simple_function* const entity) const
	{
		return semantic_entities::function_call<semantic_entities::simple_function>(*entity, std::vector<semantic_entities::expression_t>());
	}
} entity_to_expression_visitor;

template<class DeclarativeRegion>
semantic_entities::expression_t
create_expression_from_qualified_identifier
(
	const syntax_nodes::qualified_identifier& qualified_identifier_node,
	DeclarativeRegion& declarative_region
)
{
	using namespace semantic_entities;

	auto found_entity =
		name_lookup::find
		<
			semantic_entity_analysis::identification_policies::by_name,
			false,
			false,
			variable,
			enum_constant<int>,
			enum_constant<unsigned int>,
			enum_constant<long int>,
			enum_constant<unsigned long int>
		>
		(
			true,
			syntax_nodes::optional_node<syntax_nodes::nested_name_specifier>(),
			get_identifier(qualified_identifier_node).value(),
			&declarative_region
		)
	;

	return utility::apply_visitor(entity_to_expression_visitor, found_entity);
}

template<class DeclarativeRegion>
semantic_entities::expression_t
create_expression_from_identifier
(
	const syntax_nodes::identifier& identifier_node,
	DeclarativeRegion& declarative_region,
	const bool local_name_lookup
)
{
	using namespace semantic_entities;

	auto found_entity =
		local_name_lookup ?
		name_lookup::find_local
		<
			semantic_entity_analysis::identification_policies::by_name,
			DeclarativeRegion,
			false,
			false,
			variable,
			enum_constant<int>,
			enum_constant<unsigned int>,
			enum_constant<long int>,
			enum_constant<unsigned long int>
		>
		(
			identifier_node.value(),
			declarative_region
		) :
		name_lookup::find
		<
			semantic_entity_analysis::identification_policies::by_name,
			false,
			false,
			variable,
			enum_constant<int>,
			enum_constant<unsigned int>,
			enum_constant<long int>,
			enum_constant<unsigned long int>
		>
		(
			identifier_node.value(),
			&declarative_region
		)
	;

	return apply_visitor(entity_to_expression_visitor, found_entity);
}

}}}} //namespace scalpel::cpp::semantic_analysis::detail

#endif

