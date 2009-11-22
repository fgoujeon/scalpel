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

#ifndef SCALPEL_CPP_SEMANTIC_ANALYZER_HPP
#define SCALPEL_CPP_SEMANTIC_ANALYZER_HPP

#include <memory>
#include "syntax_tree.hpp"
#include "semantic_graph.hpp"
#include "detail/semantic_analysis/scope_cursor.hpp"

namespace scalpel { namespace cpp
{

/**
@brief Analyses the semantic of the source code of a full C++ program.
*/
class semantic_analyzer
{
    public:
		class alternative_visitor
		{
			public:
				alternative_visitor(semantic_analyzer& analyzer);

				template<class T>
				inline
				void
				operator()(const T& syntax_node) const;

			private:
				semantic_analyzer& analyzer_;
		};

		semantic_analyzer();

		semantic_graph
		operator()(const syntax_tree& tree);

	private:
		template<class NodeT>
		inline
		void
		analyze(const NodeT& node);

		template<class NodeT>
		inline
		void
		analyze_alternative(const NodeT& node);

		template<class T, const syntax_nodes::leaf_node& SeparatorNode>
		inline
		void
		analyze(const syntax_nodes::list_node<T, SeparatorNode>& seq);

		template<class T, const syntax_nodes::leaf_node& SeparatorNode>
		void
		analyze_list(const syntax_nodes::list_node<T, SeparatorNode>& seq);

        void
		analyze(const syntax_nodes::asm_definition& syntax_node);

        void
		analyze(const syntax_nodes::break_statement& syntax_node);

        void
		analyze(const syntax_nodes::case_statement& syntax_node);

        void
		analyze(const syntax_nodes::class_head& syntax_node);

        void
		analyze(const syntax_nodes::class_specifier& syntax_node);

        void
		analyze(const syntax_nodes::classic_labeled_statement& syntax_node);

        void
		analyze(const syntax_nodes::compound_statement& syntax_node, const bool create_statement_block = true);

        void
		analyze(const syntax_nodes::conversion_function_id& syntax_node);

        void
		analyze(const syntax_nodes::continue_statement& syntax_node);

        void
		analyze(const syntax_nodes::ctor_initializer& syntax_node);

        void
		analyze(const syntax_nodes::cv_qualifier& syntax_node);

        void
		analyze(const syntax_nodes::declarator& syntax_node);

        void
		analyze(const syntax_nodes::default_statement& syntax_node);

        void
		analyze(const syntax_nodes::destructor_name& syntax_node);

        void
		analyze(const syntax_nodes::direct_declarator& syntax_node);

        void
		analyze(const syntax_nodes::direct_declarator_array_part& syntax_node);

        void
		analyze(const syntax_nodes::direct_declarator_function_part& syntax_node);

        void
		analyze(const syntax_nodes::do_while_statement& syntax_node);

        void
		analyze(const syntax_nodes::elaborated_type_specifier& syntax_node);

        void
		analyze(const syntax_nodes::explicit_instantiation& syntax_node);

        void
		analyze(const syntax_nodes::explicit_specialization& syntax_node);

        void
		analyze(const syntax_nodes::expression_statement& syntax_node);

        void
		analyze(const syntax_nodes::for_statement& syntax_node);

        void
		analyze(const syntax_nodes::function_definition& syntax_node);

        void
		analyze(const syntax_nodes::goto_statement& syntax_node);

        void
		analyze(const syntax_nodes::handler& syntax_node);

        void
		analyze(const syntax_nodes::identifier& syntax_node);

        void
		analyze(const syntax_nodes::if_statement& syntax_node);

        void
		analyze(const syntax_nodes::init_declarator& syntax_node);

        void
		analyze(const syntax_nodes::linkage_specification& syntax_node);

        void
		analyze(const syntax_nodes::mem_initializer& syntax_node);

        void
		analyze(const syntax_nodes::member_declaration_function_definition& syntax_node);

        void
		analyze(const syntax_nodes::member_declaration_member_declarator_list& syntax_node);

        void
		analyze(const syntax_nodes::member_declaration_unqualified_id& syntax_node);

        void
		analyze(const syntax_nodes::member_declarator_bit_field_member& syntax_node);

        void
		analyze(const syntax_nodes::member_declarator_declarator& syntax_node);

        void
		analyze(const syntax_nodes::member_specification& syntax_node);

        void
		analyze(const syntax_nodes::member_specification_access_specifier& syntax_node);

        void
		analyze(const syntax_nodes::namespace_alias_definition& syntax_node);

        void
		analyze(const syntax_nodes::namespace_definition& syntax_node);

        void
		analyze(const syntax_nodes::nested_identifier_or_template_id& syntax_node);

        void
		analyze(const syntax_nodes::nested_name_specifier& syntax_node);

        void
		analyze(const syntax_nodes::nested_name_specifier_last_part& syntax_node);

        void
		analyze(const syntax_nodes::operator_function_id& syntax_node);

        void
		analyze(const syntax_nodes::parameter_declaration& syntax_node);

        void
		analyze(const syntax_nodes::parameter_declaration_clause& syntax_node);

        void
		analyze(const syntax_nodes::ptr_operator& syntax_node);

        void
		analyze(const syntax_nodes::qualified_identifier& syntax_node);

        void
		analyze(const syntax_nodes::qualified_nested_id& syntax_node);

        void
		analyze(const syntax_nodes::qualified_operator_function_id& syntax_node);

