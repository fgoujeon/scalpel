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

#include "scope_impl.hpp"

namespace scalpel { namespace cpp { namespace semantic_entities
{

scope_impl::scope_impl()
{
}

scope_impl::scope_impl(scope_impl&& s):
	scopes_(std::move(s.scopes_)),
	named_entities_(std::move(s.named_entities_))
{
}

const scope_impl&
scope_impl::operator=(scope_impl&& s)
{
	scopes_ = std::move(s.scopes_);
	named_entities_ = std::move(s.named_entities_);

	return *this;
}

scope::scope_iterator_range
scope_impl::scopes()
{
	return scopes_;
}

scope::scope_const_iterator_range
scope_impl::scopes() const
{
	return scopes_;
}

void
scope_impl::add_to_scopes(scope& s)
{
	scopes_.push_back(&s);
}

scope::named_entity_iterator_range
scope_impl::named_entities()
{
	return named_entities_;
}

scope::named_entity_const_iterator_range
scope_impl::named_entities() const
{
	return named_entities_;
}

void
scope_impl::add_to_named_entities(named_entity& n)
{
	named_entities_.push_back(&n);
}

}}} //namespace scalpel::cpp::semantic_entities

