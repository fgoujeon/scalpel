/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008, 2009  Florian Goujeon

This file is part of Scalpel.

Scalpel is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Scalpel is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Scalpel.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "grammar.hpp"

#include <boost/spirit/utility/chset.hpp>

namespace scalpel { namespace cpp { namespace detail { namespace syntax_analysis
{

/*-----------------------------------------------*
 *	class internal_type_name_functor_parser	*
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
 *		class grammar		 *
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

	//white separator
	s = token_node_d[*(ch_p(' ') | '\t' | '\v' | '\f' | '\n')];


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
		= str_p("\\u") >> hex_quad
		| str_p("\\U") >> hex_quad >> hex_quad
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
		= token_node_d
		[
			decimal_literal >> !integer_suffix
			| hexadecimal_literal >> !integer_suffix
			| octal_literal >> !integer_suffix
		]
	;

	decimal_literal
		= nonzero_digit >> *digit_p
	;

	octal_literal
		= '0' >> *octal_digit
	;

	hexadecimal_literal
		= (str_p("0x") | "0X") >> +hexadecimal_digit
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
		= !ch_p('L') >> '\'' >> token_node_d[c_char_sequence] >> '\''
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
		= '\\' >> octal_digit >> !octal_digit >> !octal_digit
	;

	hexadecimal_escape_sequence
		= "\\x" >> +hexadecimal_digit
	;

	floating_literal
		= token_node_d
		[
			fractional_constant >> !exponent_part >> !floating_suffix
			| digit_sequence >> exponent_part >> !floating_suffix
		]
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
		= !ch_p('L') >> '"' >> !token_node_d[s_char_sequence] >> '"'
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
		= token_node_d
		[
			str_p("false")
			| "true"
		]
	;

	//1.3 - Basic concepts [gram.basic]
	translation_unit
		= !s >> !(declaration_seq >> !s) >> end_p
	;

	//1.4 - Expressions [gram.expr]
	primary_expression
		= str_p("this")
		| literal
		| round_bracketed_expression
		| id_expression
	;

	round_bracketed_expression
		= '(' >> !s >> expression >> !s >> ')'
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
		= !(str_p("::") >> !s) >> nested_name_specifier >> !s >> !("template" >> !s) >> unqualified_id
	;
	qualified_operator_function_id
		= str_p("::") >> !s >> operator_function_id
	;
	qualified_template_id
		= str_p("::") >> !s >> template_id
	;
	qualified_identifier
		= str_p("::") >> !s >> identifier
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
		= identifier_or_template_id >> !s >> "::" >> !(!s >> nested_name_specifier_last_part_seq)
	;
	nested_name_specifier_last_part_seq
		= nested_name_specifier_last_part % !s
	;
	nested_name_specifier_last_part
		= !(str_p("template") >> !s) >> identifier_or_template_id >> !s >> "::"
	;

	/*
	The following rule is written like this in the standard:
		postfix_expression
			= primary_expression
			| postfix_expression >> '[' >> expression >> ']'
			| postfix_expression >> '(' >> !expression >> ')'
			| simple_type_specifier >> '(' >> !expression >> ')'
			| str_p("typename") >> !str_p("::") >> nested_name_specifier >> identifier >> '(' >> !expression >> ')'
			| str_p("typename") >> !str_p("::") >> nested_name_specifier >> !str_p("template") >> template_id >> '(' >> !expression >> ')'
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
		= postfix_expression_first_part >> !(!s >> postfix_expression_last_part_seq)
	;
	postfix_expression_first_part
		= primary_expression
		| simple_type_specifier_postfix_expression
		| typename_expression
		| template_typename_expression
		| dynamic_cast_expression
		| static_cast_expression
		| reinterpret_cast_expression
		| const_cast_expression
		| typeid_expression
		| type_id_typeid_expression
	;
	postfix_expression_last_part_seq
		= postfix_expression_last_part % !s
	;
	postfix_expression_last_part
		= square_bracketed_expression
		| round_bracketed_optional_expression
		| dot_id_expression
		| arrow_id_expression
		| dot_pseudo_destructor_name
		| arrow_pseudo_destructor_name
		| "++"
		| "--"
	;

	simple_type_specifier_postfix_expression
		= simple_type_specifier >> !s >> '(' >> !s >> !(expression >> !s) >> ')'
	;

	typename_expression
		= str_p("typename") >> !s >> !(str_p("::") >> !s) >> nested_name_specifier >> !s >> identifier >> !s >> '(' >> !s >> !(expression >> !s) >> ')'
	;

	template_typename_expression
		= str_p("typename") >> !s >> !(str_p("::") >> !s) >> nested_name_specifier >> !s >> !(str_p("template") >> !s) >> template_id >> !s >> '(' >> !s >> !(expression >> !s) >> ')'
	;

	dynamic_cast_expression
		= str_p("dynamic_cast") >> !s >> '<' >> !s >> type_id >> !s >> '>' >> !s >> '(' >> !s >> expression >> !s >> ')'
	;

	static_cast_expression
		= str_p("static_cast") >> !s >> '<' >> !s >> type_id >> !s >> '>' >> !s >> '(' >> !s >> expression >> !s >> ')'
	;

	reinterpret_cast_expression
		= str_p("reinterpret_cast") >> !s >> '<' >> !s >> type_id >> !s >> '>' >> !s >> '(' >> !s >> expression >> !s >> ')'
	;

	const_cast_expression
		= str_p("const_cast") >> !s >> '<' >> !s >> type_id >> !s >> '>' >> !s >> '(' >> !s >> expression >> !s >> ')'
	;

	typeid_expression
		= str_p("typeid") >> !s >> '(' >> !s >> expression >> !s >> ')'
	;

	type_id_typeid_expression
		= str_p("typeid") >> !s >> '(' >> !s >> type_id >> !s >> ')'
	;

	square_bracketed_expression
		= '[' >> !s >> expression >> !s >> ']'
	;

	round_bracketed_optional_expression
		= '(' >> !s >> !(expression >> !s) >> ')'
	;

	dot_id_expression
		= '.' >> !s >> !(str_p("template") >> !s) >> id_expression
	;

	arrow_id_expression
		= "->" >> !s >> !(str_p("template") >> !s) >> id_expression
	;

	dot_pseudo_destructor_name
		= '.' >> !s >> pseudo_destructor_name
	;

	arrow_pseudo_destructor_name
		= "->" >> !s >> pseudo_destructor_name
	;

	pseudo_destructor_name
		= nested_identifier_or_template_id >> !s >> str_p("::") >> !s >> '~' >> !s >> identifier_or_template_id
		| !(str_p("::") >> !s) >> nested_name_specifier >> !s >> str_p("template") >> !s >> template_id >> !s >> str_p("::") >> !s >> '~' >> !s >> identifier_or_template_id
		| !(str_p("::") >> !s) >> !(nested_name_specifier >> !s) >> '~' >> !s >> identifier_or_template_id
	;

	unary_expression
		= unary_operator_unary_expression
		| type_id_sizeof_expression
		| unary_sizeof_expression
		| postfix_expression
		| new_expression
		| delete_expression
	;

	unary_operator_unary_expression
		= unary_operator >> !s >> cast_expression
	;

	type_id_sizeof_expression
		= str_p("sizeof") >> !s >> '(' >> !s >> type_id >> !s >> ')'
	;

	unary_sizeof_expression
		= str_p("sizeof") >> !s >> unary_expression
	;

	unary_operator
		= str_p("++")
		| "--"
		| '*'
		| '&'
		| '+'
		| '-'
		| '!'
		| '~'
	;

	new_expression
		= type_id_new_expression
		| new_type_id_new_expression
	;

	type_id_new_expression
		= !(str_p("::") >> !s) >> str_p("new") >> !s >> !(new_placement >> !s) >> '(' >> !s >> type_id >> !s >> ')' >> !(!s >> new_initializer)
	;

	new_type_id_new_expression
		= !(str_p("::") >> !s) >> str_p("new") >> !s >> !(new_placement >> !s) >> new_type_id >> !(!s >> new_initializer)
	;

	new_placement
		= '(' >> !s >> expression >> !s >> ')'
	;

	new_type_id
		= type_specifier_seq >> !(!s >> new_declarator)
	;

	new_declarator
		= ptr_operator_seq >> !s >> direct_new_declarator
		| ptr_operator_seq
		| direct_new_declarator
	;

	direct_new_declarator
		= '[' >> !s >> expression >> !s >> ']' >> !(!s >> '[' >> !s >> conditional_expression >> !s >> ']')
	;

	new_initializer
		= '(' >> !s >> !(expression >> !s) >> ')'
	;

	delete_expression
		= simple_delete_expression
		| array_delete_expression
	;

	simple_delete_expression
		= !(str_p("::") >> !s) >> "delete" >> !s >> cast_expression
	;

	array_delete_expression
		= !(str_p("::") >> !s) >> "delete" >> !s >> '[' >> !s >> ']' >> !s >> cast_expression
	;

	cast_expression
		= longest_d
		[
			unary_expression //this alternative must be tried first
			| cast_expression_first_part_seq >> !s >> unary_expression
		]
	;
	cast_expression_first_part_seq
		= cast_expression_first_part % !s
	;
	cast_expression_first_part
		= '(' >> !s >> type_id >> !s >> ')'
	;

	pm_ptr_expression
		= cast_expression % (!s >> "->*" >> !s)
	;

	pm_ref_expression
		= pm_ptr_expression % (!s >> ".*" >> !s)
	;

	modulo_expression
		= pm_ref_expression % (!s >> '%' >> !s)
	;

	divisive_expression
		= modulo_expression % (!s >> '/' >> !s)
	;

	multiplicative_expression
		= divisive_expression % (!s >> '*' >> !s)
	;

	subtractive_expression
		= multiplicative_expression % (!s >> '-' >> !s)
	;

	additive_expression
		= subtractive_expression % (!s >> '+' >> !s)
	;

	left_shift_expression
		= additive_expression % (!s >> "<<" >> !s)
	;

	right_shift_expression
		= left_shift_expression % (!s >> ">>" >> !s)
	;
	//a shift expression used as a template argument must be placed between brackets if it contains any '>' characters
	template_argument_right_shift_expression
		= round_bracketed_right_shift_expression
		| left_shift_expression
	;
	round_bracketed_right_shift_expression
		= '(' >> !s >> right_shift_expression >> !s >> ')'
	;

	less_than_or_equal_to_expression
		= right_shift_expression % (!s >> "<=" >> !s)
	;
	template_argument_less_than_or_equal_to_expression
		= template_argument_right_shift_expression % (!s >> "<=" >> !s)
	;

	less_than_expression
		= less_than_or_equal_to_expression % (!s >> '<' >> !s)
	;
	template_argument_less_than_expression
		= template_argument_less_than_or_equal_to_expression % (!s >> '<' >> !s)
	;

	greater_than_or_equal_to_expression
		= less_than_expression % (!s >> ">=" >> !s)
	;
	template_argument_greater_than_or_equal_to_expression
		= template_argument_less_than_expression % (!s >> ">=" >> !s)
	;

	greater_than_expression
		= greater_than_or_equal_to_expression % (!s >> '>' >> !s)
	;
	//a shift expression used as a template argument must be placed between brackets if it contains any '>' characters
	template_argument_greater_than_expression
		= round_bracketed_greater_than_expression
		| template_argument_greater_than_or_equal_to_expression
	;
	round_bracketed_greater_than_expression
		= '(' >> !s >> greater_than_expression >> !s >> ')'
	;

	inequality_expression
		= greater_than_expression % (!s >> "!=" >> !s)
	;
	template_argument_inequality_expression
		= template_argument_greater_than_expression % (!s >> "!=" >> !s)
	;

	equality_expression
		= inequality_expression % (!s >> "==" >> !s)
	;
	template_argument_equality_expression
		= template_argument_inequality_expression % (!s >> "==" >> !s)
	;

	and_expression
		= equality_expression % (!s >> '&' >> !s)
	;
	template_argument_and_expression
		= template_argument_equality_expression % (!s >> '&' >> !s)
	;

	exclusive_or_expression
		= and_expression % (!s >> '^' >> !s)
	;
	template_argument_exclusive_or_expression
		= template_argument_and_expression % (!s >> '^' >> !s)
	;

	inclusive_or_expression
		= exclusive_or_expression % (!s >> '|' >> !s)
	;
	template_argument_inclusive_or_expression
		= template_argument_exclusive_or_expression % (!s >> '|' >> !s)
	;

	logical_and_expression
		= inclusive_or_expression % (!s >> "&&" >> !s)
	;
	template_argument_logical_and_expression
		= template_argument_inclusive_or_expression % (!s >> "&&" >> !s)
	;

	logical_or_expression
		= logical_and_expression % (!s >> "||" >> !s)
	;
	template_argument_logical_or_expression
		= template_argument_logical_and_expression % (!s >> "||" >> !s)
	;

	conditional_expression
		= logical_or_expression >> !(!s >> '?' >> !s >> expression >> !s >> ':' >> !s >> assignment_expression)
	;
	template_argument_conditional_expression
		= template_argument_logical_or_expression >> !(!s >> '?' >> !s >> expression >> !s >> ':' >> !s >> template_argument_assignment_expression)
	;

	/*
	Original rule is:
		assignment_expression
			= logical_or_expression >> !s >> assignment_operator >> !s >> assignment_expression
			| conditional_expression
			| throw_expression
		;
	*/
	assignment_expression
		= !(assignment_expression_first_part_seq >> !s) >> assignment_expression_last_part
	;
	assignment_expression_first_part_seq
		= assignment_expression_first_part % !s
	;
	assignment_expression_first_part
		= logical_or_expression >> !s >> assignment_operator
	;
	assignment_expression_last_part
		= conditional_expression
		| throw_expression
	;

