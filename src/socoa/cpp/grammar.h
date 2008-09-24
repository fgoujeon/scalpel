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

#ifndef SOCOA_CPP_GRAMMAR_H
#define SOCOA_CPP_GRAMMAR_H

#include <memory>
#include <boost/spirit/core.hpp>

namespace socoa { namespace cpp
{

template <typename ScannerT>
class grammar_definition_impl;

class grammar: public boost::spirit::grammar<grammar>
{
    public:
        template <typename ScannerT>
        class definition
        {
            public:
                definition(const grammar& self);

                const boost::spirit::rule<ScannerT>&
                start() const;

            private:
                std::shared_ptr<grammar_definition_impl<ScannerT>> pimpl_;
        };

        struct configuration
        {
            configuration():
                skip_function_bodies(false),
                enable_typeof_support(true),
                enable_restrict_support(true)
            {
            }

            bool skip_function_bodies;

            bool enable_typeof_support;
            bool enable_restrict_support;
        };

        enum parser_id
        {
            FILE,
            SOURCE_CHARACTER_SET,
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
            NESTED_NAME_SPECIFIER,
            NESTED_NAME_SPECIFIER_TEMPLATE_ID_PART,
            POSTFIX_EXPRESSION,
            EXPRESSION_LIST,
            PSEUDO_DESTRUCTOR_NAME,
            UNARY_EXPRESSION,
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
            CONDITION_TYPE_SPECIFIER_SEQ,
            ITERATION_STATEMENT,
            FOR_INIT_STATEMENT,
            JUMP_STATEMENT,
            DECLARATION_STATEMENT,

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
            DIRECT_DECLARATOR_FUNCTION_PART,
            DIRECT_DECLARATOR_ARRAY_PART,
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
            FUNCTION_BODY,
            INITIALIZER,
            INITIALIZER_CLAUSE,
            INITIALIZER_LIST,

            CLASS_SPECIFIER,
            CLASS_HEAD,
            CLASS_KEY,
            MEMBER_SPECIFICATION,
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


            NESTED_IDENTIFIER_OR_TEMPLATE_ID,
            SKIP_FUNCTION_BODIES_MODE_STATEMENT_SEQ_ITEM,
            SKIP_FUNCTION_BODIES_MODE_NON_SPECIAL_CHAR_SEQ,
            SKIP_FUNCTION_BODIES_MODE_NON_SPECIAL_CHAR,


            TYPEOF_EXPRESSION,
            TYPEOF_KEYWORD,
            RESTRICT_KEYWORD
        };

        grammar(configuration& a_configuration);

        const configuration&
        get_configuration() const;

    private:
        configuration& configuration_;
};

}} //namespace socoa::cpp

#endif
