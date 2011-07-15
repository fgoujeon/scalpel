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

#ifndef SCALPEL_CPP_SEMANTIC_ANALYSIS_DETAIL_OTHER_ENTITY_CONSTRUCTION_HPP
#define SCALPEL_CPP_SEMANTIC_ANALYSIS_DETAIL_OTHER_ENTITY_CONSTRUCTION_HPP

#include <scalpel/cpp/semantic_graph.hpp>
#include <scalpel/cpp/syntax_tree.hpp>
#include <scalpel/utility/ptr_variant.hpp>

namespace scalpel { namespace cpp { namespace semantic_analysis { namespace detail
{

typedef
	utility::ptr_variant
	<
		semantic_entities::constructor,
		semantic_entities::destructor,
		semantic_entities::operator_function,
		semantic_entities::conversion_function,
		semantic_entities::simple_function,
		semantic_entities::operator_member_function,
		semantic_entities::simple_member_function,
		semantic_entities::variable,
		semantic_entities::member_variable,
		semantic_entities::static_member_variable,
		semantic_entities::typedef_,
		semantic_entities::member_typedef
	>::type
	declarator_entity_ptr_variant
;

//Create variable/function/typedef/etc. corresponding to the given declarator.
template<class DeclarativeRegion>
declarator_entity_ptr_variant
create_entity
(
	const syntax_nodes::declarator& declarator_node,
	DeclarativeRegion& current_declarative_region,
	boost::optional<semantic_entities::type_t> opt_type,
	const bool has_typedef_specifier,
	const bool has_mutable_specifier,
	const bool has_static_specifier,
	const bool has_inline_specifier,
	const bool has_virtual_specifier,
	const bool has_explicit_specifier,
	const bool has_pure_specifier,
	const bool is_class_member,
	const semantic_entities::member_access access
);

template<class Namespace>
std::unique_ptr<semantic_entities::namespace_alias>
create_namespace_alias
(
	const syntax_nodes::namespace_alias_definition& namespace_alias_definition_node,
	Namespace& current_namespace
);

template<class Namespace>
semantic_entities::namespace_&
find_using_directive_namespace
(
	const syntax_nodes::using_directive& using_directive_node,
	Namespace& current_namespace
);

template<class Class>
std::unique_ptr<semantic_entities::bit_field>
create_bit_field
(
	const syntax_nodes::member_declarator_bit_field_member& member_declarator_bit_field_member_node,
	const semantic_entities::type_t& type,
	const bool is_mutable,
	const semantic_entities::member_access access,
	Class& current_class
);

}}}} //namespace scalpel::cpp::semantic_analysis::detail

#include "other_entity_construction.ipp"

#endif

