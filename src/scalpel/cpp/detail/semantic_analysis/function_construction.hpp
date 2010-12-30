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
#include <scalpel/utility/shared_ptr_variant.hpp>
#include <memory>

namespace scalpel { namespace cpp { namespace detail { namespace semantic_analysis
{

typedef
	utility::shared_ptr_variant
	<
		semantic_entities::constructor,
		semantic_entities::destructor,
		semantic_entities::operator_member_function,
		semantic_entities::conversion_function,
		semantic_entities::simple_member_function,
		semantic_entities::operator_function,
		semantic_entities::simple_function
	>::type
	function_shared_ptr_variant
;

function_shared_ptr_variant
create_function
(
	const syntax_nodes::function_definition& function_definition_node,
	const semantic_entities::declarative_region_shared_ptr_variant current_declarative_region,
	const bool is_class_member
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
	const function_shared_ptr_variant& function_signature,
	const semantic_entities::open_declarative_region_shared_ptr_variant& function_declarative_region
);

//find the function corresponding to the given function signature
template<class FunctionT>
std::shared_ptr<FunctionT>
find_function
(
	const std::shared_ptr<const FunctionT> function_signature,
	const semantic_entities::open_declarative_region_shared_ptr_variant& function_declarative_region
);

semantic_entities::overloadable_operator
get_operator_function_operator
(
	const syntax_nodes::declarator& declarator_node
);

semantic_entities::type_variant
get_conversion_function_type
(
	const syntax_nodes::declarator& declarator_node,
	const semantic_entities::declarative_region_shared_ptr_variant current_declarative_region
);

semantic_entities::function_parameter_list
create_parameters
(
	boost::optional<const syntax_nodes::parameter_declaration_list&> opt_parameter_declaration_list_node,
	const semantic_entities::declarative_region_shared_ptr_variant current_declarative_region
);

semantic_entities::function_parameter_list
create_parameters
(
	const syntax_nodes::parameter_declaration_list& parameter_declaration_list_node,
	const semantic_entities::declarative_region_shared_ptr_variant current_declarative_region
);

}}}} //namespace scalpel::cpp::detail::semantic_analysis

#include "function_construction.ipp"

#endif

