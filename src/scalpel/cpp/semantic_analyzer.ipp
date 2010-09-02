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

template<class DeclarativeRegionT>
semantic_analyzer::alternative_visitor<DeclarativeRegionT>::alternative_visitor(semantic_analyzer& analyzer, std::shared_ptr<DeclarativeRegionT> current_declarative_region):
	analyzer_(analyzer),
	parent_entity_(current_declarative_region)
{
}

template<class DeclarativeRegionT>
template<class T>
inline
void
semantic_analyzer::alternative_visitor<DeclarativeRegionT>::operator()(const T& syntax_node) const
{
	analyzer_.analyze(syntax_node, parent_entity_);
}



template<class SyntaxNodeT, class DeclarativeRegionT>
void
semantic_analyzer::analyze
(
	const SyntaxNodeT& syntax_node,
	std::shared_ptr<DeclarativeRegionT> current_declarative_region,
	typename boost::enable_if<syntax_nodes::utility::is_alternative_node<SyntaxNodeT>>::type*
)
{
	alternative_visitor<DeclarativeRegionT> visitor(*this, current_declarative_region);
	syntax_nodes::apply_visitor(visitor, syntax_node);
}

template<class SyntaxNodeT, class DeclarativeRegionT>
void
semantic_analyzer::analyze
(
	const SyntaxNodeT& syntax_node,
	std::shared_ptr<DeclarativeRegionT> current_declarative_region,
	typename boost::enable_if<syntax_nodes::utility::is_list_node<SyntaxNodeT>>::type*
)
{
	for(auto i = syntax_node.begin(); i != syntax_node.end(); ++i)
	{
		analyze(i->main_node(), current_declarative_region);
	}
}



template<class DeclarativeRegionT>
void
semantic_analyzer::analyze(const syntax_nodes::asm_definition&, std::shared_ptr<DeclarativeRegionT>)
{
}

template<class DeclarativeRegionT>
void
semantic_analyzer::analyze(const syntax_nodes::break_statement&, std::shared_ptr<DeclarativeRegionT>)
{
}

template<class DeclarativeRegionT>
void
semantic_analyzer::analyze(const syntax_nodes::case_statement&, std::shared_ptr<DeclarativeRegionT>)
{
}

template<class DeclarativeRegionT>
void
semantic_analyzer::analyze(const syntax_nodes::class_head&, std::shared_ptr<DeclarativeRegionT>)
{
}

template<class DeclarativeRegionT>
void
semantic_analyzer::analyze(const syntax_nodes::class_specifier& class_specifier_node, std::shared_ptr<DeclarativeRegionT> current_declarative_region)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	std::shared_ptr<class_> new_class = create_class(class_specifier_node);
	current_declarative_region->add_member(new_class);
	fill_class(new_class, class_specifier_node);
}

template<class DeclarativeRegionT>
void
semantic_analyzer::analyze(const syntax_nodes::classic_labeled_statement&, std::shared_ptr<DeclarativeRegionT>)
{
}

template<class DeclarativeRegionT>
void
semantic_analyzer::analyze(const syntax_nodes::compound_statement& syntax_node, std::shared_ptr<DeclarativeRegionT> current_declarative_region)
{
}

template<class DeclarativeRegionT>
void
semantic_analyzer::analyze(const syntax_nodes::continue_statement&, std::shared_ptr<DeclarativeRegionT>)
{
}

template<class DeclarativeRegionT>
void
semantic_analyzer::analyze(const syntax_nodes::conversion_function_id&, std::shared_ptr<DeclarativeRegionT>)
{
}

template<class DeclarativeRegionT>
void
semantic_analyzer::analyze(const syntax_nodes::ctor_initializer&, std::shared_ptr<DeclarativeRegionT>)
{
}

template<class DeclarativeRegionT>
void
semantic_analyzer::analyze(const syntax_nodes::cv_qualifier&, std::shared_ptr<DeclarativeRegionT>)
{
}

template<class DeclarativeRegionT>
void
semantic_analyzer::analyze(const syntax_nodes::declarator&, std::shared_ptr<DeclarativeRegionT>)
{
}

template<class DeclarativeRegionT>
void
semantic_analyzer::analyze(const syntax_nodes::default_statement&, std::shared_ptr<DeclarativeRegionT>)
{
}

template<class DeclarativeRegionT>
void
semantic_analyzer::analyze(const syntax_nodes::destructor_name&, std::shared_ptr<DeclarativeRegionT>)
{
}

template<class DeclarativeRegionT>
void
semantic_analyzer::analyze(const syntax_nodes::direct_declarator&, std::shared_ptr<DeclarativeRegionT>)
{
}

template<class DeclarativeRegionT>
void
semantic_analyzer::analyze(const syntax_nodes::direct_declarator_array_part&, std::shared_ptr<DeclarativeRegionT>)
{
}

template<class DeclarativeRegionT>
void
semantic_analyzer::analyze(const syntax_nodes::direct_declarator_function_part&, std::shared_ptr<DeclarativeRegionT>)
{
}

