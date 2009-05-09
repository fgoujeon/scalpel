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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_SCOPE_IMPL_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_SCOPE_IMPL_HPP

#include <list>
#include "scope.hpp"
#include "named_entity.hpp"
#include "scope_visitor.hpp"

namespace scalpel { namespace cpp { namespace semantic_entities
{

class scope_impl: public boost::noncopyable
{
	public:
		scope_impl();

		scope_impl(scope_impl&& s);

		const scope_impl&
		operator=(scope_impl&& s);

		scope::scope_iterator_range
		scopes();

		scope::scope_const_iterator_range
		scopes() const;

		void
		add_to_scopes(scope& s);

		scope::named_entity_iterator_range
		named_entities();

		scope::named_entity_const_iterator_range
		named_entities() const;

		void
		add_to_named_entities(named_entity& n);

		bool
		has_enclosing_scope() const;

		const scope&
		enclosing_scope() const;

		scope&
		enclosing_scope();

		void
		enclosing_scope(scope& enclosing_scope);

	private:
		scope* enclosing_scope_;
		scope::scopes_t scopes_;
		scope::named_entities_t named_entities_;
};

}}} //namespace scalpel::cpp::semantic_entities

#endif
