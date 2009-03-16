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
#include "syntax_tree_to_any_conversion_helper.hpp"

namespace socoa { namespace cpp
{

/**
@brief Analyses the semantic of the source code of a full C++ program.
*/
class semantic_analyzer: private syntax_tree_to_any_conversion_helper
{
    public:
		semantic_graph_t
		operator()(const syntax_tree_t& tree);

        void
		convert(const syntax_tree::class_head& item);

        void
		convert(const syntax_tree::class_specifier& item);

        void
		convert(const syntax_tree::conversion_function_id& item);

        void
		convert(const syntax_tree::ctor_initializer& item);

        void
		convert(const syntax_tree::cv_qualifier& item);

        void
		convert(const syntax_tree::declarator& item);

        void
		convert(const syntax_tree::destructor_name& item);

        void
		convert(const syntax_tree::direct_declarator& item);

        void
		convert(const syntax_tree::direct_declarator::array_part& item);

        void
		convert(const syntax_tree::direct_declarator::function_part& item);

        void
		convert(const syntax_tree::elaborated_type_specifier& item);

        void
		convert(const syntax_tree::function_definition& item);

        void
		convert(const syntax_tree::identifier& item);

        void
		convert(const syntax_tree::init_declarator& item);

        void
		convert(const syntax_tree::mem_initializer& item);

        void
		convert(const syntax_tree::member_declaration_function_definition& item);

        void
		convert(const syntax_tree::member_declaration_member_declarator_list& item);

        void
		convert(const syntax_tree::member_declaration_unqualified_id& item);

        void
		convert(const syntax_tree::member_declarator_bit_field_member& item);

        void
		convert(const syntax_tree::member_declarator_declarator& item);

        void
		convert(const syntax_tree::member_specification& item);

        void
		convert(const syntax_tree::member_specification_access_specifier& item);

        void
		convert(const syntax_tree::namespace_definition& item);

        void
		convert(const syntax_tree::nested_identifier_or_template_id& item);

        void
		convert(const syntax_tree::nested_name_specifier& item);

        void
		convert(const syntax_tree::nested_name_specifier::second_part& item);

        void
		convert(const syntax_tree::operator_function_id& item);

        void
		convert(const syntax_tree::parameter_declaration& item);

        void
		convert(const syntax_tree::parameter_declaration_clause& item);

        void
		convert(const syntax_tree::ptr_operator& item);

        void
		convert(const syntax_tree::qualified_identifier& item);

        void
		convert(const syntax_tree::qualified_nested_id& item);

        void
		convert(const syntax_tree::qualified_operator_function_id& item);

        void
		convert(const syntax_tree::qualified_template_id& item);

        void
		convert(const syntax_tree::simple_declaration& item);

        void
		convert(const syntax_tree::simple_template_type_specifier& item);

        void
		convert(const syntax_tree::template_declaration& item);

        void
		convert(const syntax_tree::template_id& item);

        void
		convert(const syntax_tree::using_declaration& item);

        void
		convert(const syntax_tree::using_directive& item);

        template<class T>
        void
        convert(const T& item);

        void
        convert_separator(const std::string& separator);

    private:
		semantic_graph_t semantic_graph_;
};

template<class T>
void
semantic_analyzer::convert(const T& item)
{
	syntax_tree_to_any_conversion_helper::convert(item);
}

}} //namespace socoa::cpp

#endif
