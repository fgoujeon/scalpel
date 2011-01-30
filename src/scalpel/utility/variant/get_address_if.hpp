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

#ifndef SCALPEL_UTILITY_VARIANT_GET_ADDRESS_IF_HPP
#define SCALPEL_UTILITY_VARIANT_GET_ADDRESS_IF_HPP

namespace scalpel { namespace utility
{

template<bool Cond, bool Const, typename T>
struct get_address_if_impl;

template<typename T>
struct get_address_if_impl<true, false, T>
{
	typedef T* return_type;

	static
	return_type
	result(T& t)
	{
		return &t;
	}
};

template<typename T>
struct get_address_if_impl<false, false, T>
{
	typedef T& return_type;

	static
	return_type
	result(T& t)
	{
		return t;
	}
};

template<typename T>
struct get_address_if_impl<true, true, T>
{
	typedef T const* return_type;

	static
	return_type
	result(T const& t)
	{
		return &t;
	}
};

template<typename T>
struct get_address_if_impl<false, true, T>
{
	typedef T const& return_type;

	static
	return_type
	result(T const& t)
	{
		return t;
	}
};

template<bool Cond, typename T>
const typename get_address_if_impl<Cond, false, T>::return_type
get_address_if(T& t)
{
	return get_address_if_impl<Cond, false, T>::result(t);
}

template<bool Cond, typename T>
const typename get_address_if_impl<Cond, true, T>::return_type
get_address_if(T const& t)
{
	return get_address_if_impl<Cond, true, T>::result(t);
}

}} //namespace scalpel::utility

#endif

