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
class semantic_analyzer
{
    public:
		semantic_analyzer();

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

        template<class T, const std::string& Separator>
        void
        convert(const util::sequence<T, Separator>& seq);

        template<const std::vector<std::string>& StringList>
        void
        convert(const util::string_enumeration<StringList>& a_string_enumeration);

		template<BOOST_VARIANT_ENUM_PARAMS(typename T)>
		void
		convert(const boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>& item);

        template<class T>
        void
        convert(const boost::optional<T> item);

        void
        convert_separator(const std::string& separator);

    private:
//		syntax_tree_to_any_conversion_helper<semantic_analyzer> conversion_helper_;
		semantic_graph_t* semantic_graph_;
};

template<class T, const std::string& Separator>
void
semantic_analyzer::convert(const util::sequence<T, Separator>& seq)
{
//	conversion_helper_.convert(seq);
}

template<const std::vector<std::string>& StringList>
void
semantic_analyzer::convert(const util::string_enumeration<StringList>& a_string_enumeration)
{
}

template<BOOST_VARIANT_ENUM_PARAMS(typename T)>
void
semantic_analyzer::convert(const boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>& item)
{
//	conversion_helper_.convert(item);
}

template<class T>
void
semantic_analyzer::convert(const boost::optional<T> item)
{
//	conversion_helper_.convert(item);
}

}} //namespace socoa::cpp

#endif
