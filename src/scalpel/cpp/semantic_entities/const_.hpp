/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008, 2009  Florian Goujeon

This file is part of Scalpel.

Scalpel is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Scalpel is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Scalpel.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_CONST_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_CONST_HPP

#include <memory>
#include "type.hpp"
#include "type_decorator.hpp"

namespace scalpel { namespace cpp { namespace semantic_entities
{

/**
Represents the const qualifier.
*/
class const_:
	public type_decorator
{
	public:
		const_(const type& decorated_type);

		const type&
		decorated_type() const;

	private:
		const type& decorated_type_;
};

}}} //namespace scalpel::cpp::semantic_entities

#endif