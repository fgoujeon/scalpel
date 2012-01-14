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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_ENTITY_ALIAS_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_ENTITY_ALIAS_HPP

#include "member_accessibility.hpp"
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>

#define ENTITY_ALIAS(CLASS_NAME, IS_MEMBER) \
template<class Entity> \
class CLASS_NAME \
{ \
	public: \
		CLASS_NAME \
		( \
			Entity& referred_entity BOOST_PP_COMMA_IF(IS_MEMBER) \
			BOOST_PP_IIF(IS_MEMBER, const member_accessibility access,) \
		); \
 \
		CLASS_NAME(const CLASS_NAME& rhs); \
 \
		CLASS_NAME& \
		operator=(const CLASS_NAME& rhs); \
 \
		Entity& \
		referred_entity() \
		{ \
			return *referred_entity_; \
		} \
 \
		const Entity& \
		referred_entity() const \
		{ \
			return *referred_entity_; \
		} \
 \
		BOOST_PP_IIF \
		( \
			IS_MEMBER, \
			member_accessibility \
			accessibility() const \
			{ \
				return accessibility_; \
			}, \
		) \
 \
	private: \
		Entity* referred_entity_; \
		BOOST_PP_IIF \
		( \
			IS_MEMBER, \
			member_accessibility accessibility_;, \
		) \
};

namespace scalpel { namespace cpp { namespace semantic_entities
{

ENTITY_ALIAS(entity_alias, 0)
ENTITY_ALIAS(member_entity_alias, 1)

}}} //namespace scalpel::cpp::semantic_entities

#undef ENTITY_ALIAS

#include "entity_alias.ipp"

#endif

