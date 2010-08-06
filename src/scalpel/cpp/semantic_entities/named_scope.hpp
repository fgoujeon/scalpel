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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_NAMED_SCOPE_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_NAMED_SCOPE_HPP

#include "scope.hpp"
#include "named_entity.hpp"

namespace scalpel { namespace cpp { namespace semantic_entities
{

/**
Refers to the named scopes.
*/
struct named_scope: public scope, public named_entity
{
	virtual
	~named_scope(){}

	/**
	Must the scope be considered by the name_lookup::find_scope() functions?
	@return true for classes and namespaces, false otherwise
	*/
	virtual
	bool
	considered_by_scope_find() const = 0;
};

}}} //namespace scalpel::cpp::semantic_entities

#endif