	template_argument_assignment_expression
		= !(template_argument_assignment_expression_first_part_seq >> !s) >> template_argument_assignment_expression_last_part
	;
	template_argument_assignment_expression_first_part_seq
		= template_argument_assignment_expression_first_part % !s
	;
	template_argument_assignment_expression_first_part
		= template_argument_logical_or_expression >> !s >> assignment_operator
	;
	template_argument_assignment_expression_last_part
		= template_argument_conditional_expression
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
		= assignment_expression % (!s >> ',' >> !s)
	;

	//1.5 - Statements [gram.stmt.stmt]
	statement
		= labeled_statement
		| expression_statement
		| compound_statement
		| selection_statement
		| iteration_statement
		| jump_statement
		| block_declaration
		| try_block
	;

	labeled_statement
		= case_statement
		| default_statement
		| classic_labeled_statement
	;

	case_statement
		= str_p("case") >> !s >> conditional_expression >> !s >> ':' >> !s >> statement
	;

	default_statement
		= str_p("default") >> !s >> ':' >> !s >> statement
	;

	classic_labeled_statement
		= identifier >> !s >> ':' >> !s >> statement
	;

	expression_statement
		= !(expression >> !s) >> ch_p(';')
	;

	compound_statement
		= ch_p('{') >> !s >> !(statement_seq >> !s) >> ch_p('}')
	;

