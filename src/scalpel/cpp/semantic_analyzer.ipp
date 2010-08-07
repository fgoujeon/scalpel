/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2010  Florian Goujeon

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

#ifndef SCALPEL_CPP_SEMANTIC_ANALYZER_IPP
#define SCALPEL_CPP_SEMANTIC_ANALYZER_IPP

#include "detail/semantic_analysis/basic_functions.hpp"
#include "detail/semantic_analysis/name_lookup.hpp"
#include <sstream>

namespace scalpel { namespace cpp
{

template<class ParentEntityT>
semantic_analyzer::alternative_visitor<ParentEntityT>::alternative_visitor(semantic_analyzer& analyzer, std::shared_ptr<ParentEntityT> parent_entity):
	analyzer_(analyzer),
	parent_entity_(parent_entity)
{
}

template<class ParentEntityT>
template<class T>
inline
void
semantic_analyzer::alternative_visitor<ParentEntityT>::operator()(const T& syntax_node) const
{
	analyzer_.analyze(syntax_node, parent_entity_);
}



template<class SyntaxNodeT, class ParentEntityT>
void
semantic_analyzer::analyze
(
	const SyntaxNodeT& syntax_node,
	std::shared_ptr<ParentEntityT> parent_entity,
	typename boost::enable_if<syntax_nodes::utility::is_alternative_node<SyntaxNodeT>>::type*
)
{
	alternative_visitor<ParentEntityT> visitor(*this, parent_entity);
	syntax_nodes::apply_visitor(visitor, syntax_node);
}

template<class SyntaxNodeT, class ParentEntityT>
void
semantic_analyzer::analyze
(
	const SyntaxNodeT& syntax_node,
	std::shared_ptr<ParentEntityT> parent_entity,
	typename boost::enable_if<syntax_nodes::utility::is_list_node<SyntaxNodeT>>::type*
)
{
	for(auto i = syntax_node.begin(); i != syntax_node.end(); ++i)
	{
		analyze(i->main_node(), parent_entity);
	}
}



template<class ParentEntityT>
void
semantic_analyzer::analyze(const syntax_nodes::asm_definition&, std::shared_ptr<ParentEntityT>)
{
}

template<class ParentEntityT>
void
semantic_analyzer::analyze(const syntax_nodes::break_statement&, std::shared_ptr<ParentEntityT>)
{
}

template<class ParentEntityT>
void
semantic_analyzer::analyze(const syntax_nodes::case_statement&, std::shared_ptr<ParentEntityT>)
{
}

template<class ParentEntityT>
void
semantic_analyzer::analyze(const syntax_nodes::class_head&, std::shared_ptr<ParentEntityT>)
{
}

template<class ParentEntityT>
void
semantic_analyzer::analyze(const syntax_nodes::class_specifier& class_specifier_node, std::shared_ptr<ParentEntityT> parent_entity)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	std::shared_ptr<class_> new_class = create_class(class_specifier_node);
	parent_entity->add(new_class);
	declarative_region_cursor_.enter_declarative_region(new_class);
	fill_class(new_class, class_specifier_node);
	declarative_region_cursor_.leave_current_declarative_region();
}

template<class ParentEntityT>
void
semantic_analyzer::analyze(const syntax_nodes::classic_labeled_statement&, std::shared_ptr<ParentEntityT>)
{
}

template<class ParentEntityT>
void
semantic_analyzer::analyze(const syntax_nodes::compound_statement& syntax_node, std::shared_ptr<ParentEntityT> parent_entity)
{
}

template<class ParentEntityT>
void
semantic_analyzer::analyze(const syntax_nodes::continue_statement&, std::shared_ptr<ParentEntityT>)
{
}

template<class ParentEntityT>
void
semantic_analyzer::analyze(const syntax_nodes::conversion_function_id&, std::shared_ptr<ParentEntityT>)
{
}

template<class ParentEntityT>
void
semantic_analyzer::analyze(const syntax_nodes::ctor_initializer&, std::shared_ptr<ParentEntityT>)
{
}

template<class ParentEntityT>
void
semantic_analyzer::analyze(const syntax_nodes::cv_qualifier&, std::shared_ptr<ParentEntityT>)
{
}

template<class ParentEntityT>
void
semantic_analyzer::analyze(const syntax_nodes::declarator&, std::shared_ptr<ParentEntityT>)
{
}

template<class ParentEntityT>
void
semantic_analyzer::analyze(const syntax_nodes::default_statement&, std::shared_ptr<ParentEntityT>)
{
}

template<class ParentEntityT>
void
semantic_analyzer::analyze(const syntax_nodes::destructor_name&, std::shared_ptr<ParentEntityT>)
{
}

template<class ParentEntityT>
void
semantic_analyzer::analyze(const syntax_nodes::direct_declarator&, std::shared_ptr<ParentEntityT>)
{
}

template<class ParentEntityT>
void
semantic_analyzer::analyze(const syntax_nodes::direct_declarator_array_part&, std::shared_ptr<ParentEntityT>)
{
}

template<class ParentEntityT>
void
semantic_analyzer::analyze(const syntax_nodes::direct_declarator_function_part&, std::shared_ptr<ParentEntityT>)
{
}

template<class ParentEntityT>
void
semantic_analyzer::analyze(const syntax_nodes::do_while_statement& syntax_node, std::shared_ptr<ParentEntityT> parent_entity)
{
}

template<class ParentEntityT>
void
semantic_analyzer::analyze(const syntax_nodes::elaborated_type_specifier&, std::shared_ptr<ParentEntityT>)
{
}

template<class ParentEntityT>
void
semantic_analyzer::analyze(const syntax_nodes::explicit_instantiation&, std::shared_ptr<ParentEntityT>)
{
}

template<class ParentEntityT>
void
semantic_analyzer::analyze(const syntax_nodes::explicit_specialization&, std::shared_ptr<ParentEntityT>)
{
}

template<class ParentEntityT>
void
semantic_analyzer::analyze(const syntax_nodes::expression_statement&, std::shared_ptr<ParentEntityT>)
{
}

template<class ParentEntityT>
void
semantic_analyzer::analyze(const syntax_nodes::for_statement& syntax_node, std::shared_ptr<ParentEntityT> parent_entity)
{
}

template<class ParentEntityT>
void
semantic_analyzer::analyze(const syntax_nodes::function_definition& function_definition_node, std::shared_ptr<ParentEntityT> parent_entity)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;
	using namespace detail::semantic_analysis;

