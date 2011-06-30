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

#ifndef SCALPEL_CPP_SEMANTIC_ANALYSIS_DETAIL_CLASS_CONSTRUCTION_HPP
#define SCALPEL_CPP_SEMANTIC_ANALYSIS_DETAIL_CLASS_CONSTRUCTION_HPP

#include <scalpel/cpp/semantic_graph.hpp>
#include <scalpel/cpp/semantic_entities/type_traits/has_base_classes.hpp>
#include <scalpel/cpp/semantic_entities/type_traits/has_entity_aliases.hpp>
#include <scalpel/cpp/syntax_tree.hpp>
#include <boost/utility/enable_if.hpp>
#include <memory>

namespace scalpel { namespace cpp { namespace semantic_analysis { namespace detail
{

template<class Class>
std::unique_ptr<Class>
create_class(const syntax_nodes::class_specifier& class_specifier_node);

template<class Class>
std::unique_ptr<Class>
create_member_class
(
	const syntax_nodes::class_specifier& class_specifier_node,
	const semantic_entities::member_access access
);

template<class Class>
std::unique_ptr<Class>
create_class
(
	const syntax_nodes::class_elaborated_specifier& class_elaborated_specifier_node
);

template<class Class>
std::unique_ptr<Class>
create_member_class
(
	const syntax_nodes::class_elaborated_specifier& class_elaborated_specifier_node,
	const semantic_entities::member_access access
);

template<class Class>
void
fill_class
(
	Class& class_entity,
	const syntax_nodes::class_specifier& class_specifier_node
);

template<class Class>
void
fill_class
(
	Class& class_entity,
	const semantic_entities::member_access default_access,
	const syntax_nodes::base_clause& base_clause_node,
	typename boost::enable_if<semantic_entities::type_traits::has_base_classes<Class>>::type* = 0
);

template<class Class>
void
fill_class
(
	Class& class_entity,
	const semantic_entities::member_access default_access,
	const syntax_nodes::base_clause& base_clause_node,
	typename boost::disable_if<semantic_entities::type_traits::has_base_classes<Class>>::type* = 0
);

template<class Class>
void
fill_class
(
	Class& class_entity,
	const semantic_entities::member_access current_access,
	const syntax_nodes::member_declaration_member_declarator_list& member_declaration_member_declarator_list_node
);

template<class Class>
void
fill_class
(
	Class& class_entity,
	const semantic_entities::member_access access,
	const syntax_nodes::function_definition& function_definition_node
);

template<class Class>
void
fill_class
(
	Class& class_entity,
	const semantic_entities::member_access access,
	const syntax_nodes::using_declaration& using_declaration_node,
	typename boost::enable_if<semantic_entities::type_traits::has_entity_aliases<Class>>::type* = 0
);

template<class Class>
void
fill_class
(
	Class& class_entity,
	const semantic_entities::member_access access,
	const syntax_nodes::using_declaration& using_declaration_node,
	typename boost::disable_if<semantic_entities::type_traits::has_entity_aliases<Class>>::type* = 0
);

//Check whether the given class hasn't been forward declared in the given
//parent class.
//If so, return the forward declared class.
//If not, add the given class to the given parent class
//and return the given class.
template<class ParentClass>
semantic_entities::member_class&
add_class
(
	ParentClass& parent_class_entity,
	std::unique_ptr<semantic_entities::member_class>&& class_entity
);

//add the entity alias to the given class
template<class Class, class... Entities>
void
add_alias
(
	Class& class_entity,
	const utility::variant<Entities...>& entity,
	const semantic_entities::member_access access
);

semantic_entities::class_ptr_variant
find_class
(
	const syntax_nodes::ptr_to_member_operator& ptr_to_member_operator_node,
	const semantic_entities::declarative_region_t& current_declarative_region
);

}}}} //namespace scalpel::cpp::semantic_analysis::detail

#include "class_construction.ipp"

#endif

