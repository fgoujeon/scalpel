/*
Socoa - Source Code Analysis Library
Copyright © 2008, 2009  Florian Goujeon

This file is part of Socoa.

Socoa is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Socoa is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Socoa.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "parse_tree_to_syntax_tree.h"

#include <iostream>
#include <sstream>

using namespace boost::spirit;
using namespace socoa::cpp::syntax_tree;
using namespace socoa::util;

namespace socoa { namespace cpp
{

namespace parse_tree_to_syntax_tree
{

typedef grammar::parser_id id;

/**
Convert the parse_tree node given to the convert() static function to the
correspondant syntax_tree node.
\tparam SyntaxNodeT type of the syntax_node (must be a boost::variant<...>)
\tparam Ids list of the potential values of the given node's parser_id
*/
template<class SyntaxNodeT, int... Ids>
struct node_converter;

template<class SyntaxNodeT>
struct node_converter<SyntaxNodeT>
{
	static
	SyntaxNodeT
	convert(const tree_node_t&)
	{
		assert(false);
	}
};

//If the node is optional, return an empty node instead of
//throwing an error.
template<class SyntaxNodeT>
struct node_converter<boost::optional<SyntaxNodeT>>
{
	static
	boost::optional<SyntaxNodeT>
	convert(const tree_node_t&)
	{
		return boost::optional<SyntaxNodeT>();
	}
};

template<class SyntaxNodeT, int Id, int... Ids>
struct node_converter<SyntaxNodeT, Id, Ids...>
{
	static
	SyntaxNodeT
	convert(const tree_node_t& node)
	{
		const int node_id = get_id(node);
		if(node_id == Id)
		{
			return SyntaxNodeT(generic_converter_from_id<SyntaxNodeT, Id>::convert(node));
		}
		else
		{
			return node_converter<SyntaxNodeT, Ids...>::convert(node);
		}
	}
};

/**
Converts the given node.
*/
template<class SyntaxNodeT, int... Ids>
SyntaxNodeT
convert_node(const tree_node_t& node)
{
	return node_converter<SyntaxNodeT, Ids...>::convert(node);
}

/**
Converts a sequence of nodes.
*/
template<class ContainerT, class SyntaxNodeT, int... Ids>
ContainerT
convert_nodes(const tree_node_t& parent_node)
{
	ContainerT c;
    for(tree_node_iterator_t i = parent_node.children.begin(); i != parent_node.children.end(); ++i) //for each child node
	{
		const tree_node_t& child_node = *i;

		boost::optional<SyntaxNodeT> optional_node = convert_node<boost::optional<SyntaxNodeT>, Ids...>(child_node);
		if(optional_node)
		{
			c.push_back(*optional_node);
		}
	}
	return c;
}


template<class SyntaxNodeT, grammar::parser_id... Ids>
struct node_finder_and_converter
{
	static
	SyntaxNodeT
	convert(const tree_node_t& parent_node)
	{
		const tree_node_t* child_node = find_child_node<Ids...>(parent_node);
		assert(child_node);
		return node_converter<SyntaxNodeT, Ids...>::convert
		(
			*child_node
		);
	}
};

template<class SyntaxNodeT, grammar::parser_id... Ids>
struct node_finder_and_converter<boost::optional<SyntaxNodeT>, Ids...>
{
	static
	boost::optional<SyntaxNodeT>
	convert(const tree_node_t& parent_node)
	{
		const tree_node_t* child_node = find_child_node<Ids...>(parent_node);
		if(child_node)
			return boost::optional<SyntaxNodeT>
			(
				node_converter<SyntaxNodeT, Ids...>::convert
				(
					*child_node
				)
			);
		else
			return boost::optional<SyntaxNodeT>();
	}
};

/**
Finds a node corresponding to the given parser id among the child nodes of the
given parent node and converts it.
*/
template<class SyntaxNodeT, grammar::parser_id... Ids>
SyntaxNodeT
find_and_convert_node(const tree_node_t& parent_node)
{
	return node_finder_and_converter<SyntaxNodeT, Ids...>::convert(parent_node);
}




/*------------------------------------------
			convert_* functions
------------------------------------------*/

