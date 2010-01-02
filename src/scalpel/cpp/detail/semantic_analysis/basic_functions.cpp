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

bool
is_function_declaration(const declarator& declarator_node)
{
	auto direct_declarator_node = get_direct_declarator(declarator_node);
	if(auto direct_declarator_node_last_part_seq = get_last_part_seq(direct_declarator_node))
	{
		for(auto i = direct_declarator_node_last_part_seq->begin(); i != direct_declarator_node_last_part_seq->end(); ++i)
		{
			const direct_declarator_last_part& last_part = i->main_node();

			if(get<direct_declarator_function_part>(&last_part))
			{
				return true;
			}
		}
	}

	return false;
}

bool
is_simple_function_declaration(const declarator& declarator_node)
{
	auto direct_declarator_node = get_direct_declarator(declarator_node);

	if(!has_name(declarator_node))
		return false;

	if(auto direct_declarator_node_last_part_seq = get_last_part_seq(direct_declarator_node))
	{
		for(auto i = direct_declarator_node_last_part_seq->begin(); i != direct_declarator_node_last_part_seq->end(); ++i)
		{
			const direct_declarator_last_part& last_part = i->main_node();

			if(get<direct_declarator_function_part>(&last_part))
			{
				return true;
			}
		}
	}

	return false;
}

bool
is_operator_function_declaration(const declarator& declarator_node)
{
	auto direct_declarator_node = get_direct_declarator(declarator_node);
	auto direct_declarator_node_first_part_node = get_first_part(direct_declarator_node);
	if(auto opt_declarator_id_node = get<declarator_id>(&direct_declarator_node_first_part_node))
	{
		auto declarator_id_node = *opt_declarator_id_node;
		if(auto opt_id_expression_node = get<id_expression>(&declarator_id_node))
		{
			auto id_expression_node = *opt_id_expression_node;
			if(auto opt_unqualified_id_node = get<unqualified_id>(&id_expression_node))
			{
				auto unqualified_id_node = *opt_unqualified_id_node;
				if(get<operator_function_id>(&unqualified_id_node))
				{
					return true;
				}
			}
		}
	}

	return false;
}

bool
is_conversion_function_declaration(const declarator& declarator_node)
{
	auto direct_declarator_node = get_direct_declarator(declarator_node);
	auto direct_declarator_node_first_part_node = get_first_part(direct_declarator_node);
	if(auto opt_declarator_id_node = get<declarator_id>(&direct_declarator_node_first_part_node))
	{
		auto declarator_id_node = *opt_declarator_id_node;
		if(auto opt_id_expression_node = get<id_expression>(&declarator_id_node))
		{
			auto id_expression_node = *opt_id_expression_node;
			if(auto opt_unqualified_id_node = get<unqualified_id>(&id_expression_node))
			{
				auto unqualified_id_node = *opt_unqualified_id_node;
				if(get<conversion_function_id>(&unqualified_id_node))
				{
					return true;
				}
			}
		}
	}

	return false;
}

bool
is_destructor_declaration(const syntax_nodes::declarator& declarator_node)
{
	auto direct_declarator_node = get_direct_declarator(declarator_node);
	auto first_part_node = get_first_part(direct_declarator_node);
	auto opt_declarator_id_node = get<declarator_id>(&first_part_node);
	if(opt_declarator_id_node)
	{
		auto opt_id_expression_node = get<id_expression>(&*opt_declarator_id_node);
		if(opt_id_expression_node)
		{
			auto opt_unqualified_id_node = get<unqualified_id>(&*opt_id_expression_node);
			auto opt_qualified_id_node = get<qualified_id>(&*opt_id_expression_node);

			if(opt_unqualified_id_node)
			{
				return get<destructor_name>(&*opt_unqualified_id_node);
			}
		}
	}

	return false;
}

bool
has_pure_specifier(const syntax_nodes::member_declarator_declarator& member_declarator_declarator_node)
{
	if(auto opt_constant_initializer_node = get_constant_initializer(member_declarator_declarator_node))
	{
		//auto constant_initializer_node = *opt_constant_initializer_node;
		//if(get<pure_specifier>(&constant_initializer_node))
		{
			return true;
		}
	}

	return false;
}



//
//simple-declaration related
//

bool
is_class_declaration(const syntax_nodes::simple_declaration& simple_declaration_node)
{
	auto opt_decl_specifier_seq_node = get_decl_specifier_seq(simple_declaration_node);
	//auto opt_init_declarator_list_node = get_init_declarator_list(simple_declaration_node);

	if(opt_decl_specifier_seq_node)
	{
		auto decl_specifier_seq_node = *opt_decl_specifier_seq_node;
		for(auto i = decl_specifier_seq_node.begin(); i != decl_specifier_seq_node.end(); ++i)
		{
			auto decl_specifier_node = i->main_node();
			if(auto opt_type_specifier_ptr_node = get<type_specifier>(&decl_specifier_node))
			{
				auto type_specifier_ptr_node = *opt_type_specifier_ptr_node;
				if(auto opt_class_specifier_node = get<class_specifier>(&type_specifier_ptr_node))
				{
					return true;
				}
			}
		}
	}

	return false;
}

