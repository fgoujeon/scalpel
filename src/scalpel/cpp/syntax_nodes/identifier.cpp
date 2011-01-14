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

#include "identifier.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

identifier::identifier(const std::string& value):
	leaf_node(value)
{
}

identifier::identifier(std::string&& value):
	leaf_node(value)
{
}

identifier::identifier(const identifier& i):
	leaf_node(i.value())
{
}

identifier::identifier(identifier&& i):
	leaf_node(i.value())
{
}

const identifier&
identifier::operator=(const identifier& i)
{
	value(i.value());

	return *this;
}

const identifier&
identifier::operator=(identifier&& i)
{
	value(i.value());

	return *this;
}

}}} //namespace scalpel::cpp::syntax_nodes

