/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2011  Florian Goujeon

This file is part of Scalpel.

Scalpel is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Scalpel is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Scalpel.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef BOOST_SPIRIT_USE_OLD_NAMESPACE
#define BOOST_SPIRIT_USE_OLD_NAMESPACE
#endif

#include "grammar.hpp"
#include <boost/spirit/include/classic_chset.hpp>

namespace scalpel { namespace cpp { namespace syntax_analysis { namespace detail
{

grammar::grammar()
{
	using namespace boost::spirit;

	file
		= translation_unit
	;

	source_character_set
		= no_node_d
		[
			anychar_p
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
		= token_node_d[!ch_p('L') >> '\'' >> c_char_sequence >> '\'']
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
		= token_node_d[+single_string_literal]
	;
	single_string_literal
		= !ch_p('L') >> '"' >> !s_char_sequence >> '"'
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
		= !declaration_seq >> end_p
	;

	//1.4 - Expressions [gram.expr]
	primary_expression
		= str_p("this")
		| lexeme_d[literal]
		| round_bracketed_expression
		| id_expression
	;

	round_bracketed_expression
		= '(' >> expression >> ')'
	;

	id_expression
		= qualified_id
		| unqualified_id
	;

	unqualified_id
		= operator_function_id
		| conversion_function_id
		| destructor_name
		| (template_id - fake_template_id) // "a < b || c > d" is not a template-id, but a boolean expression!
		| lexeme_d[identifier]
	;
	fake_template_id
		= template_id >>
		(
			str_p("this")
			| lexeme_d[literal]
			| id_expression
		)
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
		= str_p("::") >> lexeme_d[identifier]
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
		= identifier_or_template_id >> "::" >> !nested_name_specifier_last_part_seq
	;
	nested_name_specifier_last_part_seq
		= +nested_name_specifier_last_part
	;
	nested_name_specifier_last_part
		= !str_p("template") >> identifier_or_template_id >> "::"
	;

	/*
	The following rule is written like this in the standard:
		postfix_expression
			= primary_expression
			| postfix_expression >> '[' >> expression >> ']'
			| postfix_expression >> '(' >> !expression >> ')'
			| simple_type_specifier >> '(' >> !expression >> ')'
			| str_p("typename")tr_p("::") >> nested_name_specifier >> lexeme_d[identifier] >> '(' >> !expression >> ')'
			| str_p("typename")tr_p("::") >> nested_name_specifiertr_p("template") >> template_id >> '(' >> !expression >> ')'
			| postfix_expression >> '.'tr_p("template") >> id_expression
			| postfix_expression >> "->"tr_p("template") >> id_expression
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
		= postfix_expression_first_part >> !postfix_expression_last_part_seq
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
		= +postfix_expression_last_part
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
		= simple_type_specifier >> '(' >> !expression >> ')'
	;

	typename_expression
		= str_p("typename") >> !str_p("::") >> nested_name_specifier >> lexeme_d[identifier] >> '(' >> !expression >> ')'
	;

	template_typename_expression
		= str_p("typename") >> !str_p("::") >> nested_name_specifier >> !str_p("template") >> template_id >> '(' >> !expression >> ')'
	;

	dynamic_cast_expression
		= str_p("dynamic_cast") >> '<' >> type_id >> '>' >> '(' >> expression >> ')'
	;

	static_cast_expression
		= str_p("static_cast") >> '<' >> type_id >> '>' >> '(' >> expression >> ')'
	;

	reinterpret_cast_expression
		= str_p("reinterpret_cast") >> '<' >> type_id >> '>' >> '(' >> expression >> ')'
	;

	const_cast_expression
		= str_p("const_cast") >> '<' >> type_id >> '>' >> '(' >> expression >> ')'
	;

	typeid_expression
		= str_p("typeid") >> '(' >> expression >> ')'
	;

	type_id_typeid_expression
		= str_p("typeid") >> '(' >> type_id >> ')'
	;

	square_bracketed_expression
		= '[' >> expression >> ']'
	;

	round_bracketed_optional_expression
		= '(' >> !expression >> ')'
	;

	dot_id_expression
		= '.' >> !str_p("template") >> id_expression
	;

	arrow_id_expression
		= "->" >> !str_p("template") >> id_expression
	;

	dot_pseudo_destructor_name
		= '.' >> pseudo_destructor_name
	;

	arrow_pseudo_destructor_name
		= "->" >> pseudo_destructor_name
	;

	pseudo_destructor_name
		= nested_identifier_or_template_id >> str_p("::") >> '~' >> identifier_or_template_id
		| !str_p("::") >> nested_name_specifier >> str_p("template") >> template_id >> str_p("::") >> '~' >> identifier_or_template_id
		| !str_p("::") >> !nested_name_specifier >> '~' >> identifier_or_template_id
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
		= unary_operator >> cast_expression
	;

	type_id_sizeof_expression
		= str_p("sizeof") >> '(' >> type_id >> ')'
	;

	unary_sizeof_expression
		= str_p("sizeof") >> unary_expression
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
		= !str_p("::") >> str_p("new") >> !round_bracketed_expression >> '(' >> type_id >> ')' >> !round_bracketed_optional_expression
	;

	new_type_id_new_expression
		= !str_p("::") >> str_p("new") >> !round_bracketed_expression >> new_type_id >> !round_bracketed_optional_expression
	;

	new_type_id
		= type_specifier_seq >> !new_declarator
	;

	new_declarator
		= ptr_operator_seq >> direct_new_declarator
		| ptr_operator_seq
		| direct_new_declarator
	;

	direct_new_declarator
		= '[' >> expression >> ']' >> !('[' >> conditional_expression >> ']')
	;

	delete_expression
		= simple_delete_expression
		| array_delete_expression
	;

	simple_delete_expression
		= !str_p("::") >> "delete" >> cast_expression
	;

	array_delete_expression
		= !str_p("::") >> "delete" >> '[' >> ']' >> cast_expression
	;

	cast_expression
		= longest_d
		[
			unary_expression //this alternative must be tried first
			| cast_expression_first_part_seq >> unary_expression
		]
	;
	cast_expression_first_part_seq
		= +cast_expression_first_part
	;
	cast_expression_first_part
		= '(' >> type_id >> ')'
	;

	pm_ptr_expression
		= cast_expression % ("->*")
	;

	pm_ref_expression
		= pm_ptr_expression % (".*")
	;

	modulo_expression
		= pm_ref_expression % ('%')
	;

	divisive_expression
		= modulo_expression % ('/')
	;

	multiplicative_expression
		= divisive_expression % ('*')
	;

	subtractive_expression
		= multiplicative_expression % ('-')
	;

	additive_expression
		= subtractive_expression % ('+')
	;

	left_shift_expression
		= additive_expression % ("<<")
	;

	right_shift_expression
		= left_shift_expression % (">>")
	;
	//a shift expression used as a template argument must be placed between brackets if it contains any '>' characters
	template_argument_right_shift_expression
		= round_bracketed_right_shift_expression
		| left_shift_expression
	;
	round_bracketed_right_shift_expression
		= '(' >> right_shift_expression >> ')'
	;

	less_than_or_equal_to_expression
		= right_shift_expression % ("<=")
	;
	template_argument_less_than_or_equal_to_expression
		= template_argument_right_shift_expression % ("<=")
	;

	less_than_expression
		= less_than_or_equal_to_expression % ('<')
	;
	template_argument_less_than_expression
		= template_argument_less_than_or_equal_to_expression % ('<')
	;

	greater_than_or_equal_to_expression
		= less_than_expression % (">=")
	;
	template_argument_greater_than_or_equal_to_expression
		= template_argument_less_than_expression % (">=")
	;

	greater_than_expression
		= greater_than_or_equal_to_expression % ('>')
	;
	//a shift expression used as a template argument must be placed between brackets if it contains any '>' characters
	template_argument_greater_than_expression
		= round_bracketed_greater_than_expression
		| template_argument_greater_than_or_equal_to_expression
	;
	round_bracketed_greater_than_expression
		= '(' >> greater_than_expression >> ')'
	;

	inequality_expression
		= greater_than_expression % ("!=")
	;
	template_argument_inequality_expression
		= template_argument_greater_than_expression % ("!=")
	;

	equality_expression
		= inequality_expression % ("==")
	;
	template_argument_equality_expression
		= template_argument_inequality_expression % ("==")
	;

	and_expression
		= equality_expression % ('&')
	;
	template_argument_and_expression
		= template_argument_equality_expression % ('&')
	;

	exclusive_or_expression
		= and_expression % ('^')
	;
	template_argument_exclusive_or_expression
		= template_argument_and_expression % ('^')
	;

	inclusive_or_expression
		= exclusive_or_expression % ('|')
	;
	template_argument_inclusive_or_expression
		= template_argument_exclusive_or_expression % ('|')
	;

	logical_and_expression
		= inclusive_or_expression % ("&&")
	;
	template_argument_logical_and_expression
		= template_argument_inclusive_or_expression % ("&&")
	;

	logical_or_expression
		= logical_and_expression % ("||")
	;
	template_argument_logical_or_expression
		= template_argument_logical_and_expression % ("||")
	;

	conditional_expression
		= logical_or_expression >> !('?' >> expression >> ':' >> assignment_expression)
	;
	template_argument_conditional_expression
		= template_argument_logical_or_expression >> !('?' >> expression >> ':' >> template_argument_assignment_expression)
	;

	/*
	Original rule is:
		assignment_expression
			= logical_or_expression >> assignment_operator >> assignment_expression
			| conditional_expression
			| throw_expression
		;
	*/
	assignment_expression
		= !assignment_expression_first_part_seq >> assignment_expression_last_part
	;
	assignment_expression_first_part_seq
		= +assignment_expression_first_part
	;
	assignment_expression_first_part
		= logical_or_expression >> assignment_operator
	;
	assignment_expression_last_part
		= conditional_expression
		| throw_expression
	;

	template_argument_assignment_expression
		= !template_argument_assignment_expression_first_part_seq >> template_argument_assignment_expression_last_part
	;
	template_argument_assignment_expression_first_part_seq
		= +template_argument_assignment_expression_first_part
	;
	template_argument_assignment_expression_first_part
		= template_argument_logical_or_expression >> assignment_operator
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
		= assignment_expression % ','
	;

	//1.5 - Statements [gram.stmt.stmt]
	statement
		= block_declaration
		| labeled_statement
		| expression_statement
		| compound_statement
		| selection_statement
		| iteration_statement
		| jump_statement
		| try_block
	;

	labeled_statement
		= case_statement
		| default_statement
		| classic_labeled_statement
	;

	case_statement
		= str_p("case") >> conditional_expression >> ':' >> statement
	;

	default_statement
		= str_p("default") >> ':' >> statement
	;

	classic_labeled_statement
		= lexeme_d[identifier] >> ':' >> statement
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
		= if_statement
		| switch_statement
	;

	if_statement
		= str_p("if") >> '(' >> condition >> ')' >> statement >> !("else" >> statement)
	;

	switch_statement
		= str_p("switch") >> '(' >> condition >> ')' >> statement
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
		= assignment_expression_condition_type_specifier_seq >> declarator >> '=' >> assignment_expression
	;
	assignment_expression_condition_type_specifier_seq
		= +(type_specifier - (declarator >> '=' >> assignment_expression))
	;

	iteration_statement
		= while_statement
		| do_while_statement
		| for_statement
	;

	while_statement
		= str_p("while") >> '(' >> condition >> ')' >> statement
	;

	do_while_statement
		= str_p("do") >> statement >> "while" >> '(' >> expression >> ')' >> ch_p(';')
	;

	for_statement
		= str_p("for") >> '(' >> for_init_statement >> !condition >> ch_p(';') >> !expression >> ')' >> statement
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
		= str_p("break") >> ch_p(';')
	;

	continue_statement
		= str_p("continue") >> ch_p(';')
	;

	return_statement
		= str_p("return") >> !expression >> ch_p(';')
	;

	goto_statement
		= str_p("goto") >> lexeme_d[identifier] >> ch_p(';')
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
		= str_p("register")
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
	;

	simple_type_specifier
		= nested_identifier_or_template_id
		| simple_template_type_specifier
		| fundamental_type_specifier
	;
	simple_template_type_specifier
		= !str_p("::") >> nested_name_specifier >> "template" >> template_id
	;
	fundamental_type_specifier
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
		= class_elaborated_specifier
		| enum_elaborated_specifier
		| typename_template_elaborated_specifier
		| typename_elaborated_specifier
	;

	class_elaborated_specifier
		= class_key >> !str_p("::") >> !nested_name_specifier >> identifier_or_template_id
	;

	enum_elaborated_specifier
		= str_p("enum") >> !str_p("::") >> !nested_name_specifier >> lexeme_d[identifier]
	;

	typename_template_elaborated_specifier
		= str_p("typename") >> !str_p("::") >> nested_name_specifier >> !str_p("template") >> template_id
	;

	typename_elaborated_specifier
		= str_p("typename") >> !str_p("::") >> nested_name_specifier >> lexeme_d[identifier]
	;

	enum_specifier
		= str_p("enum") >> !lexeme_d[identifier] >> ch_p('{') >> !enumerator_list >> !ch_p(',') >> ch_p('}')
	;

	enumerator_list
		= enumerator_definition % ','
	;

	enumerator_definition
		= lexeme_d[identifier] >> !('=' >> conditional_expression)
	;

	namespace_definition
		= str_p("namespace") >> !lexeme_d[identifier] >> '{' >> !declaration_seq >> '}'
	;

	namespace_alias_definition
		= str_p("namespace") >> lexeme_d[identifier] >> '=' >> qualified_namespace_specifier >> ch_p(';')
	;

	qualified_namespace_specifier
		= !str_p("::") >> !nested_name_specifier >> lexeme_d[identifier]
	;

	using_declaration
		= "using" >> !str_p("typename") >> !str_p("::") >> nested_name_specifier >> unqualified_id >> ch_p(';')
		| "using" >> str_p("::") >> unqualified_id >> ch_p(';')
	;

	using_directive
		= str_p("using") >> "namespace" >> !str_p("::") >> !nested_name_specifier >> lexeme_d[identifier] >> ch_p(';')
	;

	asm_definition
		= str_p("asm") >> '(' >> lexeme_d[string_literal] >> ')' >> ch_p(';')
	;

	linkage_specification
		= declaration_seq_linkage_specification
		| declaration_linkage_specification
	;

	declaration_seq_linkage_specification
		= "extern" >> lexeme_d[string_literal] >> ch_p('{') >> !declaration_seq >> ch_p('}')
	;

	declaration_linkage_specification
		= "extern" >> lexeme_d[string_literal] >> declaration
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
		= !ptr_operator_seq >> direct_declarator
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
		= direct_declarator_first_part >> !direct_declarator_last_part_seq
	;
	direct_declarator_first_part
		= bracketed_declarator
		| declarator_id
	;
	bracketed_declarator
		= '(' >> declarator >> ')'
	;
	direct_declarator_last_part_seq
		= +direct_declarator_last_part
	;
	direct_declarator_last_part
		= direct_declarator_function_part
		| direct_declarator_array_part
	;
	direct_declarator_function_part
		= '(' >> !parameter_declaration_clause >> ')' >> !cv_qualifier_seq >> !exception_specification
	;
	direct_declarator_array_part
		= '[' >> !conditional_expression >> ']'
	;

	ptr_operator_seq
		= +ptr_operator
	;

	ptr_operator
		= ptr_ptr_operator
		| ref_ptr_operator
	;

	ptr_ptr_operator
		= simple_ptr_ptr_operator
		| ptr_to_member_operator
	;

	simple_ptr_ptr_operator
		= ch_p('*') >> !cv_qualifier_seq
	;

	ptr_to_member_operator
		= !str_p("::") >> nested_name_specifier >> '*' >> !cv_qualifier_seq
	;

	ref_ptr_operator
		= ch_p('&')
	;

	cv_qualifier_seq
		= +cv_qualifier
	;

	cv_qualifier
		= str_p("const")
		| "volatile"
	;

	declarator_id
		= nested_identifier_or_template_id
		| id_expression
	;

	type_id
		= type_specifier_seq >> !abstract_declarator
	;

	type_specifier_seq
		= +type_specifier
	;

	/*
	Original rule is:
		abstract-declarator
			= ptr-operator, [abstract-declarator]
			| direct-abstract-declarator
		;
	*/
	abstract_declarator
		= !ptr_operator_seq >> direct_abstract_declarator
		| ptr_operator_seq
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
		= '(' >> abstract_declarator >> ')' >> !direct_declarator_last_part
	;

	parameter_declaration_clause
		= parameter_declaration_list >> ',' >> "..."
		| parameter_declaration_list >> str_p("...")
		| parameter_declaration_list
		| str_p("...")
	;

	parameter_declaration_list
		= parameter_declaration % ','
	;

	parameter_declaration
		= decl_specifier_seq >> '=' >> assignment_expression
		| parameter_declaration_decl_specifier_seq1 >> declarator >> '=' >> assignment_expression
		| parameter_declaration_decl_specifier_seq2 >> declarator
		| parameter_declaration_decl_specifier_seq3 >> abstract_declarator >> '=' >> assignment_expression
		| parameter_declaration_decl_specifier_seq4 >> !abstract_declarator
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
			= !decl_specifier_seq >> declarator >> !ctor_initializer >> compound_statement
			| !decl_specifier_seq >> declarator >> function_try_block
		;
	*/
	function_definition
		= simple_function_definition
		| try_block_function_definition
	;
	simple_function_definition
		= !function_definition_decl_specifier_seq1 >> declarator >> ctor_initializer >> compound_statement
		| !function_definition_decl_specifier_seq2 >> declarator >> compound_statement
	;
	try_block_function_definition
		= !function_definition_decl_specifier_seq3 >> declarator >> function_try_block
	;
	function_definition_decl_specifier_seq1
		= +(decl_specifier - (declarator >> ctor_initializer >> compound_statement))
	;
	function_definition_decl_specifier_seq2
		= +(decl_specifier - (declarator >> compound_statement))
	;
	function_definition_decl_specifier_seq3
		= +(decl_specifier - (declarator >> function_try_block))
	;

	initializer
		= equal_initializer
		| round_bracketed_expression
	;

	equal_initializer
		= ch_p('=') >> initializer_clause
	;

	initializer_clause
		= assignment_expression
		| initializer_list_initializer_clause
	;

	initializer_list_initializer_clause
		= ch_p('{') >> initializer_list >> !ch_p(',') >> ch_p('}')
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
		= class_key >> !nested_name_specifier >> identifier_or_template_id >> !base_clause
		| class_key >> !base_clause
	;

	class_key
		= str_p("class")
		| "struct"
		| "union"
	;

	member_specification
		= +member_specification_part
	;
	member_specification_part
		= member_declaration
		| member_specification_access_specifier
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
		= member_declarator_bit_field_member
		| member_declarator_declarator
	;
	member_declarator_declarator
		= declarator >> !constant_initializer
	;
	member_declarator_bit_field_member
		= !lexeme_d[identifier] >> ':' >> conditional_expression
	;

	constant_initializer
		= '=' >> conditional_expression
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
		= str_p("private")
		| "protected"
		| "public"
	;

	//1.10 - Special member functions [gram.special]
	conversion_function_id
		= str_p("operator") >> type_specifier_seq >> !ptr_operator_seq
	;

	ctor_initializer
		= ':' >> mem_initializer_list
	;

	mem_initializer_list
		= mem_initializer % ','
	;

	mem_initializer
		= mem_initializer_id >> '(' >> !expression >> ')'
	;

	mem_initializer_id
		= nested_identifier_or_template_id
		| lexeme_d[identifier]
	;

	//1.11 - Overloading [gram.over]
	operator_function_id
		= str_p("operator") >> operator_
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
		= str_p("new") >> '[' >> ']'
	;

	delete_array_operator
		= str_p("delete") >> '[' >> ']'
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
		= class_type_parameter
		| typename_type_parameter
		| template_type_parameter
	;

	class_type_parameter
		= str_p("class") >> !lexeme_d[identifier] >> !('=' >> type_id)
	;

	typename_type_parameter
		= str_p("typename") >> !lexeme_d[identifier] >> !('=' >> type_id)
	;

	template_type_parameter
		= str_p("template") >> '<' >> template_parameter_list >> '>' >> str_p("class") >> !lexeme_d[identifier] >> !('=' >> id_expression)
	;

	simple_template_id
		= lexeme_d[identifier] >> '<' >> !template_argument_list >> '>'
	;

	operator_function_template_id
		= operator_function_id >> '<' >> !template_argument_list >> '>'
	;

	template_id
		= operator_function_template_id
		| simple_template_id
	;

	template_argument_list
		= template_argument % ','
	;

	/*
	The original rule is:
		template_argument
			= type_id
			| assignment_expression
			| id_expression
		;

	As assignment_expression can contain a '>', we cannot use it directly.

	In each of these cases, (1) must be considered before (2):
		type_template< a < b > t; //(1) assignment_expression
		type_template< a < b > > t; //(2) id_expression or type_id

		type_template< a * > t; //(1) type_id
		type_template< a * b > t; //(2) assignment_expression

		type_template< a & > t; //(1) type_id
		type_template< a & b > t; //(2) assignment_expression
	*/
	template_argument
		= template_argument_assignment_expression - (nested_identifier_or_template_id >> (ch_p('*') | '&'))
		| type_id
		| id_expression
		| template_argument_assignment_expression
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
		= str_p("try") >> !ctor_initializer >> compound_statement >> handler_seq
	;

	handler_seq
		= +handler
	;

	handler
		= str_p("catch") >> '(' >> exception_declaration >> ')' >> compound_statement
	;

	exception_declaration
		= exception_declarator
		| exception_abstract_declarator
		| type_specifier_seq
		| str_p("...")
	;

	exception_declarator
		= type_specifier_seq >> declarator
	;

	exception_abstract_declarator
		= type_specifier_seq >> abstract_declarator
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
	identifier_or_template_id
		= template_id
		| lexeme_d[identifier]
	;

	nested_identifier_or_template_id
		= !str_p("::") >> !nested_name_specifier >> identifier_or_template_id
	;
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

}}}} //namespace scalpel::cpp::syntax_analysis::detail

