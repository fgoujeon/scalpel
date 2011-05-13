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

#include <scalpel/cpp/semantic_entities/type_traits/is_member.hpp>
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
	//A type object allocated on the heap by create_type().
	//This object is set when the given decl-specifier-seq declares a new type.
	boost::optional<user_defined_type_ptr_variant> opt_new_type;

	//This object is set when the given decl-specifier-seq defines a type, previously declared or not.
	boost::optional<user_defined_type_ptr_variant> opt_defined_type;

	//The full type definition described by the given decl-specifier-seq, including potential cv-qualifiers.
	boost::optional<semantic_entities::type_variant> opt_complete_type;

	bool has_typedef_specifier;
	bool has_friend_specifier;
	bool has_mutable_specifier;
	bool has_static_specifier;
	bool has_inline_specifier;
	bool has_virtual_specifier;
	bool has_explicit_specifier;
	bool create_anonymous_object; //true if an anonymous object must be created (anonymous union)
};

//Create and/or get the type described by the given decl-specifier-seq.
template<class DeclarativeRegion>
type_info
create_type
(
	const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node,
	const bool has_declarator,
	DeclarativeRegion& current_declarative_region,
	const semantic_entities::member_access access = semantic_entities::member_access::PUBLIC
);



template<class Type>
Type*
create_type
(
	const std::string& type_name,
	const semantic_entities::member_access access,
	typename boost::enable_if<semantic_entities::type_traits::is_member<Type>>::type* = 0
);

template<class Type>
Type*
create_type
(
	const std::string& type_name,
	const semantic_entities::member_access, //ignored
	typename boost::disable_if<semantic_entities::type_traits::is_member<Type>>::type* = 0
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



//Find a type named type_name in the given declarative_region.
//Return 0 if nothing is found.
template<class Type, class DeclarativeRegion>
Type*
find_type
(
	DeclarativeRegion& declarative_region,
	const std::string& type_name
);

}}}} //namespace scalpel::cpp::semantic_analysis::detail

#include "type_construction.ipp"

#endif

