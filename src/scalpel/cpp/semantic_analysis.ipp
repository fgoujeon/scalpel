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

#ifndef SCALPEL_CPP_SEMANTIC_ANALYSIS_IPP
#define SCALPEL_CPP_SEMANTIC_ANALYSIS_IPP

#include "detail/semantic_analysis/basic_functions.hpp"
#include "detail/semantic_analysis/name_lookup.hpp"
#include <scalpel/utility/variant.hpp>
#include <sstream>

namespace scalpel { namespace cpp
{

namespace semantic_analysis
{

template<class DeclarativeRegionT>
void
analyze
(
	const syntax_nodes::function_definition& function_definition_node,
	std::shared_ptr<DeclarativeRegionT> current_declarative_region
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;
	namespace detail = detail::semantic_analysis;

	const boost::optional<const simple_function_definition&> opt_simple_function_definition =
		get<simple_function_definition>(&function_definition_node)
	;
	const boost::optional<const try_block_function_definition&> opt_try_block_function_definition =
		get<try_block_function_definition>(&function_definition_node)
	;
	assert(opt_simple_function_definition || opt_try_block_function_definition);

	const optional_node<decl_specifier_seq>& opt_decl_specifier_seq_node =
		opt_simple_function_definition ?
		get_decl_specifier_seq(*opt_simple_function_definition) :
		get_decl_specifier_seq(*opt_try_block_function_definition)
	;
	const declarator& declarator_node =
		opt_simple_function_definition ?
		get_declarator(*opt_simple_function_definition) :
		get_declarator(*opt_try_block_function_definition)
	;

	//If the function definition has a nested-name-specifier
	//(like in "void n::f(){/*...*/}"), the function must be already declared.
	//Check whether it's the case.
	bool declaration_must_exist = false;
	boost::optional<nested_identifier_or_template_id> opt_nested_identifier_or_template_id_node;
	{
		auto direct_declarator_node = get_direct_declarator(declarator_node);
		auto first_part_node = get_first_part(direct_declarator_node);
		auto opt_declarator_id_node = get<declarator_id>(&first_part_node);
		if(opt_declarator_id_node)
		{
			auto declarator_id_node = *opt_declarator_id_node;
			if(opt_nested_identifier_or_template_id_node = get<nested_identifier_or_template_id>(&declarator_id_node))
			{
				auto nested_identifier_or_template_id_node = *opt_nested_identifier_or_template_id_node;
				if(get_nested_name_specifier(nested_identifier_or_template_id_node))
				{
					declaration_must_exist = true;
				}
			}
		}
	}



	//
	//Analyze the decl-specifier-seq node.
	//

	boost::optional<type_shared_ptr_variant> opt_decl_specifier_seq_type;
	bool has_typedef_specifier = false;
	bool has_static_specifier = false;
	bool has_inline_specifier = false;
	bool has_explicit_specifier = false;

	if(opt_decl_specifier_seq_node)
	{
		const decl_specifier_seq& decl_specifier_seq_node = *opt_decl_specifier_seq_node;

		has_typedef_specifier = detail::has_typedef_specifier(decl_specifier_seq_node);
		has_static_specifier = detail::has_static_specifier(decl_specifier_seq_node);
		has_inline_specifier = detail::has_inline_specifier(decl_specifier_seq_node);
		has_explicit_specifier = detail::has_explicit_specifier(decl_specifier_seq_node);

		opt_decl_specifier_seq_type = process_decl_specifier_seq(decl_specifier_seq_node, current_declarative_region);
	}



	//
	//Analyze and process the declarator node.
	//

	declarator_entity_shared_ptr_variant declarator_entity = create_entity
	(
		declarator_node,
		current_declarative_region,
		opt_decl_specifier_seq_type,
		has_typedef_specifier,
		has_static_specifier,
		has_inline_specifier,
		has_explicit_specifier
	);

	if(auto opt_constructor_entity = get<std::shared_ptr<class_::constructor>>(&declarator_entity))
	{
	}
	else if(auto opt_destructor_entity = get<std::shared_ptr<class_::destructor>>(&declarator_entity))
	{
	}
	else if(auto opt_operator_function_entity = get<std::shared_ptr<operator_function>>(&declarator_entity))
	{
	}
	else if(auto opt_conversion_function_entity = get<std::shared_ptr<class_::conversion_function>>(&declarator_entity))
	{
	}
	else if(auto opt_simple_function_entity = get<std::shared_ptr<simple_function>>(&declarator_entity))
	{
		std::shared_ptr<simple_function> new_function = *opt_simple_function_entity;

		//this function pointer will point to either new_function or
		//(if any) to the already existing (undefined) function
		std::shared_ptr<simple_function> function_to_be_defined;


		//find the functions of the same name
		std::set<std::shared_ptr<simple_function>> found_functions;
		if(opt_nested_identifier_or_template_id_node)
		{
			found_functions =
				detail::name_lookup::find<simple_function, true, true>
				(
					*opt_nested_identifier_or_template_id_node,
					current_declarative_region
				)
			;
		}
		else
		{
			found_functions =
				detail::name_lookup::find<simple_function, true, true>
				(
					identifier(new_function->name()),
					current_declarative_region
				)
			;
		}

		//filter the found functions with signature
		for
		(
			auto i = found_functions.begin();
			i != found_functions.end();
			++i
		)
		{
			std::shared_ptr<simple_function> found_function = *i;
			if(found_function->has_same_signature(*new_function))
			{
				function_to_be_defined = found_function;
				break;
			}
		}

		//
		if(declaration_must_exist && !function_to_be_defined)
		{
			std::ostringstream oss;
			oss << new_function->name() << " is not declared";
			throw std::runtime_error(oss.str().c_str());
		}

		if(!function_to_be_defined)
		{
			//declare the function and add it to the current declarative region
			function_to_be_defined = new_function;
			current_declarative_region->add_member(new_function);
		}

		//check whether the function is undefined as expected
		if(function_to_be_defined->defined())
		{
			std::ostringstream oss;
			oss << "Redefinition of " << function_to_be_defined->name();
			throw std::runtime_error(oss.str().c_str());
		}

		//TODO define the function
		function_to_be_defined->body(std::make_shared<semantic_entities::statement_block>());
	}
	else
		assert(false);
}

template<class DeclarativeRegionT>
boost::optional<semantic_entities::type_shared_ptr_variant>
process_decl_specifier_seq
(
	const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node,
	std::shared_ptr<DeclarativeRegionT> current_declarative_region
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;
	namespace detail = detail::semantic_analysis;

	boost::optional<type_shared_ptr_variant> opt_undecorated_type;

	//create and/or get undecorated type
	switch(detail::get_decl_specifier_seq_type(decl_specifier_seq_node))
	{
		case detail::decl_specifier_seq_type::CLASS_DECL_SPECIFIER_SEQ:
		{
			const syntax_nodes::class_specifier& class_specifier_node = detail::get_class_specifier(decl_specifier_seq_node);

			std::shared_ptr<class_> new_class = create_class(class_specifier_node);
			current_declarative_region->add_member(new_class);
			fill_class(new_class, class_specifier_node);

			opt_undecorated_type = std::shared_ptr<const class_>(new_class);

			break;
		}
		case detail::decl_specifier_seq_type::CLASS_FORWARD_DECL_SPECIFIER_SEQ:
		{
			const syntax_nodes::class_elaborated_specifier& class_elaborated_specifier_node = detail::get_class_elaborated_specifier(decl_specifier_seq_node);

			std::shared_ptr<class_> new_class = create_class(class_elaborated_specifier_node);
			current_declarative_region->add_member(new_class);

			opt_undecorated_type = std::shared_ptr<const class_>(new_class);

			break;
		}
		case detail::decl_specifier_seq_type::SIMPLE_DECL_SPECIFIER_SEQ:
		{
			opt_undecorated_type = create_undecorated_type(decl_specifier_seq_node, current_declarative_region);
			break;
		}
		case detail::decl_specifier_seq_type::CONSTRUCTOR_DECL_SPECIFIER_SEQ:
		{
			break;
		}
	}

	//decorate type
	if(opt_undecorated_type)
		return decorate_type(*opt_undecorated_type, decl_specifier_seq_node);
	else
		return opt_undecorated_type;
}

template<class DeclarativeRegionT>
declarator_entity_shared_ptr_variant
create_entity
(
	const syntax_nodes::declarator& declarator_node,
	std::shared_ptr<DeclarativeRegionT> current_declarative_region,
	const boost::optional<semantic_entities::type_shared_ptr_variant> opt_decl_specifier_seq_type,
	const bool has_typedef_specifier,
	const bool has_static_specifier,
	const bool has_inline_specifier,
	const bool has_explicit_specifier
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;
	namespace detail = detail::semantic_analysis;

	//decorate type with hypothetical pointers and references
	boost::optional<type_shared_ptr_variant> opt_type = opt_decl_specifier_seq_type;
	if(const syntax_nodes::optional_node<syntax_nodes::ptr_operator_seq>& opt_ptr_operator_seq_node = get_ptr_operator_seq(declarator_node))
	{
		//if there's no type to decorate, there's an error
		if(!opt_decl_specifier_seq_type)
			throw std::runtime_error("create_entity error 1");

		opt_type = decorate_type(*opt_decl_specifier_seq_type, *opt_ptr_operator_seq_node);
	}

	switch(detail::get_declarator_type(declarator_node))
	{
		case detail::declarator_type::SIMPLE_FUNCTION_DECLARATOR:
		{
			if(opt_type)
				return semantic_entities::simple_function::make_shared
				(
					detail::get_identifier(declarator_node).value(),
					*opt_type,
					create_parameters(detail::get_parameter_declaration_list(declarator_node), current_declarative_region),
					has_inline_specifier,
					has_static_specifier
				);
			else
				return std::make_shared<semantic_entities::class_::constructor>
				(
					create_parameters(detail::get_parameter_declaration_list(declarator_node), current_declarative_region),
					has_inline_specifier,
					has_explicit_specifier
				);
		}
		case detail::declarator_type::DESTRUCTOR_DECLARATOR:
		{
			if(opt_type)
				throw std::runtime_error("create_entity error 2");

			return std::make_shared<semantic_entities::class_::destructor>
			(
				has_inline_specifier
			);
		}
		case detail::declarator_type::OPERATOR_FUNCTION_DECLARATOR:
		{
			if(!opt_type)
				throw std::runtime_error("create_entity error 3");

			return create_operator_function
			(
				declarator_node,
				*opt_type,
				has_inline_specifier,
				current_declarative_region
			);
		}
		case detail::declarator_type::CONVERSION_FUNCTION_DECLARATOR:
		{
			if(opt_type)
				throw std::runtime_error("create_entity error 3b");

			return std::make_shared<semantic_entities::class_::conversion_function>
			(
				get_conversion_function_type(declarator_node, current_declarative_region),
				has_inline_specifier
			);
		}
		case detail::declarator_type::VARIABLE_DECLARATOR:
		{
			if(!opt_type)
				throw std::runtime_error("create_entity error 4");

			if(has_typedef_specifier)
			{
				return std::make_shared<semantic_entities::typedef_>
				(
					detail::get_identifier(declarator_node).value(),
					*opt_type
				);
			}
			else
			{
				return std::make_shared<semantic_entities::variable>
				(
					detail::get_identifier(declarator_node).value(),
					*opt_type,
					has_static_specifier
				);
			}
		}
	}

	throw std::runtime_error("create_entity error 5");
}



template<class DeclarativeRegionT>
std::shared_ptr<semantic_entities::operator_function>
create_operator_function
(
	const syntax_nodes::declarator& declarator_node,
	const semantic_entities::type_shared_ptr_variant type,
	const bool is_inline,
	std::shared_ptr<DeclarativeRegionT> current_declarative_region
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;
	namespace detail = detail::semantic_analysis;

	//
	//get the overloaded operator
	//
	semantic_entities::operator_ op = semantic_entities::operator_::AMPERSAND;

	auto direct_declarator_node = get_direct_declarator(declarator_node);
	auto direct_declarator_node_first_part_node = get_first_part(direct_declarator_node);
	auto opt_declarator_id_node = syntax_nodes::get<syntax_nodes::declarator_id>(&direct_declarator_node_first_part_node);
	assert(opt_declarator_id_node);
	auto declarator_id_node = *opt_declarator_id_node;
	auto opt_id_expression_node = syntax_nodes::get<syntax_nodes::id_expression>(&declarator_id_node);
	assert(opt_id_expression_node);
	auto id_expression_node = *opt_id_expression_node;
	auto opt_unqualified_id_node = syntax_nodes::get<syntax_nodes::unqualified_id>(&id_expression_node);
	assert(opt_unqualified_id_node);
	auto unqualified_id_node = *opt_unqualified_id_node;
	auto opt_operator_function_id_node = syntax_nodes::get<syntax_nodes::operator_function_id>(&unqualified_id_node);
	assert(opt_operator_function_id_node);
	auto operator_function_id_node = *opt_operator_function_id_node;
	auto operator_node = get_operator(operator_function_id_node);

	if(auto opt_simple_operator_node = syntax_nodes::get<syntax_nodes::simple_operator>(&operator_node))
	{
		auto simple_operator_node = *opt_simple_operator_node;

		if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::new_>>(&simple_operator_node))
			op = semantic_entities::operator_::NEW;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::delete_>>(&simple_operator_node))
			op = semantic_entities::operator_::DELETE;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::double_right_angle_bracket_equal>>(&simple_operator_node))
			op = semantic_entities::operator_::DOUBLE_RIGHT_ANGLE_BRACKET_EQUAL;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::double_left_angle_bracket_equal>>(&simple_operator_node))
			op = semantic_entities::operator_::DOUBLE_LEFT_ANGLE_BRACKET_EQUAL;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::arrow_asterisk>>(&simple_operator_node))
			op = semantic_entities::operator_::ARROW_ASTERISK;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::plus_equal>>(&simple_operator_node))
			op = semantic_entities::operator_::PLUS_EQUAL;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::minus_equal>>(&simple_operator_node))
			op = semantic_entities::operator_::MINUS_EQUAL;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::asterisk_equal>>(&simple_operator_node))
			op = semantic_entities::operator_::ASTERISK_EQUAL;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::slash_equal>>(&simple_operator_node))
			op = semantic_entities::operator_::SLASH_EQUAL;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::percent_equal>>(&simple_operator_node))
			op = semantic_entities::operator_::PERCENT_EQUAL;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::circumflex_equal>>(&simple_operator_node))
			op = semantic_entities::operator_::CIRCUMFLEX_EQUAL;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::ampersand_equal>>(&simple_operator_node))
			op = semantic_entities::operator_::AMPERSAND_EQUAL;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::pipe_equal>>(&simple_operator_node))
			op = semantic_entities::operator_::PIPE_EQUAL;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::double_left_angle_bracket>>(&simple_operator_node))
			op = semantic_entities::operator_::DOUBLE_LEFT_ANGLE_BRACKET;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::double_right_angle_bracket>>(&simple_operator_node))
			op = semantic_entities::operator_::DOUBLE_RIGHT_ANGLE_BRACKET;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::double_equal>>(&simple_operator_node))
			op = semantic_entities::operator_::DOUBLE_EQUAL;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::exclamation_equal>>(&simple_operator_node))
			op = semantic_entities::operator_::EXCLAMATION_EQUAL;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::left_angle_bracket_equal>>(&simple_operator_node))
			op = semantic_entities::operator_::LEFT_ANGLE_BRACKET_EQUAL;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::right_angle_bracket_equal>>(&simple_operator_node))
			op = semantic_entities::operator_::RIGHT_ANGLE_BRACKET_EQUAL;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::double_ampersand>>(&simple_operator_node))
			op = semantic_entities::operator_::DOUBLE_AMPERSAND;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::double_pipe>>(&simple_operator_node))
			op = semantic_entities::operator_::DOUBLE_PIPE;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::double_plus>>(&simple_operator_node))
			op = semantic_entities::operator_::DOUBLE_PLUS;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::double_minus>>(&simple_operator_node))
			op = semantic_entities::operator_::DOUBLE_MINUS;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::arrow>>(&simple_operator_node))
			op = semantic_entities::operator_::ARROW;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::round_brackets>>(&simple_operator_node))
			op = semantic_entities::operator_::ROUND_BRACKETS;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::square_brackets>>(&simple_operator_node))
			op = semantic_entities::operator_::SQUARE_BRACKETS;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::comma>>(&simple_operator_node))
			op = semantic_entities::operator_::COMMA;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::plus>>(&simple_operator_node))
			op = semantic_entities::operator_::PLUS;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::minus>>(&simple_operator_node))
			op = semantic_entities::operator_::MINUS;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::asterisk>>(&simple_operator_node))
			op = semantic_entities::operator_::ASTERISK;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::slash>>(&simple_operator_node))
			op = semantic_entities::operator_::SLASH;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::percent>>(&simple_operator_node))
			op = semantic_entities::operator_::PERCENT;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::circumflex>>(&simple_operator_node))
			op = semantic_entities::operator_::CIRCUMFLEX;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::ampersand>>(&simple_operator_node))
			op = semantic_entities::operator_::AMPERSAND;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::pipe>>(&simple_operator_node))
			op = semantic_entities::operator_::PIPE;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::tilde>>(&simple_operator_node))
			op = semantic_entities::operator_::TILDE;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::exclamation>>(&simple_operator_node))
			op = semantic_entities::operator_::EXCLAMATION;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::equal>>(&simple_operator_node))
			op = semantic_entities::operator_::EQUAL;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::left_angle_bracket>>(&simple_operator_node))
			op = semantic_entities::operator_::LEFT_ANGLE_BRACKET;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::right_angle_bracket>>(&simple_operator_node))
			op = semantic_entities::operator_::RIGHT_ANGLE_BRACKET;
		else
			assert(false);
	}
	else if(auto opt_array_operator_node = syntax_nodes::get<syntax_nodes::array_operator>(&operator_node))
	{
		auto array_operator_node = *opt_array_operator_node;

		if(syntax_nodes::get<syntax_nodes::new_array_operator>(&array_operator_node))
			op = semantic_entities::operator_::NEW_ARRAY;
		else if(syntax_nodes::get<syntax_nodes::delete_array_operator>(&array_operator_node))
			op = semantic_entities::operator_::DELETE_ARRAY;
		else
			assert(false);
	}
	else
	{
		assert(false);
	}

	return std::make_shared<semantic_entities::operator_function>
	(
		op,
		type,
		create_parameters(detail::get_parameter_declaration_list(declarator_node), current_declarative_region),
		is_inline
	);
}

