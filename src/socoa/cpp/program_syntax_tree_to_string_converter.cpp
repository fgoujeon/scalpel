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

#include "program_syntax_tree/declaration_seq.h"
#include "program_syntax_tree/namespace_definition.h"
#include "program_syntax_tree/class_specifier.h"
#include "program_syntax_tree/simple_declaration.h"
#include "program_syntax_tree/decl_specifier_seq.h"
#include "program_syntax_tree/simple_type_specifier.h"

#include "program_syntax_tree_to_string_converter.h"

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
    m_result_oss.str("");
    m_indentation_level = 0;
    translation_unit->accept(*this);
    return m_result_oss.str();
}

void
program_syntax_tree_to_string_converter::visit(const declaration_seq& item)
{
    const std::vector<std::shared_ptr<declaration>>& declarations = item.declarations();
    for(std::vector<std::shared_ptr<declaration>>::const_iterator i = declarations.begin(); i != declarations.end(); ++i)
    {
        (**i).accept(*this);
    }
}

void
program_syntax_tree_to_string_converter::visit(const namespace_definition& item)
{
    indent();
    m_result_oss << "namespace " << item.name() << "\n";
    indent();
    m_result_oss << "{\n";

    ++m_indentation_level;
    visit(item.body());
    --m_indentation_level;

    indent();
    m_result_oss << "}\n";
}

void
program_syntax_tree_to_string_converter::visit(const class_specifier& item)
{
    indent();
    m_result_oss << "class " << item.name() << "\n";
    indent();
    m_result_oss << "{\n";

    indent();
    m_result_oss << "};\n";
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
    visit(item.decl_specifiers());
}

void
program_syntax_tree_to_string_converter::visit(const decl_specifier_seq& item)
{
    const std::vector<std::shared_ptr<decl_specifier>>& decl_specifiers = item.decl_specifiers();
    for(std::vector<std::shared_ptr<decl_specifier>>::const_iterator i = decl_specifiers.begin(); i != decl_specifiers.end(); ++i)
    {
        (**i).accept(*this);
    }
}

void
program_syntax_tree_to_string_converter::visit(const simple_type_specifier& item)
{
    indent();
    m_result_oss << item.type() << "\n";
}

void
program_syntax_tree_to_string_converter::indent()
{
    for(unsigned int i = 0; i < m_indentation_level; ++i)
    {
        m_result_oss << "  ";
    }
}

}} //namespace socoa::cpp
