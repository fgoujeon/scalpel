/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2012  Florian Goujeon

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

#ifndef SCALPEL_CPP_LINKAGE_DETAIL_CREATE_UNIQUE_ID_IPP
#define SCALPEL_CPP_LINKAGE_DETAIL_CREATE_UNIQUE_ID_IPP

namespace scalpel { namespace cpp { namespace linkage { namespace detail
{

template<class Entity>
std::string
create_enclosing_declarative_region_unique_id(const Entity& entity)
{
	typedef typename semantic_entities::type_traits::const_enclosing_declarative_region<Entity>::type enclosing_declarative_region_t;

	if(semantic_entities::generic_queries::detail::has_enclosing_declarative_region(entity))
	{
		enclosing_declarative_region_t enclosing_declarative_region =
			semantic_entities::generic_queries::detail::get_enclosing_declarative_region(entity)
		;

		//if(enclosing_declarative_region.has_enclosing_declarative_region()) //global namespace?
		{
			return create_unique_id(enclosing_declarative_region) + "::";
		}
	}

	return "";
}



struct: utility::static_visitor<std::string>
{
	template<typename T>
	std::string
	operator()(const T& t)
	{
		return create_unique_id(t);
	}

	template<typename T>
	std::string
	operator()(const T* t)
	{
		return create_unique_id(*t);
	}

	template<typename T>
	std::string
	operator()(T* const& t)
	{
		return create_unique_id(*t);
	}

	std::string
	operator()(const semantic_entities::unnamed_namespace*)
	{
		assert(false);
		return "";
	}

	std::string
	operator()(const semantic_entities::linked_namespace*)
	{
		assert(false);
		return "";
	}

	std::string
	operator()(const semantic_entities::linked_unnamed_namespace*)
	{
		assert(false);
		return "";
	}

	std::string
	operator()(const semantic_entities::anonymous_union*)
	{
		assert(false);
		return "";
	}

	std::string
	operator()(const semantic_entities::anonymous_member_union*)
	{
		assert(false);
		return "";
	}
} create_unique_id_visitor;

template<class... Entities>
std::string
create_unique_id(const utility::variant<Entities...>& entity)
{
	return apply_visitor(create_unique_id_visitor, entity);
}



template<typename UnderlyingType>
std::string
create_unique_id(const semantic_entities::enum_constant<UnderlyingType>& entity)
{
	return create_enclosing_declarative_region_unique_id(entity) + entity.name();
}

}}}} //namespace scalpel::cpp::linkage::detail

#endif