syntax_tree_t
convert_tree(const tree_node_t& node)
{
	const tree_node_t& child_node = get_only_child_node(node);
    assert(child_node.value.id() == id::TRANSLATION_UNIT);

	const tree_node_t& grandchild_node = get_only_child_node(child_node);
    assert(grandchild_node.value.id() == id::DECLARATION_SEQ);

	return convert_nodes
	<
		declaration_seq,
		declaration,
		id::DECLARATION
	>
	(
		grandchild_node
	);
}

identifier
convert_identifier(const tree_node_t& node)
{
    assert
    (
        node.value.id() == grammar::IDENTIFIER ||
        node.value.id() == grammar::TYPE_NAME
    );

    return identifier(get_only_child_value(node));
}

id_expression
convert_id_expression(const tree_node_t& node)
{
    assert(node.value.id() == id::ID_EXPRESSION);

	return convert_node
	<
		id_expression,
		id::UNQUALIFIED_ID,
	   	id::QUALIFIED_ID
	>
	(
		get_only_child_node(node)
	);
}

unqualified_id
convert_unqualified_id(const tree_node_t& node)
{
    assert(node.value.id() == grammar::UNQUALIFIED_ID);

	return convert_node
	<
		unqualified_id,
		id::OPERATOR_FUNCTION_ID,
		id::CONVERSION_FUNCTION_ID,
		id::DESTRUCTOR_NAME,
		id::TEMPLATE_ID,
		id::IDENTIFIER
	>
	(
		get_only_child_node(node)
	);
}

qualified_id
convert_qualified_id(const tree_node_t& node)
{
    assert(node.value.id() == grammar::QUALIFIED_ID);

	return convert_node
	<
		qualified_id,
		id::QUALIFIED_NESTED_ID,
		id::QUALIFIED_OPERATOR_FUNCTION_ID,
		id::QUALIFIED_TEMPLATE_ID,
		id::QUALIFIED_IDENTIFIER
	>
	(
		get_only_child_node(node)
	);
}

qualified_nested_id
convert_qualified_nested_id(const tree_node_t& node)
{
    assert(node.value.id() == grammar::QUALIFIED_NESTED_ID);

    return qualified_nested_id
    (
		check_node_existence(node, "::", 0),
		find_and_convert_node<nested_name_specifier, id::NESTED_NAME_SPECIFIER>(node),
		check_node_existence(node, "template", 1) || check_node_existence(node, "template", 2),
		find_and_convert_node<unqualified_id, id::UNQUALIFIED_ID>(node)
    );
}

qualified_operator_function_id
convert_qualified_operator_function_id(const tree_node_t& node)
{
    assert(node.value.id() == grammar::QUALIFIED_OPERATOR_FUNCTION_ID);

    return qualified_operator_function_id
    (
        //find_and_convert_node<operator_function_id, id::OPERATOR_FUNCTION_ID>(node)
    );
}

qualified_template_id
convert_qualified_template_id(const tree_node_t& node)
{
    assert(node.value.id() == grammar::QUALIFIED_TEMPLATE_ID);

    return qualified_template_id
    (
        find_and_convert_node<template_id, id::TEMPLATE_ID>(node)
    );
}

qualified_identifier
convert_qualified_identifier(const tree_node_t& node)
{
    assert(node.value.id() == grammar::QUALIFIED_IDENTIFIER);

    return qualified_identifier
    (
        find_and_convert_node<identifier, id::IDENTIFIER>(node)
    );
}

nested_name_specifier
convert_nested_name_specifier(const tree_node_t& node)
{
    assert(node.value.id() == grammar::NESTED_NAME_SPECIFIER);

    return nested_name_specifier
    (
        find_and_convert_node<identifier_or_template_id, id::IDENTIFIER_OR_TEMPLATE_ID>(node),
		convert_nodes
		<
			std::vector<nested_name_specifier::second_part>,
			nested_name_specifier::second_part,
			id::NESTED_NAME_SPECIFIER_SECOND_PART
		>(node)
    );
}