bool
is_class_forward_declaration(const syntax_nodes::simple_declaration& simple_declaration_node)
{
	auto opt_decl_specifier_seq_node = get_decl_specifier_seq(simple_declaration_node);
	//auto opt_init_declarator_list_node = get_init_declarator_list(simple_declaration_node);

	if(opt_decl_specifier_seq_node)
	{
		const decl_specifier_seq& decl_specifier_seq_node = *opt_decl_specifier_seq_node;
		for(auto i = decl_specifier_seq_node.begin(); i != decl_specifier_seq_node.end(); ++i)
		{
			const decl_specifier& decl_specifier_node = i->main_node();

			if(auto opt_type_specifier_ptr_node = get<type_specifier>(&decl_specifier_node))
			{
				auto type_specifier_ptr_node = *opt_type_specifier_ptr_node;
				if(auto opt_elaborated_type_specifier_ptr_node = get<elaborated_type_specifier>(&type_specifier_ptr_node))
				{
					auto elaborated_type_specifier_ptr_node = *opt_elaborated_type_specifier_ptr_node;
					if
					(
						auto opt_class_elaborated_specifier_node = get<class_elaborated_specifier>
						(
							&elaborated_type_specifier_ptr_node
						)
					)
					{
						return true;
					}
				}
			}
		}
	}

	return false;
}

bool
is_function_declaration(const syntax_nodes::simple_declaration& simple_declaration_node)
{
	auto opt_decl_specifier_seq_node = get_decl_specifier_seq(simple_declaration_node);
	auto opt_init_declarator_list_node = get_init_declarator_list(simple_declaration_node);

	if(!opt_decl_specifier_seq_node)
		return false;

	if(opt_init_declarator_list_node)
	{
		auto init_declarator_list_node = *opt_init_declarator_list_node;
		for(auto i = init_declarator_list_node.begin(); i != init_declarator_list_node.end(); ++i)
		{
			auto declarator_node = get_declarator(i->main_node());
			if(is_function_declaration(declarator_node))
				return true;
		}
	}

	return false;
}

bool
is_simple_function_declaration(const syntax_nodes::simple_declaration& simple_declaration_node)
{
	auto opt_decl_specifier_seq_node = get_decl_specifier_seq(simple_declaration_node);
	auto opt_init_declarator_list_node = get_init_declarator_list(simple_declaration_node);

	if(!opt_decl_specifier_seq_node)
		return false;

	if(opt_init_declarator_list_node)
	{
		auto init_declarator_list_node = *opt_init_declarator_list_node;
		for(auto i = init_declarator_list_node.begin(); i != init_declarator_list_node.end(); ++i)
		{
			auto declarator_node = get_declarator(i->main_node());
			if(is_simple_function_declaration(declarator_node))
				return true;
		}
	}

	return false;
}

bool
is_operator_function_declaration(const syntax_nodes::simple_declaration& simple_declaration_node)
{
	auto opt_decl_specifier_seq_node = get_decl_specifier_seq(simple_declaration_node);
	auto opt_init_declarator_list_node = get_init_declarator_list(simple_declaration_node);

	if(!opt_decl_specifier_seq_node)
		return false;

	if(opt_init_declarator_list_node)
	{
		auto init_declarator_list_node = *opt_init_declarator_list_node;
		for(auto i = init_declarator_list_node.begin(); i != init_declarator_list_node.end(); ++i)
		{
			auto declarator_node = get_declarator(i->main_node());
			if(is_operator_function_declaration(declarator_node))
				return true;
		}
	}

	return false;
}

bool
is_variable_declaration(const syntax_nodes::simple_declaration& simple_declaration_node)
{
	auto opt_decl_specifier_seq_node = get_decl_specifier_seq(simple_declaration_node);
	auto opt_init_declarator_list_node = get_init_declarator_list(simple_declaration_node);

	if(!opt_decl_specifier_seq_node)
		return false;

	if(opt_init_declarator_list_node)
	{
		auto init_declarator_list_node = *opt_init_declarator_list_node;
		for(auto i = init_declarator_list_node.begin(); i != init_declarator_list_node.end(); ++i)
		{
			auto declarator_node = get_declarator(i->main_node());
			auto direct_declarator_node = get_direct_declarator(declarator_node);
			auto direct_declarator_node_last_part_seq = get_last_part_seq(direct_declarator_node);
			if(direct_declarator_node_last_part_seq)
			{
				for(auto j = direct_declarator_node_last_part_seq->begin(); j != direct_declarator_node_last_part_seq->end(); ++j)
				{
					const direct_declarator_last_part& last_part = j->main_node();

					if(get<direct_declarator_function_part>(&last_part))
					{
						return false;
					}
				}
			}
		}

		return true;
	}

	return false;
}



//
//common
//

std::string
get_name(const declarator& declarator_node)
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
					return opt_identifier_node->value();
				}
				else if(auto opt_destructor_name_node = get<destructor_name>(&*opt_unqualified_id_node))
				{
					auto destructor_name_node = *opt_destructor_name_node;
					auto identifier_or_template_id = get_identifier_or_template_id(destructor_name_node);
					if(auto opt_identifier_node = get<identifier>(&identifier_or_template_id))
					{
						return opt_identifier_node->value();
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
						return opt_identifier_node->value();
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
				return opt_identifier_node->value();
			}
		}
		else
		{
			assert(false);
		}
	}

	throw std::runtime_error("Cannot find the name of the semantic entity");
}

bool
has_name(const declarator& declarator_node)
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

}}}} //namespace scalpel::cpp::detail::semantic_analysis

