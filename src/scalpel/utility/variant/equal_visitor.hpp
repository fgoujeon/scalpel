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

#ifndef SCALPEL_UTILITY_VARIANT_EQUAL_VISITOR_HPP
#define SCALPEL_UTILITY_VARIANT_EQUAL_VISITOR_HPP

#include "apply_visitor_fwd.hpp"
#include "variant_fwd.hpp"

namespace scalpel { namespace utility
{

template<typename T>
struct complete_equal_visitor
{
	public:
		typedef bool return_type;

		complete_equal_visitor(const T& rhs):
			rhs_(rhs)
		{
		}

		bool
		operator()(const T& lhs) const
		{
			return lhs == rhs_;
		}

		template<typename U>
		bool
		operator()(const U&) const
		{
			return false;
		}

	private:
		const T& rhs_;
};

template<typename... Ts>
struct partial_equal_visitor
{
	public:
		typedef bool return_type;

		partial_equal_visitor(const variant<Ts...>& lhs):
			lhs_(lhs)
		{
		}

		template<typename T>
		bool
		operator()(const T& rhs) const
		{
			complete_equal_visitor<T> visitor(rhs);
			return apply_visitor(visitor, lhs_);
		}

	private:
		const variant<Ts...>& lhs_;
};

}} //namespace scalpel::utility

#endif