nested_name_specifier::second_part
convert_nested_name_specifier_second_part(const tree_node_t& node)
{
    assert(node.value.id() == grammar::NESTED_NAME_SPECIFIER_SECOND_PART);

    return nested_name_specifier::second_part
    (
		check_node_existence(node, "template", 0),
		find_and_convert_node<identifier_or_template_id, id::IDENTIFIER_OR_TEMPLATE_ID>(node)
    );
}

declaration
convert_declaration(const tree_node_t& node)
{
    assert(node.value.id() == grammar::DECLARATION);

	return convert_node
	<
		declaration,
		id::BLOCK_DECLARATION,
		id::FUNCTION_DEFINITION,
		id::TEMPLATE_DECLARATION,
//            id::EXPLICIT_INSTANTIATION,
//            id::EXPLICIT_SPECIALIZATION,
//            id::LINKAGE_SPECIFICATION,
		id::NAMESPACE_DEFINITION
	>
	(
		get_only_child_node(node)
	);
}

block_declaration
convert_block_declaration(const tree_node_t& node)
{
    assert(node.value.id() == grammar::BLOCK_DECLARATION);

	return convert_node
	<
		block_declaration,
		//id::ASM_DEFINITION,
		id::SIMPLE_DECLARATION,
		//id::NAMESPACE_ALIAS_DEFINITION,
		id::USING_DECLARATION,
		id::USING_DIRECTIVE
	>
	(
		get_only_child_node(node)
	);
}

simple_declaration
convert_simple_declaration(const tree_node_t& node)
{
    assert(node.value.id() == grammar::SIMPLE_DECLARATION);

    return simple_declaration
    (
		find_and_convert_node<boost::optional<decl_specifier_seq>, id::SIMPLE_DECLARATION_DECL_SPECIFIER_SEQ>(node),
		find_and_convert_node<boost::optional<init_declarator_list>, id::INIT_DECLARATOR_LIST>(node)
    );
}

decl_specifier
convert_decl_specifier(const tree_node_t& node)
{
    assert(node.value.id() == grammar::DECL_SPECIFIER);

	return convert_node
	<
		decl_specifier,
		id::STORAGE_CLASS_SPECIFIER,
		id::TYPE_SPECIFIER,
		id::FUNCTION_SPECIFIER
	>
	(
		get_only_child_node(node)
	);
}

type_specifier
convert_type_specifier(const tree_node_t& node)
{
    assert(node.value.id() == grammar::TYPE_SPECIFIER);

	return convert_node
	<
		type_specifier,
		id::SIMPLE_TYPE_SPECIFIER,
		id::CLASS_SPECIFIER,
		//id::ENUM_SPECIFIER,
		id::ELABORATED_TYPE_SPECIFIER,
		id::CV_QUALIFIER
		//id::TYPEOF_EXPRESSION
	>
	(
		get_only_child_node(node)
	);
}

simple_type_specifier
convert_simple_type_specifier(const tree_node_t& node)
{
    assert(node.value.id() == grammar::SIMPLE_TYPE_SPECIFIER);

	return convert_node
	<
		simple_type_specifier,
		id::NESTED_IDENTIFIER_OR_TEMPLATE_ID,
		id::SIMPLE_TEMPLATE_TYPE_SPECIFIER,
		id::BUILT_IN_TYPE_SPECIFIER
	>
	(
		get_only_child_node(node)
	);
}

simple_template_type_specifier
convert_simple_template_type_specifier(const tree_node_t& node)
{
    assert(node.value.id() == grammar::SIMPLE_TEMPLATE_TYPE_SPECIFIER);

    return simple_template_type_specifier
	(
		check_node_existence(node, "::", 0),
		find_and_convert_node<nested_name_specifier, id::NESTED_NAME_SPECIFIER>(node),
		find_and_convert_node<template_id, id::TEMPLATE_ID>(node)
	);
}

identifier_or_template_id
convert_identifier_or_template_id(const tree_node_t& node)
{
    assert(node.value.id() == grammar::IDENTIFIER_OR_TEMPLATE_ID);

	return convert_node
	<
		identifier_or_template_id,
		id::IDENTIFIER,
		id::TEMPLATE_ID
	>
	(
		get_only_child_node(node)
	);
}

