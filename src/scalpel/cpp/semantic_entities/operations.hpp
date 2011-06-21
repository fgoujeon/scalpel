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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_OPERATIONS_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_OPERATIONS_HPP

#include "binary_operation.hpp"

namespace scalpel { namespace cpp { namespace semantic_entities
{

enum class operation_tag
{
	MULTIPLICATION,
	DIVISION,
	MODULO,
	ADDITION,
	SUBTRACTION
};

typedef
	binary_operation<static_cast<int>(operation_tag::MULTIPLICATION)>
	multiplication
;

typedef
	binary_operation<static_cast<int>(operation_tag::DIVISION)>
	division
;

typedef
	binary_operation<static_cast<int>(operation_tag::MODULO)>
	modulo
;

typedef
	binary_operation<static_cast<int>(operation_tag::ADDITION)>
	addition
;

typedef
	binary_operation<static_cast<int>(operation_tag::SUBTRACTION)>
	subtraction
;

}}} //namespace scalpel::cpp::semantic_entities

#endif