template<class DeclarativeRegionT>
semantic_entities::simple_function::parameters_t
create_parameters
(
	const syntax_nodes::parameter_declaration_list& parameter_declaration_list_node,
	std::shared_ptr<DeclarativeRegionT> current_declarative_region
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;
	namespace detail = detail::semantic_analysis;

	std::list<simple_function::parameter> parameters;

	for
	(
		auto j = parameter_declaration_list_node.begin();
		j != parameter_declaration_list_node.end();
		++j
	)
	{
		auto parameter_declaration_node = j->main_node();
		auto decl_specifier_seq_node = get_decl_specifier_seq(parameter_declaration_node);

		semantic_entities::type_shared_ptr_variant type =
			decorate_type
			(
				create_undecorated_type
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

			if(const optional_node<ptr_operator_seq>& opt_ptr_operator_seq_node = get_ptr_operator_seq(declarator_node))
			{
				type = decorate_type(type, *opt_ptr_operator_seq_node);
			}

			parameters.push_back
			(
				std::move
				(
					simple_function::parameter
					(
						type,
						detail::get_identifier(declarator_node).value()
					)
				)
			);
		}
		else if(auto opt_abstract_declarator_node = get_abstract_declarator(parameter_declaration_node))
		{
			auto abstract_declarator_node = *opt_abstract_declarator_node;

			if(boost::optional<const ptr_operator_seq&> opt_ptr_operator_seq_node = get<ptr_operator_seq>(&abstract_declarator_node))
			{
				type = decorate_type(type, *opt_ptr_operator_seq_node);
			}
			else if(boost::optional<const direct_abstract_declarator&> opt_direct_abstract_declarator_node = get<direct_abstract_declarator>(&abstract_declarator_node))
			{
				assert(false); //not managed yet
			}

			parameters.push_back
			(
				std::move
				(
					simple_function::parameter
					(
						type,
						""
					)
				)
			);
		}
		else
		{
			parameters.push_back
			(
				std::move
				(
					simple_function::parameter
					(
						type,
						""
					)
				)
			);
		}
	}

	return parameters;
}

