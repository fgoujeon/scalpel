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

#ifndef SOCOA_CPP_GRAMMAR_HPP
#define SOCOA_CPP_GRAMMAR_HPP

#include <boost/spirit/core.hpp>
#include <boost/spirit/tree/parse_tree.hpp>
#include <boost/spirit/utility/functor_parser.hpp>
#include "scanner.hpp"

namespace socoa { namespace cpp
{

class grammar
{
    public:
        struct configuration
        {
            configuration():
                enable_typeof_support(true),
                enable_restrict_support(true)
            {
            }

            bool enable_typeof_support;
            bool enable_restrict_support;
        };

        enum parser_id
        {
            FILE,
            SOURCE_CHARACTER_SET,
            SPACE,
            KEYWORD,

            HEX_QUAD,
            UNIVERSAL_CHARACTER_NAME,
            IDENTIFIER,
            NONDIGIT,
            LITERAL,
            INTEGER_LITERAL,
            DECIMAL_LITERAL,
            OCTAL_LITERAL,
            HEXADECIMAL_LITERAL,
            HEXADECIMAL_DIGIT,
            OCTAL_DIGIT,
            NONZERO_DIGIT,
            INTEGER_SUFFIX,
            UNSIGNED_SUFFIX,
            LONG_SUFFIX,
            LONG_LONG_SUFFIX,
            CHARACTER_LITERAL,
            C_CHAR_SEQUENCE,
            C_CHAR,
            ESCAPE_SEQUENCE,
            SIMPLE_ESCAPE_SEQUENCE,
            OCTAL_ESCAPE_SEQUENCE,
            HEXADECIMAL_ESCAPE_SEQUENCE,
            FLOATING_LITERAL,
            FRACTIONAL_CONSTANT,
            EXPONENT_PART,
            DIGIT_SEQUENCE,
            FLOATING_SUFFIX,
            STRING_LITERAL,
            S_CHAR_SEQUENCE,
            S_CHAR,
            BOOLEAN_LITERAL,

            TRANSLATION_UNIT,

            PRIMARY_EXPRESSION,
            ID_EXPRESSION,
            UNQUALIFIED_ID,
            QUALIFIED_ID,
            QUALIFIED_NESTED_ID,
            QUALIFIED_OPERATOR_FUNCTION_ID,
            QUALIFIED_TEMPLATE_ID,
            QUALIFIED_IDENTIFIER,
            NESTED_NAME_SPECIFIER,
            NESTED_NAME_SPECIFIER_NEXT_PART_SEQ,
            NESTED_NAME_SPECIFIER_NEXT_PART,
            POSTFIX_EXPRESSION,
            EXPRESSION_LIST,
            PSEUDO_DESTRUCTOR_NAME,
            UNARY_EXPRESSION,
			UNARY_OPERATOR_UNARY_EXPRESSION,
			TYPE_ID_SIZEOF_EXPRESSION,
			UNARY_SIZEOF_EXPRESSION,
            UNARY_OPERATOR,
            NEW_EXPRESSION,
            NEW_PLACEMENT,
            NEW_TYPE_ID,
            NEW_DECLARATOR,
            DIRECT_NEW_DECLARATOR,
            NEW_INITIALIZER,
            DELETE_EXPRESSION,
            CAST_EXPRESSION,
            PM_EXPRESSION,
            MULTIPLICATIVE_EXPRESSION,
            ADDITIVE_EXPRESSION,
            SHIFT_EXPRESSION,
            TEMPLATE_ARGUMENT_SHIFT_EXPRESSION,
            RELATIONAL_EXPRESSION,
            TEMPLATE_ARGUMENT_RELATIONAL_EXPRESSION,
            EQUALITY_EXPRESSION,
            TEMPLATE_ARGUMENT_EQUALITY_EXPRESSION,
            AND_EXPRESSION,
            TEMPLATE_ARGUMENT_AND_EXPRESSION,
            EXCLUSIVE_OR_EXPRESSION,
            TEMPLATE_ARGUMENT_EXCLUSIVE_OR_EXPRESSION,
            INCLUSIVE_OR_EXPRESSION,
            TEMPLATE_ARGUMENT_INCLUSIVE_OR_EXPRESSION,
            LOGICAL_AND_EXPRESSION,
            TEMPLATE_ARGUMENT_LOGICAL_AND_EXPRESSION,
            LOGICAL_OR_EXPRESSION,
            TEMPLATE_ARGUMENT_LOGICAL_OR_EXPRESSION,
            CONDITIONAL_EXPRESSION,
            TEMPLATE_ARGUMENT_CONDITIONAL_EXPRESSION,
            ASSIGNMENT_EXPRESSION,
            ASSIGNMENT_EXPRESSION_FIRST_PART_SEQ,
            ASSIGNMENT_EXPRESSION_FIRST_PART,
            TEMPLATE_ARGUMENT_ASSIGNMENT_EXPRESSION,
            ASSIGNMENT_OPERATOR,
            EXPRESSION,
            CONSTANT_EXPRESSION,

