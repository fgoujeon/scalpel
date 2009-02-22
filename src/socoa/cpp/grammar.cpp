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

#include "grammar.h"

#include <boost/spirit/utility/chset.hpp>

namespace socoa { namespace cpp
{

/*-----------------------------------------------*
 *    class internal_type_name_functor_parser    *
 *-----------------------------------------------*/

grammar::internal_type_name_functor_parser::internal_type_name_functor_parser
(
    type_name_parser& a_type_name_parser
):
    type_name_parser_(a_type_name_parser)
{
}

std::ptrdiff_t
grammar::internal_type_name_functor_parser::operator()
(
    const scanner_t& scan,
    internal_type_name_functor_parser::result_t&
) const
{
    return type_name_parser_(scan);
}


/*------------------------------*
 *        class grammar         *
 *------------------------------*/

grammar::grammar(type_name_parser& a_type_name_parser):
    internal_type_name_parser_(a_type_name_parser),
	type_name_p(internal_type_name_parser_)
{
    using namespace boost::spirit;

    file
        = translation_unit
    ;

    source_character_set
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
    keyword
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
            | typeof_keyword
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
            | restrict_keyword
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
    hex_quad
        = hexadecimal_digit >> hexadecimal_digit >> hexadecimal_digit >> hexadecimal_digit
    ;

    universal_character_name
        = lexeme_d[str_p("\\u") >> hex_quad]
        | lexeme_d[str_p("\\U") >> hex_quad >> hex_quad]
    ;

    identifier
        = token_node_d
        [
            (nondigit >> *(nondigit | digit_p)) - keyword
        ]
    ;

    nondigit
        = no_node_d
        [
            universal_character_name
            | chset_p("a-zA-Z")
            | '_'
        ]
    ;

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
        = !declaration_seq >> end_p
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
        | destructor_name
        | template_id
        | identifier
    ;

    qualified_id
        = qualified_nested_id
        | qualified_operator_function_id
        | qualified_template_id
        | qualified_identifier
    ;
    qualified_nested_id
        = !str_p("::") >> nested_name_specifier >> !str_p("template") >> unqualified_id
    ;
    qualified_operator_function_id
        = str_p("::") >> operator_function_id
    ;
    qualified_template_id
        = str_p("::") >> template_id
    ;
    qualified_identifier
        = str_p("::") >> identifier
    ;

	/*
	Original rule:
		nested_name_specifier
			= identifier_or_template_id >> "::" >> !nested_name_specifier
			| identifier_or_template_id >> "::" >> "template" >> nested_name_specifier
		;

		nested_name_specifier
			= identifier_or_template_id >> "::"
			| identifier_or_template_id >> "::" >> nested_name_specifier
			| identifier_or_template_id >> "::" >> "template" >> nested_name_specifier
		;

		nested_name_specifier
			= identifier_or_template_id >> "::" >> nested_name_specifier_second_part
		;
		nested_name_specifier_second_part
			= epsilon_p
			| nested_name_specifier
			| "template" >> nested_name_specifier
		;

		nested_name_specifier
			= identifier_or_template_id >> "::" >> nested_name_specifier_second_part
		;
		nested_name_specifier_second_part
			= epsilon_p
			| !str_p("template") >> nested_name_specifier
		;

		nested_name_specifier
			= identifier_or_template_id >> "::" >> nested_name_specifier_second_part
		;
		nested_name_specifier_second_part
			= epsilon_p
			| !str_p("template") >> identifier_or_template_id >> "::" >> nested_name_specifier_second_part
		;

		nested_name_specifier
			= identifier_or_template_id >> "::" >> nested_name_specifier_second_part
		;
		nested_name_specifier_second_part
			= *(!str_p("template") >> identifier_or_template_id >> "::")
		;
	*/
	nested_name_specifier
		= identifier_or_template_id >> "::" >> *nested_name_specifier_second_part
	;
	nested_name_specifier_second_part
		= !str_p("template") >> identifier_or_template_id >> "::"
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
        = nested_identifier_or_template_id >> str_p("::") >> '~' >> identifier_or_template_id
        | !str_p("::") >> nested_name_specifier >> str_p("template") >> template_id >> str_p("::") >> '~' >> identifier_or_template_id
        | !str_p("::") >> !nested_name_specifier >> '~' >> identifier_or_template_id
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

    pm_ptr_expression
        = cast_expression % "->*"
    ;

    pm_ref_expression
        = pm_ptr_expression % ".*"
    ;

    modulo_expression
        = pm_ref_expression % '%'
    ;

    divisive_expression
        = modulo_expression % '/'
    ;

    multiplicative_expression
        = divisive_expression % '*'
    ;

    subtractive_expression
        = multiplicative_expression % '-'
    ;

    additive_expression
        = subtractive_expression % '+'
    ;

    left_shift_expression
        = additive_expression % "<<"
    ;

    right_shift_expression
        = left_shift_expression % ">>"
    ;
    //a shift expression used as a template argument must be placed between brackets if it contains any '>' characters
    template_argument_right_shift_expression
        = '(' >> (left_shift_expression % ">>") >> ')'
        | left_shift_expression
    ;

    less_than_or_equal_to_expression
        = right_shift_expression % "<="
    ;
    template_less_than_or_equal_to_expression
        = template_argument_right_shift_expression
    ;

    less_than_expression
        = less_than_or_equal_to_expression % '<'
    ;
    template_less_than_expression
        = template_less_than_or_equal_to_expression
    ;

    greater_than_or_equal_to_expression
        = less_than_expression % ">="
    ;
    //a shift expression used as a template argument must be placed between brackets if it contains any '>' characters
    template_greater_than_or_equal_to_expression
        = '(' >> (less_than_expression % ">=") >> ')'
        | template_less_than_expression
    ;

    greater_than_expression
        = greater_than_or_equal_to_expression % '>'
    ;
    //a shift expression used as a template argument must be placed between brackets if it contains any '>' characters
    template_greater_than_expression
        = '(' >> (greater_than_or_equal_to_expression % '>') >> ')'
        | template_greater_than_or_equal_to_expression
    ;

    inequality_expression
        = greater_than_expression % "!="
    ;
    template_argument_inequality_expression
        = template_greater_than_expression % "!="
    ;

    equality_expression
        = inequality_expression % "=="
    ;
    template_argument_equality_expression
        = template_argument_inequality_expression % "=="
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

    if(configuration_.skip_function_bodies)
    {
        statement_seq
            = +skip_function_bodies_mode_statement_seq_item
        ;
        skip_function_bodies_mode_statement_seq_item
            = token_node_d
            [
                character_literal
                | string_literal
                | compound_statement
                | skip_function_bodies_mode_non_special_char_seq
            ]
        ;
    }
    else
    {
        statement_seq
            = +statement
        ;
    }

    selection_statement
        = str_p("if") >> '(' >> condition >> ')' >> statement >> !("else" >> statement)
        | str_p("switch") >> '(' >> condition >> ')' >> statement
    ;

    /*
    Original rule is:
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
    If we wrote it that way, with such an input:
        int i, j;
    The scanner will parse "i" as a decl_specifier (it is indeed a correct identifier_or_template_id).
    Consequently, when it will try to parse the comma, it will raise an error.

    In order to solve this issue, we have to create an extra rule which specifies a tail parser.
    */
    ///@todo semantic disambiguation between decl_specifier and init_declarator_list
    simple_declaration
        = !simple_declaration_decl_specifier_seq >> !init_declarator_list >> ch_p(';')
    ;
    simple_declaration_decl_specifier_seq
        = +(decl_specifier - (init_declarator_list >> ch_p(';')))
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

    type_specifier
        = simple_type_specifier
        | class_specifier
        | enum_specifier
        | elaborated_type_specifier
        | cv_qualifier
        | typeof_expression
    ;

    simple_type_specifier
        = nested_identifier_or_template_id
        | simple_template_type_specifier
        | built_in_type_specifier
    ;
    simple_template_type_specifier
        = !str_p("::") >> nested_name_specifier >> "template" >> template_id
    ;
    built_in_type_specifier
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

    elaborated_type_specifier
        = class_key >> !str_p("::") >> !nested_name_specifier >> template_id //not in the standard, but seems to be required for parsing standard library
        | class_key >> !str_p("::") >> !nested_name_specifier >> identifier
        | str_p("enum") >> !str_p("::") >> !nested_name_specifier >> identifier
        | str_p("typename") >> !str_p("::") >> nested_name_specifier >> !str_p("template") >> template_id
        | str_p("typename") >> !str_p("::") >> nested_name_specifier >> identifier
    ;

    enum_specifier
        = str_p("enum") >> !identifier >> ch_p('{') >> !enumerator_list >> ch_p('}')
    ;

    enumerator_list
        = enumerator_definition % ','
    ;

    enumerator_definition
        = identifier >> !('=' >> constant_expression)
    ;

    namespace_definition
        = str_p("namespace") >> !identifier >> '{' >> !declaration_seq >> '}'
    ;

    namespace_alias_definition
        = str_p("namespace") >> identifier >> '=' >> qualified_namespace_specifier >> ch_p(';')
    ;

    qualified_namespace_specifier
        = !str_p("::") >> !nested_name_specifier >> identifier
    ;

    using_declaration
        = "using" >> !str_p("typename") >> !str_p("::") >> nested_name_specifier >> unqualified_id >> ch_p(';')
        | "using" >> str_p("::") >> unqualified_id >> ch_p(';')
    ;

    using_directive
        = str_p("using") >> "namespace" >> !str_p("::") >> !nested_name_specifier >> identifier >> ch_p(';')
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

    /*
    Original rule is:
        declarator
            = ptr_operator >> declarator
            | direct_declarator
        ;
    */
    declarator
        = *ptr_operator >> direct_declarator
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
    direct_declarator
        =
        (
            declarator_id
            | '(' >> declarator >> ')'
        )
        >>
        *(
            direct_declarator_function_part
            | direct_declarator_array_part
        )
    ;
    direct_declarator_function_part
        = '(' >> parameter_declaration_clause >> ')' >> !cv_qualifier_seq >> !exception_specification
    ;
    direct_declarator_array_part
        = '[' >> !constant_expression >> ']'
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
        | restrict_keyword
    ;

    declarator_id
        = id_expression
        | nested_identifier_or_template_id
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
        = +(decl_specifier - (declarator >> (ch_p(',') | ')' | "...")))
    ;
    parameter_declaration_decl_specifier_seq3
        = +(decl_specifier - (abstract_declarator >> '=' >> assignment_expression))
    ;
    parameter_declaration_decl_specifier_seq4
        = +(decl_specifier - (abstract_declarator >> (ch_p(',') | ')' | "...")))
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
    class_specifier
        = class_head >> '{' >> !member_specification >> '}'
    ;

    class_head
        = class_key >> !nested_name_specifier >> template_id >> !base_clause //class template specialization -> the class already had been declared
        | class_key >> nested_name_specifier >> identifier >> !base_clause //ditto
        | class_key >> !identifier >> !base_clause
    ;

    class_key
        = token_node_d
        [
            str_p("class")
            | "struct"
            | "union"
        ]
    ;

    member_specification
        = *(member_declaration | member_specification_access_specifier)
    ;
    member_specification_access_specifier
        = access_specifier >> ':'
    ;

    member_declaration
        = member_declaration_member_declarator_list
        | member_declaration_unqualified_id
        | member_declaration_function_definition
        | using_declaration
        | template_declaration
    ;
    member_declaration_member_declarator_list
        = !member_declaration_decl_specifier_seq >> !member_declarator_list >> ch_p(';')
    ;
    member_declaration_unqualified_id
        = !str_p("::") >> nested_name_specifier >> !str_p("template") >> unqualified_id >> ch_p(';')
    ;
    member_declaration_function_definition
        = function_definition >> !ch_p(';')
    ;
    member_declaration_decl_specifier_seq
        = +(decl_specifier - (member_declarator_list >> ch_p(';')))
    ;

    member_declarator_list
        = member_declarator % ','
    ;

    member_declarator
        = member_declarator_declarator
        | member_declarator_bit_field_member
    ;
    member_declarator_declarator
        = declarator >> !(pure_specifier | constant_initializer) ///@todo find what declarator >> constant_initializer stands for
    ;
    member_declarator_bit_field_member
        = !identifier >> ':' >> constant_expression //bit field member
    ;

    pure_specifier
        = ch_p('=') >> '0'
    ;

    constant_initializer
        = '=' >> constant_expression
    ;

    //convenience rule, not explicitly in the standard
    destructor_name
        = '~' >> identifier_or_template_id
    ;


    //1.9 - Derived classes [gram.class.derived]
    base_clause
        = ':' >> base_specifier_list
    ;

    base_specifier_list
        = base_specifier % ','
    ;

    base_specifier
        = nested_identifier_or_template_id
        | "virtual" >> !access_specifier >> nested_identifier_or_template_id
        | access_specifier >> !str_p("virtual") >> nested_identifier_or_template_id
    ;

    access_specifier
        = token_node_d
        [
            str_p("private")
            | "protected"
            | "public"
        ]
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
        = nested_identifier_or_template_id
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
        = type_name >> '<' >> !template_argument_list >> '>'
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


    /*
    Convenience rules
    */
    // !space_p   -> we don't want to have to parse any space char in type_name_p
    // identifier -> we have to read last_parsed_identifier_ in type_name_p
    type_name
        = token_node_d[!space_p >> (identifier & type_name_p)]
    ;

    identifier_or_template_id
        = template_id
        | identifier
    ;

    nested_identifier_or_template_id
        = !str_p("::") >> !nested_name_specifier >> identifier_or_template_id
    ;

    //Convenience rules for declaration-only mode
    skip_function_bodies_mode_non_special_char_seq
        = +skip_function_bodies_mode_non_special_char
    ;
    skip_function_bodies_mode_non_special_char
        = anychar_p - (ch_p('"') | '\'' | '{' | '}')
    ;


    /*
    Extensions
    These rules are not in the standard, but are required to parse some standard library implementations
    */
    if(configuration_.enable_typeof_support)
    {
        typeof_expression
            = typeof_keyword >> '(' >> expression >> ')'
        ;

        typeof_keyword
            = str_p("__typeof__")
            | "__typeof"
            | "typeof"
        ;
    }

    if(configuration_.enable_restrict_support)
    {
        restrict_keyword
            = str_p("__restrict__")
            | "__restrict"
            | "restrict"
        ;
    }
}

const grammar::configuration&
grammar::get_configuration() const
{
    return configuration_;
}

void
grammar::set_configuration(const configuration& a_configuration)
{
    configuration_ = a_configuration;
}

const boost::spirit::rule<scanner_t>&
grammar::get_start_rule() const
{
    return file;
}

}} //namespace socoa::cpp