	auto declarator_node = get_declarator(function_definition_node);

	//
	//get the declarative region of the function
	//
	/*
	std::shared_ptr<named_declarative_region> enclosing_declarative_region;

	auto direct_declarator_node = get_direct_declarator(declarator_node);
	auto first_part_node = get_first_part(direct_declarator_node);
	auto opt_declarator_id_node = get<declarator_id>(&first_part_node);
	if(opt_declarator_id_node)
	{
		auto declarator_id_node = *opt_declarator_id_node;
		if(auto opt_id_expression_node = get<id_expression>(&declarator_id_node))
		{
			auto id_expression_node = *opt_id_expression_node;

			if(auto opt_unqualified_id_node = get<unqualified_id>(&id_expression_node))
			{
				enclosing_declarative_region = declarative_region_cursor_.current_declarative_region();
			}
			else if(auto opt_qualified_id_node = get<qualified_id>(&id_expression_node))
			{
				return;
				auto qualified_id_node = *opt_qualified_id_node;
				//get<qualified_identifier>(a_qualified_id)
				//get<qualified_operator_function_id>(a_qualified_id)
				//get<qualified_template_id>(a_qualified_id)

				if(auto opt_qualified_nested_id_node = get<qualified_nested_id>(&qualified_id_node))
				{
					bool leading_double_colon = has_double_colon(*opt_qualified_nested_id_node);
					auto nested_name_specifier_node = get_nested_name_specifier(*opt_qualified_nested_id_node);

					if(leading_double_colon)
					{
						enclosing_declarative_region = name_lookup::find_declarative_region(declarative_region_cursor_.global_declarative_region_path(), nested_name_specifier_node);
					}
					else
					{
						enclosing_declarative_region = name_lookup::find_declarative_region(declarative_region_cursor_.declarative_region_path(), nested_name_specifier_node);
					}
				}
			}
			else
			{
				assert(false);
			}
		}
	}
	*/

	if(auto opt_decl_specifier_seq_node = get_decl_specifier_seq(function_definition_node))
	{
		auto decl_specifier_seq_node = *opt_decl_specifier_seq_node;
		if(is_simple_function_declaration(declarator_node))
		{
			define_function<simple_function>(decl_specifier_seq_node, declarator_node, parent_entity);
		}
		else if(is_operator_function_declaration(declarator_node))
		{
			define_function<operator_function>(decl_specifier_seq_node, declarator_node, parent_entity);
		}
	}
}

template<class ParentEntityT>
void
semantic_analyzer::analyze(const syntax_nodes::goto_statement&, std::shared_ptr<ParentEntityT>)
{
}