            STATEMENT,
            LABELED_STATEMENT,
            EXPRESSION_STATEMENT,
            COMPOUND_STATEMENT,
            STATEMENT_SEQ,
            SELECTION_STATEMENT,
            CONDITION,
			ASSIGNMENT_EXPRESSION_CONDITION,
			ASSIGNMENT_EXPRESSION_CONDITION_TYPE_SPECIFIER_SEQ,
            ITERATION_STATEMENT,
			WHILE_STATEMENT,
			DO_WHILE_STATEMENT,
			FOR_STATEMENT,
            FOR_INIT_STATEMENT,
            JUMP_STATEMENT,
			BREAK_STATEMENT,
			CONTINUE_STATEMENT,
			RETURN_STATEMENT,
			GOTO_STATEMENT,

            DECLARATION_SEQ,
            DECLARATION,
            BLOCK_DECLARATION,
            SIMPLE_DECLARATION,
            SIMPLE_DECLARATION_DECL_SPECIFIER_SEQ,
            DECL_SPECIFIER,
            DECL_SPECIFIER_SEQ,
            STORAGE_CLASS_SPECIFIER,
            FUNCTION_SPECIFIER,
            TYPE_SPECIFIER,
            SIMPLE_TYPE_SPECIFIER,
            SIMPLE_TEMPLATE_TYPE_SPECIFIER,
            BUILT_IN_TYPE_SPECIFIER,
            IDENTIFIER_OR_TEMPLATE_ID,
            ELABORATED_TYPE_SPECIFIER,
            ENUM_SPECIFIER,
            ENUMERATOR_LIST,
            ENUMERATOR_DEFINITION,
            NAMESPACE_DEFINITION,
            NAMESPACE_ALIAS_DEFINITION,
            QUALIFIED_NAMESPACE_SPECIFIER,
            USING_DECLARATION,
            USING_DIRECTIVE,
            ASM_DEFINITION,
            LINKAGE_SPECIFICATION,

            INIT_DECLARATOR_LIST,
            INIT_DECLARATOR,
            DECLARATOR,
            DIRECT_DECLARATOR,
            DIRECT_DECLARATOR_NEXT_PART_SEQ,
            DIRECT_DECLARATOR_NEXT_PART,
            DIRECT_DECLARATOR_FUNCTION_PART,
            DIRECT_DECLARATOR_ARRAY_PART,
            PTR_OPERATOR_SEQ,
            PTR_OPERATOR,
            CV_QUALIFIER_SEQ,
            CV_QUALIFIER,
            DECLARATOR_ID,
            TYPE_ID,
            TYPE_SPECIFIER_SEQ,
            ABSTRACT_DECLARATOR,
            DIRECT_ABSTRACT_DECLARATOR,
            PARAMETER_DECLARATION_CLAUSE,
            PARAMETER_DECLARATION_LIST,
            PARAMETER_DECLARATION,
            PARAMETER_DECLARATION_DECL_SPECIFIER_SEQ1,
            PARAMETER_DECLARATION_DECL_SPECIFIER_SEQ2,
            PARAMETER_DECLARATION_DECL_SPECIFIER_SEQ3,
            PARAMETER_DECLARATION_DECL_SPECIFIER_SEQ4,
            FUNCTION_DEFINITION,
            FUNCTION_DEFINITION_DECL_SPECIFIER_SEQ1,
            FUNCTION_DEFINITION_DECL_SPECIFIER_SEQ2,
            FUNCTION_DEFINITION_DECL_SPECIFIER_SEQ3,
            INITIALIZER,
			EQUAL_INITIALIZER,
			BRACKETED_INITIALIZER,
            INITIALIZER_CLAUSE,
			INITIALIZER_LIST_INITIALIZER_CLAUSE,
			EMPTY_INITIALIZER_LIST_INITIALIZER_CLAUSE,
            INITIALIZER_LIST,

