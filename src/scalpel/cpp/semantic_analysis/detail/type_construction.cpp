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

namespace scalpel { namespace cpp { namespace semantic_analysis { namespace detail
{

using namespace syntax_nodes;
using namespace semantic_entities;

semantic_entities::type_variant
create_type
(
	const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node,
	const declarative_region_shared_ptr_variant current_declarative_region
)
{
	return create_type(syntax_node_analysis::to_type_specifier_seq(decl_specifier_seq_node), current_declarative_region);
}

semantic_entities::type_variant
create_type
(
	const syntax_nodes::type_specifier_seq& type_specifier_seq_node,
	const semantic_entities::declarative_region_shared_ptr_variant current_declarative_region
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
		const syntax_nodes::type_specifier& type_specifier_node = i->main_node();

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

				utility::shared_ptr_variant<class_, typedef_>::type found_type =
					name_lookup::find
					<
						semantic_entity_analysis::identification_policies::by_name,
						false,
						false,
						class_,
						typedef_
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
		const decl_specifier& decl_specifier_node = i->main_node();

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
	const declarative_region_shared_ptr_variant& current_declarative_region,
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

		for(auto i = last_part_seq_node.begin(); i != last_part_seq_node.end(); ++i)
		{
			const direct_declarator_last_part& last_part_node = i->main_node();

			if(!ignore_function_type)
			{
				if(const boost::optional<const direct_declarator_function_part&> opt_function_part_node = get<direct_declarator_function_part>(&last_part_node))
				{
					type =
						function_type
						(
							0,
							type, //return type
							create_parameter_types(syntax_node_analysis::get_parameter_declaration_list(declarator_node), current_declarative_region),
							syntax_node_analysis::has_ellipsis(declarator_node),
							syntax_node_analysis::has_const_function_qualifier(declarator_node),
							syntax_node_analysis::has_volatile_function_qualifier(declarator_node)
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
		}
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
	const syntax_nodes::ptr_operator_seq& ptr_operator_seq_node,
	const semantic_entities::declarative_region_shared_ptr_variant& current_declarative_region
)
{
	for(auto i = ptr_operator_seq_node.begin(); i != ptr_operator_seq_node.end(); ++i)
	{
		auto ptr_operator_node = i->main_node();
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
			else if(auto opt_member_function_ptr_operator_node = get<member_function_ptr_operator>(&ptr_ptr_operator_node))
			{
				const member_function_ptr_operator& member_function_ptr_operator_node = *opt_member_function_ptr_operator_node;

				//get the class designated by the member-function-ptr-operator (c in "void (c::*f)(int)")
				std::shared_ptr<class_> parent_class =
					find_class
					(
						member_function_ptr_operator_node,
						current_declarative_region
					)
				;

				utility::get<function_type>(type).parent_class(parent_class.get());
				type = pointer(type);

				if(auto opt_cv_qualifier_seq_node = get_cv_qualifier_seq(member_function_ptr_operator_node))
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
		auto cv_qualifier_node = i->main_node();

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