	statement_seq
		= statement % !s
	;

	selection_statement
		= if_statement
		| switch_statement
	;

	if_statement
		= str_p("if") >> !s >> '(' >> !s >> condition >> !s >> ')' >> !s >> statement >> !(!s >> "else" >> !s >> statement)
	;

	switch_statement
		= str_p("switch") >> !s >> '(' >> !s >> condition >> !s >> ')' >> !s >> statement
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
		| assignment_expression_condition
	;

	assignment_expression_condition
		= assignment_expression_condition_type_specifier_seq >> !s >> declarator >> !s >> '=' >> !s >> assignment_expression
	;
	assignment_expression_condition_type_specifier_seq
		= (type_specifier - (declarator >> !s >> '=' >> !s >> assignment_expression)) % !s
	;

	iteration_statement
		= while_statement
		| do_while_statement
		| for_statement
	;

	while_statement
		= str_p("while") >> !s >> '(' >> !s >> condition >> !s >> ')' >> !s >> statement
	;

	do_while_statement
		= str_p("do") >> !s >> statement >> !s >> "while" >> !s >> '(' >> !s >> expression >> !s >> ')' >> !s >> ch_p(';')
	;

	for_statement
		= str_p("for") >> !s >> '(' >> !s >> for_init_statement >> !s >> !(condition >> !s) >> ch_p(';') >> !s >> !(expression >> !s) >> ')' >> !s >> statement
	;

