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

#ifndef SOCOA_CPP_SYNTAX_TREE_HPP
#define SOCOA_CPP_SYNTAX_TREE_HPP

#include "syntax_tree/access_specifier.hpp"
#include "syntax_tree/assignment_expression.hpp"
#include "syntax_tree/assignment_operator.hpp"
#include "syntax_tree/alternative_node.hpp"
#include "syntax_tree/base_clause.hpp"
#include "syntax_tree/base_specifier.hpp"
#include "syntax_tree/base_specifier_list.hpp"
#include "syntax_tree/block_declaration.hpp"
#include "syntax_tree/built_in_type_specifier.hpp"
#include "syntax_tree/cast_expression.hpp"
#include "syntax_tree/class_head.hpp"
#include "syntax_tree/class_key.hpp"
#include "syntax_tree/class_specifier.hpp"
#include "syntax_tree/common_nodes.hpp"
#include "syntax_tree/compound_statement.hpp"
#include "syntax_tree/conversion_function_id.hpp"
#include "syntax_tree/ctor_initializer.hpp"
#include "syntax_tree/cv_qualifier.hpp"
#include "syntax_tree/decl_specifier.hpp"
#include "syntax_tree/decl_specifier_seq.hpp"
#include "syntax_tree/declaration.hpp"
#include "syntax_tree/declaration_seq.hpp"
#include "syntax_tree/declarator.hpp"
#include "syntax_tree/declarator_id.hpp"
#include "syntax_tree/destructor_name.hpp"
#include "syntax_tree/direct_declarator.hpp"
#include "syntax_tree/elaborated_type_specifier.hpp"
#include "syntax_tree/expressions.hpp"
#include "syntax_tree/expression_statement.hpp"
#include "syntax_tree/function_definition.hpp"
#include "syntax_tree/function_specifier.hpp"
#include "syntax_tree/id_expression.hpp"
#include "syntax_tree/identifier.hpp"
#include "syntax_tree/identifier_or_template_id.hpp"
#include "syntax_tree/init_declarator.hpp"
#include "syntax_tree/iteration_statement.hpp"
#include "syntax_tree/jump_statement.hpp"
#include "syntax_tree/labeled_statement.hpp"
#include "syntax_tree/leaf_node.hpp"
#include "syntax_tree/mem_initializer.hpp"
#include "syntax_tree/mem_initializer_id.hpp"
#include "syntax_tree/mem_initializer_list.hpp"
#include "syntax_tree/member_declaration.hpp"
#include "syntax_tree/member_declaration_function_definition.hpp"
#include "syntax_tree/member_declaration_member_declarator_list.hpp"
#include "syntax_tree/member_declaration_unqualified_id.hpp"
#include "syntax_tree/member_declarator.hpp"
#include "syntax_tree/member_declarator_bit_field_member.hpp"
#include "syntax_tree/member_declarator_declarator.hpp"
#include "syntax_tree/member_declarator_list.hpp"
#include "syntax_tree/member_specification.hpp"
#include "syntax_tree/member_specification_access_specifier.hpp"
#include "syntax_tree/namespace_definition.hpp"
#include "syntax_tree/nested_identifier_or_template_id.hpp"
#include "syntax_tree/nested_name_specifier.hpp"
#include "syntax_tree/operator_function_id.hpp"
#include "syntax_tree/parameter_declaration.hpp"
#include "syntax_tree/parameter_declaration_clause.hpp"
#include "syntax_tree/ptr_operator.hpp"
#include "syntax_tree/ptr_operator_seq.hpp"
#include "syntax_tree/qualified_id.hpp"
#include "syntax_tree/qualified_identifier.hpp"
#include "syntax_tree/qualified_nested_id.hpp"
#include "syntax_tree/qualified_operator_function_id.hpp"
#include "syntax_tree/qualified_template_id.hpp"
#include "syntax_tree/selection_statement.hpp"
#include "syntax_tree/sequence_node.hpp"
#include "syntax_tree/simple_declaration.hpp"
#include "syntax_tree/simple_template_type_specifier.hpp"
#include "syntax_tree/simple_type_specifier.hpp"
#include "syntax_tree/statement.hpp"
#include "syntax_tree/statement_seq.hpp"
#include "syntax_tree/space.hpp"
#include "syntax_tree/string_enumeration_node.hpp"
#include "syntax_tree/storage_class_specifier.hpp"
#include "syntax_tree/template_argument.hpp"
#include "syntax_tree/template_argument_list.hpp"
#include "syntax_tree/template_declaration.hpp"
#include "syntax_tree/template_id.hpp"
#include "syntax_tree/try_block.hpp"
#include "syntax_tree/type_id.hpp"
#include "syntax_tree/type_specifier.hpp"
#include "syntax_tree/unqualified_id.hpp"
#include "syntax_tree/using_declaration.hpp"
#include "syntax_tree/using_directive.hpp"

namespace socoa { namespace cpp
{

typedef syntax_tree::declaration_seq syntax_tree_t;

}} //namespace socoa::cpp

#endif
