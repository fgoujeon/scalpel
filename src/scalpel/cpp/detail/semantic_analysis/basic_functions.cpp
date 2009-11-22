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

#include "basic_functions.hpp"

#include <iostream>
#include <stdexcept>

namespace scalpel { namespace cpp { namespace detail { namespace semantic_analysis
{

using namespace syntax_nodes;
using namespace semantic_entities;

//
//class related
//

class_::access
get_access(const syntax_nodes::access_specifier access_specifier_node)
{
	if(get<predefined_text_node<str::public_>>(&access_specifier_node))
	{
		return class_::access::PUBLIC;
	}
	else if(get<predefined_text_node<str::protected_>>(&access_specifier_node))
	{
		return class_::access::PROTECTED;
	}
	else if(get<predefined_text_node<str::private_>>(&access_specifier_node))
	{
		return class_::access::PRIVATE;
	}
	else
	{
		assert(false);
	}

	return class_::access::PRIVATE;
}



//
//function related
//

const std::string&
get_function_name(const declarator& declarator_node)
{
	auto direct_declarator_node = get_direct_declarator(declarator_node);
	auto first_part_node = get_first_part(direct_declarator_node);
	auto opt_declarator_id_node = get<declarator_id>(&first_part_node);
	if(opt_declarator_id_node)
	{
		auto opt_id_expression_node = get<id_expression>(opt_declarator_id_node);
		if(opt_id_expression_node)
		{
			auto opt_unqualified_id_node = get<unqualified_id>(opt_id_expression_node);
			auto opt_qualified_id_node = get<qualified_id>(opt_id_expression_node);

			if(opt_unqualified_id_node)
			{
				auto opt_identifier_node = get<identifier>(opt_unqualified_id_node);
				if(opt_identifier_node)
				{
					return opt_identifier_node->value();
				}

			}
			else if(opt_qualified_id_node)
			{
			//	const qualified_identifier* const a_qualified_identifier =
			//		boost::get<qualified_identifier>(opt_qualified_id_node)
			//	;
				auto opt_qualified_nested_id_node = get<qualified_nested_id>(opt_qualified_id_node);
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
						return opt_identifier_node->value();
					}
				}
			}
			else
			{
				assert(false);
			}
		}
	}

	throw std::runtime_error("Cannot find the name of the function");
}

bool
is_function_declaration(const declarator& declarator_node)
{
	auto direct_declarator_node = get_direct_declarator(declarator_node);
	auto direct_declarator_node_last_part_seq = get_last_part_seq(direct_declarator_node);
	if(direct_declarator_node_last_part_seq)
	{
		for(auto j = direct_declarator_node_last_part_seq->begin(); j != direct_declarator_node_last_part_seq->end(); ++j)
		{
			const direct_declarator_last_part& last_part = j->main_node();

			if(get<direct_declarator_function_part>(&last_part))
			{
				return true;
			}
		}
	}

	return false;
}

bool
has_pure_specifier(const syntax_nodes::member_declarator_declarator& member_declarator_declarator_node)
{
	if(auto opt_last_part_node = get_last_part(member_declarator_declarator_node))
	{
		auto last_part_node = *opt_last_part_node;
		if(get<pure_specifier>(&last_part_node))
		{
			return true;
		}
	}

	return false;
}

}}}} //namespace scalpel::cpp::detail::semantic_analysis

