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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_MEMBER_ACCESS_EXPRESSION_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_MEMBER_ACCESS_EXPRESSION_HPP

#include <memory>

namespace scalpel { namespace cpp { namespace semantic_entities
{

class expression_t;

template<class Member>
class member_access_expression
{
	public:
		member_access_expression
		(
			const expression_t& object,
			Member& member
		);

		member_access_expression(const member_access_expression& rhs);

		const expression_t&
		object() const
		{
			return *object_;
		}

		Member&
		member() const
		{
			return member_;
		}

	private:
		std::unique_ptr<expression_t> object_;
		Member& member_;
};

}}} //namespace scalpel::cpp::semantic_entities

#include "member_access_expression.ipp"

#endif


