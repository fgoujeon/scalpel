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

#ifndef SOCOA_CPP_SYNTAX_TREE_TO_ANY_CONVERSION_HELPER_HPP
#define SOCOA_CPP_SYNTAX_TREE_TO_ANY_CONVERSION_HELPER_HPP

#include <string>
#include <boost/variant.hpp>
#include <boost/optional.hpp>
#include "../util/sequence.hpp"
#include "syntax_tree.hpp"

namespace socoa { namespace cpp
{

class syntax_tree_to_any_conversion_helper
{
    private:
		class static_visitor: public boost::static_visitor<>
		{
			public:
				static_visitor(syntax_tree_to_any_conversion_helper& converter):
					converter_(converter)
				{
				}

				template<class T>
				void
				operator()(const T& item) const
				{
					converter_.convert(item);
				}

			private:
				syntax_tree_to_any_conversion_helper& converter_;
		};

	public:
		syntax_tree_to_any_conversion_helper();

        template<class T, const std::string& Separator>
        void
        convert(const util::sequence<T, Separator>& seq);

		virtual
        void
        convert_separator(const std::string& separator) = 0;

		template<BOOST_VARIANT_ENUM_PARAMS(typename T)>
        void
		convert(const boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>& item);

        template<class T>
        void
        convert(const boost::optional<T>& item);

		template<const std::vector<std::string>& StringList>
		void
		convert(const util::string_enumeration<StringList>& a_string_enumeration);

        virtual
		void
		convert(const syntax_tree::class_head& item) = 0;

        virtual
		void
		convert(const syntax_tree::class_specifier& item) = 0;

        virtual
		void
		convert(const syntax_tree::conversion_function_id& item) = 0;

        virtual
		void
		convert(const syntax_tree::ctor_initializer& item) = 0;

        virtual
		void
		convert(const syntax_tree::cv_qualifier& item) = 0;

        virtual
		void
		convert(const syntax_tree::declarator& item) = 0;

        virtual
		void
		convert(const syntax_tree::destructor_name& item) = 0;

        virtual
		void
		convert(const syntax_tree::direct_declarator& item) = 0;

        virtual
		void
		convert(const syntax_tree::direct_declarator::array_part& item) = 0;

        virtual
		void
		convert(const syntax_tree::direct_declarator::function_part& item) = 0;

        virtual
		void
		convert(const syntax_tree::elaborated_type_specifier& item) = 0;

        virtual
		void
		convert(const syntax_tree::function_definition& item) = 0;

        virtual
		void
		convert(const syntax_tree::identifier& item) = 0;

        virtual
		void
		convert(const syntax_tree::init_declarator& item) = 0;

        virtual
		void
		convert(const syntax_tree::mem_initializer& item) = 0;

        virtual
		void
		convert(const syntax_tree::member_declaration_function_definition& item) = 0;

        virtual
		void
		convert(const syntax_tree::member_declaration_member_declarator_list& item) = 0;

        virtual
		void
		convert(const syntax_tree::member_declaration_unqualified_id& item) = 0;

        virtual
		void
		convert(const syntax_tree::member_declarator_bit_field_member& item) = 0;

        virtual
		void
		convert(const syntax_tree::member_declarator_declarator& item) = 0;

        virtual
		void
		convert(const syntax_tree::member_specification& item) = 0;

        virtual
		void
		convert(const syntax_tree::member_specification_access_specifier& item) = 0;

        virtual
		void
		convert(const syntax_tree::namespace_definition& item) = 0;

        virtual
		void
		convert(const syntax_tree::nested_identifier_or_template_id& item) = 0;

        virtual
		void
		convert(const syntax_tree::nested_name_specifier& item) = 0;

        virtual
		void
		convert(const syntax_tree::nested_name_specifier::second_part& item) = 0;

        virtual
		void
		convert(const syntax_tree::operator_function_id& item) = 0;

        virtual
		void
		convert(const syntax_tree::parameter_declaration& item) = 0;

        virtual
		void
		convert(const syntax_tree::parameter_declaration_clause& item) = 0;

        virtual
		void
		convert(const syntax_tree::ptr_operator& item) = 0;

        virtual
		void
		convert(const syntax_tree::qualified_identifier& item) = 0;

        virtual
		void
		convert(const syntax_tree::qualified_nested_id& item) = 0;

        virtual
		void
		convert(const syntax_tree::qualified_operator_function_id& item) = 0;

        virtual
		void
		convert(const syntax_tree::qualified_template_id& item) = 0;

        virtual
		void
		convert(const syntax_tree::simple_declaration& item) = 0;

        virtual
		void
		convert(const syntax_tree::simple_template_type_specifier& item) = 0;

        virtual
		void
		convert(const syntax_tree::template_declaration& item) = 0;

        virtual
		void
		convert(const syntax_tree::template_id& item) = 0;

        virtual
		void
		convert(const syntax_tree::using_declaration& item) = 0;

        virtual
		void
		convert(const syntax_tree::using_directive& item) = 0;

	private:
		static_visitor static_visitor_;
};

template<class T, const std::string& Separator>
void
syntax_tree_to_any_conversion_helper::convert(const util::sequence<T, Separator>& seq)
{
    typedef typename util::sequence<T>::list_t item_list_t;
	const item_list_t& item_list = seq.get_items();

    for(typename item_list_t::const_iterator i = item_list.begin(); i != item_list.end(); ++i)
    {
        //add separator
        if(i != item_list.begin()) //don't add a separator before the first item
		{
			convert_separator(Separator);
		}

        convert(*i);
    }
}

template<BOOST_VARIANT_ENUM_PARAMS(typename T)>
void
syntax_tree_to_any_conversion_helper::convert(const boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>& item)
{
	boost::apply_visitor(static_visitor_, item);
}

template<class T>
void
syntax_tree_to_any_conversion_helper::convert(const boost::optional<T>& item)
{
    if(item)
        convert(*item);
}

template<const std::vector<std::string>& StringList>
void
syntax_tree_to_any_conversion_helper::convert(const util::string_enumeration<StringList>& a_string_enumeration)
{
//    add_space();
 //   result_ << a_string_enumeration.get_value();
}

}} //namespace socoa::cpp

#endif
