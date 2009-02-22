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

#ifndef SOCOA_CPP_SYNTAX_TREE_H
#define SOCOA_CPP_SYNTAX_TREE_H

#include "syntax_tree/access_specifier.h"
#include "syntax_tree/assignment_expression.h"
#include "syntax_tree/assignment_operator.h"
#include "syntax_tree/base_clause.h"
#include "syntax_tree/base_specifier.h"
#include "syntax_tree/base_specifier_list.h"
#include "syntax_tree/block_declaration.h"
#include "syntax_tree/built_in_type_specifier.h"
#include "syntax_tree/class_head.h"
#include "syntax_tree/class_key.h"
#include "syntax_tree/class_specifier.h"
#include "syntax_tree/conversion_function_id.h"
#include "syntax_tree/ctor_initializer.h"
#include "syntax_tree/cv_qualifier.h"
#include "syntax_tree/decl_specifier.h"
#include "syntax_tree/decl_specifier_seq.h"
#include "syntax_tree/declaration.h"
#include "syntax_tree/declaration_seq.h"
#include "syntax_tree/declarator.h"
#include "syntax_tree/declarator_id.h"
#include "syntax_tree/destructor_name.h"
#include "syntax_tree/direct_declarator.h"
#include "syntax_tree/direct_declarator_array_part.h"
#include "syntax_tree/direct_declarator_function_part.h"
#include "syntax_tree/direct_declarator_part.h"
#include "syntax_tree/elaborated_type_specifier.h"
#include "syntax_tree/expressions.h"
#include "syntax_tree/function_definition.h"
#include "syntax_tree/function_specifier.h"
#include "syntax_tree/id_expression.h"
#include "syntax_tree/identifier.h"
#include "syntax_tree/identifier_or_template_id.h"
#include "syntax_tree/init_declarator.h"
#include "syntax_tree/mem_initializer.h"
#include "syntax_tree/mem_initializer_id.h"
#include "syntax_tree/mem_initializer_list.h"
#include "syntax_tree/member_declaration.h"
#include "syntax_tree/member_declaration_function_definition.h"
#include "syntax_tree/member_declaration_member_declarator_list.h"
#include "syntax_tree/member_declaration_unqualified_id.h"
#include "syntax_tree/member_declarator.h"
#include "syntax_tree/member_declarator_bit_field_member.h"
#include "syntax_tree/member_declarator_declarator.h"
#include "syntax_tree/member_declarator_list.h"
#include "syntax_tree/member_specification.h"
#include "syntax_tree/member_specification_access_specifier.h"
#include "syntax_tree/member_specification_part.h"
#include "syntax_tree/namespace_definition.h"
#include "syntax_tree/nested_identifier_or_template_id.h"
#include "syntax_tree/nested_name_specifier.h"
#include "syntax_tree/operator_function_id.h"
#include "syntax_tree/parameter_declaration.h"
#include "syntax_tree/parameter_declaration_clause.h"
#include "syntax_tree/ptr_operator.h"
#include "syntax_tree/qualified_id.h"
#include "syntax_tree/qualified_identifier.h"
#include "syntax_tree/qualified_nested_id.h"
#include "syntax_tree/qualified_operator_function_id.h"
#include "syntax_tree/qualified_template_id.h"
#include "syntax_tree/simple_declaration.h"
#include "syntax_tree/simple_template_type_specifier.h"
#include "syntax_tree/simple_type_specifier.h"
#include "syntax_tree/storage_class_specifier.h"
#include "syntax_tree/template_argument.h"
#include "syntax_tree/template_argument_list.h"
#include "syntax_tree/template_declaration.h"
#include "syntax_tree/template_id.h"
#include "syntax_tree/type_id.h"
#include "syntax_tree/type_specifier.h"
#include "syntax_tree/unqualified_id.h"
#include "syntax_tree/using_declaration.h"
#include "syntax_tree/using_directive.h"

namespace socoa { namespace cpp
{

typedef util::sequence<syntax_tree::declaration> syntax_tree_t;

}} //namespace socoa::cpp

#endif
