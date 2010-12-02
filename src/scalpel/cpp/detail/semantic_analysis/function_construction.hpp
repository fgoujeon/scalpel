/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2010  Florian Goujeon

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

#ifndef SCALPEL_CPP_DETAIL_SEMANTIC_ANALYSIS_FUNCTION_CONSTRUCTION_HPP
#define SCALPEL_CPP_DETAIL_SEMANTIC_ANALYSIS_FUNCTION_CONSTRUCTION_HPP

#include <scalpel/cpp/semantic_graph.hpp>
#include <scalpel/cpp/syntax_tree.hpp>
#include <scalpel/utility/variant.hpp>
#include <memory>

namespace scalpel { namespace cpp { namespace detail { namespace semantic_analysis
{

typedef
	utility::variant
	<
		std::shared_ptr<semantic_entities::constructor>,
		std::shared_ptr<semantic_entities::destructor>,
		std::shared_ptr<semantic_entities::operator_function>,
		std::shared_ptr<semantic_entities::conversion_function>,
		std::shared_ptr<semantic_entities::simple_function>
	>::type
	function_shared_ptr_variant
;

function_shared_ptr_variant
create_function
(
	const syntax_nodes::function_definition& function_definition_node,
	const semantic_entities::declarative_region_shared_ptr_variant current_declarative_region
);

void
define_function
(
	const function_shared_ptr_variant& function_entity,
	const syntax_nodes::function_definition& function_definition_node,
	const semantic_entities::declarative_region_shared_ptr_variant current_declarative_region
);

//find the function corresponding to the given function signature
boost::optional<function_shared_ptr_variant>
find_function
(
	const function_shared_ptr_variant function_signature,
	const syntax_nodes::function_definition& function_definition_node,
	const semantic_entities::declarative_region_shared_ptr_variant current_declarative_region
);

//find the function corresponding to the given function signature
template<class FunctionT>
std::shared_ptr<FunctionT>
find_function
(
	const std::shared_ptr<const FunctionT> function_signature,
	const syntax_nodes::function_definition& function_definition_node,
	const semantic_entities::declarative_region_shared_ptr_variant current_declarative_region
);

std::shared_ptr<semantic_entities::operator_function>
create_operator_function
(
	const syntax_nodes::declarator& declarator_node,
	const semantic_entities::type_shared_ptr_variant type,
	const bool is_inline,
	const bool is_static,
	const semantic_entities::declarative_region_shared_ptr_variant current_declarative_region
);

semantic_entities::type_shared_ptr_variant
get_conversion_function_type
(
	const syntax_nodes::declarator& declarator_node,
	const semantic_entities::declarative_region_shared_ptr_variant current_declarative_region
);

semantic_entities::simple_function::parameters_t
create_parameters
(
	boost::optional<const syntax_nodes::parameter_declaration_list&> opt_parameter_declaration_list_node,
	const semantic_entities::declarative_region_shared_ptr_variant current_declarative_region
);

semantic_entities::simple_function::parameters_t
create_parameters
(
	const syntax_nodes::parameter_declaration_list& parameter_declaration_list_node,
	const semantic_entities::declarative_region_shared_ptr_variant current_declarative_region
);

}}}} //namespace scalpel::cpp::detail::semantic_analysis

#include "function_construction.ipp"

#endif

