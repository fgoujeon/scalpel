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

#include "block_declaration.hpp"

#include "alternative_node.hpp"
#include "simple_declaration.hpp"
#include "using_declaration.hpp"
#include "using_directive.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

block_declaration::block_declaration(simple_declaration&& o):
	impl_(new type(std::move(o)))
{
	add(*impl_);
}

block_declaration::block_declaration(asm_definition&& o):
	impl_(new type(std::move(o)))
{
	add(*impl_);
}

block_declaration::block_declaration(namespace_alias_definition&& o):
	impl_(new type(std::move(o)))
{
	add(*impl_);
}

block_declaration::block_declaration(using_declaration&& o):
	impl_(new type(std::move(o)))
{
	add(*impl_);
}

block_declaration::block_declaration(using_directive&& o):
	impl_(new type(std::move(o)))
{
	add(*impl_);
}

block_declaration::block_declaration(const block_declaration& o):
	composite_node(),
	impl_(new type(*o.impl_))
{
	add(*impl_);
}

block_declaration::block_declaration(block_declaration&& o):
	composite_node(),
	impl_(std::move(o.impl_))
{
	add(*impl_);
}

block_declaration::~block_declaration()
{
}

const block_declaration&
block_declaration::operator=(const block_declaration& o)
{
	*impl_ = *o.impl_;
	return *this;
}

void
block_declaration::get(boost::optional<const simple_declaration&>& node) const
{
	impl_->get(node);
}

void
block_declaration::get(boost::optional<const asm_definition&>& node) const
{
	impl_->get(node);
}

void
block_declaration::get(boost::optional<const namespace_alias_definition&>& node) const
{
	impl_->get(node);
}

void
block_declaration::get(boost::optional<const using_declaration&>& node) const
{
	impl_->get(node);
}

void
block_declaration::get(boost::optional<const using_directive&>& node) const
{
	impl_->get(node);
}

}}} //namespace scalpel::cpp::syntax_nodes

