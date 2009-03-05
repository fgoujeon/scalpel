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
#include "../util/sequence.hpp"

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
					converter_.convert(item);
				}

			private:
				syntax_tree_to_any_conversion_helper& converter_;
		};

	public:
		syntax_tree_to_any_conversion_helper(ConverterT& converter);

        template<class T, const std::string& Separator>
        void
        convert(const util::sequence<T, Separator>& seq);

		template<BOOST_VARIANT_ENUM_PARAMS(typename T)>
        void
		convert(const boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>& item);

        template<class T>
        void
        convert(const boost::optional<T>& item);

        template<class T>
        void
        convert(const T& item);

	private:
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
syntax_tree_to_any_conversion_helper<ConverterT>::convert(const util::sequence<T, Separator>& seq)
{
    typedef typename util::sequence<T>::list_t item_list_t;
	const item_list_t& item_list = seq.get_items();

    for(typename item_list_t::const_iterator i = item_list.begin(); i != item_list.end(); ++i)
    {
        //add separator
        if(i != item_list.begin()) //don't add a separator before the first item
		{
			converter_.convert_separator(Separator);
		}

        convert(*i);
    }
}

template<class ConverterT>
template<BOOST_VARIANT_ENUM_PARAMS(typename T)>
void
syntax_tree_to_any_conversion_helper<ConverterT>::convert(const boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>& item)
{
	boost::apply_visitor(static_visitor_, item);
}

template<class ConverterT>
template<class T>
void
syntax_tree_to_any_conversion_helper<ConverterT>::convert(const boost::optional<T>& item)
{
    if(item)
        convert(*item);
}

template<class ConverterT>
template<class T>
void
syntax_tree_to_any_conversion_helper<ConverterT>::convert(const T& item)
{
	converter_.convert(item);
}

}} //namespace socoa::cpp

#endif
