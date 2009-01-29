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

#ifndef SOCOA_CPP_GRAMMAR_DEFINITION_IMPL_H
#define SOCOA_CPP_GRAMMAR_DEFINITION_IMPL_H

#include <boost/spirit/core.hpp>
#include <boost/spirit/utility/chset.hpp>
#include <boost/spirit/utility/functor_parser.hpp>
#include "grammar.h"
#include "functor_parsers/type_name.h"

namespace socoa { namespace cpp
{

template <typename ScannerT>
struct grammar_definition_initializer
{
    typedef typename ScannerT::iterator_t iterator_t;

    grammar_definition_initializer
    (
        grammar::definition<ScannerT>& def,
        const grammar& gram
    );


    /*
    Functor parsers
    */
    functor_parsers::type_name type_name_parser_;
    boost::spirit::functor_parser<functor_parsers::type_name> type_name_p;
};

template<typename ScannerT>
grammar_definition_initializer<ScannerT>::grammar_definition_initializer
(
    grammar::definition<ScannerT>& def,
    const grammar& gram
):
    type_name_p(type_name_parser_)
{
    using namespace boost::spirit;

    def.file
        = def.translation_unit
    ;

    def.source_character_set
        = no_node_d
        [
            chset_p("a-zA-Z0-9")
            | '_'
            | '{'
            | '}'
            | '['
            | ']'
            | '#'
            | '('
            | ')'
            | '<'
            | '>'
            | '%'
            | ':'
            | ';'
            | '.'
            | '?'
            | '*'
            | '+'
            | '-'
            | '/'
            | '^'
            | '&'
            | '|'
            | '~'
            | '!'
            | '='
            | ','
            | '\\'
            | '"'
            | '\''
            | ' '  //space
            | '\t' //horizontal tab
            | '\v' //vertical tab
            | '\f' //form feed
            | '\n' //new line
        ]
    ;

    /*
    Sorted in inverse alphabetical order to prevent scanner to parse e.g. "do" when scanning "double"
    Longest to shortest order would have been right too.
    */
    def.keyword
        = no_node_d
        [
            str_p("xor_eq")
            | "xor"
            | "while"
            | "wchar_t"
            | "volatile"
            | "void"
            | "virtual"
            | "using"
            | "unsigned"
            | "union"
            | def.typeof_keyword
            | "typename"
            | "typeid"
            | "typedef"
            | "try"
            | "true"
            | "throw"
            | "this"
            | "template"
            | "switch"
            | "struct"
            | "static_cast"
            | "static"
            | "sizeof"
            | "signed"
            | "short"
            | "return"
            | def.restrict_keyword
            | "reinterpret_cast"
            | "register"
            | "public"
            | "protected"
            | "private"
            | "or_eq"
            | "or"
            | "operator"
            | "not_eq"
            | "not"
            | "new"
            | "namespace"
            | "mutable"
            | "long"
            | "int"
            | "inline"
            | "if"
            | "goto"
            | "friend"
            | "for"
            | "float"
            | "false"
            | "extern"
            | "export"
            | "explicit"
            | "enum"
            | "else"
            | "dynamic_cast"
            | "double"
            | "do"
            | "delete"
            | "default"
            | "continue"
            | "const_cast"
            | "const"
            | "compl"
            | "class"
            | "char"
            | "catch"
            | "case"
            | "break"
            | "bool"
            | "bitor"
            | "bitand"
            | "auto"
            | "asm"
            | "and_eq"
            | "and"
        ]
    ;


    //1.2 - Lexical conventions [gram.lex]
    def.hex_quad
        = def.hexadecimal_digit >> def.hexadecimal_digit >> def.hexadecimal_digit >> def.hexadecimal_digit
    ;

    def.universal_character_name
        = lexeme_d[str_p("\\u") >> def.hex_quad]
        | lexeme_d[str_p("\\U") >> def.hex_quad >> def.hex_quad]
    ;

    def.identifier
        = token_node_d
        [
            (def.nondigit >> *(def.nondigit | digit_p)) - def.keyword
        ]
    ;

    def.nondigit
        = no_node_d
        [
            def.universal_character_name
            | chset_p("a-zA-Z")
            | '_'
        ]
    ;

    def.literal
        = def.boolean_literal
        | def.character_literal
        | def.string_literal
        | def.floating_literal
        | def.integer_literal
    ;

    def.integer_literal
        = lexeme_d[def.decimal_literal >> !def.integer_suffix]
        | lexeme_d[def.hexadecimal_literal >> !def.integer_suffix]
        | lexeme_d[def.octal_literal >> !def.integer_suffix]
    ;

    def.decimal_literal
        = lexeme_d[def.nonzero_digit >> *digit_p]
    ;

    def.octal_literal
        = lexeme_d['0' >> *def.octal_digit]
    ;

    def.hexadecimal_literal
        = lexeme_d[(str_p("0x") | "0X") >> +def.hexadecimal_digit]
    ;

    def.hexadecimal_digit
        = chset_p("0-9a-fA-F")
    ;

    def.octal_digit
        = chset_p("0-7")
    ;

    def.nonzero_digit
        = chset_p("1-9")
    ;

    def.integer_suffix
        = def.unsigned_suffix >> !(def.long_long_suffix | def.long_suffix)
        | (def.long_long_suffix | def.long_suffix) >> !def.unsigned_suffix
    ;

    def.unsigned_suffix
        = ch_p('u') | 'U'
    ;

    def.long_suffix
        = ch_p('l') | 'L'
    ;

    def.long_long_suffix
        = str_p("ll") | "LL"
    ;

    def.character_literal
        = lexeme_d['\'' >> def.c_char_sequence >> '\'']
        | lexeme_d["L\'" >> def.c_char_sequence >> '\'']
    ;

    def.c_char_sequence
        = +def.c_char
    ;

    def.c_char
        = (def.source_character_set & ~ch_p('\'') & ~ch_p('\\') & ~ch_p('\n'))
        | def.escape_sequence
        | def.universal_character_name
    ;

    def.escape_sequence
        = def.simple_escape_sequence
        | def.octal_escape_sequence
        | def.hexadecimal_escape_sequence
    ;

    def.simple_escape_sequence
        = str_p("\\'")
        | "\\\""
        | "\\?"
        | "\\\\"
        | "\\a"
        | "\\b"
        | "\\f"
        | "\\n"
        | "\\r"
        | "\\t"
        | "\\v"
    ;

    def.octal_escape_sequence
        = lexeme_d['\\' >> def.octal_digit >> !def.octal_digit >> !def.octal_digit]
    ;

    def.hexadecimal_escape_sequence
        = lexeme_d["\\x" >> +def.hexadecimal_digit]
    ;

    def.floating_literal
        = lexeme_d[def.fractional_constant >> !def.exponent_part >> !def.floating_suffix]
        | lexeme_d[def.digit_sequence >> def.exponent_part >> !def.floating_suffix]
    ;

    def.fractional_constant
        = !def.digit_sequence >> '.' >> def.digit_sequence
        | def.digit_sequence >> '.'
    ;

    def.exponent_part
        = ch_p('e') >> !sign_p >> def.digit_sequence
        | ch_p('E') >> !sign_p >> def.digit_sequence
    ;

    def.digit_sequence
        = +digit_p
    ;

    def.floating_suffix
        = ch_p('f')
        | 'l'
        | 'F'
        | 'L'
    ;

    def.string_literal
        = +('"' >> !def.s_char_sequence >> '"')
        | +("L\"" >> !def.s_char_sequence >> '"')
    ;

    def.s_char_sequence
        = +def.s_char
    ;

    def.s_char
        = (def.source_character_set & ~ch_p('"') & ~ch_p('\\') & ~ch_p('\n'))
        | def.escape_sequence
        | def.universal_character_name
    ;

    def.boolean_literal
        = str_p("false")
        | "true"
    ;

    //1.3 - Basic concepts [gram.basic]
    def.translation_unit
        = !def.declaration_seq >> end_p
    ;

    //1.4 - Expressions [gram.expr]
    def.primary_expression
        = "this"
        | def.literal
        | '(' >> def.expression >> ')'
        | def.id_expression
    ;

    def.id_expression
        = def.qualified_id
        | def.unqualified_id
    ;

    def.unqualified_id
        = def.operator_function_id
        | def.conversion_function_id
        | def.destructor_name
        | def.template_id
        | def.identifier
    ;

    def.qualified_id
        = def.qualified_nested_id
        | def.qualified_operator_function_id
        | def.qualified_template_id
        | def.qualified_identifier
    ;
    def.qualified_nested_id
        = !str_p("::") >> def.nested_name_specifier >> !str_p("template") >> def.unqualified_id
    ;
    def.qualified_operator_function_id
        = str_p("::") >> def.operator_function_id
    ;
    def.qualified_template_id
        = str_p("::") >> def.template_id
    ;
    def.qualified_identifier
        = str_p("::") >> def.identifier
    ;

    /*
        nested_name_specifier
            = identifier_or_template_id >> "::"
            | nested_name_specifier >> identifier >> "::"
            | nested_name_specifier >> !str_p("template") >> template_id >> "::"
        ;
    */
    def.nested_name_specifier
        = def.identifier_or_template_id >> "::" >> *((def.nested_name_specifier_template_id_part | def.identifier) >> "::")
    ;
    def.nested_name_specifier_template_id_part
        = !str_p("template") >> def.template_id
    ;

    /*
    The following rule is written like this in the standard:
        postfix_expression
            = primary_expression
            | postfix_expression >> '[' >> expression >> ']'
            | postfix_expression >> '(' >> !expression_list >> ')'
            | simple_type_specifier >> '(' >> !expression_list >> ')'
            | str_p("typename") >> !str_p("::") >> nested_name_specifier >> identifier >> '(' >> !expression_list >> ')'
            | str_p("typename") >> !str_p("::") >> nested_name_specifier >> !str_p("template") >> template_id >> '(' >> !expression_list >> ')'
            | postfix_expression >> '.' >> !str_p("template") >> id_expression
            | postfix_expression >> "->" >> !str_p("template") >> id_expression
            | postfix_expression >> '.' >> pseudo_destructor_name
            | postfix_expression >> "->" >> pseudo_destructor_name
            | postfix_expression >> "++"
            | postfix_expression >> "--"
            | str_p("dynamic_cast") >> '<' >> type_id >> '>' >> '(' >> expression >> ')'
            | str_p("static_cast") >> '<' >> type_id >> '>' >> '(' >> expression >> ')'
            | str_p("reinterpret_cast") >> '<' >> type_id >> '>' >> '(' >> expression >> ')'
            | str_p("const_cast") >> '<' >> type_id >> '>' >> '(' >> expression >> ')'
            | str_p("typeid") >> '(' >> expression >> ')'
            | str_p("typeid") >> '(' >> type_id >> ')'
        ;
    There are some left recursions that we had to eliminate.
    See direct_declarator rule for more information about the different steps to follow.
    */
    def.postfix_expression
        =
        (
            def.primary_expression
            | def.simple_type_specifier >> '(' >> !def.expression_list >> ')'
            | str_p("typename") >> !str_p("::") >> def.nested_name_specifier >> def.identifier >> '(' >> !def.expression_list >> ')'
            | str_p("typename") >> !str_p("::") >> def.nested_name_specifier >> !str_p("template") >> def.template_id >> '(' >> !def.expression_list >> ')'
            | str_p("dynamic_cast") >> '<' >> def.type_id >> '>' >> '(' >> def.expression >> ')'
            | str_p("static_cast") >> '<' >> def.type_id >> '>' >> '(' >> def.expression >> ')'
            | str_p("reinterpret_cast") >> '<' >> def.type_id >> '>' >> '(' >> def.expression >> ')'
            | str_p("const_cast") >> '<' >> def.type_id >> '>' >> '(' >> def.expression >> ')'
            | str_p("typeid") >> '(' >> def.expression >> ')'
            | str_p("typeid") >> '(' >> def.type_id >> ')'
        )
        >>
        *(
            '[' >> def.expression >> ']'
            | '(' >> !def.expression_list >> ')'
            | '.' >> !str_p("template") >> def.id_expression
            | "->" >> !str_p("template") >> def.id_expression
            | '.' >> def.pseudo_destructor_name
            | "->" >> def.pseudo_destructor_name
            | "++"
            | "--"
        )
    ;

    def.expression_list
        = def.assignment_expression % ','
    ;

    def.pseudo_destructor_name
        = def.nested_identifier_or_template_id >> str_p("::") >> '~' >> def.identifier_or_template_id
        | !str_p("::") >> def.nested_name_specifier >> str_p("template") >> def.template_id >> str_p("::") >> '~' >> def.identifier_or_template_id
        | !str_p("::") >> !def.nested_name_specifier >> '~' >> def.identifier_or_template_id
    ;

    def.unary_expression
        = "++" >> def.cast_expression
        | "--" >> def.cast_expression
        | def.unary_operator >> def.cast_expression
        | str_p("sizeof") >> '(' >> def.type_id >> ')'
        | str_p("sizeof") >> def.unary_expression
        | def.postfix_expression
        | def.new_expression
        | def.delete_expression
    ;

    def.unary_operator
        = ch_p('*')
        | '&'
        | '+'
        | '-'
        | '!'
        | '~'
    ;

    def.new_expression
        = !str_p("::") >> str_p("new") >> !def.new_placement >> '(' >> def.type_id >> ')' >> !def.new_initializer
        | !str_p("::") >> str_p("new") >> !def.new_placement >> def.new_type_id >> !def.new_initializer
    ;

    def.new_placement
        = '(' >> def.expression_list >> ')'
    ;

    def.new_type_id
        = def.type_specifier_seq >> !def.new_declarator
    ;

    def.new_declarator
        = def.ptr_operator >> !def.new_declarator
        | def.direct_new_declarator
    ;

    def.direct_new_declarator
        = '[' >> def.expression >> ']' >> !('[' >> def.constant_expression >> ']')
    ;

    def.new_initializer
        = '(' >> !def.expression_list >> ')'
    ;

    def.delete_expression
        = !str_p("::") >> "delete" >> '[' >> ']' >> def.cast_expression
        | !str_p("::") >> "delete" >> def.cast_expression
    ;

    def.cast_expression
        = '(' >> def.type_id >> ')' >> def.cast_expression
        | def.unary_expression
    ;

    def.pm_ptr_expression
        = def.cast_expression % "->*"
    ;

    def.pm_ref_expression
        = def.pm_ptr_expression % ".*"
    ;

    def.modulo_expression
        = def.pm_ref_expression % '%'
    ;

    def.divisive_expression
        = def.modulo_expression % '/'
    ;

    def.multiplicative_expression
        = def.divisive_expression % '*'
    ;

    def.subtractive_expression
        = def.multiplicative_expression % '-'
    ;

    def.additive_expression
        = def.subtractive_expression % '+'
    ;

    def.left_shift_expression
        = def.additive_expression % "<<"
    ;

    def.right_shift_expression
        = def.left_shift_expression % ">>"
    ;
    //a shift expression used as a template argument must be placed between brackets if it contains any '>' characters
    def.template_argument_right_shift_expression
        = '(' >> (def.left_shift_expression % ">>") >> ')'
        | def.left_shift_expression
    ;

    def.less_than_or_equal_to_expression
        = def.right_shift_expression % "<="
    ;
    def.template_less_than_or_equal_to_expression
        = def.template_argument_right_shift_expression
    ;

    def.less_than_expression
        = def.less_than_or_equal_to_expression % '<'
    ;
    def.template_less_than_expression
        = def.template_less_than_or_equal_to_expression
    ;

    def.greater_than_or_equal_to_expression
        = def.less_than_expression % ">="
    ;
    //a shift expression used as a template argument must be placed between brackets if it contains any '>' characters
    def.template_greater_than_or_equal_to_expression
        = '(' >> (def.less_than_expression % ">=") >> ')'
        | def.template_less_than_expression
    ;

    def.greater_than_expression
        = def.greater_than_or_equal_to_expression % '>'
    ;
    //a shift expression used as a template argument must be placed between brackets if it contains any '>' characters
    def.template_greater_than_expression
        = '(' >> (def.greater_than_or_equal_to_expression % '>') >> ')'
        | def.template_greater_than_or_equal_to_expression
    ;

    def.inequality_expression
        = def.greater_than_expression % "!="
    ;
    def.template_argument_inequality_expression
        = def.template_greater_than_expression % "!="
    ;

    def.equality_expression
        = def.inequality_expression % "=="
    ;
    def.template_argument_equality_expression
        = def.template_argument_inequality_expression % "=="
    ;

    def.and_expression
        = def.equality_expression % '&'
    ;
    def.template_argument_and_expression
        = def.template_argument_equality_expression % '&'
    ;

    def.exclusive_or_expression
        = def.and_expression % '^'
    ;
    def.template_argument_exclusive_or_expression
        = def.template_argument_and_expression % '^'
    ;

    def.inclusive_or_expression
        = def.exclusive_or_expression % '|'
    ;
    def.template_argument_inclusive_or_expression
        = def.template_argument_exclusive_or_expression % '|'
    ;

    def.logical_and_expression
        = def.inclusive_or_expression % "&&"
    ;
    def.template_argument_logical_and_expression
        = def.template_argument_inclusive_or_expression % "&&"
    ;

    def.logical_or_expression
        = def.logical_and_expression % "||"
    ;
    def.template_argument_logical_or_expression
        = def.template_argument_logical_and_expression % "||"
    ;

    def.conditional_expression
        = def.logical_or_expression >> !('?' >> def.expression >> ':' >> def.assignment_expression)
    ;
    def.template_argument_conditional_expression
        = def.template_argument_logical_or_expression >> !('?' >> def.expression >> ':' >> def.template_argument_assignment_expression)
    ;

    def.assignment_expression
        = def.logical_or_expression >> def.assignment_operator >> def.assignment_expression
        | def.conditional_expression
        | def.throw_expression
    ;
    def.template_argument_assignment_expression
        = def.template_argument_logical_or_expression >> def.assignment_operator >> def.template_argument_assignment_expression
        | def.template_argument_conditional_expression
        | def.throw_expression
    ;

    def.assignment_operator
        = str_p("=")
        | "*="
        | "/="
        | "%="
        | "+="
        | "-="
        | ">>="
        | "<<="
        | "&="
        | "^="
        | "|="
    ;

    def.expression
        = def.assignment_expression % ','
    ;

    def.constant_expression
        = def.conditional_expression
    ;

    //1.5 - Statements [gram.stmt.stmt]
    def.statement
        = def.labeled_statement
        | def.expression_statement
        | def.compound_statement
        | def.selection_statement
        | def.iteration_statement
        | def.jump_statement
        | def.declaration_statement
        | def.try_block
    ;

    def.labeled_statement
        = str_p("case") >> def.constant_expression >> ':' >> def.statement
        | str_p("default") >> ':' >> def.statement
        | def.identifier >> ':' >> def.statement
    ;

    def.expression_statement
        = !def.expression >> ch_p(';')
    ;

    def.compound_statement
        = ch_p('{') >> !def.statement_seq >> ch_p('}')
    ;

    if(gram.get_configuration().skip_function_bodies)
    {
        def.statement_seq
            = +def.skip_function_bodies_mode_statement_seq_item
        ;
        def.skip_function_bodies_mode_statement_seq_item
            = token_node_d
            [
                def.character_literal
                | def.string_literal
                | def.compound_statement
                | def.skip_function_bodies_mode_non_special_char_seq
            ]
        ;
    }
    else
    {
        def.statement_seq
            = +def.statement
        ;
    }

    def.selection_statement
        = str_p("if") >> '(' >> def.condition >> ')' >> def.statement >> !("else" >> def.statement)
        | str_p("switch") >> '(' >> def.condition >> ')' >> def.statement
    ;

    /*
    Original rule is:
        condition
            = expression
            | type_specifier_seq >> declarator >> '=' >> assignment_expression
        ;
    */
    def.condition
        = def.expression
        | def.condition_type_specifier_seq >> def.declarator >> '=' >> def.assignment_expression
    ;
    def.condition_type_specifier_seq
        = +(def.type_specifier - (def.declarator >> '=' >> def.assignment_expression))
    ;

    def.iteration_statement
        = str_p("while") >> '(' >> def.condition >> ')' >> def.statement
        | str_p("do") >> def.statement >> "while" >> '(' >> def.expression >> ')' >> ch_p(';')
        | str_p("for") >> '(' >> def.for_init_statement >> !def.condition >> ch_p(';') >> !def.expression >> ')' >> def.statement
    ;

    def.for_init_statement
        = def.expression_statement
        | def.simple_declaration
    ;

    def.jump_statement
        = str_p("break") >> ch_p(';')
        | str_p("continue") >> ch_p(';')
        | str_p("return") >> !def.expression >> ch_p(';')
        | str_p("goto") >> def.identifier >> ch_p(';')
    ;

    def.declaration_statement
        = def.block_declaration
    ;

    //1.6 - Declarations [gram.dcl.dcl]
    def.declaration_seq
        = +def.declaration
    ;

    def.declaration
        = def.block_declaration
        | def.function_definition
        | def.template_declaration
        | def.explicit_instantiation
        | def.explicit_specialization
        | def.linkage_specification
        | def.namespace_definition
    ;

    def.block_declaration
        = def.asm_definition
        | def.simple_declaration
        | def.namespace_alias_definition
        | def.using_declaration
        | def.using_directive
    ;

    /*
    The following rule is written like this in the standard:
        simple_declaration
            = !decl_specifier_seq >> !init_declarator_list >> ch_p(';')
        ;
    If we wrote it that way, with such an input:
        int i, j;
    The scanner will parse "i" as a decl_specifier (it is indeed a correct identifier_or_template_id).
    Consequently, when it will try to parse the comma, it will raise an error.

    In order to solve this issue, we have to create an extra rule which specifies a tail parser.
    */
    ///@todo semantic disambiguation between decl_specifier and init_declarator_list
    def.simple_declaration
        = !def.simple_declaration_decl_specifier_seq >> !def.init_declarator_list >> ch_p(';')
    ;
    def.simple_declaration_decl_specifier_seq
        = +(def.decl_specifier - (def.init_declarator_list >> ch_p(';')))
    ;

    def.decl_specifier
        = def.storage_class_specifier
        | def.type_specifier
        | def.function_specifier
        | str_p("friend")
        | str_p("typedef")
    ;

    def.decl_specifier_seq
        = +def.decl_specifier
    ;

    def.storage_class_specifier
        = str_p("auto")
        | str_p("register")
        | str_p("static")
        | str_p("extern")
        | str_p("mutable")
    ;

    def.function_specifier
        = str_p("inline")
        | "virtual"
        | "explicit"
    ;

    def.type_specifier
        = def.simple_type_specifier
        | def.class_specifier
        | def.enum_specifier
        | def.elaborated_type_specifier
        | def.cv_qualifier
        | def.typeof_expression
    ;

    def.simple_type_specifier
        = def.nested_identifier_or_template_id
        | def.simple_template_type_specifier
        | def.built_in_type_specifier
    ;
    def.simple_template_type_specifier
        = !str_p("::") >> def.nested_name_specifier >> "template" >> def.template_id
    ;
    def.built_in_type_specifier
        = str_p("char")
        | "wchar_t"
        | "bool"
        | "short"
        | "int"
        | "long"
        | "signed"
        | "unsigned"
        | "float"
        | "double"
        | "void"
    ;

    def.elaborated_type_specifier
        = def.class_key >> !str_p("::") >> !def.nested_name_specifier >> def.template_id //not in the standard, but seems to be required for parsing standard library
        | def.class_key >> !str_p("::") >> !def.nested_name_specifier >> def.identifier
        | str_p("enum") >> !str_p("::") >> !def.nested_name_specifier >> def.identifier
        | str_p("typename") >> !str_p("::") >> def.nested_name_specifier >> !str_p("template") >> def.template_id
        | str_p("typename") >> !str_p("::") >> def.nested_name_specifier >> def.identifier
    ;

    def.enum_specifier
        = str_p("enum") >> !def.identifier >> ch_p('{') >> !def.enumerator_list >> ch_p('}')
    ;

    def.enumerator_list
        = def.enumerator_definition % ','
    ;

    def.enumerator_definition
        = def.identifier >> !('=' >> def.constant_expression)
    ;

    def.namespace_definition
        = str_p("namespace") >> !def.identifier >> '{' >> !def.declaration_seq >> '}'
    ;

    def.namespace_alias_definition
        = str_p("namespace") >> def.identifier >> '=' >> def.qualified_namespace_specifier >> ch_p(';')
    ;

    def.qualified_namespace_specifier
        = !str_p("::") >> !def.nested_name_specifier >> def.identifier
    ;

    def.using_declaration
        = "using" >> !str_p("typename") >> !str_p("::") >> def.nested_name_specifier >> def.unqualified_id >> ch_p(';')
        | "using" >> str_p("::") >> def.unqualified_id >> ch_p(';')
    ;

    def.using_directive
        = str_p("using") >> "namespace" >> !str_p("::") >> !def.nested_name_specifier >> def.identifier >> ch_p(';')
    ;

    def.asm_definition
        = str_p("asm") >> '(' >> def.string_literal >> ')' >> ch_p(';')
    ;

    def.linkage_specification
        = "extern" >> def.string_literal >> ch_p('{') >> !def.declaration_seq >> ch_p('}')
        | "extern" >> def.string_literal >> def.declaration
    ;

    //1.7 - Declarators [gram.dcl.decl]
    def.init_declarator_list
        = def.init_declarator % ','
    ;

    def.init_declarator
        = def.declarator >> !def.initializer
    ;

    /*
    Original rule is:
        declarator
            = ptr_operator >> declarator
            | direct_declarator
        ;
    */
    def.declarator
        = *def.ptr_operator >> def.direct_declarator
    ;

    /*
    Original rule is:
        direct_declarator
            = declarator_id
            | direct_declarator >> '(' >> parameter_declaration_clause >> ')' >> !cv_qualifier_seq >> !exception_specification
            | direct_declarator >> '[' >> !constant_expression >> ']'
            | '(' >> declarator >> ')'
        ;

    We had to eliminate left recursion. There have been the different steps for this elimination:

        direct_declarator
            = declarator_id
            | '(' >> declarator >> ')'
            | direct_declarator >> direct_declarator_rest
        ;
        direct_declarator_rest
            = '(' >> parameter_declaration_clause >> ')' >> !cv_qualifier_seq >> !exception_specification
            | '[' >> !constant_expression >> ']'
        ;

        ***

        direct_declarator
            = (declarator_id | '(' >> declarator >> ')') >> direct_declarator_rest

        ;
        direct_declarator_rest
            = '(' >> parameter_declaration_clause >> ')' >> !cv_qualifier_seq >> !exception_specification >> direct_declarator_rest
            | '[' >> !constant_expression >> ']' >> direct_declarator_rest
            | epsilon_p
        ;

        ***

        direct_declarator
            = (declarator_id | '(' >> declarator >> ')') >> direct_declarator_rest
        ;
        direct_declarator_rest
            =
                (
                    '(' >> parameter_declaration_clause >> ')' >> !cv_qualifier_seq >> !exception_specification
                    | '[' >> !constant_expression >> ']'
                ) >> direct_declarator_rest
            | epsilon_p
        ;

        ***

        direct_declarator
            = (declarator_id | '(' >> declarator >> ')') >> direct_declarator_rest
        ;
        direct_declarator_rest
            =
                !(
                    (
                        '(' >> parameter_declaration_clause >> ')' >> !cv_qualifier_seq >> !exception_specification
                        | '[' >> !constant_expression >> ']'
                    )
                    >> direct_declarator_rest
                )
        ;

        ***

        direct_declarator
            = (declarator_id | '(' >> declarator >> ')') >> direct_declarator_rest
        ;
        direct_declarator_rest
            =
                *(

                    '(' >> parameter_declaration_clause >> ')' >> !cv_qualifier_seq >> !exception_specification
                    | '[' >> !constant_expression >> ']'
                )
        ;
    */
    def.direct_declarator
        =
        (
            def.declarator_id
            | '(' >> def.declarator >> ')'
        )
        >>
        *(
            def.direct_declarator_function_part
            | def.direct_declarator_array_part
        )
    ;
    def.direct_declarator_function_part
        = '(' >> def.parameter_declaration_clause >> ')' >> !def.cv_qualifier_seq >> !def.exception_specification
    ;
    def.direct_declarator_array_part
        = '[' >> !def.constant_expression >> ']'
    ;

    def.ptr_operator
        = ch_p('*') >> !def.cv_qualifier_seq
        | ch_p('&')
        | !str_p("::") >> def.nested_name_specifier >> '*' >> !def.cv_qualifier_seq
    ;

    def.cv_qualifier_seq
        = +def.cv_qualifier
    ;

    def.cv_qualifier
        = str_p("const")
        | "volatile"
        | def.restrict_keyword
    ;

    def.declarator_id
        = def.id_expression
        | def.nested_identifier_or_template_id
    ;

    def.type_id
        = def.type_specifier_seq >> !def.abstract_declarator
    ;

    def.type_specifier_seq
        = +def.type_specifier
    ;

    def.abstract_declarator
        = +def.ptr_operator
        | def.direct_abstract_declarator
    ;

    /*
    Original rule is:
        direct_abstract_declarator
            = !direct_abstract_declarator >> '(' >> parameter_declaration_clause >> ')' >> !cv_qualifier_seq >> !exception_specification
            | !direct_abstract_declarator >> '[' >> !constant_expression >> ']'
            | '(' >> abstract_declarator >> ')'
        ;
    */
    def.direct_abstract_declarator
        =
        !(
            '(' >> def.abstract_declarator >> ')'
        )
        >>
        *(
            '(' >> def.parameter_declaration_clause >> ')' >> !def.cv_qualifier_seq >> !def.exception_specification
            | '[' >> !def.constant_expression >> ']'
        )
    ;

    def.parameter_declaration_clause
        = def.parameter_declaration_list >> ',' >> "..."
        | !def.parameter_declaration_list >> !str_p("...")
    ;

    def.parameter_declaration_list
        = def.parameter_declaration % ','
    ;

    def.parameter_declaration
        = def.parameter_declaration_decl_specifier_seq1 >> def.declarator >> '=' >> def.assignment_expression
        | def.parameter_declaration_decl_specifier_seq2 >> def.declarator
        | def.parameter_declaration_decl_specifier_seq3 >> def.abstract_declarator >> '=' >> def.assignment_expression
        | def.parameter_declaration_decl_specifier_seq4 >> !def.abstract_declarator
        | def.decl_specifier_seq >> '=' >> def.assignment_expression
    ;
    def.parameter_declaration_decl_specifier_seq1
        = +(def.decl_specifier - (def.declarator >> '=' >> def.assignment_expression))
    ;
    def.parameter_declaration_decl_specifier_seq2
        = +(def.decl_specifier - (def.declarator >> (ch_p(',') | ')' | "...")))
    ;
    def.parameter_declaration_decl_specifier_seq3
        = +(def.decl_specifier - (def.abstract_declarator >> '=' >> def.assignment_expression))
    ;
    def.parameter_declaration_decl_specifier_seq4
        = +(def.decl_specifier - (def.abstract_declarator >> (ch_p(',') | ')' | "...")))
    ;


    /*
    Original rule is:
        function_definition
            = !decl_specifier_seq >> declarator >> !ctor_initializer >> function_body
            | !decl_specifier_seq >> declarator >> function_try_block
        ;
    */
    def.function_definition
        = !def.function_definition_decl_specifier_seq1 >> def.declarator >> def.ctor_initializer >> def.function_body
        | !def.function_definition_decl_specifier_seq2 >> def.declarator >> def.function_body
        | !def.function_definition_decl_specifier_seq3 >> def.declarator >> def.function_try_block
    ;
    def.function_definition_decl_specifier_seq1
        = +(def.decl_specifier - (def.declarator >> def.ctor_initializer >> def.function_body))
    ;
    def.function_definition_decl_specifier_seq2
        = +(def.decl_specifier - (def.declarator >> def.function_body))
    ;
    def.function_definition_decl_specifier_seq3
        = +(def.decl_specifier - (def.declarator >> def.function_try_block))
    ;

    def.function_body
        = def.compound_statement
    ;

    def.initializer
        = ch_p('=') >> def.initializer_clause
        | ch_p('(') >> def.expression_list >> ')'
    ;

    def.initializer_clause
        = def.assignment_expression
        | ch_p('{') >> def.initializer_list >> !ch_p(',') >> ch_p('}')
        | ch_p('{') >> ch_p('}')
    ;

    def.initializer_list
        = def.initializer_clause % ','
    ;

    //1.8 - Classes [gram.class]
    def.class_specifier
        = def.class_head >> '{' >> !def.member_specification >> '}'
    ;

    def.class_head
        = def.class_key >> !def.nested_name_specifier >> def.template_id >> !def.base_clause //class template specialization -> the class already had been declared
        | def.class_key >> def.nested_name_specifier >> def.identifier >> !def.base_clause //ditto
        | def.class_key >> !def.identifier >> !def.base_clause
    ;

    def.class_key
        = token_node_d
        [
            str_p("class")
            | "struct"
            | "union"
        ]
    ;

    def.member_specification
        = *(def.member_declaration | def.member_specification_access_specifier)
    ;
    def.member_specification_access_specifier
        = def.access_specifier >> ':'
    ;

    def.member_declaration
        = def.member_declaration_member_declarator_list
        | def.member_declaration_unqualified_id
        | def.member_declaration_function_definition
        | def.using_declaration
        | def.template_declaration
    ;
    def.member_declaration_member_declarator_list
        = !def.member_declaration_decl_specifier_seq >> !def.member_declarator_list >> ch_p(';')
    ;
    def.member_declaration_unqualified_id
        = !str_p("::") >> def.nested_name_specifier >> !str_p("template") >> def.unqualified_id >> ch_p(';')
    ;
    def.member_declaration_function_definition
        = def.function_definition >> !ch_p(';')
    ;
    def.member_declaration_decl_specifier_seq
        = +(def.decl_specifier - (def.member_declarator_list >> ch_p(';')))
    ;

    def.member_declarator_list
        = def.member_declarator % ','
    ;

    def.member_declarator
        = def.member_declarator_declarator
        | def.member_declarator_bit_field_member
    ;
    def.member_declarator_declarator
        = def.declarator >> !(def.pure_specifier | def.constant_initializer) ///@todo find what declarator >> constant_initializer stands for
    ;
    def.member_declarator_bit_field_member
        = !def.identifier >> ':' >> def.constant_expression //bit field member
    ;

    def.pure_specifier
        = ch_p('=') >> '0'
    ;

    def.constant_initializer
        = '=' >> def.constant_expression
    ;

    //convenience rule, not explicitly in the standard
    def.destructor_name
        = '~' >> def.identifier_or_template_id
    ;


    //1.9 - Derived classes [gram.class.derived]
    def.base_clause
        = ':' >> def.base_specifier_list
    ;

    def.base_specifier_list
        = def.base_specifier % ','
    ;

    def.base_specifier
        = def.nested_identifier_or_template_id
        | "virtual" >> !def.access_specifier >> def.nested_identifier_or_template_id
        | def.access_specifier >> !str_p("virtual") >> def.nested_identifier_or_template_id
    ;

    def.access_specifier
        = token_node_d
        [
            str_p("private")
            | "protected"
            | "public"
        ]
    ;

    //1.10 - Special member functions [gram.special]
    def.conversion_function_id
        = str_p("operator") >> def.conversion_type_id
    ;

    def.conversion_type_id
        = def.type_specifier_seq >> !def.conversion_declarator
    ;

    def.conversion_declarator
        = +def.ptr_operator
    ;

    def.ctor_initializer
        = ':' >> def.mem_initializer_list
    ;

    def.mem_initializer_list
        = def.mem_initializer % ','
    ;

    def.mem_initializer
        = def.mem_initializer_id >> '(' >> !def.expression_list >> ')'
    ;

    def.mem_initializer_id
        = def.nested_identifier_or_template_id
        | def.identifier
    ;

    //1.11 - Overloading [gram.over]
    def.operator_function_id
        = str_p("operator") >> def.operator_
    ;

    def.operator_
        = str_p("new[]")
        | "delete[]"
        | "new"
        | "delete"
        | ">>="
        | "<<="
        | "->*"
        | "+="
        | "-="
        | "*="
        | "/="
        | "%="
        | "^="
        | "&="
        | "|="
        | "<<"
        | ">>"
        | "=="
        | "!="
        | "<="
        | ">="
        | "&&"
        | "||"
        | "++"
        | "--"
        | "->"
        | "()"
        | "[]"
        | ","
        | "+"
        | "-"
        | "*"
        | "/"
        | "%"
        | "^"
        | "&"
        | "|"
        | "~"
        | "!"
        | "="
        | "<"
        | ">"
    ;

    //1.12 - Templates [gram.temp]
    def.template_declaration
        = !str_p("export") >> str_p("template") >> '<' >> def.template_parameter_list >> '>' >> def.declaration
    ;

    def.template_parameter_list
        = def.template_parameter % ','
    ;

    def.template_parameter
        = def.type_parameter
        | def.parameter_declaration
    ;

    def.type_parameter
        = str_p("class") >> !def.identifier >> '=' >> def.type_id
        | str_p("class") >> !def.identifier
        | str_p("typename") >> !def.identifier >> '=' >> def.type_id
        | str_p("typename") >> !def.identifier
        | str_p("template") >> '<' >> def.template_parameter_list >> '>' >> str_p("class") >> !def.identifier >> '=' >> def.id_expression
        | str_p("template") >> '<' >> def.template_parameter_list >> '>' >> str_p("class") >> !def.identifier
    ;

    def.template_id
        = def.type_name >> '<' >> !def.template_argument_list >> '>'
    ;

    def.template_argument_list
        = def.template_argument % ','
    ;

    def.template_argument
        = longest_d
        [
            def.template_argument_assignment_expression //As assignment_expression can contain a '>', we cannot use it directly
            | def.type_id
            | def.id_expression
        ]
    ;

    def.explicit_instantiation
        = !str_p("extern") >> str_p("template") >> def.declaration
    ;

    def.explicit_specialization
        = str_p("template") >> '<' >> '>' >> def.declaration
    ;

    //1.13 - Exception handling [gram.except]
    def.try_block
        = str_p("try") >> def.compound_statement >> def.handler_seq
    ;

    def.function_try_block
        = str_p("try") >> !def.ctor_initializer >> def.function_body >> def.handler_seq
    ;

    def.handler_seq
        = +def.handler
    ;

    def.handler
        = str_p("catch") >> '(' >> def.exception_declaration >> ')' >> def.compound_statement
    ;

    def.exception_declaration
        = def.type_specifier_seq >> def.declarator
        | def.type_specifier_seq >> def.abstract_declarator
        | def.type_specifier_seq
        | "..."
    ;

    def.throw_expression
        = "throw" >> !def.assignment_expression
    ;

    def.exception_specification
        = str_p("throw") >> '(' >> !def.type_id_list >> ')'
    ;

    def.type_id_list
        = def.type_id % ','
    ;


    /*
    Convenience rules
    */
    // !space_p   -> we don't want to have to parse any space char in type_name_p
    // identifier -> we have to read last_parsed_identifier_ in type_name_p
    def.type_name
        = token_node_d[!space_p >> (def.identifier & type_name_p)]
    ;

    def.identifier_or_template_id
        = def.template_id
        | def.identifier
    ;

    def.nested_identifier_or_template_id
        = !str_p("::") >> !def.nested_name_specifier >> def.identifier_or_template_id
    ;

    //Convenience rules for declaration-only mode
    def.skip_function_bodies_mode_non_special_char_seq
        = +def.skip_function_bodies_mode_non_special_char
    ;
    def.skip_function_bodies_mode_non_special_char
        = anychar_p - (ch_p('"') | '\'' | '{' | '}')
    ;


    /*
    Extensions
    These rules are not in the standard, but are required to parse some standard library implementations
    */
    if(gram.get_configuration().enable_typeof_support)
    {
        def.typeof_expression
            = def.typeof_keyword >> '(' >> def.expression >> ')'
        ;

        def.typeof_keyword
            = str_p("__typeof__")
            | "__typeof"
            | "typeof"
        ;
    }

    if(gram.get_configuration().enable_restrict_support)
    {
        def.restrict_keyword
            = str_p("__restrict__")
            | "__restrict"
            | "restrict"
        ;
    }
}

}} //namespace socoa::cpp

#endif
