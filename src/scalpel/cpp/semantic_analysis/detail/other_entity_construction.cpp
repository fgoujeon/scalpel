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

#include "other_entity_construction.hpp"
#include "class_construction.hpp"
#include "function_construction.hpp"
#include "type_construction.hpp"
#include "semantic_entity_analysis/get_namespace.hpp"
#include "semantic_entity_analysis/identification_policies.hpp"
#include "syntax_node_analysis/declarator.hpp"

namespace scalpel { namespace cpp { namespace semantic_analysis { namespace detail
{

using namespace syntax_nodes;
using namespace semantic_entities;

declarator_entity_ptr_variant
create_entity
(
	const syntax_nodes::declarator& declarator_node,
	const declarative_region_ptr_variant& current_declarative_region,
	boost::optional<semantic_entities::type_variant> opt_type,
	const bool has_typedef_specifier,
	const bool has_mutable_specifier,
	const bool has_static_specifier,
	const bool has_inline_specifier,
	const bool has_virtual_specifier,
	const bool has_explicit_specifier,
	const bool has_pure_specifier,
	const bool is_class_member,
	const semantic_entities::member_access access
)
{
	switch(syntax_node_analysis::get_declarator_type(declarator_node))
	{
		case syntax_node_analysis::declarator_type::SIMPLE_FUNCTION_DECLARATOR:
		{
			if(opt_type)
			{
				if(has_typedef_specifier)
				{
					opt_type = qualify_type(*opt_type, declarator_node, current_declarative_region);

					if(is_class_member)
					{
						return new member_typedef
						(
							syntax_node_analysis::get_identifier(declarator_node).value(),
							*opt_type,
							access
						);
					}
					else
					{
						return new typedef_
						(
							syntax_node_analysis::get_identifier(declarator_node).value(),
							*opt_type
						);
					}
				}
				else
				{
					if(syntax_node_analysis::has_bracketed_type_qualifiers(declarator_node))
					{
						opt_type = qualify_type(*opt_type, declarator_node, current_declarative_region);

						if(is_class_member)
						{
							return new member_variable
							(
								syntax_node_analysis::get_identifier(declarator_node).value(),
								*opt_type,
								has_static_specifier,
								has_mutable_specifier,
								access
							);
						}
						else
						{
							return new variable
							(
								syntax_node_analysis::get_identifier(declarator_node).value(),
								*opt_type,
								has_static_specifier
							);
						}
					}
					else
					{
						opt_type = qualify_type(*opt_type, declarator_node, current_declarative_region, true);

						if(is_class_member)
						{
							return new simple_member_function
							(
								syntax_node_analysis::get_identifier(declarator_node).value(),
								*opt_type,
								create_parameters(syntax_node_analysis::get_parameter_declaration_list(declarator_node), current_declarative_region),
								syntax_node_analysis::has_ellipsis(declarator_node),
								access,
								syntax_node_analysis::has_const_function_qualifier(declarator_node),
								syntax_node_analysis::has_volatile_function_qualifier(declarator_node),
								has_static_specifier,
								has_virtual_specifier,
								has_pure_specifier,
								has_inline_specifier
							);
						}
						else
						{
							return new simple_function
							(
								syntax_node_analysis::get_identifier(declarator_node).value(),
								*opt_type,
								create_parameters(syntax_node_analysis::get_parameter_declaration_list(declarator_node), current_declarative_region),
								syntax_node_analysis::has_ellipsis(declarator_node),
								has_static_specifier,
								has_inline_specifier
							);
						}
					}
				}
			}
			else
			{
				if(!is_class_member)
					throw std::runtime_error("create_entity error: a constructor must be a class member");

				return new constructor
				(
					create_parameters(syntax_node_analysis::get_parameter_declaration_list(declarator_node), current_declarative_region),
					syntax_node_analysis::has_ellipsis(declarator_node),
					access,
					has_explicit_specifier,
					has_inline_specifier
				);
			}
		}
		case syntax_node_analysis::declarator_type::DESTRUCTOR_DECLARATOR:
		{
			if(opt_type)
				throw std::runtime_error("create_entity error 2");

			if(!is_class_member)
				throw std::runtime_error("create_entity error: a destructor must be a class member");

			return new destructor
			(
				access,
				has_virtual_specifier,
				has_pure_specifier,
				has_inline_specifier
			);
		}
		case syntax_node_analysis::declarator_type::OPERATOR_FUNCTION_DECLARATOR:
		{
			if(!opt_type)
				throw std::runtime_error("create_entity error 3");

			opt_type = qualify_type(*opt_type, declarator_node, current_declarative_region, true);

			if(is_class_member)
			{
				return new operator_member_function
				(
					get_operator_function_operator(declarator_node),
					*opt_type,
					create_parameters(syntax_node_analysis::get_parameter_declaration_list(declarator_node), current_declarative_region),
					access,
					syntax_node_analysis::has_const_function_qualifier(declarator_node),
					syntax_node_analysis::has_volatile_function_qualifier(declarator_node),
					has_virtual_specifier,
					has_pure_specifier,
					has_inline_specifier
				);
			}
			else
			{
				return new operator_function
				(
					get_operator_function_operator(declarator_node),
					*opt_type,
					create_parameters(syntax_node_analysis::get_parameter_declaration_list(declarator_node), current_declarative_region),
					has_static_specifier,
					has_inline_specifier
				);
			}
		}
		case syntax_node_analysis::declarator_type::CONVERSION_FUNCTION_DECLARATOR:
		{
			if(opt_type)
				throw std::runtime_error("create_entity error 3b");

			if(!is_class_member)
				throw std::runtime_error("create_entity error: a conversion function must be a class member");

			return new conversion_function
			(
				get_conversion_function_type(declarator_node, current_declarative_region),
				access,
				syntax_node_analysis::has_const_function_qualifier(declarator_node),
				syntax_node_analysis::has_volatile_function_qualifier(declarator_node),
				has_virtual_specifier,
				has_pure_specifier,
				has_inline_specifier
			);
		}
		case syntax_node_analysis::declarator_type::VARIABLE_DECLARATOR:
		{
			if(!opt_type)
				throw std::runtime_error("create_entity error 4");

			opt_type = qualify_type(*opt_type, declarator_node, current_declarative_region);

			if(has_typedef_specifier)
			{
				if(is_class_member)
				{
					return new member_typedef
					(
						syntax_node_analysis::get_identifier(declarator_node).value(),
						*opt_type,
						access
					);
				}
				else
				{
					return new typedef_
					(
						syntax_node_analysis::get_identifier(declarator_node).value(),
						*opt_type
					);
				}
			}
			else
			{
				if(const function_type* opt_function_type = utility::get<function_type>(&*opt_type))
				{
					//the declaration looks like:
					//  typedef void fun_t(int);
					//  fun_t f;

					const function_type& ftype = *opt_function_type;
					const std::vector<type_variant>& parameter_types = ftype.parameter_types();

					function_parameter_list parameter_list;
					for(auto i = parameter_types.begin(); i != parameter_types.end(); ++i)
					{
						const type_variant& parameter_type = *i;
						parameter_list.push_back
						(
							std::unique_ptr<function_parameter>(new function_parameter(parameter_type))
						);
					}

					if(is_class_member)
					{
						return new simple_member_function
						(
							syntax_node_analysis::get_identifier(declarator_node).value(),
							ftype.return_type(),
							std::move(parameter_list),
							ftype.variadic(),
							access,
							ftype.const_qualified(),
							ftype.volatile_qualified(),
							has_static_specifier,
							has_virtual_specifier,
							has_pure_specifier,
							has_inline_specifier
						);
					}
					else
					{
						return new simple_function
						(
							syntax_node_analysis::get_identifier(declarator_node).value(),
							ftype.return_type(),
							std::move(parameter_list),
							ftype.variadic(),
							has_static_specifier,
							has_inline_specifier
						);
					}
				}
				else
				{
					if(is_class_member)
					{
						return new member_variable
						(
							syntax_node_analysis::get_identifier(declarator_node).value(),
							*opt_type,
							has_static_specifier,
							has_mutable_specifier,
							access
						);
					}
					else
					{
						return new variable
						(
							syntax_node_analysis::get_identifier(declarator_node).value(),
							*opt_type,
							has_static_specifier
						);
					}
				}
			}
		}
	}

	throw std::runtime_error("create_entity error 5");
}

}}}} //namespace scalpel::cpp::semantic_analysis::detail