	for_init_statement
		= expression_statement
		| simple_declaration
	;

	jump_statement
		= break_statement
		| continue_statement
		| return_statement
		| goto_statement
	;

	break_statement
		= str_p("break") >> !s >> ch_p(';')
	;

	continue_statement
		= str_p("continue") >> !s >> ch_p(';')
	;

	return_statement
		= str_p("return") >> !s >> !(expression >> !s) >> ch_p(';')
	;

	goto_statement
		= str_p("goto") >> !s >> identifier >> !s >> ch_p(';')
	;


	//1.6 - Declarations [gram.dcl.dcl]
	declaration_seq
		= declaration % !s
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
	simple_declaration
		= !(simple_declaration_decl_specifier_seq >> !s) >> !(init_declarator_list >> !s) >> ch_p(';')
	;
	simple_declaration_decl_specifier_seq
		= (decl_specifier - (init_declarator_list >> !s >> ch_p(';'))) % !s
	;

	decl_specifier
		= storage_class_specifier
		| type_specifier
		| function_specifier
		| str_p("friend")
		| str_p("typedef")
	;

	decl_specifier_seq
		= decl_specifier % !s
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
		= !(str_p("::") >> !s) >> nested_name_specifier >> !s >> "template" >> !s >> template_id
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
		= class_template_elaborated_specifier //not in the standard, but seems to be required for parsing GCC's standard library
		| class_elaborated_specifier
		| enum_elaborated_specifier
		| typename_template_elaborated_specifier
		| typename_elaborated_specifier
	;

