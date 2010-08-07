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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_DECLARATIVE_REGION_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_DECLARATIVE_REGION_HPP

#include <scalpel/utility/shared_ptr_vector.hpp>

namespace scalpel { namespace cpp { namespace semantic_entities
{

struct named_declarative_region;
struct named_entity;

/**
Refers to any declarative region.
*/
struct declarative_region
{
	typedef utility::shared_ptr_vector<named_declarative_region> named_declarative_regions_t;
	typedef utility::shared_ptr_vector<named_entity> named_entities_t;

	virtual
	~declarative_region(){}

	virtual
	named_declarative_regions_t::range
	named_declarative_regions() = 0;

	virtual
	named_declarative_regions_t::const_range
	named_declarative_regions() const = 0;

	virtual
	named_entities_t::range
	named_entities() = 0;

	virtual
	named_entities_t::const_range
	named_entities() const = 0;
};

}}} //namespace scalpel::cpp::semantic_entities

#endif
