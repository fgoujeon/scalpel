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

#include "declarative_region_variants.hpp"
#include "namespace_.hpp"
#include "class_.hpp"
#include "simple_function.hpp"

namespace scalpel { namespace cpp { namespace semantic_entities
{

struct get_name_impl_struct: public utility::static_visitor<const std::string&>
{
	template<class T>
	const std::string&
	operator()(std::shared_ptr<T> t) const
	{
		return t->name();
	}
};
get_name_impl_struct get_name_impl;

const std::string&
get_name(const declarative_region_shared_ptr_variant& var)
{
	return utility::apply_visitor(get_name_impl, var);
}

const std::string&
get_name(const open_declarative_region_shared_ptr_variant& var)
{
	return utility::apply_visitor(get_name_impl, var);
}



struct has_declarative_region_impl_struct: public utility::static_visitor<bool>
{
	template<class T>
	bool
	operator()(std::shared_ptr<T> t) const
	{
		return t->has_declarative_region();
	}
};
has_declarative_region_impl_struct has_declarative_region_impl;

bool
has_declarative_region(const declarative_region_shared_ptr_variant& var)
{
	return utility::apply_visitor(has_declarative_region_impl, var);
}



struct get_declarative_region_impl_struct: public utility::static_visitor<declarative_region_shared_ptr_variant>
{
	template<class T>
	declarative_region_shared_ptr_variant
	operator()(std::shared_ptr<T> t) const
	{
		return t->declarative_region();
	}
};
get_declarative_region_impl_struct get_declarative_region_impl;

declarative_region_shared_ptr_variant
get_declarative_region(const declarative_region_shared_ptr_variant& var)
{
	return utility::apply_visitor(get_declarative_region_impl, var);
}



struct to_shared_ptr_variant_impl_struct: public utility::static_visitor<declarative_region_shared_ptr_variant>
{
	template<class T>
	declarative_region_shared_ptr_variant
	operator()(std::weak_ptr<T> t) const
	{
		return std::shared_ptr<T>(t);
	}
};
to_shared_ptr_variant_impl_struct to_shared_ptr_variant_impl;

declarative_region_shared_ptr_variant
to_shared_ptr_variant(const declarative_region_weak_ptr_variant& var)
{
	return utility::apply_visitor(to_shared_ptr_variant_impl, var);
}



struct to_weak_ptr_variant_impl_struct: public utility::static_visitor<declarative_region_weak_ptr_variant>
{
	template<class T>
	declarative_region_weak_ptr_variant
	operator()(std::shared_ptr<T> t) const
	{
		return std::weak_ptr<T>(t);
	}
};
to_weak_ptr_variant_impl_struct to_weak_ptr_variant_impl;

declarative_region_weak_ptr_variant
to_weak_ptr_variant(const declarative_region_shared_ptr_variant& var)
{
	return utility::apply_visitor(to_weak_ptr_variant_impl, var);
}

}}} //namespace scalpel::cpp::semantic_entities