            CLASS_SPECIFIER,
            CLASS_HEAD,
            CLASS_KEY,
            MEMBER_SPECIFICATION,
            MEMBER_SPECIFICATION_PART,
            MEMBER_SPECIFICATION_ACCESS_SPECIFIER,
            MEMBER_DECLARATION,
            MEMBER_DECLARATION_MEMBER_DECLARATOR_LIST,
            MEMBER_DECLARATION_UNQUALIFIED_ID,
            MEMBER_DECLARATION_FUNCTION_DEFINITION,
            MEMBER_DECLARATION_DECL_SPECIFIER_SEQ,
            MEMBER_DECLARATOR_LIST,
            MEMBER_DECLARATOR,
            MEMBER_DECLARATOR_DECLARATOR,
            MEMBER_DECLARATOR_BIT_FIELD_MEMBER,
            PURE_SPECIFIER,
            CONSTANT_INITIALIZER,
            DESTRUCTOR_NAME,

            BASE_CLAUSE,
            BASE_SPECIFIER_LIST,
            BASE_SPECIFIER,
            ACCESS_SPECIFIER,

            CONVERSION_FUNCTION_ID,
            CONVERSION_TYPE_ID,
            CONVERSION_DECLARATOR,
            CTOR_INITIALIZER,
            MEM_INITIALIZER_LIST,
            MEM_INITIALIZER,
            MEM_INITIALIZER_ID,

            OPERATOR_FUNCTION_ID,
            OPERATOR_,

            TEMPLATE_DECLARATION,
            TEMPLATE_PARAMETER_LIST,
            TEMPLATE_PARAMETER,
            TYPE_PARAMETER,
            TEMPLATE_ID,
            TEMPLATE_ARGUMENT_LIST,
            TEMPLATE_ARGUMENT,
            EXPLICIT_INSTANTIATION,
            EXPLICIT_SPECIALIZATION,

            TRY_BLOCK,
            FUNCTION_TRY_BLOCK,
            HANDLER_SEQ,
            HANDLER,
            EXCEPTION_DECLARATION,
            THROW_EXPRESSION,
            EXCEPTION_SPECIFICATION,
            TYPE_ID_LIST,


            TYPE_NAME,
            NESTED_IDENTIFIER_OR_TEMPLATE_ID,
            SKIP_FUNCTION_BODIES_MODE_STATEMENT_SEQ_ITEM,
            SKIP_FUNCTION_BODIES_MODE_NON_SPECIAL_CHAR_SEQ,
            SKIP_FUNCTION_BODIES_MODE_NON_SPECIAL_CHAR,


            TYPEOF_EXPRESSION,
            TYPEOF_KEYWORD,
            RESTRICT_KEYWORD
        };

        struct type_name_parser
        {
            virtual std::ptrdiff_t
            operator()(const scanner_t& scan) const = 0;
        };

    private:
        class internal_type_name_functor_parser
        {
            public:
                typedef boost::spirit::nil_t result_t;

                internal_type_name_functor_parser(type_name_parser& a_type_name_parser);

                std::ptrdiff_t
                operator()(const scanner_t& scan, result_t&) const;

            private:
                type_name_parser& type_name_parser_;
        };

    public:
        grammar(type_name_parser& a_type_name_parser);

        const boost::spirit::rule<scanner_t>&
        get_start_rule() const;

        const configuration&
        get_configuration() const;

        void
        set_configuration(const configuration& a_configuration);

    private:
        /*
        Chapter numbers refer to ISO/IEC 14882:1998(E) (C++98 Standard), Annex A (grammar summary)
        */

        /*
        Standard rules
        */
        //
        boost::spirit::rule<scanner_t> file;
        boost::spirit::rule<scanner_t> source_character_set;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::SPACE>> s;
        boost::spirit::rule<scanner_t> keyword;

