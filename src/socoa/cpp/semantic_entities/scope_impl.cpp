/*
Socoa - Source Code Analysis Library
Copyright © 2008, 2009  Florian Goujeon

This file is part of Socoa.

Socoa is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Socoa is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Socoa.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "scope_impl.hpp"

namespace socoa { namespace cpp { namespace semantic_entities
{

scope_impl::scope_impl():
	enclosing_scope_(0)
{
}

scope_impl::scope_impl(scope_impl&& s):
	enclosing_scope_(0),
	scopes_(std::move(s.scopes_)),
	named_entities_(std::move(s.named_entities_))
{
	assert(s.enclosing_scope_ == 0);
}

const scope_impl&
scope_impl::operator=(scope_impl&& s)
{
	assert(s.enclosing_scope_ == 0);

	scopes_ = std::move(s.scopes_);
	named_entities_ = std::move(s.named_entities_);

	return *this;
}

scope::scope_iterator_range
scope_impl::scopes()
{
	scope::scope_iterator first = scopes_.begin();
	scope::scope_iterator last = scopes_.end();

	scope::scope_indirect_iterator indirect_first(first), indirect_last(last);

	return scope::scope_iterator_range(indirect_first, indirect_last);
}

scope::scope_const_iterator_range
scope_impl::scopes() const
{
	scope::scope_const_iterator first = scopes_.begin();
	scope::scope_const_iterator last = scopes_.end();

	scope::scope_const_indirect_iterator const_indirect_first(first), const_indirect_last(last);

	return scope::scope_const_iterator_range(const_indirect_first, const_indirect_last);
}

void
scope_impl::add_to_scopes(scope& s)
{
	scopes_.push_back(&s);
}

scope::named_entity_iterator_range
scope_impl::named_entities()
{
	scope::named_entity_iterator first = named_entities_.begin();
	scope::named_entity_iterator last = named_entities_.end();

	scope::named_entity_indirect_iterator indirect_first(first), indirect_last(last);

	return scope::named_entity_iterator_range(indirect_first, indirect_last);
}

scope::named_entity_const_iterator_range
scope_impl::named_entities() const
{
	scope::named_entity_const_iterator first = named_entities_.begin();
	scope::named_entity_const_iterator last = named_entities_.end();

	scope::named_entity_const_indirect_iterator const_indirect_first(first), const_indirect_last(last);

	return scope::named_entity_const_iterator_range(const_indirect_first, const_indirect_last);
}

void
scope_impl::add_to_named_entities(named_entity& n)
{
	named_entities_.push_back(&n);
}

bool
scope_impl::has_enclosing_scope() const
{
	return enclosing_scope_;
}

const scope&
scope_impl::enclosing_scope() const
{
	return *enclosing_scope_;
}

scope&
scope_impl::enclosing_scope()
{
	return *enclosing_scope_;
}

void
scope_impl::enclosing_scope(scope& enclosing_scope)
{
    assert(!enclosing_scope_); //assert that member doesn't have any enclosing scope yet
    enclosing_scope_ = &enclosing_scope;
}

}}} //namespace socoa::cpp::semantic_entities

