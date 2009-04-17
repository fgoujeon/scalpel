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
#include <boost/optional.hpp>
#include "syntax_tree.hpp"

namespace socoa { namespace cpp
{

template<class ConverterT>
class syntax_tree_to_any_conversion_helper
{
    private:
		class alternative_visitor
		{
			public:
				alternative_visitor(syntax_tree_to_any_conversion_helper& converter):
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
		friend class alternative_visitor;

	public:
		syntax_tree_to_any_conversion_helper(ConverterT& converter);

        template<class T, const syntax_tree::leaf_node& SeparatorNode>
		inline
        void
        convert(const syntax_tree::sequence_node<T, SeparatorNode>& seq);

		template<class... NodesT>
		inline
        void
		convert(const syntax_tree::alternative_node<NodesT...>& item);

        template<class T>
		inline
        void
        convert(const boost::optional<T>& item);

		inline
		void
		convert(const syntax_tree::declaration& a_declaration);

	private:
        template<class T, const syntax_tree::leaf_node& SeparatorNode>
        void
        convert_sequence_node(const syntax_tree::sequence_node<T, SeparatorNode>& seq);

		template<class... NodesT>
        void
		convert_alternative_node(const syntax_tree::alternative_node<NodesT...>& item);

        template<class T>
        void
        convert_optional_node(const boost::optional<T>& item);

        template<class T>
        void
        convert_any_node(const T& item);

		ConverterT& converter_;
		alternative_visitor alternative_visitor_;
};

template<class ConverterT>
syntax_tree_to_any_conversion_helper<ConverterT>::syntax_tree_to_any_conversion_helper
(
	ConverterT& converter
):
	converter_(converter),
	alternative_visitor_(*this)
{
}

template<class ConverterT>
template<class T, const syntax_tree::leaf_node& SeparatorNode>
void
syntax_tree_to_any_conversion_helper<ConverterT>::convert(const syntax_tree::sequence_node<T, SeparatorNode>& seq)
{
	convert_sequence_node(seq);
}

template<class ConverterT>
template<class... NodesT>
inline
void
syntax_tree_to_any_conversion_helper<ConverterT>::convert(const syntax_tree::alternative_node<NodesT...>& item)
{
	convert_alternative_node(item);
}

template<class ConverterT>
template<class T>
void
syntax_tree_to_any_conversion_helper<ConverterT>::convert(const boost::optional<T>& item)
{
	convert_optional_node(item);
}

template<class ConverterT>
void
syntax_tree_to_any_conversion_helper<ConverterT>::convert(const syntax_tree::declaration& a_declaration)
{
	const syntax_tree::declaration_t& decl = a_declaration;
	convert_alternative_node(decl);
}

template<class ConverterT>
template<class T, const syntax_tree::leaf_node& SeparatorNode>
void
syntax_tree_to_any_conversion_helper<ConverterT>::convert_sequence_node(const syntax_tree::sequence_node<T, SeparatorNode>& seq)
{
    for(auto i = seq.begin(); i != seq.end(); ++i)
    {
        convert_any_node(i->main_node());
    }
}

template<class ConverterT>
template<class... NodesT>
void
syntax_tree_to_any_conversion_helper<ConverterT>::convert_alternative_node(const syntax_tree::alternative_node<NodesT...>& item)
{
	syntax_tree::apply_visitor(alternative_visitor_, item);
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
