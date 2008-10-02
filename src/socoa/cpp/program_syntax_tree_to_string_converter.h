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
#include <vector>
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
        operator()(const std::shared_ptr<program_syntax_tree::sequence<program_syntax_tree::declaration>> translation_unit);

    private:
        void
        visit(const program_syntax_tree::identifier& item);

        void
        visit(const program_syntax_tree::qualified_nested_id& item);

        void
        visit(const program_syntax_tree::qualified_operator_function_id& item);

        void
        visit(const program_syntax_tree::qualified_template_id& item);

        void
        visit(const program_syntax_tree::qualified_identifier& item);

        void
        visit(const program_syntax_tree::nested_name_specifier& item);

        void
        visit(const program_syntax_tree::nested_name_specifier_template_id_part& item);

        void
        visit(const program_syntax_tree::simple_template_type_specifier& item);

        void
        visit(const program_syntax_tree::built_in_type_specifier& item);

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
        visit(const program_syntax_tree::cv_qualifier& item);

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
        visit(const program_syntax_tree::member_specification& item);

        void
        visit(const program_syntax_tree::member_specification_access_specifier& item);

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
        visit(const program_syntax_tree::template_declaration& item);

        void
        visit(const program_syntax_tree::simple_declaration& item);

        void
        visit(const program_syntax_tree::template_id& item);

        void
        visit(const program_syntax_tree::template_argument_list& item);

        void
        visit(const program_syntax_tree::nested_identifier_or_template_id& item);

        template<class T>
        void
        visit(const program_syntax_tree::sequence<T>& seq);

        template<class T>
        void
        visit(const T& a_string_enumeration);

        template<class T>
        inline
        void
        safe_convert(T item);

        template<class T>
        void
        safe_convert(std::shared_ptr<T> item);

        void
        add_space();

        const std::string
        new_line();

        const std::string
        opening_brace();

        const std::string
        closing_brace();

        const std::string
        indentation();

        std::ostringstream result_;
        unsigned int m_indentation_level;
};

template <class T>
void
program_syntax_tree_to_string_converter::visit(const program_syntax_tree::sequence<T>& seq)
{
    typedef std::vector<std::shared_ptr<T>> item_list_t;

    for(typename item_list_t::const_iterator i = seq.get_items().begin(); i != seq.get_items().end(); ++i)
    {
        if(*i)
            (**i).accept(*this);
    }
}

template<class T>
void
program_syntax_tree_to_string_converter::visit(const T& a_string_enumeration)
{
    result_ << a_string_enumeration.get_value();
}

template <class T>
void
program_syntax_tree_to_string_converter::safe_convert(T item)
{
    visit(item);
}

template<class T>
void
program_syntax_tree_to_string_converter::safe_convert(std::shared_ptr<T> item)
{
    if(item)
        visit(*item);
}

}} //namespace socoa::cpp

#endif