	class_template_elaborated_specifier
		= class_key >> !s >> !(str_p("::") >> !s) >> !(nested_name_specifier >> !s) >> template_id
	;

	class_elaborated_specifier
		= class_key >> !s >> !(str_p("::") >> !s) >> !(nested_name_specifier >> !s) >> identifier
	;

	enum_elaborated_specifier
		= str_p("enum") >> !s >> !(str_p("::") >> !s) >> !(nested_name_specifier >> !s) >> identifier
	;

	typename_template_elaborated_specifier
		= str_p("typename") >> !s >> !(str_p("::") >> !s) >> nested_name_specifier >> !s >> !(str_p("template") >> !s) >> template_id
	;

	typename_elaborated_specifier
		= str_p("typename") >> !s >> !(str_p("::") >> !s) >> nested_name_specifier >> !s >> identifier
	;

	enum_specifier
		= str_p("enum") >> !s >> !(identifier >> !s) >> ch_p('{') >> !s >> !(enumerator_list >> !s) >> ch_p('}')
	;

	enumerator_list
		= enumerator_definition % (!s >> ',' >> !s)
	;

	enumerator_definition
		= identifier >> !s >> !('=' >> !s >> conditional_expression)
	;

	namespace_definition
		= str_p("namespace") >> !s >> !(identifier >> !s) >> !(attribute_expression >> !s) >> '{' >> !s >> !(declaration_seq >> !s) >> '}'
	;

	namespace_alias_definition
		= str_p("namespace") >> !s >> identifier >> !s >> '=' >> !s >> qualified_namespace_specifier >> !s >> ch_p(';')
	;

	qualified_namespace_specifier
		= !(str_p("::") >> !s) >> !(nested_name_specifier >> !s) >> identifier
	;

	using_declaration
		= "using" >> !s >> !(str_p("typename") >> !s) >> !(str_p("::") >> !s) >> nested_name_specifier >> !s >> unqualified_id >> !s >> ch_p(';')
		| "using" >> !s >> str_p("::") >> !s >> unqualified_id >> !s >> ch_p(';')
	;

	using_directive
		= str_p("using") >> !s >> "namespace" >> !s >> !(str_p("::") >> !s) >> !(nested_name_specifier >> !s) >> identifier >> !s >> ch_p(';')
	;

	asm_definition
		= str_p("asm") >> !s >> '(' >> !s >> string_literal >> !s >> ')' >> !s >> ch_p(';')
	;

	linkage_specification
		= "extern" >> !s >> string_literal >> !s >> ch_p('{') >> !s >> !(declaration_seq >> !s) >> ch_p('}')
		| "extern" >> !s >> string_literal >> !s >> declaration
	;

	//1.7 - Declarators [gram.dcl.decl]
	init_declarator_list
		= init_declarator % (!s >> ',' >> !s)
	;

	init_declarator
		= declarator >> !(!s >> initializer)
	;

	/*
	Original rule is:
		declarator
			= ptr_operator >> declarator
			| direct_declarator
		;
	*/
	declarator
		= !(ptr_operator_seq >> !s) >> direct_declarator
	;

	/*
	Original rule is:
		direct_declarator
			= declarator_id
			| direct_declarator >> '(' >> parameter_declaration_clause >> ')' >> !cv_qualifier_seq >> !exception_specification
			| direct_declarator >> '[' >> !conditional_expression >> ']'
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
			| '[' >> !conditional_expression >> ']'
		;

		***

		direct_declarator
			= (declarator_id | '(' >> declarator >> ')') >> direct_declarator_rest
		;
		direct_declarator_rest
			= '(' >> parameter_declaration_clause >> ')' >> !cv_qualifier_seq >> !exception_specification >> direct_declarator_rest
			| '[' >> !conditional_expression >> ']' >> direct_declarator_rest
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
					| '[' >> !conditional_expression >> ']'
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
						| '[' >> !conditional_expression >> ']'
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
					| '[' >> !conditional_expression >> ']'
				)
		;
	*/
	direct_declarator
		= direct_declarator_first_part >> !(!s >> direct_declarator_last_part_seq)
	;
	direct_declarator_first_part
		= bracketed_declarator
		| declarator_id
	;
	bracketed_declarator
		= '(' >> !s >> declarator >> !s >> ')'
	;
	direct_declarator_last_part_seq
		= direct_declarator_last_part % !s
	;
	direct_declarator_last_part
		= direct_declarator_function_part
		| direct_declarator_array_part
	;
	direct_declarator_function_part
		= '(' >> !s >> !(parameter_declaration_clause >> !s) >> ')' >> !(!s >> cv_qualifier_seq) >> !(!s >> exception_specification) >> !(!s >> attribute_expression)
	;
	direct_declarator_array_part
		= '[' >> !s >> !(conditional_expression >> !s) >> ']'
	;

