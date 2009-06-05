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

#include "declaration.hpp"

#include "block_declaration.hpp"
#include "function_definition.hpp"
#include "template_declaration.hpp"
//#include "explicit_instantiation.hpp"
//#include "explicit_specialization.hpp"
//#include "linkage_specification.hpp"
#include "namespace_definition.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

declaration::declaration(block_declaration&& o):
	impl_(new type(o))
{
	add(*impl_);
}

declaration::declaration(function_definition&& o):
	impl_(new type(o))
{
	add(*impl_);
}

declaration::declaration(template_declaration&& o):
	impl_(new type(o))
{
	add(*impl_);
}

//declaration::declaration(explicit_instantiation&& o)

//declaration::declaration(explicit_specialization&& o)

//declaration::declaration(linkage_specification&& o)

declaration::declaration(namespace_definition&& o):
	impl_(new type(o))
{
	add(*impl_);
}

declaration::declaration(const declaration& o):
	composite_node(),
	impl_(new type(*o.impl_))
{
	add(*impl_);
}

declaration::declaration(declaration&& o):
	composite_node(),
	impl_(std::move(o.impl_))
{
	add(*impl_);
}

declaration::~declaration()
{
}

const declaration&
declaration::operator=(const declaration& o)
{
	*impl_ = *o.impl_;
	return *this;
}

void
declaration::get(boost::optional<const head_node_t&>& o) const
{
	impl_->get(o);
}

void
declaration::get(boost::optional<const function_definition&>& o) const
{
	impl_->get(o);
}

void
declaration::get(boost::optional<const template_declaration&>& o) const
{
	impl_->get(o);
}

void
declaration::get(boost::optional<const namespace_definition&>& o) const
{
	impl_->get(o);
}

}}} //namespace scalpel::cpp::syntax_nodes

