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

#ifndef SCALPEL_CPP_SEMANTIC_ANALYSIS_DETAIL_SEMANTIC_ENTITY_ANALYSIS_IDENTIFICATION_POLICIES_HPP
#define SCALPEL_CPP_SEMANTIC_ANALYSIS_DETAIL_SEMANTIC_ENTITY_ANALYSIS_IDENTIFICATION_POLICIES_HPP

#include "get_name.hpp"
#include <scalpel/cpp/semantic_graph.hpp>
#include <string>

namespace scalpel { namespace cpp { namespace semantic_analysis { namespace detail { namespace semantic_entity_analysis
{

//these policies define how an entity can be identified
//(either by its name, its overloaded operator, etc.)
namespace identification_policies
{
	struct by_nothing
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

	struct by_name
	{
		typedef std::string identifier_t;

		template<class EntityT>
		static
		const identifier_t&
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

	struct by_overloaded_operator
	{
		typedef semantic_entities::overloadable_operator identifier_t;

		template<class EntityT>
		static
		identifier_t
		get_identifier(const EntityT& entity)
		{
			return entity.overloaded_operator();
		}

		template<class EntityT>
		static
		identifier_t
		get_identifier(const std::shared_ptr<EntityT>& entity)
		{
			return entity->overloaded_operator();
		}

		template<class EntityT>
		static
		bool
		are_identifiers_equal(const EntityT& entity, const identifier_t& identifier)
		{
			return get_identifier(entity) == identifier;
		}
	};

	struct by_return_type
	{
		typedef semantic_entities::type_t identifier_t;

		template<class EntityT>
		static
		const identifier_t&
		get_identifier(const EntityT& entity)
		{
			return entity.return_type();
		}

		template<class EntityT>
		static
		const identifier_t&
		get_identifier(const std::shared_ptr<EntityT>& entity)
		{
			return entity->return_type();
		}

		template<class EntityT>
		static
		bool
		are_identifiers_equal(const EntityT& entity, const identifier_t& identifier)
		{
			return get_identifier(entity) == identifier;
		}
	};
}



//relate an entity type with its corresponding identification policy
template<class Entity>
struct get_identification_policy;

#define GENERATE_GET_IDENTIFICATION_POLICY_SPECIALIZATION(ENTITY_TYPE, POLICY) \
template<> \
struct get_identification_policy<semantic_entities::ENTITY_TYPE> \
{ \
	typedef identification_policies::POLICY policy_t; \
};

GENERATE_GET_IDENTIFICATION_POLICY_SPECIALIZATION(constructor, by_nothing)
GENERATE_GET_IDENTIFICATION_POLICY_SPECIALIZATION(destructor, by_nothing)
GENERATE_GET_IDENTIFICATION_POLICY_SPECIALIZATION(operator_member_function, by_overloaded_operator)
GENERATE_GET_IDENTIFICATION_POLICY_SPECIALIZATION(conversion_function, by_return_type)
GENERATE_GET_IDENTIFICATION_POLICY_SPECIALIZATION(simple_member_function, by_name)
GENERATE_GET_IDENTIFICATION_POLICY_SPECIALIZATION(operator_function, by_overloaded_operator)
GENERATE_GET_IDENTIFICATION_POLICY_SPECIALIZATION(simple_function, by_name)

#undef GENERATE_GET_IDENTIFICATION_POLICY_SPECIALIZATION

}}}}} //namespace scalpel::cpp::semantic_analysis::detail::semantic_entity_analysis

#endif

