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

#include "type_construction.hpp"
#include "function_construction.hpp"
#include "class_construction.hpp"
#include "name_lookup.hpp"
#include "semantic_entity_analysis/to_type_variant.hpp"
#include "syntax_node_analysis/declarator.hpp"
#include "syntax_node_analysis/decl_specifier_seq.hpp"
#include <scalpel/cpp/semantic_entities/type_traits/is_class.hpp>
#include <scalpel/cpp/semantic_entities/type_traits/is_union.hpp>
#include <scalpel/cpp/semantic_entities/type_traits/is_enum.hpp>

namespace scalpel { namespace cpp { namespace semantic_analysis { namespace detail
{

using namespace syntax_nodes;
using namespace semantic_entities;

type_info
create_type
(
	const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node,
	const bool has_declarator,
	const semantic_entities::declarative_region_ptr_variant current_declarative_region,
	const bool /*is_member*/,
	const semantic_entities::member_access access
)
{
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
	switch(syntax_node_analysis::get_decl_specifier_seq_type(decl_specifier_seq_node))
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
				class_* found_class =
					name_lookup::find<semantic_entity_analysis::identification_policies::by_name, false, false, class_>
					(
						false,
						opt_nested_name_specifier_node,
						syntax_node_analysis::get_identifier(class_specifier_node),
						current_declarative_region,
						false
					)
				;

				info.opt_complete_type = found_class;
			}
			else
			{
				member_class* new_class = create_member_class2<member_class>(class_specifier_node, access);

				info.opt_new_type = new_class;
				info.opt_complete_type = new_class;
			}

			break;
		}
		case syntax_node_analysis::type_specifier_seq_type::CLASS_FORWARD_DECLARATION:
		{
			const syntax_nodes::class_elaborated_specifier& class_elaborated_specifier_node =
				syntax_node_analysis::get_class_elaborated_specifier(decl_specifier_seq_node)
			;

			member_class* new_class = create_member_class2<member_class>(class_elaborated_specifier_node, access);

			info.opt_new_type = new_class;
			info.opt_complete_type = new_class;

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
				member_union* found_union =
					name_lookup::find<semantic_entity_analysis::identification_policies::by_name, false, false, member_union>
					(
						false,
						opt_nested_name_specifier_node,
						syntax_node_analysis::get_identifier(class_specifier_node),
						current_declarative_region,
						false
					)
				;

				info.opt_complete_type = found_union;
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
					anonymous_member_union* new_union = new anonymous_member_union();

					info.opt_new_type = new_union;
					info.opt_complete_type = new_union;
					info.create_anonymous_object = true;
				}
				else
				{
					member_union* new_union = create_member_class2<member_union>(class_specifier_node, access);

					info.opt_new_type = new_union;
					info.opt_complete_type = new_union;
				}
			}

