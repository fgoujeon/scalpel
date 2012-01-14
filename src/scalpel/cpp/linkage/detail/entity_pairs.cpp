/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2012  Florian Goujeon

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

#include "entity_pairs.hpp"

#define GENERATE_GET_PAIRS_SPECIALIZATION(ENTITY_TYPE, VARIABLE) \
template<> \
std::vector<old_and_new_entity_pair<semantic_entities::ENTITY_TYPE>>& \
entity_pairs::get_pairs_of_type<semantic_entities::ENTITY_TYPE>() \
{ \
	return VARIABLE; \
} \
 \
template<> \
const std::vector<old_and_new_entity_pair<semantic_entities::ENTITY_TYPE>>& \
entity_pairs::get_pairs_of_type<semantic_entities::ENTITY_TYPE>() const \
{ \
	return VARIABLE; \
}

namespace scalpel { namespace cpp { namespace linkage { namespace detail
{

GENERATE_GET_PAIRS_SPECIALIZATION(class_, class_pairs)
GENERATE_GET_PAIRS_SPECIALIZATION(member_class, member_class_pairs)
GENERATE_GET_PAIRS_SPECIALIZATION(union_, union_pairs)
GENERATE_GET_PAIRS_SPECIALIZATION(member_union, member_union_pairs)
GENERATE_GET_PAIRS_SPECIALIZATION(anonymous_union, anonymous_union_pairs)
GENERATE_GET_PAIRS_SPECIALIZATION(anonymous_member_union, anonymous_member_union_pairs)
GENERATE_GET_PAIRS_SPECIALIZATION(variable, variable_pairs)

}}}} //namespace scalpel::cpp::linkage::detail

#undef GENERATE_GET_PAIRS_SPECIALIZATION

