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

#include "function_construction.hpp"
#include "class_construction.hpp"
#include "type_construction.hpp"
#include "other_entity_construction.hpp"
#include "syntax_node_analysis/function_definition.hpp"
#include "syntax_node_analysis/declarator.hpp"
#include "syntax_node_analysis/decl_specifier_seq.hpp"

namespace scalpel { namespace cpp { namespace semantic_analysis { namespace detail
{

using namespace syntax_nodes;
using namespace semantic_entities;

function_shared_ptr_variant
create_function
(
	const syntax_nodes::function_definition& function_definition_node,
	const semantic_entities::declarative_region_shared_ptr_variant current_declarative_region,
	const bool is_class_member,
	const bool is_defined_in_class
)
{
	//
	//Analyze the decl-specifier-seq node.
	//

	boost::optional<type_variant> opt_unqualified_type;
	bool has_typedef_specifier = false;
	bool has_static_specifier = false;
	bool has_inline_specifier = false;
	bool has_virtual_specifier = false;
	bool has_explicit_specifier = false;

	if
	(
		const optional_node<decl_specifier_seq>& opt_decl_specifier_seq_node =
			syntax_node_analysis::get_decl_specifier_seq(function_definition_node)
	)
	{
		const decl_specifier_seq& decl_specifier_seq_node = *opt_decl_specifier_seq_node;

		has_typedef_specifier = syntax_node_analysis::has_typedef_specifier(decl_specifier_seq_node);
		has_static_specifier = syntax_node_analysis::has_static_specifier(decl_specifier_seq_node);
		has_inline_specifier = is_defined_in_class || syntax_node_analysis::has_inline_specifier(decl_specifier_seq_node);
		has_virtual_specifier = syntax_node_analysis::has_virtual_specifier(decl_specifier_seq_node);
		has_explicit_specifier = syntax_node_analysis::has_explicit_specifier(decl_specifier_seq_node);

		//create and/or get undecorated type
		switch(syntax_node_analysis::get_decl_specifier_seq_type(decl_specifier_seq_node))
		{
			case syntax_node_analysis::type_specifier_seq_type::CLASS_DECLARATION:
			{
				throw std::runtime_error("error: new types may not be defined in a return type");
				break;
			}
			case syntax_node_analysis::type_specifier_seq_type::CLASS_FORWARD_DECLARATION:
			{
				assert(false); //not managed yet

				//const syntax_nodes::class_elaborated_specifier& class_elaborated_specifier_node =
				//	syntax_node_analysis::get_class_elaborated_specifier(decl_specifier_seq_node)
				//;

				//std::shared_ptr<class_> new_class = create_class(class_elaborated_specifier_node);
				////TODO current_declarative_region->add_member(new_class);

				//opt_unqualified_type = std::shared_ptr<const class_>(new_class);

				break;
			}
			case syntax_node_analysis::type_specifier_seq_type::SIMPLE_TYPE:
			{
				opt_unqualified_type = create_type(decl_specifier_seq_node, current_declarative_region);
				break;
			}
			case syntax_node_analysis::type_specifier_seq_type::NO_TYPE:
			{
				break;
			}
		}

		//qualify type
		if(opt_unqualified_type)
			opt_unqualified_type = qualify_type(*opt_unqualified_type, decl_specifier_seq_node);
	}



	//
	//Analyze the declarator node.
	//

	declarator_entity_shared_ptr_variant declarator_entity = create_entity
	(
		syntax_node_analysis::get_declarator(function_definition_node),
		current_declarative_region,
		opt_unqualified_type,
		has_typedef_specifier,
		has_static_specifier,
		has_inline_specifier,
		has_virtual_specifier,
		has_explicit_specifier,
		false,
		is_class_member
	);

	if(auto opt_constructor_entity = get<constructor>(&declarator_entity))
		return *opt_constructor_entity;
	else if(auto opt_destructor_entity = get<destructor>(&declarator_entity))
		return *opt_destructor_entity;
	else if(auto opt_operator_member_function_entity = get<operator_member_function>(&declarator_entity))
		return *opt_operator_member_function_entity;
	else if(auto opt_conversion_function_entity = get<conversion_function>(&declarator_entity))
		return *opt_conversion_function_entity;
	else if(auto opt_simple_member_function_entity = get<simple_member_function>(&declarator_entity))
		return *opt_simple_member_function_entity;
	else if(auto opt_operator_function_entity = get<operator_function>(&declarator_entity))
		return *opt_operator_function_entity;
	else if(auto opt_simple_function_entity = get<simple_function>(&declarator_entity))
		return *opt_simple_function_entity;
	else
		assert(false);
}

class define_function_visitor: public utility::static_visitor<void>
{
	public:
		template<class T>
		void
		operator()(std::shared_ptr<T> function_entity) const
		{
			//check whether the function is undefined as it have to be
			if(function_entity->defined())
				throw std::runtime_error("error: the function is already defined");

			function_entity->body(std::make_shared<semantic_entities::statement_block>());
		}
};

void
define_function
(
	const function_shared_ptr_variant& function_entity,
	const syntax_nodes::function_definition& /*function_definition_node*/,
	const semantic_entities::declarative_region_shared_ptr_variant /*current_declarative_region*/
)
{
	define_function_visitor visitor;
	utility::apply_visitor(visitor, function_entity);
}

class find_function_visitor: public utility::static_visitor<boost::optional<function_shared_ptr_variant>>
{
	public:
		find_function_visitor
		(
			const semantic_entities::open_declarative_region_shared_ptr_variant& function_declarative_region
		):
			function_declarative_region_(function_declarative_region)
		{
		}

