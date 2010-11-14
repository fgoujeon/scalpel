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

//
//class related
//

semantic_entities::class_::access
get_access(const syntax_nodes::access_specifier access_specifier_node);



//
//function related
//

bool
is_function_declaration(const syntax_nodes::declarator& declarator_node);

bool
is_simple_function_declaration(const syntax_nodes::declarator& declarator_node);

bool
is_operator_function_declaration(const syntax_nodes::declarator& declarator_node);

bool
is_conversion_function_declaration(const syntax_nodes::declarator& declarator_node);

bool
is_destructor_declaration(const syntax_nodes::declarator& declarator_node);

bool
has_pure_specifier(const syntax_nodes::member_declarator_declarator& member_declarator_declarator_node);



//
//simple-declaration related
//

enum simple_declaration_type
{
	EMPTY,
	CLASS_DECLARATION,
	CLASS_FORWARD_DECLARATION,
	SIMPLE_FUNCTION_DECLARATION,
	OPERATOR_FUNCTION_DECLARATION,
	VARIABLE_DECLARATION,
	VARIABLE_STYLE_TYPEDEF_DECLARATION
};

simple_declaration_type
get_simple_declaration_type(const syntax_nodes::simple_declaration& simple_declaration_node);

bool
is_class_declaration(const syntax_nodes::simple_declaration& simple_declaration_node);

bool
is_class_forward_declaration(const syntax_nodes::simple_declaration& simple_declaration_node);

bool
is_simple_function_declaration(const syntax_nodes::simple_declaration& simple_declaration_node);

bool
is_operator_function_declaration(const syntax_nodes::simple_declaration& simple_declaration_node);

bool
is_variable_declaration(const syntax_nodes::simple_declaration& simple_declaration_node);



//
//qualifier related
//

template<const std::string& Qualifier>
bool
is_qualified(const syntax_nodes::declarator& declarator_node);



//
//specifier related
//

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



//
//common
//

syntax_nodes::identifier
get_identifier(const syntax_nodes::declarator& declarator_node);

bool
has_identifier(const syntax_nodes::declarator& declarator_node);

}}}} //namespace scalpel::cpp::detail::semantic_analysis

#include "basic_functions.ipp"

#endif

