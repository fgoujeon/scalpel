/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008, 2009  Florian Goujeon

This file is part of Scalpel.

Scalpel is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Scalpel is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Scalpel.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SCALPEL_CPP_SYNTAX_TREE_HPP
#define SCALPEL_CPP_SYNTAX_TREE_HPP

#include "syntax_nodes/access_specifier.hpp"
#include "syntax_nodes/alternative_node.hpp"
#include "syntax_nodes/assignment_expression.hpp"
#include "syntax_nodes/assignment_operator.hpp"
#include "syntax_nodes/base_clause.hpp"
#include "syntax_nodes/base_specifier.hpp"
#include "syntax_nodes/base_specifier_list.hpp"
#include "syntax_nodes/block_declaration.hpp"
#include "syntax_nodes/boolean_literal.hpp"
#include "syntax_nodes/break_statement.hpp"
#include "syntax_nodes/built_in_type_specifier.hpp"
#include "syntax_nodes/cast_expression.hpp"
#include "syntax_nodes/character_literal.hpp"
#include "syntax_nodes/class_elaborated_specifier.hpp"
#include "syntax_nodes/class_head.hpp"
#include "syntax_nodes/class_key.hpp"
#include "syntax_nodes/class_specifier.hpp"
#include "syntax_nodes/class_template_elaborated_specifier.hpp"
#include "syntax_nodes/common_nodes.hpp"
#include "syntax_nodes/compound_statement.hpp"
#include "syntax_nodes/continue_statement.hpp"
#include "syntax_nodes/conversion_function_id.hpp"
#include "syntax_nodes/ctor_initializer.hpp"
#include "syntax_nodes/cv_qualifier.hpp"
#include "syntax_nodes/decl_specifier.hpp"
#include "syntax_nodes/decl_specifier_seq.hpp"
#include "syntax_nodes/declaration.hpp"
#include "syntax_nodes/declaration_seq.hpp"
#include "syntax_nodes/declarator.hpp"
#include "syntax_nodes/declarator_id.hpp"
#include "syntax_nodes/destructor_name.hpp"
#include "syntax_nodes/direct_declarator.hpp"
#include "syntax_nodes/direct_new_declarator.hpp"
#include "syntax_nodes/elaborated_type_specifier.hpp"
#include "syntax_nodes/enum_elaborated_specifier.hpp"
#include "syntax_nodes/exception_declaration.hpp"
#include "syntax_nodes/exception_specification.hpp"
#include "syntax_nodes/expression.hpp"
#include "syntax_nodes/expression_statement.hpp"
#include "syntax_nodes/expressions.hpp"
#include "syntax_nodes/floating_literal.hpp"
#include "syntax_nodes/function_definition.hpp"
#include "syntax_nodes/function_specifier.hpp"
#include "syntax_nodes/function_try_block.hpp"
#include "syntax_nodes/goto_statement.hpp"
#include "syntax_nodes/id_expression.hpp"
#include "syntax_nodes/identifier.hpp"
#include "syntax_nodes/identifier_or_template_id.hpp"
#include "syntax_nodes/init_declarator.hpp"
#include "syntax_nodes/integer_literal.hpp"
#include "syntax_nodes/iteration_statement.hpp"
#include "syntax_nodes/jump_statement.hpp"
#include "syntax_nodes/labeled_statement.hpp"
#include "syntax_nodes/leaf_node.hpp"
#include "syntax_nodes/mem_initializer.hpp"
#include "syntax_nodes/mem_initializer_id.hpp"
#include "syntax_nodes/mem_initializer_list.hpp"
#include "syntax_nodes/member_declaration.hpp"
#include "syntax_nodes/member_declaration_function_definition.hpp"
#include "syntax_nodes/member_declaration_member_declarator_list.hpp"
#include "syntax_nodes/member_declaration_unqualified_id.hpp"
#include "syntax_nodes/member_declarator.hpp"
#include "syntax_nodes/member_declarator_bit_field_member.hpp"
#include "syntax_nodes/member_declarator_declarator.hpp"
#include "syntax_nodes/member_declarator_list.hpp"
#include "syntax_nodes/member_specification.hpp"
#include "syntax_nodes/member_specification_access_specifier.hpp"
#include "syntax_nodes/namespace_definition.hpp"
#include "syntax_nodes/nested_identifier_or_template_id.hpp"
#include "syntax_nodes/nested_name_specifier.hpp"
#include "syntax_nodes/operator_function_id.hpp"
#include "syntax_nodes/parameter_declaration.hpp"
#include "syntax_nodes/parameter_declaration_clause.hpp"
#include "syntax_nodes/postfix_expression.hpp"
#include "syntax_nodes/primary_expression.hpp"
#include "syntax_nodes/ptr_operator.hpp"
#include "syntax_nodes/ptr_operator_seq.hpp"
#include "syntax_nodes/qualified_id.hpp"
#include "syntax_nodes/qualified_identifier.hpp"
#include "syntax_nodes/qualified_nested_id.hpp"
#include "syntax_nodes/qualified_operator_function_id.hpp"
#include "syntax_nodes/qualified_template_id.hpp"
#include "syntax_nodes/return_statement.hpp"
#include "syntax_nodes/selection_statement.hpp"
#include "syntax_nodes/sequence_node.hpp"
#include "syntax_nodes/simple_declaration.hpp"
#include "syntax_nodes/simple_template_type_specifier.hpp"
#include "syntax_nodes/simple_type_specifier.hpp"
#include "syntax_nodes/space.hpp"
#include "syntax_nodes/statement.hpp"
#include "syntax_nodes/statement_seq.hpp"
#include "syntax_nodes/storage_class_specifier.hpp"
#include "syntax_nodes/string_enumeration_node.hpp"
#include "syntax_nodes/string_literal.hpp"
#include "syntax_nodes/template_argument.hpp"
#include "syntax_nodes/template_argument_list.hpp"
#include "syntax_nodes/template_declaration.hpp"
#include "syntax_nodes/template_id.hpp"
#include "syntax_nodes/translation_unit.hpp"
#include "syntax_nodes/try_block.hpp"
#include "syntax_nodes/type_id.hpp"
#include "syntax_nodes/type_specifier.hpp"
#include "syntax_nodes/typename_elaborated_specifier.hpp"
#include "syntax_nodes/typename_template_elaborated_specifier.hpp"
#include "syntax_nodes/unary_expression.hpp"
#include "syntax_nodes/unqualified_id.hpp"
#include "syntax_nodes/using_declaration.hpp"
#include "syntax_nodes/using_directive.hpp"

namespace scalpel { namespace cpp
{

typedef syntax_nodes::translation_unit syntax_tree;

}} //namespace scalpel::cpp

#endif