        //1.2 - Lexical conventions [gram.lex]
        boost::spirit::rule<scanner_t> hex_quad;
        boost::spirit::rule<scanner_t> universal_character_name;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::IDENTIFIER>> identifier;
        boost::spirit::rule<scanner_t> nondigit;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::LITERAL>> literal;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::INTEGER_LITERAL>> integer_literal;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::DECIMAL_LITERAL>> decimal_literal;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::OCTAL_LITERAL>> octal_literal;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::HEXADECIMAL_LITERAL>> hexadecimal_literal;
        boost::spirit::rule<scanner_t> hexadecimal_digit;
        boost::spirit::rule<scanner_t> octal_digit;
        boost::spirit::rule<scanner_t> nonzero_digit;
        boost::spirit::rule<scanner_t> integer_suffix;
        boost::spirit::rule<scanner_t> unsigned_suffix;
        boost::spirit::rule<scanner_t> long_suffix;
        boost::spirit::rule<scanner_t> long_long_suffix;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::CHARACTER_LITERAL>> character_literal;
        boost::spirit::rule<scanner_t> c_char_sequence;
        boost::spirit::rule<scanner_t> c_char;
        boost::spirit::rule<scanner_t> escape_sequence;
        boost::spirit::rule<scanner_t> simple_escape_sequence;
        boost::spirit::rule<scanner_t> octal_escape_sequence;
        boost::spirit::rule<scanner_t> hexadecimal_escape_sequence;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::FLOATING_LITERAL>> floating_literal;
        boost::spirit::rule<scanner_t> fractional_constant;
        boost::spirit::rule<scanner_t> exponent_part;
        boost::spirit::rule<scanner_t> digit_sequence;
        boost::spirit::rule<scanner_t> floating_suffix;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::STRING_LITERAL>> string_literal;
        boost::spirit::rule<scanner_t> s_char_sequence;
        boost::spirit::rule<scanner_t> s_char;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::BOOLEAN_LITERAL>> boolean_literal;

        //1.3 - Basic concepts [gram.basic]
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::TRANSLATION_UNIT>> translation_unit;

