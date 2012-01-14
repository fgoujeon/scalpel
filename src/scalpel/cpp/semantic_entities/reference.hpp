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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_REFERENCE_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_REFERENCE_HPP

#include "type_fwd.hpp"
#include <memory>

namespace scalpel { namespace cpp { namespace semantic_entities
{

/**
Represents the const qualifier.
*/
class reference
{
	public:
		reference(const type_t& qualified_type);

		reference(const reference& rhs);

		reference&
		operator=(const reference& rhs);

		const type_t&
		qualified_type() const;

	private:
		std::unique_ptr<type_t> qualified_type_;
};

bool
operator==(const reference& lhs, const reference& rhs);

bool
operator!=(const reference& lhs, const reference& rhs);

}}} //namespace scalpel::cpp::semantic_entities

#endif

