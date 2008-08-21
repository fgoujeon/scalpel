/*
CppParser - Standard C++ programming language parsing library
Copyright © 2008  Florian Goujeon

This file is part of CppParser.

CppParser is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, version 3 of the License.

CppParser is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with CppParser.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CPPPARSER_PARSING_GRAMMAR_H
#define CPPPARSER_PARSING_GRAMMAR_H

#include <boost/spirit.hpp>
#include "cursor.h"
#include "semantic_actions/enter_namespace.h"
#include "semantic_actions/leave_namespace.h"

namespace cppparser { namespace parsing
{

class grammar: public boost::spirit::grammar<grammar>
{
    public:
        grammar(bool gcc_extensions_support_enabled = true):
            m_gcc_extensions_support_enabled(gcc_extensions_support_enabled)
        {
        }

        bool
        is_gcc_extensions_support_enabled() const
        {
            return m_gcc_extensions_support_enabled;
        }

        template <typename ScannerT>
        struct definition
        {
            definition(const grammar& self);
            boost::spirit::rule<ScannerT> const& start() const;


            /*
            Comments refer to ISO/IEC 14882:1998(E) (C++98 Standard), Annex A (grammar summary)
            */

            boost::spirit::rule<ScannerT> file;

            boost::spirit::rule<ScannerT> source_character_set;
            boost::spirit::rule<ScannerT> keyword;

            //1.2 - Lexical conventions [gram.lex]
            boost::spirit::rule<typename boost::spirit::lexeme_scanner<ScannerT>::type> hex_quad;
            boost::spirit::rule<ScannerT> universal_character_name;
            boost::spirit::rule<ScannerT> preprocessing_token;
            boost::spirit::rule<ScannerT> token;
            boost::spirit::rule<ScannerT> header_name;
            boost::spirit::rule<ScannerT> h_char_sequence;
            boost::spirit::rule<ScannerT> h_char;
            boost::spirit::rule<ScannerT> q_char_sequence;
            boost::spirit::rule<ScannerT> q_char;
            //boost::spirit::rule<ScannerT> pp_number;
            boost::spirit::rule<ScannerT> identifier;
            boost::spirit::rule<typename boost::spirit::lexeme_scanner<ScannerT>::type> nondigit;
            /*boost::spirit::rule<ScannerT> preprocessing_op_or_punc;*/
            boost::spirit::rule<ScannerT> literal;
            boost::spirit::rule<ScannerT> integer_literal;
            boost::spirit::rule<ScannerT> decimal_literal;
            boost::spirit::rule<ScannerT> octal_literal;
            boost::spirit::rule<ScannerT> hexadecimal_literal;
            boost::spirit::rule<typename boost::spirit::lexeme_scanner<ScannerT>::type> hexadecimal_digit;
            boost::spirit::rule<typename boost::spirit::lexeme_scanner<ScannerT>::type> octal_digit;
            boost::spirit::rule<typename boost::spirit::lexeme_scanner<ScannerT>::type> nonzero_digit;
            boost::spirit::rule<typename boost::spirit::lexeme_scanner<ScannerT>::type> integer_suffix;
            boost::spirit::rule<typename boost::spirit::lexeme_scanner<ScannerT>::type> unsigned_suffix;
            boost::spirit::rule<typename boost::spirit::lexeme_scanner<ScannerT>::type> long_suffix;
            boost::spirit::rule<typename boost::spirit::lexeme_scanner<ScannerT>::type> long_long_suffix;
            boost::spirit::rule<ScannerT> character_literal;
            boost::spirit::rule<typename boost::spirit::lexeme_scanner<ScannerT>::type> c_char_sequence;
            boost::spirit::rule<typename boost::spirit::lexeme_scanner<ScannerT>::type> c_char;
            boost::spirit::rule<ScannerT> escape_sequence;
            boost::spirit::rule<ScannerT> simple_escape_sequence;
            boost::spirit::rule<ScannerT> octal_escape_sequence;
            boost::spirit::rule<ScannerT> hexadecimal_escape_sequence;
            boost::spirit::rule<ScannerT> floating_literal;
            boost::spirit::rule<typename boost::spirit::lexeme_scanner<ScannerT>::type> fractional_constant;
            boost::spirit::rule<typename boost::spirit::lexeme_scanner<ScannerT>::type> exponent_part;
            boost::spirit::rule<typename boost::spirit::lexeme_scanner<ScannerT>::type> digit_sequence;
            boost::spirit::rule<typename boost::spirit::lexeme_scanner<ScannerT>::type> floating_suffix;
            boost::spirit::rule<ScannerT> string_literal;
            boost::spirit::rule<ScannerT> s_char_sequence;
            boost::spirit::rule<ScannerT> s_char;
            boost::spirit::rule<ScannerT> boolean_literal;

            //1.3 - Basic concepts [gram.basic]
            boost::spirit::rule<ScannerT> translation_unit;

            //1.4 - Expressions [gram.expr]
            boost::spirit::rule<ScannerT> primary_expression;
            boost::spirit::rule<ScannerT> id_expression;
            boost::spirit::rule<ScannerT> unqualified_id;
            boost::spirit::rule<ScannerT> qualified_id;
            boost::spirit::rule<ScannerT> nested_name_specifier;
            boost::spirit::rule<ScannerT> class_or_namespace_name;
            boost::spirit::rule<ScannerT> postfix_expression;
            boost::spirit::rule<ScannerT> expression_list;
            boost::spirit::rule<ScannerT> pseudo_destructor_name;
            boost::spirit::rule<ScannerT> unary_expression;
            boost::spirit::rule<ScannerT> unary_operator;
            boost::spirit::rule<ScannerT> new_expression;
            boost::spirit::rule<ScannerT> new_placement;
            boost::spirit::rule<ScannerT> new_type_id;
            boost::spirit::rule<ScannerT> new_declarator;
            boost::spirit::rule<ScannerT> direct_new_declarator;
            boost::spirit::rule<ScannerT> new_initializer;
            boost::spirit::rule<ScannerT> delete_expression;
            boost::spirit::rule<ScannerT> cast_expression;
            boost::spirit::rule<ScannerT> pm_expression;
            boost::spirit::rule<ScannerT> multiplicative_expression;
            boost::spirit::rule<ScannerT> additive_expression;
            boost::spirit::rule<ScannerT> shift_expression;
            boost::spirit::rule<ScannerT> template_argument_shift_expression;
            boost::spirit::rule<ScannerT> relational_expression;
            boost::spirit::rule<ScannerT> template_argument_relational_expression;
            boost::spirit::rule<ScannerT> equality_expression;
            boost::spirit::rule<ScannerT> template_argument_equality_expression;
            boost::spirit::rule<ScannerT> and_expression;
            boost::spirit::rule<ScannerT> template_argument_and_expression;
            boost::spirit::rule<ScannerT> exclusive_or_expression;
            boost::spirit::rule<ScannerT> template_argument_exclusive_or_expression;
            boost::spirit::rule<ScannerT> inclusive_or_expression;
            boost::spirit::rule<ScannerT> template_argument_inclusive_or_expression;
            boost::spirit::rule<ScannerT> logical_and_expression;
            boost::spirit::rule<ScannerT> template_argument_logical_and_expression;
            boost::spirit::rule<ScannerT> logical_or_expression;
            boost::spirit::rule<ScannerT> template_argument_logical_or_expression;
            boost::spirit::rule<ScannerT> conditional_expression;
            boost::spirit::rule<ScannerT> template_argument_conditional_expression;
            boost::spirit::rule<ScannerT> assignment_expression;
            boost::spirit::rule<ScannerT> template_argument_assignment_expression;
            boost::spirit::rule<ScannerT> assignment_operator;
            boost::spirit::rule<ScannerT> expression;
            boost::spirit::rule<ScannerT> constant_expression;

            //1.5 - Statements [gram.stmt.stmt]
            boost::spirit::rule<ScannerT> statement;
            boost::spirit::rule<ScannerT> labeled_statement;
            boost::spirit::rule<ScannerT> expression_statement;
            boost::spirit::rule<ScannerT> compound_statement;
            boost::spirit::rule<ScannerT> statement_seq;
            boost::spirit::rule<ScannerT> selection_statement;
            boost::spirit::rule<ScannerT> condition;
            boost::spirit::rule<ScannerT> condition_type_specifier_seq;
            boost::spirit::rule<ScannerT> iteration_statement;
            boost::spirit::rule<ScannerT> for_init_statement;
            boost::spirit::rule<ScannerT> jump_statement;
            boost::spirit::rule<ScannerT> declaration_statement;

            //1.6 - Declarations [gram.dcl.dcl]
            boost::spirit::rule<ScannerT> declaration_seq;
            boost::spirit::rule<ScannerT> declaration;
            boost::spirit::rule<ScannerT> block_declaration;
            boost::spirit::rule<ScannerT> simple_declaration;
            boost::spirit::rule<ScannerT> simple_declaration_decl_specifier_seq;
            boost::spirit::rule<ScannerT> decl_specifier;
            boost::spirit::rule<ScannerT> decl_specifier_seq;
            boost::spirit::rule<ScannerT> storage_class_specifier;
            boost::spirit::rule<ScannerT> function_specifier;
            boost::spirit::rule<ScannerT> typedef_name;
            boost::spirit::rule<ScannerT> type_specifier;
            boost::spirit::rule<ScannerT> simple_type_specifier;
            boost::spirit::rule<ScannerT> type_name;
            boost::spirit::rule<ScannerT> elaborated_type_specifier;
            boost::spirit::rule<ScannerT> enum_name;
            boost::spirit::rule<ScannerT> enum_specifier;
            boost::spirit::rule<ScannerT> enumerator_list;
            boost::spirit::rule<ScannerT> enumerator_definition;
            boost::spirit::rule<ScannerT> enumerator;
            boost::spirit::rule<ScannerT> namespace_name;
            boost::spirit::rule<ScannerT> original_namespace_name;
            boost::spirit::rule<ScannerT> namespace_definition;
            boost::spirit::rule<ScannerT> named_namespace_definition;
            boost::spirit::rule<ScannerT> original_namespace_definition;
            boost::spirit::rule<ScannerT> extension_namespace_definition;
            boost::spirit::rule<ScannerT> unnamed_namespace_definition;
            boost::spirit::rule<ScannerT> namespace_body;
            boost::spirit::rule<ScannerT> namespace_alias;
            boost::spirit::rule<ScannerT> namespace_alias_definition;
            boost::spirit::rule<ScannerT> qualified_namespace_specifier;
            boost::spirit::rule<ScannerT> using_declaration;
            boost::spirit::rule<ScannerT> using_directive;
            boost::spirit::rule<ScannerT> asm_definition;
            boost::spirit::rule<ScannerT> linkage_specification;

            //1.7 - Declarators [gram.dcl.decl]
            boost::spirit::rule<ScannerT> init_declarator_list;
            boost::spirit::rule<ScannerT> init_declarator;
            boost::spirit::rule<ScannerT> declarator;
            boost::spirit::rule<ScannerT> direct_declarator;
            boost::spirit::rule<ScannerT> ptr_operator;
            boost::spirit::rule<ScannerT> cv_qualifier_seq;
            boost::spirit::rule<ScannerT> cv_qualifier;
            boost::spirit::rule<ScannerT> declarator_id;
            boost::spirit::rule<ScannerT> type_id;
            boost::spirit::rule<ScannerT> type_specifier_seq;
            boost::spirit::rule<ScannerT> abstract_declarator;
            boost::spirit::rule<ScannerT> direct_abstract_declarator;
            boost::spirit::rule<ScannerT> parameter_declaration_clause;
            boost::spirit::rule<ScannerT> parameter_declaration_list;
            boost::spirit::rule<ScannerT> parameter_declaration;
            boost::spirit::rule<ScannerT> parameter_declaration_decl_specifier_seq1;
            boost::spirit::rule<ScannerT> parameter_declaration_decl_specifier_seq2;
            boost::spirit::rule<ScannerT> parameter_declaration_decl_specifier_seq3;
            boost::spirit::rule<ScannerT> parameter_declaration_decl_specifier_seq4;
            boost::spirit::rule<ScannerT> function_definition;
            boost::spirit::rule<ScannerT> function_definition_decl_specifier_seq1;
            boost::spirit::rule<ScannerT> function_definition_decl_specifier_seq2;
            boost::spirit::rule<ScannerT> function_definition_decl_specifier_seq3;
            boost::spirit::rule<ScannerT> function_body;
            boost::spirit::rule<ScannerT> initializer;
            boost::spirit::rule<ScannerT> initializer_clause;
            boost::spirit::rule<ScannerT> initializer_list;

            //1.8 - Classes [gram.class]
            boost::spirit::rule<ScannerT> class_name;
            boost::spirit::rule<ScannerT> class_specifier;
            boost::spirit::rule<ScannerT> class_head;
            boost::spirit::rule<ScannerT> class_key;
            boost::spirit::rule<ScannerT> member_specification;
            boost::spirit::rule<ScannerT> member_declaration;
            boost::spirit::rule<ScannerT> member_declaration_decl_specifier_seq;
            boost::spirit::rule<ScannerT> member_declarator_list;
            boost::spirit::rule<ScannerT> member_declarator;
            boost::spirit::rule<ScannerT> pure_specifier;
            boost::spirit::rule<ScannerT> constant_initializer;

            //1.9 - Derived classes [gram.class.derived]
            boost::spirit::rule<ScannerT> base_clause;
            boost::spirit::rule<ScannerT> base_specifier_list;
            boost::spirit::rule<ScannerT> base_specifier;
            boost::spirit::rule<ScannerT> access_specifier;

            //1.10 - Special member functions [gram.special]
            boost::spirit::rule<ScannerT> conversion_function_id;
            boost::spirit::rule<ScannerT> conversion_type_id;
            boost::spirit::rule<ScannerT> conversion_declarator;
            boost::spirit::rule<ScannerT> ctor_initializer;
            boost::spirit::rule<ScannerT> mem_initializer_list;
            boost::spirit::rule<ScannerT> mem_initializer;
            boost::spirit::rule<ScannerT> mem_initializer_id;

            //1.11 - Overloading [gram.over]
            boost::spirit::rule<ScannerT> operator_function_id;
            boost::spirit::rule<ScannerT> operator_;

            //1.12 - Templates [gram.temp]
            boost::spirit::rule<ScannerT> template_declaration;
            boost::spirit::rule<ScannerT> template_parameter_list;
            boost::spirit::rule<ScannerT> template_parameter;
            boost::spirit::rule<ScannerT> type_parameter;
            boost::spirit::rule<ScannerT> template_id;
            boost::spirit::rule<ScannerT> template_name;
            boost::spirit::rule<ScannerT> template_argument_list;
            boost::spirit::rule<ScannerT> template_argument;
            boost::spirit::rule<ScannerT> explicit_instantiation;
            boost::spirit::rule<ScannerT> explicit_specialization;

            //1.13 - Exception handling [gram.except]
            boost::spirit::rule<ScannerT> try_block;
            boost::spirit::rule<ScannerT> function_try_block;
            boost::spirit::rule<ScannerT> handler_seq;
            boost::spirit::rule<ScannerT> handler;
            boost::spirit::rule<ScannerT> exception_declaration;
            boost::spirit::rule<ScannerT> throw_expression;
            boost::spirit::rule<ScannerT> exception_specification;
            boost::spirit::rule<ScannerT> type_id_list;

            //1.14 - Preprocessing directives [gram.cpp]
            boost::spirit::rule<ScannerT> preprocessing_file;
            boost::spirit::rule<ScannerT> group;
            boost::spirit::rule<ScannerT> group_part;
            boost::spirit::rule<ScannerT> if_section;
            boost::spirit::rule<ScannerT> if_group;
            boost::spirit::rule<ScannerT> elif_groups;
            boost::spirit::rule<ScannerT> elif_group;
            boost::spirit::rule<ScannerT> else_group;
            boost::spirit::rule<ScannerT> endif_line;
            boost::spirit::rule<ScannerT> control_line;
            boost::spirit::rule<ScannerT> replacement_list;
            boost::spirit::rule<ScannerT> pp_tokens;

            //GCC extensions
            boost::spirit::rule<ScannerT> gcc_typeof;

            //semantic actions
            cursor m_cursor;
            semantic_actions::enter_namespace<typename ScannerT::value_t> enter_namespace_a;
            semantic_actions::leave_namespace<typename ScannerT::value_t> leave_namespace_a;
        };

    private:
        //options
        bool m_gcc_extensions_support_enabled;
};

