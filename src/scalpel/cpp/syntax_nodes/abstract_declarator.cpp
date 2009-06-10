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

#include "abstract_declarator.hpp"

#include "direct_abstract_declarator.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

abstract_declarator::abstract_declarator(ptr_operator_seq&& o):
	impl_(new type(o))
{
	add(*impl_);
}

abstract_declarator::abstract_declarator(direct_abstract_declarator&& o):
	impl_(new type(o))
{
	add(*impl_);
}

abstract_declarator::abstract_declarator(const abstract_declarator& o):
	impl_(new type(*o.impl_))
{
	add(*impl_);
}

abstract_declarator::abstract_declarator(abstract_declarator&& o):
	impl_(std::move(o.impl_))
{
	add(*impl_);
}

abstract_declarator::~abstract_declarator()
{
}

const abstract_declarator&
abstract_declarator::operator=(const abstract_declarator& o)
{
	*impl_ = *o.impl_;
	return *this;
}

}}} //namespace scalpel::cpp::syntax_nodes

