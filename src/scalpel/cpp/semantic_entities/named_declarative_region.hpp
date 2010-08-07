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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_NAMED_DECLARATIVE_REGION_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_NAMED_DECLARATIVE_REGION_HPP

#include "declarative_region.hpp"
#include "named_entity.hpp"

namespace scalpel { namespace cpp { namespace semantic_entities
{

/**
Refers to the named scopes.
*/
struct named_declarative_region: public declarative_region, public named_entity
{
	virtual
	~named_declarative_region(){}

	/**
	Given a declarative region R, is "R::x" a correct expression?
	@return true for classes and namespaces, false otherwise
	*/
	virtual
	bool
	is_open_to_outside() const = 0;
};

}}} //namespace scalpel::cpp::semantic_entities

#endif