template<class ParentEntityT>
void
semantic_analyzer::analyze(const syntax_nodes::handler& syntax_node, std::shared_ptr<ParentEntityT> parent_entity)
{
}

template<class ParentEntityT>
void
semantic_analyzer::analyze(const syntax_nodes::identifier&, std::shared_ptr<ParentEntityT>)
{
}

template<class ParentEntityT>
void
semantic_analyzer::analyze(const syntax_nodes::if_statement& syntax_node, std::shared_ptr<ParentEntityT> parent_entity)
{
}

template<class ParentEntityT>
void
semantic_analyzer::analyze(const syntax_nodes::init_declarator&, std::shared_ptr<ParentEntityT>)
{
}

template<class ParentEntityT>
void
semantic_analyzer::analyze(const syntax_nodes::linkage_specification&, std::shared_ptr<ParentEntityT>)
{
}

template<class ParentEntityT>
void
semantic_analyzer::analyze(const syntax_nodes::mem_initializer&, std::shared_ptr<ParentEntityT>)
{
}

template<class ParentEntityT>
void
semantic_analyzer::analyze(const syntax_nodes::member_declaration_function_definition&, std::shared_ptr<ParentEntityT>)
{
}

template<class ParentEntityT>
void
semantic_analyzer::analyze(const syntax_nodes::member_declaration_member_declarator_list&, std::shared_ptr<ParentEntityT>)
{
}

template<class ParentEntityT>
void
semantic_analyzer::analyze(const syntax_nodes::member_declaration_unqualified_id&, std::shared_ptr<ParentEntityT>)
{
}

template<class ParentEntityT>
void
semantic_analyzer::analyze(const syntax_nodes::member_declarator_bit_field_member&, std::shared_ptr<ParentEntityT>)
{
}

template<class ParentEntityT>
void
semantic_analyzer::analyze(const syntax_nodes::member_declarator_declarator&, std::shared_ptr<ParentEntityT>)
{
}

template<class ParentEntityT>
void
semantic_analyzer::analyze(const syntax_nodes::member_specification&, std::shared_ptr<ParentEntityT>)
{
}

template<class ParentEntityT>
void
semantic_analyzer::analyze(const syntax_nodes::member_specification_access_specifier&, std::shared_ptr<ParentEntityT>)
{
}

template<class ParentEntityT>
void
semantic_analyzer::analyze(const syntax_nodes::namespace_alias_definition&, std::shared_ptr<ParentEntityT>)
{
}

template<class ParentEntityT>
void
semantic_analyzer::analyze(const syntax_nodes::namespace_definition& syntax_node, std::shared_ptr<ParentEntityT> parent_entity)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	//get the namespace name
	std::string namespace_name;
	const optional_node<identifier>& identifier_node = get_identifier(syntax_node);
	if(identifier_node)
	{
		namespace_name = identifier_node->value();
	}

	//create the namespace entity
	std::shared_ptr<namespace_> new_namespace = std::make_shared<namespace_>(namespace_name);

	//add the namespace to the current declarative region
	parent_entity->add(new_namespace);

	//add the declarations of the namespace definition in the namespace semantic node
	declarative_region_cursor_.enter_declarative_region(new_namespace);
	const optional_node<declaration_seq>& a_declaration_seq = get_declaration_seq(syntax_node);
	if(a_declaration_seq)
	{
		analyze(*a_declaration_seq, new_namespace);
	}
	declarative_region_cursor_.leave_current_declarative_region();
}

template<class ParentEntityT>
void
semantic_analyzer::analyze(const syntax_nodes::nested_identifier_or_template_id&, std::shared_ptr<ParentEntityT>)
{
}

template<class ParentEntityT>
void
semantic_analyzer::analyze(const syntax_nodes::nested_name_specifier&, std::shared_ptr<ParentEntityT>)
{
}

template<class ParentEntityT>
void
semantic_analyzer::analyze(const syntax_nodes::nested_name_specifier_last_part&, std::shared_ptr<ParentEntityT>)
{
}

template<class ParentEntityT>
void
semantic_analyzer::analyze(const syntax_nodes::operator_function_id&, std::shared_ptr<ParentEntityT>)
{
}

template<class ParentEntityT>
void
semantic_analyzer::analyze(const syntax_nodes::parameter_declaration&, std::shared_ptr<ParentEntityT>)
{
}

template<class ParentEntityT>
void
semantic_analyzer::analyze(const syntax_nodes::parameter_declaration_clause&, std::shared_ptr<ParentEntityT>)
{
}