	ptr_operator_seq
		= ptr_operator % !s
	;

	ptr_operator
		= ch_p('*') >> !(!s >> cv_qualifier_seq)
		| ch_p('&')
		| !(str_p("::") >> !s) >> nested_name_specifier >> !s >> '*' >> !(!s >> cv_qualifier_seq)
	;

	cv_qualifier_seq
		= cv_qualifier % !s
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
		= type_specifier_seq >> !(!s >> abstract_declarator)
	;

	type_specifier_seq
		= type_specifier % !s
	;

	abstract_declarator
		= ptr_operator_seq
		| direct_abstract_declarator
	;

	/*
	Original rule is:
		direct_abstract_declarator
			= !direct_abstract_declarator >> '(' >> parameter_declaration_clause >> ')' >> !cv_qualifier_seq >> !exception_specification
			| !direct_abstract_declarator >> '[' >> !conditional_expression >> ']'
			| '(' >> abstract_declarator >> ')'
		;

		***

		direct_abstract_declarator
			= !direct_abstract_declarator >> direct_abstract_declarator_rest
			| '(' >> abstract_declarator >> ')'
		;
		direct_abstract_declarator_rest
			= '(' >> parameter_declaration_clause >> ')' >> !cv_qualifier_seq >> !exception_specification
			| '[' >> !conditional_expression >> ']'
		;

		***

		direct_abstract_declarator
			= '(' >> abstract_declarator >> ')' >> !direct_abstract_declarator_rest
			| +direct_abstract_declarator_rest
		;
		direct_abstract_declarator_rest
			= '(' >> parameter_declaration_clause >> ')' >> !cv_qualifier_seq >> !exception_specification
			| '[' >> !conditional_expression >> ']'
		;

		We have direct_abstract_declarator_rest == direct_declarator_last_part
	*/
	direct_abstract_declarator
		= bracketed_abstract_declarator
		| direct_declarator_last_part_seq
	;
	bracketed_abstract_declarator
		= '(' >> !s >> abstract_declarator >> !s >> ')' >> !(!s >> direct_declarator_last_part)
	;

	parameter_declaration_clause
		= parameter_declaration_list >> !s >> ',' >> !s >> "..."
		| parameter_declaration_list >> !s >> str_p("...")
		| parameter_declaration_list
		| str_p("...")
	;

	parameter_declaration_list
		= parameter_declaration % (!s >> ',' >> !s)
	;

	parameter_declaration
		= decl_specifier_seq >> !s >> '=' >> !s >> assignment_expression
		| parameter_declaration_decl_specifier_seq1 >> !s >> declarator >> !s >> '=' >> !s >> assignment_expression
		| parameter_declaration_decl_specifier_seq2 >> !s >> declarator
		| parameter_declaration_decl_specifier_seq3 >> !s >> abstract_declarator >> !s >> '=' >> !s >> assignment_expression
		| parameter_declaration_decl_specifier_seq4 >> !(!s >> abstract_declarator)
	;
	parameter_declaration_decl_specifier_seq1
		= (decl_specifier - (declarator >> !s >> '=' >> !s >> assignment_expression)) % !s
	;
	parameter_declaration_decl_specifier_seq2
		= (decl_specifier - (declarator >> !s >> (ch_p(',') | ')' | "..."))) % !s
	;
	parameter_declaration_decl_specifier_seq3
		= (decl_specifier - (abstract_declarator >> !s >> '=' >> !s >> assignment_expression)) % !s
	;
	parameter_declaration_decl_specifier_seq4
		= (decl_specifier - (abstract_declarator >> !s >> (ch_p(',') | ')' | "..."))) % !s
	;


