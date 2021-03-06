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

#ifndef SCALPEL_UTILITY_VARIANT_VARIANT_HPP
#define SCALPEL_UTILITY_VARIANT_VARIANT_HPP

#include "select_type.hpp"
#include "max_size.hpp"
#include "any_container.hpp"
#include "assign_visitor.hpp"
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <boost/utility/enable_if.hpp>

namespace scalpel { namespace utility
{

template<typename... Ts>
class variant
{
	public:
		static const unsigned int size = max_size<Ts...>::value;

		template<typename... T2s>
		friend struct assign_visitor;

		//general case
		template<typename U>
		variant
		(
			const U& value,
			typename boost::disable_if<boost::is_const<U>>::type* = 0,
			typename boost::disable_if<boost::is_reference<U>>::type* = 0,
			typename boost::disable_if<boost::is_same<U, variant>>::type* = 0
		);

		//for noncopyable movable types
		template<typename U>
		variant
		(
			U&& value,
			typename boost::disable_if<boost::is_const<U>>::type* = 0,
			typename boost::disable_if<boost::is_reference<U>>::type* = 0,
			typename boost::disable_if<boost::is_same<U, variant>>::type* = 0
		);

		variant(const variant& rhs);

		~variant();

		variant&
		operator=(const variant& rhs);

		//general case
		template<typename U>
		typename boost::disable_if<boost::is_same<U, variant<Ts...>>, variant<Ts...>&>::type
		operator=(const U& value);

		template<typename U>
		U&
		get();

		template<typename U>
		const U&
		get() const;

		template<typename U>
		U*
		get_optional();

		template<typename U>
		const U*
		get_optional() const;

	private:
		//general case
		template<typename U>
		void
		set
		(
			const U& value,
			const bool clear = true
		);

		//for noncopyable movable types
		template<typename U>
		void
		set2
		(
			U&& value,
			const bool clear = true
		);

	public:
		unsigned int
		type_index() const
		{
			return type_index_;
		}

	private:
		any_container<size> container_;
		unsigned int type_index_;
};

template<typename... Ts>
bool
operator==(const variant<Ts...>& lhs, const variant<Ts...>& rhs);

template<typename... Ts>
bool
operator!=(const variant<Ts...>& lhs, const variant<Ts...>& rhs);

template<typename... Ts>
bool
operator<(const variant<Ts...>& lhs, const variant<Ts...>& rhs);

}} //namespace scalpel::utility

#include "variant.ipp"

#endif