template<class ParentEntityT>
void
semantic_analyzer::analyze(const syntax_nodes::ptr_operator&, std::shared_ptr<ParentEntityT>)
{
}

template<class ParentEntityT>
void
semantic_analyzer::analyze(const syntax_nodes::qualified_identifier&, std::shared_ptr<ParentEntityT>)
{
}

template<class ParentEntityT>
void
semantic_analyzer::analyze(const syntax_nodes::qualified_nested_id&, std::shared_ptr<ParentEntityT>)
{
}

template<class ParentEntityT>
void
semantic_analyzer::analyze(const syntax_nodes::qualified_operator_function_id&, std::shared_ptr<ParentEntityT>)
{
}

template<class ParentEntityT>
void
semantic_analyzer::analyze(const syntax_nodes::qualified_template_id&, std::shared_ptr<ParentEntityT>)
{
}

template<class ParentEntityT>
void
semantic_analyzer::analyze(const syntax_nodes::return_statement&, std::shared_ptr<ParentEntityT>)
{
}

template<class ParentEntityT>
void
semantic_analyzer::analyze(const syntax_nodes::simple_declaration& simple_declaration_node, std::shared_ptr<ParentEntityT> parent_entity)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;
	using namespace detail::semantic_analysis;

	if(is_class_declaration(simple_declaration_node))
	{
		auto opt_decl_specifier_seq_node = get_decl_specifier_seq(simple_declaration_node);
		assert(opt_decl_specifier_seq_node);

		const decl_specifier_seq& decl_specifier_seq_node = *opt_decl_specifier_seq_node;
		assert(decl_specifier_seq_node.size() == 1);

		const decl_specifier& decl_specifier_node = decl_specifier_seq_node.front().main_node();

		auto opt_type_specifier_node = get<type_specifier>(&decl_specifier_node);
		assert(opt_type_specifier_node);

		auto type_specifier_node = *opt_type_specifier_node;

		auto opt_class_specifier_node = get<class_specifier>(&type_specifier_node);
		assert(opt_class_specifier_node);

		analyze(*opt_class_specifier_node, parent_entity);
	}
	else if(is_class_forward_declaration(simple_declaration_node))
	{
		auto opt_decl_specifier_seq_node = get_decl_specifier_seq(simple_declaration_node);
		assert(opt_decl_specifier_seq_node);

		const decl_specifier_seq& decl_specifier_seq_node = *opt_decl_specifier_seq_node;
		assert(decl_specifier_seq_node.size() == 1);

		const decl_specifier& decl_specifier_node = decl_specifier_seq_node.front().main_node();

		auto opt_type_specifier_node = get<type_specifier>(&decl_specifier_node);
		assert(opt_type_specifier_node);

		auto type_specifier_node = *opt_type_specifier_node;

		auto opt_elaborated_type_specifier_node = get<elaborated_type_specifier>(&type_specifier_node);
		assert(opt_elaborated_type_specifier_node);

		auto elaborated_type_specifier_node = *opt_elaborated_type_specifier_node;

		auto opt_class_elaborated_specifier_node = get<class_elaborated_specifier>(&elaborated_type_specifier_node);
		assert(opt_class_elaborated_specifier_node);

		const identifier_or_template_id& identifier_or_template_id_node = get_identifier_or_template_id(*opt_class_elaborated_specifier_node);

		auto opt_identifier_node = get<identifier>(&identifier_or_template_id_node);
		assert(opt_identifier_node);

		const std::string& class_name = opt_identifier_node->value();
		parent_entity->add(std::make_shared<class_>(class_name));
	}
	else if(is_variable_declaration(simple_declaration_node))
	{
		auto opt_decl_specifier_seq_node = get_decl_specifier_seq(simple_declaration_node);
		auto opt_init_declarator_list_node = get_init_declarator_list(simple_declaration_node);
		assert(opt_decl_specifier_seq_node);
		assert(opt_init_declarator_list_node);

		const decl_specifier_seq& decl_specifier_seq_node = *opt_decl_specifier_seq_node;

		auto init_declarator_list_node = *opt_init_declarator_list_node;

		std::vector<std::shared_ptr<variable>> variables = create_variables(decl_specifier_seq_node, init_declarator_list_node);
		//for each variable
		for
		(
			auto i = variables.begin();
			i != variables.end();
			++i
		)
		{
			parent_entity->add(*i);
		}
	}
	else if(is_simple_function_declaration(simple_declaration_node))
	{
		auto opt_decl_specifier_seq_node = get_decl_specifier_seq(simple_declaration_node);
		auto opt_init_declarator_list_node = get_init_declarator_list(simple_declaration_node);
		assert(opt_decl_specifier_seq_node);
		assert(opt_init_declarator_list_node);

		auto init_declarator_list_node = *opt_init_declarator_list_node;
		assert(init_declarator_list_node.size() == 1);

		auto decl_specifier_seq_node = *opt_decl_specifier_seq_node;
		auto declarator_node = get_declarator(init_declarator_list_node.front().main_node());
		parent_entity->add(create_simple_function(decl_specifier_seq_node, declarator_node));
	}
	else if(is_operator_function_declaration(simple_declaration_node))
	{
		auto opt_decl_specifier_seq_node = get_decl_specifier_seq(simple_declaration_node);
		auto opt_init_declarator_list_node = get_init_declarator_list(simple_declaration_node);
		assert(opt_decl_specifier_seq_node);
		assert(opt_init_declarator_list_node);

		auto init_declarator_list_node = *opt_init_declarator_list_node;
		assert(init_declarator_list_node.size() == 1);

		auto decl_specifier_seq_node = *opt_decl_specifier_seq_node;
		auto declarator_node = get_declarator(init_declarator_list_node.front().main_node());
		parent_entity->add(create_operator_function(decl_specifier_seq_node, declarator_node));
	}
}

