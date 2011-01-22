/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2010  Florian Goujeon

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

#include "get_namespace.hpp"

namespace scalpel { namespace cpp { namespace semantic_analysis { namespace detail { namespace semantic_entity_analysis
{

using namespace semantic_entities;

struct get_namespace_impl_struct: public utility::static_visitor<namespace_&>
{
	namespace_&
	operator()(namespace_* t) const
	{
		return *t;
	}

	namespace_&
	operator()(namespace_alias* t) const
	{
		return t->referred_namespace();
	}
};
get_namespace_impl_struct get_namespace_impl;

namespace_&
get_namespace(const utility::ptr_variant<semantic_entities::namespace_, semantic_entities::namespace_alias>::type& var)
{
	return utility::apply_visitor(get_namespace_impl, var);
}

}}}}} //namespace scalpel::cpp::semantic_analysis::detail::semantic_entity_analysis

