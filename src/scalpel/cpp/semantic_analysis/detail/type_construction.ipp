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

#ifndef SCALPEL_CPP_SEMANTIC_ANALYSIS_DETAIL_TYPE_CONSTRUCTION_IPP
#define SCALPEL_CPP_SEMANTIC_ANALYSIS_DETAIL_TYPE_CONSTRUCTION_IPP

#include "expression_construction.hpp"
#include "expression_evaluation.hpp"
#include "class_construction.hpp"
#include "name_lookup.hpp"
#include "syntax_node_analysis/class_specifier.hpp"
#include "syntax_node_analysis/enum_specifier.hpp"
#include "syntax_node_analysis/decl_specifier_seq.hpp"
#include "syntax_node_analysis/type_specifier_seq.hpp"
#include "syntax_node_analysis/declarator.hpp"
#include <scalpel/cpp/semantic_entities/type_traits/is_class.hpp>
#include <scalpel/cpp/semantic_entities/type_traits/is_union.hpp>
#include <scalpel/utility/type_alternative.hpp>

namespace scalpel { namespace cpp { namespace semantic_analysis { namespace detail
{

template<class DeclarativeRegion>
type_info
create_type
(
	const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node,
	const bool has_declarator,
	DeclarativeRegion& current_declarative_region,
	const semantic_entities::member_access access
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	const bool is_member =
		type_traits::is_class<DeclarativeRegion>::value ||
		type_traits::is_union<DeclarativeRegion>::value
	;

	type_info info;

	info.has_typedef_specifier = syntax_node_analysis::has_typedef_specifier(decl_specifier_seq_node);
	info.has_friend_specifier = syntax_node_analysis::has_friend_specifier(decl_specifier_seq_node);
	info.has_mutable_specifier = syntax_node_analysis::has_mutable_specifier(decl_specifier_seq_node);
	info.has_static_specifier = syntax_node_analysis::has_static_specifier(decl_specifier_seq_node);
	info.has_inline_specifier = syntax_node_analysis::has_inline_specifier(decl_specifier_seq_node);
	info.has_virtual_specifier = syntax_node_analysis::has_virtual_specifier(decl_specifier_seq_node);
	info.has_explicit_specifier = syntax_node_analysis::has_explicit_specifier(decl_specifier_seq_node);
	info.create_anonymous_object = false;

	//friend specifications are not implemented yet
	if(info.has_friend_specifier) return info;

	//create and/or get undecorated type
	syntax_node_analysis::type_specifier_seq_type type_specifier_seq_type =
		syntax_node_analysis::get_decl_specifier_seq_type(decl_specifier_seq_node)
	;
	switch(type_specifier_seq_type)
	{
		case syntax_node_analysis::type_specifier_seq_type::CLASS_DECLARATION:
		{
			const class_specifier& class_specifier_node =
				syntax_node_analysis::get_class_specifier(decl_specifier_seq_node)
			;
			const class_head& class_head_node = get_class_head(class_specifier_node);
			const optional_node<nested_name_specifier>& opt_nested_name_specifier_node =
				get_nested_name_specifier(class_head_node)
			;

			if(opt_nested_name_specifier_node)
			{
				//find the class
				utility::variant<class_*, member_class*> found_class =
					name_lookup::find
					<
						semantic_entity_analysis::identification_policies::by_name,
						false,
						false,
						class_,
						member_class
					>
					(
						false,
						opt_nested_name_specifier_node,
						syntax_node_analysis::get_identifier(class_specifier_node),
						&current_declarative_region,
						false
					)
				;

				if(class_** c = utility::get<class_*>(&found_class))
				{
					info.opt_defined_type = *c;
					info.opt_complete_type = *c;
				}
				else if(member_class** c = utility::get<member_class*>(&found_class))
				{
					info.opt_defined_type = *c;
					info.opt_complete_type = *c;
				}
			}
			else
			{
				const bool type_index = is_member ? 0 : 1;
				typedef typename utility::type_alternative<type_index, member_class, class_>::type class_t;

				const std::string& class_name = syntax_node_analysis::get_identifier(class_specifier_node);

				//has the class been already declared?
				if(class_t* found_class = detail::find_type<class_t>(current_declarative_region, class_name))
				{
					info.opt_defined_type = found_class;
					info.opt_complete_type = found_class;
				}
				else
				{
					class_t* new_class = detail::create_type<class_t>(class_name, access);
					info.opt_new_type = new_class;
					info.opt_defined_type = new_class;
					info.opt_complete_type = new_class;
				}
			}

			break;
		}
		case syntax_node_analysis::type_specifier_seq_type::CLASS_FORWARD_DECLARATION:
		{
			const syntax_nodes::class_elaborated_specifier& class_elaborated_specifier_node =
				syntax_node_analysis::get_class_elaborated_specifier(decl_specifier_seq_node)
			;
			const identifier_or_template_id& identifier_or_template_id_node =
				get_identifier_or_template_id(class_elaborated_specifier_node)
			;

			if(const boost::optional<const identifier&> opt_identifier_node = get<identifier>(&identifier_or_template_id_node))
			{
				const bool type_index = is_member ? 0 : 1;
				typedef typename utility::type_alternative<type_index, member_class, class_>::type class_t;

				const std::string& class_name = opt_identifier_node->value();

				//has the class been already declared?
				if(class_t* found_class = detail::find_type<class_t>(current_declarative_region, class_name))
				{
					info.opt_complete_type = found_class;
				}
				else
				{
					class_t* new_class = detail::create_type<class_t>(class_name, access);
					info.opt_new_type = new_class;
					info.opt_complete_type = new_class;
				}
			}
			else
			{
				assert(false); //not implemented yet
			}

			break;
		}
		case syntax_node_analysis::type_specifier_seq_type::UNION_DECLARATION:
		{
			const class_specifier& class_specifier_node =
				syntax_node_analysis::get_class_specifier(decl_specifier_seq_node)
			;
			const class_head& class_head_node = get_class_head(class_specifier_node);
			const optional_node<nested_name_specifier>& opt_nested_name_specifier_node =
				get_nested_name_specifier(class_head_node)
			;

			if(opt_nested_name_specifier_node)
			{
				//find the union
				utility::variant<union_*, member_union*> found_union =
					name_lookup::find
					<
						semantic_entity_analysis::identification_policies::by_name,
						false,
						false,
						union_,
						member_union
					>
					(
						false,
						opt_nested_name_specifier_node,
						syntax_node_analysis::get_identifier(class_specifier_node),
						&current_declarative_region,
						false
					)
				;

				if(union_** c = utility::get<union_*>(&found_union))
				{
					info.opt_defined_type = *c;
					info.opt_complete_type = *c;
				}
				else if(member_union** c = utility::get<member_union*>(&found_union))
				{
					info.opt_defined_type = *c;
					info.opt_complete_type = *c;
				}
			}
			else
			{
				//is it an anonymous union?
				const bool anonymous =
					syntax_node_analysis::get_identifier(class_specifier_node).empty() &&
					!has_declarator
				;

				if(anonymous)
				{
					const bool type_index = is_member ? 0 : 1;
					typedef typename utility::type_alternative<type_index, anonymous_member_union, anonymous_union>::type union_t;

					union_t* new_union = detail::create_type<union_t>(access);
					info.opt_new_type = new_union;
					info.opt_defined_type = new_union;
					info.opt_complete_type = new_union;

					info.create_anonymous_object = true;
				}
				else
				{
					const bool type_index = is_member ? 0 : 1;
					typedef typename utility::type_alternative<type_index, member_union, union_>::type union_t;

					const std::string& union_name = syntax_node_analysis::get_identifier(class_specifier_node);

					//has the union been already declared?
					if(union_t* found_union = detail::find_type<union_t>(current_declarative_region, union_name))
					{
						info.opt_defined_type = found_union;
						info.opt_complete_type = found_union;
					}
					else
					{
						union_t* new_union = detail::create_type<union_t>(union_name, access);
						info.opt_new_type = new_union;
						info.opt_defined_type = new_union;
						info.opt_complete_type = new_union;
					}
				}
			}

			break;
		}
		case syntax_node_analysis::type_specifier_seq_type::UNION_FORWARD_DECLARATION:
		{
			const syntax_nodes::class_elaborated_specifier& class_elaborated_specifier_node =
				syntax_node_analysis::get_class_elaborated_specifier(decl_specifier_seq_node)
			;
			const identifier_or_template_id& identifier_or_template_id_node =
				get_identifier_or_template_id(class_elaborated_specifier_node)
			;

			if(const boost::optional<const identifier&> opt_identifier_node = get<identifier>(&identifier_or_template_id_node))
			{
				const bool type_index = is_member ? 0 : 1;
				typedef typename utility::type_alternative<type_index, member_union, union_>::type union_t;

				const std::string& union_name = opt_identifier_node->value();

				//has the union been already declared?
				if(union_t* found_union = detail::find_type<union_t>(current_declarative_region, union_name))
				{
					info.opt_complete_type = found_union;
				}
				else
				{
					union_t* new_union = detail::create_type<union_t>(union_name, access);
					info.opt_new_type = new_union;
					info.opt_complete_type = new_union;
				}
			}
			else
			{
				assert(false); //not implemented yet
			}

			break;
		}
		case syntax_node_analysis::type_specifier_seq_type::ENUMERATION_DECLARATION:
		{
			const bool type_index = is_member ? 0 : 1;
			typedef typename utility::type_alternative<type_index, member_enum_t, enum_t>::type enum_type;

			const enum_specifier& enum_specifier_node =
				syntax_node_analysis::get_enum_specifier(decl_specifier_seq_node)
			;
			const std::string& enum_name = syntax_node_analysis::get_identifier(enum_specifier_node);

			enum_type* new_enum = detail::create_type<enum_type>(enum_name, access);
			info.opt_new_type = new_enum;
			info.opt_defined_type = new_enum;
			info.opt_complete_type = new_enum;

			break;
		}
		case syntax_node_analysis::type_specifier_seq_type::SIMPLE_TYPE:
		{
			info.opt_complete_type = detail::create_simple_type(decl_specifier_seq_node, &current_declarative_region);
			break;
		}
		case syntax_node_analysis::type_specifier_seq_type::NO_TYPE:
		{
			break;
		}
	}

	//qualify type
	if(info.opt_complete_type)
		info.opt_complete_type = qualify_type(*info.opt_complete_type, decl_specifier_seq_node);

	return info;
}

template<class DeclarativeRegion>
type_info
create_type
(
	const syntax_nodes::type_specifier_seq& type_specifier_seq_node,
	const bool has_declarator,
	DeclarativeRegion& current_declarative_region,
	const semantic_entities::member_access access
)
{
	return create_type
	(
		syntax_node_analysis::to_decl_specifier_seq(type_specifier_seq_node),
		has_declarator,
		current_declarative_region,
		access
	);
}



template<class DeclarativeRegion>
semantic_entities::type_t
qualify_type
(
	semantic_entities::type_t type,
	const syntax_nodes::declarator& declarator_node,
	DeclarativeRegion& current_declarative_region,
	const bool ignore_function_type
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	const direct_declarator& direct_declarator_node = get_direct_declarator(declarator_node);
	const direct_declarator_first_part& first_part_node = get_first_part(direct_declarator_node);

	//pointers
	if(auto opt_ptr_operator_seq_node = get_ptr_operator_seq(declarator_node))
	{
		auto ptr_operator_seq_node = *opt_ptr_operator_seq_node;
		type = qualify_type(type, ptr_operator_seq_node, &current_declarative_region);
	}

	//arrays and function type
	if(const optional_node<direct_declarator_last_part_seq>& opt_last_part_seq_node = get_last_part_seq(direct_declarator_node))
	{
		const direct_declarator_last_part_seq& last_part_seq_node = *opt_last_part_seq_node;
		type = qualify_type(type, last_part_seq_node, current_declarative_region, ignore_function_type);
	}

	//bracketed-declarator's qualifiers
	if(const boost::optional<const bracketed_declarator&> opt_bracketed_declarator_node = get<bracketed_declarator>(&first_part_node))
	{
		const bracketed_declarator& bracketed_declarator_node = *opt_bracketed_declarator_node;
		type = qualify_type(type, get_declarator(bracketed_declarator_node), current_declarative_region);
	}

	return type;
}

template<class DeclarativeRegion>
semantic_entities::type_t
qualify_type
(
	semantic_entities::type_t type,
	const syntax_nodes::abstract_declarator& abstract_declarator_node,
	DeclarativeRegion& current_declarative_region
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	if(const optional_node<ptr_operator_seq>& opt_ptr_operator_seq_node = get_ptr_operator_seq(abstract_declarator_node))
	{
		type = qualify_type(type, *opt_ptr_operator_seq_node, &current_declarative_region);
	}

	if(const optional_node<direct_abstract_declarator>& opt_direct_abstract_declarator_node = get_direct_abstract_declarator(abstract_declarator_node))
	{
		const direct_abstract_declarator& direct_abstract_declarator_node = *opt_direct_abstract_declarator_node;

		if
		(
			boost::optional<const bracketed_abstract_declarator&> opt_bracketed_abstract_declarator_node =
				get<bracketed_abstract_declarator>(&direct_abstract_declarator_node)
		)
		{
			const bracketed_abstract_declarator& bracketed_abstract_declarator_node = *opt_bracketed_abstract_declarator_node;

			if
			(
				const optional_node<direct_declarator_last_part>& opt_last_part_node =
					get_last_part(bracketed_abstract_declarator_node)
			)
			{
				const direct_declarator_last_part& last_part_node = *opt_last_part_node;
				type = qualify_type(type, last_part_node, current_declarative_region, false);
			}

			const abstract_declarator& abstract_declarator_node = get_abstract_declarator(bracketed_abstract_declarator_node);
			type = qualify_type(type, abstract_declarator_node, current_declarative_region);
		}
		else if
		(
			boost::optional<const direct_declarator_last_part_seq&> opt_direct_declarator_last_part_seq_node =
				get<direct_declarator_last_part_seq>(&direct_abstract_declarator_node)
		)
		{
			const direct_declarator_last_part_seq& last_part_seq_node = *opt_direct_declarator_last_part_seq_node;
			type = qualify_type(type, last_part_seq_node, current_declarative_region, false);
		}
	}

	return type;
}

template<class DeclarativeRegion>
semantic_entities::type_t
qualify_type
(
	semantic_entities::type_t type,
	const syntax_nodes::direct_declarator_last_part_seq& last_part_seq_node,
	DeclarativeRegion& current_declarative_region,
	const bool ignore_function_type
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	for(auto i = last_part_seq_node.rbegin(); i != last_part_seq_node.rend(); ++i)
	{
		const direct_declarator_last_part& last_part_node = *i;
		type = qualify_type(type, last_part_node, current_declarative_region, ignore_function_type);
	}

	return type;
}

template<class DeclarativeRegion>
semantic_entities::type_t
qualify_type
(
	semantic_entities::type_t type,
	const syntax_nodes::direct_declarator_last_part& last_part_node,
	DeclarativeRegion& current_declarative_region,
	const bool ignore_function_type
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	if(!ignore_function_type)
	{
		if(const boost::optional<const direct_declarator_function_part&> opt_function_part_node = get<direct_declarator_function_part>(&last_part_node))
		{
			type =
				function_type
				(
					type, //return type
					create_parameter_types(syntax_node_analysis::get_parameter_declaration_list(last_part_node), current_declarative_region),
					syntax_node_analysis::has_ellipsis(last_part_node),
					syntax_node_analysis::has_const_function_qualifier(last_part_node),
					syntax_node_analysis::has_volatile_function_qualifier(last_part_node)
				)
			;
		}
	}

	if
	(
		const boost::optional<const direct_declarator_array_part&> opt_array_part_node =
			get<direct_declarator_array_part>(&last_part_node)
	)
	{
		if(const optional_node<syntax_nodes::conditional_expression>& opt_conditional_expression_node = get_conditional_expression(*opt_array_part_node))
		{
			const syntax_nodes::conditional_expression& conditional_expression_node = *opt_conditional_expression_node;

			const semantic_entities::expression_t expr = create_expression_from_conditional_expression(conditional_expression_node, current_declarative_region);
			const unsigned int size = evaluate_expression_to_unsigned_int(expr);

			type = array(size, type);
		}
		else
		{
			//int i[] == int i*
			type = pointer(type);
		}
	}

	return type;
}



namespace detail
{
	template<class Type>
	Type*
	create_type
	(
		const std::string& type_name,
		const semantic_entities::member_access access,
		typename boost::enable_if<semantic_entities::type_traits::is_member<Type>>::type*
	)
	{
		return new Type(type_name, access);
	}

	template<class Type>
	Type*
	create_type
	(
		const std::string& type_name,
		const semantic_entities::member_access, //ignored
		typename boost::disable_if<semantic_entities::type_traits::is_member<Type>>::type*
	)
	{
		return new Type(type_name);
	}

	template<class Type>
	Type*
	create_type
	(
		const semantic_entities::member_access access,
		typename boost::enable_if<semantic_entities::type_traits::is_member<Type>>::type*
	)
	{
		return new Type(access);
	}

	template<class Type>
	Type*
	create_type
	(
		const semantic_entities::member_access, //ignored
		typename boost::disable_if<semantic_entities::type_traits::is_member<Type>>::type*
	)
	{
		return new Type();
	}



	template<class Type, class DeclarativeRegion>
	Type*
	find_type
	(
		DeclarativeRegion& declarative_region,
		const std::string& type_name
	)
	{
		return
			name_lookup::find_local
			<
				semantic_entity_analysis::identification_policies::by_name,
				DeclarativeRegion,
				true,
				false,
				Type
			>
			(
				type_name,
				declarative_region
			)
		;
	}
}

}}}} //namespace scalpel::cpp::semantic_analysis::detail

#endif

