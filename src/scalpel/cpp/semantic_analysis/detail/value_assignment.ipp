/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2012  Florian Goujeon

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

#ifndef SCALPEL_CPP_SEMANTIC_ANALYSIS_DETAIL_VALUE_ASSIGNMENT_IPP
#define SCALPEL_CPP_SEMANTIC_ANALYSIS_DETAIL_VALUE_ASSIGNMENT_IPP

#include "expression_construction.hpp"
#include "conversion_construction.hpp"

namespace scalpel { namespace cpp { namespace semantic_analysis { namespace detail
{

class value_assignment_visitor: public utility::static_visitor<void>
{
	public:
		value_assignment_visitor(semantic_entities::expression_t& expr):
			expression_(expr)
		{
		}

		template<class Entity>
		void
		operator()(Entity* entity)
		{
			expression_ = create_conversion(expression_, entity->type());
			entity->default_value(expression_);
		}

#define VALUE_ASSIGNMENT_ERROR(TYPE) \
void \
operator()(semantic_entities::TYPE*) \
{ \
}

		VALUE_ASSIGNMENT_ERROR(constructor)
		VALUE_ASSIGNMENT_ERROR(destructor)
		VALUE_ASSIGNMENT_ERROR(simple_function)
		VALUE_ASSIGNMENT_ERROR(operator_function)
		VALUE_ASSIGNMENT_ERROR(simple_member_function)
		VALUE_ASSIGNMENT_ERROR(operator_member_function)
		VALUE_ASSIGNMENT_ERROR(conversion_function)
		VALUE_ASSIGNMENT_ERROR(typedef_)
		VALUE_ASSIGNMENT_ERROR(member_typedef)

#undef VALUE_ASSIGNMENT_ERROR

	private:
		semantic_entities::expression_t& expression_;
};

template<class DeclarativeRegion>
void
assign_value
(
	declarator_entity_ptr_variant& declarator_entity,
	const syntax_nodes::assignment_expression& assignment_expression_node,
	DeclarativeRegion& declarative_region
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	semantic_entities::expression_t expr = create_expression_from_assignment_expression(assignment_expression_node, declarative_region);

	value_assignment_visitor visitor(expr);
	utility::apply_visitor(visitor, declarator_entity);
}

template<typename UnderlyingType, class DeclarativeRegion>
void
assign_value
(
	semantic_entities::enum_constant<UnderlyingType>& entity,
	const syntax_nodes::conditional_expression& conditional_expression_node,
	DeclarativeRegion& declarative_region
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	semantic_entities::expression_t expr = create_expression_from_conditional_expression(conditional_expression_node, declarative_region);
	expr = create_conversion(expr, fundamental_type::INT);

	if(int* opt_int = utility::get<int>(&expr))
		entity.value(*opt_int);
	else
		assert(false);
}

}}}} //namespace scalpel::cpp::semantic_analysis::detail

#endif

