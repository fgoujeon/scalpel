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
program_syntax_tree_to_string_converter::operator()(const std::shared_ptr<program_syntax_tree::declaration_seq> translation_unit)
{
    result_.str("");
    m_indentation_level = 0;
    visit(*translation_unit);
    return result_.str();
}

void
program_syntax_tree_to_string_converter::visit(const identifier& item)
{
    result_ << item.get_value();
}

void
program_syntax_tree_to_string_converter::visit(const qualified_nested_id& item)
{
    if(item.has_leading_double_colon())
        result_ << "::";

    visit(item.get_nested_name_specifier());

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
    visit(item.get_template_id());
}

void
program_syntax_tree_to_string_converter::visit(const qualified_identifier& item)
{
    result_ << "::";
    visit(item.get_identifier());
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

    visit(item.get_template_id());
}

void
program_syntax_tree_to_string_converter::visit(const declaration_seq& item)
{
    const std::vector<std::shared_ptr<declaration>>& declarations = item.get_declarations();
    for(std::vector<std::shared_ptr<declaration>>::const_iterator i = declarations.begin(); i != declarations.end(); ++i)
    {
        (**i).accept(*this);
    }
}

void
program_syntax_tree_to_string_converter::visit(const namespace_definition& item)
{
    result_ << indentation();
    result_ << "namespace ";

    if(std::shared_ptr<identifier> namespace_name = item.get_identifier())
        visit(*namespace_name);

    result_ << opening_brace();

    if(std::shared_ptr<declaration_seq> namespace_body = item.get_declaration_seq())
        visit(*namespace_body);

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

    if(item.get_nested_name_specifier())
        visit(*item.get_nested_name_specifier());

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
        visit(init_decl);
    }
}

void
program_syntax_tree_to_string_converter::visit(const init_declarator& item)
{
    visit(item.get_declarator());
}

void
program_syntax_tree_to_string_converter::visit(const declarator& item)
{
    const std::vector<std::shared_ptr<ptr_operator>>& ptr_operators = item.get_ptr_operators();
    for(std::vector<std::shared_ptr<ptr_operator>>::const_iterator i = ptr_operators.begin(); i != ptr_operators.end(); ++i)
    {
        visit(**i);
        result_ << ' ';
    }

    visit(item.get_direct_declarator());
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
        visit(*a_declarator);
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
    visit(item.get_parameter_declaration_clause());
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

    if(item.get_cv_qualifier_seq())
        visit(*item.get_cv_qualifier_seq());
}

void
program_syntax_tree_to_string_converter::visit(const cv_qualifier_seq& item)
{
    for
    (
        std::vector<std::shared_ptr<cv_qualifier>>::const_iterator i = item.get_cv_qualifiers().begin();
        i != item.get_cv_qualifiers().end();
        ++i
    )
    {
        visit(**i);
    }
}

void
program_syntax_tree_to_string_converter::visit(const cv_qualifier& item)
{
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

    result_ << " ";
}

void
program_syntax_tree_to_string_converter::visit(const parameter_declaration_clause& item)
{
    const std::shared_ptr<parameter_declaration_list> a_parameter_declaration_list(item.get_parameter_declaration_list());
    if(a_parameter_declaration_list)
    {
        visit(*a_parameter_declaration_list);
    }

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
        visit(**i);
    }
}

void
program_syntax_tree_to_string_converter::visit(const parameter_declaration& item)
{
    visit(item.get_decl_specifier_seq());

    const std::shared_ptr<declarator> a_declarator = item.get_declarator();
    if(a_declarator)
    {
        visit(*a_declarator);
    }
}

void
program_syntax_tree_to_string_converter::visit(const function_definition& item)
{
    result_ << indentation();

    if(item.get_decl_specifier_seq())
        visit(*item.get_decl_specifier_seq());

    visit(item.get_declarator());
    result_ << opening_brace();

    result_ << closing_brace();
    result_ << new_line();
}

void
program_syntax_tree_to_string_converter::visit(const class_specifier& item)
{
    //result_ << indentation();
    visit(item.get_head());

    result_ << opening_brace();

    if(item.get_member_specification())
    {
        visit(*item.get_member_specification());
    }

    result_ << closing_brace();
}

void
program_syntax_tree_to_string_converter::visit(const class_head& item)
{
    visit(item.get_key());
    result_ << " ";

    if(item.get_nested_name_specifier())
        visit(*item.get_nested_name_specifier());

    if(item.get_template_id())
        visit(*item.get_template_id());

    if(item.get_identifier())
        visit(*item.get_identifier());
}

