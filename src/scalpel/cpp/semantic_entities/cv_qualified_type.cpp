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

#include "cv_qualified_type.hpp"
#include "type.hpp"

namespace scalpel { namespace cpp { namespace semantic_entities
{

cv_qualified_type::cv_qualified_type(const type_t& qualified_type, const qualification_type qualification):
	qualified_type_(std::unique_ptr<type_t>(new type_t(qualified_type))),
	qualification_(qualification)
{
}

cv_qualified_type::cv_qualified_type(const cv_qualified_type& rhs):
	qualified_type_(std::unique_ptr<type_t>(new type_t(*rhs.qualified_type_))),
	qualification_(rhs.qualification_)
{
}

cv_qualified_type&
cv_qualified_type::operator=(const cv_qualified_type& rhs)
{
	qualified_type_ = std::unique_ptr<type_t>(new type_t(*rhs.qualified_type_));
	qualification_ = rhs.qualification_;
	return *this;
}

const type_t&
cv_qualified_type::qualified_type() const
{
	return *qualified_type_;
}

bool
operator==(const cv_qualified_type& lhs, const cv_qualified_type& rhs)
{
	return
		lhs.qualification() == rhs.qualification() &&
		lhs.qualified_type() == rhs.qualified_type()
	;
}

bool
operator!=(const cv_qualified_type& lhs, const cv_qualified_type& rhs)
{
	return !operator==(lhs, rhs);
}

}}} //namespace scalpel::cpp::semantic_entities

