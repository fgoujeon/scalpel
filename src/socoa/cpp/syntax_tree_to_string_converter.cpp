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

#include "syntax_tree_to_string_converter.hpp"

#include <cassert>

namespace socoa { namespace cpp
{

using namespace syntax_tree;

syntax_tree_to_string_converter::syntax_tree_to_string_converter():
    indentation_level_(0)
{
}

std::string
syntax_tree_to_string_converter::operator()(const syntax_tree_t& a_syntax_tree)
{
    result_.str("");
    indentation_level_ = 0;
    convert(a_syntax_tree);
    return result_.str();
}

void
syntax_tree_to_string_converter::convert(const identifier& item)
{
    add_space();
    result_ << item.get_value();
}

void
syntax_tree_to_string_converter::convert(const qualified_nested_id& item)
{
    if(item.has_leading_double_colon())
        result_ << "::";

    convert(item.get_nested_name_specifier());

    if(item.has_template_keyword())
        result_ << "template ";

	convert(item.get_unqualified_id());
}

void
syntax_tree_to_string_converter::convert(const qualified_operator_function_id&)
{
    result_ << "::";

    result_ << "[NOT IMPLEMENTED]";
}

void
syntax_tree_to_string_converter::convert(const qualified_template_id& item)
{
    result_ << "::";
    convert(item.get_template_id());
}

void
syntax_tree_to_string_converter::convert(const qualified_identifier& item)
{
    result_ << "::";
    convert(item.get_identifier());
}

void
syntax_tree_to_string_converter::convert(const nested_name_specifier& item)
{
	convert(item.get_identifier_or_template_id());
    result_ << "::";
    for
    (
        std::vector<nested_name_specifier::second_part>::const_iterator i = item.get_parts().begin();
        i != item.get_parts().end();
        ++i
    )
    {
		convert(*i);
        result_ << "::";
    }
}

void
syntax_tree_to_string_converter::convert(const nested_name_specifier::second_part&)
{
}

void
syntax_tree_to_string_converter::convert(const simple_template_type_specifier& item)
{
    if(item.has_leading_double_colon())
        result_ << "::";

    convert(item.get_nested_name_specifier());

    result_ << "template ";
    convert(item.get_template_id());
}

void
syntax_tree_to_string_converter::convert(const namespace_definition& item)
{
    result_ << indentation();
    result_ << "namespace ";

    convert(item.get_identifier());

    result_ << opening_brace();

	convert(item.get_declaration_seq());

    result_ << closing_brace() << new_line();
}

void
syntax_tree_to_string_converter::convert(const using_declaration& item)
{
    result_ << indentation();
    result_ << "using ";

    if(item.has_typename_keyword())
        result_ << "typename ";

    if(item.has_leading_double_colon())
        result_ << "::";

    convert(item.get_nested_name_specifier());

    convert(item.get_unqualified_id());

    result_ << ";";
    result_ << new_line();
}

void
syntax_tree_to_string_converter::convert(const using_directive& item)
{
    result_ << indentation();
    result_ << "using namespace ";

    if(item.has_leading_double_colon())
        result_ << "::";

    convert(item.get_nested_name_specifier());
    convert(item.get_identifier());

    result_ << ";";
    result_ << new_line();
}

void
syntax_tree_to_string_converter::convert(const init_declarator& item)
{
    convert(item.get_declarator());
}

void
syntax_tree_to_string_converter::convert(const declarator& item)
{
    const std::vector<ptr_operator>& ptr_operators = item.get_ptr_operators();
    for(std::vector<ptr_operator>::const_iterator i = ptr_operators.begin(); i != ptr_operators.end(); ++i)
    {
        convert(*i);
    }

    convert(item.get_direct_declarator());
}

void
syntax_tree_to_string_converter::convert(const direct_declarator& item)
{
	convert(item.get_declarator_id());

    const boost::optional<const declarator&> a_declarator = item.get_declarator();
    if(a_declarator)
    {
        result_ << '(';
        convert(a_declarator);
        result_ << ')';
    }

    const std::vector<direct_declarator::other_part>& other_parts = item.get_other_parts();
    for
    (
        std::vector<direct_declarator::other_part>::const_iterator i = other_parts.begin();
        i != other_parts.end();
        ++i
    )
    {
		convert(*i);
    }
}

void
syntax_tree_to_string_converter::convert(const direct_declarator::function_part& item)
{
    result_ << '(';
    convert(item.get_parameter_declaration_clause());
    result_ << ')';

    if(item.get_cv_qualifier_seq())
        result_ << ' ';
	convert(item.get_cv_qualifier_seq());
}

void
syntax_tree_to_string_converter::convert(const direct_declarator::array_part&)
{
    result_ << '[';

    result_ << ']';
}

void
syntax_tree_to_string_converter::convert(const ptr_operator& item)
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