	/*
	Original rule is:
		function_definition
			= !decl_specifier_seq >> declarator >> !ctor_initializer >> compound_statement
			| !decl_specifier_seq >> declarator >> function_try_block
		;
	*/
	function_definition
		= !(function_definition_decl_specifier_seq1 >> !s) >> declarator >> !s >> ctor_initializer >> !s >> compound_statement
		| !(function_definition_decl_specifier_seq2 >> !s) >> declarator >> !s >> compound_statement
		| !(function_definition_decl_specifier_seq3 >> !s) >> declarator >> !s >> function_try_block
	;
	function_definition_decl_specifier_seq1
		= (decl_specifier - (declarator >> !s >> ctor_initializer >> !s >> compound_statement)) % !s
	;
	function_definition_decl_specifier_seq2
		= (decl_specifier - (declarator >> !s >> compound_statement)) % !s
	;
	function_definition_decl_specifier_seq3
		= (decl_specifier - (declarator >> !s >> function_try_block)) % !s
	;

	initializer
		= equal_initializer
		| round_bracketed_expression
	;

	equal_initializer
		= ch_p('=') >> !s >> initializer_clause
	;

	initializer_clause
		= assignment_expression
		| initializer_list_initializer_clause
		| empty_initializer_list_initializer_clause
	;

	initializer_list_initializer_clause
		= ch_p('{') >> !s >> initializer_list >> !s >> !(ch_p(',') >> !s) >> ch_p('}')
	;

	empty_initializer_list_initializer_clause
		= ch_p('{') >> !s >> ch_p('}')
	;

	initializer_list
		= initializer_clause % (!s >> ',' >> !s)
	;

	//1.8 - Classes [gram.class]
	class_specifier
		= class_head >> !s >> '{' >> !s >> !(member_specification >> !s) >> '}'
	;

	class_head
		= class_key >> !(!s >> nested_name_specifier) >> !s >> template_id >> !(!s >> base_clause)
		| class_key >> !s >> nested_name_specifier >> !s >> identifier >> !(!s >> base_clause)
		| class_key >> !(!s >> identifier) >> !(!s >> base_clause)
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
		= member_specification_part % !s
	;
	member_specification_part
		= member_declaration
		| member_specification_access_specifier
	;
	member_specification_access_specifier
		= access_specifier >> !s >> ':'
	;

	member_declaration
		= member_declaration_member_declarator_list
		| member_declaration_unqualified_id
		| member_declaration_function_definition
		| using_declaration
		| template_declaration
	;
	member_declaration_member_declarator_list
		= !(member_declaration_decl_specifier_seq >> !s) >> !(member_declarator_list >> !s) >> ch_p(';')
	;
	member_declaration_unqualified_id
		= !(str_p("::") >> !s) >> nested_name_specifier >> !s >> !(str_p("template") >> !s) >> unqualified_id >> !s >> ch_p(';')
	;
	member_declaration_function_definition
		= function_definition >> !(!s >> ch_p(';'))
	;
	member_declaration_decl_specifier_seq
		= (decl_specifier - (member_declarator_list >> !s >> ch_p(';'))) % !s
	;

	member_declarator_list
		= member_declarator % (!s >> ',' >> !s)
	;

	member_declarator
		= member_declarator_declarator
		| member_declarator_bit_field_member
	;
	member_declarator_declarator
		= declarator >> !(!s >> (pure_specifier | constant_initializer)) ///@todo find what declarator >> !s >> constant_initializer stands for
	;
	member_declarator_bit_field_member
		= !(identifier >> !s) >> ':' >> !s >> conditional_expression //bit field member
	;

	pure_specifier
		= ch_p('=') >> !s >> '0'
	;

	constant_initializer
		= '=' >> !s >> conditional_expression
	;

	//convenience rule, not explicitly in the standard
	destructor_name
		= '~' >> !s >> identifier_or_template_id
	;


	//1.9 - Derived classes [gram.class.derived]
	base_clause
		= ':' >> !s >> base_specifier_list
	;

	base_specifier_list
		= base_specifier % (!s >> ',' >> !s)
	;

	base_specifier
		= nested_identifier_or_template_id
		| "virtual" >> !s >> !(access_specifier >> !s) >> nested_identifier_or_template_id
		| access_specifier >> !s >> !(str_p("virtual") >> !s) >> nested_identifier_or_template_id
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
		= str_p("operator") >> !s >> type_specifier_seq >> !(!s >> ptr_operator_seq)
	;

	ctor_initializer
		= ':' >> !s >> mem_initializer_list
	;

	mem_initializer_list
		= mem_initializer % (!s >> ',' >> !s)
	;

