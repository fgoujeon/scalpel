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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_CONVERSION_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_CONVERSION_HPP

#include <memory>

namespace scalpel { namespace cpp { namespace semantic_entities
{

class expression_t;

template<int Tag>
class conversion
{
	public:
		conversion
		(
			const expression_t& source_value
		);

		conversion(const conversion& rhs);

		const expression_t&
		source_value() const
		{
			return *source_value_;
		}

	private:
		std::unique_ptr<expression_t> source_value_;
};

}}} //namespace scalpel::cpp::semantic_entities

#include "conversion.ipp"

#endif