template<class DeclarativeRegionT>
void
semantic_analyzer::analyze(const syntax_nodes::do_while_statement& syntax_node, std::shared_ptr<DeclarativeRegionT> current_declarative_region)
{
}

template<class DeclarativeRegionT>
void
semantic_analyzer::analyze(const syntax_nodes::elaborated_type_specifier&, std::shared_ptr<DeclarativeRegionT>)
{
}

template<class DeclarativeRegionT>
void
semantic_analyzer::analyze(const syntax_nodes::explicit_instantiation&, std::shared_ptr<DeclarativeRegionT>)
{
}

template<class DeclarativeRegionT>
void
semantic_analyzer::analyze(const syntax_nodes::explicit_specialization&, std::shared_ptr<DeclarativeRegionT>)
{
}

template<class DeclarativeRegionT>
void
semantic_analyzer::analyze(const syntax_nodes::expression_statement&, std::shared_ptr<DeclarativeRegionT>)
{
}

template<class DeclarativeRegionT>
void
semantic_analyzer::analyze(const syntax_nodes::for_statement& syntax_node, std::shared_ptr<DeclarativeRegionT> current_declarative_region)
{
}

template<class DeclarativeRegionT>
void
semantic_analyzer::analyze(const syntax_nodes::function_definition& function_definition_node, std::shared_ptr<DeclarativeRegionT> current_declarative_region)
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
			define_simple_function(decl_specifier_seq_node, declarator_node, current_declarative_region);
		}
		else if(is_operator_function_declaration(declarator_node))
		{
			//TODO define_function<operator_function>(decl_specifier_seq_node, declarator_node, current_declarative_region);
		}
	}
}

template<class DeclarativeRegionT>
void
semantic_analyzer::analyze(const syntax_nodes::goto_statement&, std::shared_ptr<DeclarativeRegionT>)
{
}

template<class DeclarativeRegionT>
void
semantic_analyzer::analyze(const syntax_nodes::handler& syntax_node, std::shared_ptr<DeclarativeRegionT> current_declarative_region)
{
}

template<class DeclarativeRegionT>
void
semantic_analyzer::analyze(const syntax_nodes::identifier&, std::shared_ptr<DeclarativeRegionT>)
{
}

template<class DeclarativeRegionT>
void
semantic_analyzer::analyze(const syntax_nodes::if_statement& syntax_node, std::shared_ptr<DeclarativeRegionT> current_declarative_region)
{
}

template<class DeclarativeRegionT>
void
semantic_analyzer::analyze(const syntax_nodes::init_declarator&, std::shared_ptr<DeclarativeRegionT>)
{
}

template<class DeclarativeRegionT>
void
semantic_analyzer::analyze(const syntax_nodes::linkage_specification&, std::shared_ptr<DeclarativeRegionT>)
{
}

template<class DeclarativeRegionT>
void
semantic_analyzer::analyze(const syntax_nodes::mem_initializer&, std::shared_ptr<DeclarativeRegionT>)
{
}

template<class DeclarativeRegionT>
void
semantic_analyzer::analyze(const syntax_nodes::member_declaration_function_definition&, std::shared_ptr<DeclarativeRegionT>)
{
}

template<class DeclarativeRegionT>
void
semantic_analyzer::analyze(const syntax_nodes::member_declaration_member_declarator_list&, std::shared_ptr<DeclarativeRegionT>)
{
}

template<class DeclarativeRegionT>
void
semantic_analyzer::analyze(const syntax_nodes::member_declaration_unqualified_id&, std::shared_ptr<DeclarativeRegionT>)
{
}

template<class DeclarativeRegionT>
void
semantic_analyzer::analyze(const syntax_nodes::member_declarator_bit_field_member&, std::shared_ptr<DeclarativeRegionT>)
{
}

template<class DeclarativeRegionT>
void
semantic_analyzer::analyze(const syntax_nodes::member_declarator_declarator&, std::shared_ptr<DeclarativeRegionT>)
{
}

template<class DeclarativeRegionT>
void
semantic_analyzer::analyze(const syntax_nodes::member_specification&, std::shared_ptr<DeclarativeRegionT>)
{
}

template<class DeclarativeRegionT>
void
semantic_analyzer::analyze(const syntax_nodes::member_specification_access_specifier&, std::shared_ptr<DeclarativeRegionT>)
{
}

template<class DeclarativeRegionT>
void
semantic_analyzer::analyze(const syntax_nodes::namespace_alias_definition&, std::shared_ptr<DeclarativeRegionT>)
{
}

template<class DeclarativeRegionT>
void
semantic_analyzer::analyze(const syntax_nodes::namespace_definition& syntax_node, std::shared_ptr<DeclarativeRegionT> current_declarative_region)
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
	std::shared_ptr<namespace_> new_namespace = namespace_::make_shared(namespace_name);

	//add_member the namespace to the current declarative region
	current_declarative_region->add_member(new_namespace);

	//add_member the declarations of the namespace definition in the namespace semantic node
	const optional_node<declaration_seq>& a_declaration_seq = get_declaration_seq(syntax_node);
	if(a_declaration_seq)
	{
		analyze(*a_declaration_seq, new_namespace);
	}
}

