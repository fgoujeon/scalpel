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

#include "class_.hpp"
#include "macros/get_entity_list.hpp"

namespace scalpel { namespace cpp { namespace linking { namespace detail { namespace linking_tree
{

GENERATE_GET_ENTITY_LIST_SPECIALIZATION(class_, enum_, enums)
GENERATE_GET_ENTITY_LIST_SPECIALIZATION(class_, typedef_, typedefs)
GENERATE_GET_ENTITY_LIST_SPECIALIZATION(class_, constructor, constructors)
GENERATE_GET_ENTITY_LIST_SPECIALIZATION(class_, destructor, destructors)
GENERATE_GET_ENTITY_LIST_SPECIALIZATION(class_, operator_member_function, operator_member_functions)
GENERATE_GET_ENTITY_LIST_SPECIALIZATION(class_, conversion_function, conversion_functions)
GENERATE_GET_ENTITY_LIST_SPECIALIZATION(class_, simple_member_function, simple_member_functions)
GENERATE_GET_ENTITY_LIST_SPECIALIZATION(class_, variable, variables)

}}}}} //namespace scalpel::cpp::linking::detail

#include "macros/get_entity_list_undef.hpp"

