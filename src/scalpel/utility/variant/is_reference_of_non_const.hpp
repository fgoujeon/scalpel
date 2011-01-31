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

#ifndef SCALPEL_UTILITY_VARIANT_IS_REFERENCE_OF_NON_CONST_HPP
#define SCALPEL_UTILITY_VARIANT_IS_REFERENCE_OF_NON_CONST_HPP

#include <boost/type_traits/integral_constant.hpp>

namespace scalpel { namespace utility
{

template<typename T>
struct is_reference_of_non_const: public boost::false_type{};

template<typename T>
struct is_reference_of_non_const<T&>: public boost::true_type{};

template<typename T>
struct is_reference_of_non_const<T const&>: public boost::false_type{};

}} //namespace scalpel::utility

#endif