		template<class T>
		boost::optional<function_shared_ptr_variant>
		operator()(std::shared_ptr<T> function_signature) const
		{
			std::shared_ptr<T> found_function =
				find_function<T>
				(
					function_signature,
					function_declarative_region_
				)
			;

			if(found_function)
				return function_shared_ptr_variant(found_function);
			else
				return boost::optional<function_shared_ptr_variant>();
		}

	private:
		const semantic_entities::open_declarative_region_shared_ptr_variant& function_declarative_region_;
};

boost::optional<function_shared_ptr_variant>
find_function
(
	const function_shared_ptr_variant& function_signature,
	const semantic_entities::open_declarative_region_shared_ptr_variant& function_declarative_region
)
{
	find_function_visitor visitor(function_declarative_region);
	return utility::apply_visitor(visitor, function_signature);
}

semantic_entities::overloadable_operator
get_operator_function_operator
(
	const syntax_nodes::declarator& declarator_node
)
{
	const syntax_nodes::operator_& operator_node = syntax_node_analysis::get_operator(declarator_node);
	if(auto opt_simple_operator_node = syntax_nodes::get<syntax_nodes::simple_operator>(&operator_node))
	{
		auto simple_operator_node = *opt_simple_operator_node;

		if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::new_>>(&simple_operator_node))
			return semantic_entities::overloadable_operator::NEW;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::delete_>>(&simple_operator_node))
			return semantic_entities::overloadable_operator::DELETE;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::double_right_angle_bracket_equal>>(&simple_operator_node))
			return semantic_entities::overloadable_operator::DOUBLE_RIGHT_ANGLE_BRACKET_EQUAL;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::double_left_angle_bracket_equal>>(&simple_operator_node))
			return semantic_entities::overloadable_operator::DOUBLE_LEFT_ANGLE_BRACKET_EQUAL;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::arrow_asterisk>>(&simple_operator_node))
			return semantic_entities::overloadable_operator::ARROW_ASTERISK;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::plus_equal>>(&simple_operator_node))
			return semantic_entities::overloadable_operator::PLUS_EQUAL;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::minus_equal>>(&simple_operator_node))
			return semantic_entities::overloadable_operator::MINUS_EQUAL;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::asterisk_equal>>(&simple_operator_node))
			return semantic_entities::overloadable_operator::ASTERISK_EQUAL;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::slash_equal>>(&simple_operator_node))
			return semantic_entities::overloadable_operator::SLASH_EQUAL;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::percent_equal>>(&simple_operator_node))
			return semantic_entities::overloadable_operator::PERCENT_EQUAL;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::circumflex_equal>>(&simple_operator_node))
			return semantic_entities::overloadable_operator::CIRCUMFLEX_EQUAL;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::ampersand_equal>>(&simple_operator_node))
			return semantic_entities::overloadable_operator::AMPERSAND_EQUAL;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::pipe_equal>>(&simple_operator_node))
			return semantic_entities::overloadable_operator::PIPE_EQUAL;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::double_left_angle_bracket>>(&simple_operator_node))
			return semantic_entities::overloadable_operator::DOUBLE_LEFT_ANGLE_BRACKET;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::double_right_angle_bracket>>(&simple_operator_node))
			return semantic_entities::overloadable_operator::DOUBLE_RIGHT_ANGLE_BRACKET;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::double_equal>>(&simple_operator_node))
			return semantic_entities::overloadable_operator::DOUBLE_EQUAL;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::exclamation_equal>>(&simple_operator_node))
			return semantic_entities::overloadable_operator::EXCLAMATION_EQUAL;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::left_angle_bracket_equal>>(&simple_operator_node))
			return semantic_entities::overloadable_operator::LEFT_ANGLE_BRACKET_EQUAL;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::right_angle_bracket_equal>>(&simple_operator_node))
			return semantic_entities::overloadable_operator::RIGHT_ANGLE_BRACKET_EQUAL;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::double_ampersand>>(&simple_operator_node))
			return semantic_entities::overloadable_operator::DOUBLE_AMPERSAND;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::double_pipe>>(&simple_operator_node))
			return semantic_entities::overloadable_operator::DOUBLE_PIPE;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::double_plus>>(&simple_operator_node))
			return semantic_entities::overloadable_operator::DOUBLE_PLUS;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::double_minus>>(&simple_operator_node))
			return semantic_entities::overloadable_operator::DOUBLE_MINUS;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::arrow>>(&simple_operator_node))
			return semantic_entities::overloadable_operator::ARROW;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::round_brackets>>(&simple_operator_node))
			return semantic_entities::overloadable_operator::ROUND_BRACKETS;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::square_brackets>>(&simple_operator_node))
			return semantic_entities::overloadable_operator::SQUARE_BRACKETS;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::comma>>(&simple_operator_node))
			return semantic_entities::overloadable_operator::COMMA;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::plus>>(&simple_operator_node))
			return semantic_entities::overloadable_operator::PLUS;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::minus>>(&simple_operator_node))
			return semantic_entities::overloadable_operator::MINUS;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::asterisk>>(&simple_operator_node))
			return semantic_entities::overloadable_operator::ASTERISK;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::slash>>(&simple_operator_node))
			return semantic_entities::overloadable_operator::SLASH;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::percent>>(&simple_operator_node))
			return semantic_entities::overloadable_operator::PERCENT;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::circumflex>>(&simple_operator_node))
			return semantic_entities::overloadable_operator::CIRCUMFLEX;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::ampersand>>(&simple_operator_node))
			return semantic_entities::overloadable_operator::AMPERSAND;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::pipe>>(&simple_operator_node))
			return semantic_entities::overloadable_operator::PIPE;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::tilde>>(&simple_operator_node))
			return semantic_entities::overloadable_operator::TILDE;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::exclamation>>(&simple_operator_node))
			return semantic_entities::overloadable_operator::EXCLAMATION;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::equal>>(&simple_operator_node))
			return semantic_entities::overloadable_operator::EQUAL;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::left_angle_bracket>>(&simple_operator_node))
			return semantic_entities::overloadable_operator::LEFT_ANGLE_BRACKET;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::right_angle_bracket>>(&simple_operator_node))
			return semantic_entities::overloadable_operator::RIGHT_ANGLE_BRACKET;
		else
			assert(false);
	}
	else if(auto opt_array_operator_node = syntax_nodes::get<syntax_nodes::array_operator>(&operator_node))
	{
		auto array_operator_node = *opt_array_operator_node;

		if(syntax_nodes::get<syntax_nodes::new_array_operator>(&array_operator_node))
			return semantic_entities::overloadable_operator::NEW_ARRAY;
		else if(syntax_nodes::get<syntax_nodes::delete_array_operator>(&array_operator_node))
			return semantic_entities::overloadable_operator::DELETE_ARRAY;
		else
			assert(false);
	}
	else
	{
		assert(false);
	}
}

