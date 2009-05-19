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

#include "member_specification_part.hpp"

#include "member_specification_part_impl.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

member_specification_part::member_specification_part(member_declaration&& o):
	impl_(new member_specification_part_impl(std::move(o)))
{
	add(*impl_);
}

member_specification_part::member_specification_part(member_specification_access_specifier&& o):
	impl_(new member_specification_part_impl(std::move(o)))
{
	add(*impl_);
}

member_specification_part::member_specification_part(const member_specification_part& o):
	composite_node(),
	impl_(new member_specification_part_impl(*o.impl_))
{
	add(*impl_);
}

member_specification_part::member_specification_part(member_specification_part&& o):
	composite_node(),
	impl_(new member_specification_part_impl(std::move(*o.impl_)))
{
	add(*impl_);
}

member_specification_part::~member_specification_part()
{
	delete impl_;
}

const member_specification_part&
member_specification_part::operator=(const member_specification_part& o)
{
	*impl_ = *o.impl_;
	return *this;
}

}}} //namespace scalpel::cpp::syntax_nodes

