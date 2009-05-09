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

#include "semantic_analyzer.hpp"

#include <iostream>
#include "detail/semantic_analysis/name_lookup.hpp"

namespace scalpel { namespace cpp
{

using namespace syntax_nodes;
using namespace semantic_entities;
using namespace detail::semantic_analysis;

semantic_analyzer::alternative_visitor::alternative_visitor(semantic_analyzer& analyzer):
	analyzer_(analyzer)
{
}

semantic_analyzer::semantic_analyzer():
	alternative_visitor_(*this)
{
}

semantic_graph
semantic_analyzer::operator()(const syntax_tree& tree)
{
	//create semantic graph
	semantic_graph graph;

	//current scope = global namespace
	scope_cursor_.initialize(graph.root_node());

	auto opt_declaration_seq_node = tree.declaration_seq_node();

	if(opt_declaration_seq_node)
	{
		auto declaration_seq_node = *opt_declaration_seq_node;
		for
		(
			auto i = declaration_seq_node.begin();
			i != declaration_seq_node.end();
			++i
		)
		{
			analyze_alternative(i->main_node());
		}
	}

	auto lastly_leaved_scopes = scope_cursor_.lastly_leaved_scopes();
	lastly_leaved_scopes.push_back(&graph.root_node());
	graph.lastly_closed_scopes(lastly_leaved_scopes);

	graph.lastly_closed_scope_iterator().back().has_enclosing_scope();

	return graph;
}

void
semantic_analyzer::analyze(const break_statement&)
{
}

void
semantic_analyzer::analyze(const case_statement&)
{
}

void
semantic_analyzer::analyze(const class_head&)
{
}

void
semantic_analyzer::analyze(const class_specifier& syntax_node)
{
	boost::optional<const identifier&> id = syntax_node.class_head_node().identifier_node();

	if(id)
	{
		scope_cursor_.add_to_current_scope(class_(id->value()));
		scope_cursor_.enter_last_added_scope();
		scope_cursor_.leave_scope();
	}
}

void
semantic_analyzer::analyze(const classic_labeled_statement&)
{
}

void
semantic_analyzer::analyze(const compound_statement& syntax_node, const bool create_statement_block)
{
	if(create_statement_block)
	{
		statement_block s;
		scope_cursor_.add_to_current_scope(s);
		scope_cursor_.enter_last_added_scope();
	}

	auto opt_statement_seq_node = syntax_node.statement_seq_node();
	if(opt_statement_seq_node)
	{
		analyze(*opt_statement_seq_node);
	}

	if(create_statement_block)
	{
		scope_cursor_.leave_scope();
	}
}

void
semantic_analyzer::analyze(const continue_statement&)
{
}

void
semantic_analyzer::analyze(const conversion_function_id&)
{
}

void
semantic_analyzer::analyze(const ctor_initializer&)
{
}

void
semantic_analyzer::analyze(const cv_qualifier&)
{
}

void
semantic_analyzer::analyze(const declarator&)
{
}

void
semantic_analyzer::analyze(const default_statement&)
{
}

void
semantic_analyzer::analyze(const destructor_name&)
{
}

void
semantic_analyzer::analyze(const direct_declarator&)
{
}

void
semantic_analyzer::analyze(const direct_declarator::array_part&)
{
}

void
semantic_analyzer::analyze(const direct_declarator::function_part&)
{
}

void
semantic_analyzer::analyze(const do_while_statement&)
{
}

void
semantic_analyzer::analyze(const elaborated_type_specifier&)
{
}

void
semantic_analyzer::analyze(const expression_statement&)
{
}

void
semantic_analyzer::analyze(const for_statement& syntax_node)
{
	analyze(syntax_node.statement_node());
}

void
semantic_analyzer::analyze(const function_definition& syntax_node)
{
	//
	//get the name and the enclosing scope of the function
	//
	std::string name;
	scope* enclosing_scope = 0;

	const direct_declarator::first_part& first_part_node = syntax_node.declarator_node().direct_declarator_node().first_part_node();
	const boost::optional<const declarator_id&> a_declarator_id = get<declarator_id>(&first_part_node);
	if(a_declarator_id)
	{
		boost::optional<const id_expression&> an_id_expression = get<id_expression>(a_declarator_id);
		if(an_id_expression)
		{
			boost::optional<const unqualified_id&> an_unqualified_id = get<unqualified_id>(an_id_expression);
			boost::optional<const qualified_id&> a_qualified_id = get<qualified_id>(an_id_expression);

			if(an_unqualified_id)
			{
				boost::optional<const identifier&> an_identifier = get<identifier>(an_unqualified_id);
				if(an_identifier)
				{
					name = an_identifier->value();
				}

				enclosing_scope = &scope_cursor_.get_current_scope();
			}
			else if(a_qualified_id)
			{
				std::cout << "qualified_id\n";
			//	const qualified_identifier* const a_qualified_identifier =
			//		boost::get<qualified_identifier>(a_qualified_id)
			//	;
				boost::optional<const qualified_nested_id&> a_qualified_nested_id = get<qualified_nested_id>(a_qualified_id);
			//	const qualified_operator_function_id* const a_qualified_operator_function_id =
			//	   	boost::get<qualified_operator_function_id>(a_qualified_id)
			//	;
			//	const qualified_template_id* const a_qualified_template_id =
			//	   	boost::get<qualified_template_id>(a_qualified_id)
			//	;

				if(a_qualified_nested_id)
				{
					std::cout << "qualified_nested_id\n";

					bool leading_double_colon = a_qualified_nested_id->has_leading_double_colon();
					const nested_name_specifier& a_nested_name_specifier = a_qualified_nested_id->nested_name_specifier_node();

					if(leading_double_colon)
					{
						enclosing_scope = name_lookup::find_scope(scope_cursor_.get_global_scope(), a_nested_name_specifier);
					}
					else
					{
						enclosing_scope = name_lookup::find_scope(scope_cursor_.get_current_scope(), a_nested_name_specifier);
					}

					const unqualified_id& unqualified_id_node = a_qualified_nested_id->unqualified_id_node();
					boost::optional<const identifier&> identifier_node = get<identifier>(&unqualified_id_node);
					if(identifier_node)
					{
						name = identifier_node->value();
					}
				}
			}
			else
			{
				assert(false);
			}
		}
	}

	//get the corresponding function semantic node (it exists if the function has been declared)
	scope* function_scope = 0;
	if(!name.empty() && enclosing_scope)
	{
		auto scopes = enclosing_scope->scopes();
		for(auto i = scopes.begin(); i != scopes.end(); ++i)
		{
			scope& scope = *i;

			///\todo check the function's signature
			if(scope.name() == name)
			{
				function_scope = &scope;
				break;
			}
		}
	}

	//if the function hasn't been declared, this definition serves as a declaration
	if(!function_scope && enclosing_scope && !name.empty())
	{
		scope_cursor_.add_to_current_scope(function(name));
		function_scope = &scope_cursor_.get_current_scope().scopes().back();
	}

	//enter and leave the function body
	if(function_scope)
	{
		scope_cursor_.enter_scope(*function_scope);

		auto opt_compound_statement = syntax_node.compound_statement_node();
		if(opt_compound_statement) analyze(*opt_compound_statement, false);

		scope_cursor_.leave_scope();
	}
	else
	{
		std::cout << "function name: " << name << "\n";
	}
}

void
semantic_analyzer::analyze(const goto_statement&)
{
}

void
semantic_analyzer::analyze(const handler& syntax_node)
{
	analyze(syntax_node.compound_statement_node());
}

void
semantic_analyzer::analyze(const identifier&)
{
}

void
semantic_analyzer::analyze(const if_statement& syntax_node)
{
	analyze(syntax_node.statement_node());

	auto opt_else_statement_node = syntax_node.else_statement_node();
	if(opt_else_statement_node)
		analyze(*opt_else_statement_node);
}

void
semantic_analyzer::analyze(const init_declarator&)
{
}

void
semantic_analyzer::analyze(const mem_initializer&)
{
}

void
semantic_analyzer::analyze(const member_declaration_function_definition&)
{
}

void
semantic_analyzer::analyze(const member_declaration_member_declarator_list&)
{
}

void
semantic_analyzer::analyze(const member_declaration_unqualified_id&)
{
}

void
semantic_analyzer::analyze(const member_declarator_bit_field_member&)
{
}

void
semantic_analyzer::analyze(const member_declarator_declarator&)
{
}

void
semantic_analyzer::analyze(const member_specification&)
{
}

void
semantic_analyzer::analyze(const member_specification_access_specifier&)
{
}

void
semantic_analyzer::analyze(const namespace_definition& syntax_node)
{
	//get the namespace name
	std::string namespace_name;
	const boost::optional<const identifier&> an_identifier = syntax_node.identifier_node();
	if(an_identifier)
	{
		namespace_name = an_identifier->value();
	}

	//add the namespace to the current scope
	scope_cursor_.add_to_current_scope(namespace_(namespace_name));

	//add the declarations of the namespace definition in the namespace semantic node
	scope_cursor_.enter_last_added_scope(); //we have to enter even if there's no declaration
	const boost::optional<const declaration_seq&> a_declaration_seq = syntax_node.declaration_seq_node();
	if(a_declaration_seq)
	{
		analyze_sequence(*a_declaration_seq);
	}
	scope_cursor_.leave_scope();
}

void
semantic_analyzer::analyze(const nested_identifier_or_template_id&)
{
}

void
semantic_analyzer::analyze(const nested_name_specifier&)
{
}

void
semantic_analyzer::analyze(const nested_name_specifier::last_part&)
{
}

void
semantic_analyzer::analyze(const operator_function_id&)
{
}

void
semantic_analyzer::analyze(const parameter_declaration&)
{
}

void
semantic_analyzer::analyze(const parameter_declaration_clause&)
{
}

void
semantic_analyzer::analyze(const ptr_operator&)
{
}

void
semantic_analyzer::analyze(const qualified_identifier&)
{
}

void
semantic_analyzer::analyze(const qualified_nested_id&)
{
}

void
semantic_analyzer::analyze(const qualified_operator_function_id&)
{
}

void
semantic_analyzer::analyze(const qualified_template_id&)
{
}

void
semantic_analyzer::analyze(const return_statement&)
{
}

void
semantic_analyzer::analyze(const simple_declaration& syntax_node)
{
	std::vector<std::string> names;
	std::string class_name;
	bool is_a_class_declaration = false;
	bool is_a_class_forward_declaration = false;
	bool is_a_function_declaration = false;

	const boost::optional<const decl_specifier_seq&> an_optional_decl_specifier_seq = syntax_node.decl_specifier_seq_node();
	const boost::optional<const init_declarator_list&> an_optional_init_declarator_list = syntax_node.init_declarator_list_node();

	if(an_optional_decl_specifier_seq)
	{
		const decl_specifier_seq& a_decl_specifier_seq = *an_optional_decl_specifier_seq;
		for(auto i = a_decl_specifier_seq.begin(); i != a_decl_specifier_seq.end(); ++i)
		{
			const decl_specifier& a_decl_specifier = i->main_node();

			if(auto a_type_specifier_ptr = get<type_specifier>(&a_decl_specifier))
			{
				if(auto opt_class_specifier_node = get<class_specifier>(a_type_specifier_ptr))
				{
					is_a_class_declaration = true;
					analyze(*opt_class_specifier_node);
				}
				else if(auto an_elaborated_type_specifier_ptr = get<elaborated_type_specifier>(a_type_specifier_ptr))
				{
					//const class_template_elaborated_specifier* = get<>;
					//const enum_elaborated_specifier* ;
					//const typename_template_elaborated_specifier* ;
					//const typename_elaborated_specifier* ;

					if
					(
						auto opt_class_elaborated_specifier_node = get<class_elaborated_specifier>
						(
							an_elaborated_type_specifier_ptr
						)
					)
					{
						is_a_class_forward_declaration = true;
						const identifier& identifier_node = opt_class_elaborated_specifier_node->identifier_node();
						class_name = identifier_node.value();
					}
				}
			}
		}
	}

	if(an_optional_init_declarator_list)
	{
		const init_declarator_list& an_init_declarator_list = *an_optional_init_declarator_list;
		for(auto i = an_init_declarator_list.begin(); i != an_init_declarator_list.end(); ++i)
		{
			const declarator& a_declarator = i->main_node().declarator_node();
			const direct_declarator& a_direct_declarator = a_declarator.direct_declarator_node();

			//get the syntax_node name
			const direct_declarator::first_part& first_part_node = a_direct_declarator.first_part_node();
			const boost::optional<const declarator_id&> opt_declarator_id = get<declarator_id>(&first_part_node);
			if(opt_declarator_id)
			{
				const declarator_id& a_declarator_id = *opt_declarator_id;
				if(boost::optional<const id_expression&> an_id_expression = get<id_expression>(&a_declarator_id))
				{
					if(boost::optional<const unqualified_id&> an_unqualified_id = get<unqualified_id>(an_id_expression))
					{
						if(boost::optional<const identifier&> an_identifier = get<identifier>(an_unqualified_id))
						{
							names.push_back(an_identifier->value());
						}
					}
				}
			}

			//determine the appropriate semantic graph node
			auto a_direct_declarator_last_part_seq = a_direct_declarator.last_part_seq_node();
			if(a_direct_declarator_last_part_seq)
			{
				for(auto j = a_direct_declarator_last_part_seq->begin(); j != a_direct_declarator_last_part_seq->end(); ++j)
				{
					const direct_declarator::last_part& last_part = j->main_node();

					if(get<direct_declarator::function_part>(&last_part))
					{
						is_a_function_declaration = true;
					}
				}
			}
		}
	}

	if(is_a_class_declaration)
	{
		//analysis is already done
	}
	else if(is_a_class_forward_declaration)
	{
		if(!class_name.empty())
			scope_cursor_.add_to_current_scope(class_(class_name));
	}
	else if(is_a_function_declaration)
	{
		if(names.size() == 1)
		{
			scope_cursor_.add_to_current_scope(function(names.front()));
		}
	}
	else if(!is_a_function_declaration && !is_a_class_forward_declaration) //variable declaration
	{
		//there can be several names, like in:
		//int i1, i2;
		for(auto i = names.begin(); i != names.end(); ++i) //for each name
		{
			const std::string& name = *i;
			scope_cursor_.add_to_current_scope(variable(name));
		}
	}
}

void
semantic_analyzer::analyze(const simple_template_type_specifier&)
{
}

void
semantic_analyzer::analyze(const switch_statement&)
{
}

void
semantic_analyzer::analyze(const template_declaration&)
{
}

void
semantic_analyzer::analyze(const template_id&)
{
}

void
semantic_analyzer::analyze(const try_block& syntax_node)
{
	analyze(syntax_node.compound_statement_node());
	analyze(syntax_node.handler_seq_node());
}

void
semantic_analyzer::analyze(const using_declaration&)
{
}

void
semantic_analyzer::analyze(const using_directive&)
{
}

void
semantic_analyzer::analyze(const while_statement&)
{
}

}} //namespace scalpel::cpp