namespace_definition
convert_namespace_definition(const tree_node_t& node)
{
    assert(node.value.id() == grammar::NAMESPACE_DEFINITION);

    return namespace_definition
    (
        find_and_convert_node<boost::optional<identifier>, id::IDENTIFIER>(node),
        find_and_convert_node<declaration_seq, id::DECLARATION_SEQ>(node)
    );
}

using_declaration
convert_using_declaration(const tree_node_t& node)
{
    assert(node.value.id() == grammar::USING_DECLARATION);

    return using_declaration
    (
        check_node_existence(node, "typename", 1),
        check_node_existence(node, "::"),
        find_and_convert_node<boost::optional<nested_name_specifier>, id::NESTED_NAME_SPECIFIER>(node),
        find_and_convert_node<unqualified_id, id::UNQUALIFIED_ID>(node)
    );
}

using_directive
convert_using_directive(const tree_node_t& node)
{
    assert(node.value.id() == grammar::USING_DIRECTIVE);

    return using_directive
    (
        check_node_existence(node, "::", 2),
        find_and_convert_node<boost::optional<nested_name_specifier>, id::NESTED_NAME_SPECIFIER>(node),
        find_and_convert_node<identifier, id::IDENTIFIER>(node)
    );
}

init_declarator
convert_init_declarator(const tree_node_t& node)
{
    assert(node.value.id() == grammar::INIT_DECLARATOR);

    return init_declarator
    (
		find_and_convert_node<declarator, id::DECLARATOR>(node)
    );
}

declarator
convert_declarator(const tree_node_t& node)
{
    assert(node.value.id() == grammar::DECLARATOR);

    return declarator
    (
		convert_nodes
		<
			std::vector<ptr_operator>,
			ptr_operator,
			id::PTR_OPERATOR
		>(node),
		find_and_convert_node<direct_declarator, id::DIRECT_DECLARATOR>(node)
    );
}

direct_declarator
convert_direct_declarator(const tree_node_t& node)
{
    assert(node.value.id() == grammar::DIRECT_DECLARATOR);

    direct_declarator decl
    (
		find_and_convert_node<boost::optional<declarator_id>, id::DECLARATOR_ID>(node),
		find_and_convert_node<boost::optional<declarator>, id::DECLARATOR>(node),
		convert_nodes
		<
			std::vector<direct_declarator::other_part>,
			direct_declarator::other_part,
			id::DIRECT_DECLARATOR_FUNCTION_PART
			//id::DIRECT_DECLARATOR_ARRAY_PART
		>(node)
    );

	return decl;
}

direct_declarator::function_part
convert_direct_declarator_function_part(const tree_node_t& node)
{
    assert(node.value.id() == grammar::DIRECT_DECLARATOR_FUNCTION_PART);

	boost::optional<parameter_declaration_clause> new_parameter_declaration_clause = find_and_convert_node<boost::optional<parameter_declaration_clause>, id::PARAMETER_DECLARATION_CLAUSE>(node);

    ///@todo why must I do this?
    //grammar defines that this node MUST exist, but in practice it's not always the case
    if(!new_parameter_declaration_clause)
    {
        typedef util::sequence<parameter_declaration, util::extern_strings::comma> parameter_declaration_seq;

        //create an empty parameter declaration clause, if node didn't have been found
        new_parameter_declaration_clause = parameter_declaration_clause
        (
			parameter_declaration_seq(),
			false,
			false
        );
    }

    return direct_declarator::function_part
    (
        *new_parameter_declaration_clause,
        find_and_convert_node<boost::optional<cv_qualifier_seq>, id::CV_QUALIFIER_SEQ>(node)
    );
}

direct_declarator::array_part
convert_direct_declarator_array_part(const tree_node_t& node)
{
    assert(node.value.id() == grammar::DIRECT_DECLARATOR_ARRAY_PART);

    return direct_declarator::array_part();
}

