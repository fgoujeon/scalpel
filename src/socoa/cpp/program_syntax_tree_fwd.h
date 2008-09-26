/*
Socoa - Source Code Analysis Library
Copyright © 2008  Florian Goujeon

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

#ifndef SOCOA_CPP_PROGRAM_SYNTAX_TREE_FWD_H
#define SOCOA_CPP_PROGRAM_SYNTAX_TREE_FWD_H

namespace socoa { namespace cpp { namespace program_syntax_tree
{

class identifier;
class id_expression;
class unqualified_id;
class qualified_id;
class qualified_nested_id;
class qualified_operator_function_id;
class qualified_template_id;
class qualified_identifier;
class nested_name_specifier;
class nested_name_specifier_part;
class nested_name_specifier_template_id_part;
class declaration_seq;
class declaration;
class simple_declaration;
class decl_specifier_seq;
class decl_specifier;
class type_specifier;
class simple_type_specifier;
class simple_template_type_specifier;
class built_in_type_specifier;
class identifier_or_template_id;
class namespace_definition;
class using_declaration;
class init_declarator_list;
class init_declarator;
class declarator;
class direct_declarator;
class direct_declarator_function_part;
class direct_declarator_array_part;
class ptr_operator;
class cv_qualifier_seq;
class cv_qualifier;
class declarator_id;
class parameter_declaration_clause;
class parameter_declaration_list;
class parameter_declaration;
class function_definition;
class class_specifier;
class class_head;
class class_key;
class member_specification;
class member_declaration;
class member_declaration_member_declarator_list;
class member_declaration_unqualified_id;
class member_declaration_function_definition;
class member_declarator_list;
class member_declarator;
class member_declarator_declarator;
class member_declarator_bit_field_member;
class access_specifier;
class template_declaration;
class template_id;
class nested_identifier_or_template_id;

}}} //namespace socoa::cpp::program_syntax_tree

#endif
