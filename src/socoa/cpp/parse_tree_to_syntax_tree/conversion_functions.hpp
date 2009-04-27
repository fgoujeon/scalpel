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

syntax_nodes::arrow_id_expression
convert_arrow_id_expression(const tree_node_t& node);

syntax_nodes::arrow_pseudo_destructor_name
convert_arrow_pseudo_destructor_name(const tree_node_t& node);

syntax_nodes::assignment_expression::first_part
convert_assignment_expression_first_part(const tree_node_t& node);

syntax_nodes::assignment_expression
convert_assignment_expression(const tree_node_t& node);

syntax_nodes::assignment_expression_condition
convert_assignment_expression_condition(const tree_node_t& node);

syntax_nodes::base_clause
convert_base_clause(const tree_node_t& node);

syntax_nodes::base_specifier
convert_base_specifier(const tree_node_t& node);

syntax_nodes::block_declaration
convert_block_declaration(const tree_node_t& node);

syntax_nodes::boolean_literal
convert_boolean_literal(const tree_node_t& node);

syntax_nodes::bracketed_expression_list
convert_bracketed_expression_list(const tree_node_t& node);

syntax_nodes::bracketed_initializer
convert_bracketed_initializer(const tree_node_t& node);

syntax_nodes::break_statement
convert_break_statement(const tree_node_t& node);

syntax_nodes::case_statement
convert_case_statement(const tree_node_t& node);

syntax_nodes::cast_expression
convert_cast_expression(const tree_node_t& node);

syntax_nodes::character_literal
convert_character_literal(const tree_node_t& node);

syntax_nodes::class_head
convert_class_head(const tree_node_t& node);

syntax_nodes::class_specifier
convert_class_specifier(const tree_node_t& node);

syntax_nodes::classic_labeled_statement
convert_classic_labeled_statement(const tree_node_t& node);

syntax_nodes::compound_statement
convert_compound_statement(const tree_node_t& node);

syntax_nodes::condition
convert_condition(const tree_node_t& node);

syntax_nodes::conditional_expression
convert_conditional_expression(const tree_node_t& node);

syntax_nodes::const_cast_expression
convert_const_cast_expression(const tree_node_t& node);

syntax_nodes::continue_statement
convert_continue_statement(const tree_node_t& node);

syntax_nodes::conversion_function_id
convert_conversion_function_id(const tree_node_t& node);

syntax_nodes::ctor_initializer
convert_ctor_initializer(const tree_node_t& node);

syntax_nodes::cv_qualifier
convert_cv_qualifier(const tree_node_t& node);

syntax_nodes::decl_specifier
convert_decl_specifier(const tree_node_t& node);

syntax_nodes::declaration
convert_declaration(const tree_node_t& node);

syntax_nodes::declarator
convert_declarator(const tree_node_t& node);

syntax_nodes::declarator_id
convert_declarator_id(const tree_node_t& node);

syntax_nodes::default_statement
convert_default_statement(const tree_node_t& node);

syntax_nodes::delete_expression
convert_delete_expression(const tree_node_t& node);

syntax_nodes::destructor_name
convert_destructor_name(const tree_node_t& node);

syntax_nodes::direct_declarator::array_part
convert_direct_declarator_array_part(const tree_node_t& node);

syntax_nodes::direct_declarator::function_part
convert_direct_declarator_function_part(const tree_node_t& node);

syntax_nodes::direct_declarator::next_part
convert_direct_declarator_next_part(const tree_node_t& node);

syntax_nodes::direct_declarator
convert_direct_declarator(const tree_node_t& node);

syntax_nodes::do_while_statement
convert_do_while_statement(const tree_node_t& node);

syntax_nodes::dot_id_expression
convert_dot_id_expression(const tree_node_t& node);

syntax_nodes::dot_pseudo_destructor_name
convert_dot_pseudo_destructor_name(const tree_node_t& node);

syntax_nodes::dynamic_cast_expression
convert_dynamic_cast_expression(const tree_node_t& node);

syntax_nodes::elaborated_type_specifier
convert_elaborated_type_specifier(const tree_node_t& node);