ptr_operator
convert_ptr_operator(const tree_node_t& node)
{
    assert(node.value.id() == grammar::PTR_OPERATOR);

    #ifndef NDEBUG
    bool asterisk = check_node_existence(node, "*");
    bool ampersand = check_node_existence(node, "&", 0);
    assert
    (
        (asterisk && !ampersand) ||
        (!asterisk && ampersand)
    );
    #endif

    return ptr_operator
	(
		check_node_existence(node, "*") ? ptr_operator::ASTERISK : ptr_operator::AMPERSAND,
		check_node_existence(node, "::", 0),
		find_and_convert_node<boost::optional<nested_name_specifier>, id::NESTED_NAME_SPECIFIER>(node),
		find_and_convert_node<boost::optional<cv_qualifier_seq>, id::CV_QUALIFIER_SEQ>(node)
    );
}

cv_qualifier
convert_cv_qualifier(const tree_node_t& node)
{
    assert(node.value.id() == grammar::CV_QUALIFIER);

    const tree_node_t child_node = *node.children.begin();
    const parser_id child_id = child_node.value.id();
    if(child_id == grammar::RESTRICT_KEYWORD)
	{
		const std::string child_value = get_only_child_value(child_node);
        return cv_qualifier(child_value);
	}
    else
	{
		const std::string value = get_only_child_value(node);
		return cv_qualifier(value);
	}
}

declarator_id
convert_declarator_id(const tree_node_t& node)
{
    assert(node.value.id() == grammar::DECLARATOR_ID);

	return convert_node
	<
		declarator_id,
		id::ID_EXPRESSION,
		id::NESTED_IDENTIFIER_OR_TEMPLATE_ID
	>
	(
		get_only_child_node(node)
	);
}

parameter_declaration_clause
convert_parameter_declaration_clause(const tree_node_t& node)
{
    assert(node.value.id() == grammar::PARAMETER_DECLARATION_CLAUSE);

    bool trailing_comma = check_node_existence(node, ",", 1);
    bool ellipsis = check_node_existence(node, "...");

    if(trailing_comma) assert(ellipsis);

    return parameter_declaration_clause
    (
        parameter_declaration_clause
        {
            find_and_convert_node<parameter_declaration_list, id::PARAMETER_DECLARATION_LIST>(node),
            trailing_comma,
            ellipsis
        }
    );
}

///@todo factorize it
parameter_declaration
convert_parameter_declaration(const tree_node_t& node)
{
    assert(node.value.id() == grammar::PARAMETER_DECLARATION);

    return parameter_declaration
    (
		find_and_convert_node
		<
			decl_specifier_seq,
			id::PARAMETER_DECLARATION_DECL_SPECIFIER_SEQ1,
			id::PARAMETER_DECLARATION_DECL_SPECIFIER_SEQ2,
			id::PARAMETER_DECLARATION_DECL_SPECIFIER_SEQ3,
			id::PARAMETER_DECLARATION_DECL_SPECIFIER_SEQ4,
			id::DECL_SPECIFIER_SEQ
		>(node),
		find_and_convert_node<boost::optional<declarator>, id::DECLARATOR>(node),
		false
    );
}

///@todo factorize it
function_definition
convert_function_definition(const tree_node_t& node)
{
    assert(node.value.id() == grammar::FUNCTION_DEFINITION);

    //find decl_specifier_seq node...
    const tree_node_t* decl_specifier_seq_node;
    decl_specifier_seq_node = find_child_node(node, grammar::FUNCTION_DEFINITION_DECL_SPECIFIER_SEQ1);
    if(!decl_specifier_seq_node)
        decl_specifier_seq_node = find_child_node(node, grammar::FUNCTION_DEFINITION_DECL_SPECIFIER_SEQ2);
    if(!decl_specifier_seq_node)
        decl_specifier_seq_node = find_child_node(node, grammar::FUNCTION_DEFINITION_DECL_SPECIFIER_SEQ3);

    //... and evaluate it
    util::sequence<decl_specifier> new_decl_specifier_seq;
    if(decl_specifier_seq_node)
    {
        new_decl_specifier_seq = convert_sequence
        <
            decl_specifier,
            util::extern_strings::space
        >(*decl_specifier_seq_node);
    }

    //create function definition object
    return function_definition
    (
        new_decl_specifier_seq,
        find_and_convert_node<declarator, id::DECLARATOR>(node),
        find_and_convert_node<boost::optional<ctor_initializer>, id::CTOR_INITIALIZER>(node)
    );
}