template<class DeclarativeRegionT>
void
semantic_analyzer::analyze(const syntax_nodes::nested_identifier_or_template_id&, std::shared_ptr<DeclarativeRegionT>)
{
}

template<class DeclarativeRegionT>
void
semantic_analyzer::analyze(const syntax_nodes::nested_name_specifier&, std::shared_ptr<DeclarativeRegionT>)
{
}

template<class DeclarativeRegionT>
void
semantic_analyzer::analyze(const syntax_nodes::nested_name_specifier_last_part&, std::shared_ptr<DeclarativeRegionT>)
{
}

template<class DeclarativeRegionT>
void
semantic_analyzer::analyze(const syntax_nodes::operator_function_id&, std::shared_ptr<DeclarativeRegionT>)
{
}

template<class DeclarativeRegionT>
void
semantic_analyzer::analyze(const syntax_nodes::parameter_declaration&, std::shared_ptr<DeclarativeRegionT>)
{
}

template<class DeclarativeRegionT>
void
semantic_analyzer::analyze(const syntax_nodes::parameter_declaration_clause&, std::shared_ptr<DeclarativeRegionT>)
{
}

template<class DeclarativeRegionT>
void
semantic_analyzer::analyze(const syntax_nodes::ptr_operator&, std::shared_ptr<DeclarativeRegionT>)
{
}

template<class DeclarativeRegionT>
void
semantic_analyzer::analyze(const syntax_nodes::qualified_identifier&, std::shared_ptr<DeclarativeRegionT>)
{
}

template<class DeclarativeRegionT>
void
semantic_analyzer::analyze(const syntax_nodes::qualified_nested_id&, std::shared_ptr<DeclarativeRegionT>)
{
}

template<class DeclarativeRegionT>
void
semantic_analyzer::analyze(const syntax_nodes::qualified_operator_function_id&, std::shared_ptr<DeclarativeRegionT>)
{
}

template<class DeclarativeRegionT>
void
semantic_analyzer::analyze(const syntax_nodes::qualified_template_id&, std::shared_ptr<DeclarativeRegionT>)
{
}

template<class DeclarativeRegionT>
void
semantic_analyzer::analyze(const syntax_nodes::return_statement&, std::shared_ptr<DeclarativeRegionT>)
{
}

template<class DeclarativeRegionT>
void
semantic_analyzer::analyze(const syntax_nodes::simple_declaration& simple_declaration_node, std::shared_ptr<DeclarativeRegionT> current_declarative_region)
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

		analyze(*opt_class_specifier_node, current_declarative_region);
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
		current_declarative_region->add_member(class_::make_shared(class_name));
	}
	else if(is_variable_declaration(simple_declaration_node))
	{
		auto opt_decl_specifier_seq_node = get_decl_specifier_seq(simple_declaration_node);
		auto opt_init_declarator_list_node = get_init_declarator_list(simple_declaration_node);
		assert(opt_decl_specifier_seq_node);
		assert(opt_init_declarator_list_node);

		const decl_specifier_seq& decl_specifier_seq_node = *opt_decl_specifier_seq_node;

		auto init_declarator_list_node = *opt_init_declarator_list_node;

		std::vector<std::shared_ptr<variable>> variables = create_variables(decl_specifier_seq_node, init_declarator_list_node, current_declarative_region);
		//for each variable
		for
		(
			auto i = variables.begin();
			i != variables.end();
			++i
		)
		{
			current_declarative_region->add_member(*i);
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
		current_declarative_region->add_member(create_simple_function(decl_specifier_seq_node, declarator_node, current_declarative_region));
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
		current_declarative_region->add_member(create_operator_function(decl_specifier_seq_node, declarator_node, current_declarative_region));
	}
}

template<class DeclarativeRegionT>
void
semantic_analyzer::analyze(const syntax_nodes::simple_template_type_specifier&, std::shared_ptr<DeclarativeRegionT>)
{
}

template<class DeclarativeRegionT>
void
semantic_analyzer::analyze(const syntax_nodes::switch_statement&, std::shared_ptr<DeclarativeRegionT>)
{
}

template<class DeclarativeRegionT>
void
semantic_analyzer::analyze(const syntax_nodes::template_declaration&, std::shared_ptr<DeclarativeRegionT>)
{
}

template<class DeclarativeRegionT>
void
semantic_analyzer::analyze(const syntax_nodes::template_id&, std::shared_ptr<DeclarativeRegionT>)
{
}

template<class DeclarativeRegionT>
void
semantic_analyzer::analyze(const syntax_nodes::try_block& syntax_node, std::shared_ptr<DeclarativeRegionT> current_declarative_region)
{
}

template<class DeclarativeRegionT>
void
semantic_analyzer::analyze(const syntax_nodes::type_id_sizeof_expression&, std::shared_ptr<DeclarativeRegionT>)
{
}

template<class DeclarativeRegionT>
void
semantic_analyzer::analyze(const syntax_nodes::unary_sizeof_expression&, std::shared_ptr<DeclarativeRegionT>)
{
}

