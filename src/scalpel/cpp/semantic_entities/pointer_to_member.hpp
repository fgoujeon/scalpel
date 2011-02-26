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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_POINTER_TO_MEMBER_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_POINTER_TO_MEMBER_HPP

#include "type_variant_fwd.hpp"
#include <scalpel/utility/ptr_variant.hpp>
#include <memory>

namespace scalpel { namespace cpp { namespace semantic_entities
{

/**
Represents the const qualifier.
*/
class pointer_to_member
{
	public:
		typedef typename utility::ptr_variant<class_, member_class>::type parent_class_t;

		pointer_to_member
		(
			const type_variant& qualified_type,
			const parent_class_t& member_class
		);

		pointer_to_member(const pointer_to_member& rhs);

		pointer_to_member&
		operator=(const pointer_to_member& rhs);

		const type_variant&
		qualified_type() const;

		const parent_class_t&
		parent_class() const
		{
			return parent_class_;
		}

	private:
		std::unique_ptr<type_variant> qualified_type_;
		parent_class_t parent_class_;
};

bool
operator==(const pointer_to_member& lhs, const pointer_to_member& rhs);

bool
operator!=(const pointer_to_member& lhs, const pointer_to_member& rhs);

}}} //namespace scalpel::cpp::semantic_entities

#endif