template<class ParentEntityT>
void
semantic_analyzer::analyze(const syntax_nodes::simple_template_type_specifier&, std::shared_ptr<ParentEntityT>)
{
}

template<class ParentEntityT>
void
semantic_analyzer::analyze(const syntax_nodes::switch_statement&, std::shared_ptr<ParentEntityT>)
{
}

template<class ParentEntityT>
void
semantic_analyzer::analyze(const syntax_nodes::template_declaration&, std::shared_ptr<ParentEntityT>)
{
}

template<class ParentEntityT>
void
semantic_analyzer::analyze(const syntax_nodes::template_id&, std::shared_ptr<ParentEntityT>)
{
}

template<class ParentEntityT>
void
semantic_analyzer::analyze(const syntax_nodes::try_block& syntax_node, std::shared_ptr<ParentEntityT> parent_entity)
{
}

template<class ParentEntityT>
void
semantic_analyzer::analyze(const syntax_nodes::type_id_sizeof_expression&, std::shared_ptr<ParentEntityT>)
{
}

template<class ParentEntityT>
void
semantic_analyzer::analyze(const syntax_nodes::unary_sizeof_expression&, std::shared_ptr<ParentEntityT>)
{
}

template<class ParentEntityT>
void
semantic_analyzer::analyze(const syntax_nodes::using_declaration&, std::shared_ptr<ParentEntityT>)
{
}

template<class ParentEntityT>
void
semantic_analyzer::analyze(const syntax_nodes::using_directive&, std::shared_ptr<ParentEntityT>)
{
}

template<class ParentEntityT>
void
semantic_analyzer::analyze(const syntax_nodes::while_statement&, std::shared_ptr<ParentEntityT>)
{
}

template<class FunctionT, class ParentEntityT>
void
semantic_analyzer::define_function
(
	const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node,
	const syntax_nodes::declarator& declarator_node,
	std::shared_ptr<ParentEntityT> parent_entity
)
{
	using namespace detail::semantic_analysis;

	//get the function name
	std::string function_name = get_name(declarator_node);

	//create a FunctionT object
	std::shared_ptr<FunctionT> new_function = create_function<FunctionT>(decl_specifier_seq_node, declarator_node);

	//find the corresponding function semantic entity (must exist if the function has already been declared)
	std::shared_ptr<FunctionT> function_entity;
	std::shared_ptr<semantic_entities::named_entity> found_entity = name_lookup::find_name(declarative_region_cursor_.declarative_region_path(), function_name);
	std::shared_ptr<FunctionT> possible_function_entity;
	if
	(
		found_entity &&
		(possible_function_entity = std::dynamic_pointer_cast<FunctionT>(found_entity)) &&
		possible_function_entity->has_same_signature(*new_function)
	)
	{
		function_entity = possible_function_entity;
	}

	//if the function hasn't been declared, this definition serves as a declaration
	if(!function_entity)
	{
		function_entity = new_function;
		parent_entity->add(new_function);
	}

	assert(function_entity);

	//check whether the function is undefined
	if(function_entity->defined())
	{
		std::ostringstream oss;
		oss << "Redefinition of " << function_name;
		throw std::runtime_error(oss.str().c_str());
	}

	function_entity->defined(true);
}

}} //namespace scalpel::cpp

#endif

