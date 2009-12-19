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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_ARRAY_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_ARRAY_HPP

#include "type.hpp"
#include "type_decorator.hpp"
#include <memory>

namespace scalpel { namespace cpp { namespace semantic_entities
{

/**
Represents the const qualifier.
*/
class array:
	public type_decorator
{
	public:
		array(const unsigned int size, std::shared_ptr<const type> decorated_type);

		unsigned int
		size() const;

		std::shared_ptr<const type>
		decorated_type() const;

	private:
		unsigned int size_;
		std::shared_ptr<const type> decorated_type_;
};

}}} //namespace scalpel::cpp::semantic_entities

#endif
