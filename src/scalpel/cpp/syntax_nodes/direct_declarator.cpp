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

#include "direct_declarator.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

direct_declarator::direct_declarator
(
	head_node_t&& head,
	tail_sequence_node_t&& tail
):
	type(head, tail)
{
}

direct_declarator::direct_declarator
(
	const direct_declarator& o
):
	type(o)
{
}

direct_declarator::direct_declarator
(
	direct_declarator&& o
):
	type(o)
{
}

}}} //namespace scalpel::cpp::syntax_nodes

