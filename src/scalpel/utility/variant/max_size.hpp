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

#ifndef SCALPEL_UTILITY_VARIANT_MAX_SIZE_HPP
#define SCALPEL_UTILITY_VARIANT_MAX_SIZE_HPP

#include "custom_sizeof.hpp"

namespace scalpel { namespace utility
{

template<typename... Ts>
struct max_size;

template<>
struct max_size<>
{
	static const unsigned int value = 0;
};

template<typename T, typename... Ts>
struct max_size<T, Ts...>
{
	static const unsigned int current_type_size = custom_sizeof<T>::value;
	static const unsigned int next_type_size = max_size<Ts...>::value;
	static const unsigned int value = current_type_size > next_type_size ? current_type_size : next_type_size;
};

}} //namespace scalpel::utility

#endif

