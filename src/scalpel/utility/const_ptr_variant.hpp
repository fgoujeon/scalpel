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

#ifndef SCALPEL_UTILITY_CONST_PTR_VARIANT_HPP
#define SCALPEL_UTILITY_CONST_PTR_VARIANT_HPP

#include "variant.hpp"

namespace scalpel { namespace utility
{

template<typename... Ts>
struct const_ptr_variant;

template
<
	typename T1
>
struct const_ptr_variant<T1>
{
	typedef variant<const T1*> type;
};

template
<
	typename T1,
	typename T2
>
struct const_ptr_variant<T1, T2>
{
	typedef variant<const T1*, const T2*> type;
};

template
<
	typename T1,
	typename T2,
	typename T3
>
struct const_ptr_variant<T1, T2, T3>
{
	typedef variant<const T1*, const T2*, const T3*> type;
};

template
<
	typename T1,
	typename T2,
	typename T3,
	typename T4,
	typename T5,
	typename T6,
	typename T7,
	typename T8,
	typename T9
>
struct const_ptr_variant<T1, T2, T3, T4, T5, T6, T7, T8, T9>
{
	typedef variant<const T1*, const T2*, const T3*, const T4*, const T5*, const T6*, const T7*, const T8*, const T9*> type;
};

template
<
	typename T1,
	typename T2,
	typename T3,
	typename T4,
	typename T5,
	typename T6,
	typename T7,
	typename T8,
	typename T9,
	typename T10
>
struct const_ptr_variant<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>
{
	typedef variant<const T1*, const T2*, const T3*, const T4*, const T5*, const T6*, const T7*, const T8*, const T9*, const T10*> type;
};

}} //namespace scalpel::utility

#endif