template<class DeclarativeRegionT>
void
semantic_analyzer::analyze(const syntax_nodes::using_declaration&, std::shared_ptr<DeclarativeRegionT>)
{
}

template<class DeclarativeRegionT>
void
semantic_analyzer::analyze(const syntax_nodes::using_directive&, std::shared_ptr<DeclarativeRegionT>)
{
}

template<class DeclarativeRegionT>
void
semantic_analyzer::analyze(const syntax_nodes::while_statement&, std::shared_ptr<DeclarativeRegionT>)
{
}

template<class DeclarativeRegionT>
void
semantic_analyzer::define_simple_function
(
	const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node,
	const syntax_nodes::declarator& declarator_node,
	std::shared_ptr<DeclarativeRegionT> current_declarative_region
)
{
	using namespace detail::semantic_analysis;

	//get the function name
	syntax_nodes::identifier function_name = get_identifier(declarator_node);

	//create a simple_function object
	std::shared_ptr<semantic_entities::simple_function> new_function =
		create_simple_function(decl_specifier_seq_node, declarator_node, current_declarative_region)
	;

	//find a matching simple_function semantic entity (must exist if the function has already been declared)
	std::shared_ptr<semantic_entities::simple_function> function_entity;
	{
		std::shared_ptr<semantic_entities::simple_function> found_function =
			name_lookup::find<semantic_entities::simple_function, false, true>(function_name, current_declarative_region)
		;
		if
		(
			found_function &&
			found_function->has_same_signature(*new_function)
		)
		{
			function_entity = found_function;
		}
	}

	//if the function hasn't been declared, this definition serves as a declaration
	if(!function_entity)
	{
		function_entity = new_function;
		current_declarative_region->add_member(new_function);
	}

	assert(function_entity);

	//check whether the function is undefined
	if(function_entity->defined())
	{
		std::ostringstream oss;
		oss << "Redefinition of " << function_name.value();
		throw std::runtime_error(oss.str().c_str());
	}

	//TODO define the function
	function_entity->body(std::make_shared<semantic_entities::statement_block>());
}

template<class DeclarativeRegionT>
std::shared_ptr<semantic_entities::simple_function>
semantic_analyzer::create_simple_function
(
	const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node,
	const syntax_nodes::declarator& declarator_node,
	std::shared_ptr<DeclarativeRegionT> current_declarative_region
)
{
	return semantic_entities::simple_function::make_shared
	(
		detail::semantic_analysis::get_identifier(declarator_node).value(),
		create_type(decl_specifier_seq_node, declarator_node, current_declarative_region),
		create_parameters(declarator_node, current_declarative_region),
		detail::semantic_analysis::has_inline_specifier(decl_specifier_seq_node),
		detail::semantic_analysis::has_static_specifier(decl_specifier_seq_node)
	);
}

