/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2010  Florian Goujeon

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

#include "named_scope_impl.hpp"

namespace scalpel { namespace cpp { namespace semantic_entities
{

named_scope_impl::named_scope_impl()
{
}

named_scope_impl::named_scope_impl(named_scope_impl&& s):
	named_scopes_(std::move(s.named_scopes_)),
	named_entities_(std::move(s.named_entities_))
{
}

const named_scope_impl&
named_scope_impl::operator=(named_scope_impl&& s)
{
	named_scopes_ = std::move(s.named_scopes_);
	named_entities_ = std::move(s.named_entities_);

	return *this;
}

named_scope::named_scope_iterator_range
named_scope_impl::named_scopes()
{
	return named_scopes_.pointers();
}

named_scope::named_scope_const_iterator_range
named_scope_impl::named_scopes() const
{
	return named_scopes_.pointers();
}

void
named_scope_impl::add_to_named_scopes(std::shared_ptr<named_scope> s)
{
	named_scopes_.push_back(s);
}

named_scope::named_entity_iterator_range
named_scope_impl::named_entities()
{
	return named_entities_.pointers();
}

named_scope::named_entity_const_iterator_range
named_scope_impl::named_entities() const
{
	return named_entities_.pointers();
}

void
named_scope_impl::add_to_named_entities(std::shared_ptr<named_entity> n)
{
	named_entities_.push_back(n);
}

}}} //namespace scalpel::cpp::semantic_entities

