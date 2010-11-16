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

	if(!has_identifier(declarator_node))
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
//decl_specifier_seq related
//

decl_specifier_seq_type
get_decl_specifier_seq_type(const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node)
{
	//
	//node counters' declaration
	//

	unsigned int class_specifier_count = 0; //class XXX {...};
	unsigned int class_elaborated_specifier_count = 0; //class XXX;
	unsigned int simple_type_specifier_count = 0;
	unsigned int typedef_keyword_count = 0;
	unsigned int friend_keyword_count = 0;



	//
	//node counting
	//

	for(auto i = decl_specifier_seq_node.begin(); i != decl_specifier_seq_node.end(); ++i)
	{
		auto decl_specifier_node = i->main_node();

		if(auto opt_type_specifier_node = get<type_specifier>(&decl_specifier_node))
		{
			auto type_specifier_node = *opt_type_specifier_node;

			if(get<simple_type_specifier>(&type_specifier_node))
			{
				++simple_type_specifier_count;
			}
			else if(get<class_specifier>(&type_specifier_node))
			{
				++class_specifier_count;
			}
			else if(get<enum_specifier>(&type_specifier_node))
			{
			}
			else if(auto opt_elaborated_type_specifier_node = get<elaborated_type_specifier>(&type_specifier_node))
			{
				auto elaborated_type_specifier_node = *opt_elaborated_type_specifier_node;

				if(get<class_elaborated_specifier>(&elaborated_type_specifier_node))
				{
					++class_elaborated_specifier_count;
				}
				else if(get<enum_elaborated_specifier>(&elaborated_type_specifier_node))
				{
				}
				else if(get<typename_template_elaborated_specifier>(&elaborated_type_specifier_node))
				{
				}
				else if(get<typename_elaborated_specifier>(&elaborated_type_specifier_node))
				{
				}
			}
			else if(get<cv_qualifier>(&type_specifier_node))
			{
			}
		}
		else if(get<function_specifier>(&decl_specifier_node))
		{
		}
		else if(get<storage_class_specifier>(&decl_specifier_node))
		{
		}
		else if(get<function_specifier>(&decl_specifier_node))
		{
		}
		else if(get<predefined_text_node<str::friend_>>(&decl_specifier_node))
		{
			++friend_keyword_count;
		}
		else if(get<predefined_text_node<str::typedef_>>(&decl_specifier_node))
		{
			++typedef_keyword_count;
		}
	}



	//
	//result
	//

	if
	(
		class_specifier_count == 0 &&
		class_elaborated_specifier_count == 0 &&
		simple_type_specifier_count >= 1 &&
		typedef_keyword_count == 0 &&
		friend_keyword_count == 0
	)
		return decl_specifier_seq_type::SIMPLE_DECL_SPECIFIER_SEQ;
	else if
	(
		class_specifier_count == 1 &&
		class_elaborated_specifier_count == 0 &&
		simple_type_specifier_count == 0 &&
		typedef_keyword_count == 0 &&
		friend_keyword_count == 0
	)
		return decl_specifier_seq_type::CLASS_DECL_SPECIFIER_SEQ;
	else if
	(
		class_specifier_count == 0 &&
		class_elaborated_specifier_count == 1 &&
		simple_type_specifier_count == 0 &&
		typedef_keyword_count == 0 &&
		friend_keyword_count == 0
	)
		return decl_specifier_seq_type::CLASS_FORWARD_DECL_SPECIFIER_SEQ;
	else if
	(
		class_specifier_count == 0 &&
		class_elaborated_specifier_count == 0 &&
		simple_type_specifier_count >= 1 &&
		typedef_keyword_count == 1 &&
		friend_keyword_count == 0
	)
		return decl_specifier_seq_type::TYPEDEF_DECL_SPECIFIER_SEQ;

	throw std::runtime_error("get_decl_specifier_seq_type error");
}