template<class DeclarativeRegionT>
std::shared_ptr<semantic_entities::operator_function>
semantic_analyzer::create_operator_function
(
	const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node,
	const syntax_nodes::declarator& declarator_node,
	std::shared_ptr<DeclarativeRegionT> current_declarative_region
)
{
	//
	//get the overloaded operator
	//
	semantic_entities::operator_ op = semantic_entities::operator_::AMPERSAND;

	auto direct_declarator_node = get_direct_declarator(declarator_node);
	auto direct_declarator_node_first_part_node = get_first_part(direct_declarator_node);
	auto opt_declarator_id_node = syntax_nodes::get<syntax_nodes::declarator_id>(&direct_declarator_node_first_part_node);
	assert(opt_declarator_id_node);
	auto declarator_id_node = *opt_declarator_id_node;
	auto opt_id_expression_node = syntax_nodes::get<syntax_nodes::id_expression>(&declarator_id_node);
	assert(opt_id_expression_node);
	auto id_expression_node = *opt_id_expression_node;
	auto opt_unqualified_id_node = syntax_nodes::get<syntax_nodes::unqualified_id>(&id_expression_node);
	assert(opt_unqualified_id_node);
	auto unqualified_id_node = *opt_unqualified_id_node;
	auto opt_operator_function_id_node = syntax_nodes::get<syntax_nodes::operator_function_id>(&unqualified_id_node);
	assert(opt_operator_function_id_node);
	auto operator_function_id_node = *opt_operator_function_id_node;
	auto operator_node = get_operator(operator_function_id_node);

	if(auto opt_simple_operator_node = syntax_nodes::get<syntax_nodes::simple_operator>(&operator_node))
	{
		auto simple_operator_node = *opt_simple_operator_node;

		if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::new_>>(&simple_operator_node))
			op = semantic_entities::operator_::NEW;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::delete_>>(&simple_operator_node))
			op = semantic_entities::operator_::DELETE;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::double_right_angle_bracket_equal>>(&simple_operator_node))
			op = semantic_entities::operator_::DOUBLE_RIGHT_ANGLE_BRACKET_EQUAL;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::double_left_angle_bracket_equal>>(&simple_operator_node))
			op = semantic_entities::operator_::DOUBLE_LEFT_ANGLE_BRACKET_EQUAL;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::arrow_asterisk>>(&simple_operator_node))
			op = semantic_entities::operator_::ARROW_ASTERISK;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::plus_equal>>(&simple_operator_node))
			op = semantic_entities::operator_::PLUS_EQUAL;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::minus_equal>>(&simple_operator_node))
			op = semantic_entities::operator_::MINUS_EQUAL;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::asterisk_equal>>(&simple_operator_node))
			op = semantic_entities::operator_::ASTERISK_EQUAL;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::slash_equal>>(&simple_operator_node))
			op = semantic_entities::operator_::SLASH_EQUAL;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::percent_equal>>(&simple_operator_node))
			op = semantic_entities::operator_::PERCENT_EQUAL;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::circumflex_equal>>(&simple_operator_node))
			op = semantic_entities::operator_::CIRCUMFLEX_EQUAL;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::ampersand_equal>>(&simple_operator_node))
			op = semantic_entities::operator_::AMPERSAND_EQUAL;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::pipe_equal>>(&simple_operator_node))
			op = semantic_entities::operator_::PIPE_EQUAL;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::double_left_angle_bracket>>(&simple_operator_node))
			op = semantic_entities::operator_::DOUBLE_LEFT_ANGLE_BRACKET;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::double_right_angle_bracket>>(&simple_operator_node))
			op = semantic_entities::operator_::DOUBLE_RIGHT_ANGLE_BRACKET;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::double_equal>>(&simple_operator_node))
			op = semantic_entities::operator_::DOUBLE_EQUAL;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::exclamation_equal>>(&simple_operator_node))
			op = semantic_entities::operator_::EXCLAMATION_EQUAL;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::left_angle_bracket_equal>>(&simple_operator_node))
			op = semantic_entities::operator_::LEFT_ANGLE_BRACKET_EQUAL;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::right_angle_bracket_equal>>(&simple_operator_node))
			op = semantic_entities::operator_::RIGHT_ANGLE_BRACKET_EQUAL;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::double_ampersand>>(&simple_operator_node))
			op = semantic_entities::operator_::DOUBLE_AMPERSAND;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::double_pipe>>(&simple_operator_node))
			op = semantic_entities::operator_::DOUBLE_PIPE;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::double_plus>>(&simple_operator_node))
			op = semantic_entities::operator_::DOUBLE_PLUS;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::double_minus>>(&simple_operator_node))
			op = semantic_entities::operator_::DOUBLE_MINUS;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::arrow>>(&simple_operator_node))
			op = semantic_entities::operator_::ARROW;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::round_brackets>>(&simple_operator_node))
			op = semantic_entities::operator_::ROUND_BRACKETS;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::square_brackets>>(&simple_operator_node))
			op = semantic_entities::operator_::SQUARE_BRACKETS;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::comma>>(&simple_operator_node))
			op = semantic_entities::operator_::COMMA;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::plus>>(&simple_operator_node))
			op = semantic_entities::operator_::PLUS;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::minus>>(&simple_operator_node))
			op = semantic_entities::operator_::MINUS;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::asterisk>>(&simple_operator_node))
			op = semantic_entities::operator_::ASTERISK;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::slash>>(&simple_operator_node))
			op = semantic_entities::operator_::SLASH;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::percent>>(&simple_operator_node))
			op = semantic_entities::operator_::PERCENT;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::circumflex>>(&simple_operator_node))
			op = semantic_entities::operator_::CIRCUMFLEX;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::ampersand>>(&simple_operator_node))
			op = semantic_entities::operator_::AMPERSAND;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::pipe>>(&simple_operator_node))
			op = semantic_entities::operator_::PIPE;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::tilde>>(&simple_operator_node))
			op = semantic_entities::operator_::TILDE;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::exclamation>>(&simple_operator_node))
			op = semantic_entities::operator_::EXCLAMATION;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::equal>>(&simple_operator_node))
			op = semantic_entities::operator_::EQUAL;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::left_angle_bracket>>(&simple_operator_node))
			op = semantic_entities::operator_::LEFT_ANGLE_BRACKET;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::right_angle_bracket>>(&simple_operator_node))
			op = semantic_entities::operator_::RIGHT_ANGLE_BRACKET;
		else
			assert(false);
	}
	else if(auto opt_array_operator_node = syntax_nodes::get<syntax_nodes::array_operator>(&operator_node))
	{
		auto array_operator_node = *opt_array_operator_node;

		if(syntax_nodes::get<syntax_nodes::new_array_operator>(&array_operator_node))
			op = semantic_entities::operator_::NEW_ARRAY;
		else if(syntax_nodes::get<syntax_nodes::delete_array_operator>(&array_operator_node))
			op = semantic_entities::operator_::DELETE_ARRAY;
		else
			assert(false);
	}
	else
	{
		assert(false);
	}



	return std::make_shared<semantic_entities::operator_function>
	(
		op,
		create_type(decl_specifier_seq_node, declarator_node, current_declarative_region),
		create_parameters(declarator_node, current_declarative_region),
		detail::semantic_analysis::has_inline_specifier(decl_specifier_seq_node)
	);
}