    convert(item.get_cv_qualifier_seq());
}

void
syntax_tree_to_string_converter::convert(const cv_qualifier& item)
{
    add_space();
	result_ << item.get_value();
}

void
syntax_tree_to_string_converter::convert(const parameter_declaration_clause& item)
{
    convert(item.get_parameter_declaration_list());

    if(item.has_trailing_comma())
        result_ << ", ";

    if(item.has_ellipsis())
        result_ << "...";
}

void
syntax_tree_to_string_converter::convert(const parameter_declaration& item)
{
    convert(item.get_decl_specifier_seq());
    convert(item.get_declarator());
}

void
syntax_tree_to_string_converter::convert(const elaborated_type_specifier& item)
{
}

void
syntax_tree_to_string_converter::convert(const function_definition& item)
{
    result_ << indentation();

    convert(item.get_decl_specifier_seq());
    convert(item.get_declarator());
    convert(item.get_ctor_initializer());

    result_ << opening_brace();

    result_ << closing_brace();
    result_ << new_line();
}

void
syntax_tree_to_string_converter::convert(const class_specifier& item)
{
    //result_ << indentation();
    convert(item.get_class_head());

    result_ << opening_brace();

    convert(item.get_member_specification());

    result_ << closing_brace();
}

void
syntax_tree_to_string_converter::convert(const class_head& item)
{
    convert(item.get_class_key());

    convert(item.get_nested_name_specifier());
    convert(item.get_template_id());
    convert(item.get_identifier());
}

void
syntax_tree_to_string_converter::convert(const member_specification& item)
{
    for
    (
        std::vector<member_specification_part>::const_iterator i = item.get_parts().begin();
        i != item.get_parts().end();
        ++i
    )
    {
		convert(*i);
    }
}

void
syntax_tree_to_string_converter::convert(const member_specification_access_specifier& item)
{
	--indentation_level_;
    result_ << indentation();
    convert(item.get_access_specifier());
    result_ << ":" << new_line();
	++indentation_level_;
}

void
syntax_tree_to_string_converter::convert(const member_declaration_member_declarator_list& item)
{
    result_ << indentation();

    convert(item.get_decl_specifier_seq());
    convert(item.get_member_declarator_list());

    result_ << ";" << new_line();
}

void
syntax_tree_to_string_converter::convert(const member_declaration_unqualified_id& item)
{
    result_ << indentation();

    if(item.has_leading_double_colon())
        result_ << "::";

    convert(item.get_nested_name_specifier());

    if(item.has_template_keyword())
        result_ << "template ";

    convert(item.get_unqualified_id());

    result_ << ";" << new_line();
}

void
syntax_tree_to_string_converter::convert(const member_declaration_function_definition& item)
{
    convert(item.get_function_definition());
}

void
syntax_tree_to_string_converter::convert(const member_declarator_declarator& item)
{
    //result_ << indentation();

    convert(item.get_declarator());

    if(item.has_pure_specifier())
        result_ << " = 0";
}

void
syntax_tree_to_string_converter::convert(const member_declarator_bit_field_member& item)
{
    convert(item.get_identifier());

    result_ << ": ";
}

void
syntax_tree_to_string_converter::convert(const ctor_initializer& item)
{
    result_ << ":";
    ++indentation_level_;
    convert(item.get_mem_initializer_list());
    --indentation_level_;
}

void
syntax_tree_to_string_converter::convert(const mem_initializer& item)
{
    result_ << new_line();
    result_ << indentation();
    convert(item.get_mem_initializer_id());
    result_ << "(";
    //convert(item.get_expression_list());
    result_ << ")";
}

void
syntax_tree_to_string_converter::convert(const template_declaration& item)
{
    result_ << indentation();

    if(item.has_export_keyword())
        result_ << "export ";

    result_ << "template";
    result_ << "<";
    result_ << ">\n";

    convert(item.get_declaration());
}

void
syntax_tree_to_string_converter::convert(const simple_declaration& item)
{
    result_ << indentation();

    convert(item.get_decl_specifier_seq());
    convert(item.get_init_declarator_list());

    result_ << ";" << new_line();
}

void
syntax_tree_to_string_converter::convert(const template_id& item)
{
    convert(item.get_identifier());
    result_ << "<";
    convert(item.get_template_argument_list());
    result_ << ">";
}

void
syntax_tree_to_string_converter::convert(const nested_identifier_or_template_id& item)
{
    if(item.has_leading_double_colon())
        result_ << "::";

    convert(item.get_nested_name_specifier());
    convert(item.get_identifier_or_template_id());
}

void
syntax_tree_to_string_converter::convert(const operator_function_id&)
{
}

void
syntax_tree_to_string_converter::convert(const conversion_function_id&)
{
}

void
syntax_tree_to_string_converter::convert(const destructor_name&)
{
}


void
syntax_tree_to_string_converter::convert_separator(const std::string& separator)
{
	if(separator == " ")
		add_space();
	else
		result_ << separator << " ";
}

void
syntax_tree_to_string_converter::add_space()
{
    if(result_.str().size() > 0)
    {
        //get last character added to result
        const char last_char = *result_.str().rbegin();

        //if last char is neither a white space nor a punctuation sign, let's
		//add a space
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
syntax_tree_to_string_converter::new_line()
{
    return "\n";
}

const std::string
syntax_tree_to_string_converter::opening_brace()
{
    std::string result = new_line() + indentation() + "{";
    ++indentation_level_;
    result += new_line();
    return result;
}

const std::string
syntax_tree_to_string_converter::closing_brace()
{
    --indentation_level_;
    return indentation() + "}";
}

const std::string
syntax_tree_to_string_converter::indentation()
{
    std::ostringstream result;
    for(unsigned int i = 0; i < indentation_level_; ++i)
    {
        result << "    ";
    }
    return result.str();
}

}} //namespace socoa::cpp