void
program_syntax_tree_to_string_converter::visit(const class_key& item)
{
    switch(item.get_value())
    {
        case class_key::CLASS:
            result_ << "class";
            break;
        case class_key::STRUCT:
            result_ << "struct";
            break;
        case class_key::UNION:
            result_ << "union";
            break;
    }
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
program_syntax_tree_to_string_converter::visit(const member_declaration_member_declarator_list& item)
{
    result_ << indentation();

    if(item.get_decl_specifier_seq())
        visit(*item.get_decl_specifier_seq());

    if(item.get_member_declarator_list())
        visit(*item.get_member_declarator_list());

    result_ << ";" << new_line();
}

void
program_syntax_tree_to_string_converter::visit(const member_declaration_unqualified_id& item)
{
    result_ << indentation();

    if(item.has_leading_double_colon())
        result_ << "::";

    visit(item.get_nested_name_specifier());

    if(item.has_template_keyword())
        result_ << "template ";

    item.get_unqualified_id()->accept(*this);

    result_ << ";" << new_line();
}

void
program_syntax_tree_to_string_converter::visit(const member_declaration_function_definition& item)
{
    visit(item.get_function_definition());
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

    if(item.get_declarator())
        visit(*item.get_declarator());

    if(item.has_pure_specifier())
        result_ << " = 0";
}

void
program_syntax_tree_to_string_converter::visit(const member_declarator_bit_field_member& item)
{
    if(item.get_identifier())
        visit(*item.get_identifier());

    result_ << ": ";
}

void
program_syntax_tree_to_string_converter::visit(const access_specifier& item)
{
    result_ << indentation();

    switch(item.get_value())
    {
        case access_specifier::PUBLIC:
            result_ << "public";
            break;
        case access_specifier::PROTECTED:
            result_ << "protected";
            break;
        case access_specifier::PRIVATE:
            result_ << "private";
            break;
    }

    result_ << ":" << new_line();
}

void
program_syntax_tree_to_string_converter::visit(const template_declaration& item)
{
    result_ << indentation();

    if(item.has_export_keyword())
        result_ << "export ";

    result_ << "template ";
    result_ << "<";
    result_ << ">\n";

    item.get_declaration()->accept(*this);
}

void
program_syntax_tree_to_string_converter::visit(const simple_declaration& item)
{
    result_ << indentation();

    std::shared_ptr<decl_specifier_seq> decl_specifiers = item.get_decl_specifier_seq();
    if(decl_specifiers)
        visit(*decl_specifiers);

    std::shared_ptr<init_declarator_list> init_declarators = item.get_init_declarator_list();
    if(init_declarators)
        visit(*init_declarators);

    result_ << ";" << new_line();
}

void
program_syntax_tree_to_string_converter::visit(const decl_specifier_seq& item)
{
    const std::vector<std::shared_ptr<decl_specifier>>& decl_specifiers = item.get_decl_specifiers();
    for(std::vector<std::shared_ptr<decl_specifier>>::const_iterator i = decl_specifiers.begin(); i != decl_specifiers.end(); ++i)
    {
        (**i).accept(*this);
    }
}

void
program_syntax_tree_to_string_converter::visit(const simple_type_specifier& item)
{
    switch(item.get_type())
    {
        case simple_type_specifier::CHAR:
            result_ << "char";
            break;
        case simple_type_specifier::WCHAR_T:
            result_ << "wchar_t";
            break;
        case simple_type_specifier::BOOL:
            result_ << "bool";
            break;
        case simple_type_specifier::SHORT:
            result_ << "short";
            break;
        case simple_type_specifier::INT:
            result_ << "int";
            break;
        case simple_type_specifier::LONG:
            result_ << "long";
            break;
        case simple_type_specifier::SIGNED:
            result_ << "signed";
            break;
        case simple_type_specifier::UNSIGNED:
            result_ << "unsigned";
            break;
        case simple_type_specifier::FLOAT:
            result_ << "float";
            break;
        case simple_type_specifier::DOUBLE:
            result_ << "double";
            break;
        case simple_type_specifier::VOID:
            result_ << "void";
            break;
        case simple_type_specifier::OTHER:
        {
            if(item.has_leading_double_colon())
                result_ << "::";

            if(item.get_nested_name_specifier())
                visit(*item.get_nested_name_specifier());

            if(item.get_template_id())
            {
                result_ << "template ";
                visit(*item.get_template_id());
            }
            else
            {
                item.get_identifier_or_template_id()->accept(*this);
            }

            break;
        }
    }

    result_ << ' ';
}

void
program_syntax_tree_to_string_converter::visit(const template_id& item)
{
    result_ << item.get_identifier().get_value() << "<>";
}

void
program_syntax_tree_to_string_converter::visit(const nested_identifier_or_template_id& item)
{
    if(item.has_leading_double_colon())
        result_ << "::";

    if(item.get_nested_name_specifier())
        visit(*item.get_nested_name_specifier());

    item.get_identifier_or_template_id()->accept(*this);
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
