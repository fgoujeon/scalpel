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

#ifndef SCALPEL_CPP_SEMANTIC_ANALYSIS_HPP
#define SCALPEL_CPP_SEMANTIC_ANALYSIS_HPP

#include "syntax_tree.hpp"
#include "semantic_graph.hpp"
#include <memory>

namespace scalpel { namespace cpp
{

namespace semantic_analysis
{

std::shared_ptr<semantic_graph>
analyze(const syntax_tree& tree);

template<class DeclarativeRegionT>
void
analyze(const syntax_nodes::function_definition& function_definition_node, std::shared_ptr<DeclarativeRegionT> current_declarative_region);

template<class DeclarativeRegionT>
void
analyze(const syntax_nodes::simple_declaration& syntax_node, std::shared_ptr<DeclarativeRegionT> current_declarative_region);



//
//namespace creation functions
//

std::shared_ptr<semantic_entities::namespace_>
create_namespace
(
	const syntax_nodes::namespace_definition& namespace_definition_node
);

void
fill_namespace
(
	std::shared_ptr<semantic_entities::namespace_> namespace_entity,
	const syntax_nodes::namespace_definition& namespace_definition_node
);

void
fill_namespace
(
	std::shared_ptr<semantic_entities::namespace_> namespace_entity,
	const syntax_nodes::declaration_seq& declaration_seq_node
);



//
//class creation functions
//

std::shared_ptr<semantic_entities::class_>
create_class(const syntax_nodes::class_specifier& syntax_node);

void
fill_class(std::shared_ptr<semantic_entities::class_> c, const syntax_nodes::class_specifier& syntax_node);



//
//function creation functions
//

template<class DeclarativeRegionT>
std::shared_ptr<semantic_entities::simple_function>
create_simple_function
(
	const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node,
	const syntax_nodes::declarator& declarator_node,
	std::shared_ptr<DeclarativeRegionT> current_declarative_region
);

template<class DeclarativeRegionT>
std::shared_ptr<semantic_entities::operator_function>
create_operator_function
(
	const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node,
	const syntax_nodes::declarator& declarator_node,
	std::shared_ptr<DeclarativeRegionT> current_declarative_region
);

template<class DeclarativeRegionT>
semantic_entities::simple_function::parameters_t
create_parameters
(
	const syntax_nodes::declarator& declarator_node,
	std::shared_ptr<DeclarativeRegionT> current_declarative_region
);



//
//type creation functions
//

template<class DeclarativeRegionT>
semantic_entities::type_shared_ptr_variant
create_type
(
	const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node,
	const syntax_nodes::declarator& declarator_node,
	std::shared_ptr<DeclarativeRegionT> current_declarative_region
);

template<class DeclarativeRegionT>
semantic_entities::type_shared_ptr_variant
create_type
(
	const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node,
	const syntax_nodes::abstract_declarator& abstract_declarator_node,
	std::shared_ptr<DeclarativeRegionT> current_declarative_region
);

template<class DeclarativeRegionT>
semantic_entities::type_shared_ptr_variant
create_type
(
	const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node,
	std::shared_ptr<DeclarativeRegionT> current_declarative_region
);

template<class DeclarativeRegionT>
semantic_entities::type_shared_ptr_variant
get_conversion_function_type
(
	const syntax_nodes::declarator& declarator_node,
	std::shared_ptr<DeclarativeRegionT> current_declarative_region
);

semantic_entities::type_shared_ptr_variant
decorate_type
(
	semantic_entities::type_shared_ptr_variant return_type,
	const bool const_qualified,
	const bool volatile_qualified
);

semantic_entities::type_shared_ptr_variant
decorate_type
(
	semantic_entities::type_shared_ptr_variant return_type,
	const syntax_nodes::ptr_operator_seq& ptr_operator_seq_node
);

template<class DeclarativeRegionT>
void
get_type_info
(
	const syntax_nodes::type_specifier& type_specifier_node,
	boost::optional<semantic_entities::type_shared_ptr_variant>& t,
	bool& bool_type,
	bool& char_type,
	bool& double_type,
	bool& float_type,
	bool& int_type,
	bool& long_long_type,
	bool& long_type,
	bool& short_type,
	bool& signed_type,
	bool& unsigned_type,
	bool& void_type,
	bool& wchar_t_type,
	bool& const_qualified,
	bool& volatile_qualified,
	std::shared_ptr<DeclarativeRegionT> current_declarative_region
);

std::shared_ptr<const semantic_entities::fundamental_type>
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



//
//variable creation functions
//

template<class DeclarativeRegionT>
std::vector<std::shared_ptr<semantic_entities::variable>>
create_variables
(
	const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node,
	const syntax_nodes::init_declarator_list& init_declarator_list_node,
	std::shared_ptr<DeclarativeRegionT> current_declarative_region
);

template<class DeclarativeRegionT>
std::shared_ptr<semantic_entities::variable>
create_variable
(
	const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node,
	const syntax_nodes::declarator& declarator_node,
	std::shared_ptr<DeclarativeRegionT> current_declarative_region
);



//
//misc creation functions
//

std::shared_ptr<semantic_entities::namespace_alias>
create_namespace_alias
(
	const syntax_nodes::namespace_alias_definition& namespace_alias_definition_node,
	std::shared_ptr<semantic_entities::namespace_> current_namespace
);

std::shared_ptr<semantic_entities::namespace_>
create_using_directive
(
	const syntax_nodes::using_directive& using_directive_node,
	std::shared_ptr<semantic_entities::namespace_> current_namespace
);

} //namespace semantic_analysis

}} //namespace scalpel::cpp

#include "semantic_analysis.ipp"

#endif