        //1.4 - Expressions [gram.expr]
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::PRIMARY_EXPRESSION>> primary_expression;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::ID_EXPRESSION>> id_expression;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::UNQUALIFIED_ID>> unqualified_id;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::QUALIFIED_ID>> qualified_id;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::QUALIFIED_NESTED_ID>> qualified_nested_id;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::QUALIFIED_OPERATOR_FUNCTION_ID>> qualified_operator_function_id;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::QUALIFIED_TEMPLATE_ID>> qualified_template_id;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::QUALIFIED_IDENTIFIER>> qualified_identifier;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::NESTED_NAME_SPECIFIER>> nested_name_specifier;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::NESTED_NAME_SPECIFIER_NEXT_PART_SEQ>> nested_name_specifier_next_part_seq;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::NESTED_NAME_SPECIFIER_NEXT_PART>> nested_name_specifier_next_part;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::POSTFIX_EXPRESSION>> postfix_expression;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::EXPRESSION_LIST>> expression_list;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::PSEUDO_DESTRUCTOR_NAME>> pseudo_destructor_name;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::UNARY_EXPRESSION>> unary_expression;
		boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::UNARY_OPERATOR_UNARY_EXPRESSION>> unary_operator_unary_expression;
		boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::TYPE_ID_SIZEOF_EXPRESSION>> type_id_sizeof_expression;
		boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::UNARY_SIZEOF_EXPRESSION>> unary_sizeof_expression;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::UNARY_OPERATOR>> unary_operator;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::NEW_EXPRESSION>> new_expression;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::NEW_PLACEMENT>> new_placement;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::NEW_TYPE_ID>> new_type_id;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::NEW_DECLARATOR>> new_declarator;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::DIRECT_NEW_DECLARATOR>> direct_new_declarator;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::NEW_INITIALIZER>> new_initializer;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::DELETE_EXPRESSION>> delete_expression;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::CAST_EXPRESSION>> cast_expression;
        boost::spirit::rule<scanner_t> pm_ptr_expression;
        boost::spirit::rule<scanner_t> pm_ref_expression;
        boost::spirit::rule<scanner_t> modulo_expression;
        boost::spirit::rule<scanner_t> divisive_expression;
        boost::spirit::rule<scanner_t> multiplicative_expression;
        boost::spirit::rule<scanner_t> subtractive_expression;
        boost::spirit::rule<scanner_t> additive_expression;
        boost::spirit::rule<scanner_t> left_shift_expression;
        boost::spirit::rule<scanner_t> right_shift_expression;
        boost::spirit::rule<scanner_t> template_argument_right_shift_expression;
        boost::spirit::rule<scanner_t> less_than_or_equal_to_expression;
        boost::spirit::rule<scanner_t> template_less_than_or_equal_to_expression;
        boost::spirit::rule<scanner_t> less_than_expression;
        boost::spirit::rule<scanner_t> template_less_than_expression;
        boost::spirit::rule<scanner_t> greater_than_or_equal_to_expression;
        boost::spirit::rule<scanner_t> template_greater_than_or_equal_to_expression;
        boost::spirit::rule<scanner_t> greater_than_expression;
        boost::spirit::rule<scanner_t> template_greater_than_expression;
        boost::spirit::rule<scanner_t> inequality_expression;
        boost::spirit::rule<scanner_t> template_argument_inequality_expression;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::EQUALITY_EXPRESSION>> equality_expression;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::TEMPLATE_ARGUMENT_EQUALITY_EXPRESSION>> template_argument_equality_expression;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::AND_EXPRESSION>> and_expression;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::TEMPLATE_ARGUMENT_AND_EXPRESSION>> template_argument_and_expression;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::EXCLUSIVE_OR_EXPRESSION>> exclusive_or_expression;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::TEMPLATE_ARGUMENT_EXCLUSIVE_OR_EXPRESSION>> template_argument_exclusive_or_expression;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::INCLUSIVE_OR_EXPRESSION>> inclusive_or_expression;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::TEMPLATE_ARGUMENT_INCLUSIVE_OR_EXPRESSION>> template_argument_inclusive_or_expression;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::LOGICAL_AND_EXPRESSION>> logical_and_expression;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::TEMPLATE_ARGUMENT_LOGICAL_AND_EXPRESSION>> template_argument_logical_and_expression;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::LOGICAL_OR_EXPRESSION>> logical_or_expression;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::TEMPLATE_ARGUMENT_LOGICAL_OR_EXPRESSION>> template_argument_logical_or_expression;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::CONDITIONAL_EXPRESSION>> conditional_expression;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::TEMPLATE_ARGUMENT_CONDITIONAL_EXPRESSION>> template_argument_conditional_expression;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::ASSIGNMENT_EXPRESSION>> assignment_expression;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::ASSIGNMENT_EXPRESSION_FIRST_PART_SEQ>> assignment_expression_first_part_seq;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::ASSIGNMENT_EXPRESSION_FIRST_PART>> assignment_expression_first_part;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::TEMPLATE_ARGUMENT_ASSIGNMENT_EXPRESSION>> template_argument_assignment_expression;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::ASSIGNMENT_OPERATOR>> assignment_operator;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::EXPRESSION>> expression;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::CONSTANT_EXPRESSION>> constant_expression;

        //1.5 - Statements [gram.stmt.stmt]
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::STATEMENT>> statement;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::LABELED_STATEMENT>> labeled_statement;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::EXPRESSION_STATEMENT>> expression_statement;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::COMPOUND_STATEMENT>> compound_statement;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::STATEMENT_SEQ>> statement_seq;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::SELECTION_STATEMENT>> selection_statement;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::CONDITION>> condition;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::ASSIGNMENT_EXPRESSION_CONDITION>> assignment_expression_condition;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::ASSIGNMENT_EXPRESSION_CONDITION_TYPE_SPECIFIER_SEQ>> assignment_expression_condition_type_specifier_seq;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::ITERATION_STATEMENT>> iteration_statement;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::WHILE_STATEMENT>> while_statement;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::DO_WHILE_STATEMENT>> do_while_statement;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::FOR_STATEMENT>> for_statement;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::FOR_INIT_STATEMENT>> for_init_statement;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::JUMP_STATEMENT>> jump_statement;
		boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::BREAK_STATEMENT>> break_statement;
		boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::CONTINUE_STATEMENT>> continue_statement;
		boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::RETURN_STATEMENT>> return_statement;
		boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::GOTO_STATEMENT>> goto_statement;

