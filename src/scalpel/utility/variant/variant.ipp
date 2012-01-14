/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2012  Florian Goujeon

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
#include "clear_and_set_visitor.hpp"
#include "clear_visitor.hpp"
#include "equals_visitors.hpp"
#include "less_than_visitors.hpp"
#include "strict_select_type.hpp"
#include "type_index_getter.hpp"
#include <stdexcept>
#include <cassert>

namespace scalpel { namespace utility
{

template<typename... Ts>
template<typename U>
variant<Ts...>::variant
(
	const U& value,
	typename boost::disable_if<boost::is_const<U>>::type*,
	typename boost::disable_if<boost::is_reference<U>>::type*,
	typename boost::disable_if<boost::is_same<U, variant>>::type*
)
{
	set<typename select_type<U, Ts...>::type>(value, false);
	assert(type_index_ != 0);
}

template<typename... Ts>
template<typename U>
variant<Ts...>::variant
(
	U&& value,
	typename boost::disable_if<boost::is_const<U>>::type*,
	typename boost::disable_if<boost::is_reference<U>>::type*,
	typename boost::disable_if<boost::is_same<U, variant>>::type*
)
{
	set2<typename select_type<U, Ts...>::type>(std::move(value), false);
	assert(type_index_ != 0);
}

template<typename... Ts>
variant<Ts...>::variant(const variant& rhs)
{
	assign_visitor<Ts...> visitor(*this, false);
	apply_visitor(visitor, rhs);
	assert(type_index_ != 0);
}

template<typename... Ts>
variant<Ts...>::~variant()
{
	clear_visitor<size> visitor(container_);
	apply_visitor(visitor, *this);
}

template<typename... Ts>
variant<Ts...>&
variant<Ts...>::operator=(const variant& rhs)
{
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
	set<typename select_type<U, Ts...>::type>(value);
	return *this;
}

template<typename... Ts>
template<typename U>
U&
variant<Ts...>::get()
{
	typedef typename strict_select_type<U, Ts...>::type ignored_t; //just check whether U is in Ts

	if(type_index_getter<Ts...>::template get<U>() != type_index_) throw std::runtime_error("bad get");

	return container_.get<U>();
}

template<typename... Ts>
template<typename U>
const U&
variant<Ts...>::get() const
{
	typedef typename strict_select_type<U, Ts...>::type ignored_t; //just check whether U is in Ts

	if(type_index_getter<Ts...>::template get<U>() != type_index_) throw std::runtime_error("bad get");

	return container_.get<U>();
}

template<typename... Ts>
template<typename U>
U*
variant<Ts...>::get_optional()
{
	typedef typename strict_select_type<U, Ts...>::type ignored_t; //just check whether U is in Ts

	if(type_index_getter<Ts...>::template get<U>() != type_index_) return 0;

	return &container_.get<U>();
}

template<typename... Ts>
template<typename U>
const U*
variant<Ts...>::get_optional() const
{
	typedef typename strict_select_type<U, Ts...>::type ignored_t; //just check whether U is in Ts

	if(type_index_getter<Ts...>::template get<U>() != type_index_) return 0;

	return &container_.get<U>();
}

template<typename... Ts>
template<typename U>
void
variant<Ts...>::set
(
	const U& value,
	const bool clear
)
{
	typedef typename select_type<U, Ts...>::type selected_type_t;
	typedef selected_type_t any_container_type_t;

	const any_container_type_t& any_container_value = value;
	if(clear)
	{
		clear_and_set_visitor<size, any_container_type_t> visitor(container_, any_container_value);
		apply_visitor(visitor, *this);
	}
	else
	{
		container_.set<any_container_type_t>(any_container_value);
	}

	type_index_ = type_index_getter<Ts...>::template get<selected_type_t>();
}

template<typename... Ts>
template<typename U>
void
variant<Ts...>::set2
(
	U&& value,
	const bool clear
)
{
	typedef typename select_type<U, Ts...>::type selected_type_t;
	typedef selected_type_t any_container_type_t;

	any_container_type_t&& any_container_value = std::move(value);
	if(clear)
	{
		clear_and_set_visitor2<size, any_container_type_t> visitor(container_, std::move(any_container_value));
		apply_visitor(visitor, *this);
	}
	else
	{
		container_.set<any_container_type_t>(std::move(any_container_value));
	}

	type_index_ = type_index_getter<Ts...>::template get<selected_type_t>();
}



template<typename... Ts>
bool
operator==(const variant<Ts...>& lhs, const variant<Ts...>& rhs)
{
	partial_equals_visitor<Ts...> visitor(lhs);
	return apply_visitor(visitor, rhs);
}

template<typename... Ts>
bool
operator!=(const variant<Ts...>& lhs, const variant<Ts...>& rhs)
{
	return !(lhs == rhs);
}

template<typename... Ts>
bool
operator<(const variant<Ts...>& lhs, const variant<Ts...>& rhs)
{
	if(lhs.type_index() != rhs.type_index())
	{
		return lhs.type_index() > rhs.type_index();
	}
	else
	{
		partial_less_than_visitor<Ts...> visitor(lhs);
		return apply_visitor(visitor, rhs);
	}
}

}} //namespace scalpel::utility

#endif

