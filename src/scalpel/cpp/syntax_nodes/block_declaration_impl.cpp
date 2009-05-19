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

#include "block_declaration_impl.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

block_declaration_impl::block_declaration_impl(simple_declaration&& o):
	block_declaration_t(std::move(o))
{
}

block_declaration_impl::block_declaration_impl(using_declaration&& o):
	block_declaration_t(std::move(o))
{
}

block_declaration_impl::block_declaration_impl(using_directive&& o):
	block_declaration_t(std::move(o))
{
}

block_declaration_impl::block_declaration_impl(const block_declaration_impl& o):
	block_declaration_t(static_cast<const block_declaration_t&>(o))
{
}

block_declaration_impl::block_declaration_impl(block_declaration_impl&& o):
	block_declaration_t(static_cast<block_declaration_t&&>(o))
{
}

}}} //namespace scalpel::cpp::syntax_nodes

