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

bool
has_declarative_region(const declarative_region_shared_ptr_variant& var)
{
	if(auto opt_shared_ptr = utility::get<std::shared_ptr<namespace_>>(&var))
		return (*opt_shared_ptr)->has_declarative_region();
	else if(auto opt_shared_ptr = utility::get<std::shared_ptr<class_>>(&var))
		return (*opt_shared_ptr)->has_declarative_region();
	else if(auto opt_shared_ptr = utility::get<std::shared_ptr<simple_function>>(&var))
		return (*opt_shared_ptr)->has_declarative_region();
	else
		throw "";
}

declarative_region_shared_ptr_variant
get_declarative_region(const declarative_region_shared_ptr_variant& var)
{
	if(auto opt_shared_ptr = utility::get<std::shared_ptr<namespace_>>(&var))
		return (*opt_shared_ptr)->declarative_region();
	else if(auto opt_shared_ptr = utility::get<std::shared_ptr<class_>>(&var))
		return (*opt_shared_ptr)->declarative_region();
	else if(auto opt_shared_ptr = utility::get<std::shared_ptr<simple_function>>(&var))
		return (*opt_shared_ptr)->declarative_region();
	else
		throw "";
}

declarative_region_shared_ptr_variant
to_shared_ptr_variant(const declarative_region_weak_ptr_variant& var)
{
	if(auto opt_shared_ptr = utility::get<std::weak_ptr<namespace_>>(&var))
		return std::shared_ptr<namespace_>(*opt_shared_ptr);
	else if(auto opt_shared_ptr = utility::get<std::weak_ptr<class_>>(&var))
		return std::shared_ptr<class_>(*opt_shared_ptr);
	else if(auto opt_shared_ptr = utility::get<std::weak_ptr<simple_function>>(&var))
		return std::shared_ptr<simple_function>(*opt_shared_ptr);

	throw "";
}

declarative_region_weak_ptr_variant
to_weak_ptr_variant(const declarative_region_shared_ptr_variant& var)
{
	if(auto opt_weak_ptr = utility::get<std::shared_ptr<namespace_>>(&var))
		return std::weak_ptr<namespace_>(*opt_weak_ptr);
	else if(auto opt_weak_ptr = utility::get<std::shared_ptr<class_>>(&var))
		return std::weak_ptr<class_>(*opt_weak_ptr);
	else if(auto opt_weak_ptr = utility::get<std::shared_ptr<simple_function>>(&var))
		return std::weak_ptr<simple_function>(*opt_weak_ptr);

	throw "";
}

}}} //namespace scalpel::cpp::semantic_entities