class_specifier
convert_class_specifier(const tree_node_t& node)
{
    assert(node.value.id() == grammar::CLASS_SPECIFIER);

    return class_specifier
    (
        find_and_convert_node<class_head, id::CLASS_HEAD>(node),
        find_and_convert_node<boost::optional<member_specification>, id::MEMBER_SPECIFICATION>(node)
    );
}

class_head
convert_class_head(const tree_node_t& node)
{
    assert(node.value.id() == grammar::CLASS_HEAD);

    return class_head
    (
		find_and_convert_node<class_key, id::CLASS_KEY>(node),
		find_and_convert_node<boost::optional<nested_name_specifier>, id::NESTED_NAME_SPECIFIER>(node),
		find_and_convert_node<boost::optional<template_id>, id::TEMPLATE_ID>(node),
		find_and_convert_node<boost::optional<identifier>, id::IDENTIFIER>(node),
		find_and_convert_node<boost::optional<base_clause>, id::BASE_CLAUSE>(node)
    );
}

member_specification
convert_member_specification(const tree_node_t& node)
{
    assert(node.value.id() == grammar::MEMBER_SPECIFICATION);

    return member_specification
    (
		convert_nodes
		<
			std::vector<member_specification_part>,
			member_specification_part,
			id::MEMBER_DECLARATION,
			id::MEMBER_SPECIFICATION_ACCESS_SPECIFIER
		>(node)
    );
}

member_specification_access_specifier
convert_member_specification_access_specifier(const tree_node_t& node)
{
    assert(node.value.id() == grammar::MEMBER_SPECIFICATION_ACCESS_SPECIFIER);

    return member_specification_access_specifier
    (
        find_and_convert_node<access_specifier, id::ACCESS_SPECIFIER>(node)
    );
}

member_declaration
convert_member_declaration(const tree_node_t& node)
{
    assert(node.value.id() == grammar::MEMBER_DECLARATION);

	return convert_node
	<
		member_declaration,
		id::MEMBER_DECLARATION_MEMBER_DECLARATOR_LIST,
		id::MEMBER_DECLARATION_UNQUALIFIED_ID,
		id::MEMBER_DECLARATION_FUNCTION_DEFINITION,
		id::USING_DECLARATION,
		id::TEMPLATE_DECLARATION
	>
	(
		get_only_child_node(node)
	);
}

member_declaration_member_declarator_list
convert_member_declaration_member_declarator_list(const tree_node_t& node)
{
    assert(node.value.id() == grammar::MEMBER_DECLARATION_MEMBER_DECLARATOR_LIST);

    return member_declaration_member_declarator_list
    (
        find_and_convert_node<boost::optional<decl_specifier_seq>, id::MEMBER_DECLARATION_DECL_SPECIFIER_SEQ>(node),
        find_and_convert_node<boost::optional<member_declarator_list>, id::MEMBER_DECLARATOR_LIST>(node)
    );
}

member_declaration_unqualified_id
convert_member_declaration_unqualified_id(const tree_node_t& node)
{
    assert(node.value.id() == grammar::MEMBER_DECLARATION_UNQUALIFIED_ID);

    return member_declaration_unqualified_id
    (
        check_node_existence(node, "::", 0),
        find_and_convert_node<nested_name_specifier, id::NESTED_NAME_SPECIFIER>(node),
        check_node_existence(node, "template"),
        find_and_convert_node<unqualified_id, id::UNQUALIFIED_ID>(node)
    );
}

member_declaration_function_definition
convert_member_declaration_function_definition(const tree_node_t& node)
{
    assert(node.value.id() == grammar::MEMBER_DECLARATION_FUNCTION_DEFINITION);

    return member_declaration_function_definition
    (
        find_and_convert_node<function_definition, id::FUNCTION_DEFINITION>(node)
    );
}

