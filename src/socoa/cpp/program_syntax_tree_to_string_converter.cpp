/*
Socoa - Source Code Analysis Library
Copyright © 2008  Florian Goujeon

This file is part of Socoa.

Socoa is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, version 3 of the License.

Socoa is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Socoa.  If not, see <http://www.gnu.org/licenses/>.
*/

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
    m_result.str("");
    m_indentation_level = 0;
    visit(*translation_unit);
    return m_result.str();
}

void
program_syntax_tree_to_string_converter::visit(const identifier& item)
{
    m_result << item.get_value();
}

void
program_syntax_tree_to_string_converter::visit(const declaration_seq& item)
{
    const std::vector<std::shared_ptr<declaration>>& declarations = item.get_declarations();
    for(std::vector<std::shared_ptr<declaration>>::const_iterator i = declarations.begin(); i != declarations.end(); ++i)
    {
        m_result << indentation();
        (**i).accept(*this);
    }
}

void
program_syntax_tree_to_string_converter::visit(const namespace_definition& item)
{
    m_result << "namespace " << item.get_name();
    m_result << opening_brace();
    visit(item.get_body());
    m_result << closing_brace() << new_line();
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
    std::shared_ptr<declarator> decl = item.get_declarator();

    if(decl)
        visit(*decl);
}

void
program_syntax_tree_to_string_converter::visit(const declarator& item)
{
    const std::shared_ptr<direct_declarator> a_direct_declarator(item.get_direct_declarator());
    if(a_direct_declarator)
    {
        visit(*a_direct_declarator);
    }
}

void
program_syntax_tree_to_string_converter::visit(const direct_declarator& item)
{
    const std::shared_ptr<declarator_id> a_declarator_id = item.get_declarator_id();
    if(a_declarator_id)
    {
        visit(*a_declarator_id);
    }

    const std::shared_ptr<declarator> a_declarator = item.get_declarator();
    if(a_declarator)
    {
        m_result << '(';
        visit(*a_declarator);
        m_result << ')';
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
program_syntax_tree_to_string_converter::visit(const function_direct_declarator_part& item)
{
    m_result << '(';
    visit(item.get_parameter_declaration_clause());
    m_result << ')';
}

void
program_syntax_tree_to_string_converter::visit(const array_direct_declarator_part& item)
{
    m_result << '[';

    m_result << ']';
}

void
program_syntax_tree_to_string_converter::visit(const declarator_id& item)
{
    const std::shared_ptr<id_expression> an_id_expression = item.get_id_expression();
    if(an_id_expression)
    {
        an_id_expression->accept(*this);
        return;
    }
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
        m_result << ", ";

    if(item.has_ellipsis())
        m_result << "...";
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
            m_result << ", ";
        visit(**i);
    }
}

void
program_syntax_tree_to_string_converter::visit(const parameter_declaration& item)
{
    visit(item.get_decl_specifier_seq());
}

void
program_syntax_tree_to_string_converter::visit(const function_definition& item)
{
    const std::shared_ptr<decl_specifier_seq> a_decl_specifier_seq = item.get_decl_specifier_seq();
    if(a_decl_specifier_seq)
        visit(*a_decl_specifier_seq);

    visit(item.get_declarator());
    m_result << opening_brace();

    m_result << closing_brace();
    m_result << new_line();
}

void
program_syntax_tree_to_string_converter::visit(const class_specifier& item)
{
    m_result << "class " << item.get_name();
    m_result << opening_brace();

    m_result << closing_brace();
}

void
program_syntax_tree_to_string_converter::visit(const member_specification& item)
{
}

void
program_syntax_tree_to_string_converter::visit(const access_specifier& item)
{
}

void
program_syntax_tree_to_string_converter::visit(const template_declaration& item)
{
}

void
program_syntax_tree_to_string_converter::visit(const simple_declaration& item)
{
    std::shared_ptr<decl_specifier_seq> decl_specifiers = item.get_decl_specifier_seq();
    if(decl_specifiers)
        visit(*decl_specifiers);

    std::shared_ptr<init_declarator_list> init_declarators = item.get_init_declarator_list();
    if(init_declarators)
        visit(*init_declarators);

    m_result << ";" << new_line();
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
    m_result << item.get_type() << " ";
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
