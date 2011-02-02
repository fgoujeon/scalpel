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

#ifndef SCALPEL_UTILITY_VARIANT_APPLY_VISITOR_HPP
#define SCALPEL_UTILITY_VARIANT_APPLY_VISITOR_HPP

#include "apply_visitor_fwd.hpp"
#include "variant.hpp"
#include <cassert>

namespace scalpel { namespace utility
{

namespace impl
{
	template<class Visitor, class Variant, typename... Ts>
	struct apply_void_visitor_impl;

	template<class Visitor, class Variant>
	struct apply_void_visitor_impl<Visitor, Variant>
	{
		static const unsigned int index = 0;

		static
		void
		visit
		(
			Visitor&,
			const Variant&
		)
		{
			//won't be called
			assert(false);
			throw "";
		}
	};

	template<class Visitor, class Variant, typename T, typename... Ts>
	struct apply_void_visitor_impl<Visitor, Variant, T, Ts...>
	{
		static const unsigned int index = apply_void_visitor_impl<Visitor, Variant, Ts...>::index + 1;

		static
		void
		visit
		(
			Visitor& visitor,
			const Variant& var
		)
		{
			if(var.type_index() == index)
			{
				visitor(var.template get<T>());
			}
			else
			{
				apply_void_visitor_impl<Visitor, Variant, Ts...>::visit(visitor, var);
			}
		}
	};



	template<class Visitor, class Variant, typename... Ts>
	struct apply_return_visitor_impl;

	template<class Visitor, class Variant>
	struct apply_return_visitor_impl<Visitor, Variant>
	{
		static const unsigned int index = 0;

		static
		typename Visitor::result_type
		visit
		(
			Visitor&,
			const Variant&
		)
		{
			//won't be called
			assert(false);
			throw "";
		}
	};

	template<class Visitor, class Variant, typename T, typename... Ts>
	struct apply_return_visitor_impl<Visitor, Variant, T, Ts...>
	{
		static const unsigned int index = apply_return_visitor_impl<Visitor, Variant, Ts...>::index + 1;

		static
		typename Visitor::result_type
		visit
		(
			Visitor& visitor,
			const Variant& var
		)
		{
			if(var.type_index() == index)
			{
				return visitor(var.template get<T>());
			}
			else
			{
				return apply_return_visitor_impl<Visitor, Variant, Ts...>::visit(visitor, var);
			}
		}
	};
}



template<class Visitor, typename... Ts>
void
apply_visitor
(
	Visitor& visitor,
	const variant<Ts...>& var,
	typename boost::enable_if
	<
		boost::is_same<typename Visitor::result_type, void>
	>::type* = 0
)
{
	impl::apply_void_visitor_impl<Visitor, variant<Ts...>, Ts...>::visit(visitor, var);
}

template<class Visitor, typename... Ts>
typename Visitor::result_type
apply_visitor
(
	Visitor& visitor,
	const variant<Ts...>& var,
	typename boost::disable_if
	<
		boost::is_same<typename Visitor::result_type, void>
	>::type* = 0
)
{
	return impl::apply_return_visitor_impl<Visitor, variant<Ts...>, Ts...>::visit(visitor, var);
}

}} //namespace scalpel::utility

#endif

