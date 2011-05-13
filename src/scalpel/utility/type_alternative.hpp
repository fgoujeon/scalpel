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

#ifndef SCALPEL_UTILITY_TYPE_ALTERNATIVE_HPP
#define SCALPEL_UTILITY_TYPE_ALTERNATIVE_HPP

namespace scalpel { namespace utility
{

template<typename... Ts>
struct type_list;

template<>
struct type_list<>
{
};

template<typename T, typename... Ts>
struct type_list<T, Ts...>
{
	typedef T type;
	typedef type_list<Ts...> tail;
};



template<class TypeList, unsigned int Index>
struct type_selector;

template<class TypeList>
struct type_selector<TypeList, 0>
{
	typedef typename TypeList::type type;
	typedef typename TypeList::tail tail;
};

template<class TypeList, unsigned int Index>
struct type_selector
{
	typedef typename type_selector<TypeList, Index - 1>::tail::type type;
	typedef typename type_selector<TypeList, Index - 1>::tail::tail tail;
};



template<unsigned int Index, typename... Ts>
struct type_alternative
{
	typedef typename type_selector<type_list<Ts...>, Index>::type type;
};

}} //namespace scalpel::utility

#endif

