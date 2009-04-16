/*
Socoa - Source Code Analysis Library
Copyright © 2008, 2009  Florian Goujeon

This file is part of Socoa.

Socoa is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Socoa is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Socoa.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SOCOA_CPP_PARSE_TREE_TO_SYNTAX_TREE_CONVERT_FUNCTIONS_HPP
#define SOCOA_CPP_PARSE_TREE_TO_SYNTAX_TREE_CONVERT_FUNCTIONS_HPP

#include "../syntax_tree.hpp"
#include "typedefs.hpp"

namespace socoa { namespace cpp { namespace parse_tree_to_syntax_tree
{

syntax_tree::identifier
convert_identifier(const tree_node_t& node);

syntax_tree::id_expression
convert_id_expression(const tree_node_t& node);

syntax_tree::unqualified_id
convert_unqualified_id(const tree_node_t& node);

syntax_tree::qualified_id
convert_qualified_id(const tree_node_t& node);

syntax_tree::qualified_nested_id
convert_qualified_nested_id(const tree_node_t& node);

syntax_tree::qualified_operator_function_id
convert_qualified_operator_function_id(const tree_node_t& node);

syntax_tree::qualified_template_id
convert_qualified_template_id(const tree_node_t& node);

syntax_tree::qualified_identifier
convert_qualified_identifier(const tree_node_t& node);

syntax_tree::nested_name_specifier
convert_nested_name_specifier(const tree_node_t& node);

syntax_tree::nested_name_specifier::second_part
convert_nested_name_specifier_second_part(const tree_node_t& node);

syntax_tree::declaration
convert_declaration(const tree_node_t& node);

syntax_tree::block_declaration
convert_block_declaration(const tree_node_t& node);

syntax_tree::simple_declaration
convert_simple_declaration(const tree_node_t& node);

syntax_tree::decl_specifier
convert_decl_specifier(const tree_node_t& node);

syntax_tree::type_specifier
convert_type_specifier(const tree_node_t& node);

syntax_tree::simple_type_specifier
convert_simple_type_specifier(const tree_node_t& node);

syntax_tree::simple_template_type_specifier
convert_simple_template_type_specifier(const tree_node_t& node);

syntax_tree::identifier_or_template_id
convert_identifier_or_template_id(const tree_node_t& node);

syntax_tree::namespace_definition
convert_namespace_definition(const tree_node_t& node);

syntax_tree::using_declaration
convert_using_declaration(const tree_node_t& node);

syntax_tree::using_directive
convert_using_directive(const tree_node_t& node);

syntax_tree::init_declarator
convert_init_declarator(const tree_node_t& node);

syntax_tree::declarator
convert_declarator(const tree_node_t& node);

syntax_tree::direct_declarator
convert_direct_declarator(const tree_node_t& node);

syntax_tree::direct_declarator::function_part
convert_direct_declarator_function_part(const tree_node_t& node);

syntax_tree::direct_declarator::array_part
convert_direct_declarator_array_part(const tree_node_t& node);

syntax_tree::ptr_operator
convert_ptr_operator(const tree_node_t& node);

syntax_tree::cv_qualifier
convert_cv_qualifier(const tree_node_t& node);

syntax_tree::declarator_id
convert_declarator_id(const tree_node_t& node);

syntax_tree::parameter_declaration_clause
convert_parameter_declaration_clause(const tree_node_t& node);

syntax_tree::parameter_declaration
convert_parameter_declaration(const tree_node_t& node);

syntax_tree::function_definition
convert_function_definition(const tree_node_t& node);

syntax_tree::class_specifier
convert_class_specifier(const tree_node_t& node);

syntax_tree::class_head
convert_class_head(const tree_node_t& node);

syntax_tree::member_specification
convert_member_specification(const tree_node_t& node);

syntax_tree::member_specification_access_specifier
convert_member_specification_access_specifier(const tree_node_t& node);

syntax_tree::member_declaration
convert_member_declaration(const tree_node_t& node);

syntax_tree::member_declaration_member_declarator_list
convert_member_declaration_member_declarator_list(const tree_node_t& node);

syntax_tree::member_declaration_unqualified_id
convert_member_declaration_unqualified_id(const tree_node_t& node);

syntax_tree::member_declaration_function_definition
convert_member_declaration_function_definition(const tree_node_t& node);

syntax_tree::member_declarator
convert_member_declarator(const tree_node_t& node);

syntax_tree::member_declarator_declarator
convert_member_declarator_declarator(const tree_node_t& node);

syntax_tree::member_declarator_bit_field_member
convert_member_declarator_bit_field_member(const tree_node_t& node);

syntax_tree::base_clause
convert_base_clause(const tree_node_t& node);

syntax_tree::base_specifier
convert_base_specifier(const tree_node_t& node);

syntax_tree::ctor_initializer
convert_ctor_initializer(const tree_node_t& node);

syntax_tree::mem_initializer
convert_mem_initializer(const tree_node_t& node);

syntax_tree::mem_initializer_id
convert_mem_initializer_id(const tree_node_t& node);

syntax_tree::template_declaration
convert_template_declaration(const tree_node_t& node);

syntax_tree::template_id
convert_template_id(const tree_node_t& node);

syntax_tree::template_argument
convert_template_argument(const tree_node_t& node);

syntax_tree::nested_identifier_or_template_id
convert_nested_identifier_or_template_id(const tree_node_t& node);

syntax_tree::elaborated_type_specifier
convert_elaborated_type_specifier(const tree_node_t& node);

syntax_tree::destructor_name
convert_destructor_name(const tree_node_t& node);

syntax_tree::operator_function_id
convert_operator_function_id(const tree_node_t& node);

syntax_tree::conversion_function_id
convert_conversion_function_id(const tree_node_t& node);

syntax_tree::space
convert_space(const tree_node_t& node);

}}} //namespace socoa::cpp

#endif