        //1.6 - Declarations [gram.dcl.dcl]
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::DECLARATION_SEQ>> declaration_seq;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::DECLARATION>> declaration;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::BLOCK_DECLARATION>> block_declaration;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::SIMPLE_DECLARATION>> simple_declaration;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::SIMPLE_DECLARATION_DECL_SPECIFIER_SEQ>> simple_declaration_decl_specifier_seq;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::DECL_SPECIFIER>> decl_specifier;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::DECL_SPECIFIER_SEQ>> decl_specifier_seq;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::STORAGE_CLASS_SPECIFIER>> storage_class_specifier;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::FUNCTION_SPECIFIER>> function_specifier;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::TYPE_SPECIFIER>> type_specifier;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::SIMPLE_TYPE_SPECIFIER>> simple_type_specifier;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::SIMPLE_TEMPLATE_TYPE_SPECIFIER>> simple_template_type_specifier;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::BUILT_IN_TYPE_SPECIFIER>> built_in_type_specifier;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::ELABORATED_TYPE_SPECIFIER>> elaborated_type_specifier;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::ENUM_SPECIFIER>> enum_specifier;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::ENUMERATOR_LIST>> enumerator_list;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::ENUMERATOR_DEFINITION>> enumerator_definition;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::NAMESPACE_DEFINITION>> namespace_definition;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::NAMESPACE_ALIAS_DEFINITION>> namespace_alias_definition;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::QUALIFIED_NAMESPACE_SPECIFIER>> qualified_namespace_specifier;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::USING_DECLARATION>> using_declaration;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::USING_DIRECTIVE>> using_directive;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::ASM_DEFINITION>> asm_definition;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::LINKAGE_SPECIFICATION>> linkage_specification;

        //1.7 - Declarators [gram.dcl.decl]
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::INIT_DECLARATOR_LIST>> init_declarator_list;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::INIT_DECLARATOR>> init_declarator;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::DECLARATOR>> declarator;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::DIRECT_DECLARATOR>> direct_declarator;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::DIRECT_DECLARATOR_NEXT_PART_SEQ>> direct_declarator_next_part_seq;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::DIRECT_DECLARATOR_NEXT_PART>> direct_declarator_next_part;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::DIRECT_DECLARATOR_FUNCTION_PART>> direct_declarator_function_part;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::DIRECT_DECLARATOR_ARRAY_PART>> direct_declarator_array_part;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::PTR_OPERATOR_SEQ>> ptr_operator_seq;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::PTR_OPERATOR>> ptr_operator;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::CV_QUALIFIER_SEQ>> cv_qualifier_seq;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::CV_QUALIFIER>> cv_qualifier;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::DECLARATOR_ID>> declarator_id;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::TYPE_ID>> type_id;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::TYPE_SPECIFIER_SEQ>> type_specifier_seq;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::ABSTRACT_DECLARATOR>> abstract_declarator;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::DIRECT_ABSTRACT_DECLARATOR>> direct_abstract_declarator;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::PARAMETER_DECLARATION_CLAUSE>> parameter_declaration_clause;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::PARAMETER_DECLARATION_LIST>> parameter_declaration_list;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::PARAMETER_DECLARATION>> parameter_declaration;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::PARAMETER_DECLARATION_DECL_SPECIFIER_SEQ1>> parameter_declaration_decl_specifier_seq1;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::PARAMETER_DECLARATION_DECL_SPECIFIER_SEQ2>> parameter_declaration_decl_specifier_seq2;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::PARAMETER_DECLARATION_DECL_SPECIFIER_SEQ3>> parameter_declaration_decl_specifier_seq3;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::PARAMETER_DECLARATION_DECL_SPECIFIER_SEQ4>> parameter_declaration_decl_specifier_seq4;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::FUNCTION_DEFINITION>> function_definition;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::FUNCTION_DEFINITION_DECL_SPECIFIER_SEQ1>> function_definition_decl_specifier_seq1;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::FUNCTION_DEFINITION_DECL_SPECIFIER_SEQ2>> function_definition_decl_specifier_seq2;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::FUNCTION_DEFINITION_DECL_SPECIFIER_SEQ3>> function_definition_decl_specifier_seq3;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::INITIALIZER>> initializer;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::EQUAL_INITIALIZER>> equal_initializer;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::BRACKETED_INITIALIZER>> bracketed_initializer;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::INITIALIZER_CLAUSE>> initializer_clause;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::INITIALIZER_LIST_INITIALIZER_CLAUSE>> initializer_list_initializer_clause;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::EMPTY_INITIALIZER_LIST_INITIALIZER_CLAUSE>> empty_initializer_list_initializer_clause;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::INITIALIZER_LIST>> initializer_list;

