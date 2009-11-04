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

		semantic_entities::class_
		create_class(const syntax_nodes::class_specifier& syntax_node);

		std::unique_ptr<semantic_entities::type>
		create_type(const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node);

		detail::semantic_analysis::scope_cursor scope_cursor_;
		alternative_visitor alternative_visitor_;
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

}} //namespace scalpel::cpp

#endif
