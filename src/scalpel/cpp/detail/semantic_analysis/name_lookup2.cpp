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

#include "name_lookup2.hpp"
#include <algorithm>
#include <functional>
#include <iostream>

namespace scalpel { namespace cpp { namespace detail { namespace semantic_analysis
{

//
//get_members() specializations
//

#define GENERATE_GET_MEMBERS_SPECIALIZATION(MEMBER_TYPE, PARENT_TYPE, PARENT_MEMBER_FUNCTION) \
template<> \
typename utility::shared_ptr_vector<semantic_entities::MEMBER_TYPE>::range \
name_lookup2::get_members<semantic_entities::MEMBER_TYPE, semantic_entities::PARENT_TYPE>(std::shared_ptr<semantic_entities::PARENT_TYPE> parent) \
{ \
	return parent->PARENT_MEMBER_FUNCTION(); \
}

#define GENERATE_GET_MEMBERS_SPECIALIZATION_EMPTY(MEMBER_TYPE, PARENT_TYPE) \
template<> \
typename utility::shared_ptr_vector<semantic_entities::MEMBER_TYPE>::range \
name_lookup2::get_members<semantic_entities::MEMBER_TYPE, semantic_entities::PARENT_TYPE>(std::shared_ptr<semantic_entities::PARENT_TYPE>) \
{ \
	return utility::shared_ptr_vector<semantic_entities::MEMBER_TYPE>::range(); \
}

GENERATE_GET_MEMBERS_SPECIALIZATION(namespace_, namespace_, namespaces)
GENERATE_GET_MEMBERS_SPECIALIZATION(class_, namespace_, classes)
GENERATE_GET_MEMBERS_SPECIALIZATION(simple_function, namespace_, simple_functions)
GENERATE_GET_MEMBERS_SPECIALIZATION(variable, namespace_, variables)

GENERATE_GET_MEMBERS_SPECIALIZATION_EMPTY(namespace_, class_)
GENERATE_GET_MEMBERS_SPECIALIZATION(class_, class_, nested_classes)
GENERATE_GET_MEMBERS_SPECIALIZATION(simple_function, class_, simple_functions)
GENERATE_GET_MEMBERS_SPECIALIZATION(variable, class_, variables)

}}}} //namespace scalpel::cpp::detail::semantic_analysis

