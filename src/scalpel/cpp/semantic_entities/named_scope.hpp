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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_NAMED_SCOPE_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_NAMED_SCOPE_HPP

#include "named_entity.hpp"
#include <boost/range/iterator_range.hpp>
#include <boost/iterator/indirect_iterator.hpp>
#include <vector>
#include <memory>

namespace scalpel { namespace cpp { namespace semantic_entities
{

/**
Refers to the scopes that can be browsed by the name lookup functions.
*/
struct named_scope
{
	typedef std::vector<std::shared_ptr<named_scope>> named_scopes_t;
	typedef named_scopes_t::const_iterator named_scope_const_iterator;
	typedef boost::iterator_range<named_scope_const_iterator> named_scope_const_iterator_range;
	typedef named_scopes_t::iterator named_scope_iterator;
	typedef boost::iterator_range<named_scope_iterator> named_scope_iterator_range;

	typedef std::vector<std::shared_ptr<named_entity>> named_entities_t;
	typedef named_entities_t::const_iterator named_entity_const_iterator;
	typedef boost::iterator_range<named_entity_const_iterator> named_entity_const_iterator_range;
	typedef named_entities_t::iterator named_entity_iterator;
	typedef boost::iterator_range<named_entity_iterator> named_entity_iterator_range;

	virtual
	~named_scope(){}

	virtual
	const std::string&
	name() const = 0;

	virtual
	named_scope_iterator_range
	named_scopes() = 0;

	virtual
	named_scope_const_iterator_range
	named_scopes() const = 0;

	virtual
	named_entity_iterator_range
	named_entities() = 0;

	virtual
	named_entity_const_iterator_range
	named_entities() const = 0;
};

}}} //namespace scalpel::cpp::semantic_entities

#endif