/*
	//decorate type with hypothetical arrays
	auto direct_declarator_node = get_direct_declarator(declarator_node);
	if(auto opt_last_part_seq_node = get_last_part_seq(direct_declarator_node))
	{
		auto last_part_seq_node = *opt_last_part_seq_node;
		for
		(
			auto i = last_part_seq_node.begin();
			i != last_part_seq_node.end();
			++i
		)
		{
			auto last_part_node = i->main_node();
			if(auto array_part = syntax_nodes::get<syntax_nodes::direct_declarator_array_part>(&last_part_node))
			{
				return_type = std::make_shared<const semantic_entities::array>(0, return_type);
			}
		}
	}
*/

template<class DeclarativeRegionT>
semantic_entities::type_shared_ptr_variant
create_undecorated_type
(
	const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node,
	std::shared_ptr<DeclarativeRegionT> current_declarative_region
)
{
	boost::optional<semantic_entities::type_shared_ptr_variant> opt_return_type;
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

	bool ignored;
	/*
	bool is_const = false;
	bool is_volatile = false;
	*/

	for
	(
		auto i = decl_specifier_seq_node.begin();
		i < decl_specifier_seq_node.end();
		++i
	)
	{
		const syntax_nodes::decl_specifier& decl_specifier_node = i->main_node();

		//auto opt_function_specifier_node = syntax_nodes::get<function_specifier>(&decl_specifier_node);
		//auto opt_storage_class_specifier_node = syntax_nodes::get<storage_class_specifier>(&decl_specifier_node);
		//syntax_nodes::predefined_text_node<str::friend_>
		//syntax_nodes::predefined_text_node<str::typedef_>

		if(auto opt_type_specifier_node = syntax_nodes::get<syntax_nodes::type_specifier>(&decl_specifier_node))
		{
			auto type_specifier_node = *opt_type_specifier_node;
			get_type_info
			(
				type_specifier_node,
				opt_return_type,
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
				wchar_t_type,
				ignored,
				ignored,
				current_declarative_region
			);
		}
	}

	if(!opt_return_type)
	{
		opt_return_type = get_fundamental_type
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

	assert(opt_return_type);
	semantic_entities::type_shared_ptr_variant return_type = *opt_return_type;

	return return_type;
}

template<class DeclarativeRegionT>
semantic_entities::type_shared_ptr_variant
get_conversion_function_type
(
	const syntax_nodes::declarator& declarator_node,
	std::shared_ptr<DeclarativeRegionT> current_declarative_region
)
{
	boost::optional<semantic_entities::type_shared_ptr_variant> opt_return_type;
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
	bool is_const = false;
	bool is_volatile = false;

	auto direct_declarator_node = get_direct_declarator(declarator_node);
	auto direct_declarator_node_first_part_node = get_first_part(direct_declarator_node);
	auto opt_declarator_id_node = syntax_nodes::get<syntax_nodes::declarator_id>(&direct_declarator_node_first_part_node);
	assert(opt_declarator_id_node);
	auto declarator_id_node = *opt_declarator_id_node;
	auto opt_id_expression_node = syntax_nodes::get<syntax_nodes::id_expression>(&declarator_id_node);
	assert(opt_id_expression_node);
	auto id_expression_node = *opt_id_expression_node;
	auto opt_unqualified_id_node = syntax_nodes::get<syntax_nodes::unqualified_id>(&id_expression_node);
	assert(opt_unqualified_id_node);
	auto unqualified_id_node = *opt_unqualified_id_node;
	auto opt_conversion_function_id_node = syntax_nodes::get<syntax_nodes::conversion_function_id>(&unqualified_id_node);
	assert(opt_conversion_function_id_node);
	auto conversion_function_id_node = *opt_conversion_function_id_node;

	auto type_specifier_seq_node = get_type_specifier_seq(conversion_function_id_node);
	for(auto i = type_specifier_seq_node.begin(); i != type_specifier_seq_node.end(); ++i)
	{
		auto type_specifier_node = i->main_node();
		get_type_info
		(
			type_specifier_node,
			opt_return_type,
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
			wchar_t_type,
			is_const,
			is_volatile,
			current_declarative_region
		);
	}

	if(!opt_return_type)
	{
		opt_return_type = get_fundamental_type
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

	assert(opt_return_type);
	semantic_entities::type_shared_ptr_variant return_type = *opt_return_type;

	return_type = decorate_type(return_type, is_const, is_volatile);

	if(auto opt_ptr_operator_seq_node = get_ptr_operator_seq(conversion_function_id_node))
	{
		auto ptr_operator_seq_node = *opt_ptr_operator_seq_node;
		return_type = decorate_type(return_type, ptr_operator_seq_node);
	}

	return return_type;
}

template<class DeclarativeRegionT>
void
get_type_info
(
	const syntax_nodes::type_specifier& type_specifier_node,
	boost::optional<semantic_entities::type_shared_ptr_variant>& t,
	bool& bool_type,
	bool& char_type,
	bool& double_type,
	bool& float_type,
	bool& int_type,
	bool& long_long_type,
	bool& long_type,
	bool& short_type,
	bool& signed_type,
	bool& unsigned_type,
	bool& void_type,
	bool& wchar_t_type,
	bool& is_const,
	bool& is_volatile,
	std::shared_ptr<DeclarativeRegionT> current_declarative_region
)
{
	//simple_type_specifier
	//class_specifier
	//enum_specifier
	//elaborated_type_specifier
	//cv_qualifier

	if(auto opt_simple_type_specifier_node = syntax_nodes::get<syntax_nodes::simple_type_specifier>(&type_specifier_node))
	{
		auto simple_type_specifier_node = *opt_simple_type_specifier_node;
		//simple_template_type_specifier,

		if(auto opt_nested_identifier_or_template_id_node = syntax_nodes::get<syntax_nodes::nested_identifier_or_template_id>(&simple_type_specifier_node))
		{
			auto nested_identifier_or_template_id_node = *opt_nested_identifier_or_template_id_node;
			t =
				std::shared_ptr<const semantic_entities::class_>
				(
					detail::semantic_analysis::name_lookup::find
					<
						semantic_entities::class_,
						false,
						false
					>
					(
						nested_identifier_or_template_id_node,
						current_declarative_region
					)
				)
			;
		}
		else if(auto opt_fundamental_type_specifier_node = syntax_nodes::get<syntax_nodes::fundamental_type_specifier>(&simple_type_specifier_node))
		{
			auto fundamental_type_specifier_node = *opt_fundamental_type_specifier_node;

			if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::char_>>(&fundamental_type_specifier_node))
			{
				char_type = true;
			}
			else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::wchar_t_>>(&fundamental_type_specifier_node))
			{
				wchar_t_type = true;
			}
			else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::bool_>>(&fundamental_type_specifier_node))
			{
				bool_type = true;
			}
			else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::short_>>(&fundamental_type_specifier_node))
			{
				short_type = true;
			}
			else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::int_>>(&fundamental_type_specifier_node))
			{
				int_type = true;
			}
			else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::long_>>(&fundamental_type_specifier_node))
			{
				if(!long_type)
					long_type = true;
				else
					long_long_type = true;
			}
			else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::signed_>>(&fundamental_type_specifier_node))
			{
				signed_type = true;
			}
			else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::unsigned_>>(&fundamental_type_specifier_node))
			{
				unsigned_type = true;
			}
			else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::float_>>(&fundamental_type_specifier_node))
			{
				float_type = true;
			}
			else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::double_>>(&fundamental_type_specifier_node))
			{
				double_type = true;
			}
			else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::void_>>(&fundamental_type_specifier_node))
			{
				void_type = true;
			}
		}
	}
	else if(auto opt_cv_qualifier_node = syntax_nodes::get<syntax_nodes::cv_qualifier>(&type_specifier_node))
	{
		auto cv_qualifier_node = *opt_cv_qualifier_node;
		//syntax_nodes::predefined_text_node<syntax_nodes::str::const_>
		//syntax_nodes::predefined_text_node<syntax_nodes::str::volatile_>

		if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::const_>>(&cv_qualifier_node))
		{
			is_const = true;
		}
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::volatile_>>(&cv_qualifier_node))
		{
			is_volatile = true;
		}
	}
}

} //namespace semantic_analysis

}} //namespace scalpel::cpp

#endif

