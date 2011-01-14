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

#include "to_type_variant.hpp"

namespace scalpel { namespace cpp { namespace detail { namespace semantic_analysis { namespace semantic_entity_analysis
{

using namespace semantic_entities;

struct: public utility::static_visitor<type_variant>
{
	type_variant
	operator()(std::shared_ptr<class_> t) const
	{
		return type_variant(static_cast<const class_*>(t.get()));
	}

	type_variant
	operator()(std::shared_ptr<typedef_> t) const
	{
		return t->type();
	}
} to_type_variant_impl;

type_variant
to_type_variant(const utility::shared_ptr_variant<semantic_entities::class_, semantic_entities::typedef_>::type& var)
{
	return utility::apply_visitor(to_type_variant_impl, var);
}

}}}}} //namespace scalpel::cpp::detail::semantic_analysis::semantic_entity_analysis

