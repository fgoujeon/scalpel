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

#ifndef SCALPEL_CPP_DETAIL_SEMANTIC_ANALYSIS_BASIC_FUNCTIONS_HPP
#define SCALPEL_CPP_DETAIL_SEMANTIC_ANALYSIS_BASIC_FUNCTIONS_HPP

#include <scalpel/cpp/syntax_tree.hpp>
#include <scalpel/cpp/semantic_graph.hpp>

namespace scalpel { namespace cpp { namespace detail { namespace semantic_analysis
{

//TODO A lot of syntax checks are done in some of these functions.
//That kind of work should be done by the syntax analyzer.
//The grammar should be reformulated so the semantic analysis
//can be performed more straightforwardly.

//
//class related
//

semantic_entities::class_::access
get_access(const syntax_nodes::access_specifier access_specifier_node);



//
//decl_specifier_seq related
//

enum class decl_specifier_seq_type
{
	NO_TYPE,
	SIMPLE_TYPE,
	CLASS_DECLARATION,
	CLASS_FORWARD_DECLARATION
};

decl_specifier_seq_type
get_decl_specifier_seq_type(const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node);

const syntax_nodes::class_specifier&
get_class_specifier(const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node);

const syntax_nodes::class_elaborated_specifier&
get_class_elaborated_specifier(const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node);

template<class SpecifierNodeT, const std::string& Specifier>
bool
has_specifier(const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node);

inline
bool
has_inline_specifier(const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node)
{
	return has_specifier<syntax_nodes::function_specifier, utility::extern_strings::inline_>(decl_specifier_seq_node);
}

inline
bool
has_virtual_specifier(const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node)
{
	return has_specifier<syntax_nodes::function_specifier, utility::extern_strings::virtual_>(decl_specifier_seq_node);
}

inline
bool
has_explicit_specifier(const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node)
{
	return has_specifier<syntax_nodes::function_specifier, utility::extern_strings::explicit_>(decl_specifier_seq_node);
}

inline
bool
has_static_specifier(const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node)
{
	return has_specifier<syntax_nodes::storage_class_specifier, utility::extern_strings::static_>(decl_specifier_seq_node);
}

inline
bool
has_mutable_specifier(const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node)
{
	return has_specifier<syntax_nodes::storage_class_specifier, utility::extern_strings::mutable_>(decl_specifier_seq_node);
}

bool
has_typedef_specifier(const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node);

bool
has_pure_specifier(const syntax_nodes::member_declarator_declarator& member_declarator_declarator_node);



//
//type-specifier-seq related
//

enum class type_specifier_seq_type
{
	NO_TYPE,
	SIMPLE_TYPE,
	CLASS_DECLARATION,
	CLASS_FORWARD_DECLARATION
};

type_specifier_seq_type
get_type_specifier_seq_type(const syntax_nodes::type_specifier_seq& type_specifier_seq_node);



//
//declarator related
//

enum class declarator_type
{
	DESTRUCTOR_DECLARATOR,
	OPERATOR_FUNCTION_DECLARATOR,
	CONVERSION_FUNCTION_DECLARATOR,
	SIMPLE_FUNCTION_DECLARATOR,
	VARIABLE_DECLARATOR
};

declarator_type
get_declarator_type(const syntax_nodes::declarator& declarator_node);

const syntax_nodes::parameter_declaration_list&
get_parameter_declaration_list(const syntax_nodes::declarator& declarator_node);

template<const std::string& Qualifier>
bool
is_qualified(const syntax_nodes::declarator& declarator_node);

syntax_nodes::identifier
get_identifier(const syntax_nodes::declarator& declarator_node);

bool
has_identifier(const syntax_nodes::declarator& declarator_node);

}}}} //namespace scalpel::cpp::detail::semantic_analysis

#include "basic_functions.ipp"

#endif

