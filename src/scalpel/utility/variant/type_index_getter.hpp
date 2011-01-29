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

#ifndef SCALPEL_UTILITY_VARIANT_TYPE_INDEX_GETTER_HPP
#define SCALPEL_UTILITY_VARIANT_TYPE_INDEX_GETTER_HPP

#include <boost/utility/enable_if.hpp>

namespace scalpel { namespace utility
{

template<typename... Ts>
struct type_index_getter;

template<>
struct type_index_getter<>
{
	static const unsigned int index = 0;

	template<typename U>
	static
	unsigned int
	get()
	{
		return 0;
	}
};

template<typename T, typename... Ts>
struct type_index_getter<T, Ts...>
{
	static const unsigned int index = type_index_getter<Ts...>::index + 1;

	template<typename U>
	static
	unsigned int
	get
	(
		typename boost::enable_if
		<
			boost::is_same<T, U>
		>::type* = 0
	)
	{
		return index;
	}

	template<typename U>
	static
	unsigned int
	get
	(
		typename boost::disable_if
		<
			boost::is_same<T, U>
		>::type* = 0
	)
	{
		return type_index_getter<Ts...>::template get<U>();
	}
};

}} //namespace scalpel::utility

#endif

