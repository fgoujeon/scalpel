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

#include "type_variants.hpp"

namespace scalpel { namespace cpp { namespace semantic_entities
{

struct get_named_compound_type_name_impl_struct: public utility::static_visitor<const std::string&>
{
	template<class T>
	const std::string&
	operator()(std::shared_ptr<T> t) const
	{
		return t->name();
	}
};
get_named_compound_type_name_impl_struct get_named_compound_type_name_impl;

const std::string&
get_name(const named_compound_type_shared_ptr_variant var)
{
	return utility::apply_visitor(get_named_compound_type_name_impl, var);
}



struct to_type_shared_ptr_variant_impl_struct: public utility::static_visitor<type_shared_ptr_variant>
{
	template<class T>
	type_shared_ptr_variant
	operator()(std::shared_ptr<T> t) const
	{
		return type_shared_ptr_variant(std::shared_ptr<const T>(t));
	}
};
to_type_shared_ptr_variant_impl_struct to_type_shared_ptr_variant_impl;

type_shared_ptr_variant
to_type_shared_ptr_variant(const named_compound_type_shared_ptr_variant var)
{
	return utility::apply_visitor(to_type_shared_ptr_variant_impl, var);
}

}}} //namespace scalpel::cpp::semantic_entities

