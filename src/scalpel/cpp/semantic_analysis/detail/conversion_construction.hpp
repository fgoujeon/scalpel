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

#ifndef SCALPEL_CPP_SEMANTIC_ANALYSIS_DETAIL_CONVERSION_CONSTRUCTION_HPP
#define SCALPEL_CPP_SEMANTIC_ANALYSIS_DETAIL_CONVERSION_CONSTRUCTION_HPP

#include "semantic_entity_analysis/type_category.hpp"
#include <scalpel/cpp/semantic_graph.hpp>

namespace scalpel { namespace cpp { namespace semantic_analysis { namespace detail
{

semantic_entities::expression_t
create_conversion
(
	const semantic_entities::expression_t& expr,
	const semantic_entities::type_t& destination_type
);



semantic_entities::expression_t
create_conversion_to_bool(const semantic_entities::expression_t& expr);

semantic_entities::expression_t
create_conversion_to_long_int(const semantic_entities::expression_t& expr);

semantic_entities::expression_t
create_conversion_to_unsigned_int(const semantic_entities::expression_t& expr);

semantic_entities::expression_t
create_conversion_to_unsigned_long_int(const semantic_entities::expression_t& expr);

semantic_entities::expression_t
create_conversion_to_float(const semantic_entities::expression_t& expr);

semantic_entities::expression_t
create_conversion_to_double(const semantic_entities::expression_t& expr);

semantic_entities::expression_t
create_conversion_to_long_double(const semantic_entities::expression_t& expr);



semantic_entities::expression_t
create_integral_promotions
(
	const semantic_entities::expression_t& source,
	const semantic_entity_analysis::type_category source_type_category
);

void
create_usual_arithmetic_conversions
(
	semantic_entities::expression_t& left_operand,
	semantic_entities::expression_t& right_operand,
	const semantic_entity_analysis::type_category left_operand_type_category,
	const semantic_entity_analysis::type_category right_operand_type_category
);

}}}} //namespace scalpel::cpp::semantic_analysis::detail

#endif

