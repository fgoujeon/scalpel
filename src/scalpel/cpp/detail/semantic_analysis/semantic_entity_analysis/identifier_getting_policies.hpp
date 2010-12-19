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

#ifndef SCALPEL_CPP_DETAIL_SEMANTIC_ANALYSIS_SEMANTIC_ENTITY_ANALYSIS_IDENTIFIER_GETTING_POLICIES_HPP
#define SCALPEL_CPP_DETAIL_SEMANTIC_ANALYSIS_SEMANTIC_ENTITY_ANALYSIS_IDENTIFIER_GETTING_POLICIES_HPP

#include "get_name.hpp"
#include <scalpel/cpp/semantic_graph.hpp>
#include <scalpel/utility/are_pointed_objects_equal.hpp>
#include <string>

namespace scalpel { namespace cpp { namespace detail { namespace semantic_analysis { namespace semantic_entity_analysis
{

namespace identifier_getting_policies
{
	struct get_null
	{
		typedef void* identifier_t;

		template<class EntityT>
		static
		identifier_t
		get_identifier(const EntityT&)
		{
			return 0;
		}

		template<class EntityT>
		static
		bool
		are_identifiers_equal(const EntityT&, const identifier_t&)
		{
			return true;
		}
	};

	struct get_name
	{
		typedef std::string identifier_t;

		template<class EntityT>
		static
		identifier_t
		get_identifier(const EntityT& entity)
		{
			return semantic_entity_analysis::get_name(entity);
		}

		template<class EntityT>
		static
		bool
		are_identifiers_equal(const EntityT& entity, const identifier_t& identifier)
		{
			return get_identifier(entity) == identifier;
		}
	};

	struct get_operator
	{
		typedef semantic_entities::overloadable_operator identifier_t;

		template<class EntityT>
		static
		identifier_t
		get_identifier(const EntityT& entity)
		{
			return entity->get_operator();
		}

		template<class EntityT>
		static
		bool
		are_identifiers_equal(const EntityT& entity, const identifier_t& identifier)
		{
			return get_identifier(entity) == identifier;
		}
	};

	struct get_type
	{
		typedef semantic_entities::type_shared_ptr_variant identifier_t;

		template<class EntityT>
		static
		identifier_t
		get_identifier(const EntityT& entity)
		{
			return entity->return_type();
		}

		template<class EntityT>
		static
		bool
		are_identifiers_equal(const EntityT& entity, const identifier_t& identifier)
		{
			return are_pointed_objects_equal(get_identifier(entity), identifier);
		}
	};
}



template<class Entity>
struct get_identifier_getting_policy;

#define GENERATE_GET_IDENTIFIER_GETTING_POLICY_SPECIALIZATION(ENTITY_TYPE, POLICY) \
template<> \
struct get_identifier_getting_policy<semantic_entities::ENTITY_TYPE> \
{ \
	typedef identifier_getting_policies::POLICY policy_t; \
};

GENERATE_GET_IDENTIFIER_GETTING_POLICY_SPECIALIZATION(constructor, get_null)
GENERATE_GET_IDENTIFIER_GETTING_POLICY_SPECIALIZATION(destructor, get_null)
GENERATE_GET_IDENTIFIER_GETTING_POLICY_SPECIALIZATION(operator_member_function, get_operator)
GENERATE_GET_IDENTIFIER_GETTING_POLICY_SPECIALIZATION(conversion_function, get_type)
GENERATE_GET_IDENTIFIER_GETTING_POLICY_SPECIALIZATION(simple_member_function, get_name)
GENERATE_GET_IDENTIFIER_GETTING_POLICY_SPECIALIZATION(operator_function, get_operator)
GENERATE_GET_IDENTIFIER_GETTING_POLICY_SPECIALIZATION(simple_function, get_name)

#undef GENERATE_GET_IDENTIFIER_GETTING_POLICY_SPECIALIZATION

}}}}} //namespace scalpel::cpp::detail::semantic_analysis::semantic_entity_analysis

#endif

