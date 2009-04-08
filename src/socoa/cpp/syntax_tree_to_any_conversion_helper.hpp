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

#ifndef SOCOA_CPP_SYNTAX_TREE_TO_CONVERSION_HELPER_HPP
#define SOCOA_CPP_SYNTAX_TREE_TO_CONVERSION_HELPER_HPP

#include <string>
#include <boost/variant.hpp>
#include <boost/optional.hpp>
#include "syntax_tree.hpp"

namespace socoa { namespace cpp
{

template<class ConverterT>
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
					converter_.convert_any_node(item);
				}

			private:
				syntax_tree_to_any_conversion_helper& converter_;
		};

		friend class static_visitor;

	public:
		syntax_tree_to_any_conversion_helper(ConverterT& converter);

        template<class T, const std::string& Separator>
		inline
        void
        convert(const syntax_tree::sequence_node<T, Separator>& seq);

		template<BOOST_VARIANT_ENUM_PARAMS(typename T)>
		inline
        void
		convert(const boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>& item);

        template<class T>
		inline
        void
        convert(const boost::optional<T>& item);

	private:
        template<class T, const std::string& Separator>
        void
        convert_sequence_node(const syntax_tree::sequence_node<T, Separator>& seq);

		template<BOOST_VARIANT_ENUM_PARAMS(typename T)>
        void
		convert_variant_node(const boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>& item);

        template<class T>
        void
        convert_optional_node(const boost::optional<T>& item);

        template<class T>
        void
        convert_any_node(const T& item);

		ConverterT& converter_;
		static_visitor static_visitor_;
};

template<class ConverterT>
syntax_tree_to_any_conversion_helper<ConverterT>::syntax_tree_to_any_conversion_helper
(
	ConverterT& converter
):
	converter_(converter),
	static_visitor_(*this)
{
}

template<class ConverterT>
template<class T, const std::string& Separator>
void
syntax_tree_to_any_conversion_helper<ConverterT>::convert(const syntax_tree::sequence_node<T, Separator>& seq)
{
	convert_sequence_node(seq);
}

template<class ConverterT>
template<BOOST_VARIANT_ENUM_PARAMS(typename T)>
void
syntax_tree_to_any_conversion_helper<ConverterT>::convert(const boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>& item)
{
	convert_variant_node(item);
}

template<class ConverterT>
template<class T>
void
syntax_tree_to_any_conversion_helper<ConverterT>::convert(const boost::optional<T>& item)
{
	convert_optional_node(item);
}

template<class ConverterT>
template<class T, const std::string& Separator>
void
syntax_tree_to_any_conversion_helper<ConverterT>::convert_sequence_node(const syntax_tree::sequence_node<T, Separator>& seq)
{
    for(auto i = seq.begin(); i != seq.end(); ++i)
    {
        //add separator
        if(i != seq.begin()) //don't add a separator before the first item
		{
			converter_.convert_separator(Separator);
		}

        convert_any_node(*i);
    }
}

template<class ConverterT>
template<BOOST_VARIANT_ENUM_PARAMS(typename T)>
void
syntax_tree_to_any_conversion_helper<ConverterT>::convert_variant_node(const boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>& item)
{
	boost::apply_visitor(static_visitor_, item);
}

template<class ConverterT>
template<class T>
void
syntax_tree_to_any_conversion_helper<ConverterT>::convert_optional_node(const boost::optional<T>& item)
{
    if(item)
        convert_any_node(*item);
}

template<class ConverterT>
template<class T>
void
syntax_tree_to_any_conversion_helper<ConverterT>::convert_any_node(const T& item)
{
	//This may call either one of the ConverterT's basic node convert functions
	//or the ConverterT's generic convert function template which will call one
	//of the syntax_tree_to_any_conversion_helper's convert functions in its
	//turn.
	//The ConverterT's generic convert function template definition must be:
	//	template<class T>
	//	void
	//	syntax_tree_to_string_converter::convert(const T& item)
	//	{
	//		conversion_helper_.convert(item);
	//	}
	converter_.convert(item);
}

}} //namespace socoa::cpp

#endif
