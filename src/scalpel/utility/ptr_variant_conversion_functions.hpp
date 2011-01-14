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

#ifndef SCALPEL_UTILITY_PTR_VARIANT_CONVERSION_FUNCTIONS_HPP
#define SCALPEL_UTILITY_PTR_VARIANT_CONVERSION_FUNCTIONS_HPP

#include "shared_ptr_variant.hpp"
#include "weak_ptr_variant.hpp"

namespace scalpel { namespace utility
{

template<typename... Ts>
struct to_weak_ptr_variant_impl_struct: public utility::static_visitor<typename weak_ptr_variant<Ts...>::type>
{
	template<class T>
	typename weak_ptr_variant<Ts...>::type
	operator()(std::shared_ptr<T> t) const
	{
		return std::weak_ptr<T>(t);
	}
};

template<typename... Ts>
typename weak_ptr_variant<Ts...>::type
to_weak_ptr_variant(const basic_variant<add_shared_ptr, Ts...>& var)
{
	to_weak_ptr_variant_impl_struct<Ts...> visitor;
	return utility::apply_visitor(visitor, var);
}



template<typename... Ts>
struct to_shared_ptr_variant_impl_struct: public utility::static_visitor<typename shared_ptr_variant<Ts...>::type>
{
	template<class T>
	typename shared_ptr_variant<Ts...>::type
	operator()(std::weak_ptr<T> t) const
	{
		return std::shared_ptr<T>(t);
	}
};

template<typename... Ts>
typename shared_ptr_variant<Ts...>::type
to_shared_ptr_variant(const basic_variant<add_weak_ptr, Ts...>& var)
{
	to_shared_ptr_variant_impl_struct<Ts...> visitor;
	return utility::apply_visitor(visitor, var);
}

}} //namespace scalpel::utility

#endif

