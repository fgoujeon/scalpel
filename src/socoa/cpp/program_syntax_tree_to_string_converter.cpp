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

#include <cassert>
#include "program_syntax_tree_to_string_converter.h"
#include "program_syntax_tree.h"

namespace socoa { namespace cpp
{

using namespace program_syntax_tree;

program_syntax_tree_to_string_converter::program_syntax_tree_to_string_converter():
    m_indentation_level(0)
{
}

std::string
program_syntax_tree_to_string_converter::operator()(const std::shared_ptr<program_syntax_tree::sequence<declaration>> translation_unit)
{
    result_.str("");
    m_indentation_level = 0;
    safe_convert(*translation_unit);
    return result_.str();
}

void
program_syntax_tree_to_string_converter::visit(const identifier& item)
{
    add_space();
    result_ << item.get_value();
}

void
program_syntax_tree_to_string_converter::visit(const qualified_nested_id& item)
{
    if(item.has_leading_double_colon())
        result_ << "::";

    safe_convert(item.get_nested_name_specifier());

    if(item.has_template_keyword())
        result_ << "template ";

    item.get_unqualified_id()->accept(*this);
}

void
program_syntax_tree_to_string_converter::visit(const qualified_operator_function_id& item)
{
    result_ << "::";

    result_ << "[NOT IMPLEMENTED]";
}

void
program_syntax_tree_to_string_converter::visit(const qualified_template_id& item)
{
    result_ << "::";
    safe_convert(item.get_template_id());
}

void
program_syntax_tree_to_string_converter::visit(const qualified_identifier& item)
{
    result_ << "::";
    safe_convert(item.get_identifier());
}

void
program_syntax_tree_to_string_converter::visit(const nested_name_specifier& item)
{
    item.get_identifier_or_template_id()->accept(*this);
    result_ << "::";
    for
    (
        std::vector<std::shared_ptr<nested_name_specifier_part>>::const_iterator i = item.get_other_parts().begin();
        i != item.get_other_parts().end();
        ++i
    )
    {
        (**i).accept(*this);
        result_ << "::";
    }
}

void
program_syntax_tree_to_string_converter::visit(const nested_name_specifier_template_id_part& item)
{
    if(item.has_template_keyword())
        result_ << "template ";

    safe_convert(item.get_template_id());
}

void
program_syntax_tree_to_string_converter::visit(const simple_template_type_specifier& item)
{
    if(item.has_leading_double_colon())
        result_ << "::";

    safe_convert(item.get_nested_name_specifier());

    result_ << "template ";
    safe_convert(item.get_template_id());
}

void
program_syntax_tree_to_string_converter::visit(const built_in_type_specifier& item)
{
    add_space();

    switch(item.get_type())
    {
        case built_in_type_specifier::CHAR:
            result_ << "char";
            break;
        case built_in_type_specifier::WCHAR_T:
            result_ << "wchar_t";
            break;
        case built_in_type_specifier::BOOL:
            result_ << "bool";
            break;
        case built_in_type_specifier::SHORT:
            result_ << "short";
            break;
        case built_in_type_specifier::INT:
            result_ << "int";
            break;
        case built_in_type_specifier::LONG:
            result_ << "long";
            break;
        case built_in_type_specifier::SIGNED:
            result_ << "signed";
            break;
        case built_in_type_specifier::UNSIGNED:
            result_ << "unsigned";
            break;
        case built_in_type_specifier::FLOAT:
            result_ << "float";
            break;
        case built_in_type_specifier::DOUBLE:
            result_ << "double";
            break;
        case built_in_type_specifier::VOID:
            result_ << "void";
            break;
    }
}

void
program_syntax_tree_to_string_converter::visit(const namespace_definition& item)
{
    result_ << indentation();
    result_ << "namespace ";

    safe_convert(item.get_identifier());

    result_ << opening_brace();

    safe_convert(item.get_declaration_seq());

    result_ << closing_brace() << new_line();
}

void
program_syntax_tree_to_string_converter::visit(const using_declaration& item)
{
    result_ << indentation();
    result_ << "using ";

    if(item.has_typename_keyword())
        result_ << "typename ";

    if(item.has_leading_double_colon())
        result_ << "::";

    safe_convert(item.get_nested_name_specifier());

    item.get_unqualified_id()->accept(*this);

    result_ << ";";
    result_ << new_line();
}

void
program_syntax_tree_to_string_converter::visit(const init_declarator_list& item)
{
    const std::vector<std::shared_ptr<init_declarator>>& init_declarators = item.get_init_declarators();
    for(std::vector<std::shared_ptr<init_declarator>>::const_iterator i = init_declarators.begin(); i != init_declarators.end(); ++i)
    {
        const init_declarator& init_decl = **i;
        safe_convert(init_decl);
    }
}

void
program_syntax_tree_to_string_converter::visit(const init_declarator& item)
{
    safe_convert(item.get_declarator());
}

void
program_syntax_tree_to_string_converter::visit(const declarator& item)
{
    const std::vector<std::shared_ptr<ptr_operator>>& ptr_operators = item.get_ptr_operators();
    for(std::vector<std::shared_ptr<ptr_operator>>::const_iterator i = ptr_operators.begin(); i != ptr_operators.end(); ++i)
    {
        safe_convert(**i);
    }

    safe_convert(item.get_direct_declarator());
}

void
program_syntax_tree_to_string_converter::visit(const direct_declarator& item)
{
    const std::shared_ptr<declarator_id> a_declarator_id = item.get_declarator_id();
    if(a_declarator_id)
    {
        a_declarator_id->accept(*this);
    }

    const std::shared_ptr<declarator> a_declarator = item.get_declarator();
    if(a_declarator)
    {
        result_ << '(';
        safe_convert(*a_declarator);
        result_ << ')';
    }

    const std::vector<std::shared_ptr<direct_declarator_part>>& other_parts = item.get_other_parts();
    for
    (
        std::vector<std::shared_ptr<direct_declarator_part>>::const_iterator i = other_parts.begin();
        i != other_parts.end();
        ++i
    )
    {
        (**i).accept(*this);
    }
}

void
program_syntax_tree_to_string_converter::visit(const direct_declarator_function_part& item)
{
    result_ << '(';
    safe_convert(item.get_parameter_declaration_clause());
    result_ << ')';
}

void
program_syntax_tree_to_string_converter::visit(const direct_declarator_array_part& item)
{
    result_ << '[';

    result_ << ']';
}

void
program_syntax_tree_to_string_converter::visit(const ptr_operator& item)
{
    if(item.has_leading_double_colon())
        result_ << "::";

    switch(item.get_type())
    {
        case ptr_operator::ASTERISK:
            result_ << '*';
            break;
        case ptr_operator::AMPERSAND:
            result_ << '&';
            break;
    }

    safe_convert(item.get_cv_qualifier_seq());
}

void
program_syntax_tree_to_string_converter::visit(const cv_qualifier& item)
{
    add_space();

    switch(item.get_type())
    {
        case cv_qualifier::CONST:
            result_ << "const";
            break;
        case cv_qualifier::VOLATILE:
            result_ << "volatile";
            break;
        case cv_qualifier::RESTRICT:
            result_ << "__restrict__";
            break;
    }
}

void
program_syntax_tree_to_string_converter::visit(const parameter_declaration_clause& item)
{
    safe_convert(item.get_parameter_declaration_list());

    if(item.has_trailing_comma())
        result_ << ", ";

    if(item.has_ellipsis())
        result_ << "...";
}

void
program_syntax_tree_to_string_converter::visit(const parameter_declaration_list& item)
{
    const std::vector<std::shared_ptr<parameter_declaration>> parameter_declarations = item.get_parameter_declarations();
    for
    (
        std::vector<std::shared_ptr<parameter_declaration>>::const_iterator i = parameter_declarations.begin();
        i != parameter_declarations.end();
        ++i
    )
    {
        if(i != parameter_declarations.begin())
            result_ << ", ";
        safe_convert(**i);
    }
}

void
program_syntax_tree_to_string_converter::visit(const parameter_declaration& item)
{
    safe_convert(item.get_decl_specifier_seq());
    safe_convert(item.get_declarator());
}

void
program_syntax_tree_to_string_converter::visit(const function_definition& item)
{
    result_ << indentation();

    safe_convert(item.get_decl_specifier_seq());

    safe_convert(item.get_declarator());
    result_ << opening_brace();

    result_ << closing_brace();
    result_ << new_line();
}

void
program_syntax_tree_to_string_converter::visit(const class_specifier& item)
{
    //result_ << indentation();
    safe_convert(item.get_head());

    result_ << opening_brace();

    safe_convert(item.get_member_specification());

    result_ << closing_brace();
}

void
program_syntax_tree_to_string_converter::visit(const class_head& item)
{
    safe_convert(item.get_key());

    safe_convert(item.get_nested_name_specifier());
    safe_convert(item.get_template_id());
    safe_convert(item.get_identifier());
}

void
program_syntax_tree_to_string_converter::visit(const member_specification& item)
{
    for
    (
        std::vector<std::shared_ptr<member_specification_part>>::const_iterator i = item.get_parts().begin();
        i != item.get_parts().end();
        ++i
    )
    {
        assert(*i);
        (**i).accept(*this);
    }
}

void
program_syntax_tree_to_string_converter::visit(const member_specification_access_specifier& item)
{
    result_ << indentation();
    safe_convert(item.get_access_specifier());
    result_ << ":" << new_line();
}

void
program_syntax_tree_to_string_converter::visit(const member_declaration_member_declarator_list& item)
{
    result_ << indentation();

    safe_convert(item.get_decl_specifier_seq());
    safe_convert(item.get_member_declarator_list());

    result_ << ";" << new_line();
}

void
program_syntax_tree_to_string_converter::visit(const member_declaration_unqualified_id& item)
{
    result_ << indentation();

    if(item.has_leading_double_colon())
        result_ << "::";

    safe_convert(item.get_nested_name_specifier());

    if(item.has_template_keyword())
        result_ << "template ";

    item.get_unqualified_id()->accept(*this);

    result_ << ";" << new_line();
}

void
program_syntax_tree_to_string_converter::visit(const member_declaration_function_definition& item)
{
    safe_convert(item.get_function_definition());
}

void
program_syntax_tree_to_string_converter::visit(const member_declarator_list& item)
{
    for
    (
        std::vector<std::shared_ptr<member_declarator>>::const_iterator i = item.get_member_declarators().begin();
        i != item.get_member_declarators().end();
        ++i
    )
    {
        (**i).accept(*this);
    }
}

void
program_syntax_tree_to_string_converter::visit(const member_declarator_declarator& item)
{
    //result_ << indentation();

    safe_convert(item.get_declarator());

    if(item.has_pure_specifier())
        result_ << " = 0";
}

void
program_syntax_tree_to_string_converter::visit(const member_declarator_bit_field_member& item)
{
    safe_convert(item.get_identifier());

    result_ << ": ";
}

void
program_syntax_tree_to_string_converter::visit(const template_declaration& item)
{
    result_ << indentation();

    if(item.has_export_keyword())
        result_ << "export ";

    result_ << "template";
    result_ << "<";
    result_ << ">\n";

    item.get_declaration()->accept(*this);
}

void
program_syntax_tree_to_string_converter::visit(const simple_declaration& item)
{
    result_ << indentation();

    safe_convert(item.get_decl_specifier_seq());
    safe_convert(item.get_init_declarator_list());

    result_ << ";" << new_line();
}

void
program_syntax_tree_to_string_converter::visit(const template_id& item)
{
    safe_convert(item.get_identifier());
    result_ << "<";
    safe_convert(item.get_template_argument_list());
    result_ << ">";
}

void
program_syntax_tree_to_string_converter::visit(const template_argument_list& item)
{
    for
    (
        std::vector<std::shared_ptr<template_argument>>::const_iterator i = item.get_arguments().begin();
        i != item.get_arguments().end();
        ++i
    )
    {
        if(i != item.get_arguments().begin())
            result_ << ", ";

        if(*i)
            (**i).accept(*this);
    }
}

void
program_syntax_tree_to_string_converter::visit(const nested_identifier_or_template_id& item)
{
    if(item.has_leading_double_colon())
        result_ << "::";

    safe_convert(item.get_nested_name_specifier());

    item.get_identifier_or_template_id()->accept(*this);
}

void
program_syntax_tree_to_string_converter::add_space()
{
    if(result_.str().size() > 0)
    {
        //get last character added to result
        const char last_char = *result_.str().rbegin();

        //if last char is neither a white space or a punctuation sign, let's add a space
        if
        (
            (last_char >= 'a' && last_char <= 'z') ||
            (last_char >= 'A' && last_char <= 'Z') ||
            (last_char >= '0' && last_char <= '9') ||
            last_char == '*' || last_char == '&' || last_char == '>'
        )
        {
            result_ << ' ';
        }
    }
}

const std::string
program_syntax_tree_to_string_converter::new_line()
{
    return "\n";
}

const std::string
program_syntax_tree_to_string_converter::opening_brace()
{
    std::string result = new_line() + indentation() + "{";
    ++m_indentation_level;
    result += new_line();
    return result;
}

const std::string
program_syntax_tree_to_string_converter::closing_brace()
{
    --m_indentation_level;
    return indentation() + "}";
}

const std::string
program_syntax_tree_to_string_converter::indentation()
{
    std::ostringstream result;
    for(unsigned int i = 0; i < m_indentation_level; ++i)
    {
        result << "    ";
    }
    return result.str();
}

}} //namespace socoa::cpp
