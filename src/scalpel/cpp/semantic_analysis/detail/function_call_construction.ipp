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

#ifndef SCALPEL_CPP_SEMANTIC_ANALYSIS_DETAIL_FUNCTION_CALL_CONSTRUCTION_IPP
#define SCALPEL_CPP_SEMANTIC_ANALYSIS_DETAIL_FUNCTION_CALL_CONSTRUCTION_IPP

#include "name_lookup.hpp"

namespace scalpel { namespace cpp { namespace semantic_analysis { namespace detail
{

class create_function_call_visitor: public utility::static_visitor<semantic_entities::function_call<semantic_entities::simple_function>>
{
	public:
		create_function_call_visitor(std::vector<semantic_entities::expression_t>&& argument_list):
			argument_list_(std::move(argument_list))
		{
		}

		semantic_entities::function_call<semantic_entities::simple_function>
		operator()(semantic_entities::simple_function* const function) const
		{
			return semantic_entities::function_call<semantic_entities::simple_function>
			(
				*function,
				std::move(argument_list_)
			);
		}

		semantic_entities::function_call<semantic_entities::simple_function>
		operator()(semantic_entities::variable* const) const
		{
			assert(false); //TODO
		}

	private:
		std::vector<semantic_entities::expression_t> argument_list_;
};

template<class DeclarativeRegion>
semantic_entities::function_call<semantic_entities::simple_function>
create_simple_function_call
(
	const std::string& identifier,
	const syntax_nodes::round_bracketed_optional_expression& round_bracketed_optional_expression_node,
	DeclarativeRegion& declarative_region
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	auto found_entity =
		name_lookup::find
		<
			semantic_entity_analysis::identification_policies::by_name,
			false,
			false,
			simple_function,
			variable
		>
		(
			identifier,
			&declarative_region
		)
	;

	create_function_call_visitor visitor(create_function_argument_list(round_bracketed_optional_expression_node, declarative_region));
	return apply_visitor(visitor, found_entity);
}



template<class DeclarativeRegion>
std::vector<semantic_entities::expression_t>
create_function_argument_list
(
	const syntax_nodes::round_bracketed_optional_expression& round_bracketed_optional_expression_node,
	DeclarativeRegion& declarative_region
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	std::vector<semantic_entities::expression_t> argument_list;

	const optional_node<expression>& opt_expression_node = get_expression(round_bracketed_optional_expression_node);
	if(opt_expression_node)
	{
		for(const syntax_nodes::assignment_expression& assignment_expression_node: *opt_expression_node)
		{
			argument_list.push_back
			(
				create_expression_from_assignment_expression
				(
					assignment_expression_node,
					declarative_region
				)
			);
		}
	}

	return argument_list;
}

}}}} //namespace scalpel::cpp::semantic_analysis::detail

#endif

