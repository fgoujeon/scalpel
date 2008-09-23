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

#ifndef SOCOA_CPP_PROGRAM_SYNTAX_TREE_TO_STRING_CONVERTER_H
#define SOCOA_CPP_PROGRAM_SYNTAX_TREE_TO_STRING_CONVERTER_H

#include <string>
#include <sstream>
#include <memory>
#include "program_syntax_tree/visitor.h"
#include "program_syntax_tree_fwd.h"

namespace socoa { namespace cpp
{

class program_syntax_tree_to_string_converter: public program_syntax_tree::visitor
{
    public:
        program_syntax_tree_to_string_converter();

        std::string
        operator()(const std::shared_ptr<program_syntax_tree::declaration_seq> translation_unit);

    private:
        void
        visit(const program_syntax_tree::identifier& item);

        void
        visit(const program_syntax_tree::nested_name_specifier& item);

        void
        visit(const program_syntax_tree::nested_name_specifier_template_id_part& item);

        void
        visit(const program_syntax_tree::declaration_seq& item);

        void
        visit(const program_syntax_tree::namespace_definition& item);

        void
        visit(const program_syntax_tree::using_declaration& item);

        void
        visit(const program_syntax_tree::init_declarator_list& item);

        void
        visit(const program_syntax_tree::init_declarator& item);

        void
        visit(const program_syntax_tree::declarator& item);

        void
        visit(const program_syntax_tree::direct_declarator& item);

        void
        visit(const program_syntax_tree::direct_declarator_function_part& item);

        void
        visit(const program_syntax_tree::direct_declarator_array_part& item);

        void
        visit(const program_syntax_tree::ptr_operator& item);

        void
        visit(const program_syntax_tree::cv_qualifier_seq& item);

        void
        visit(const program_syntax_tree::cv_qualifier& item);

        void
        visit(const program_syntax_tree::declarator_id& item);

        void
        visit(const program_syntax_tree::parameter_declaration_clause& item);

        void
        visit(const program_syntax_tree::parameter_declaration_list& item);

        void
        visit(const program_syntax_tree::parameter_declaration& item);

        void
        visit(const program_syntax_tree::function_definition& item);

        void
        visit(const program_syntax_tree::class_specifier& item);

        void
        visit(const program_syntax_tree::class_head& item);

        void
        visit(const program_syntax_tree::class_key& item);

        void
        visit(const program_syntax_tree::member_specification& item);

        void
        visit(const program_syntax_tree::member_declaration_member_declarator_list& item);

        void
        visit(const program_syntax_tree::member_declaration_unqualified_id& item);

        void
        visit(const program_syntax_tree::member_declaration_function_definition& item);

        void
        visit(const program_syntax_tree::member_declarator_list& item);

        void
        visit(const program_syntax_tree::member_declarator_declarator& item);

        void
        visit(const program_syntax_tree::member_declarator_bit_field_member& item);

        void
        visit(const program_syntax_tree::access_specifier& item);

        void
        visit(const program_syntax_tree::template_declaration& item);

        void
        visit(const program_syntax_tree::simple_declaration& item);

        void
        visit(const program_syntax_tree::decl_specifier_seq& item);

        void
        visit(const program_syntax_tree::simple_type_specifier& item);

        void
        visit(const program_syntax_tree::template_id& item);

        const std::string
        new_line();

        const std::string
        opening_brace();

        const std::string
        closing_brace();

        const std::string
        indentation();

        std::ostringstream m_result;
        unsigned int m_indentation_level;
};

}} //namespace socoa::cpp

#endif
