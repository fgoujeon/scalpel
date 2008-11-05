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

#include <socoa/cpp/program_syntax_tree_to_string_converter.h>

#include <cassert>

namespace socoa { namespace cpp
{

using namespace program_syntax_tree;

program_syntax_tree_to_string_converter::program_syntax_tree_to_string_converter():
    m_indentation_level(0)
{
}

std::string
program_syntax_tree_to_string_converter::operator()(const std::shared_ptr<util::sequence<declaration>> translation_unit)
{
    result_.str("");
    m_indentation_level = 0;
    safe_convert(*translation_unit);
    return result_.str();
}

void
program_syntax_tree_to_string_converter::convert(const identifier& item)
{
    add_space();
    result_ << item.value_;
}

void
program_syntax_tree_to_string_converter::convert(const qualified_nested_id& item)
{
    if(item.leading_double_colon_)
        result_ << "::";

    safe_convert(item.nested_name_specifier_);

    if(item.template_keyword_)
        result_ << "template ";

    item.unqualified_id_->accept(*this);
}

void
program_syntax_tree_to_string_converter::convert(const qualified_operator_function_id& item)
{
    result_ << "::";

    result_ << "[NOT IMPLEMENTED]";
}

void
program_syntax_tree_to_string_converter::convert(const qualified_template_id& item)
{
    result_ << "::";
    safe_convert(item.template_id_);
}

void
program_syntax_tree_to_string_converter::convert(const qualified_identifier& item)
{
    result_ << "::";
    safe_convert(item.identifier_);
}

void
program_syntax_tree_to_string_converter::convert(const nested_name_specifier& item)
{
    item.identifier_or_template_id_->accept(*this);
    result_ << "::";
    for
    (
        std::vector<std::shared_ptr<nested_name_specifier_part>>::const_iterator i = item.parts_.begin();
        i != item.parts_.end();
        ++i
    )
    {
        (**i).accept(*this);
        result_ << "::";
    }
}

void
program_syntax_tree_to_string_converter::convert(const nested_name_specifier_template_id_part& item)
{
    if(item.template_keyword_)
        result_ << "template ";

    safe_convert(item.template_id_);
}

void
program_syntax_tree_to_string_converter::convert(const simple_template_type_specifier& item)
{
    if(item.leading_double_colon_)
        result_ << "::";

    safe_convert(item.nested_name_specifier_);

    result_ << "template ";
    safe_convert(item.template_id_);
}

void
program_syntax_tree_to_string_converter::convert(const namespace_definition& item)
{
    result_ << indentation();
    result_ << "namespace ";

    safe_convert(item.identifier_);

    result_ << opening_brace();

    safe_convert(item.declaration_seq_);

    result_ << closing_brace() << new_line();
}

void
program_syntax_tree_to_string_converter::convert(const using_declaration& item)
{
    result_ << indentation();
    result_ << "using ";

    if(item.typename_keyword_)
        result_ << "typename ";

    if(item.leading_double_colon_)
        result_ << "::";

    safe_convert(item.nested_name_specifier_);

    item.unqualified_id_->accept(*this);

    result_ << ";";
    result_ << new_line();
}

void
program_syntax_tree_to_string_converter::convert(const using_directive& item)
{
    result_ << indentation();
    result_ << "using namespace ";

    if(item.leading_double_colon_)
        result_ << "::";

    safe_convert(item.nested_name_specifier_);
    safe_convert(item.identifier_);

    result_ << ";";
    result_ << new_line();
}

void
program_syntax_tree_to_string_converter::convert(const init_declarator& item)
{
    safe_convert(item.declarator_);
}

void
program_syntax_tree_to_string_converter::convert(const declarator& item)
{
    const std::vector<std::shared_ptr<ptr_operator>>& ptr_operators = item.ptr_operators_;
    for(std::vector<std::shared_ptr<ptr_operator>>::const_iterator i = ptr_operators.begin(); i != ptr_operators.end(); ++i)
    {
        safe_convert(**i);
    }

    safe_convert(item.direct_declarator_);
}

void
program_syntax_tree_to_string_converter::convert(const direct_declarator& item)
{
    const std::shared_ptr<declarator_id> a_declarator_id = item.declarator_id_;
    if(a_declarator_id)
    {
        a_declarator_id->accept(*this);
    }

    const std::shared_ptr<declarator> a_declarator = item.declarator_;
    if(a_declarator)
    {
        result_ << '(';
        safe_convert(*a_declarator);
        result_ << ')';
    }

    const std::vector<std::shared_ptr<direct_declarator_part>>& other_parts = item.other_parts_;
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
program_syntax_tree_to_string_converter::convert(const direct_declarator_function_part& item)
{
    result_ << '(';
    safe_convert(item.parameter_declaration_clause_);
    result_ << ')';

    if(item.cv_qualifier_seq_)
        result_ << ' ';
    safe_convert(item.cv_qualifier_seq_);
}

void
program_syntax_tree_to_string_converter::convert(const direct_declarator_array_part& item)
{
    result_ << '[';

    result_ << ']';
}

void
program_syntax_tree_to_string_converter::convert(const ptr_operator& item)
{
    if(item.leading_double_colon_)
        result_ << "::";

    switch(item.type_)
    {
        case ptr_operator::ASTERISK:
            result_ << '*';
            break;
        case ptr_operator::AMPERSAND:
            result_ << '&';
            break;
    }

    safe_convert(item.cv_qualifier_seq_);
}

void
program_syntax_tree_to_string_converter::convert(const cv_qualifier& item)
{
    add_space();

    switch(item.type_)
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
program_syntax_tree_to_string_converter::convert(const parameter_declaration_clause& item)
{
    safe_convert(item.parameter_declaration_list_);

    if(item.trailing_comma_)
        result_ << ", ";

    if(item.ellipsis_)
        result_ << "...";
}

void
program_syntax_tree_to_string_converter::convert(const parameter_declaration& item)
{
    safe_convert(item.decl_specifier_seq_);
    safe_convert(item.declarator_);
}

void
program_syntax_tree_to_string_converter::convert(const function_definition& item)
{
    result_ << indentation();

    safe_convert(item.decl_specifier_seq_);
    safe_convert(item.declarator_);
    safe_convert(item.ctor_initializer_);

    result_ << opening_brace();

    result_ << closing_brace();
    result_ << new_line();
}

void
program_syntax_tree_to_string_converter::convert(const class_specifier& item)
{
    //result_ << indentation();
    safe_convert(item.head_);

    result_ << opening_brace();

    safe_convert(item.member_specification_);

    result_ << closing_brace();
}

void
program_syntax_tree_to_string_converter::convert(const class_head& item)
{
    safe_convert(item.key_);

    safe_convert(item.nested_name_specifier_);
    safe_convert(item.template_id_);
    safe_convert(item.identifier_);
}

void
program_syntax_tree_to_string_converter::convert(const member_specification& item)
{
    for
    (
        std::vector<std::shared_ptr<member_specification_part>>::const_iterator i = item.parts_.begin();
        i != item.parts_.end();
        ++i
    )
    {
        assert(*i);
        (**i).accept(*this);
    }
}

void
program_syntax_tree_to_string_converter::convert(const member_specification_access_specifier& item)
{
    result_ << indentation();
    safe_convert(item.access_specifier_);
    result_ << ":" << new_line();
}

void
program_syntax_tree_to_string_converter::convert(const member_declaration_member_declarator_list& item)
{
    result_ << indentation();

    safe_convert(item.decl_specifier_seq_);
    safe_convert(item.member_declarator_list_);

    result_ << ";" << new_line();
}

void
program_syntax_tree_to_string_converter::convert(const member_declaration_unqualified_id& item)
{
    result_ << indentation();

    if(item.leading_double_colon_)
        result_ << "::";

    safe_convert(item.nested_name_specifier_);

    if(item.template_keyword_)
        result_ << "template ";

    item.unqualified_id_->accept(*this);

    result_ << ";" << new_line();
}

void
program_syntax_tree_to_string_converter::convert(const member_declaration_function_definition& item)
{
    safe_convert(item.function_definition_);
}

void
program_syntax_tree_to_string_converter::convert(const member_declarator_declarator& item)
{
    //result_ << indentation();

    safe_convert(item.declarator_);

    if(item.pure_specifier_)
        result_ << " = 0";
}

void
program_syntax_tree_to_string_converter::convert(const member_declarator_bit_field_member& item)
{
    safe_convert(item.identifier_);

    result_ << ": ";
}

void
program_syntax_tree_to_string_converter::convert(const ctor_initializer& item)
{
    result_ << ":";
    ++m_indentation_level;
    safe_convert(item.mem_initializer_list_);
    --m_indentation_level;
}

void
program_syntax_tree_to_string_converter::convert(const mem_initializer& item)
{
    result_ << new_line();
    result_ << indentation();
    item.mem_initializer_id_->accept(*this);
    result_ << "(";
    //safe_convert(item.expression_list_);
    result_ << ")";
}

void
program_syntax_tree_to_string_converter::convert(const template_declaration& item)
{
    result_ << indentation();

    if(item.export_keyword_)
        result_ << "export ";

    result_ << "template";
    result_ << "<";
    result_ << ">\n";

    item.declaration_->accept(*this);
}

void
program_syntax_tree_to_string_converter::convert(const simple_declaration& item)
{
    result_ << indentation();

    safe_convert(item.decl_specifier_seq_);
    safe_convert(item.init_declarator_list_);

    result_ << ";" << new_line();
}

void
program_syntax_tree_to_string_converter::convert(const template_id& item)
{
    safe_convert(item.identifier_);
    result_ << "<";
    safe_convert(item.template_argument_list_);
    result_ << ">";
}

void
program_syntax_tree_to_string_converter::convert(const nested_identifier_or_template_id& item)
{
    if(item.leading_double_colon_)
        result_ << "::";

    safe_convert(item.nested_name_specifier_);

    item.identifier_or_template_id_->accept(*this);
}

/**
@todo could be simplified with C++0x concepts:
    template<Visitable T>
    ...
*/
//unlike other comma-separated list classes, these classes require visitation
template<>
void
program_syntax_tree_to_string_converter::convert
(
    const util::sequence<program_syntax_tree::member_declarator, util::extern_strings::comma>& seq
)
{
    convert_visitable(seq);
}
template<>
void
program_syntax_tree_to_string_converter::convert
(
    const util::sequence<program_syntax_tree::template_argument, util::extern_strings::comma>& seq
)
{
    convert_visitable(seq);
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
            last_char == '*' ||
            last_char == '&' ||
            last_char == '>' ||
            last_char == ')'
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