        void
		analyze(const syntax_nodes::qualified_template_id& syntax_node);

        void
		analyze(const syntax_nodes::return_statement& syntax_node);

        void
		analyze(const syntax_nodes::simple_declaration& syntax_node);

        void
		analyze(const syntax_nodes::simple_template_type_specifier& syntax_node);

        void
		analyze(const syntax_nodes::switch_statement& syntax_node);

        void
		analyze(const syntax_nodes::template_declaration& syntax_node);

        void
		analyze(const syntax_nodes::template_id& syntax_node);

        void
		analyze(const syntax_nodes::try_block& syntax_node);

        void
		analyze(const syntax_nodes::type_id_sizeof_expression& syntax_node);

        void
		analyze(const syntax_nodes::unary_sizeof_expression& syntax_node);

        void
		analyze(const syntax_nodes::using_declaration& syntax_node);

        void
		analyze(const syntax_nodes::using_directive& syntax_node);

        void
		analyze(const syntax_nodes::while_statement& syntax_node);

		bool
		is_constructor_declaration(const syntax_nodes::declarator& declarator_node);

		bool
		is_function_declaration(const syntax_nodes::declarator& declarator_node);

		const semantic_entities::type&
		add_custom_type(std::unique_ptr<semantic_entities::type> t);

		semantic_entities::class_
		create_class(const syntax_nodes::class_specifier& syntax_node);

		void
		fill_class(semantic_entities::class_& c, const syntax_nodes::class_specifier& syntax_node);

		semantic_entities::function
		create_function
		(
			const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node,
			const syntax_nodes::declarator& declarator_node
		);

		const std::string&
		get_function_name(const syntax_nodes::declarator& declarator_node);

		template<const std::string& Qualifier>
		bool
		is_qualified(const syntax_nodes::declarator& declarator_node);

		template<const std::string& Specifier>
		bool
		is_specified(const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node);

		semantic_entities::function::parameters_t
		create_parameters(const syntax_nodes::declarator& declarator_node);

		const semantic_entities::type&
		create_type
		(
			const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node,
			const syntax_nodes::declarator& declarator_node
		);

		std::list<semantic_entities::variable>
		create_variables
		(
			const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node,
			const syntax_nodes::init_declarator_list& init_declarator_list_node
		);

		semantic_entities::variable
		create_variable
		(
			const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node,
			const syntax_nodes::declarator& declarator_node
		);

		detail::semantic_analysis::scope_cursor scope_cursor_;
		alternative_visitor alternative_visitor_;
		std::list<std::unique_ptr<semantic_entities::type>> custom_types_;
};

template<class T>
inline
void
semantic_analyzer::alternative_visitor::operator()(const T& syntax_node) const
{
	analyzer_.analyze(syntax_node);
}

template<class NodeT>
void
semantic_analyzer::analyze(const NodeT& node)
{
	analyze_alternative(node);
}

template<class NodeT>
void
semantic_analyzer::analyze_alternative(const NodeT& node)
{
	syntax_nodes::apply_visitor(alternative_visitor_, node);
}

template<class T, const syntax_nodes::leaf_node& SeparatorNode>
void
semantic_analyzer::analyze(const syntax_nodes::list_node<T, SeparatorNode>& seq)
{
	analyze_list(seq);
}

template<class T, const syntax_nodes::leaf_node& SeparatorNode>
void
semantic_analyzer::analyze_list(const syntax_nodes::list_node<T, SeparatorNode>& seq)
{
    for(auto i = seq.begin(); i != seq.end(); ++i)
    {
        analyze(i->main_node());
    }
}

template<const std::string& Qualifier>
bool
semantic_analyzer::is_qualified(const syntax_nodes::declarator& declarator_node)
{
	using namespace syntax_nodes;

	auto direct_declarator_node = get_direct_declarator(declarator_node);
	if(auto opt_last_part_seq_node = get_last_part_seq(direct_declarator_node))
	{
		auto last_part_seq_node = *opt_last_part_seq_node;
		for(auto i = last_part_seq_node.begin(); i != last_part_seq_node.end(); ++i)
		{
			auto last_part_node = i->main_node();
			if(auto opt_function_part_node = get<direct_declarator_function_part>(&last_part_node))
			{
				auto function_part_node = *opt_function_part_node;
				if(auto opt_cv_qualifier_seq_node = get_cv_qualifier_seq(function_part_node))
				{
					auto cv_qualifier_seq_node = *opt_cv_qualifier_seq_node;
					for(auto j = cv_qualifier_seq_node.begin(); j != cv_qualifier_seq_node.end(); ++j)
					{
						auto cv_qualifier_node = j->main_node();
						if(get<predefined_text_node<Qualifier>>(&cv_qualifier_node))
						{
							return true;
						}
					}
				}
			}
		}
	}

	return false;
}

template<const std::string& Specifier>
bool
semantic_analyzer::is_specified(const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node)
{
	using namespace syntax_nodes;

	for
	(
		auto i = decl_specifier_seq_node.begin();
		i < decl_specifier_seq_node.end();
		++i
	)
	{
		const decl_specifier& decl_specifier_node = i->main_node();

		if(auto opt_function_specifier_node = get<function_specifier>(&decl_specifier_node))
		{
			auto function_specifier_node = *opt_function_specifier_node;
			if(get<predefined_text_node<Specifier>>(&function_specifier_node))
				return true;
		}
	}

	return false;
}

}} //namespace scalpel::cpp

#endif
