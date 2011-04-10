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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_ENTITY_ALIAS_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_ENTITY_ALIAS_HPP

#include <string>

namespace scalpel { namespace cpp { namespace semantic_entities
{

/**
Represents an entity alias introduced by a using declaration.
*/
template<class Entity>
class entity_alias
{
	public:
		entity_alias
		(
			Entity& referred_entity
		);

		entity_alias(const entity_alias& rhs);

		entity_alias&
		operator=(const entity_alias& rhs);

		Entity&
		referred_entity()
		{
			return *referred_entity_;
		}

		const Entity&
		referred_entity() const
		{
			return *referred_entity_;
		}

	private:
		Entity* referred_entity_;
};

template<class Entity>
entity_alias<Entity>::entity_alias
(
	Entity& referred_entity
):
	referred_entity_(&referred_entity)
{
}

template<class Entity>
entity_alias<Entity>::entity_alias(const entity_alias& rhs):
	referred_entity_(rhs.referred_entity_)
{
}

template<class Entity>
entity_alias<Entity>&
entity_alias<Entity>::operator=(const entity_alias& rhs)
{
	referred_entity_ = rhs.referred_entity_;
	return *this;
}

}}} //namespace scalpel::cpp::semantic_entities

#endif