const syntax_nodes::class_specifier&
get_class_specifier(const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node)
{
	assert(decl_specifier_seq_node.size() == 1);

	const decl_specifier& decl_specifier_node = decl_specifier_seq_node.front().main_node();

	const boost::optional<const type_specifier&> opt_type_specifier_node = get<type_specifier>(&decl_specifier_node);
	assert(opt_type_specifier_node);

	const type_specifier& type_specifier_node = *opt_type_specifier_node;

	const boost::optional<const class_specifier&> opt_class_specifier_node = get<class_specifier>(&type_specifier_node);
	assert(opt_class_specifier_node);

	return *opt_class_specifier_node;
}

const syntax_nodes::class_elaborated_specifier&
get_class_elaborated_specifier(const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node)
{
	assert(decl_specifier_seq_node.size() == 1);

	const decl_specifier& decl_specifier_node = decl_specifier_seq_node.front().main_node();

	const boost::optional<const type_specifier&> opt_type_specifier_node = get<type_specifier>(&decl_specifier_node);
	assert(opt_type_specifier_node);

	const type_specifier& type_specifier_node = *opt_type_specifier_node;

	const boost::optional<const elaborated_type_specifier&> opt_elaborated_type_specifier_node = get<elaborated_type_specifier>(&type_specifier_node);
	assert(opt_elaborated_type_specifier_node);

	const elaborated_type_specifier& elaborated_type_specifier_node = *opt_elaborated_type_specifier_node;

	const boost::optional<const class_elaborated_specifier&> opt_class_elaborated_specifier_node = get<class_elaborated_specifier>(&elaborated_type_specifier_node);
	assert(opt_class_elaborated_specifier_node);

	return *opt_class_elaborated_specifier_node;
}



//
//declarator related
//

declarator_type
get_declarator_type(const syntax_nodes::declarator& declarator_node)
{
	//
	//node counters' declaration
	//

	unsigned int operator_function_id_count = 0;
	unsigned int direct_declarator_function_part_count = 0;



	//
	//node counting
	//

	auto direct_declarator_node = get_direct_declarator(declarator_node);

	auto first_part_node = get_first_part(direct_declarator_node);
	if(get<bracketed_declarator>(&first_part_node))
	{
	}
	else if(auto opt_declarator_id_node = get<declarator_id>(&first_part_node))
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
					++operator_function_id_count;
				}
				else if(get<conversion_function_id>(&unqualified_id_node))
				{
				}
				else if(get<destructor_name>(&unqualified_id_node))
				{
				}
				else if(get<template_id>(&unqualified_id_node))
				{
				}
				else if(get<identifier>(&unqualified_id_node))
				{
				}
			}
			else if(get<qualified_id>(&id_expression_node))
			{
			}
		}
		else if(get<nested_identifier_or_template_id>(&declarator_id_node))
		{
		}
	}

	if(auto opt_last_part_seq_node = get_last_part_seq(direct_declarator_node))
	{
		auto last_part_seq_node = *opt_last_part_seq_node;

		for(auto j = last_part_seq_node.begin(); j != last_part_seq_node.end(); ++j)
		{
			const direct_declarator_last_part& last_part_node = j->main_node();

			if(get<direct_declarator_function_part>(&last_part_node))
			{
				++direct_declarator_function_part_count;
			}
			else if(get<direct_declarator_array_part>(&last_part_node))
			{
			}
		}
	}



	//
	//result
	//

	if
	(
		operator_function_id_count == 0 &&
		direct_declarator_function_part_count == 1
	)
		return declarator_type::SIMPLE_FUNCTION_DECLARATOR;
	else if
	(
		operator_function_id_count == 1 &&
		direct_declarator_function_part_count == 1
	)
		return declarator_type::OPERATOR_FUNCTION_DECLARATOR;
	else if
	(
		operator_function_id_count == 0 &&
		direct_declarator_function_part_count == 0
	)
		return declarator_type::VARIABLE_DECLARATOR;

	throw std::runtime_error("get_declarator_type error");
}



//
//common
//

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

	throw std::runtime_error("Cannot find the name of the semantic entity");
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

}}}} //namespace scalpel::cpp::detail::semantic_analysis

