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

#ifndef SCALPEL_UTILITY_VARIANT_CLEAR_AND_SET_VISITOR_HPP
#define SCALPEL_UTILITY_VARIANT_CLEAR_AND_SET_VISITOR_HPP

#include "variant_fwd.hpp"

namespace scalpel { namespace utility
{

template<unsigned int Size, typename Set>
struct clear_and_set_visitor
{
	public:
		typedef void return_type;

		clear_and_set_visitor(any_container<Size>& container, const Set& value):
			container_(container),
			value_(value)
		{
		}

		template<typename Clear>
		void
		operator()(const Clear&) const
		{
			container_.template clear_and_set<Clear, Set>(value_);
		}

	private:
		any_container<Size>& container_;
		const Set& value_;
};

}} //namespace scalpel::utility

#endif

