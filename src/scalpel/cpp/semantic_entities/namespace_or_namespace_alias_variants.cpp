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

#include "namespace_or_namespace_alias_variants.hpp"
#include "namespace_.hpp"
#include "namespace_alias.hpp"

namespace scalpel { namespace cpp { namespace semantic_entities
{

struct get_namespace_or_namespace_alias_name_impl_struct: public utility::static_visitor<const std::string&>
{
	template<class T>
	const std::string&
	operator()(std::shared_ptr<T> t) const
	{
		return t->name();
	}
};
get_namespace_or_namespace_alias_name_impl_struct get_namespace_or_namespace_alias_name_impl;

const std::string&
get_name(const namespace_or_namespace_alias_shared_ptr_variant var)
{
	return utility::apply_visitor(get_namespace_or_namespace_alias_name_impl, var);
}



struct get_namespace_impl_struct: public utility::static_visitor<std::shared_ptr<namespace_>>
{
	std::shared_ptr<namespace_>
	operator()(std::shared_ptr<namespace_> t) const
	{
		return t;
	}

	std::shared_ptr<namespace_>
	operator()(std::shared_ptr<namespace_alias> t) const
	{
		return t->referred_namespace();
	}
};
get_namespace_impl_struct get_namespace_impl;

std::shared_ptr<namespace_>
get_namespace(const namespace_or_namespace_alias_shared_ptr_variant var)
{
	return utility::apply_visitor(get_namespace_impl, var);
}

}}} //namespace scalpel::cpp::semantic_entities

