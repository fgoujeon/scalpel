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

#ifndef SCALPEL_UTILITY_VARIANT_ASSIGN_VISITOR_HPP
#define SCALPEL_UTILITY_VARIANT_ASSIGN_VISITOR_HPP

#include "variant_fwd.hpp"

namespace scalpel { namespace utility
{

template<typename... Ts>
struct assign_visitor
{
	public:
		typedef void return_type;

		assign_visitor(variant<Ts...>& lhs):
			lhs_(lhs)
		{
		}

		template<typename T>
		void
		operator()(const T& rhs) const
		{
			lhs_.template set<T>(rhs);
		}

	private:
		variant<Ts...>& lhs_;
};

}} //namespace scalpel::utility

#endif