template<class DeclarativeRegionT>
semantic_entities::simple_function::parameters_t
semantic_analyzer::create_parameters
(
	const syntax_nodes::declarator& declarator_node,
	std::shared_ptr<DeclarativeRegionT> current_declarative_region
)
{
	std::list<semantic_entities::simple_function::parameter> parameters;

	auto direct_declarator_node = get_direct_declarator(declarator_node);
	if(auto opt_last_part_seq_node = get_last_part_seq(direct_declarator_node))
	{
		auto last_part_seq_node = *opt_last_part_seq_node;
		for(auto i = last_part_seq_node.begin(); i != last_part_seq_node.end(); ++i)
		{
			auto last_part_node = i->main_node();
			if(auto opt_function_part_node = syntax_nodes::get<syntax_nodes::direct_declarator_function_part>(&last_part_node))
			{
				if(auto opt_parameter_declaration_clause_node = get_parameter_declaration_clause(*opt_function_part_node))
				{
					if(auto opt_parameter_declaration_list_node = get_parameter_declaration_list(*opt_parameter_declaration_clause_node))
					{
						auto parameter_declaration_list_node = *opt_parameter_declaration_list_node;
						for
						(
							auto j = parameter_declaration_list_node.begin();
							j != parameter_declaration_list_node.end();
							++j
						)
						{
							auto parameter_declaration_node = j->main_node();
							auto decl_specifier_seq_node = get_decl_specifier_seq(parameter_declaration_node);

							if(auto opt_declarator_node = get_declarator(parameter_declaration_node))
							{
								auto declarator_node = *opt_declarator_node;

								parameters.push_back
								(
									std::move
									(
										semantic_entities::simple_function::parameter
										(
											create_type(decl_specifier_seq_node, declarator_node, current_declarative_region),
											detail::semantic_analysis::get_identifier(declarator_node).value()
										)
									)
								);
							}
							else if(auto opt_abstract_declarator_node = get_abstract_declarator(parameter_declaration_node))
							{
								auto abstract_declarator_node = *opt_abstract_declarator_node;

								parameters.push_back
								(
									std::move
									(
										semantic_entities::simple_function::parameter
										(
											create_type(decl_specifier_seq_node, abstract_declarator_node, current_declarative_region),
											""
										)
									)
								);
							}
							else
							{
								parameters.push_back
								(
									std::move
									(
										semantic_entities::simple_function::parameter
										(
											create_type(decl_specifier_seq_node, current_declarative_region),
											""
										)
									)
								);
							}
						}
					}
				}
			}
		}
	}

	return parameters;
}

template<class DeclarativeRegionT>
semantic_entities::type_shared_ptr_variant
semantic_analyzer::create_type
(
	const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node,
	const syntax_nodes::declarator& declarator_node,
	std::shared_ptr<DeclarativeRegionT> current_declarative_region
)
{
	semantic_entities::type_shared_ptr_variant return_type = create_type(decl_specifier_seq_node, current_declarative_region);

	//decorate type with hypothetical pointers and/or reference
	if(auto opt_ptr_operator_seq_node = get_ptr_operator_seq(declarator_node))
	{
		auto ptr_operator_seq_node = *opt_ptr_operator_seq_node;
		return_type = decorate_type(return_type, ptr_operator_seq_node);
	}

	//decorate type with hypothetical arrays
	auto direct_declarator_node = get_direct_declarator(declarator_node);
	if(auto opt_last_part_seq_node = get_last_part_seq(direct_declarator_node))
	{
		auto last_part_seq_node = *opt_last_part_seq_node;
		for
		(
			auto i = last_part_seq_node.begin();
			i != last_part_seq_node.end();
			++i
		)
		{
			auto last_part_node = i->main_node();
			if(auto array_part = syntax_nodes::get<syntax_nodes::direct_declarator_array_part>(&last_part_node))
			{
				return_type = std::make_shared<const semantic_entities::array>(0, return_type);
			}
		}
	}

	return return_type;
}

template<class DeclarativeRegionT>
semantic_entities::type_shared_ptr_variant
semantic_analyzer::create_type
(
	const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node,
	const syntax_nodes::abstract_declarator& abstract_declarator_node,
	std::shared_ptr<DeclarativeRegionT> current_declarative_region
)
{
	semantic_entities::type_shared_ptr_variant return_type = create_type(decl_specifier_seq_node, current_declarative_region);

	if(auto opt_ptr_operator_seq_node = syntax_nodes::get<syntax_nodes::ptr_operator_seq>(&abstract_declarator_node))
	{
		auto ptr_operator_seq_node = *opt_ptr_operator_seq_node;
		return_type = decorate_type(return_type, ptr_operator_seq_node);
	}

	return return_type;
}

