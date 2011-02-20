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

namespace scalpel { namespace cpp { namespace linking { namespace detail { namespace linking_tree
{

#define GENERATE_ENTITIES_FUNCTION_TEMPLATE_SPECIALIZATION(CLASS, ENTITY_TYPE, VARIABLE) \
template<> \
entity_list<semantic_entities::ENTITY_TYPE>& \
get_entities(CLASS& o) \
{ \
	return o.VARIABLE; \
} \
 \
template<> \
const entity_list<semantic_entities::ENTITY_TYPE>& \
get_entities(const CLASS& o) \
{ \
	return o.VARIABLE; \
}

GENERATE_ENTITIES_FUNCTION_TEMPLATE_SPECIALIZATION(class_, enum_, enums)
GENERATE_ENTITIES_FUNCTION_TEMPLATE_SPECIALIZATION(class_, typedef_, typedefs)
GENERATE_ENTITIES_FUNCTION_TEMPLATE_SPECIALIZATION(class_, constructor, constructors)
GENERATE_ENTITIES_FUNCTION_TEMPLATE_SPECIALIZATION(class_, destructor, destructors)
GENERATE_ENTITIES_FUNCTION_TEMPLATE_SPECIALIZATION(class_, operator_member_function, operator_member_functions)
GENERATE_ENTITIES_FUNCTION_TEMPLATE_SPECIALIZATION(class_, conversion_function, conversion_functions)
GENERATE_ENTITIES_FUNCTION_TEMPLATE_SPECIALIZATION(class_, simple_member_function, simple_member_functions)
GENERATE_ENTITIES_FUNCTION_TEMPLATE_SPECIALIZATION(class_, variable, variables)

#undef GENERATE_ENTITIES_FUNCTION_TEMPLATE_SPECIALIZATION

}}}}} //namespace scalpel::cpp::linking::detail

