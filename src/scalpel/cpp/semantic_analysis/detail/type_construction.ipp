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

#include "class_construction.hpp"
#include "name_lookup.hpp"
#include "syntax_node_analysis/class_specifier.hpp"
#include "syntax_node_analysis/decl_specifier_seq.hpp"

namespace scalpel { namespace cpp { namespace semantic_analysis { namespace detail
{

template<class DeclarativeRegion>
type_info
create_type
(
	const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node,
	const bool has_declarator,
	DeclarativeRegion& current_declarative_region,
	const bool is_member,
	const semantic_entities::member_access access
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

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
				const std::string& class_name = syntax_node_analysis::get_identifier(class_specifier_node);

				if(is_member)
				{
					//has the class been already declared?
					member_class* found_class =
						name_lookup::find_local
						<
							semantic_entity_analysis::identification_policies::by_name,
							DeclarativeRegion,
							true,
							false,
							member_class
						>
						(
							class_name,
							current_declarative_region
						)
					;

					if(found_class)
					{
						info.opt_defined_type = found_class;
						info.opt_complete_type = found_class;
					}
					else
					{
						member_class* new_class = new member_class(class_name, access);
						info.opt_new_type = new_class;
						info.opt_defined_type = new_class;
						info.opt_complete_type = new_class;
					}
				}
				else
				{
					//has the class been already declared?
					class_* found_class =
						name_lookup::find_local
						<
							semantic_entity_analysis::identification_policies::by_name,
							DeclarativeRegion,
							true,
							false,
							class_
						>
						(
							class_name,
							current_declarative_region
						)
					;

					if(found_class)
					{
						info.opt_defined_type = found_class;
						info.opt_complete_type = found_class;
					}
					else
					{
						class_* new_class = new class_(class_name);
						info.opt_new_type = new_class;
						info.opt_defined_type = new_class;
						info.opt_complete_type = new_class;
					}
				}
			}