member_declarator
convert_member_declarator(const tree_node_t& node)
{
    assert(node.value.id() == grammar::MEMBER_DECLARATOR);

	return convert_node
	<
		member_declarator,
		id::MEMBER_DECLARATOR_DECLARATOR,
		id::MEMBER_DECLARATOR_BIT_FIELD_MEMBER
	>
	(
		get_only_child_node(node)
	);
}

member_declarator_declarator
convert_member_declarator_declarator(const tree_node_t& node)
{
    assert(node.value.id() == grammar::MEMBER_DECLARATOR_DECLARATOR);

    return member_declarator_declarator
    (
        find_and_convert_node<declarator, id::DECLARATOR>(node),
        check_node_existence(node, grammar::PURE_SPECIFIER, 1)
    );
}

member_declarator_bit_field_member
convert_member_declarator_bit_field_member(const tree_node_t& node)
{
    assert(node.value.id() == grammar::MEMBER_DECLARATOR_BIT_FIELD_MEMBER);

    return member_declarator_bit_field_member
    (
        find_and_convert_node<boost::optional<identifier>, id::IDENTIFIER>(node)
    );
}

base_clause
convert_base_clause(const tree_node_t& node)
{
    assert(node.value.id() == grammar::BASE_CLAUSE);

	boost::optional<base_specifier_list> obs = find_and_convert_node<boost::optional<base_specifier_list>, id::BASE_SPECIFIER>(node);
	base_specifier_list bs;
	if(obs)
		bs = *obs;

    //unlike what grammar defines, base specifier may be missing
    return base_clause
    (
		bs
    );
}

base_specifier
convert_base_specifier(const tree_node_t& node)
{
    assert(node.value.id() == grammar::BASE_SPECIFIER);

    return base_specifier
    (
		check_node_existence(node, "virtual"),
		convert_string_enumeration<syntax_tree::access_specifier>
		(
			*find_child_node(node, grammar::ACCESS_SPECIFIER)
		),
		find_and_convert_node<boost::optional<nested_identifier_or_template_id>, id::NESTED_IDENTIFIER_OR_TEMPLATE_ID>(node)
    );
}

ctor_initializer
convert_ctor_initializer(const tree_node_t& node)
{
    assert(node.value.id() == grammar::CTOR_INITIALIZER);

    return ctor_initializer
    (
		find_and_convert_node<mem_initializer_list, id::MEM_INITIALIZER_LIST>(node)
    );
}

mem_initializer
convert_mem_initializer(const tree_node_t& node)
{
    assert(node.value.id() == grammar::MEM_INITIALIZER);

    return mem_initializer
    (
		find_and_convert_node<mem_initializer_id, id::MEM_INITIALIZER_ID>(node)
    );
}

mem_initializer_id
convert_mem_initializer_id(const tree_node_t& node)
{
    assert(node.value.id() == grammar::MEM_INITIALIZER_ID);

	return convert_node
	<
		mem_initializer_id,
		id::NESTED_IDENTIFIER_OR_TEMPLATE_ID,
		id::IDENTIFIER
	>
	(
		get_only_child_node(node)
	);
}

template_declaration
convert_template_declaration(const tree_node_t& node)
{
    assert(node.value.id() == grammar::TEMPLATE_DECLARATION);

    return template_declaration
    (
        check_node_existence(node, "export", 0),
        find_and_convert_node<declaration, id::DECLARATION>(node)
    );
}

template_id
convert_template_id(const tree_node_t& node)
{
    assert(node.value.id() == grammar::TEMPLATE_ID);

    return template_id
    (
        find_and_convert_node<identifier, id::TYPE_NAME>(node),
        find_and_convert_node<template_argument_list, id::TEMPLATE_ARGUMENT_LIST>(node)
    );
}

template_argument
convert_template_argument(const tree_node_t& node)
{
    assert(node.value.id() == grammar::TEMPLATE_ARGUMENT);

	return convert_node
	<
		template_argument,
		//id::TEMPLATE_ARGUMENT_ASSIGNMENT_EXPRESSION,
		//id::TYPE_ID,
		id::ID_EXPRESSION
	>
	(
		get_only_child_node(node)
	);
}

