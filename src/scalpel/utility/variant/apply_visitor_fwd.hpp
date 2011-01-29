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

#ifndef SCALPEL_UTILITY_VARIANT_APPLY_VISITOR_FWD_HPP
#define SCALPEL_UTILITY_VARIANT_APPLY_VISITOR_FWD_HPP

#include "variant_fwd.hpp"
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_same.hpp>

namespace scalpel { namespace utility
{

template<class Visitor, typename... Ts>
void
apply_visitor
(
	Visitor& visitor,
	const variant<Ts...>& var,
	typename boost::enable_if
	<
		boost::is_same<typename Visitor::return_type, void>
	>::type* = 0
);

template<class Visitor, typename... Ts>
typename Visitor::return_type
apply_visitor
(
	Visitor& visitor,
	const variant<Ts...>& var,
	typename boost::disable_if
	<
		boost::is_same<typename Visitor::return_type, void>
	>::type* = 0
);

}} //namespace scalpel::utility

#endif