template<typename ScannerT>
grammar::definition<ScannerT>::definition(const grammar& self):
    enter_namespace_a(m_cursor),
    leave_namespace_a(m_cursor)
{
    using namespace boost::spirit;

    file
        = translation_unit >> end_p
    ;

    source_character_set
        = chset_p("a-zA-Z0-9")
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
    ;

    /*
    Sorted in inverse alphabetical order to prevent scanner to parse e.g. "do" when scanning "double"
    Longest to shortest order would have been right too.
    */
    keyword
        = str_p("xor_eq")
        | "xor"
        | "while"
        | "wchar_t"
        | "volatile"
        | "void"
        | "virtual"
        | "using"
        | "unsigned"
        | "union"
        | lexeme_d[!str_p("__") >> "typeof" >> !str_p("__")]
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
    ;


    //1.2 - Lexical conventions [gram.lex]
    hex_quad
        = hexadecimal_digit >> hexadecimal_digit >> hexadecimal_digit >> hexadecimal_digit
    ;

    universal_character_name
        = lexeme_d[str_p("\\u") >> hex_quad]
        | lexeme_d[str_p("\\U") >> hex_quad >> hex_quad]
    ;

    preprocessing_token
        = header_name
        | identifier
        //| pp_number
        | character_literal
        | string_literal
        //| preprocessing_op_or_punc
        //| alpha_p //each non_white_space character that cannot be one of the above
    ;

    token
        = identifier
        | keyword
        | literal
        | operator_
        //| punctuator
    ;

    header_name
        = '<' >> h_char_sequence >> '>'
        | '"' >> q_char_sequence >> '"'
    ;

    h_char_sequence
        = +h_char
    ;

    h_char
        = source_character_set - (ch_p('\n') | ch_p('>'));
    ;

    q_char_sequence
        = +q_char
    ;

    q_char
        = source_character_set - (ch_p('\n') | ch_p('\"'));
    ;
/*
    pp_number
        = digit_p
        | '.' >> digit_p
        | pp_number >> digit_p
        | pp_number >> nondigit
        | pp_number >> 'e' >> sign
        | pp_number >> 'E' >> sign
        | pp_number >> '.'
    ;
*/
    identifier
        = lexeme_d[ nondigit >> *(nondigit | digit_p) ] - keyword
    ;

    nondigit
        = universal_character_name
        | chset_p("a-zA-Z")
        | '_'
    ;

/*    preprocessing_op_or_punc
        = str_p("{")
        | "}"
        | "["
        | "]"
        | "#"
        | "##"
        | "("
        | ")"
        | "<:"
        | ":>"
        | "<%"
        | "%>"
        | "%:"
        | "%:%:"
        | ";"
        | ":"
        | "..."
        | "new"
        | "delete"
        | "?"
        | "::"
        | "."
        | ".*"
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
        | ">>="
        | "<<="
        | "=="
        | "!="
        | "<="
        | ">="
        | "&&"
        | "--"
        | ","
        | "->*"
        | "->"
        | "and"
        | "and_eq"
        | "bitand"
        | "bitor"
        | "compl"
        | "not"
        | "not_eq"
        | "or"
        | "or_eq"
        | "xor"
        | "xor_eq"
    ;
*/
    literal
        = boolean_literal
        | character_literal
        | string_literal
        | floating_literal
        | integer_literal
    ;

    integer_literal
        = lexeme_d[decimal_literal >> !integer_suffix]
        | lexeme_d[hexadecimal_literal >> !integer_suffix]
        | lexeme_d[octal_literal >> !integer_suffix]
    ;

    decimal_literal
        = lexeme_d[nonzero_digit >> *digit_p]
    ;

    octal_literal
        = lexeme_d['0' >> *octal_digit]
    ;

    hexadecimal_literal
        = lexeme_d[(str_p("0x") | "0X") >> +hexadecimal_digit]
    ;

    hexadecimal_digit
        = chset_p("0-9a-fA-F")
    ;

    octal_digit
        = chset_p("0-7")
    ;

    nonzero_digit
        = chset_p("1-9")
    ;

    integer_suffix
        = unsigned_suffix >> !(long_long_suffix | long_suffix)
        | (long_long_suffix | long_suffix) >> !unsigned_suffix
    ;

    unsigned_suffix
        = ch_p('u') | 'U'
    ;

    long_suffix
        = ch_p('l') | 'L'
    ;

    long_long_suffix
        = str_p("ll") | "LL"
    ;

    character_literal
        = lexeme_d['\'' >> c_char_sequence >> '\'']
        | lexeme_d["L\'" >> c_char_sequence >> '\'']
    ;

    c_char_sequence
        = +c_char
    ;

    c_char
        = (source_character_set & ~ch_p('\'') & ~ch_p('\\') & ~ch_p('\n'))
        | escape_sequence
        | universal_character_name
    ;

    escape_sequence
        = simple_escape_sequence
        | octal_escape_sequence
        | hexadecimal_escape_sequence
    ;

    simple_escape_sequence
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

    octal_escape_sequence
        = lexeme_d['\\' >> octal_digit >> !octal_digit >> !octal_digit]
    ;

    hexadecimal_escape_sequence
        = lexeme_d["\\x" >> +hexadecimal_digit]
    ;

    floating_literal
        = lexeme_d[fractional_constant >> !exponent_part >> !floating_suffix]
        | lexeme_d[digit_sequence >> exponent_part >> !floating_suffix]
    ;

    fractional_constant
        = !digit_sequence >> '.' >> digit_sequence
        | digit_sequence >> '.'
    ;

    exponent_part
        = ch_p('e') >> !sign_p >> digit_sequence
        | ch_p('E') >> !sign_p >> digit_sequence
    ;

    digit_sequence
        = +digit_p
    ;

    floating_suffix
        = ch_p('f')
        | 'l'
        | 'F'
        | 'L'
    ;

    string_literal
        = +('"' >> !s_char_sequence >> '"')
        | +("L\"" >> !s_char_sequence >> '"')
    ;

    s_char_sequence
        = +s_char
    ;

    s_char
        = (source_character_set & ~ch_p('"') & ~ch_p('\\') & ~ch_p('\n'))
        | escape_sequence
        | universal_character_name
    ;

    boolean_literal
        = str_p("false")
        | "true"
    ;

    //1.3 - Basic concepts [gram.basic]
    translation_unit
        = !declaration_seq
    ;

    //1.4 - Expressions [gram.expr]
    primary_expression
        = "this"
        | literal
        | '(' >> expression >> ')'
        | id_expression
    ;

    id_expression
        = qualified_id
        | unqualified_id
    ;

    unqualified_id
        = operator_function_id
        | conversion_function_id
        | '~' >> class_name
        | template_id
        | identifier
    ;

    qualified_id
        = !str_p("::") >> nested_name_specifier >> !str_p("template") >> unqualified_id
        | str_p("::") >> operator_function_id
        | str_p("::") >> template_id
        | str_p("::") >> identifier
    ;

    nested_name_specifier
        = class_or_namespace_name >> str_p("::") >> "template" >> nested_name_specifier
        | class_or_namespace_name >> str_p("::") >> !nested_name_specifier
    ;

    class_or_namespace_name
        = class_name
        | namespace_name
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
    postfix_expression
        =
        (
            primary_expression
            | simple_type_specifier >> '(' >> !expression_list >> ')'
            | str_p("typename") >> !str_p("::") >> nested_name_specifier >> identifier >> '(' >> !expression_list >> ')'
            | str_p("typename") >> !str_p("::") >> nested_name_specifier >> !str_p("template") >> template_id >> '(' >> !expression_list >> ')'
            | str_p("dynamic_cast") >> '<' >> type_id >> '>' >> '(' >> expression >> ')'
            | str_p("static_cast") >> '<' >> type_id >> '>' >> '(' >> expression >> ')'
            | str_p("reinterpret_cast") >> '<' >> type_id >> '>' >> '(' >> expression >> ')'
            | str_p("const_cast") >> '<' >> type_id >> '>' >> '(' >> expression >> ')'
            | str_p("typeid") >> '(' >> expression >> ')'
            | str_p("typeid") >> '(' >> type_id >> ')'
        )
        >>
        *(
            '[' >> expression >> ']'
            | '(' >> !expression_list >> ')'
            | '.' >> !str_p("template") >> id_expression
            | "->" >> !str_p("template") >> id_expression
            | '.' >> pseudo_destructor_name
            | "->" >> pseudo_destructor_name
            | "++"
            | "--"
        )
    ;

    expression_list
        = assignment_expression % ','
    ;

    pseudo_destructor_name
        = !str_p("::") >> !nested_name_specifier >> type_name >> str_p("::") >> '~' >> type_name
        | !str_p("::") >> nested_name_specifier >> str_p("template") >> template_id >> str_p("::") >> '~' >> type_name
        | !str_p("::") >> !nested_name_specifier >> '~' >> type_name
    ;

    unary_expression
        = "++" >> cast_expression
        | "--" >> cast_expression
        | unary_operator >> cast_expression
        | str_p("sizeof") >> '(' >> type_id >> ')'
        | str_p("sizeof") >> unary_expression
        | postfix_expression
        | new_expression
        | delete_expression
    ;

    unary_operator
        = ch_p('*')
        | '&'
        | '+'
        | '-'
        | '!'
        | '~'
    ;

    new_expression
        = !str_p("::") >> str_p("new") >> !new_placement >> '(' >> type_id >> ')' >> !new_initializer
        | !str_p("::") >> str_p("new") >> !new_placement >> new_type_id >> !new_initializer
    ;

    new_placement
        = '(' >> expression_list >> ')'
    ;

    new_type_id
        = type_specifier_seq >> !new_declarator
    ;

    new_declarator
        = ptr_operator >> !new_declarator
        | direct_new_declarator
    ;

    direct_new_declarator
        = '[' >> expression >> ']' >> !('[' >> constant_expression >> ']')
    ;

    new_initializer
        = '(' >> !expression_list >> ')'
    ;

    delete_expression
        = !str_p("::") >> "delete" >> '[' >> ']' >> cast_expression
        | !str_p("::") >> "delete" >> cast_expression
    ;

    cast_expression
        = '(' >> type_id >> ')' >> cast_expression
        | unary_expression
    ;

    pm_expression
        = cast_expression % (str_p(".*") | "->*")
    ;

    multiplicative_expression
        = pm_expression % (ch_p('*') | '/' | '%')
    ;

    additive_expression
        = multiplicative_expression % (ch_p('+') | '-')
    ;

    shift_expression
        = additive_expression % (str_p("<<") | ">>")
    ;
    //a shift expression used as a template argument must be placed between braces if it contains any '>' characters
    template_argument_shift_expression
        = '(' >> (additive_expression % (str_p("<<") | ">>")) >> ')'
        | additive_expression % str_p("<<")
    ;

    relational_expression
        = shift_expression % (str_p("<=") | ">=" | '<' | '>')
    ;
    //a relational_expression used as a template argument must be placed between braces if it contains any '>' characters
    template_argument_relational_expression
        = '(' >> (shift_expression % (str_p("<=") | ">=" | '<' | '>')) >> ')'
        | template_argument_shift_expression % (str_p("<=") | '<')
    ;

    equality_expression
        = relational_expression % (str_p("==") | "!=")
    ;
    template_argument_equality_expression
        = template_argument_relational_expression % (str_p("==") | "!=")
    ;

    and_expression
        = equality_expression % '&'
    ;
    template_argument_and_expression
        = template_argument_equality_expression % '&'
    ;

    exclusive_or_expression
        = and_expression % '^'
    ;
    template_argument_exclusive_or_expression
        = template_argument_and_expression % '^'
    ;

    inclusive_or_expression
        = exclusive_or_expression % '|'
    ;
    template_argument_inclusive_or_expression
        = template_argument_exclusive_or_expression % '|'
    ;

    logical_and_expression
        = inclusive_or_expression % "&&"
    ;
    template_argument_logical_and_expression
        = template_argument_inclusive_or_expression % "&&"
    ;

    logical_or_expression
        = logical_and_expression % "||"
    ;
    template_argument_logical_or_expression
        = template_argument_logical_and_expression % "||"
    ;

    conditional_expression
        = logical_or_expression >> !('?' >> expression >> ':' >> assignment_expression)
    ;
    template_argument_conditional_expression
        = template_argument_logical_or_expression >> !('?' >> expression >> ':' >> template_argument_assignment_expression)
    ;

    assignment_expression
        = logical_or_expression >> assignment_operator >> assignment_expression
        | conditional_expression
        | throw_expression
    ;
    template_argument_assignment_expression
        = template_argument_logical_or_expression >> assignment_operator >> template_argument_assignment_expression
        | template_argument_conditional_expression
        | throw_expression
    ;

    assignment_operator
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

    expression
        = assignment_expression % ','
    ;

    constant_expression
        = conditional_expression
    ;

    //1.5 - Statements [gram.stmt.stmt]
    statement
        = labeled_statement
        | expression_statement
        | compound_statement
        | selection_statement
        | iteration_statement
        | jump_statement
        | declaration_statement
        | try_block
    ;

    labeled_statement
        = str_p("case") >> constant_expression >> ':' >> statement
        | str_p("default") >> ':' >> statement
        | identifier >> ':' >> statement
    ;

    expression_statement
        = !expression >> ch_p(';')
    ;

    compound_statement
        = ch_p('{') >> !statement_seq >> ch_p('}')
    ;

    statement_seq
        = +statement
    ;

    selection_statement
        = str_p("if") >> '(' >> condition >> ')' >> statement >> !("else" >> statement)
        | str_p("switch") >> '(' >> condition >> ')' >> statement
    ;

    /*
        condition
            = expression
            | type_specifier_seq >> declarator >> '=' >> assignment_expression
        ;
    */
    condition
        = expression
        | condition_type_specifier_seq >> declarator >> '=' >> assignment_expression
    ;
    condition_type_specifier_seq
        = +(type_specifier - (declarator >> '=' >> assignment_expression))
    ;

    iteration_statement
        = str_p("while") >> '(' >> condition >> ')' >> statement
        | str_p("do") >> statement >> "while" >> '(' >> expression >> ')' >> ch_p(';')
        | str_p("for") >> '(' >> for_init_statement >> !condition >> ch_p(';') >> !expression >> ')' >> statement
    ;

    for_init_statement
        = expression_statement
        | simple_declaration
    ;

    jump_statement
        = str_p("break") >> ch_p(';')
        | str_p("continue") >> ch_p(';')
        | str_p("return") >> !expression >> ch_p(';')
        | str_p("goto") >> identifier >> ch_p(';')
    ;

    declaration_statement
        = block_declaration
    ;

    //1.6 - Declarations [gram.dcl.dcl]
    declaration_seq
        = +declaration
    ;

    declaration
        = block_declaration
        | function_definition
        | template_declaration
        | explicit_instantiation
        | explicit_specialization
        | linkage_specification
        | namespace_definition
    ;

    block_declaration
        = asm_definition
        | simple_declaration
        | namespace_alias_definition
        | using_declaration
        | using_directive
    ;

    /*
    The following rule is written like this in the standard:
        simple_declaration
            = !decl_specifier_seq >> !init_declarator_list >> ch_p(';')
        ;
    If we wrote it in that way, with such an input:
        int i, j;
    The scanner will parse "i" as a decl_specifier (it is indeed a correct type_name).
    Consequently, when it will try to parse the comma, it will raise an error.

    In order to solve this issue, we have to create an extra rule which specify a tail parser.
    */
    ///@todo semantic disambiguation between decl_specifier and init_declarator_list
    simple_declaration
        = !simple_declaration_decl_specifier_seq >> !init_declarator_list >> ch_p(';')
    ;
    simple_declaration_decl_specifier_seq
        = +(decl_specifier - (init_declarator_list >> ch_p(';')));
    ;

    decl_specifier
        = storage_class_specifier
        | type_specifier
        | function_specifier
        | str_p("friend")
        | str_p("typedef")
    ;

    decl_specifier_seq
        = +decl_specifier
    ;

    storage_class_specifier
        = str_p("auto")
        | str_p("register")
        | str_p("static")
        | str_p("extern")
        | str_p("mutable")
    ;

    function_specifier
        = str_p("inline")
        | "virtual"
        | "explicit"
    ;

    typedef_name
        = identifier
    ;

    type_specifier
        = simple_type_specifier
        | class_specifier
        | enum_specifier
        | elaborated_type_specifier
        | cv_qualifier
        | gcc_typeof
    ;

    simple_type_specifier
        = !str_p("::") >> !nested_name_specifier >> type_name
        | !str_p("::") >> nested_name_specifier >> "template" >> template_id
        | str_p("char")
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

    type_name
        = class_name
        | enum_name
        | typedef_name
    ;

    elaborated_type_specifier
        = class_key >> !str_p("::") >> !nested_name_specifier >> template_id //not in the standard, but seems to be required for parsing standard library
        | class_key >> !str_p("::") >> !nested_name_specifier >> identifier
        | str_p("enum") >> !str_p("::") >> !nested_name_specifier >> identifier
        | str_p("typename") >> !str_p("::") >> nested_name_specifier >> !str_p("template") >> template_id
        | str_p("typename") >> !str_p("::") >> nested_name_specifier >> identifier
    ;

    enum_name
        = identifier
    ;

    enum_specifier
        = str_p("enum") >> !identifier >> ch_p('{') >> !enumerator_list >> ch_p('}')
    ;

    enumerator_list
        = enumerator_definition % ','
    ;

    enumerator_definition
        = enumerator >> !('=' >> constant_expression)
    ;

    enumerator
        = identifier
    ;

    namespace_name
        = original_namespace_name
        | namespace_alias
    ;

    original_namespace_name
        = identifier
    ;

    namespace_definition
        = named_namespace_definition
        | unnamed_namespace_definition
    ;

    named_namespace_definition
        = original_namespace_definition
        | extension_namespace_definition
    ;

    original_namespace_definition
        = str_p("namespace") >> identifier[enter_namespace_a] >> ch_p('{') >> namespace_body >> str_p("}")[leave_namespace_a]
    ;

    extension_namespace_definition
        = str_p("namespace") >> original_namespace_name >> ch_p('{') >> namespace_body >> ch_p('}')
    ;

    unnamed_namespace_definition
        = str_p("namespace") >> ch_p('{') >> str_p("")[enter_namespace_a] >> namespace_body >> ch_p('}')
    ;

    namespace_body
        = !declaration_seq
    ;

    namespace_alias
        = identifier
    ;

    namespace_alias_definition
        = str_p("namespace") >> identifier >> '=' >> qualified_namespace_specifier >> ch_p(';')
    ;

    qualified_namespace_specifier
        = !str_p("::") >> !nested_name_specifier >> namespace_name
    ;

    using_declaration
        = "using" >> !str_p("typename") >> !str_p("::") >> nested_name_specifier >> unqualified_id >> ch_p(';')
        | "using" >> str_p("::") >> unqualified_id >> ch_p(';')
    ;

    using_directive
        = str_p("using") >> "namespace" >> !str_p("::") >> !nested_name_specifier >> namespace_name >> ch_p(';')
    ;

    asm_definition
        = str_p("asm") >> '(' >> string_literal >> ')' >> ch_p(';')
    ;

    linkage_specification
        = "extern" >> string_literal >> ch_p('{') >> !declaration_seq >> ch_p('}')
        | "extern" >> string_literal >> declaration
    ;

    //1.7 - Declarators [gram.dcl.decl]
    init_declarator_list
        = init_declarator % ','
    ;

    init_declarator
        = declarator >> !initializer
    ;

    declarator
        = ptr_operator >> declarator
        | direct_declarator
    ;

    /*
    Original rule is:
        direct_declarator
            = declarator_id
            | direct_declarator >> '(' >> parameter_declaration_clause >> ')' >> !cv_qualifier_seq >> !exception_specification
            | direct_declarator >> '[' >> !constant_expression >> ']'
            | '(' >> declarator >> ')'
        ;

    We have to eliminate left recursion. There are the different steps on this elimination:

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
    direct_declarator
        =
        (
            declarator_id
            | '(' >> declarator >> ')'
        )
        >>
        *(
            '(' >> parameter_declaration_clause >> ')' >> !cv_qualifier_seq >> !exception_specification
            | '[' >> !constant_expression >> ']'
        )
    ;

    ptr_operator
        = ch_p('*') >> !cv_qualifier_seq
        | ch_p('&')
        | !str_p("::") >> nested_name_specifier >> '*' >> !cv_qualifier_seq
    ;

    cv_qualifier_seq
        = +cv_qualifier
    ;

    cv_qualifier
        = str_p("const")
        | "volatile"
    ;

    declarator_id
        = id_expression
        | !str_p("::") >> !nested_name_specifier >> type_name
    ;

    type_id
        = type_specifier_seq >> !abstract_declarator
    ;

    type_specifier_seq
        = +type_specifier
    ;

    abstract_declarator
        = +ptr_operator
        | direct_abstract_declarator
    ;

    /*
    Original rule is:
        direct_abstract_declarator
            = !direct_abstract_declarator >> '(' >> parameter_declaration_clause >> ')' >> !cv_qualifier_seq >> !exception_specification
            | !direct_abstract_declarator >> '[' >> !constant_expression >> ']'
            | '(' >> abstract_declarator >> ')'
        ;
    */
    direct_abstract_declarator
        =
        !(
            '(' >> abstract_declarator >> ')'
        )
        >>
        *(
            '(' >> parameter_declaration_clause >> ')' >> !cv_qualifier_seq >> !exception_specification
            | '[' >> !constant_expression >> ']'
        )
    ;

    parameter_declaration_clause
        = parameter_declaration_list >> ',' >> "..."
        | !parameter_declaration_list >> !str_p("...")
    ;

    parameter_declaration_list
        = parameter_declaration % ','
    ;

    parameter_declaration
        = parameter_declaration_decl_specifier_seq1 >> declarator >> '=' >> assignment_expression
        | parameter_declaration_decl_specifier_seq2 >> declarator
        | parameter_declaration_decl_specifier_seq3 >> abstract_declarator >> '=' >> assignment_expression
        | parameter_declaration_decl_specifier_seq4 >> !abstract_declarator
        | decl_specifier_seq >> '=' >> assignment_expression
    ;
    parameter_declaration_decl_specifier_seq1
        = +(decl_specifier - (declarator >> '=' >> assignment_expression))
    ;
    parameter_declaration_decl_specifier_seq2
        = +(decl_specifier - (declarator >> (ch_p(',') >> ')' >> "...")))
    ;
    parameter_declaration_decl_specifier_seq3
        = +(decl_specifier - (abstract_declarator >> '=' >> assignment_expression))
    ;
    parameter_declaration_decl_specifier_seq4
        = +(decl_specifier - (abstract_declarator >> (ch_p(',') >> ')' >> "...")))
    ;


    /*
    Original rule is:
        function_definition
            = !decl_specifier_seq >> declarator >> !ctor_initializer >> function_body
            | !decl_specifier_seq >> declarator >> function_try_block
        ;
    */
    function_definition
        = !function_definition_decl_specifier_seq1 >> declarator >> ctor_initializer >> function_body
        | !function_definition_decl_specifier_seq2 >> declarator >> function_body
        | !function_definition_decl_specifier_seq3 >> declarator >> function_try_block
    ;
    function_definition_decl_specifier_seq1
        = +(decl_specifier - (declarator >> ctor_initializer >> function_body))
    ;
    function_definition_decl_specifier_seq2
        = +(decl_specifier - (declarator >> function_body))
    ;
    function_definition_decl_specifier_seq3
        = +(decl_specifier - (declarator >> function_try_block))
    ;

    function_body
        = compound_statement
    ;

    initializer
        = ch_p('=') >> initializer_clause
        | ch_p('(') >> expression_list >> ')'
    ;

    initializer_clause
        = assignment_expression
        | ch_p('{') >> initializer_list >> !ch_p(',') >> ch_p('}')
        | ch_p('{') >> ch_p('}')
    ;

    initializer_list
        = initializer_clause % ','
    ;

    //1.8 - Classes [gram.class]
    class_name
        = template_id
        | identifier
    ;

    class_specifier
        = class_head >> ch_p('{') >> !member_specification >> ch_p('}')
    ;

    class_head
        = class_key >> !nested_name_specifier >> template_id >> !base_clause
        | class_key >> nested_name_specifier >> identifier >> !base_clause
        | class_key >> !identifier >> !base_clause
    ;

    class_key
        = str_p("class")
        | "struct"
        | "union"
    ;

    member_specification
        = member_declaration >> !member_specification
        | access_specifier >> ':' >> !member_specification
    ;

    member_declaration
        = !member_declaration_decl_specifier_seq >> !member_declarator_list >> ch_p(';')
        | !str_p("::") >> nested_name_specifier >> !str_p("template") >> unqualified_id >> ch_p(';')
        | function_definition >> !ch_p(';')
        | using_declaration
        | template_declaration
    ;
    member_declaration_decl_specifier_seq
        = +(decl_specifier - (member_declarator_list >> ch_p(';')))
    ;

    member_declarator_list
        = member_declarator % ','
    ;

    member_declarator
        = declarator >> !(pure_specifier | constant_initializer) ///@todo find what declarator >> constant_initializer stands for
        | !identifier >> ':' >> constant_expression ///@todo find what's that
    ;

    pure_specifier
        = ch_p('=') >> '0'
    ;

    constant_initializer
        = '=' >> constant_expression
    ;

    //1.9 - Derived classes [gram.class.derived]
    base_clause
        = ':' >> base_specifier_list
    ;

    base_specifier_list
        = base_specifier % ','
    ;

    base_specifier
        = !str_p("::") >> !nested_name_specifier >> class_name
        | "virtual" >> !access_specifier >> !str_p("::") >> !nested_name_specifier >> class_name
        | access_specifier >> !str_p("virtual") >> !str_p("::") >> !nested_name_specifier >> class_name
    ;

    access_specifier
        = str_p("private")
        | "protected"
        | "public"
    ;

    //1.10 - Special member functions [gram.special]
    conversion_function_id
        = str_p("operator") >> conversion_type_id
    ;

    conversion_type_id
        = type_specifier_seq >> !conversion_declarator
    ;

    conversion_declarator
        = +ptr_operator
    ;

    ctor_initializer
        = ':' >> mem_initializer_list
    ;

    mem_initializer_list
        = mem_initializer % ','
    ;

    mem_initializer
        = mem_initializer_id >> '(' >> !expression_list >> ')'
    ;

    mem_initializer_id
        = !str_p("::") >> !nested_name_specifier >> class_name
        | identifier
    ;

    //1.11 - Overloading [gram.over]
    operator_function_id
        = str_p("operator") >> operator_
    ;

    operator_
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
    template_declaration
        = !str_p("export") >> str_p("template") >> '<' >> template_parameter_list >> '>' >> declaration
    ;

    template_parameter_list
        = template_parameter % ','
    ;

    template_parameter
        = type_parameter
        | parameter_declaration
    ;

    type_parameter
        = str_p("class") >> !identifier >> '=' >> type_id
        | str_p("class") >> !identifier
        | str_p("typename") >> !identifier >> '=' >> type_id
        | str_p("typename") >> !identifier
        | str_p("template") >> '<' >> template_parameter_list >> '>' >> str_p("class") >> !identifier >> '=' >> id_expression
        | str_p("template") >> '<' >> template_parameter_list >> '>' >> str_p("class") >> !identifier
    ;

    template_id
        = template_name >> '<' >> !template_argument_list >> '>'
    ;

    template_name
        = identifier
    ;

    template_argument_list
        = template_argument % ','
    ;

    template_argument
        = longest_d
        [
            template_argument_assignment_expression //As assignment_expression can contain a '>', we cannot use it directly
            | type_id
            | id_expression
        ]
    ;

    explicit_instantiation
        = !str_p("extern") >> str_p("template") >> declaration
    ;

    explicit_specialization
        = str_p("template") >> '<' >> '>' >> declaration
    ;

    //1.13 - Exception handling [gram.except]
    try_block
        = str_p("try") >> compound_statement >> handler_seq
    ;

    function_try_block
        = str_p("try") >> !ctor_initializer >> function_body >> handler_seq
    ;

    handler_seq
        = +handler
    ;

    handler
        = str_p("catch") >> '(' >> exception_declaration >> ')' >> compound_statement
    ;

    exception_declaration
        = type_specifier_seq >> declarator
        | type_specifier_seq >> abstract_declarator
        | type_specifier_seq
        | "..."
    ;

    throw_expression
        = "throw" >> !assignment_expression
    ;

    exception_specification
        = str_p("throw") >> '(' >> !type_id_list >> ')'
    ;

    type_id_list
        = type_id % ','
    ;

    //1.14 - Preprocessing directives [gram.cpp]
    ///@todo Parsing should be processed just like it was a compilation.
    //This part of the grammar should be used for the preprocessing phase.

    /*
    The rule, as written in the standard, define preprocessing_file as an optional group.
    However, the only rule where preprocessing_file is used put it inside a kleen star.
    Leave preprocessing_file rule as is will lead to an infinite loop.
        preprocessing_file
            = !group
        ;
    */
    preprocessing_file
        = group
    ;

    group
        = +group_part
    ;

    group_part
        = if_section
        | control_line
        | !pp_tokens >> '\n'
    ;

    if_section
        = if_group >> !elif_groups >> !else_group >> endif_line
    ;

    if_group
        = ch_p('#') >> "if" >> constant_expression >> '\n' >> !group
        | ch_p('#') >> "ifdef" >> identifier >> '\n' >> !group
        | ch_p('#') >> "ifndef" >> identifier >> '\n' >> !group
    ;

    elif_groups
        = +elif_group
    ;

    elif_group
        = ch_p('#') >> "elif" >> constant_expression >> '\n' >> !group
    ;

    else_group
        = ch_p('#') >> "else" >> '\n' >> !group
    ;

    endif_line
        = ch_p('#') >> "endif" >> '\n'
    ;

    ///@todo control lines should be ended by an end-of-line character
    control_line
        = ch_p('#') >> "include" >> pp_tokens //>> '\n'
        | ch_p('#') >> "define" >> identifier >> replacement_list //>> '\n'
        | ch_p('#') >> "define" >> lexeme_d[identifier >> '('] >> *identifier >> ')' >> replacement_list //>> '\n' //it cannot be a space between a macro function's name and the left parenthesis
        | ch_p('#') >> "undef" >> identifier //>> '\n'
        | ch_p('#') >> "line" >> pp_tokens //>> '\n'
        | ch_p('#') >> "error" >> !pp_tokens //>> '\n'
        | ch_p('#') >> "pragma" >> !pp_tokens //>> '\n'
        | ch_p('#') //>> '\n'
    ;

    replacement_list
        = !pp_tokens
    ;

    ///@todo there should be a + prefix, but it causes issues
    pp_tokens
        = /*+*/preprocessing_token
    ;

    //GCC extensions
    if(self.is_gcc_extensions_support_enabled())
    {
        gcc_typeof
            = lexeme_d[!str_p("__") >> "typeof" >> !str_p("__")] >> '(' >> expression >> ')' //GCC typeof extension
        ;
    }
}

template<typename ScannerT>
boost::spirit::rule<ScannerT> const&
grammar::definition<ScannerT>::start() const
{
    return file;
}

}} //namespace cppparser::parsing

#endif
