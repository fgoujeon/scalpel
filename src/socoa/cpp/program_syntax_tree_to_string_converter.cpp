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

#include "program_syntax_tree/identifier.h"

//#include "program_syntax_tree/primary_expression.h"
#include "program_syntax_tree/id_expression.h"
#include "program_syntax_tree/unqualified_id.h"
//#include "program_syntax_tree/qualified_id.h"
//#include "program_syntax_tree/nested_name_specifier.h"
//#include "program_syntax_tree/class_or_namespace_name.h"
//#include "program_syntax_tree/postfix_expression.h"
//#include "program_syntax_tree/expression_list.h"
//#include "program_syntax_tree/pseudo_destructor_name.h"
//#include "program_syntax_tree/unary_expression.h"
//#include "program_syntax_tree/unary_operator.h"
//#include "program_syntax_tree/new_expression.h"
//#include "program_syntax_tree/new_placement.h"
//#include "program_syntax_tree/new_type_id.h"
//#include "program_syntax_tree/new_declarator.h"
//#include "program_syntax_tree/direct_new_declarator.h"
//#include "program_syntax_tree/new_initializer.h"
//#include "program_syntax_tree/delete_expression.h"
//#include "program_syntax_tree/cast_expression.h"
//#include "program_syntax_tree/pm_expression.h"
//#include "program_syntax_tree/multiplicative_expression.h"
//#include "program_syntax_tree/additive_expression.h"
//#include "program_syntax_tree/shift_expression.h"
//#include "program_syntax_tree/relational_expression.h"
//#include "program_syntax_tree/equality_expression.h"
//#include "program_syntax_tree/and_expression.h"
//#include "program_syntax_tree/exclusive_or_expression.h"
//#include "program_syntax_tree/inclusive_or_expression.h"
//#include "program_syntax_tree/logical_and_expression.h"
//#include "program_syntax_tree/logical_or_expression.h"
//#include "program_syntax_tree/conditional_expression.h"
//#include "program_syntax_tree/assignment_expression.h"
//#include "program_syntax_tree/assignment_operator.h"
//#include "program_syntax_tree/expression.h"
//#include "program_syntax_tree/constant_expression.h"

