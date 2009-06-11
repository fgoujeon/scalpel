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

#include "linkage_specification.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

linkage_specification::linkage_specification(declaration_linkage_specification&& o):
	impl_(o)
{
	add(impl_);
}

linkage_specification::linkage_specification(declaration_seq_linkage_specification&& o):
	impl_(o)
{
	add(impl_);
}

linkage_specification::linkage_specification(const linkage_specification& o):
	composite_node(),
	impl_(o.impl_)
{
	add(impl_);
}

linkage_specification::linkage_specification(linkage_specification&& o):
	composite_node(),
	impl_(std::move(o.impl_))
{
	add(impl_);
}

const linkage_specification&
linkage_specification::operator=(const linkage_specification& o)
{
	impl_ = o.impl_;
	return *this;
}

}}} //namespace scalpel::cpp::syntax_nodes

