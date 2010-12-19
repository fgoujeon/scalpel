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

#ifndef SCALPEL_CPP_DETAIL_SEMANTIC_ANALYSIS_FUNCTION_CONSTRUCTION_IPP
#define SCALPEL_CPP_DETAIL_SEMANTIC_ANALYSIS_FUNCTION_CONSTRUCTION_IPP

#include "semantic_entity_analysis/identifier_getting_policies.hpp"
#include "name_lookup.hpp"
#include <set>
#include <iostream>

namespace scalpel { namespace cpp { namespace detail { namespace semantic_analysis
{

template<class FunctionT>
std::shared_ptr<FunctionT>
find_function
(
	const std::shared_ptr<const FunctionT> function_signature,
	const semantic_entities::open_declarative_region_shared_ptr_variant& function_declarative_region
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	typedef typename semantic_entity_analysis::get_identifier_getting_policy<FunctionT>::policy_t identifier_getting_policy_t;

	//find the functions with the same identifier
	std::set<std::shared_ptr<FunctionT>> found_functions;

	found_functions =
		name_lookup::find_local
		<
			identifier_getting_policy_t,
			true,
			true,
			FunctionT
		>
		(
			identifier_getting_policy_t::get_identifier(function_signature),
			function_declarative_region
		)
	;

	//filter the found functions with the signature
	for
	(
		auto i = found_functions.begin();
		i != found_functions.end();
		++i
	)
	{
		std::shared_ptr<FunctionT> found_function = *i;
		if(have_same_signature(*found_function, *function_signature))
		{
			return found_function;
		}
	}

	//if nothing is found
	return std::shared_ptr<FunctionT>();
}

}}}} //namespace scalpel::cpp::detail::semantic_analysis

#endif