//#include "program_syntax_tree/statement.h"
//#include "program_syntax_tree/labeled_statement.h"
//#include "program_syntax_tree/expression_statement.h"
//#include "program_syntax_tree/compound_statement.h"
//#include "program_syntax_tree/statement_seq.h"
//#include "program_syntax_tree/selection_statement.h"
//#include "program_syntax_tree/condition.h"
//#include "program_syntax_tree/condition_type_specifier_seq.h"
//#include "program_syntax_tree/iteration_statement.h"
//#include "program_syntax_tree/for_init_statement.h"
//#include "program_syntax_tree/jump_statement.h"
//#include "program_syntax_tree/declaration_statement.h"
//
//#include "program_syntax_tree/declaration_seq.h"
#include "program_syntax_tree/declaration.h"
//#include "program_syntax_tree/block_declaration.h"
#include "program_syntax_tree/simple_declaration.h"
//#include "program_syntax_tree/decl_specifier.h"
#include "program_syntax_tree/decl_specifier_seq.h"
//#include "program_syntax_tree/storage_class_specifier.h"
//#include "program_syntax_tree/function_specifier.h"
//#include "program_syntax_tree/typedef_name.h"
//#include "program_syntax_tree/type_specifier.h"
#include "program_syntax_tree/simple_type_specifier.h"
//#include "program_syntax_tree/type_name.h"
//#include "program_syntax_tree/elaborated_type_specifier.h"
//#include "program_syntax_tree/enum_name.h"
//#include "program_syntax_tree/enum_specifier.h"
//#include "program_syntax_tree/enumerator_list.h"
//#include "program_syntax_tree/enumerator_definition.h"
//#include "program_syntax_tree/enumerator.h"
//#include "program_syntax_tree/namespace_name.h"
#include "program_syntax_tree/namespace_definition.h"
//#include "program_syntax_tree/named_namespace_definition.h"
//#include "program_syntax_tree/unnamed_namespace_definition.h"
//#include "program_syntax_tree/namespace_body.h"
//#include "program_syntax_tree/namespace_alias.h"
//#include "program_syntax_tree/namespace_alias_definition.h"
//#include "program_syntax_tree/qualified_namespace_specifier.h"
//#include "program_syntax_tree/using_declaration.h"
//#include "program_syntax_tree/using_directive.h"
//#include "program_syntax_tree/asm_definition.h"
//#include "program_syntax_tree/linkage_specification.h"
//
#include "program_syntax_tree/init_declarator_list.h"
#include "program_syntax_tree/init_declarator.h"
#include "program_syntax_tree/declarator.h"
#include "program_syntax_tree/direct_declarator.h"
//#include "program_syntax_tree/ptr_operator.h"
//#include "program_syntax_tree/cv_qualifier_seq.h"
//#include "program_syntax_tree/cv_qualifier.h"
#include "program_syntax_tree/declarator_id.h"
//#include "program_syntax_tree/type_id.h"
//#include "program_syntax_tree/type_specifier_seq.h"
//#include "program_syntax_tree/abstract_declarator.h"
//#include "program_syntax_tree/direct_abstract_declarator.h"
//#include "program_syntax_tree/parameter_declaration_clause.h"
//#include "program_syntax_tree/parameter_declaration_list.h"
//#include "program_syntax_tree/parameter_declaration.h"
//#include "program_syntax_tree/function_definition.h"
//#include "program_syntax_tree/function_body.h"
//#include "program_syntax_tree/initializer.h"
//#include "program_syntax_tree/initializer_clause.h"
//#include "program_syntax_tree/initializer_list.h"
//
//#include "program_syntax_tree/class_name.h"
#include "program_syntax_tree/class_specifier.h"
//#include "program_syntax_tree/class_head.h"
//#include "program_syntax_tree/class_key.h"
//#include "program_syntax_tree/member_specification.h"
//#include "program_syntax_tree/member_declaration.h"
//#include "program_syntax_tree/member_declaration_decl_specifier_seq.h"
//#include "program_syntax_tree/member_declarator_list.h"
//#include "program_syntax_tree/member_declarator.h"
//#include "program_syntax_tree/pure_specifier.h"
//#include "program_syntax_tree/constant_initializer.h"
//#include "program_syntax_tree/destructor_name.h"
//
//#include "program_syntax_tree/base_clause.h"
//#include "program_syntax_tree/base_specifier_list.h"
//#include "program_syntax_tree/base_specifier.h"
//#include "program_syntax_tree/access_specifier.h"
//
//#include "program_syntax_tree/conversion_function_id.h"
//#include "program_syntax_tree/conversion_type_id.h"
//#include "program_syntax_tree/conversion_declarator.h"
//#include "program_syntax_tree/ctor_initializer.h"
//#include "program_syntax_tree/mem_initializer_list.h"
//#include "program_syntax_tree/mem_initializer.h"
//#include "program_syntax_tree/mem_initializer_id.h"
//
//#include "program_syntax_tree/operator_function_id.h"
//#include "program_syntax_tree/operator_.h"
//
//#include "program_syntax_tree/template_declaration.h"
//#include "program_syntax_tree/template_parameter_list.h"
//#include "program_syntax_tree/template_parameter.h"
//#include "program_syntax_tree/type_parameter.h"
//#include "program_syntax_tree/template_id.h"
//#include "program_syntax_tree/template_name.h"
//#include "program_syntax_tree/template_argument_list.h"
//#include "program_syntax_tree/template_argument.h"
//#include "program_syntax_tree/explicit_instantiation.h"
//#include "program_syntax_tree/explicit_specialization.h"
//
//#include "program_syntax_tree/try_block.h"
//#include "program_syntax_tree/function_try_block.h"
//#include "program_syntax_tree/handler_seq.h"
//#include "program_syntax_tree/handler.h"
//#include "program_syntax_tree/exception_declaration.h"
//#include "program_syntax_tree/throw_expression.h"
//#include "program_syntax_tree/exception_specification.h"
//#include "program_syntax_tree/type_id_list.h"
//
//#include "program_syntax_tree/typeof_expression.h"

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
    visit(*item.get_direct_declarator());
}

void
program_syntax_tree_to_string_converter::visit(const direct_declarator& item)
{
    const std::shared_ptr<declarator_id> a_declarator_id = item.get_declarator_id();
    if(a_declarator_id)
    {
        visit(*a_declarator_id);
        return;
    }

    const std::shared_ptr<declarator> a_declarator = item.get_declarator();
    if(a_declarator)
    {
        m_result << '(';
        visit(*a_declarator);
        m_result << ')';
        return;
    }
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
    visit(item.get_decl_specifier_seq());

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
