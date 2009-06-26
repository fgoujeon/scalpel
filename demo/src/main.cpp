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

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <scalpel/cpp/preprocessor.hpp>
#include <scalpel/cpp/syntax_analyzer.hpp>

std::string
indent(unsigned int level)
{
	std::ostringstream oss;
	for(unsigned int j = 0; j < level; ++j)
		oss << " ";
	return oss.str();
}

std::string
printable_node_value(const std::string& value)
{
	std::string new_value;
	for(unsigned int i = 0; i < value.size(); ++i)
	{
		switch(value.at(i))
		{
			case '\n':
				new_value += "\\n";
				break;
			case '\t':
				new_value += "\\t";
				break;
			case ' ':
				new_value += "\\s";
				break;
			default:
				new_value += value.at(i);
		}
	}
	return new_value;
}

#define AAA(type)\
	if(dynamic_cast<const type*>(&node)) return #type;\
	if(dynamic_cast<const optional_node<type>*>(&node)) return "optional " #type;

std::string
get_node_type(const scalpel::cpp::syntax_nodes::node& node)
{
	using namespace scalpel::cpp::syntax_nodes;

	AAA(abstract_declarator)
	AAA(access_specifier)
	AAA(array_delete_expression)
	AAA(array_operator)
	AAA(arrow_id_expression)
	AAA(arrow_pseudo_destructor_name)
	AAA(asm_definition)
	AAA(assignment_expression)
	AAA(assignment_expression_condition)
	AAA(assignment_operator)
	AAA(base_clause)
	AAA(base_specifier)
	AAA(base_specifier_list)
	AAA(block_declaration)
	AAA(boolean_literal)
	AAA(bracketed_abstract_declarator)
	AAA(bracketed_declarator)
	AAA(break_statement)
	AAA(built_in_type_specifier)
	AAA(case_statement)
	AAA(cast_expression)
	AAA(character_literal)
	AAA(class_elaborated_specifier)
	AAA(class_head)
	AAA(class_key)
	AAA(class_specifier)
	AAA(class_type_parameter)
	AAA(classic_labeled_statement)
	AAA(compound_statement)
	AAA(condition)
	AAA(conditional_expression)
	AAA(const_cast_expression)
	AAA(constant_initializer)
	AAA(continue_statement)
	AAA(conversion_function_id)
	AAA(ctor_initializer)
	AAA(cv_qualifier)
	AAA(cv_qualifier_seq)
	AAA(decl_specifier)
	AAA(decl_specifier_seq)
	AAA(declaration)
	AAA(declaration_linkage_specification)
	AAA(declaration_seq)
	AAA(declaration_seq_linkage_specification)
	AAA(declarator)
	AAA(declarator_id)
	AAA(default_statement)
	AAA(delete_array_operator)
	AAA(delete_expression)
	AAA(destructor_name)
	AAA(direct_abstract_declarator)
	AAA(direct_declarator)
	AAA(direct_new_declarator)
	AAA(do_while_statement)
	AAA(dot_id_expression)
	AAA(dot_pseudo_destructor_name)
	AAA(dynamic_cast_expression)
	AAA(elaborated_type_specifier)
	AAA(enum_elaborated_specifier)
	AAA(enum_specifier)
	AAA(enumerator_definition)
	AAA(enumerator_list)
	AAA(equal_initializer)
	AAA(exception_abstract_declarator)
	AAA(exception_declaration)
	AAA(exception_declarator)
	AAA(exception_specification)
	AAA(explicit_instantiation)
	AAA(explicit_specialization)
	AAA(expression)
	AAA(expression_statement)
	AAA(floating_literal)
	AAA(for_init_statement)
	AAA(for_statement)
	AAA(function_definition)
	AAA(function_specifier)
	AAA(function_try_block)
	AAA(goto_statement)
	AAA(handler)
	AAA(handler_seq)
	AAA(id_expression)
	AAA(identifier)
	AAA(identifier_or_template_id)
	AAA(if_statement)
	AAA(init_declarator)
	AAA(init_declarator_list)
	AAA(initializer)
	AAA(initializer_clause)
	AAA(initializer_list)
	AAA(initializer_list_initializer_clause)
	AAA(integer_literal)
	AAA(iteration_statement)
	AAA(jump_statement)
	AAA(labeled_statement)
	AAA(linkage_specification)
	AAA(literal)
	AAA(mem_initializer)
	AAA(mem_initializer_id)
	AAA(mem_initializer_list)
	AAA(member_declaration)
	AAA(member_declaration_function_definition)
	AAA(member_declaration_member_declarator_list)
	AAA(member_declaration_unqualified_id)
	AAA(member_declarator)
	AAA(member_declarator_bit_field_member)
	AAA(member_declarator_declarator)
	AAA(member_declarator_list)
	AAA(member_specification)
	AAA(member_specification_access_specifier)
	AAA(member_specification_part)
	AAA(namespace_alias_definition)
	AAA(namespace_definition)
	AAA(nested_identifier_or_template_id)
	AAA(nested_name_specifier)
	AAA(new_array_operator)
	AAA(new_declarator)
	AAA(new_expression)
	AAA(new_initializer)
	AAA(new_type_id)
	AAA(new_type_id_new_expression)
	AAA(operator_)
	AAA(operator_function_id)
	AAA(parameter_declaration)
	AAA(parameter_declaration_clause)
	AAA(parameter_declaration_list)
	AAA(postfix_expression)
	AAA(primary_expression)
	AAA(ptr_operator)
	AAA(ptr_operator_seq)
	AAA(ptr_ptr_operator)
	AAA(pure_specifier)
	AAA(qualified_id)
	AAA(qualified_identifier)
	AAA(qualified_namespace_specifier)
	AAA(qualified_nested_id)
	AAA(qualified_operator_function_id)
	AAA(qualified_template_id)
	AAA(ref_ptr_operator)
	AAA(reinterpret_cast_expression)
	AAA(return_statement)
	AAA(round_bracketed_expression)
	AAA(round_bracketed_optional_expression)
	AAA(selection_statement)
	AAA(simple_declaration)
	AAA(simple_delete_expression)
	AAA(simple_function_definition)
	AAA(simple_operator)
	AAA(simple_template_type_specifier)
	AAA(simple_type_specifier)
	AAA(simple_type_specifier_postfix_expression)
	AAA(square_bracketed_expression)
	AAA(statement)
	AAA(statement_seq)
	AAA(static_cast_expression)
	AAA(storage_class_specifier)
	AAA(string_literal)
	AAA(switch_statement)
	AAA(template_argument)
	AAA(template_argument_assignment_expression)
	AAA(template_argument_conditional_expression)
	AAA(template_argument_list)
	AAA(template_declaration)
	AAA(template_id)
	AAA(template_parameter)
	AAA(template_parameter_list)
	AAA(template_type_parameter)
	AAA(template_typename_expression)
	AAA(throw_expression)
	AAA(translation_unit)
	AAA(try_block)
	AAA(try_block_function_definition)
	AAA(type_id)
	AAA(type_id_list)
	AAA(type_id_new_expression)
	AAA(type_id_sizeof_expression)
	AAA(type_id_typeid_expression)
	AAA(type_parameter)
	AAA(type_specifier)
	AAA(type_specifier_seq)
	AAA(typeid_expression)
	AAA(typename_elaborated_specifier)
	AAA(typename_expression)
	AAA(typename_template_elaborated_specifier)
	AAA(typename_type_parameter)
	AAA(typeof_expression)
	AAA(unary_expression)
	AAA(unary_operator)
	AAA(unary_operator_unary_expression)
	AAA(unary_sizeof_expression)
	AAA(unqualified_id)
	AAA(using_declaration)
	AAA(using_directive)
	AAA(while_statement)

	AAA(leaf_node)

	return "???";
}

