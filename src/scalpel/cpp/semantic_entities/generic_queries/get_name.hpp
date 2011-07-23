/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2011  Florian Goujeon

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

#ifndef SCALPEL_CPP_SEMANTIC_ANALYSIS_DETAIL_SEMANTIC_ENTITY_ANALYSIS_GET_NAME_HPP
#define SCALPEL_CPP_SEMANTIC_ANALYSIS_DETAIL_SEMANTIC_ENTITY_ANALYSIS_GET_NAME_HPP

#include <string>

namespace scalpel { namespace cpp { namespace semantic_entities { namespace generic_queries
{

template<class Entity>
const std::string&
get_name(const Entity& entity)
{
	return entity.name();
}



struct: utility::static_visitor<const std::string&>
{
	template<class Entity>
	const std::string&
	operator()(const Entity* const entity) const
	{
		return entity->name();
	}

	template<class Entity>
	const std::string&
	operator()(const Entity& entity) const
	{
		return entity.name();
	}
} get_name_visitor;

template<class... Entities>
const std::string&
get_name(const utility::variant<Entities...>& entity)
{
	return apply_visitor(get_name_visitor, entity);
}



inline
const std::string&
get_name(const enum_t& entity)
{
	return apply_visitor(get_name_visitor, entity);
}

inline
const std::string&
get_name(const member_enum_t& entity)
{
	return apply_visitor(get_name_visitor, entity);
}

}}}} //namespace scalpel::cpp::semantic_entities::generic_queries

#endif