template<class DeclarativeRegionT>
semantic_entities::type_shared_ptr_variant
semantic_analyzer::create_type
(
	const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node,
	std::shared_ptr<DeclarativeRegionT> current_declarative_region
)
{
	boost::optional<semantic_entities::type_shared_ptr_variant> opt_return_type;
	bool bool_type = false;
	bool char_type = false;
	bool double_type = false;
	bool float_type = false;
	bool int_type = false;
	bool long_long_type = false;
	bool long_type = false;
	bool short_type = false;
	bool signed_type = false;
	bool unsigned_type = false;
	bool void_type = false;
	bool wchar_t_type = false;
	bool is_const = false;
	bool is_volatile = false;

	for
	(
		auto i = decl_specifier_seq_node.begin();
		i < decl_specifier_seq_node.end();
		++i
	)
	{
		const syntax_nodes::decl_specifier& decl_specifier_node = i->main_node();

		//auto opt_function_specifier_node = syntax_nodes::get<function_specifier>(&decl_specifier_node);
		//auto opt_storage_class_specifier_node = syntax_nodes::get<storage_class_specifier>(&decl_specifier_node);
		//syntax_nodes::predefined_text_node<str::friend_>
		//syntax_nodes::predefined_text_node<str::typedef_>

		if(auto opt_type_specifier_node = syntax_nodes::get<syntax_nodes::type_specifier>(&decl_specifier_node))
		{
			auto type_specifier_node = *opt_type_specifier_node;
			get_type_info
			(
				type_specifier_node,
				opt_return_type,
				bool_type,
				char_type,
				double_type,
				float_type,
				int_type,
				long_long_type,
				long_type,
				short_type,
				signed_type,
				unsigned_type,
				void_type,
				wchar_t_type,
				is_const,
				is_volatile,
				current_declarative_region
			);
		}
	}

	if(!opt_return_type)
	{
		opt_return_type = get_fundamental_type
		(
			bool_type,
			char_type,
			double_type,
			float_type,
			int_type,
			long_long_type,
			long_type,
			short_type,
			signed_type,
			unsigned_type,
			void_type,
			wchar_t_type
		);
	}

	assert(opt_return_type);
	semantic_entities::type_shared_ptr_variant return_type = *opt_return_type;

	return_type = decorate_type(return_type, is_const, is_volatile);

	return return_type;
}

template<class DeclarativeRegionT>
semantic_entities::type_shared_ptr_variant
semantic_analyzer::get_conversion_function_type
(
	const syntax_nodes::declarator& declarator_node,
	std::shared_ptr<DeclarativeRegionT> current_declarative_region
)
{
	boost::optional<semantic_entities::type_shared_ptr_variant> opt_return_type;
	bool bool_type = false;
	bool char_type = false;
	bool double_type = false;
	bool float_type = false;
	bool int_type = false;
	bool long_long_type = false;
	bool long_type = false;
	bool short_type = false;
	bool signed_type = false;
	bool unsigned_type = false;
	bool void_type = false;
	bool wchar_t_type = false;
	bool is_const = false;
	bool is_volatile = false;

	auto direct_declarator_node = get_direct_declarator(declarator_node);
	auto direct_declarator_node_first_part_node = get_first_part(direct_declarator_node);
	auto opt_declarator_id_node = syntax_nodes::get<syntax_nodes::declarator_id>(&direct_declarator_node_first_part_node);
	assert(opt_declarator_id_node);
	auto declarator_id_node = *opt_declarator_id_node;
	auto opt_id_expression_node = syntax_nodes::get<syntax_nodes::id_expression>(&declarator_id_node);
	assert(opt_id_expression_node);
	auto id_expression_node = *opt_id_expression_node;
	auto opt_unqualified_id_node = syntax_nodes::get<syntax_nodes::unqualified_id>(&id_expression_node);
	assert(opt_unqualified_id_node);
	auto unqualified_id_node = *opt_unqualified_id_node;
	auto opt_conversion_function_id_node = syntax_nodes::get<syntax_nodes::conversion_function_id>(&unqualified_id_node);
	assert(opt_conversion_function_id_node);
	auto conversion_function_id_node = *opt_conversion_function_id_node;

	auto type_specifier_seq_node = get_type_specifier_seq(conversion_function_id_node);
	for(auto i = type_specifier_seq_node.begin(); i != type_specifier_seq_node.end(); ++i)
	{
		auto type_specifier_node = i->main_node();
		get_type_info
		(
			type_specifier_node,
			opt_return_type,
			bool_type,
			char_type,
			double_type,
			float_type,
			int_type,
			long_long_type,
			long_type,
			short_type,
			signed_type,
			unsigned_type,
			void_type,
			wchar_t_type,
			is_const,
			is_volatile,
			current_declarative_region
		);
	}

	if(!opt_return_type)
	{
		opt_return_type = get_fundamental_type
		(
			bool_type,
			char_type,
			double_type,
			float_type,
			int_type,
			long_long_type,
			long_type,
			short_type,
			signed_type,
			unsigned_type,
			void_type,
			wchar_t_type
		);
	}

	assert(opt_return_type);
	semantic_entities::type_shared_ptr_variant return_type = *opt_return_type;

	return_type = decorate_type(return_type, is_const, is_volatile);

	if(auto opt_ptr_operator_seq_node = get_ptr_operator_seq(conversion_function_id_node))
	{
		auto ptr_operator_seq_node = *opt_ptr_operator_seq_node;
		return_type = decorate_type(return_type, ptr_operator_seq_node);
	}

	return return_type;
}

