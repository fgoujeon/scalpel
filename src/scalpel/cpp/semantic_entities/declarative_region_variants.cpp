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

#include "declarative_region_variants.hpp"
#include "namespace_.hpp"
#include "namespace_alias.hpp"
#include "class_.hpp"
#include "functions.hpp"
#include "statement_block.hpp"
#include <scalpel/utility/extern_strings.hpp>

namespace scalpel { namespace cpp { namespace semantic_entities
{

struct get_name_impl_struct: public utility::static_visitor<const std::string&>
{
	template<class T>
	const std::string&
	operator()(T* t) const
	{
		return t->name();
	}

	const std::string&
	operator()(constructor*) const
	{
		return utility::extern_strings::empty;
	}

	const std::string&
	operator()(destructor*) const
	{
		return utility::extern_strings::empty;
	}

	const std::string&
	operator()(operator_function*) const
	{
		return utility::extern_strings::empty;
	}

	const std::string&
	operator()(operator_member_function*) const
	{
		return utility::extern_strings::empty;
	}

	const std::string&
	operator()(conversion_function*) const
	{
		return utility::extern_strings::empty;
	}

	const std::string&
	operator()(statement_block*) const
	{
		return utility::extern_strings::empty;
	}
};
get_name_impl_struct get_name_impl;

const std::string&
get_name(const declarative_region_ptr_variant& var)
{
	return utility::apply_visitor(get_name_impl, var);
}

const std::string&
get_name(const open_declarative_region_ptr_variant& var)
{
	return utility::apply_visitor(get_name_impl, var);
}



struct has_enclosing_declarative_region_impl_struct: public utility::static_visitor<bool>
{
	template<class T>
	bool
	operator()(T* t) const
	{
		return t->has_enclosing_declarative_region();
	}
};
has_enclosing_declarative_region_impl_struct has_enclosing_declarative_region_impl;

bool
has_enclosing_declarative_region(const declarative_region_ptr_variant& var)
{
	return utility::apply_visitor(has_enclosing_declarative_region_impl, var);
}



struct get_enclosing_declarative_region_impl_struct: public utility::static_visitor<declarative_region_ptr_variant>
{
	template<class T>
	declarative_region_ptr_variant
	operator()(T* t) const
	{
		return t->enclosing_declarative_region();
	}
};
get_enclosing_declarative_region_impl_struct get_enclosing_declarative_region_impl;

declarative_region_ptr_variant
get_enclosing_declarative_region(const declarative_region_ptr_variant& var)
{
	return utility::apply_visitor(get_enclosing_declarative_region_impl, var);
}

}}} //namespace scalpel::cpp::semantic_entities

