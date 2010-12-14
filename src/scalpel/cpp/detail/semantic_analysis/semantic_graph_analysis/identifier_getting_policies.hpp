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

#ifndef SCALPEL_CPP_DETAIL_SEMANTIC_ANALYSIS_SEMANTIC_GRAPH_ANALYSIS_IDENTIFIER_GETTING_POLICIES_HPP
#define SCALPEL_CPP_DETAIL_SEMANTIC_ANALYSIS_SEMANTIC_GRAPH_ANALYSIS_IDENTIFIER_GETTING_POLICIES_HPP

#include "get_name.hpp"
#include <scalpel/cpp/semantic_graph.hpp>
#include <string>

namespace scalpel { namespace cpp { namespace detail { namespace semantic_analysis { namespace semantic_graph_analysis
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
	};

	struct get_name
	{
		typedef std::string identifier_t;

		template<class EntityT>
		static
		identifier_t
		get_identifier(const EntityT& entity)
		{
			return semantic_graph_analysis::get_name(entity);
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
GENERATE_GET_IDENTIFIER_GETTING_POLICY_SPECIALIZATION(operator_function, get_operator)
GENERATE_GET_IDENTIFIER_GETTING_POLICY_SPECIALIZATION(simple_function, get_name)

#undef GENERATE_GET_IDENTIFIER_GETTING_POLICY_SPECIALIZATION

}}}}} //namespace scalpel::cpp::detail::semantic_analysis::semantic_graph_analysis

#endif

