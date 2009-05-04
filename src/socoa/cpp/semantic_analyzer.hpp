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
#include "detail/semantic_analysis/syntax_tree_to_any_conversion_helper.hpp"
#include "detail/semantic_analysis/scope_cursor.hpp"

namespace socoa { namespace cpp
{

/**
@brief Analyses the semantic of the source code of a full C++ program.
*/
class semantic_analyzer
{
    public:
		semantic_analyzer();

		semantic_graph
		operator()(const syntax_tree& tree);

	private:
        void
		convert(const syntax_nodes::class_head& item);

        void
		convert(const syntax_nodes::class_specifier& item);

        void
		convert(const syntax_nodes::compound_statement& item);

        void
		convert(const syntax_nodes::conversion_function_id& item);

        void
		convert(const syntax_nodes::ctor_initializer& item);

        void
		convert(const syntax_nodes::cv_qualifier& item);

        void
		convert(const syntax_nodes::declarator& item);

        void
		convert(const syntax_nodes::destructor_name& item);

        void
		convert(const syntax_nodes::direct_declarator& item);

        void
		convert(const syntax_nodes::direct_declarator::array_part& item);

        void
		convert(const syntax_nodes::direct_declarator::function_part& item);

        void
		convert(const syntax_nodes::elaborated_type_specifier& item);

        void
		convert(const syntax_nodes::function_definition& item);

        void
		convert(const syntax_nodes::identifier& item);

        void
		convert(const syntax_nodes::init_declarator& item);

        void
		convert(const syntax_nodes::mem_initializer& item);

        void
		convert(const syntax_nodes::member_declaration_function_definition& item);

        void
		convert(const syntax_nodes::member_declaration_member_declarator_list& item);

        void
		convert(const syntax_nodes::member_declaration_unqualified_id& item);

        void
		convert(const syntax_nodes::member_declarator_bit_field_member& item);

        void
		convert(const syntax_nodes::member_declarator_declarator& item);

        void
		convert(const syntax_nodes::member_specification& item);

        void
		convert(const syntax_nodes::member_specification_access_specifier& item);

        void
		convert(const syntax_nodes::namespace_definition& item);

        void
		convert(const syntax_nodes::nested_identifier_or_template_id& item);

        void
		convert(const syntax_nodes::nested_name_specifier& item);

        void
		convert(const syntax_nodes::nested_name_specifier::next_part& item);

        void
		convert(const syntax_nodes::operator_function_id& item);

        void
		convert(const syntax_nodes::parameter_declaration& item);

        void
		convert(const syntax_nodes::parameter_declaration_clause& item);

        void
		convert(const syntax_nodes::ptr_operator& item);

        void
		convert(const syntax_nodes::qualified_identifier& item);

        void
		convert(const syntax_nodes::qualified_nested_id& item);

        void
		convert(const syntax_nodes::qualified_operator_function_id& item);

        void
		convert(const syntax_nodes::qualified_template_id& item);

        void
		convert(const syntax_nodes::simple_declaration& item);

        void
		convert(const syntax_nodes::simple_template_type_specifier& item);

        void
		convert(const syntax_nodes::template_declaration& item);

        void
		convert(const syntax_nodes::template_id& item);

        void
		convert(const syntax_nodes::using_declaration& item);

        void
		convert(const syntax_nodes::using_directive& item);

		template<const std::vector<std::string>& StringList>
		void
		convert(const util::string_enumeration<StringList>& a_string_enumeration);

        void
        convert_separator(const std::string& separator);

        template<class T>
        void
        convert(const T& item);

		friend class detail::semantic_analysis::syntax_tree_to_any_conversion_helper<semantic_analyzer>;

		detail::semantic_analysis::syntax_tree_to_any_conversion_helper<semantic_analyzer> conversion_helper_;
		detail::semantic_analysis::scope_cursor scope_cursor_;
};

template<const std::vector<std::string>& StringList>
void
semantic_analyzer::convert(const util::string_enumeration<StringList>&)
{
}

template<class T>
void
semantic_analyzer::convert(const T& item)
{
	conversion_helper_.convert(item);
}

}} //namespace socoa::cpp

#endif