bool
is_alive(const scalpel::cpp::syntax_nodes::node& node)
{
	return node.value() != "";
}

unsigned int
get_alive_node_count(const scalpel::cpp::syntax_nodes::node& node)
{
	unsigned int count = 0;
	for(auto i = node.children().begin(); i != node.children().end(); ++i)
	{
		const scalpel::cpp::syntax_nodes::node& child_node = *i;
		if(is_alive(child_node))
			++count;
	}
	return count;
}

void
print_node(const scalpel::cpp::syntax_nodes::node& node, const bool abstract = false, const unsigned int indent_level = 0)
{
	if(is_alive(node))
	{
		if(node.children().empty())
		{
			std::cout << indent(indent_level) << "[" << get_node_type(node) << "] ";
			std::cout << printable_node_value(node.value());
			std::cout << "\n";
		}
		else
		{
			unsigned int alive_node_count = get_alive_node_count(node);
			switch(alive_node_count)
			{
				case 0:
					break;
				case 1:
					if(abstract)
					{
						for(auto i = node.children().begin(); i != node.children().end(); ++i)
						{
							const scalpel::cpp::syntax_nodes::node& child_node = *i;
							print_node(child_node, abstract, indent_level);
						}
						break;
					}
				default:
					std::cout << indent(indent_level) << "[" << get_node_type(node) << " begin]\n";
					for(auto i = node.children().begin(); i != node.children().end(); ++i)
					{
						const scalpel::cpp::syntax_nodes::node& child_node = *i;
						print_node(child_node, abstract, indent_level + 1);
					}
					std::cout << indent(indent_level) << "[" << get_node_type(node) << " end]\n";
			}
		}
	}
}

int
main(int argc, char** argv)
{
	scalpel::cpp::preprocessor preprocessor;
	scalpel::cpp::syntax_analyzer syntax_analyzer;

	std::string filename = argv[1];

	//open file
	std::ifstream file(filename);
	if(!file)
	{
		std::cout << filename << " doesn't exits.";
		return 1;
	}

	//read file
	std::ostringstream buffer;
	buffer << file.rdbuf();

	//close file
	file.close();

	std::cout << "Analyzing " << filename << "...\n";

	//preprocessing
	std::vector<std::string> include_paths =
	{
		"/usr/include",
		"/usr/include/c++/4.4.0",
		"/usr/include/c++/4.4.0/i686-pc-linux-gnu",
		"/usr/include/c++/4.4.0/parallel",
		"/usr/include/linux",
		"/usr/lib/gcc/i686-pc-linux-gnu/4.4.0/include"
	};
	std::string preprocessed_code = preprocessor(buffer.str(), include_paths);

	//syntax analysis
	scalpel::cpp::syntax_tree tree = syntax_analyzer(preprocessed_code);

	//print abstract syntax tree
	std::cout << "Abstract syntax tree:\n";
	print_node(tree, true);

	return 0;
}
