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

#ifndef CPP2XML_SYNTAX_TREE_HPP
#define CPP2XML_SYNTAX_TREE_HPP

#include "detail/basic_print_functions.hpp"
#include <scalpel/cpp/syntax_tree.hpp>
#include <scalpel/cpp/syntax_nodes/utility/type_traits.hpp>
#include <string>
#include <sstream>
#include <iostream>

namespace cpp2xml
{

template<class T>
struct type_getter;

#define GET_TYPE_SPECIALIZATION(NODE_TYPE)\
template<> \
struct type_getter<scalpel::cpp::syntax_nodes::NODE_TYPE> \
{ \
	static \
	const std::string \
	get() \
	{ \
		return #NODE_TYPE; \
	} \
}; \
 \
template<> \
struct type_getter<scalpel::cpp::syntax_nodes::optional_node<scalpel::cpp::syntax_nodes::NODE_TYPE>> \
{ \
	static \
	const std::string \
	get() \
	{ \
		return "optional " #NODE_TYPE; \
	} \
};

GET_TYPE_SPECIALIZATION(abstract_declarator)
GET_TYPE_SPECIALIZATION(access_specifier)
GET_TYPE_SPECIALIZATION(additive_expression)
GET_TYPE_SPECIALIZATION(additive_operator)
GET_TYPE_SPECIALIZATION(and_expression)
GET_TYPE_SPECIALIZATION(array_delete_expression)
GET_TYPE_SPECIALIZATION(array_operator)
GET_TYPE_SPECIALIZATION(arrow_id_expression)
GET_TYPE_SPECIALIZATION(arrow_pseudo_destructor_name)
GET_TYPE_SPECIALIZATION(asm_definition)
GET_TYPE_SPECIALIZATION(assignment_expression)
GET_TYPE_SPECIALIZATION(assignment_expression_condition)
GET_TYPE_SPECIALIZATION(assignment_expression_first_part)
GET_TYPE_SPECIALIZATION(assignment_expression_first_part_seq)
GET_TYPE_SPECIALIZATION(assignment_expression_last_part)
GET_TYPE_SPECIALIZATION(assignment_operator)
GET_TYPE_SPECIALIZATION(base_clause)
GET_TYPE_SPECIALIZATION(base_specifier)
GET_TYPE_SPECIALIZATION(base_specifier_list)
GET_TYPE_SPECIALIZATION(block_declaration)
GET_TYPE_SPECIALIZATION(boolean_literal)
GET_TYPE_SPECIALIZATION(bracketed_abstract_declarator)
GET_TYPE_SPECIALIZATION(bracketed_declarator)
GET_TYPE_SPECIALIZATION(break_statement)
GET_TYPE_SPECIALIZATION(c_char)
GET_TYPE_SPECIALIZATION(c_char_sequence)
GET_TYPE_SPECIALIZATION(case_statement)
GET_TYPE_SPECIALIZATION(cast_expression)
GET_TYPE_SPECIALIZATION(cast_expression_first_part)
GET_TYPE_SPECIALIZATION(cast_expression_first_part_seq)
GET_TYPE_SPECIALIZATION(character_literal)
GET_TYPE_SPECIALIZATION(class_elaborated_specifier)
GET_TYPE_SPECIALIZATION(class_head)
GET_TYPE_SPECIALIZATION(class_key)
GET_TYPE_SPECIALIZATION(class_specifier)
GET_TYPE_SPECIALIZATION(class_type_parameter)
GET_TYPE_SPECIALIZATION(classic_labeled_statement)
GET_TYPE_SPECIALIZATION(compound_statement)
GET_TYPE_SPECIALIZATION(condition)
GET_TYPE_SPECIALIZATION(conditional_expression)
GET_TYPE_SPECIALIZATION(const_cast_expression)
GET_TYPE_SPECIALIZATION(constant_initializer)
GET_TYPE_SPECIALIZATION(continue_statement)
GET_TYPE_SPECIALIZATION(conversion_function_id)
GET_TYPE_SPECIALIZATION(ctor_initializer)
GET_TYPE_SPECIALIZATION(cv_qualifier)
GET_TYPE_SPECIALIZATION(cv_qualifier_seq)
GET_TYPE_SPECIALIZATION(decimal_literal)
GET_TYPE_SPECIALIZATION(decl_specifier)
GET_TYPE_SPECIALIZATION(decl_specifier_seq)
GET_TYPE_SPECIALIZATION(declaration)
GET_TYPE_SPECIALIZATION(declaration_linkage_specification)
GET_TYPE_SPECIALIZATION(declaration_seq)
GET_TYPE_SPECIALIZATION(declaration_seq_linkage_specification)
GET_TYPE_SPECIALIZATION(declarator)
GET_TYPE_SPECIALIZATION(declarator_id)
GET_TYPE_SPECIALIZATION(default_statement)
GET_TYPE_SPECIALIZATION(delete_array_operator)
GET_TYPE_SPECIALIZATION(delete_expression)
GET_TYPE_SPECIALIZATION(destructor_name)
GET_TYPE_SPECIALIZATION(direct_abstract_declarator)
GET_TYPE_SPECIALIZATION(direct_declarator)
GET_TYPE_SPECIALIZATION(direct_declarator_array_part)
GET_TYPE_SPECIALIZATION(direct_declarator_first_part)
GET_TYPE_SPECIALIZATION(direct_declarator_function_part)
GET_TYPE_SPECIALIZATION(direct_declarator_last_part)
GET_TYPE_SPECIALIZATION(direct_declarator_last_part_seq)
GET_TYPE_SPECIALIZATION(direct_new_declarator)
GET_TYPE_SPECIALIZATION(do_while_statement)
GET_TYPE_SPECIALIZATION(dot_id_expression)
GET_TYPE_SPECIALIZATION(dot_pseudo_destructor_name)
GET_TYPE_SPECIALIZATION(dynamic_cast_expression)
GET_TYPE_SPECIALIZATION(elaborated_type_specifier)
GET_TYPE_SPECIALIZATION(enum_elaborated_specifier)
GET_TYPE_SPECIALIZATION(enum_specifier)
GET_TYPE_SPECIALIZATION(enumerator_definition)
GET_TYPE_SPECIALIZATION(enumerator_list)
GET_TYPE_SPECIALIZATION(equal_initializer)
GET_TYPE_SPECIALIZATION(equality_expression)
GET_TYPE_SPECIALIZATION(equality_operator)
GET_TYPE_SPECIALIZATION(escape_sequence)
GET_TYPE_SPECIALIZATION(exception_abstract_declarator)
GET_TYPE_SPECIALIZATION(exception_declaration)
GET_TYPE_SPECIALIZATION(exception_declarator)
GET_TYPE_SPECIALIZATION(exception_specification)
GET_TYPE_SPECIALIZATION(exclusive_or_expression)
GET_TYPE_SPECIALIZATION(explicit_instantiation)
GET_TYPE_SPECIALIZATION(explicit_specialization)
GET_TYPE_SPECIALIZATION(exponent_part)
GET_TYPE_SPECIALIZATION(expression)
GET_TYPE_SPECIALIZATION(expression_statement)
GET_TYPE_SPECIALIZATION(floating_literal)
GET_TYPE_SPECIALIZATION(floating_suffix)
GET_TYPE_SPECIALIZATION(for_init_statement)
GET_TYPE_SPECIALIZATION(for_statement)
GET_TYPE_SPECIALIZATION(function_definition)
GET_TYPE_SPECIALIZATION(function_specifier)
GET_TYPE_SPECIALIZATION(function_try_block)
GET_TYPE_SPECIALIZATION(fundamental_type_specifier)
GET_TYPE_SPECIALIZATION(goto_statement)
GET_TYPE_SPECIALIZATION(handler)
GET_TYPE_SPECIALIZATION(handler_seq)
GET_TYPE_SPECIALIZATION(hex_quad)
GET_TYPE_SPECIALIZATION(hexadecimal_literal)
GET_TYPE_SPECIALIZATION(id_expression)
GET_TYPE_SPECIALIZATION(identifier)
GET_TYPE_SPECIALIZATION(identifier_or_template_id)
GET_TYPE_SPECIALIZATION(if_statement)
GET_TYPE_SPECIALIZATION(inclusive_or_expression)
GET_TYPE_SPECIALIZATION(init_declarator)
GET_TYPE_SPECIALIZATION(init_declarator_list)
GET_TYPE_SPECIALIZATION(initializer)
GET_TYPE_SPECIALIZATION(initializer_clause)
GET_TYPE_SPECIALIZATION(initializer_list)
GET_TYPE_SPECIALIZATION(initializer_list_initializer_clause)
GET_TYPE_SPECIALIZATION(integer_literal)
GET_TYPE_SPECIALIZATION(integer_literal_no_suffix)
GET_TYPE_SPECIALIZATION(integer_suffix)
GET_TYPE_SPECIALIZATION(iteration_statement)
GET_TYPE_SPECIALIZATION(jump_statement)
GET_TYPE_SPECIALIZATION(labeled_statement)
GET_TYPE_SPECIALIZATION(linkage_specification)
GET_TYPE_SPECIALIZATION(literal)
GET_TYPE_SPECIALIZATION(logical_and_expression)
GET_TYPE_SPECIALIZATION(logical_or_expression)
GET_TYPE_SPECIALIZATION(mem_initializer)
GET_TYPE_SPECIALIZATION(mem_initializer_id)
GET_TYPE_SPECIALIZATION(mem_initializer_list)
GET_TYPE_SPECIALIZATION(member_declaration)
GET_TYPE_SPECIALIZATION(member_declaration_function_definition)
GET_TYPE_SPECIALIZATION(member_declaration_member_declarator_list)
GET_TYPE_SPECIALIZATION(member_declaration_unqualified_id)
GET_TYPE_SPECIALIZATION(member_declarator)
GET_TYPE_SPECIALIZATION(member_declarator_bit_field_member)
GET_TYPE_SPECIALIZATION(member_declarator_declarator)
GET_TYPE_SPECIALIZATION(member_declarator_list)
GET_TYPE_SPECIALIZATION(member_specification)
GET_TYPE_SPECIALIZATION(member_specification_access_specifier)
GET_TYPE_SPECIALIZATION(member_specification_part)
GET_TYPE_SPECIALIZATION(multiplicative_expression)
GET_TYPE_SPECIALIZATION(multiplicative_operator)
GET_TYPE_SPECIALIZATION(namespace_alias_definition)
GET_TYPE_SPECIALIZATION(namespace_definition)
GET_TYPE_SPECIALIZATION(nested_identifier_or_template_id)
GET_TYPE_SPECIALIZATION(nested_name_specifier)
GET_TYPE_SPECIALIZATION(nested_name_specifier_last_part)
GET_TYPE_SPECIALIZATION(nested_name_specifier_last_part_seq)
GET_TYPE_SPECIALIZATION(new_array_operator)
GET_TYPE_SPECIALIZATION(new_declarator)
GET_TYPE_SPECIALIZATION(new_expression)
GET_TYPE_SPECIALIZATION(new_type_id)
GET_TYPE_SPECIALIZATION(new_type_id_new_expression)
GET_TYPE_SPECIALIZATION(octal_literal)
GET_TYPE_SPECIALIZATION(operator_)
GET_TYPE_SPECIALIZATION(operator_function_id)
GET_TYPE_SPECIALIZATION(operator_function_template_id)
GET_TYPE_SPECIALIZATION(parameter_declaration)
GET_TYPE_SPECIALIZATION(parameter_declaration_clause)
GET_TYPE_SPECIALIZATION(parameter_declaration_list)
GET_TYPE_SPECIALIZATION(pm_expression)
GET_TYPE_SPECIALIZATION(pm_operator)
GET_TYPE_SPECIALIZATION(postfix_expression)
GET_TYPE_SPECIALIZATION(postfix_expression_first_part)
GET_TYPE_SPECIALIZATION(postfix_expression_last_part)
GET_TYPE_SPECIALIZATION(postfix_expression_last_part_seq)
GET_TYPE_SPECIALIZATION(primary_expression)
GET_TYPE_SPECIALIZATION(ptr_operator)
GET_TYPE_SPECIALIZATION(ptr_operator_seq)
GET_TYPE_SPECIALIZATION(ptr_ptr_operator)
GET_TYPE_SPECIALIZATION(ptr_to_member_operator)
GET_TYPE_SPECIALIZATION(qualified_id)
GET_TYPE_SPECIALIZATION(qualified_identifier)
GET_TYPE_SPECIALIZATION(qualified_namespace_specifier)
GET_TYPE_SPECIALIZATION(qualified_nested_id)
GET_TYPE_SPECIALIZATION(qualified_operator_function_id)
GET_TYPE_SPECIALIZATION(qualified_template_id)
GET_TYPE_SPECIALIZATION(ref_ptr_operator)
GET_TYPE_SPECIALIZATION(reinterpret_cast_expression)
GET_TYPE_SPECIALIZATION(relational_expression)
GET_TYPE_SPECIALIZATION(relational_operator)
GET_TYPE_SPECIALIZATION(return_statement)
GET_TYPE_SPECIALIZATION(round_bracketed_expression)
GET_TYPE_SPECIALIZATION(round_bracketed_optional_expression)
GET_TYPE_SPECIALIZATION(s_char)
GET_TYPE_SPECIALIZATION(s_char_sequence)
GET_TYPE_SPECIALIZATION(selection_statement)
GET_TYPE_SPECIALIZATION(shift_expression)
GET_TYPE_SPECIALIZATION(shift_operator)
GET_TYPE_SPECIALIZATION(simple_declaration)
GET_TYPE_SPECIALIZATION(simple_delete_expression)
GET_TYPE_SPECIALIZATION(simple_escape_sequence)
GET_TYPE_SPECIALIZATION(simple_function_definition)
GET_TYPE_SPECIALIZATION(simple_operator)
GET_TYPE_SPECIALIZATION(simple_ptr_ptr_operator)
GET_TYPE_SPECIALIZATION(simple_template_id)
GET_TYPE_SPECIALIZATION(simple_template_type_specifier)
GET_TYPE_SPECIALIZATION(simple_type_specifier)
GET_TYPE_SPECIALIZATION(simple_type_specifier_postfix_expression)
GET_TYPE_SPECIALIZATION(single_string_literal)
GET_TYPE_SPECIALIZATION(source_character_set)
GET_TYPE_SPECIALIZATION(square_bracketed_expression)
GET_TYPE_SPECIALIZATION(statement)
GET_TYPE_SPECIALIZATION(statement_seq)
GET_TYPE_SPECIALIZATION(static_cast_expression)
GET_TYPE_SPECIALIZATION(storage_class_specifier)
GET_TYPE_SPECIALIZATION(string_literal)
GET_TYPE_SPECIALIZATION(switch_statement)
GET_TYPE_SPECIALIZATION(template_argument)
GET_TYPE_SPECIALIZATION(template_argument_and_expression)
GET_TYPE_SPECIALIZATION(template_argument_assignment_expression)
GET_TYPE_SPECIALIZATION(template_argument_assignment_expression_first_part)
GET_TYPE_SPECIALIZATION(template_argument_assignment_expression_first_part_seq)
GET_TYPE_SPECIALIZATION(template_argument_assignment_expression_last_part)
GET_TYPE_SPECIALIZATION(template_argument_conditional_expression)
GET_TYPE_SPECIALIZATION(template_argument_equality_expression)
GET_TYPE_SPECIALIZATION(template_argument_exclusive_or_expression)
GET_TYPE_SPECIALIZATION(template_argument_inclusive_or_expression)
GET_TYPE_SPECIALIZATION(template_argument_list)
GET_TYPE_SPECIALIZATION(template_argument_logical_and_expression)
GET_TYPE_SPECIALIZATION(template_argument_logical_or_expression)
GET_TYPE_SPECIALIZATION(template_argument_relational_expression)
GET_TYPE_SPECIALIZATION(template_argument_relational_operator)
GET_TYPE_SPECIALIZATION(template_argument_shift_expression)
GET_TYPE_SPECIALIZATION(template_argument_shift_operator)
GET_TYPE_SPECIALIZATION(template_declaration)
GET_TYPE_SPECIALIZATION(template_id)
GET_TYPE_SPECIALIZATION(template_parameter)
GET_TYPE_SPECIALIZATION(template_parameter_list)
GET_TYPE_SPECIALIZATION(template_type_parameter)
GET_TYPE_SPECIALIZATION(template_typename_expression)
GET_TYPE_SPECIALIZATION(throw_expression)
GET_TYPE_SPECIALIZATION(translation_unit)
GET_TYPE_SPECIALIZATION(try_block)
GET_TYPE_SPECIALIZATION(try_block_function_definition)
GET_TYPE_SPECIALIZATION(type_id)
GET_TYPE_SPECIALIZATION(type_id_list)
GET_TYPE_SPECIALIZATION(type_id_new_expression)
GET_TYPE_SPECIALIZATION(type_id_sizeof_expression)
GET_TYPE_SPECIALIZATION(type_id_typeid_expression)
GET_TYPE_SPECIALIZATION(type_parameter)
GET_TYPE_SPECIALIZATION(type_specifier)
GET_TYPE_SPECIALIZATION(type_specifier_seq)
GET_TYPE_SPECIALIZATION(typeid_expression)
GET_TYPE_SPECIALIZATION(typename_elaborated_specifier)
GET_TYPE_SPECIALIZATION(typename_expression)
GET_TYPE_SPECIALIZATION(typename_template_elaborated_specifier)
GET_TYPE_SPECIALIZATION(typename_type_parameter)
GET_TYPE_SPECIALIZATION(unary_expression)
GET_TYPE_SPECIALIZATION(unary_operator)
GET_TYPE_SPECIALIZATION(unary_operator_unary_expression)
GET_TYPE_SPECIALIZATION(unary_sizeof_expression)
GET_TYPE_SPECIALIZATION(universal_character_name)
GET_TYPE_SPECIALIZATION(unqualified_id)
GET_TYPE_SPECIALIZATION(using_declaration)
GET_TYPE_SPECIALIZATION(using_directive)
GET_TYPE_SPECIALIZATION(while_statement)

#undef GET_TYPE_SPECIALIZATION



template<class T>
const std::string
get_type()
{
	return type_getter<T>::get();
}



inline
void
print_syntax_tree(const scalpel::cpp::syntax_tree& tree);

//overload for sequence nodes
template<class SyntaxNode, bool PrintType = true>
void
print
(
	const SyntaxNode& node,
	const unsigned int indent_level = 0,
	typename boost::enable_if<syntax_nodes::utility::is_sequence_node<SyntaxNode>>::type* = 0,
	typename boost::disable_if<boost::is_same<typename SyntaxNode::head_node_t, void>>::type* = 0
);

//overload for alternative nodes
template<class SyntaxNode, bool PrintType = true>
void
print
(
	const SyntaxNode& node,
	const unsigned int indent_level = 0,
	typename boost::enable_if<syntax_nodes::utility::is_alternative_node<SyntaxNode>>::type* = 0,
	typename boost::disable_if<boost::is_same<typename SyntaxNode::head_node_t, void>>::type* = 0
);

//overload for list nodes
template<class SyntaxNode>
void
print
(
	const SyntaxNode& node,
	const unsigned int indent_level = 0,
	typename boost::enable_if<syntax_nodes::utility::is_list_node<SyntaxNode>>::type* = 0
);

//overload for optional nodes
template<class SyntaxNode>
void
print
(
	const SyntaxNode& node,
	const unsigned int indent_level = 0,
	typename boost::enable_if<syntax_nodes::utility::is_optional_node<SyntaxNode>>::type* = 0
);

//overload for predefined_text nodes
template<class SyntaxNode>
void
print
(
	const SyntaxNode& node,
	const unsigned int indent_level = 0,
	typename boost::enable_if<syntax_nodes::utility::is_predefined_text_node<SyntaxNode>>::type* = 0
);

//overload for leaf nodes
template<class SyntaxNode>
void
print
(
	const SyntaxNode& node,
	const unsigned int indent_level = 0,
	typename boost::enable_if<syntax_nodes::utility::is_leaf_node<SyntaxNode>>::type* = 0
);

//overload for empty nodes (sequence and alternative tail nodes)
template<class SyntaxNode, bool PrintType = false>
void
print
(
	const SyntaxNode&,
	const unsigned int indent_level = 0,
	typename boost::enable_if<boost::is_same<typename SyntaxNode::head_node_t, void>>::type* = 0
);



inline
void
print_syntax_tree(const scalpel::cpp::syntax_tree& tree)
{
	print(tree);
}

//overload for sequence nodes
template<class SyntaxNode, bool PrintType>
struct print_sequence_node_impl;

template<class SyntaxNode>
struct print_sequence_node_impl<SyntaxNode, true>
{
	static
	void
	print_node
	(
		const SyntaxNode& node,
		const unsigned int indent_level
	)
	{
		std::cout << detail::indent(indent_level) << "<" << get_type<SyntaxNode>() << ">\n";
		print(node.head(), indent_level + 1);
		print<typename SyntaxNode::tail_sequence_node_t, false>(node.tail(), indent_level + 1);
		std::cout << detail::indent(indent_level) << "</" << get_type<SyntaxNode>() << ">\n";
	}
};

template<class SyntaxNode>
struct print_sequence_node_impl<SyntaxNode, false>
{
	static
	void
	print_node
	(
		const SyntaxNode& node,
		const unsigned int indent_level
	)
	{
		print(node.head(), indent_level);
		print<typename SyntaxNode::tail_sequence_node_t, false>(node.tail(), indent_level);
	}
};

template<class SyntaxNode, bool PrintType>
void
print
(
	const SyntaxNode& node,
	const unsigned int indent_level,
	typename boost::enable_if<syntax_nodes::utility::is_sequence_node<SyntaxNode>>::type* = 0,
	typename boost::disable_if<boost::is_same<typename SyntaxNode::head_node_t, void>>::type* = 0
)
{
	print_sequence_node_impl<SyntaxNode, PrintType>::print_node(node, indent_level);
}

//overload for alternative nodes
template<class SyntaxNode, bool PrintType>
struct print_alternative_node_impl;

template<class SyntaxNode>
struct print_alternative_node_impl<SyntaxNode, true>
{
	static
	void
	print_node
	(
		const SyntaxNode& node,
		const unsigned int indent_level
	)
	{
		typedef typename SyntaxNode::head_node_t head_node_t;
		boost::optional<const head_node_t&> opt_node = scalpel::cpp::syntax_nodes::get<head_node_t>(&node);

		std::cout << detail::indent(indent_level) << "<" << get_type<SyntaxNode>() << ">\n";
		if(opt_node)
			print(*opt_node, indent_level + 1);
		else
			print<typename SyntaxNode::tail_alternative_node_t, false>(node.tail(), indent_level + 1);
		std::cout << detail::indent(indent_level) << "</" << get_type<SyntaxNode>() << ">\n";
	}
};

template<class SyntaxNode>
struct print_alternative_node_impl<SyntaxNode, false>
{
	static
	void
	print_node
	(
		const SyntaxNode& node,
		const unsigned int indent_level
	)
	{
		typedef typename SyntaxNode::head_node_t head_node_t;
		boost::optional<const head_node_t&> opt_node = scalpel::cpp::syntax_nodes::get<head_node_t>(&node);

		if(opt_node)
			print(*opt_node, indent_level);
		else
			print<typename SyntaxNode::tail_alternative_node_t, false>(node.tail(), indent_level);
	}
};

template<class SyntaxNode, bool PrintType>
void
print
(
	const SyntaxNode& node,
	const unsigned int indent_level,
	typename boost::enable_if<syntax_nodes::utility::is_alternative_node<SyntaxNode>>::type* = 0,
	typename boost::disable_if<boost::is_same<typename SyntaxNode::head_node_t, void>>::type* = 0
)
{
	print_alternative_node_impl<SyntaxNode, PrintType>::print_node(node, indent_level);
}

//overload for list nodes
template<class SyntaxNode>
void
print
(
	const SyntaxNode& node,
	const unsigned int indent_level,
	typename boost::enable_if<syntax_nodes::utility::is_list_node<SyntaxNode>>::type* = 0
)
{
	std::cout << detail::indent(indent_level) << "<" << get_type<SyntaxNode>() << ">\n";
	for(auto i = node.begin(); i != node.end(); ++i) //for each node of the list
		print(*i, indent_level + 1);
	std::cout << detail::indent(indent_level) << "</" << get_type<SyntaxNode>() << ">\n";
}

//overload for optional nodes
template<class SyntaxNode>
void
print
(
	const SyntaxNode& node,
	const unsigned int indent_level,
	typename boost::enable_if<syntax_nodes::utility::is_optional_node<SyntaxNode>>::type* = 0
)
{
	if(node) print(*node, indent_level);
}

//overload for predefined_text nodes
template<class SyntaxNode>
void
print
(
	const SyntaxNode& node,
	const unsigned int indent_level,
	typename boost::enable_if<syntax_nodes::utility::is_predefined_text_node<SyntaxNode>>::type* = 0
)
{
	std::cout << detail::indent(indent_level) << "<predefined_text_node>";
	std::cout << detail::strip_special_chars(node.text());
	std::cout << "</predefined_text_node>";
	std::cout << "\n";
}

//overload for leaf nodes
template<class SyntaxNode>
void
print
(
	const SyntaxNode& node,
	const unsigned int indent_level,
	typename boost::enable_if<syntax_nodes::utility::is_leaf_node<SyntaxNode>>::type* = 0
)
{
	std::cout << detail::indent(indent_level) << "<leaf_node>";
	std::cout << detail::strip_special_chars(node.value());
	std::cout << "</leaf_node>";
	std::cout << "\n";
}

//overload for empty nodes (sequence and alternative tail nodes)
template<class SyntaxNode, bool PrintType>
void
print
(
	const SyntaxNode&,
	const unsigned int,
	typename boost::enable_if<boost::is_same<typename SyntaxNode::head_node_t, void>>::type* = 0
)
{
	//does nothing
}

} //namespace cpp2xml

#endif

