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

#include "declarator.hpp"
#include <stdexcept>

namespace scalpel { namespace cpp { namespace detail { namespace semantic_analysis { namespace syntax_node_analysis
{

using namespace syntax_nodes;

declarator_type
get_declarator_type(const syntax_nodes::declarator& declarator_node)
{
	//
	//node counters' declaration
	//

	bool has_operator_function_id = false;
	bool has_conversion_function_id = false;
	bool has_destructor_name = false;
	unsigned int direct_declarator_function_part_count = 0;



	//
	//node counting
	//

	const direct_declarator& direct_declarator_node = get_direct_declarator(declarator_node);

	const direct_declarator_first_part& first_part_node = get_first_part(direct_declarator_node);
	if(get<bracketed_declarator>(&first_part_node))
	{
		assert(false); //not managed yet
	}
	else if(boost::optional<const declarator_id&> opt_declarator_id_node = get<declarator_id>(&first_part_node))
	{
		const declarator_id& declarator_id_node = *opt_declarator_id_node;

		if(boost::optional<const id_expression&> opt_id_expression_node = get<id_expression>(&declarator_id_node))
		{
			const id_expression& id_expression_node = *opt_id_expression_node;

			if(boost::optional<const unqualified_id&> opt_unqualified_id_node = get<unqualified_id>(&id_expression_node))
			{
				const unqualified_id& unqualified_id_node = *opt_unqualified_id_node;

				if(get<operator_function_id>(&unqualified_id_node))
				{
					has_operator_function_id = true;
				}
				else if(get<conversion_function_id>(&unqualified_id_node))
				{
					has_conversion_function_id = true;
				}
				else if(get<destructor_name>(&unqualified_id_node))
				{
					has_destructor_name = true;
				}
				else if(get<template_id>(&unqualified_id_node))
				{
					assert(false); //not managed yet
				}
				else if(get<identifier>(&unqualified_id_node))
				{
					//nothing
				}
			}
			else if(boost::optional<const qualified_id&> opt_qualified_id_node = get<qualified_id>(&id_expression_node))
			{
				const qualified_id& qualified_id_node = *opt_qualified_id_node;

				if(get<qualified_identifier>(&qualified_id_node))
				{
					assert(false); //not managed yet
				}
				else if(boost::optional<const qualified_nested_id&> opt_qualified_nested_id_node = get<qualified_nested_id>(&qualified_id_node))
				{
					const qualified_nested_id& qualified_nested_id_node = *opt_qualified_nested_id_node;
					const unqualified_id& unqualified_id_node = get_unqualified_id(qualified_nested_id_node);

					if(get<operator_function_id>(&unqualified_id_node))
					{
						has_operator_function_id = true;
					}
					else if(get<conversion_function_id>(&unqualified_id_node))
					{
						has_conversion_function_id = true;
					}
					else if(get<destructor_name>(&unqualified_id_node))
					{
						has_destructor_name = true;
					}
					else if(get<template_id>(&unqualified_id_node))
					{
						assert(false); //not managed yet
					}
					else if(get<identifier>(&unqualified_id_node))
					{
						//nothing
					}
				}
				else if(get<qualified_operator_function_id>(&qualified_id_node))
				{
					assert(false); //not managed yet
				}
				else if(get<qualified_template_id>(&qualified_id_node))
				{
					assert(false); //not managed yet
				}
			}
		}
		else if(get<nested_identifier_or_template_id>(&declarator_id_node))
		{
		}
	}

	if(const optional_node<direct_declarator_last_part_seq>& opt_last_part_seq_node = get_last_part_seq(direct_declarator_node))
	{
		const direct_declarator_last_part_seq& last_part_seq_node = *opt_last_part_seq_node;

		for(auto j = last_part_seq_node.begin(); j != last_part_seq_node.end(); ++j)
		{
			const direct_declarator_last_part& last_part_node = j->main_node();

			if(get<direct_declarator_function_part>(&last_part_node))
			{
				++direct_declarator_function_part_count;
			}
			else if(get<direct_declarator_array_part>(&last_part_node))
			{
				assert(false); //not managed yet
			}
		}
	}



	//
	//result
	//

	if
	(
		!has_operator_function_id &&
		!has_conversion_function_id &&
		has_destructor_name &&
		direct_declarator_function_part_count == 1
	)
		return declarator_type::DESTRUCTOR_DECLARATOR;
	else if
	(
		has_operator_function_id &&
		!has_conversion_function_id &&
		!has_destructor_name &&
		direct_declarator_function_part_count == 1
	)
		return declarator_type::OPERATOR_FUNCTION_DECLARATOR;
	else if
	(
		!has_operator_function_id &&
		has_conversion_function_id &&
		!has_destructor_name &&
		direct_declarator_function_part_count == 1
	)
		return declarator_type::CONVERSION_FUNCTION_DECLARATOR;
	else if
	(
		!has_operator_function_id &&
		!has_conversion_function_id &&
		!has_destructor_name &&
		direct_declarator_function_part_count == 1
	)
		return declarator_type::SIMPLE_FUNCTION_DECLARATOR;
	else if
	(
		!has_operator_function_id &&
		!has_conversion_function_id &&
		!has_destructor_name &&
		direct_declarator_function_part_count == 0
	)
		return declarator_type::VARIABLE_DECLARATOR;

	throw std::runtime_error("get_declarator_type error");
}

boost::optional<const syntax_nodes::parameter_declaration_list&>
get_parameter_declaration_list(const syntax_nodes::declarator& declarator_node)
{
	const direct_declarator& direct_declarator_node = get_direct_declarator(declarator_node);
	if(const optional_node<direct_declarator_last_part_seq>& opt_last_part_seq_node = get_last_part_seq(direct_declarator_node))
	{
		const direct_declarator_last_part_seq& last_part_seq_node = *opt_last_part_seq_node;
		for(auto i = last_part_seq_node.begin(); i != last_part_seq_node.end(); ++i)
		{
			const direct_declarator_last_part& last_part_node = i->main_node();
			if(boost::optional<const direct_declarator_function_part&> opt_function_part_node = syntax_nodes::get<syntax_nodes::direct_declarator_function_part>(&last_part_node))
			{
				if(const optional_node<parameter_declaration_clause>& opt_parameter_declaration_clause_node = get_parameter_declaration_clause(*opt_function_part_node))
				{
					if
					(
						const optional_node<parameter_declaration_list>& opt_parameter_declaration_list_node =
							get_parameter_declaration_list(*opt_parameter_declaration_clause_node)
					)
					{
						return *opt_parameter_declaration_list_node;
					}
				}
			}
		}
	}

	return boost::optional<const syntax_nodes::parameter_declaration_list&>();
}

syntax_nodes::identifier
get_identifier(const declarator& declarator_node)
{
	auto direct_declarator_node = get_direct_declarator(declarator_node);
	auto first_part_node = get_first_part(direct_declarator_node);
	auto opt_declarator_id_node = get<declarator_id>(&first_part_node);
	if(opt_declarator_id_node)
	{
		auto declarator_id_node = *opt_declarator_id_node;
		if(auto opt_id_expression_node = get<id_expression>(&declarator_id_node))
		{
			auto opt_unqualified_id_node = get<unqualified_id>(&*opt_id_expression_node);
			auto opt_qualified_id_node = get<qualified_id>(&*opt_id_expression_node);

			if(opt_unqualified_id_node)
			{
				if(auto opt_identifier_node = get<identifier>(&*opt_unqualified_id_node))
				{
					return *opt_identifier_node;
				}
				else if(auto opt_destructor_name_node = get<destructor_name>(&*opt_unqualified_id_node))
				{
					auto destructor_name_node = *opt_destructor_name_node;
					auto identifier_or_template_id = get_identifier_or_template_id(destructor_name_node);
					if(auto opt_identifier_node = get<identifier>(&identifier_or_template_id))
					{
						return *opt_identifier_node;
					}
				}
			}
			else if(opt_qualified_id_node)
			{
			//	const qualified_identifier* const a_qualified_identifier =
			//		boost::get<qualified_identifier>(opt_qualified_id_node)
			//	;
				auto opt_qualified_nested_id_node = get<qualified_nested_id>(&*opt_qualified_id_node);
			//	const qualified_operator_function_id* const a_qualified_operator_function_id =
			//	   	boost::get<qualified_operator_function_id>(opt_qualified_id_node)
			//	;
			//	const qualified_template_id* const a_qualified_template_id =
			//	   	boost::get<qualified_template_id>(opt_qualified_id_node)
			//	;

				if(opt_qualified_nested_id_node)
				{
					auto unqualified_id_node = get_unqualified_id(*opt_qualified_nested_id_node);
					auto opt_identifier_node = get<identifier>(&unqualified_id_node);
					if(opt_identifier_node)
					{
						return *opt_identifier_node;
					}
				}
			}
			else
			{
				assert(false);
			}
		}
		else if(auto opt_nested_identifier_or_template_id_node = get<nested_identifier_or_template_id>(&declarator_id_node))
		{
			auto nested_identifier_or_template_id_node = *opt_nested_identifier_or_template_id_node;
			auto identifier_or_template_id_node = get_identifier_or_template_id(nested_identifier_or_template_id_node);
			if(auto opt_identifier_node = get<identifier>(&identifier_or_template_id_node))
			{
				return *opt_identifier_node;
			}
		}
		else
		{
			assert(false);
		}
	}

	assert(false);
	throw std::runtime_error("Cannot find the name");
}

bool
has_identifier(const declarator& declarator_node)
{
	auto direct_declarator_node = get_direct_declarator(declarator_node);
	auto first_part_node = get_first_part(direct_declarator_node);
	auto opt_declarator_id_node = get<declarator_id>(&first_part_node);
	if(opt_declarator_id_node)
	{
		auto declarator_id_node = *opt_declarator_id_node;
		if(auto opt_id_expression_node = get<id_expression>(&declarator_id_node))
		{
			auto opt_unqualified_id_node = get<unqualified_id>(&*opt_id_expression_node);
			auto opt_qualified_id_node = get<qualified_id>(&*opt_id_expression_node);

			if(opt_unqualified_id_node)
			{
				if(auto opt_identifier_node = get<identifier>(&*opt_unqualified_id_node))
				{
					return true;
				}
				else if(auto opt_destructor_name_node = get<destructor_name>(&*opt_unqualified_id_node))
				{
					auto destructor_name_node = *opt_destructor_name_node;
					auto identifier_or_template_id = get_identifier_or_template_id(destructor_name_node);
					if(auto opt_identifier_node = get<identifier>(&identifier_or_template_id))
					{
						return true;
					}
				}
			}
			else if(opt_qualified_id_node)
			{
			//	const qualified_identifier* const a_qualified_identifier =
			//		boost::get<qualified_identifier>(opt_qualified_id_node)
			//	;
				auto opt_qualified_nested_id_node = get<qualified_nested_id>(&*opt_qualified_id_node);
			//	const qualified_operator_function_id* const a_qualified_operator_function_id =
			//	   	boost::get<qualified_operator_function_id>(opt_qualified_id_node)
			//	;
			//	const qualified_template_id* const a_qualified_template_id =
			//	   	boost::get<qualified_template_id>(opt_qualified_id_node)
			//	;

				if(opt_qualified_nested_id_node)
				{
					auto unqualified_id_node = get_unqualified_id(*opt_qualified_nested_id_node);
					auto opt_identifier_node = get<identifier>(&unqualified_id_node);
					if(opt_identifier_node)
					{
						return true;
					}
				}
			}
			else
			{
				assert(false);
			}
		}
		else if(auto opt_nested_identifier_or_template_id_node = get<nested_identifier_or_template_id>(&declarator_id_node))
		{
			auto nested_identifier_or_template_id_node = *opt_nested_identifier_or_template_id_node;
			auto identifier_or_template_id_node = get_identifier_or_template_id(nested_identifier_or_template_id_node);
			if(auto opt_identifier_node = get<identifier>(&identifier_or_template_id_node))
			{
				return true;
			}
		}
		else
		{
			assert(false);
		}
	}

	return false;
}

syntax_nodes::optional_node<syntax_nodes::nested_name_specifier>
get_nested_name_specifier(const syntax_nodes::declarator& declarator_node)
{
	const direct_declarator& direct_declarator_node = get_direct_declarator(declarator_node);
	const direct_declarator_first_part& first_part_node = get_first_part(direct_declarator_node);
	if(const boost::optional<const declarator_id&> opt_declarator_id_node = get<declarator_id>(&first_part_node))
	{
		const declarator_id& declarator_id_node = *opt_declarator_id_node;

		//operator function:
		//declarator_id -> id_expression -> qualified_id -> qualified_nested_id -> nested_name_specifier

		//simple function:
		//declarator_id -> nested_identifier_or_template_id -> nested_name_specifier

		if(boost::optional<const id_expression&> opt_id_expression_node = get<id_expression>(&declarator_id_node))
		{
			const id_expression& id_expression_node = *opt_id_expression_node;

			if(boost::optional<const qualified_id&> opt_qualified_id_node = get<qualified_id>(&id_expression_node))
			{
				const qualified_id& qualified_id_node = *opt_qualified_id_node;

				if(boost::optional<const qualified_nested_id&> opt_qualified_nested_id_node = get<qualified_nested_id>(&qualified_id_node))
				{
					const qualified_nested_id& qualified_nested_id_node = *opt_qualified_nested_id_node;
					return optional_node<nested_name_specifier>(get_nested_name_specifier(qualified_nested_id_node));
				}
			}
		}
		else if
		(
			boost::optional<const nested_identifier_or_template_id&> opt_nested_identifier_or_template_id_node =
				get<nested_identifier_or_template_id>(&declarator_id_node)
		)
		{
			const nested_identifier_or_template_id& nested_identifier_or_template_id_node =
				*opt_nested_identifier_or_template_id_node
			;

			if
			(
				const optional_node<nested_name_specifier>& opt_nested_name_specifier_node =
					get_nested_name_specifier(nested_identifier_or_template_id_node)
			)
			{
				return *opt_nested_name_specifier_node;
			}
		}
	}

	return optional_node<nested_name_specifier>();
}

const syntax_nodes::operator_&
get_operator(const syntax_nodes::declarator& declarator_node)
{
	const direct_declarator& direct_declarator_node = get_direct_declarator(declarator_node);

	const direct_declarator_first_part& first_part_node = get_first_part(direct_declarator_node);
	if(boost::optional<const declarator_id&> opt_declarator_id_node = get<declarator_id>(&first_part_node))
	{
		const declarator_id& declarator_id_node = *opt_declarator_id_node;

		if(boost::optional<const id_expression&> opt_id_expression_node = get<id_expression>(&declarator_id_node))
		{
			const id_expression& id_expression_node = *opt_id_expression_node;

			if(boost::optional<const unqualified_id&> opt_unqualified_id_node = get<unqualified_id>(&id_expression_node))
			{
				const unqualified_id& unqualified_id_node = *opt_unqualified_id_node;

				if(boost::optional<const operator_function_id&> opt_operator_function_id_node = get<operator_function_id>(&unqualified_id_node))
				{
					return get_operator(*opt_operator_function_id_node);
				}
			}
			else if(boost::optional<const qualified_id&> opt_qualified_id_node = get<qualified_id>(&id_expression_node))
			{
				const qualified_id& qualified_id_node = *opt_qualified_id_node;

				if(boost::optional<const qualified_nested_id&> opt_qualified_nested_id_node = get<qualified_nested_id>(&qualified_id_node))
				{
					const qualified_nested_id& qualified_nested_id_node = *opt_qualified_nested_id_node;
					const unqualified_id& unqualified_id_node = get_unqualified_id(qualified_nested_id_node);

					if(boost::optional<const operator_function_id&> opt_operator_function_id_node = get<operator_function_id>(&unqualified_id_node))
					{
						return get_operator(*opt_operator_function_id_node);
					}
				}
			}
		}
	}

	assert(false);
}

}}}}} //namespace scalpel::cpp::detail::semantic_analysis::syntax_node_analysis

