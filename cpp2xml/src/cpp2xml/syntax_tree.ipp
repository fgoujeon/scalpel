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

#ifndef CPP2XML_SYNTAX_TREE_IPP
#define CPP2XML_SYNTAX_TREE_IPP

namespace cpp2xml
{

template<class T>
struct type_to_string;

#define TYPE_TO_STRING(NODE_TYPE)\
template<> \
struct type_to_string<scalpel::cpp::syntax_nodes::NODE_TYPE> \
{ \
	static constexpr const char* value = #NODE_TYPE; \
};

TYPE_TO_STRING(abstract_declarator)
TYPE_TO_STRING(access_specifier)
TYPE_TO_STRING(additive_expression)
TYPE_TO_STRING(additive_operator)
TYPE_TO_STRING(and_expression)
TYPE_TO_STRING(array_delete_expression)
TYPE_TO_STRING(array_operator)
TYPE_TO_STRING(arrow_id_expression)
TYPE_TO_STRING(arrow_pseudo_destructor_name)
TYPE_TO_STRING(asm_definition)
TYPE_TO_STRING(assignment_expression)
TYPE_TO_STRING(assignment_assignment_expression)
TYPE_TO_STRING(assignment_expression_condition)
TYPE_TO_STRING(assignment_operator)
TYPE_TO_STRING(base_clause)
TYPE_TO_STRING(base_specifier)
TYPE_TO_STRING(base_specifier_list)
TYPE_TO_STRING(block_declaration)
TYPE_TO_STRING(boolean_literal)
TYPE_TO_STRING(bracketed_abstract_declarator)
TYPE_TO_STRING(bracketed_declarator)
TYPE_TO_STRING(break_statement)
TYPE_TO_STRING(c_char)
TYPE_TO_STRING(c_char_sequence)
TYPE_TO_STRING(case_statement)
TYPE_TO_STRING(cast_expression)
TYPE_TO_STRING(cast_expression_first_part)
TYPE_TO_STRING(cast_expression_first_part_seq)
TYPE_TO_STRING(character_literal)
TYPE_TO_STRING(class_elaborated_specifier)
TYPE_TO_STRING(class_head)
TYPE_TO_STRING(class_key)
TYPE_TO_STRING(class_specifier)
TYPE_TO_STRING(class_type_parameter)
TYPE_TO_STRING(classic_labeled_statement)
TYPE_TO_STRING(compound_statement)
TYPE_TO_STRING(condition)
TYPE_TO_STRING(conditional_expression)
TYPE_TO_STRING(const_cast_expression)
TYPE_TO_STRING(constant_initializer)
TYPE_TO_STRING(continue_statement)
TYPE_TO_STRING(conversion_function_id)
TYPE_TO_STRING(ctor_initializer)
TYPE_TO_STRING(cv_qualifier)
TYPE_TO_STRING(cv_qualifier_seq)
TYPE_TO_STRING(decimal_literal)
TYPE_TO_STRING(decl_specifier)
TYPE_TO_STRING(decl_specifier_seq)
TYPE_TO_STRING(declaration)
TYPE_TO_STRING(declaration_linkage_specification)
TYPE_TO_STRING(declaration_seq)
TYPE_TO_STRING(declaration_seq_linkage_specification)
TYPE_TO_STRING(declarator)
TYPE_TO_STRING(declarator_id)
TYPE_TO_STRING(default_statement)
TYPE_TO_STRING(delete_array_operator)
TYPE_TO_STRING(delete_expression)
TYPE_TO_STRING(destructor_name)
TYPE_TO_STRING(direct_abstract_declarator)
TYPE_TO_STRING(direct_declarator)
TYPE_TO_STRING(direct_declarator_array_part)
TYPE_TO_STRING(direct_declarator_first_part)
TYPE_TO_STRING(direct_declarator_function_part)
TYPE_TO_STRING(direct_declarator_last_part)
TYPE_TO_STRING(direct_declarator_last_part_seq)
TYPE_TO_STRING(direct_new_declarator)
TYPE_TO_STRING(do_while_statement)
TYPE_TO_STRING(dot_id_expression)
TYPE_TO_STRING(dot_pseudo_destructor_name)
TYPE_TO_STRING(dynamic_cast_expression)
TYPE_TO_STRING(elaborated_type_specifier)
TYPE_TO_STRING(enum_elaborated_specifier)
TYPE_TO_STRING(enum_specifier)
TYPE_TO_STRING(enumerator_definition)
TYPE_TO_STRING(enumerator_list)
TYPE_TO_STRING(equal_initializer)
TYPE_TO_STRING(equality_expression)
TYPE_TO_STRING(equality_operator)
TYPE_TO_STRING(escape_sequence)
TYPE_TO_STRING(exception_abstract_declarator)
TYPE_TO_STRING(exception_declaration)
TYPE_TO_STRING(exception_declarator)
TYPE_TO_STRING(exception_specification)
TYPE_TO_STRING(exclusive_or_expression)
TYPE_TO_STRING(explicit_instantiation)
TYPE_TO_STRING(explicit_specialization)
TYPE_TO_STRING(exponent_part)
TYPE_TO_STRING(expression)
TYPE_TO_STRING(expression_statement)
TYPE_TO_STRING(floating_literal)
TYPE_TO_STRING(floating_suffix)
TYPE_TO_STRING(for_init_statement)
TYPE_TO_STRING(for_statement)
TYPE_TO_STRING(function_definition)
TYPE_TO_STRING(function_specifier)
TYPE_TO_STRING(function_try_block)
TYPE_TO_STRING(fundamental_type_specifier)
TYPE_TO_STRING(goto_statement)
TYPE_TO_STRING(handler)
TYPE_TO_STRING(handler_seq)
TYPE_TO_STRING(hex_quad)
TYPE_TO_STRING(hexadecimal_literal)
TYPE_TO_STRING(id_expression)
TYPE_TO_STRING(identifier)
TYPE_TO_STRING(identifier_or_template_id)
TYPE_TO_STRING(if_statement)
TYPE_TO_STRING(inclusive_or_expression)
TYPE_TO_STRING(init_declarator)
TYPE_TO_STRING(init_declarator_list)
TYPE_TO_STRING(initializer)
TYPE_TO_STRING(initializer_clause)
TYPE_TO_STRING(initializer_list)
TYPE_TO_STRING(initializer_list_initializer_clause)
TYPE_TO_STRING(integer_literal)
TYPE_TO_STRING(integer_literal_no_suffix)
TYPE_TO_STRING(integer_suffix)
TYPE_TO_STRING(iteration_statement)
TYPE_TO_STRING(jump_statement)
TYPE_TO_STRING(labeled_statement)
TYPE_TO_STRING(linkage_specification)
TYPE_TO_STRING(literal)
TYPE_TO_STRING(logical_and_expression)
TYPE_TO_STRING(logical_or_expression)
TYPE_TO_STRING(mem_initializer)
TYPE_TO_STRING(mem_initializer_id)
TYPE_TO_STRING(mem_initializer_list)
TYPE_TO_STRING(member_declaration)
TYPE_TO_STRING(member_declaration_function_definition)
TYPE_TO_STRING(member_declaration_member_declarator_list)
TYPE_TO_STRING(member_declaration_unqualified_id)
TYPE_TO_STRING(member_declarator)
TYPE_TO_STRING(member_declarator_bit_field_member)
TYPE_TO_STRING(member_declarator_declarator)
TYPE_TO_STRING(member_declarator_list)
TYPE_TO_STRING(member_specification)
TYPE_TO_STRING(member_specification_access_specifier)
TYPE_TO_STRING(member_specification_part)
TYPE_TO_STRING(multiplicative_expression)
TYPE_TO_STRING(multiplicative_operator)
TYPE_TO_STRING(namespace_alias_definition)
TYPE_TO_STRING(namespace_definition)
TYPE_TO_STRING(nested_identifier_or_template_id)
TYPE_TO_STRING(nested_name_specifier)
TYPE_TO_STRING(nested_name_specifier_last_part)
TYPE_TO_STRING(nested_name_specifier_last_part_seq)
TYPE_TO_STRING(new_array_operator)
TYPE_TO_STRING(new_declarator)
TYPE_TO_STRING(new_expression)
TYPE_TO_STRING(new_type_id)
TYPE_TO_STRING(new_type_id_new_expression)
TYPE_TO_STRING(octal_literal)
TYPE_TO_STRING(operator_)
TYPE_TO_STRING(operator_function_id)
TYPE_TO_STRING(operator_function_template_id)
TYPE_TO_STRING(parameter_declaration)
TYPE_TO_STRING(parameter_declaration_clause)
TYPE_TO_STRING(parameter_declaration_list)
TYPE_TO_STRING(pm_expression)
TYPE_TO_STRING(pm_operator)
TYPE_TO_STRING(postfix_expression)
TYPE_TO_STRING(postfix_expression_first_part)
TYPE_TO_STRING(postfix_expression_last_part)
TYPE_TO_STRING(postfix_expression_last_part_seq)
TYPE_TO_STRING(primary_expression)
TYPE_TO_STRING(ptr_operator)
TYPE_TO_STRING(ptr_operator_seq)
TYPE_TO_STRING(ptr_ptr_operator)
TYPE_TO_STRING(ptr_to_member_operator)
TYPE_TO_STRING(qualified_id)
TYPE_TO_STRING(qualified_identifier)
TYPE_TO_STRING(qualified_namespace_specifier)
TYPE_TO_STRING(qualified_nested_id)
TYPE_TO_STRING(qualified_operator_function_id)
TYPE_TO_STRING(qualified_template_id)
TYPE_TO_STRING(ref_ptr_operator)
TYPE_TO_STRING(reinterpret_cast_expression)
TYPE_TO_STRING(relational_expression)
TYPE_TO_STRING(relational_operator)
TYPE_TO_STRING(return_statement)
TYPE_TO_STRING(round_bracketed_expression)
TYPE_TO_STRING(round_bracketed_optional_expression)
TYPE_TO_STRING(s_char)
TYPE_TO_STRING(s_char_sequence)
TYPE_TO_STRING(selection_statement)
TYPE_TO_STRING(shift_expression)
TYPE_TO_STRING(shift_operator)
TYPE_TO_STRING(simple_declaration)
TYPE_TO_STRING(simple_delete_expression)
TYPE_TO_STRING(simple_escape_sequence)
TYPE_TO_STRING(simple_function_definition)
TYPE_TO_STRING(simple_operator)
TYPE_TO_STRING(simple_ptr_ptr_operator)
TYPE_TO_STRING(simple_template_id)
TYPE_TO_STRING(simple_template_type_specifier)
TYPE_TO_STRING(simple_type_specifier)
TYPE_TO_STRING(simple_type_specifier_postfix_expression)
TYPE_TO_STRING(single_string_literal)
TYPE_TO_STRING(source_character_set)
TYPE_TO_STRING(square_bracketed_expression)
TYPE_TO_STRING(statement)
TYPE_TO_STRING(statement_seq)
TYPE_TO_STRING(static_cast_expression)
TYPE_TO_STRING(storage_class_specifier)
TYPE_TO_STRING(string_literal)
TYPE_TO_STRING(switch_statement)
TYPE_TO_STRING(template_argument)
TYPE_TO_STRING(template_argument_and_expression)
TYPE_TO_STRING(template_argument_assignment_expression)
TYPE_TO_STRING(template_argument_assignment_assignment_expression)
TYPE_TO_STRING(template_argument_conditional_expression)
TYPE_TO_STRING(template_argument_equality_expression)
TYPE_TO_STRING(template_argument_exclusive_or_expression)
TYPE_TO_STRING(template_argument_inclusive_or_expression)
TYPE_TO_STRING(template_argument_list)
TYPE_TO_STRING(template_argument_logical_and_expression)
TYPE_TO_STRING(template_argument_logical_or_expression)
TYPE_TO_STRING(template_argument_relational_expression)
TYPE_TO_STRING(template_argument_relational_operator)
TYPE_TO_STRING(template_argument_shift_expression)
TYPE_TO_STRING(template_argument_shift_operator)
TYPE_TO_STRING(template_declaration)
TYPE_TO_STRING(template_id)
TYPE_TO_STRING(template_parameter)
TYPE_TO_STRING(template_parameter_list)
TYPE_TO_STRING(template_type_parameter)
TYPE_TO_STRING(template_typename_expression)
TYPE_TO_STRING(throw_expression)
TYPE_TO_STRING(translation_unit)
TYPE_TO_STRING(try_block)
TYPE_TO_STRING(try_block_function_definition)
TYPE_TO_STRING(type_id)
TYPE_TO_STRING(type_id_list)
TYPE_TO_STRING(type_id_new_expression)
TYPE_TO_STRING(type_id_sizeof_expression)
TYPE_TO_STRING(type_id_typeid_expression)
TYPE_TO_STRING(type_parameter)
TYPE_TO_STRING(type_specifier)
TYPE_TO_STRING(type_specifier_seq)
TYPE_TO_STRING(typeid_expression)
TYPE_TO_STRING(typename_elaborated_specifier)
TYPE_TO_STRING(typename_expression)
TYPE_TO_STRING(typename_template_elaborated_specifier)
TYPE_TO_STRING(typename_type_parameter)
TYPE_TO_STRING(unary_expression)
TYPE_TO_STRING(unary_operator)
TYPE_TO_STRING(unary_operator_expression)
TYPE_TO_STRING(unary_sizeof_expression)
TYPE_TO_STRING(universal_character_name)
TYPE_TO_STRING(unqualified_id)
TYPE_TO_STRING(using_declaration)
TYPE_TO_STRING(using_directive)
TYPE_TO_STRING(while_statement)

#undef TYPE_TO_STRING



inline
void
print_syntax_tree(const scalpel::cpp::syntax_tree& tree)
{
	detail::json_writer writer(std::cout);
	print(tree, writer, false);
}



//overload for sequence nodes
template<class SyntaxNode>
struct print_sequence_node_impl
{
	static
	void
	print_node
	(
		const SyntaxNode& node,
		detail::json_writer& writer
	)
	{
		//print the head node
		print(node.head(), writer);

		//print the tail nodes (recursive call)
		print_sequence_node_impl<typename SyntaxNode::tail_sequence_node_t>::print_node(node.tail(), writer);
	}
};

template<>
struct print_sequence_node_impl<syntax_nodes::sequence_node<>>
{
	static
	void
	print_node
	(
		const syntax_nodes::sequence_node<>&,
		detail::json_writer&
	)
	{
		//does nothing
	}
};

template<class SyntaxNode>
void
print
(
	const SyntaxNode& node,
	detail::json_writer& writer,
	const bool print_node_type,
	typename boost::enable_if<syntax_nodes::utility::is_sequence_node<SyntaxNode>>::type* = 0
)
{
	if(print_node_type)
		writer.open_object(type_to_string<SyntaxNode>::value);
	else
		writer.open_object();
	print_sequence_node_impl<SyntaxNode>::print_node(node, writer);
	writer.close_object();
}



//overload for alternative nodes
template<class SyntaxNode>
struct print_alternative_node_impl
{
	static
	void
	print_node
	(
		const SyntaxNode& node,
		detail::json_writer& writer
	)
	{
		typedef typename SyntaxNode::head_node_t head_node_t;
		boost::optional<const head_node_t&> opt_node = scalpel::cpp::syntax_nodes::get<head_node_t>(&node);

		if(opt_node)
			//print the head node
			print(*opt_node, writer);
		else
			//print one of the tail nodes (recursive call)
			print_alternative_node_impl<typename SyntaxNode::tail_alternative_node_t>::print_node(node.tail(), writer);
	}
};

template<>
struct print_alternative_node_impl<syntax_nodes::alternative_node<>>
{
	static
	void
	print_node
	(
		const syntax_nodes::alternative_node<>&,
		detail::json_writer&
	)
	{
		//does nothing
	}
};

template<class SyntaxNode>
void
print
(
	const SyntaxNode& node,
	detail::json_writer& writer,
	const bool print_node_type,
	typename boost::enable_if<syntax_nodes::utility::is_alternative_node<SyntaxNode>>::type* = 0
)
{
	if(print_node_type)
		writer.open_object(type_to_string<SyntaxNode>::value);
	else
		writer.open_object();
	print_alternative_node_impl<SyntaxNode>::print_node(node, writer);
	writer.close_object();
}



//overload for list nodes
template<class SyntaxNode>
void
print
(
	const SyntaxNode& node,
	detail::json_writer& writer,
	typename boost::enable_if<syntax_nodes::utility::is_list_node<SyntaxNode>>::type* = 0
)
{
	writer.open_array(type_to_string<SyntaxNode>::value);
	for(auto i = node.begin(); i != node.end(); ++i) //for each node of the list
		print(*i, writer, false);
	writer.close_array();
}



//overload for optional nodes
template<class SyntaxNode>
void
print
(
	const SyntaxNode& node,
	detail::json_writer& writer,
	typename boost::enable_if<syntax_nodes::utility::is_optional_node<SyntaxNode>>::type* = 0
)
{
	if(node) print(*node, writer);
}



//overload for predefined text nodes
template<class SyntaxNode>
void
print
(
	const SyntaxNode&,
	detail::json_writer& writer,
	typename boost::enable_if<syntax_nodes::utility::is_predefined_text_node<SyntaxNode>>::type* = 0
)
{
	writer.write_key_value_pair("predefined text", SyntaxNode::text);
}



//overload for leaf nodes
template<class SyntaxNode>
void
print
(
	const SyntaxNode& node,
	detail::json_writer& writer,
	typename boost::enable_if<syntax_nodes::utility::is_leaf_node<SyntaxNode>>::type* = 0
)
{
	writer.write_key_value_pair("text", node.value());
}

} //namespace cpp2xml

#endif

