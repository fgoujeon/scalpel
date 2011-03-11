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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_GENERIC_FUNCTIONS_DETAIL_IS_DEFINIED_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_GENERIC_FUNCTIONS_DETAIL_IS_DEFINIED_HPP

#include <scalpel/cpp/semantic_graph.hpp>

namespace scalpel { namespace cpp { namespace semantic_entities { namespace generic_functions { namespace detail
{

bool
is_defined(const namespace_&)
{
	return true;
}

bool
is_defined(const class_& entity)
{
	return entity.complete();
}

bool
is_defined(const member_class& entity)
{
	return entity.complete();
}

bool
is_defined(const enum_&)
{
	return true;
}

bool
is_defined(const member_enum&)
{
	return true;
}

bool
is_defined(const typedef_&)
{
	return true;
}

bool
is_defined(const member_typedef&)
{
	return true;
}

bool
is_defined(const variable&)
{
	return true;
}

bool
is_defined(const member_variable&)
{
	return true;
}

template<class Entity>
bool
is_defined(const Entity& entity)
{
	return entity.defined();
}

}}}}} //namespace scalpel::cpp::semantic_entities::generic_functions::detail

#endif

