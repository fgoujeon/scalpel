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

#ifndef SCALPEL_UTILITY_VARIANT_SELECT_TYPE_HPP
#define SCALPEL_UTILITY_VARIANT_SELECT_TYPE_HPP

namespace scalpel { namespace utility
{

template<typename U, typename... Ts>
struct select_type;

template<typename U>
struct select_type<U>
{
};

//U == T
template<typename T, typename... Ts>
struct select_type<T, T, Ts...>
{
	typedef T type;
};

//U& == T
template<typename T, typename... Ts>
struct select_type<T, T&, Ts...>
{
	typedef T& type;
};

//U == T&
template<typename T, typename... Ts>
struct select_type<T&, T, Ts...>
{
	typedef T type;
};

//const U& == T
template<typename T, typename... Ts>
struct select_type<T, const T&, Ts...>
{
	typedef const T& type;
};

//U == const T&
template<typename T, typename... Ts>
struct select_type<const T&, T, Ts...>
{
	typedef T type;
};

//U == X*
//T == const X*
template<typename T, typename... Ts>
struct select_type<T*, const T*, Ts...>
{
	typedef const T* type;
};

//U == X&
//T == const X&
template<typename T, typename... Ts>
struct select_type<T&, const T&, Ts...>
{
	typedef const T& type;
};

//U != T, let's try to find U among Ts
template<typename U, typename T, typename... Ts>
struct select_type<U, T, Ts...>
{
	typedef typename select_type<U, Ts...>::type type;
};

}} //namespace scalpel::utility

#endif

