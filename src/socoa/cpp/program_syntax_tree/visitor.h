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

#ifndef SOCOA_CPP_PROGRAM_SYNTAX_TREE_VISITOR_H
#define SOCOA_CPP_PROGRAM_SYNTAX_TREE_VISITOR_H

namespace socoa { namespace cpp { namespace program_syntax_tree
{

class identifier;
class qualified_nested_id;
class qualified_operator_function_id;
class qualified_template_id;
class qualified_identifier;
class nested_name_specifier_template_id_part;
class simple_template_type_specifier;
class built_in_type_specifier;
class namespace_definition;
class using_declaration;
class using_directive;
class function_definition;
class class_specifier;
class member_specification_access_specifier;
class member_declaration_member_declarator_list;
class member_declaration_unqualified_id;
class member_declaration_function_definition;
class member_declarator_declarator;
class member_declarator_bit_field_member;
class template_declaration;
class simple_declaration;
class direct_declarator_function_part;
class direct_declarator_array_part;
class template_id;
class cv_qualifier;
class nested_identifier_or_template_id;

class visitor
{
    public:
        virtual ~visitor(){};

        virtual void
        visit(const identifier&) = 0;

        virtual void
        visit(const qualified_nested_id&) = 0;

        virtual void
        visit(const qualified_operator_function_id&) = 0;

        virtual void
        visit(const qualified_template_id&) = 0;

        virtual void
        visit(const qualified_identifier&) = 0;

        virtual void
        visit(const nested_name_specifier_template_id_part&) = 0;

        virtual void
        visit(const simple_template_type_specifier&) = 0;

        virtual void
        visit(const built_in_type_specifier&) = 0;

        virtual void
        visit(const namespace_definition&) = 0;

        virtual void
        visit(const using_declaration&) = 0;

        virtual void
        visit(const using_directive&) = 0;

        virtual void
        visit(const class_specifier&) = 0;

        virtual void
        visit(const member_specification_access_specifier&) = 0;

        virtual void
        visit(const member_declaration_member_declarator_list&) = 0;

        virtual void
        visit(const member_declaration_unqualified_id&) = 0;

        virtual void
        visit(const member_declaration_function_definition&) = 0;

        virtual void
        visit(const member_declarator_declarator&) = 0;

        virtual void
        visit(const member_declarator_bit_field_member&) = 0;

        virtual void
        visit(const template_declaration&) = 0;

        virtual void
        visit(const simple_declaration&) = 0;

        virtual void
        visit(const function_definition&) = 0;

        virtual void
        visit(const direct_declarator_function_part&) = 0;

        virtual void
        visit(const direct_declarator_array_part&) = 0;

        virtual void
        visit(const template_id&) = 0;

        virtual void
        visit(const cv_qualifier&) = 0;

        virtual void
        visit(const nested_identifier_or_template_id&) = 0;
};

}}} //namespace socoa::cpp::program_syntax_tree

#endif