template<class DeclarativeRegionT>
void
semantic_analyzer::get_type_info
(
	const syntax_nodes::type_specifier& type_specifier_node,
	boost::optional<semantic_entities::type_shared_ptr_variant>& t,
	bool& bool_type,
	bool& char_type,
	bool& double_type,
	bool& float_type,
	bool& int_type,
	bool& long_long_type,
	bool& long_type,
	bool& short_type,
	bool& signed_type,
	bool& unsigned_type,
	bool& void_type,
	bool& wchar_t_type,
	bool& is_const,
	bool& is_volatile,
	std::shared_ptr<DeclarativeRegionT> current_declarative_region
)
{
	//simple_type_specifier
	//class_specifier
	//enum_specifier
	//elaborated_type_specifier
	//cv_qualifier

	if(auto opt_simple_type_specifier_node = syntax_nodes::get<syntax_nodes::simple_type_specifier>(&type_specifier_node))
	{
		auto simple_type_specifier_node = *opt_simple_type_specifier_node;
		//simple_template_type_specifier,

		if(auto opt_nested_identifier_or_template_id_node = syntax_nodes::get<syntax_nodes::nested_identifier_or_template_id>(&simple_type_specifier_node))
		{
			auto nested_identifier_or_template_id_node = *opt_nested_identifier_or_template_id_node;
			t =
				std::shared_ptr<const semantic_entities::class_>
				(
					detail::semantic_analysis::name_lookup::find
					<
						semantic_entities::class_,
						false,
						false
					>
					(
						nested_identifier_or_template_id_node,
						current_declarative_region
					)
				)
			;
		}
		else if(auto opt_fundamental_type_specifier_node = syntax_nodes::get<syntax_nodes::fundamental_type_specifier>(&simple_type_specifier_node))
		{
			auto fundamental_type_specifier_node = *opt_fundamental_type_specifier_node;

			if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::char_>>(&fundamental_type_specifier_node))
			{
				char_type = true;
			}
			else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::wchar_t_>>(&fundamental_type_specifier_node))
			{
				wchar_t_type = true;
			}
			else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::bool_>>(&fundamental_type_specifier_node))
			{
				bool_type = true;
			}
			else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::short_>>(&fundamental_type_specifier_node))
			{
				short_type = true;
			}
			else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::int_>>(&fundamental_type_specifier_node))
			{
				int_type = true;
			}
			else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::long_>>(&fundamental_type_specifier_node))
			{
				if(!long_type)
					long_type = true;
				else
					long_long_type = true;
			}
			else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::signed_>>(&fundamental_type_specifier_node))
			{
				signed_type = true;
			}
			else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::unsigned_>>(&fundamental_type_specifier_node))
			{
				unsigned_type = true;
			}
			else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::float_>>(&fundamental_type_specifier_node))
			{
				float_type = true;
			}
			else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::double_>>(&fundamental_type_specifier_node))
			{
				double_type = true;
			}
			else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::void_>>(&fundamental_type_specifier_node))
			{
				void_type = true;
			}
		}
	}
	else if(auto opt_cv_qualifier_node = syntax_nodes::get<syntax_nodes::cv_qualifier>(&type_specifier_node))
	{
		auto cv_qualifier_node = *opt_cv_qualifier_node;
		//syntax_nodes::predefined_text_node<syntax_nodes::str::const_>
		//syntax_nodes::predefined_text_node<syntax_nodes::str::volatile_>

		if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::const_>>(&cv_qualifier_node))
		{
			is_const = true;
		}
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::volatile_>>(&cv_qualifier_node))
		{
			is_volatile = true;
		}
	}
}

template<class DeclarativeRegionT>
std::vector<std::shared_ptr<semantic_entities::variable>>
semantic_analyzer::create_variables
(
	const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node,
	const syntax_nodes::init_declarator_list& init_declarator_list_node,
	std::shared_ptr<DeclarativeRegionT> current_declarative_region
)
{
	std::vector<std::shared_ptr<semantic_entities::variable>> variables;

	//for each variable
	for
	(
		auto i = init_declarator_list_node.begin();
		i != init_declarator_list_node.end();
		++i
	)
	{
		auto init_declarator_node = i->main_node();
		auto declarator_node = get_declarator(init_declarator_node);
		variables.push_back
		(
			create_variable
			(
				decl_specifier_seq_node,
				declarator_node,
				current_declarative_region
			)
		);
	}

	return variables;
}

template<class DeclarativeRegionT>
std::shared_ptr<semantic_entities::variable>
semantic_analyzer::create_variable
(
	const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node,
	const syntax_nodes::declarator& declarator_node,
	std::shared_ptr<DeclarativeRegionT> current_declarative_region
)
{
	return std::make_shared<semantic_entities::variable>
	(
		detail::semantic_analysis::get_identifier(declarator_node).value(),
		create_type(decl_specifier_seq_node, declarator_node, current_declarative_region),
		detail::semantic_analysis::has_static_specifier(decl_specifier_seq_node)
	);
}

}} //namespace scalpel::cpp

#endif