			break;
		}
		case syntax_node_analysis::type_specifier_seq_type::CLASS_FORWARD_DECLARATION:
		{
			const syntax_nodes::class_elaborated_specifier& class_elaborated_specifier_node =
				syntax_node_analysis::get_class_elaborated_specifier(decl_specifier_seq_node)
			;

			if(is_member)
			{
				member_class* new_class = create_member_class2<member_class>(class_elaborated_specifier_node, access);

				//has the class been already declared?
				member_class* found_class =
					name_lookup::find_local
					<
						semantic_entity_analysis::identification_policies::by_name,
						DeclarativeRegion,
						true,
						false,
						member_class
					>
					(
						new_class->name(),
						current_declarative_region
					)
				;

				if(found_class)
				{
					info.opt_complete_type = found_class;
				}
				else
				{
					info.opt_new_type = new_class;
					info.opt_complete_type = new_class;
				}
			}
			else
			{
				class_* new_class = create_class2<class_>(class_elaborated_specifier_node);

				//has the class been already declared?
				class_* found_class =
					name_lookup::find_local
					<
						semantic_entity_analysis::identification_policies::by_name,
						DeclarativeRegion,
						true,
						false,
						class_
					>
					(
						new_class->name(),
						current_declarative_region
					)
				;

				if(found_class)
				{
					info.opt_complete_type = found_class;
				}
				else
				{
					info.opt_new_type = new_class;
					info.opt_complete_type = new_class;
				}
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
					if(is_member)
					{




						anonymous_member_union* new_union = new anonymous_member_union();
						info.opt_new_type = new_union;
						info.opt_defined_type = new_union;
						info.opt_complete_type = new_union;
					}
					else
					{
						anonymous_union* new_union = new anonymous_union();
						info.opt_new_type = new_union;
						info.opt_defined_type = new_union;
						info.opt_complete_type = new_union;
					}

					info.create_anonymous_object = true;
				}
				else
				{
					const std::string& union_name = syntax_node_analysis::get_identifier(class_specifier_node);

					if(is_member)
					{
						//has the union been already declared?
						member_union* found_union =
							name_lookup::find_local
							<
								semantic_entity_analysis::identification_policies::by_name,
								DeclarativeRegion,
								true,
								false,
								member_union
							>
							(
								union_name,
								current_declarative_region
							)
						;

						if(found_union)
						{
							info.opt_defined_type = found_union;
							info.opt_complete_type = found_union;
						}
						else
						{
							member_union* new_union = new member_union(union_name, access);
							info.opt_new_type = new_union;
							info.opt_defined_type = new_union;
							info.opt_complete_type = new_union;
						}
					}
					else
					{
						//has the union been already declared?
						union_* found_union =
							name_lookup::find_local
							<
								semantic_entity_analysis::identification_policies::by_name,
								DeclarativeRegion,
								true,
								false,
								union_
							>
							(
								union_name,
								current_declarative_region
							)
						;

						if(found_union)
						{
							info.opt_defined_type = found_union;
							info.opt_complete_type = found_union;
						}
						else
						{
							union_* new_union = new union_(union_name);
							info.opt_new_type = new_union;
							info.opt_defined_type = new_union;
							info.opt_complete_type = new_union;
						}
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

			if(is_member)
			{
				member_union* new_union = create_member_class2<member_union>(class_elaborated_specifier_node, access);

				//has the union been already declared?
				member_union* found_union =
					name_lookup::find_local
					<
						semantic_entity_analysis::identification_policies::by_name,
						DeclarativeRegion,
						true,
						false,
						member_union
					>
					(
						new_union->name(),
						current_declarative_region
					)
				;

				if(found_union)
				{
					info.opt_complete_type = found_union;
				}
				else
				{
					info.opt_new_type = new_union;
					info.opt_complete_type = new_union;
				}
			}
			else
			{
				union_* new_union = create_class2<union_>(class_elaborated_specifier_node);

				//has the union been already declared?
				union_* found_union =
					name_lookup::find_local
					<
						semantic_entity_analysis::identification_policies::by_name,
						DeclarativeRegion,
						true,
						false,
						union_
					>
					(
						new_union->name(),
						current_declarative_region
					)
				;

				if(found_union)
				{
					info.opt_complete_type = found_union;
				}
				else
				{
					info.opt_new_type = new_union;
					info.opt_complete_type = new_union;
				}
			}

			break;
		}
//		{
//			const syntax_nodes::class_elaborated_specifier& class_elaborated_specifier_node =
//				syntax_node_analysis::get_class_elaborated_specifier(decl_specifier_seq_node)
//			;
//
//			if(is_member)
//			{
//				member_union* new_union = create_member_class2<member_union>(class_elaborated_specifier_node, access);
//				info.opt_new_type = new_union;
//				info.opt_complete_type = new_union;
//			}
//			else
//			{
//				union_* new_union = create_class2<union_>(class_elaborated_specifier_node);
//				info.opt_new_type = new_union;
//				info.opt_complete_type = new_union;
//			}
//
//			break;
//		}
		case syntax_node_analysis::type_specifier_seq_type::ENUMERATION_DECLARATION:
		{
			const enum_specifier& enum_specifier_node =
				syntax_node_analysis::get_enum_specifier(decl_specifier_seq_node)
			;

			if(is_member)
			{
				member_enum* new_enum = create_member_enum2(enum_specifier_node, access);
				info.opt_new_type = new_enum;
				info.opt_defined_type = new_enum;
				info.opt_complete_type = new_enum;
			}
			else
			{
				enum_* new_enum = create_enum2(enum_specifier_node);
				info.opt_new_type = new_enum;
				info.opt_defined_type = new_enum;
				info.opt_complete_type = new_enum;
			}

			break;
		}
		case syntax_node_analysis::type_specifier_seq_type::SIMPLE_TYPE:
		{
			info.opt_complete_type = create_simple_type(decl_specifier_seq_node, &current_declarative_region);
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

}}}} //namespace scalpel::cpp::semantic_analysis::detail

#endif