			break;
		}
		case syntax_node_analysis::type_specifier_seq_type::UNION_FORWARD_DECLARATION:
		{
			const syntax_nodes::class_elaborated_specifier& class_elaborated_specifier_node =
				syntax_node_analysis::get_class_elaborated_specifier(decl_specifier_seq_node)
			;

			member_union* new_union = create_member_class2<member_union>(class_elaborated_specifier_node, access);

			info.opt_new_type = new_union;
			info.opt_complete_type = new_union;

			break;
		}
		case syntax_node_analysis::type_specifier_seq_type::ENUMERATION_DECLARATION:
		{
			const enum_specifier& enum_specifier_node =
				syntax_node_analysis::get_enum_specifier(decl_specifier_seq_node)
			;

			member_enum* new_enum = create_member_enum2(enum_specifier_node, access);

			info.opt_new_type = new_enum;
			info.opt_complete_type = new_enum;

			break;
		}
		case syntax_node_analysis::type_specifier_seq_type::SIMPLE_TYPE:
		{
			info.opt_complete_type = create_simple_type(decl_specifier_seq_node, current_declarative_region);
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

semantic_entities::type_variant
create_simple_type
(
	const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node,
	const declarative_region_ptr_variant current_declarative_region
)
{
	return create_simple_type(syntax_node_analysis::to_type_specifier_seq(decl_specifier_seq_node), current_declarative_region);
}

semantic_entities::type_variant
create_simple_type
(
	const syntax_nodes::type_specifier_seq& type_specifier_seq_node,
	const semantic_entities::declarative_region_ptr_variant current_declarative_region
)
{
	boost::optional<semantic_entities::type_variant> opt_return_type;
	bool is_fundamental_type = false;
	bool bool_type = false;
	bool char_type = false;
	bool double_type = false;
	bool float_type = false;
	bool int_type = false;
	bool long_long_type = false;
	bool long_type = false;
	bool short_type = false;
	bool signed_type = false;
	bool unsigned_type = false;
	bool void_type = false;
	bool wchar_t_type = false;

	for
	(
		auto i = type_specifier_seq_node.begin();
		i < type_specifier_seq_node.end();
		++i
	)
	{
		const syntax_nodes::type_specifier& type_specifier_node = *i;

		if(auto opt_simple_type_specifier_node = get<simple_type_specifier>(&type_specifier_node))
		{
			auto simple_type_specifier_node = *opt_simple_type_specifier_node;

			if(auto opt_nested_identifier_or_template_id_node = get<nested_identifier_or_template_id>(&simple_type_specifier_node))
			{
				auto nested_identifier_or_template_id_node = *opt_nested_identifier_or_template_id_node;

				std::string entity_name;
				if(boost::optional<const identifier&> opt_identifier_node = get<identifier>(&get_identifier_or_template_id(nested_identifier_or_template_id_node)))
					entity_name = opt_identifier_node->value();
				else
					assert(false);

				utility::ptr_variant
				<
					class_,
					member_class,
					union_,
					member_union,
					typedef_,
					member_typedef,
					enum_,
					member_enum
				>::type found_type =
					name_lookup::find
					<
						semantic_entity_analysis::identification_policies::by_name,
						false,
						false,
						class_,
						member_class,
						union_,
						member_union,
						typedef_,
						member_typedef,
						enum_,
						member_enum
					>
					(
						has_leading_double_colon(nested_identifier_or_template_id_node),
						get_nested_name_specifier(nested_identifier_or_template_id_node),
						entity_name,
						current_declarative_region
					)
				;

				opt_return_type = semantic_entity_analysis::to_type_variant(found_type);
			}
			else if(auto opt_fundamental_type_specifier_node = get<fundamental_type_specifier>(&simple_type_specifier_node))
			{
				auto fundamental_type_specifier_node = *opt_fundamental_type_specifier_node;

				is_fundamental_type = true;

				if(get<predefined_text_node<str::char_>>(&fundamental_type_specifier_node))
					char_type = true;
				else if(get<predefined_text_node<str::wchar_t_>>(&fundamental_type_specifier_node))
					wchar_t_type = true;
				else if(get<predefined_text_node<str::bool_>>(&fundamental_type_specifier_node))
					bool_type = true;
				else if(get<predefined_text_node<str::short_>>(&fundamental_type_specifier_node))
					short_type = true;
				else if(get<predefined_text_node<str::int_>>(&fundamental_type_specifier_node))
					int_type = true;
				else if(get<predefined_text_node<str::long_>>(&fundamental_type_specifier_node))
					if(!long_type)
						long_type = true;
					else
						long_long_type = true;
				else if(get<predefined_text_node<str::signed_>>(&fundamental_type_specifier_node))
					signed_type = true;
				else if(get<predefined_text_node<str::unsigned_>>(&fundamental_type_specifier_node))
					unsigned_type = true;
				else if(get<predefined_text_node<str::float_>>(&fundamental_type_specifier_node))
					float_type = true;
				else if(get<predefined_text_node<str::double_>>(&fundamental_type_specifier_node))
					double_type = true;
				else if(get<predefined_text_node<str::void_>>(&fundamental_type_specifier_node))
					void_type = true;
			}
		}
	}

	if(is_fundamental_type)
	{
		assert(!opt_return_type);
		return get_fundamental_type
		(
			bool_type,
			char_type,
			double_type,
			float_type,
			int_type,
			long_long_type,
			long_type,
			short_type,
			signed_type,
			unsigned_type,
			void_type,
			wchar_t_type
		);
	}
	else
	{
		assert(opt_return_type);
		return *opt_return_type;
	}
}



namespace
{
	class fill_type_visitor: public utility::static_visitor<void>
	{
		public:
			fill_type_visitor(const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node):
				decl_specifier_seq_node_(decl_specifier_seq_node)
			{
			}

			//class or union type
			template<class Type>
			void
			operator()
			(
				Type* type,
				typename boost::enable_if_c<type_traits::is_class<Type>::value || type_traits::is_union<Type>::value>::type* = 0
			)
			{
				const class_specifier& class_specifier_node =
					syntax_node_analysis::get_class_specifier(decl_specifier_seq_node_)
				;

				fill_class(*type, class_specifier_node);
			}

			//enum type
			template<class Type>
			void
			operator()
			(
				Type* type,
				typename boost::enable_if<type_traits::is_enum<Type>>::type* = 0
			)
			{
				const enum_specifier& enum_specifier_node =
					syntax_node_analysis::get_enum_specifier(decl_specifier_seq_node_)
				;

				fill_enum(*type, enum_specifier_node);
			}

		private:
			const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node_;
	};
}

void
fill_type
(
	const user_defined_type_ptr_variant& type,
	const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node
)
{
	fill_type_visitor visitor(decl_specifier_seq_node);
	apply_visitor(visitor, type);
}



semantic_entities::type_variant
qualify_type
(
	semantic_entities::type_variant type,
	const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node
)
{
	bool const_qualified = false;
	bool volatile_qualified = false;

	//find qualifiers
	for(auto i = decl_specifier_seq_node.begin(); i != decl_specifier_seq_node.end(); ++i)
	{
		const decl_specifier& decl_specifier_node = *i;

		if(const boost::optional<const type_specifier&> opt_type_specifier_node = get<type_specifier>(&decl_specifier_node))
		{
			const type_specifier& type_specifier_node = *opt_type_specifier_node;

			if(const boost::optional<const cv_qualifier&> opt_cv_qualifier_node = get<cv_qualifier>(&type_specifier_node))
			{
				const cv_qualifier& cv_qualifier_node = *opt_cv_qualifier_node;

				if(get<predefined_text_node<str::const_>>(&cv_qualifier_node))
					const_qualified = true;
				else if(get<predefined_text_node<str::volatile_>>(&cv_qualifier_node))
					volatile_qualified = true;

				//TODO error if two const or two volatile
			}
		}
	}

	//qualify
	if(const_qualified && volatile_qualified)
		type = cv_qualified_type(type, cv_qualified_type::qualification_type::CONST_AND_VOLATILE);
	else if(const_qualified)
		type = cv_qualified_type(type, cv_qualified_type::qualification_type::CONST);
	else if(volatile_qualified)
		type = cv_qualified_type(type, cv_qualified_type::qualification_type::VOLATILE);

	return type;
}

semantic_entities::type_variant
qualify_type
(
	semantic_entities::type_variant type,
	const syntax_nodes::declarator& declarator_node,
	const declarative_region_ptr_variant& current_declarative_region,
	const bool ignore_function_type
)
{
	const direct_declarator& direct_declarator_node = get_direct_declarator(declarator_node);
	const direct_declarator_first_part& first_part_node = get_first_part(direct_declarator_node);

	//pointers
	if(auto opt_ptr_operator_seq_node = get_ptr_operator_seq(declarator_node))
	{
		auto ptr_operator_seq_node = *opt_ptr_operator_seq_node;
		type = qualify_type(type, ptr_operator_seq_node, current_declarative_region);
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

semantic_entities::type_variant
qualify_type
(
	semantic_entities::type_variant type,
	const syntax_nodes::abstract_declarator& abstract_declarator_node,
	const semantic_entities::declarative_region_ptr_variant& current_declarative_region
)
{
	if(const optional_node<ptr_operator_seq>& opt_ptr_operator_seq_node = get_ptr_operator_seq(abstract_declarator_node))
	{
		type = qualify_type(type, *opt_ptr_operator_seq_node, current_declarative_region);
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

semantic_entities::type_variant
qualify_type
(
	semantic_entities::type_variant type,
	const syntax_nodes::direct_declarator_last_part_seq& last_part_seq_node,
	const semantic_entities::declarative_region_ptr_variant& current_declarative_region,
	const bool ignore_function_type
)
{
	for(auto i = last_part_seq_node.begin(); i != last_part_seq_node.end(); ++i)
	{
		const direct_declarator_last_part& last_part_node = *i;
		type = qualify_type(type, last_part_node, current_declarative_region, ignore_function_type);
	}

	return type;
}

semantic_entities::type_variant
qualify_type
(
	semantic_entities::type_variant type,
	const syntax_nodes::direct_declarator_last_part& last_part_node,
	const semantic_entities::declarative_region_ptr_variant& current_declarative_region,
	const bool ignore_function_type
)
{
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
		if(get_conditional_expression(*opt_array_part_node))
		{
			type = array(0, type);
		}
		else
		{
			//int i[] == int i*
			type = pointer(type);
		}
	}

	return type;
}

semantic_entities::type_variant
qualify_type
(
	semantic_entities::type_variant type,
	const syntax_nodes::ptr_operator_seq& ptr_operator_seq_node,
	const semantic_entities::declarative_region_ptr_variant& current_declarative_region
)
{
	for(auto i = ptr_operator_seq_node.begin(); i != ptr_operator_seq_node.end(); ++i)
	{
		auto ptr_operator_node = *i;
		if(auto opt_ptr_ptr_operator_node = get<ptr_ptr_operator>(&ptr_operator_node))
		{
			auto ptr_ptr_operator_node = *opt_ptr_ptr_operator_node;

			if(auto opt_simple_ptr_ptr_operator_node = get<simple_ptr_ptr_operator>(&ptr_ptr_operator_node))
			{
				const simple_ptr_ptr_operator& simple_ptr_ptr_operator_node = *opt_simple_ptr_ptr_operator_node;

				type = pointer(type);

				if(auto opt_cv_qualifier_seq_node = get_cv_qualifier_seq(simple_ptr_ptr_operator_node))
				{
					type = qualify_type(type, *opt_cv_qualifier_seq_node);
				}
			}
			else if(auto opt_ptr_to_member_operator_node = get<ptr_to_member_operator>(&ptr_ptr_operator_node))
			{
				const ptr_to_member_operator& ptr_to_member_operator_node = *opt_ptr_to_member_operator_node;

				//get the class designated by the ptr-to-member-operator (c in "void (c::*f)(int)")
				const class_ptr_variant found_class =
					find_class
					(
						ptr_to_member_operator_node,
						current_declarative_region
					)
				;

				type = pointer_to_member(type, found_class);

				if(auto opt_cv_qualifier_seq_node = get_cv_qualifier_seq(ptr_to_member_operator_node))
				{
					type = qualify_type(type, *opt_cv_qualifier_seq_node);
				}
			}
		}
		else if(auto ref_ptr_operator_node = get<ref_ptr_operator>(&ptr_operator_node))
		{
			type = reference(type);
		}
	}

	return type;
}

semantic_entities::type_variant
qualify_type
(
	semantic_entities::type_variant type,
	const syntax_nodes::cv_qualifier_seq& cv_qualifier_seq_node
)
{
	//find cv-qualifiers
	bool const_qualified = false;
	bool volatile_qualified = false;
	for
	(
		auto i = cv_qualifier_seq_node.begin();
		i != cv_qualifier_seq_node.end();
		++i
	)
	{
		auto cv_qualifier_node = *i;

		if(get<predefined_text_node<str::const_>>(&cv_qualifier_node))
			const_qualified = true;
		else if(get<predefined_text_node<str::volatile_>>(&cv_qualifier_node))
			volatile_qualified = true;
	}

	//apply cv-qualifiers
	if(const_qualified && volatile_qualified)
		type = cv_qualified_type(type, cv_qualified_type::qualification_type::CONST_AND_VOLATILE);
	else if(const_qualified)
		type = cv_qualified_type(type, cv_qualified_type::qualification_type::CONST);
	else if(volatile_qualified)
		type = cv_qualified_type(type, cv_qualified_type::qualification_type::VOLATILE);

	return type;
}

semantic_entities::fundamental_type
get_fundamental_type
(
	const bool bool_type,
	const bool char_type,
	const bool double_type,
	const bool float_type,
	const bool int_type,
	const bool long_long_type,
	const bool long_type,
	const bool short_type,
	const bool signed_type,
	const bool unsigned_type,
	const bool void_type,
	const bool wchar_t_type
)
{
	if
	(
		bool_type &&
		!char_type &&
		!double_type &&
		!float_type &&
		!int_type &&
		!long_long_type &&
		!long_type &&
		!short_type &&
		!signed_type &&
		!unsigned_type &&
		!void_type &&
		!wchar_t_type
	)
	{
		return fundamental_type::BOOL;
	}
	else if
	(
		!bool_type &&
		char_type &&
		!double_type &&
		!float_type &&
		!int_type &&
		!long_long_type &&
		!long_type &&
		!short_type &&
		!signed_type &&
		!unsigned_type &&
		!void_type &&
		!wchar_t_type
	)
	{
		return fundamental_type::CHAR;
	}
	else if
	(
		!bool_type &&
		char_type &&
		!double_type &&
		!float_type &&
		!int_type &&
		!long_long_type &&
		!long_type &&
		!short_type &&
		signed_type &&
		!unsigned_type &&
		!void_type &&
		!wchar_t_type
	)
	{
		return fundamental_type::SIGNED_CHAR;
	}
	else if
	(
		!bool_type &&
		!char_type &&
		double_type &&
		!float_type &&
		!int_type &&
		!long_long_type &&
		!long_type &&
		!short_type &&
		!signed_type &&
		!unsigned_type &&
		!void_type &&
		!wchar_t_type
	)
	{
		return fundamental_type::DOUBLE;
	}
	else if
	(
		!bool_type &&
		!char_type &&
		!double_type &&
		float_type &&
		!int_type &&
		!long_long_type &&
		!long_type &&
		!short_type &&
		!signed_type &&
		!unsigned_type &&
		!void_type &&
		!wchar_t_type
	)
	{
		return fundamental_type::FLOAT;
	}
	else if
	(
		!bool_type &&
		!char_type &&
		!double_type &&
		!float_type &&
		(signed_type || int_type) &&
		!long_long_type &&
		!long_type &&
		!short_type &&
		!unsigned_type &&
		!void_type &&
		!wchar_t_type
	)
	{
		return fundamental_type::INT;
	}
	else if
	(
		!bool_type &&
		!char_type &&
		double_type &&
		!float_type &&
		!int_type &&
		!long_long_type &&
		long_type &&
		!short_type &&
		!signed_type &&
		!unsigned_type &&
		!void_type &&
		!wchar_t_type
	)
	{
		return fundamental_type::LONG_DOUBLE;
	}
	else if
	(
		!bool_type &&
		!char_type &&
		!double_type &&
		!float_type &&
		!long_long_type &&
		long_type &&
		!short_type &&
		!unsigned_type &&
		!void_type &&
		!wchar_t_type
	)
	{
		return fundamental_type::LONG_INT;
	}
	else if
	(
		!bool_type &&
		!char_type &&
		!double_type &&
		!float_type &&
		long_long_type &&
		!short_type &&
		!unsigned_type &&
		!void_type &&
		!wchar_t_type
	)
	{
		return fundamental_type::LONG_LONG_INT;
	}
	else if
	(
		!bool_type &&
		!char_type &&
		!double_type &&
		!float_type &&
		!long_long_type &&
		!long_type &&
		short_type &&
		!unsigned_type &&
		!void_type &&
		!wchar_t_type
	)
	{
		return fundamental_type::SHORT_INT;
	}
	else if
	(
		!bool_type &&
		char_type &&
		!double_type &&
		!float_type &&
		!int_type &&
		!long_long_type &&
		!long_type &&
		!short_type &&
		!signed_type &&
		unsigned_type &&
		!void_type &&
		!wchar_t_type
	)
	{
		return fundamental_type::UNSIGNED_CHAR;
	}
	else if
	(
		!bool_type &&
		!char_type &&
		!double_type &&
		!float_type &&
		!long_long_type &&
		!long_type &&
		!short_type &&
		!signed_type &&
		unsigned_type &&
		!void_type &&
		!wchar_t_type
	)
	{
		return fundamental_type::UNSIGNED_INT;
	}
	else if
	(
		!bool_type &&
		!char_type &&
		!double_type &&
		!float_type &&
		!long_long_type &&
		long_type &&
		!short_type &&
		!signed_type &&
		unsigned_type &&
		!void_type &&
		!wchar_t_type
	)
	{
		return fundamental_type::UNSIGNED_LONG_INT;
	}
	else if
	(
		!bool_type &&
		!char_type &&
		!double_type &&
		!float_type &&
		long_long_type &&
		!short_type &&
		!signed_type &&
		unsigned_type &&
		!void_type &&
		!wchar_t_type
	)
	{
		return fundamental_type::UNSIGNED_LONG_LONG_INT;
	}
	else if
	(
		!bool_type &&
		!char_type &&
		!double_type &&
		!float_type &&
		!long_long_type &&
		!long_type &&
		short_type &&
		!signed_type &&
		unsigned_type &&
		!void_type &&
		!wchar_t_type
	)
	{
		return fundamental_type::UNSIGNED_SHORT_INT;
	}
	else if
	(
		!bool_type &&
		!char_type &&
		!double_type &&
		!float_type &&
		!int_type &&
		!long_long_type &&
		!long_type &&
		!short_type &&
		!signed_type &&
		!unsigned_type &&
		void_type &&
		!wchar_t_type
	)
	{
		return fundamental_type::VOID;
	}
	else if
	(
		!bool_type &&
		!char_type &&
		!double_type &&
		!float_type &&
		!int_type &&
		!long_long_type &&
		!long_type &&
		!short_type &&
		!signed_type &&
		!unsigned_type &&
		!void_type &&
		wchar_t_type
	)
	{
		return fundamental_type::WCHAR_T;
	}

	throw std::runtime_error("Incorrect built-in type");
}

}}}} //namespace scalpel::cpp::semantic_analysis::detail