semantic_entities::type_variant
get_conversion_function_type
(
	const syntax_nodes::declarator& declarator_node,
	const declarative_region_shared_ptr_variant current_declarative_region
)
{
	const unqualified_id& unqualified_id_node = syntax_node_analysis::get_unqualified_id(declarator_node);
	boost::optional<const conversion_function_id&> opt_conversion_function_id_node = syntax_nodes::get<conversion_function_id>(&unqualified_id_node);
	assert(opt_conversion_function_id_node);
	const conversion_function_id& conversion_function_id_node = *opt_conversion_function_id_node;

	const type_specifier_seq& type_specifier_seq_node = get_type_specifier_seq(conversion_function_id_node);
	type_variant type = create_type(type_specifier_seq_node, current_declarative_region);

	if(const optional_node<ptr_operator_seq>& opt_ptr_operator_seq_node = get_ptr_operator_seq(conversion_function_id_node))
	{
		const ptr_operator_seq& ptr_operator_seq_node = *opt_ptr_operator_seq_node;
		type = qualify_type(type, ptr_operator_seq_node);
	}

	return type;
}

semantic_entities::function_parameter_list
create_parameters
(
	boost::optional<const syntax_nodes::parameter_declaration_list&> opt_parameter_declaration_list_node,
	const declarative_region_shared_ptr_variant current_declarative_region
)
{
	if(opt_parameter_declaration_list_node)
		return create_parameters(*opt_parameter_declaration_list_node, current_declarative_region);
	else
		return semantic_entities::function_parameter_list();
}