syntax_nodes::empty_initializer_list_initializer_clause
convert_empty_initializer_list_initializer_clause(const tree_node_t& node);

syntax_nodes::equal_initializer
convert_equal_initializer(const tree_node_t& node);

syntax_nodes::exception_abstract_declarator
convert_exception_abstract_declarator(const tree_node_t& node);

syntax_nodes::exception_declaration
convert_exception_declaration(const tree_node_t& node);

syntax_nodes::exception_declarator
convert_exception_declarator(const tree_node_t& node);

syntax_nodes::expression_statement
convert_expression_statement(const tree_node_t& node);

syntax_nodes::floating_literal
convert_floating_literal(const tree_node_t& node);

syntax_nodes::for_init_statement
convert_for_init_statement(const tree_node_t& node);

syntax_nodes::for_statement
convert_for_statement(const tree_node_t& node);

syntax_nodes::function_definition
convert_function_definition(const tree_node_t& node);

syntax_nodes::goto_statement
convert_goto_statement(const tree_node_t& node);

syntax_nodes::handler
convert_handler(const tree_node_t& node);

syntax_nodes::id_expression
convert_id_expression(const tree_node_t& node);

syntax_nodes::identifier
convert_identifier(const tree_node_t& node);

syntax_nodes::identifier_or_template_id
convert_identifier_or_template_id(const tree_node_t& node);

syntax_nodes::if_statement
convert_if_statement(const tree_node_t& node);

syntax_nodes::init_declarator
convert_init_declarator(const tree_node_t& node);

syntax_nodes::initializer
convert_initializer(const tree_node_t& node);

syntax_nodes::initializer_clause
convert_initializer_clause(const tree_node_t& node);

syntax_nodes::initializer_list_initializer_clause
convert_initializer_list_initializer_clause(const tree_node_t& node);

syntax_nodes::integer_literal
convert_integer_literal(const tree_node_t& node);

syntax_nodes::iteration_statement
convert_iteration_statement(const tree_node_t& node);

syntax_nodes::jump_statement
convert_jump_statement(const tree_node_t& node);

syntax_nodes::labeled_statement
convert_labeled_statement(const tree_node_t& node);

syntax_nodes::literal
convert_literal(const tree_node_t& node);

syntax_nodes::mem_initializer
convert_mem_initializer(const tree_node_t& node);

syntax_nodes::mem_initializer_id
convert_mem_initializer_id(const tree_node_t& node);

syntax_nodes::member_declaration
convert_member_declaration(const tree_node_t& node);

syntax_nodes::member_declaration_function_definition
convert_member_declaration_function_definition(const tree_node_t& node);

syntax_nodes::member_declaration_member_declarator_list
convert_member_declaration_member_declarator_list(const tree_node_t& node);

syntax_nodes::member_declaration_unqualified_id
convert_member_declaration_unqualified_id(const tree_node_t& node);

syntax_nodes::member_declarator
convert_member_declarator(const tree_node_t& node);

syntax_nodes::member_declarator_bit_field_member
convert_member_declarator_bit_field_member(const tree_node_t& node);

syntax_nodes::member_declarator_declarator
convert_member_declarator_declarator(const tree_node_t& node);

syntax_nodes::member_specification_access_specifier
convert_member_specification_access_specifier(const tree_node_t& node);

syntax_nodes::member_specification_part
convert_member_specification_part(const tree_node_t& node);

syntax_nodes::namespace_definition
convert_namespace_definition(const tree_node_t& node);

syntax_nodes::nested_identifier_or_template_id
convert_nested_identifier_or_template_id(const tree_node_t& node);

syntax_nodes::nested_name_specifier::next_part
convert_nested_name_specifier_next_part(const tree_node_t& node);

syntax_nodes::nested_name_specifier
convert_nested_name_specifier(const tree_node_t& node);

syntax_nodes::new_expression
convert_new_expression(const tree_node_t& node);

syntax_nodes::operator_function_id
convert_operator_function_id(const tree_node_t& node);

syntax_nodes::parameter_declaration
convert_parameter_declaration(const tree_node_t& node);

syntax_nodes::parameter_declaration_clause
convert_parameter_declaration_clause(const tree_node_t& node);

