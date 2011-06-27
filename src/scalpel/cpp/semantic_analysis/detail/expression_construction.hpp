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

#ifndef SCALPEL_CPP_SEMANTIC_ANALYSIS_DETAIL_EXPRESSION_CONSTRUCTION_HPP
#define SCALPEL_CPP_SEMANTIC_ANALYSIS_DETAIL_EXPRESSION_CONSTRUCTION_HPP

#include <scalpel/cpp/semantic_graph.hpp>
#include <scalpel/cpp/syntax_tree.hpp>

namespace scalpel { namespace cpp { namespace semantic_analysis { namespace detail
{

//
//create expressions through syntax tree analysis
//

template<class DeclarativeRegion>
semantic_entities::expression_t
create_expression
(
	const syntax_nodes::expression& expression_node,
	DeclarativeRegion& declarative_region
);

template<class DeclarativeRegion>
semantic_entities::expression_t
create_expression
(
	const syntax_nodes::assignment_expression& assignment_expression_node,
	DeclarativeRegion& declarative_region
);

template<class DeclarativeRegion>
semantic_entities::expression_t
create_expression
(
	const syntax_nodes::assignment_assignment_expression& assignment_assignment_expression_node,
	DeclarativeRegion& declarative_region
);

template<class DeclarativeRegion>
semantic_entities::expression_t
create_expression
(
	const syntax_nodes::conditional_expression& conditional_expression_node,
	DeclarativeRegion& declarative_region
);

template<class DeclarativeRegion>
semantic_entities::expression_t
create_expression
(
	const syntax_nodes::logical_or_expression& logical_or_expression_node,
	DeclarativeRegion& declarative_region
);

template<class DeclarativeRegion>
semantic_entities::expression_t
create_expression
(
	const syntax_nodes::logical_and_expression& logical_and_expression_node,
	DeclarativeRegion& declarative_region
);

template<class DeclarativeRegion>
semantic_entities::expression_t
create_expression
(
	const syntax_nodes::inclusive_or_expression& inclusive_or_expression_node,
	DeclarativeRegion& declarative_region
);

template<class DeclarativeRegion>
semantic_entities::expression_t
create_expression
(
	const syntax_nodes::exclusive_or_expression& exclusive_or_expression_node,
	DeclarativeRegion& declarative_region
);

template<class DeclarativeRegion>
semantic_entities::expression_t
create_expression
(
	const syntax_nodes::and_expression& and_expression_node,
	DeclarativeRegion& declarative_region
);

template<class DeclarativeRegion>
semantic_entities::expression_t
create_expression
(
	const syntax_nodes::equality_expression& equality_expression_node,
	DeclarativeRegion& declarative_region
);

template<class DeclarativeRegion>
semantic_entities::expression_t
create_expression
(
	const syntax_nodes::relational_expression& relational_expression_node,
	DeclarativeRegion& declarative_region
);

template<class DeclarativeRegion>
semantic_entities::expression_t
create_expression
(
	const syntax_nodes::shift_expression& shift_expression_node,
	DeclarativeRegion& declarative_region
);

template<class DeclarativeRegion>
semantic_entities::expression_t
create_expression
(
	const syntax_nodes::additive_expression& additive_expression_node,
	DeclarativeRegion& declarative_region
);

template<class DeclarativeRegion>
semantic_entities::expression_t
create_expression
(
	const syntax_nodes::multiplicative_expression& multiplicative_expression_node,
	DeclarativeRegion& declarative_region
);

template<class DeclarativeRegion>
semantic_entities::expression_t
create_expression
(
	const syntax_nodes::pm_expression& pm_expression_node,
	DeclarativeRegion& declarative_region
);

template<class DeclarativeRegion>
semantic_entities::expression_t
create_expression
(
	const syntax_nodes::cast_expression& cast_expression_node,
	DeclarativeRegion& declarative_region
);

template<class DeclarativeRegion>
semantic_entities::expression_t
create_expression
(
	const syntax_nodes::unary_expression& unary_expression_node,
	DeclarativeRegion& declarative_region
);

template<class DeclarativeRegion>
semantic_entities::expression_t
create_expression
(
	const syntax_nodes::unary_operator_expression& unary_operator_expression_node,
	DeclarativeRegion& declarative_region
);

template<class DeclarativeRegion>
semantic_entities::expression_t
create_expression
(
	const syntax_nodes::postfix_expression& postfix_expression_node,
	DeclarativeRegion& declarative_region
);

template<class DeclarativeRegion>
semantic_entities::expression_t
create_expression
(
	const syntax_nodes::primary_expression& primary_expression_node,
	DeclarativeRegion& declarative_region
);

template<class DeclarativeRegion>
semantic_entities::expression_t
create_expression
(
	const syntax_nodes::id_expression& id_expression_node,
	DeclarativeRegion& declarative_region
);

template<class DeclarativeRegion>
semantic_entities::expression_t
create_expression
(
	const syntax_nodes::unqualified_id& unqualified_id_node,
	DeclarativeRegion& declarative_region
);

template<class DeclarativeRegion>
semantic_entities::expression_t
create_expression
(
	const syntax_nodes::identifier& identifier_node,
	DeclarativeRegion& declarative_region
);

semantic_entities::expression_t
create_expression(const syntax_nodes::literal& literal_node);



//
//create and simplify expressions objects
//

semantic_entities::expression_t
create_addition_expression
(
	const semantic_entities::expression_t& left_operand,
	const semantic_entities::expression_t& right_operand
);

}}}} //namespace scalpel::cpp::semantic_analysis::detail

#include "expression_construction.ipp"

#endif