nested_identifier_or_template_id
convert_nested_identifier_or_template_id(const tree_node_t& node)
{
    assert(node.value.id() == grammar::NESTED_IDENTIFIER_OR_TEMPLATE_ID);

    return nested_identifier_or_template_id
    (
        check_node_existence(node, "::", 0),
        find_and_convert_node<boost::optional<nested_name_specifier>, id::NESTED_NAME_SPECIFIER>(node),
        find_and_convert_node<identifier_or_template_id, id::IDENTIFIER_OR_TEMPLATE_ID>(node)
    );
}

elaborated_type_specifier
convert_elaborated_type_specifier(const tree_node_t& node)
{
    assert(node.value.id() == grammar::ELABORATED_TYPE_SPECIFIER);

	return elaborated_type_specifier();
}

destructor_name
convert_destructor_name(const tree_node_t& node)
{
    assert(node.value.id() == grammar::DESTRUCTOR_NAME);

	return destructor_name(identifier(""));
}

operator_function_id
convert_operator_function_id(const tree_node_t& node)
{
    assert(node.value.id() == id::OPERATOR_FUNCTION_ID);

	return operator_function_id();
}

conversion_function_id
convert_conversion_function_id(const tree_node_t& node)
{
    assert(node.value.id() == id::CONVERSION_FUNCTION_ID);

	return conversion_function_id();
}


const tree_node_t*
find_child_node(const tree_node_t& parent_node, grammar::parser_id child_id)
{
    for(tree_node_iterator_t i = parent_node.children.begin(); i != parent_node.children.end(); ++i) //for each child
    {
        const tree_node_t& child_node = *i;

        boost::spirit::parser_id id = child_node.value.id();
        if(id == child_id)
        {
            return &child_node;
        }
    }

    return 0;
}

bool
check_node_existence(const tree_node_t& parent_node, const std::string& value, unsigned int position)
{
    if(parent_node.children.size() <= position)
        return false;

    return get_value(parent_node.children[position]) == value;
}

bool
check_node_existence(const tree_node_t& parent_node, const std::string& value)
{
    for(tree_node_iterator_t i = parent_node.children.begin(); i != parent_node.children.end(); ++i) //for each child
    {
        const tree_node_t& child_node = *i;
        if(get_value(child_node) == value)
        {
            return true;
        }
    }

    return false;
}

bool
check_node_existence
(
    const tree_node_t& parent_node,
    const grammar::parser_id id,
    unsigned int position
)
{
    if(parent_node.children.size() <= position)
        return false;

    return parent_node.children[position].value.id() == id;
}

bool
check_node_existence
(
    const tree_node_t& parent_node,
    const grammar::parser_id id
)
{
    for
    (
        tree_node_iterator_t i = parent_node.children.begin();
        i != parent_node.children.end();
        ++i
    ) //for each child
    {
        const tree_node_t& child_node = *i;
        const parser_id child_id = child_node.value.id();

        if(child_id == id)
        {
            return true;
        }
    }

    return false;
}

std::string
get_only_child_value(const tree_node_t& node)
{
    assert(node.children.size() == 1);

    //get child node
    const tree_node_t& child_node = *node.children.begin();

    return get_value(child_node);
}

std::string
get_value(const tree_node_t& node)
{
    //get value
    std::ostringstream value_oss;
    for
    (
        tree_node_value_iterator_t i = node.value.begin();
        i != node.value.end();
        ++i
    ) //iterate node value
    {
        value_oss << *i;
    }

    return strip_redundant_spaces(value_oss.str());
}

std::string
strip_redundant_spaces(const std::string& str)
{
    std::string result;

    bool skip = true;
    for(unsigned int i = 0; i < str.size(); ++i)
    {
        const char c = str[i];

        if(c == ' ' || c == '\t' || c == '\n')
        {
            if(!skip)
            {
                result += ' ';
                skip = true;
            }
        }
        else
        {
            result += c;
            skip = false;
        }
    }

    return result;
}

int
get_id(const tree_node_t& node)
{
    boost::spirit::parser_id id = node.value.id();

    for(unsigned int i = 0; i < 400; ++i)
    {
        if(id == i)
        {
            return i;
        }
    }

    return -1;
}

}

}} //namespace socoa::cpp