syntax_nodes::postfix_expression::first_part
convert_postfix_expression_first_part(const tree_node_t& node);

syntax_nodes::postfix_expression::last_part
convert_postfix_expression_last_part(const tree_node_t& node);

syntax_nodes::postfix_expression
convert_postfix_expression(const tree_node_t& node);

syntax_nodes::primary_expression
convert_primary_expression(const tree_node_t& node);

syntax_nodes::ptr_operator
convert_ptr_operator(const tree_node_t& node);

syntax_nodes::qualified_id
convert_qualified_id(const tree_node_t& node);

syntax_nodes::qualified_identifier
convert_qualified_identifier(const tree_node_t& node);

syntax_nodes::qualified_nested_id
convert_qualified_nested_id(const tree_node_t& node);

syntax_nodes::qualified_operator_function_id
convert_qualified_operator_function_id(const tree_node_t& node);

syntax_nodes::qualified_template_id
convert_qualified_template_id(const tree_node_t& node);

syntax_nodes::reinterpret_cast_expression
convert_reinterpret_cast_expression(const tree_node_t& node);

syntax_nodes::return_statement
convert_return_statement(const tree_node_t& node);

syntax_nodes::round_bracketed_expression
convert_round_bracketed_expression(const tree_node_t& node);

syntax_nodes::selection_statement
convert_selection_statement(const tree_node_t& node);

syntax_nodes::simple_declaration
convert_simple_declaration(const tree_node_t& node);

syntax_nodes::simple_template_type_specifier
convert_simple_template_type_specifier(const tree_node_t& node);

syntax_nodes::simple_type_specifier
convert_simple_type_specifier(const tree_node_t& node);

syntax_nodes::simple_type_specifier_postfix_expression
convert_simple_type_specifier_postfix_expression(const tree_node_t& node);

syntax_nodes::space
convert_space(const tree_node_t& node);

syntax_nodes::square_bracketed_expression
convert_square_bracketed_expression(const tree_node_t& node);

syntax_nodes::statement
convert_statement(const tree_node_t& node);

syntax_nodes::static_cast_expression
convert_static_cast_expression(const tree_node_t& node);

syntax_nodes::string_literal
convert_string_literal(const tree_node_t& node);

syntax_nodes::switch_statement
convert_switch_statement(const tree_node_t& node);

syntax_nodes::template_argument
convert_template_argument(const tree_node_t& node);

syntax_nodes::template_declaration
convert_template_declaration(const tree_node_t& node);

syntax_nodes::template_id
convert_template_id(const tree_node_t& node);

syntax_nodes::template_typename_expression
convert_template_typename_expression(const tree_node_t& node);

syntax_nodes::throw_expression
convert_throw_expression(const tree_node_t& node);

syntax_nodes::translation_unit
convert_translation_unit(const tree_node_t& node);

syntax_nodes::try_block
convert_try_block(const tree_node_t& node);

syntax_nodes::type_id_sizeof_expression
convert_type_id_sizeof_expression(const tree_node_t& node);

syntax_nodes::type_id_typeid_expression
convert_type_id_typeid_expression(const tree_node_t& node);

syntax_nodes::type_specifier
convert_type_specifier(const tree_node_t& node);

syntax_nodes::typeid_expression
convert_typeid_expression(const tree_node_t& node);

syntax_nodes::typename_expression
convert_typename_expression(const tree_node_t& node);

syntax_nodes::unary_expression
convert_unary_expression(const tree_node_t& node);

syntax_nodes::unary_operator_unary_expression
convert_unary_operator_unary_expression(const tree_node_t& node);

syntax_nodes::unary_sizeof_expression
convert_unary_sizeof_expression(const tree_node_t& node);

syntax_nodes::unqualified_id
convert_unqualified_id(const tree_node_t& node);

syntax_nodes::using_declaration
convert_using_declaration(const tree_node_t& node);

syntax_nodes::using_directive
convert_using_directive(const tree_node_t& node);

syntax_nodes::while_statement
convert_while_statement(const tree_node_t& node);

}}} //namespace socoa::cpp

#endif
