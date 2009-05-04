/*
Socoa - Source Code Analysis Library
Copyright © 2008, 2009  Florian Goujeon

This file is part of Socoa.

Socoa is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Socoa is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Socoa.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SOCOA_CPP_SEMANTIC_ANALYZER_HPP
#define SOCOA_CPP_SEMANTIC_ANALYZER_HPP

#include <memory>
#include "syntax_tree.hpp"
#include "semantic_graph.hpp"
#include "detail/semantic_analysis/scope_cursor.hpp"

namespace socoa { namespace cpp
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
		template<class... NodesT>
		inline
		void
		analyze(const syntax_nodes::alternative_node<NodesT...>& node);

		template<class... NodesT>
		inline
		void
		analyze_alternative(const syntax_nodes::alternative_node<NodesT...>& node);

		template<class T, const syntax_nodes::leaf_node& SeparatorNode>
		inline
		void
		analyze(const syntax_nodes::sequence_node<T, SeparatorNode>& seq);

		template<class T, const syntax_nodes::leaf_node& SeparatorNode>
		void
		analyze_sequence(const syntax_nodes::sequence_node<T, SeparatorNode>& seq);

        void
		analyze(const syntax_nodes::class_head& syntax_node);

        void
		analyze(const syntax_nodes::class_specifier& syntax_node);

        void
		analyze(const syntax_nodes::compound_statement& syntax_node);

        void
		analyze(const syntax_nodes::conversion_function_id& syntax_node);

        void
		analyze(const syntax_nodes::ctor_initializer& syntax_node);

        void
		analyze(const syntax_nodes::cv_qualifier& syntax_node);

        void
		analyze(const syntax_nodes::declaration& syntax_node);

        void
		analyze(const syntax_nodes::declarator& syntax_node);

        void
		analyze(const syntax_nodes::destructor_name& syntax_node);

        void
		analyze(const syntax_nodes::direct_declarator& syntax_node);

        void
		analyze(const syntax_nodes::direct_declarator::array_part& syntax_node);

        void
		analyze(const syntax_nodes::direct_declarator::function_part& syntax_node);

        void
		analyze(const syntax_nodes::elaborated_type_specifier& syntax_node);

        void
		analyze(const syntax_nodes::function_definition& syntax_node);

        void
		analyze(const syntax_nodes::identifier& syntax_node);

        void
		analyze(const syntax_nodes::init_declarator& syntax_node);

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
		analyze(const syntax_nodes::namespace_definition& syntax_node);

        void
		analyze(const syntax_nodes::nested_identifier_or_template_id& syntax_node);

        void
		analyze(const syntax_nodes::nested_name_specifier& syntax_node);

        void
		analyze(const syntax_nodes::nested_name_specifier::next_part& syntax_node);

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
		analyze(const syntax_nodes::simple_declaration& syntax_node);

        void
		analyze(const syntax_nodes::simple_template_type_specifier& syntax_node);

        void
		analyze(const syntax_nodes::template_declaration& syntax_node);

        void
		analyze(const syntax_nodes::template_id& syntax_node);

        void
		analyze(const syntax_nodes::using_declaration& syntax_node);

        void
		analyze(const syntax_nodes::using_directive& syntax_node);

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

template<class... NodesT>
void
semantic_analyzer::analyze(const syntax_nodes::alternative_node<NodesT...>& node)
{
	analyze_alternative(node);
}

template<class... NodesT>
void
semantic_analyzer::analyze_alternative(const syntax_nodes::alternative_node<NodesT...>& node)
{
	syntax_nodes::apply_visitor(alternative_visitor_, node);
}

template<class T, const syntax_nodes::leaf_node& SeparatorNode>
void
semantic_analyzer::analyze(const syntax_nodes::sequence_node<T, SeparatorNode>& seq)
{
	analyze_sequence(seq);
}

template<class T, const syntax_nodes::leaf_node& SeparatorNode>
void
semantic_analyzer::analyze_sequence(const syntax_nodes::sequence_node<T, SeparatorNode>& seq)
{
    for(auto i = seq.begin(); i != seq.end(); ++i)
    {
        analyze(i->main_node());
    }
}

}} //namespace socoa::cpp

#endif
