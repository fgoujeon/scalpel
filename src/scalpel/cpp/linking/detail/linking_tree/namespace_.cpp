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

#include "namespace_.hpp"

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

GENERATE_ENTITIES_FUNCTION_TEMPLATE_SPECIALIZATION(namespace_, enum_, enums)
GENERATE_ENTITIES_FUNCTION_TEMPLATE_SPECIALIZATION(namespace_, typedef_, typedefs)
GENERATE_ENTITIES_FUNCTION_TEMPLATE_SPECIALIZATION(namespace_, operator_function, operator_functions)
GENERATE_ENTITIES_FUNCTION_TEMPLATE_SPECIALIZATION(namespace_, simple_function, simple_functions)
GENERATE_ENTITIES_FUNCTION_TEMPLATE_SPECIALIZATION(namespace_, variable, variables)

#undef GENERATE_ENTITIES_FUNCTION_TEMPLATE_SPECIALIZATION

}}}}} //namespace scalpel::cpp::linking::detail

