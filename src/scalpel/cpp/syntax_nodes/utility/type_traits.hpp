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

#ifndef SCALPEL_CPP_SYNTAX_NODES_UTIL_NODE_TYPE_TRAITS_HPP
#define SCALPEL_CPP_SYNTAX_NODES_UTIL_NODE_TYPE_TRAITS_HPP

#include "../optional_node.hpp"
#include "../predefined_text_node.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes { namespace utility
{

/*
 * Utility types
 */
typedef char yes_type;

struct no_type
{
	char padding[8];
};



/*
 * sequence_node type trait
 */
namespace sequence_node_check
{
	template<class T>
	static
	yes_type
	check_sig(typename T::tail_sequence_node_t*);

	template<class T>
	static
	no_type
	check_sig(...);
}

template<class T>
struct is_sequence_node
{
	static const bool value = sizeof(sequence_node_check::check_sig<T>(0)) == sizeof(yes_type);
};



/*
 * alternative_node type trait
 */
namespace alternative_node_check
{
	template<class T>
	static
	yes_type
	check_sig(typename T::tail_alternative_node_t*);

	template<class T>
	static
	no_type
	check_sig(...);
}

template<class T>
struct is_alternative_node
{
	static const bool value = sizeof(alternative_node_check::check_sig<T>(0)) == sizeof(yes_type);
};



/*
 * list_node type trait
 */
namespace list_node_check
{
	template<class T>
	static
	yes_type
	check_sig(typename T::item*);

	template<class T>
	static
	no_type
	check_sig(...);
}

template<class T>
struct is_list_node
{
	static const bool value = sizeof(list_node_check::check_sig<T>(0)) == sizeof(yes_type);
};



/*
 * optional_node type trait
 */
template<class T>
struct is_optional_node
{
	static const bool value = false;
};

template<class T>
struct is_optional_node<syntax_nodes::optional_node<T>>
{
	static const bool value = true;
};



/*
 * predefined_text_node type trait
 */
template<class T>
struct is_predefined_text_node
{
	static const bool value = false;
};

template<const std::string& Text>
struct is_predefined_text_node<syntax_nodes::predefined_text_node<Text>>
{
	static const bool value = true;
};



/*
 * leaf_node type trait
 */
template<class T>
struct is_leaf_node
{
	static const bool value =
		!is_sequence_node<T>::value &&
		!is_alternative_node<T>::value &&
		!is_list_node<T>::value &&
		!is_optional_node<T>::value &&
		!is_predefined_text_node<T>::value
	;
};

}}}} //namespace scalpel::cpp::syntax_nodes::utility

#endif
