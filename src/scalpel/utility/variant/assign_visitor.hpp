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

#ifndef SCALPEL_UTILITY_VARIANT_ASSIGN_VISITOR_HPP
#define SCALPEL_UTILITY_VARIANT_ASSIGN_VISITOR_HPP

#include "variant.hpp"
#include "static_visitor.hpp"

namespace scalpel { namespace utility
{

template<typename... Ts>
struct assign_visitor: public static_visitor<void>
{
	public:
		assign_visitor(variant<Ts...>& lhs, const bool clear = true):
			lhs_(lhs),
			clear_(clear)
		{
		}

		template<typename T>
		void
		operator()(const T& value) const
		{
			lhs_.template set<T>(value, clear_);
		}

		template<typename T>
		void
		operator()(T& value) const
		{
			lhs_.template set<T>(value, clear_);
		}

	private:
		variant<Ts...>& lhs_;
		const bool clear_;
};

}} //namespace scalpel::utility

#endif

