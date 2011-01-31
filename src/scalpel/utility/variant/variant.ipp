/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2011  Florian Goujeon

This file is part of Scalpel.

Scalpel is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Scalpel is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Scalpel.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SCALPEL_UTILITY_VARIANT_VARIANT_IPP
#define SCALPEL_UTILITY_VARIANT_VARIANT_IPP

#include "apply_visitor_fwd.hpp"
#include "clear_visitor.hpp"
#include "equal_visitor.hpp"
#include "strict_select_type.hpp"
#include "type_index_getter.hpp"
#include "get_address_if.hpp"
#include "dereference_if.hpp"
#include <boost/type_traits/is_reference.hpp>
#include <stdexcept>
#include <cassert>

namespace scalpel { namespace utility
{

template<typename... Ts>
template<typename U>
variant<Ts...>::variant
(
	const U& value,
	typename boost::disable_if<boost::is_same<U, variant>>::type*
)
{
	//std::cout << "variant ctor 2" << std::endl;
	set<typename select_type<U, Ts...>::type>(value);
	assert(type_index_ != 0);
}

template<typename... Ts>
template<typename U>
variant<Ts...>::variant
(
	U& value,
	typename boost::disable_if<boost::is_same<U, variant>>::type*
)
{
	//std::cout << "variant ctor 1" << std::endl;
	set<typename select_type<U&, Ts...>::type>(value);
	assert(type_index_ != 0);
}

template<typename... Ts>
variant<Ts...>::variant(const variant& rhs)
{
	//std::cout << "variant copy ctor" << std::endl;
	assign_visitor<Ts...> visitor(*this);
	apply_visitor(visitor, rhs);
	assert(type_index_ != 0);
}

template<typename... Ts>
variant<Ts...>::~variant()
{
	clear();
}

template<typename... Ts>
variant<Ts...>&
variant<Ts...>::operator=(const variant& rhs)
{
	//std::cout << "variant copy assign" << std::endl;
	clear();
	assign_visitor<Ts...> visitor(*this);
	apply_visitor(visitor, rhs);
	assert(type_index_ != 0);
	return *this;
}

template<typename... Ts>
template<typename U>
typename boost::disable_if<boost::is_same<U, variant<Ts...>>, variant<Ts...>&>::type
variant<Ts...>::operator=(const U& value)
{
	//std::cout << "variant assign const" << std::endl;
	clear();
	set<typename select_type<U, Ts...>::type>(value);
	return *this;
}

template<typename... Ts>
template<typename U>
typename boost::disable_if<boost::is_same<U, variant<Ts...>>, variant<Ts...>&>::type
variant<Ts...>::operator=(U& value)
{
	//std::cout << "variant assign" << std::endl;
	clear();
	set<typename select_type<U&, Ts...>::type>(value);
	return *this;
}

template<typename... Ts>
template<typename U>
U&
variant<Ts...>::get()
{
	typedef typename strict_select_type<U, Ts...>::type ignored_t; //just check whether U is in Ts
	typedef typename replace_reference_by_pointer<U>::type any_container_type_t;

	if(type_index_getter<Ts...>::template get<U>() != type_index_) throw std::runtime_error("bad get");

	any_container_type_t& value = container_.get<any_container_type_t>();
	return dereference_if<boost::is_reference<U>::value>(value);
}

template<typename... Ts>
template<typename U>
const U&
variant<Ts...>::get() const
{
	typedef typename strict_select_type<U, Ts...>::type ignored_t; //just check whether U is in Ts
	typedef typename replace_reference_by_pointer<U>::type any_container_type_t;

	if(type_index_getter<Ts...>::template get<U>() != type_index_) throw std::runtime_error("bad get");

	const any_container_type_t& value = container_.get<any_container_type_t>();
	return dereference_if<boost::is_reference<U>::value>(value);
}

template<typename... Ts>
template<typename U>
U*
variant<Ts...>::get_optional()
{
	typedef typename strict_select_type<U, Ts...>::type ignored_t; //just check whether U is in Ts
	typedef typename replace_reference_by_pointer<U>::type any_container_type_t;

	if(type_index_getter<Ts...>::template get<U>() != type_index_) return 0;

	any_container_type_t& value = container_.get<any_container_type_t>();
	return &dereference_if<boost::is_reference<U>::value>(value);
}

template<typename... Ts>
template<typename U>
const U*
variant<Ts...>::get_optional() const
{
	typedef typename strict_select_type<U, Ts...>::type ignored_t; //just check whether U is in Ts
	typedef typename replace_reference_by_pointer<U>::type any_container_type_t;

	if(type_index_getter<Ts...>::template get<U>() != type_index_) return 0;

	const any_container_type_t& value = container_.get<any_container_type_t>();
	return &dereference_if<boost::is_reference<U>::value>(value);
}

template<typename... Ts>
template<typename U>
void
variant<Ts...>::set
(
	const U& value,
	typename boost::disable_if
	<
		is_reference_of_non_const<typename select_type<U, Ts...>::type>
	>::type*
)
{
	typedef typename select_type<U, Ts...>::type selected_type_t;
	typedef typename replace_reference_by_pointer<selected_type_t>::type any_container_type_t;

	const any_container_type_t& any_container_value = get_address_if<boost::is_reference<selected_type_t>::value>(value);
	container_.set<any_container_type_t>(any_container_value);

	type_index_ = type_index_getter<Ts...>::template get<U>();
}

template<typename... Ts>
template<typename U>
void
variant<Ts...>::set
(
	U& value,
	typename boost::enable_if
	<
		is_reference_of_non_const<typename select_type<U, Ts...>::type>
	>::type*
)
{
	typedef typename select_type<U, Ts...>::type selected_type_t;
	typedef typename replace_reference_by_pointer<selected_type_t>::type any_container_type_t;

	any_container_type_t any_container_value = get_address_if<boost::is_reference<selected_type_t>::value>(value);
	container_.set<any_container_type_t>(any_container_value);

	type_index_ = type_index_getter<Ts...>::template get<U>();
}

template<typename... Ts>
void
variant<Ts...>::clear()
{
	assert(type_index_ != 0);
	clear_visitor<size, Ts...> visitor(container_);
	apply_visitor(visitor, *this);
}



template<typename... Ts>
bool
operator==(const variant<Ts...>& lhs, const variant<Ts...>& rhs)
{
	partial_equal_visitor<Ts...> visitor(lhs);
	return apply_visitor(visitor, rhs);
}

template<typename... Ts>
bool
operator!=(const variant<Ts...>& lhs, const variant<Ts...>& rhs)
{
	return !(lhs == rhs);
}

}} //namespace scalpel::utility

#endif