        //1.8 - Classes [gram.class]
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::CLASS_SPECIFIER>> class_specifier;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::CLASS_HEAD>> class_head;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::CLASS_KEY>> class_key;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::MEMBER_SPECIFICATION>> member_specification;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::MEMBER_SPECIFICATION_PART>> member_specification_part;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::MEMBER_SPECIFICATION_ACCESS_SPECIFIER>> member_specification_access_specifier;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::MEMBER_DECLARATION>> member_declaration;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::MEMBER_DECLARATION_MEMBER_DECLARATOR_LIST>> member_declaration_member_declarator_list;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::MEMBER_DECLARATION_UNQUALIFIED_ID>> member_declaration_unqualified_id;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::MEMBER_DECLARATION_FUNCTION_DEFINITION>> member_declaration_function_definition;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::MEMBER_DECLARATION_DECL_SPECIFIER_SEQ>> member_declaration_decl_specifier_seq;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::MEMBER_DECLARATOR_LIST>> member_declarator_list;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::MEMBER_DECLARATOR>> member_declarator;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::MEMBER_DECLARATOR_DECLARATOR>> member_declarator_declarator;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::MEMBER_DECLARATOR_BIT_FIELD_MEMBER>> member_declarator_bit_field_member;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::PURE_SPECIFIER>> pure_specifier;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::CONSTANT_INITIALIZER>> constant_initializer;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::DESTRUCTOR_NAME>> destructor_name;

        //1.9 - Derived classes [gram.class.derived]
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::BASE_CLAUSE>> base_clause;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::BASE_SPECIFIER_LIST>> base_specifier_list;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::BASE_SPECIFIER>> base_specifier;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::ACCESS_SPECIFIER>> access_specifier;

        //1.10 - Special member functions [gram.special]
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::CONVERSION_FUNCTION_ID>> conversion_function_id;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::CONVERSION_TYPE_ID>> conversion_type_id;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::CONVERSION_DECLARATOR>> conversion_declarator;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::CTOR_INITIALIZER>> ctor_initializer;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::MEM_INITIALIZER_LIST>> mem_initializer_list;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::MEM_INITIALIZER>> mem_initializer;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::MEM_INITIALIZER_ID>> mem_initializer_id;

        //1.11 - Overloading [gram.over]
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::OPERATOR_FUNCTION_ID>> operator_function_id;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::OPERATOR_>> operator_;

        //1.12 - Templates [gram.temp]
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::TEMPLATE_DECLARATION>> template_declaration;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::TEMPLATE_PARAMETER_LIST>> template_parameter_list;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::TEMPLATE_PARAMETER>> template_parameter;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::TYPE_PARAMETER>> type_parameter;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::TEMPLATE_ID>> template_id;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::TEMPLATE_ARGUMENT_LIST>> template_argument_list;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::TEMPLATE_ARGUMENT>> template_argument;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::EXPLICIT_INSTANTIATION>> explicit_instantiation;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::EXPLICIT_SPECIALIZATION>> explicit_specialization;

        //1.13 - Exception handling [gram.except]
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::TRY_BLOCK>> try_block;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::FUNCTION_TRY_BLOCK>> function_try_block;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::HANDLER_SEQ>> handler_seq;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::HANDLER>> handler;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::EXCEPTION_DECLARATION>> exception_declaration;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::THROW_EXPRESSION>> throw_expression;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::EXCEPTION_SPECIFICATION>> exception_specification;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::TYPE_ID_LIST>> type_id_list;


        /*
        Convenience rules
        */
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::TYPE_NAME>> type_name;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::IDENTIFIER_OR_TEMPLATE_ID>> identifier_or_template_id;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::NESTED_IDENTIFIER_OR_TEMPLATE_ID>> nested_identifier_or_template_id;


        /*
        Non-standard extensions
        */
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::TYPEOF_EXPRESSION>> typeof_expression;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::TYPEOF_KEYWORD>> typeof_keyword;
        boost::spirit::rule<scanner_t, boost::spirit::parser_context<>, boost::spirit::parser_tag<grammar::RESTRICT_KEYWORD>> restrict_keyword;


        /*
        Functor parsers
        */
        internal_type_name_functor_parser internal_type_name_parser_;
        boost::spirit::functor_parser<internal_type_name_functor_parser> type_name_p;


        /*
        Others
        */
        configuration configuration_;
};

}} //namespace socoa::cpp

#endif