semantic_entities::function_parameter_list
create_parameters
(
	const syntax_nodes::parameter_declaration_list& parameter_declaration_list_node,
	const declarative_region_shared_ptr_variant current_declarative_region
)
{
	function_parameter_list parameters;

	for
	(
		auto j = parameter_declaration_list_node.begin();
		j != parameter_declaration_list_node.end();
		++j
	)
	{
		auto parameter_declaration_node = j->main_node();
		auto decl_specifier_seq_node = get_decl_specifier_seq(parameter_declaration_node);

		semantic_entities::type_variant type =
			qualify_type
			(
				create_type
				(
					decl_specifier_seq_node,
					current_declarative_region
				),
				decl_specifier_seq_node
			)
		;

		if(auto opt_declarator_node = get_declarator(parameter_declaration_node))
		{
			auto declarator_node = *opt_declarator_node;

			parameters.push_back
			(
				std::make_shared<function_parameter>
				(
					qualify_type(type, declarator_node),
					syntax_node_analysis::get_identifier(declarator_node).value()
				)
			);
		}
		else if(auto opt_abstract_declarator_node = get_abstract_declarator(parameter_declaration_node))
		{
			auto abstract_declarator_node = *opt_abstract_declarator_node;

			if(boost::optional<const ptr_operator_seq&> opt_ptr_operator_seq_node = get<ptr_operator_seq>(&abstract_declarator_node))
			{
				type = qualify_type(type, *opt_ptr_operator_seq_node);
			}
			else if(boost::optional<const direct_abstract_declarator&> opt_direct_abstract_declarator_node = get<direct_abstract_declarator>(&abstract_declarator_node))
			{
				assert(false); //not managed yet
			}

			parameters.push_back
			(
				std::make_shared<function_parameter>
				(
					type,
					""
				)
			);
		}
		else
		{
			//void f(void) == void f()
			bool empty_parameter_list = false;
			if(const fundamental_type* const opt_fundamental_type = get<fundamental_type>(&type))
			{
				empty_parameter_list =
					*opt_fundamental_type == fundamental_type::VOID &&
					parameter_declaration_list_node.size() == 1
				;
			}

			if(!empty_parameter_list)
			{
				parameters.push_back
				(
					std::make_shared<function_parameter>
					(
						type,
						""
					)
				);
			}
		}
	}

	return parameters;
}

std::vector<semantic_entities::type_variant>
create_parameter_types
(
	boost::optional<const syntax_nodes::parameter_declaration_list&> opt_parameter_declaration_list_node,
	const declarative_region_shared_ptr_variant current_declarative_region
)
{
	if(opt_parameter_declaration_list_node)
		return create_parameter_types(*opt_parameter_declaration_list_node, current_declarative_region);
	else
		return std::vector<semantic_entities::type_variant>();
}

std::vector<semantic_entities::type_variant>
create_parameter_types
(
	const syntax_nodes::parameter_declaration_list& parameter_declaration_list_node,
	const semantic_entities::declarative_region_shared_ptr_variant current_declarative_region
)
{
	semantic_entities::function_parameter_list parameters =
		create_parameters(parameter_declaration_list_node, current_declarative_region)
	;

	std::vector<semantic_entities::type_variant> parameter_types;
	for(auto i = parameters.begin(); i != parameters.end(); ++i)
	{
		const function_parameter& p = **i;
		parameter_types.push_back(p.type());
	}

	return parameter_types;
}

}}}} //namespace scalpel::cpp::semantic_analysis::detail

