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

#ifndef SCALPEL_CPP_SEMANTIC_ANALYSIS_DETAIL_TYPE_CONSTRUCTION_HPP
#define SCALPEL_CPP_SEMANTIC_ANALYSIS_DETAIL_TYPE_CONSTRUCTION_HPP

#include <scalpel/cpp/semantic_graph.hpp>
#include <scalpel/cpp/syntax_tree.hpp>
#include <scalpel/utility/ptr_variant.hpp>
#include <scalpel/utility/variant.hpp>
#include <memory>

namespace scalpel { namespace cpp { namespace semantic_analysis { namespace detail
{

typedef
	typename utility::ptr_variant
	<
		semantic_entities::class_,
		semantic_entities::member_class,
		semantic_entities::union_,
		semantic_entities::member_union,
		semantic_entities::anonymous_union,
		semantic_entities::anonymous_member_union,
		semantic_entities::enum_,
		semantic_entities::member_enum
	>::type
	user_defined_type_ptr_variant
;

struct type_info
{
	boost::optional<user_defined_type_ptr_variant> opt_new_type; //type object created by create_type() that must be stored
	boost::optional<user_defined_type_ptr_variant> opt_defined_type; //type *defined* (not only declared) by the decl-specifier-seq node
	boost::optional<semantic_entities::type_variant> opt_complete_type; //qualified type
	bool has_typedef_specifier;
	bool has_friend_specifier;
	bool has_mutable_specifier;
	bool has_static_specifier;
	bool has_inline_specifier;
	bool has_virtual_specifier;
	bool has_explicit_specifier;
	bool create_anonymous_object; //an anonymous object must be created
};

template<class DeclarativeRegion>
type_info
create_type
(
	const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node,
	const bool has_declarator,
	DeclarativeRegion& current_declarative_region,
	const bool is_member,
	const semantic_entities::member_access access
);



//Create the type described by the given decl-specifier-seq.
//The returned type is not qualified by the qualifiers of
//the decl-specifier-seq.
semantic_entities::type_variant
create_simple_type
(
	const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node,
	const semantic_entities::declarative_region_ptr_variant current_declarative_region
);

//Create the type described by the given type-specifier-seq.
//The returned type is not qualified by the qualifiers of
//the type-specifier-seq.
semantic_entities::type_variant
create_simple_type
(
	const syntax_nodes::type_specifier_seq& type_specifier_seq_node,
	const semantic_entities::declarative_region_ptr_variant current_declarative_region
);



void
fill_type
(
	const user_defined_type_ptr_variant& type,
	const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node
);



//qualify type with decl-specifier-seq's const and volatile specifiers
semantic_entities::type_variant
qualify_type
(
	semantic_entities::type_variant type,
	const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node
);

//qualify type with declarator's pointers, references, arrays and function types
semantic_entities::type_variant
qualify_type
(
	semantic_entities::type_variant type,
	const syntax_nodes::declarator& declarator_node,
	const semantic_entities::declarative_region_ptr_variant& current_declarative_region,
	const bool ignore_function_type = false
);

//qualify type with abstract-declarator's pointers, references, arrays and function types
semantic_entities::type_variant
qualify_type
(
	semantic_entities::type_variant type,
	const syntax_nodes::abstract_declarator& abstract_declarator_node,
	const semantic_entities::declarative_region_ptr_variant& current_declarative_region
);

//qualify type with direct-declarator-last-part-seq's arrays and function types
semantic_entities::type_variant
qualify_type
(
	semantic_entities::type_variant type,
	const syntax_nodes::direct_declarator_last_part_seq& last_part_seq_node,
	const semantic_entities::declarative_region_ptr_variant& current_declarative_region,
	const bool ignore_function_type
);

//qualify type with direct-declarator-last-part's array or function type
semantic_entities::type_variant
qualify_type
(
	semantic_entities::type_variant type,
	const syntax_nodes::direct_declarator_last_part& last_part_node,
	const semantic_entities::declarative_region_ptr_variant& current_declarative_region,
	const bool ignore_function_type
);

//qualify type with ptr-operator-seq's pointers and references
semantic_entities::type_variant
qualify_type
(
	semantic_entities::type_variant type,
	const syntax_nodes::ptr_operator_seq& ptr_operator_seq_node,
	const semantic_entities::declarative_region_ptr_variant& current_declarative_region
);

//qualify type with cv-qualifier-seq's const and volatile
semantic_entities::type_variant
qualify_type
(
	semantic_entities::type_variant type,
	const syntax_nodes::cv_qualifier_seq& cv_qualifier_seq_node
);

semantic_entities::fundamental_type
get_fundamental_type
(
	const bool bool_type,
	const bool char_type,
	const bool double_type,
	const bool float_type,
	const bool int_type,
	const bool long_long_type,
	const bool long_type,
	const bool short_type,
	const bool signed_type,
	const bool unsigned_type,
	const bool void_type,
	const bool wchar_t_type
);

}}}} //namespace scalpel::cpp::semantic_analysis::detail

#include "type_construction.ipp"

#endif