	mem_initializer
		= mem_initializer_id >> !s >> '(' >> !s >> !(expression >> !s) >> ')'
	;

	mem_initializer_id
		= nested_identifier_or_template_id
		| identifier
	;

	//1.11 - Overloading [gram.over]
	operator_function_id
		= str_p("operator") >> !s >> operator_
	;

	operator_
		= array_operator
		| simple_operator
	;

	array_operator
		= new_array_operator
		| delete_array_operator
	;

	new_array_operator
		= str_p("new") >> !s >> '[' >> !s >> ']'
	;

	delete_array_operator
		= str_p("delete") >> !s >> '[' >> !s >> ']'
	;

	simple_operator
		= str_p("new")
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
		= !(str_p("export") >> !s) >> str_p("template") >> !s >> '<' >> !s >> template_parameter_list >> !s >> '>' >> !s >> declaration
	;

	template_parameter_list
		= template_parameter % (!s >> ',' >> !s)
	;

	template_parameter
		= type_parameter
		| parameter_declaration
	;

	type_parameter
		= class_type_parameter
		| typename_type_parameter
		| template_type_parameter
	;

	class_type_parameter
		= str_p("class") >> !(!s >> identifier) >> !(!s >> '=' >> !s >> type_id)
	;

	typename_type_parameter
		= str_p("typename") >> !(!s >> identifier) >> !(!s >> '=' >> !s >> type_id)
	;

	template_type_parameter
		= str_p("template") >> !s >> '<' >> !s >> template_parameter_list >> !s >> '>' >> !s >> str_p("class") >> !(!s >> identifier) >> !(!s >> '=' >> !s >> id_expression)
	;

	template_id
		= type_name >> !s >> '<' >> !s >> !(template_argument_list >> !s) >> '>'
	;

	template_argument_list
		= template_argument % (!s >> ',' >> !s)
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
		= !(str_p("extern") >> !s) >> str_p("template") >> !s >> declaration
	;

	explicit_specialization
		= str_p("template") >> !s >> '<' >> !s >> '>' >> !s >> declaration
	;

	//1.13 - Exception handling [gram.except]
	try_block
		= str_p("try") >> !s >> compound_statement >> !(!s >> handler_seq) //handler_seq is made optional to facilitate the source code completion done during the syntax analysis
	;

	function_try_block
		= str_p("try") >> !s >> !(ctor_initializer >> !s) >> compound_statement >> !(!s >> handler_seq) //handler_seq is made optional to facilitate the source code completion done during the syntax analysis
	;

	handler_seq
		= handler % !s
	;

	handler
		= str_p("catch") >> !s >> '(' >> !s >> exception_declaration >> !s >> ')' >> !s >> compound_statement
	;

	exception_declaration
		= exception_declarator
		| exception_abstract_declarator
		| type_specifier_seq
		| str_p("...")
	;

	exception_declarator
		= type_specifier_seq >> !s >> declarator
	;

	exception_abstract_declarator
		= type_specifier_seq >> !s >> abstract_declarator
	;

	throw_expression
		= "throw" >> !(!s >> assignment_expression)
	;

	exception_specification
		= str_p("throw") >> !s >> '(' >> !s >> !(type_id_list >> !s) >> ')'
	;

	type_id_list
		= type_id % (!s >> ',' >> !s)
	;


	/*
	Convenience rules
	*/
	type_name
		= token_node_d[identifier & type_name_p]
	;

	identifier_or_template_id
		= template_id
		| identifier
	;

	nested_identifier_or_template_id
		= !(str_p("::") >> !s) >> !(nested_name_specifier >> !s) >> identifier_or_template_id
	;


	/*
	Extensions
	These rules are not in the standard, but are required to parse some standard library implementations
	*/
	if(configuration_.enable_typeof_support)
	{
		typeof_expression
			= typeof_keyword >> !s >> '(' >> !s >> expression >> !s >> ')'
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

	if(configuration_.enable_attribute_support)
	{
		attribute_expression
			= token_node_d
			[
				str_p("__attribute__") >> !s >> '(' >> !s >> '(' >> !s >> attribute_content >> !s >> ')' >> !s >> ')'
			]
		;
		attribute_content
			= bracketed_attribute_content
			| *(anychar_p - (')' >> !s >> ')'))
		;
		bracketed_attribute_content
			= *(anychar_p - (ch_p('(') | ')')) >> '(' >> attribute_content >> ')'
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

}}}} //namespace scalpel::cpp::detail::syntax_analysis
