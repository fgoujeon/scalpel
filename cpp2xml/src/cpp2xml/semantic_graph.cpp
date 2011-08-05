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

#include "semantic_graph.hpp"
#include <scalpel/utility/variant.hpp>
#include <vector>
#include <sstream>

namespace cpp2xml
{

using namespace detail;

semantic_graph_serializer::semantic_graph_serializer(std::ostream& output):
	output_(output),
	writer_(output)
{
}

void
semantic_graph_serializer::operator()(const namespace_& entity)
{
	set_ids(entity);

	writer_.open_object();
	serialize_namespace(entity);
	writer_.close_object();
}

void
semantic_graph_serializer::operator()(const linked_namespace& entity)
{
	set_ids(entity);

	writer_.open_object();
	serialize_namespace(entity);
	writer_.close_object();
}



semantic_graph_serializer::serialize_type_visitor::serialize_type_visitor
(
	semantic_graph_serializer& serializer
):
	serializer_(serializer),
	output_(serializer_.output_)
{
}

void
semantic_graph_serializer::serialize_type_visitor::operator()(const fundamental_type& type)
{
	serializer_.writer_.write_key_value_pair("category", "fundamental type");
	serializer_.serialize_fundamental_type(type);
}

void
semantic_graph_serializer::serialize_type_visitor::operator()(const function_type& type)
{
	serializer_.writer_.write_key_value_pair("category", "function type");
	serializer_.serialize_function_type(type);
}

void
semantic_graph_serializer::serialize_type_visitor::operator()(const cv_qualified_type& type)
{
	serializer_.writer_.write_key_value_pair("category", "cv-qualified type");

	if(type.const_qualified())
		serializer_.writer_.write_key_value_pair("const", true);
	if(type.volatile_qualified())
		serializer_.writer_.write_key_value_pair("volatile", true);

	serializer_.writer_.open_object("qualified type");
	serializer_.serialize_type(type.qualified_type());
	serializer_.writer_.close_object();
}

void
semantic_graph_serializer::serialize_type_visitor::operator()(const pointer& type)
{
	serializer_.writer_.write_key_value_pair("category", "pointer");

	serializer_.writer_.open_object("qualified type");
	serializer_.serialize_type(type.qualified_type());
	serializer_.writer_.close_object();
}

void
semantic_graph_serializer::serialize_type_visitor::operator()(const pointer_to_member& type)
{
	serializer_.writer_.write_key_value_pair("category", "pointer to member");
	serializer_.serialize_class_id_attribute(type.parent_class());

	serializer_.writer_.open_object("qualified type");
	serializer_.serialize_type(type.qualified_type());
	serializer_.writer_.close_object();
}

void
semantic_graph_serializer::serialize_type_visitor::operator()(const reference& type)
{
	serializer_.writer_.write_key_value_pair("category", "reference");

	serializer_.writer_.open_object("qualified type");
	serializer_.serialize_type(type.qualified_type());
	serializer_.writer_.close_object();
}

void
semantic_graph_serializer::serialize_type_visitor::operator()(const array& type)
{
	serializer_.writer_.write_key_value_pair("category", "array");

	serializer_.writer_.write_key_value_pair("size", type.size());
	serializer_.writer_.open_object("qualified type");
	serializer_.serialize_type(type.qualified_type());
	serializer_.writer_.close_object();
}

void
semantic_graph_serializer::serialize_type_visitor::operator()(const class_* type)
{
	serializer_.writer_.write_key_value_pair("category", "class");
	serializer_.writer_.write_key_value_pair("id", serializer_.get_id(*type));
}

void
semantic_graph_serializer::serialize_type_visitor::operator()(const member_class* type)
{
	serializer_.writer_.write_key_value_pair("category", "member class");
	serializer_.writer_.write_key_value_pair("id", serializer_.get_id(*type));
}

void
semantic_graph_serializer::serialize_type_visitor::operator()(const union_* type)
{
	serializer_.writer_.write_key_value_pair("category", "union");
	serializer_.writer_.write_key_value_pair("id", serializer_.get_id(*type));
}

void
semantic_graph_serializer::serialize_type_visitor::operator()(const member_union* type)
{
	serializer_.writer_.write_key_value_pair("category", "member union");
	serializer_.writer_.write_key_value_pair("id", serializer_.get_id(*type));
}

void
semantic_graph_serializer::serialize_type_visitor::operator()(const anonymous_union* type)
{
	serializer_.writer_.write_key_value_pair("category", "anonymous union");
	serializer_.writer_.write_key_value_pair("id", serializer_.get_id(*type));
}

void
semantic_graph_serializer::serialize_type_visitor::operator()(const anonymous_member_union* type)
{
	serializer_.writer_.write_key_value_pair("category", "anonymous member union");
	serializer_.writer_.write_key_value_pair("id", serializer_.get_id(*type));
}

void
semantic_graph_serializer::serialize_type_visitor::operator()(const enum_t* type)
{
	serializer_.writer_.write_key_value_pair("category", "enum");
	serializer_.writer_.write_key_value_pair("id", serializer_.get_id(*type));
}

void
semantic_graph_serializer::serialize_type_visitor::operator()(const member_enum_t* type)
{
	serializer_.writer_.write_key_value_pair("category", "member enum");
	serializer_.writer_.write_key_value_pair("id", serializer_.get_id(*type));
}

void
semantic_graph_serializer::serialize_type
(
	const semantic_entities::type_t& n
)
{
	serialize_type_visitor visitor(*this);
	apply_visitor(visitor, n);
}



void
semantic_graph_serializer::serialize_fundamental_type
(
	const fundamental_type type
)
{
	std::map<fundamental_type, const char*> fundamental_types_map =
	{
		{fundamental_type::BOOL, "bool"},
		{fundamental_type::CHAR, "char"},
		{fundamental_type::DOUBLE, "double"},
		{fundamental_type::FLOAT, "float"},
		{fundamental_type::INT, "int"},
		{fundamental_type::LONG_DOUBLE, "long double"},
		{fundamental_type::LONG_INT, "long int"},
		{fundamental_type::LONG_LONG_INT, "long long int"},
		{fundamental_type::SHORT_INT, "short int"},
		{fundamental_type::SIGNED_CHAR, "signed char"},
		{fundamental_type::UNSIGNED_CHAR, "unsigned char"},
		{fundamental_type::UNSIGNED_INT, "unsigned int"},
		{fundamental_type::UNSIGNED_LONG_INT, "unsigned long int"},
		{fundamental_type::UNSIGNED_LONG_LONG_INT, "unsigned long long int"},
		{fundamental_type::UNSIGNED_SHORT_INT, "unsigned short int"},
		{fundamental_type::VOID, "void"},
		{fundamental_type::WCHAR_T, "wchar_t"}
	};

	writer_.write_key_value_pair("type", fundamental_types_map[type]);
}

void
semantic_graph_serializer::serialize_base_class
(
	const base_class& entity
)
{
	writer_.open_object();

	serialize_class_id_attribute(entity.base());

	switch(entity.access())
	{
		case member_access::PUBLIC:
			writer_.write_key_value_pair("access", "public");
			break;
		case member_access::PROTECTED:
			writer_.write_key_value_pair("access", "protected");
			break;
		case member_access::PRIVATE:
			writer_.write_key_value_pair("access", "private");
			break;
	}

	if(entity.is_virtual())
		writer_.write_key_value_pair("virtual", true);

	writer_.close_object();
}

void
semantic_graph_serializer::serialize_constructor
(
	const constructor& entity
)
{
	serialize_access_property(entity);
	if(entity.variadic())
		writer_.write_key_value_pair("variadic", true);
	if(entity.is_inline())
		writer_.write_key_value_pair("inline", true);
	if(entity.is_explicit())
		writer_.write_key_value_pair("explicit", true);
	if(entity.defined())
		writer_.write_key_value_pair("defined", true);

	serialize_function_parameter_list(entity.parameters());
}

void
semantic_graph_serializer::serialize_destructor
(
	const destructor& entity
)
{
	serialize_access_property(entity);
	if(entity.is_inline())
		writer_.write_key_value_pair("inline", true);
	if(entity.is_virtual())
		writer_.write_key_value_pair("virtual", true);
	if(entity.is_pure())
		writer_.write_key_value_pair("pure", true);
	if(entity.defined())
		writer_.write_key_value_pair("defined", true);
}

void
semantic_graph_serializer::serialize_operator_member_function
(
	const operator_member_function& entity
)
{
	serialize_id_attribute(entity);
	serialize_overloaded_operator(entity);
	serialize_access_property(entity);
	if(entity.is_inline())
		writer_.write_key_value_pair("inline", true);
	if(entity.is_const())
		writer_.write_key_value_pair("const", true);
	if(entity.is_volatile())
		writer_.write_key_value_pair("volatile", true);
	if(entity.is_virtual())
		writer_.write_key_value_pair("virtual", true);
	if(entity.is_pure())
		writer_.write_key_value_pair("pure", true);
	if(!entity.defined())
		writer_.write_key_value_pair("defined", false);

	writer_.open_object("return type");
	serialize_type(entity.return_type());
	writer_.close_object();

	serialize_function_parameter_list(entity.parameters());
}

void
semantic_graph_serializer::serialize_conversion_function
(
	const conversion_function& entity
)
{
	serialize_id_attribute(entity);
	serialize_access_property(entity);
	if(entity.is_inline())
		writer_.write_key_value_pair("inline", true);
	if(entity.is_const())
		writer_.write_key_value_pair("const", true);
	if(entity.is_volatile())
		writer_.write_key_value_pair("volatile", true);
	if(entity.is_virtual())
		writer_.write_key_value_pair("virtual", true);
	if(entity.is_pure())
		writer_.write_key_value_pair("pure", true);
	if(!entity.defined())
		writer_.write_key_value_pair("defined", false);

	writer_.open_object("return type");
	serialize_type(entity.return_type());
	writer_.close_object();
}

void
semantic_graph_serializer::serialize_simple_member_function
(
	const simple_member_function& entity
)
{
	serialize_id_attribute(entity);
	serialize_name_property(entity);
	serialize_access_property(entity);

	if(entity.is_inline())
		writer_.write_key_value_pair("inline", true);
	if(entity.variadic())
		writer_.write_key_value_pair("variadic", true);
	if(entity.is_const())
		writer_.write_key_value_pair("const", true);
	if(entity.is_volatile())
		writer_.write_key_value_pair("volatile", true);
	if(entity.is_virtual())
		writer_.write_key_value_pair("virtual", true);
	if(entity.is_pure())
		writer_.write_key_value_pair("pure", true);
	if(!entity.defined())
		writer_.write_key_value_pair("defined", false);

	writer_.open_object("return type");
	serialize_type(entity.return_type());
	writer_.close_object();

	serialize_function_parameter_list(entity.parameters());
}

void
semantic_graph_serializer::serialize_operator_function
(
	const operator_function& entity
)
{
	serialize_id_attribute(entity);
	serialize_overloaded_operator(entity);

	if(entity.is_inline())
		writer_.write_key_value_pair("inline", true);
	if(entity.is_static())
		writer_.write_key_value_pair("static", true);
	if(!entity.defined())
		writer_.write_key_value_pair("defined", false);

	writer_.open_object("return type");
	serialize_type(entity.return_type());
	writer_.close_object();

	serialize_function_parameter_list(entity.parameters());
}

void
semantic_graph_serializer::serialize_simple_function
(
	const simple_function& entity
)
{
	serialize_id_attribute(entity);
	serialize_name_property(entity);

	if(entity.variadic())
		writer_.write_key_value_pair("variadic", true);
	if(entity.is_inline())
		writer_.write_key_value_pair("inline", true);
	if(entity.is_static())
		writer_.write_key_value_pair("static", true);
	if(!entity.defined())
		writer_.write_key_value_pair("defined", false);

	writer_.open_object("return type");
	serialize_type(entity.return_type());
	writer_.close_object();

	serialize_function_parameter_list(entity.parameters());
}

void
semantic_graph_serializer::serialize_function_type
(
	const function_type& entity
)
{
	if(entity.variadic())
		writer_.write_key_value_pair("variadic", true);
	if(entity.const_qualified())
		writer_.write_key_value_pair("const", true);
	if(entity.volatile_qualified())
		writer_.write_key_value_pair("volatile", true);

	writer_.open_object("return type");
	serialize_type(entity.return_type());
	writer_.close_object();

	const std::vector<type_t>& parameter_types = entity.parameter_types();

	writer_.open_array("parameter types");
	for(auto i = parameter_types.begin(); i != parameter_types.end(); ++i)
	{
		const type_t& type = *i;

		writer_.open_object();
		serialize_type(type);
		writer_.close_object();
	}
	writer_.close_array();
}

void
semantic_graph_serializer::serialize_function_parameter_list
(
	const function_parameter_list& entity
)
{
	if(!entity.empty())
	{
		writer_.open_array("parameters");
		for(auto i = entity.begin(); i != entity.end(); ++i)
		{
			writer_.open_object();
			serialize_function_parameter(*i);
			writer_.close_object();
		}
		writer_.close_array();
	}
}

void
semantic_graph_serializer::serialize_function_parameter
(
	const function_parameter& entity
)
{
	if(!entity.name().empty())
		writer_.write_key_value_pair("name", entity.name());
	writer_.open_object("type");
	serialize_type(entity.type());
	writer_.close_object();
}

void
semantic_graph_serializer::serialize_namespace_alias
(
	const namespace_alias& entity
)
{
	serialize_name_property(entity);
	writer_.write_key_value_pair("namespace id", get_id(entity.referred_namespace()));
}

namespace
{

#define EXPRESSION_TYPE(TYPE, STR) \
std::string \
operator()(const TYPE) \
{ \
	return STR; \
}

	struct: scalpel::utility::static_visitor<std::string>
	{
		EXPRESSION_TYPE(prefix_increment_expression, "prefix increment")
		EXPRESSION_TYPE(prefix_decrement_expression, "prefix decrement")
		EXPRESSION_TYPE(indirection_expression, "indirection")
		EXPRESSION_TYPE(pointer_expression, "pointer")
		EXPRESSION_TYPE(negation_expression, "negation")
		EXPRESSION_TYPE(logical_negation_expression, "logical negation")
		EXPRESSION_TYPE(complement_expression, "complement")
		EXPRESSION_TYPE(multiplication_expression, "multiplication")
		EXPRESSION_TYPE(division_expression, "division")
		EXPRESSION_TYPE(modulo_expression, "modulo")
		EXPRESSION_TYPE(addition_expression, "addition")
		EXPRESSION_TYPE(subtraction_expression, "subtraction")
		EXPRESSION_TYPE(left_shift_expression, "left shift")
		EXPRESSION_TYPE(right_shift_expression, "right shift")
		EXPRESSION_TYPE(less_than_expression, "less than")
		EXPRESSION_TYPE(less_than_or_equal_to_expression, "less than or equal to")
		EXPRESSION_TYPE(greater_than_expression, "greater than")
		EXPRESSION_TYPE(greater_than_or_equal_to_expression, "greater than or equal to")
		EXPRESSION_TYPE(equal_to_expression, "equal to")
		EXPRESSION_TYPE(not_equal_to_expression, "not equal to")
		EXPRESSION_TYPE(bitwise_and_expression, "bitwise and")
		EXPRESSION_TYPE(bitwise_exclusive_or_expression, "bitwise exclusive or")
		EXPRESSION_TYPE(bitwise_inclusive_or_expression, "bitwise inclusive or")
		EXPRESSION_TYPE(logical_and_expression, "logical and")
		EXPRESSION_TYPE(logical_or_expression, "logical or")
		EXPRESSION_TYPE(conditional_expression, "conditional")
		EXPRESSION_TYPE(assignment_expression, "assignment")
		EXPRESSION_TYPE(multiplication_assignment_expression, "multiplication assignment")
		EXPRESSION_TYPE(division_assignment_expression, "division assignment")
		EXPRESSION_TYPE(modulo_assignment_expression, "modulo assignment")
		EXPRESSION_TYPE(addition_assignment_expression, "addition assignment")
		EXPRESSION_TYPE(subtraction_assignment_expression, "subtraction assignment")
		EXPRESSION_TYPE(left_shift_assignment_expression, "left shift assignment")
		EXPRESSION_TYPE(right_shift_assignment_expression, "right shift assignment")
		EXPRESSION_TYPE(bitwise_and_assignment_expression, "bitwise and assignment")
		EXPRESSION_TYPE(bitwise_exclusive_or_assignment_expression, "bitwise exclusive or assignment")
		EXPRESSION_TYPE(bitwise_inclusive_or_assignment_expression, "bitwise inclusive or assignment")

		EXPRESSION_TYPE(conversion_to_bool, "conversion to bool")
		EXPRESSION_TYPE(conversion_to_int, "conversion to int")
		EXPRESSION_TYPE(conversion_to_long_int, "conversion to long int")
		EXPRESSION_TYPE(conversion_to_unsigned_int, "conversion to unsigned int")
		EXPRESSION_TYPE(conversion_to_unsigned_long_int, "conversion to unsigned long int")
		EXPRESSION_TYPE(conversion_to_float, "conversion to float")
		EXPRESSION_TYPE(conversion_to_double, "conversion to double")
		EXPRESSION_TYPE(conversion_to_long_double, "conversion to long double")

		EXPRESSION_TYPE(variable*, "variable")
		EXPRESSION_TYPE(enum_constant<int>*, "int enum constant")
		EXPRESSION_TYPE(enum_constant<unsigned int>*, "unsigned int enum constant")
		EXPRESSION_TYPE(enum_constant<long int>*, "long int enum constant")
		EXPRESSION_TYPE(enum_constant<unsigned long int>*, "unsigned long int enum constant")

		EXPRESSION_TYPE(bool, "bool")
		EXPRESSION_TYPE(char, "char")
		EXPRESSION_TYPE(wchar_t, "wchar_t")
		EXPRESSION_TYPE(int, "int")
		EXPRESSION_TYPE(long int, "long int")
		EXPRESSION_TYPE(long long int, "long long int")
		EXPRESSION_TYPE(unsigned int, "unsigned int")
		EXPRESSION_TYPE(unsigned long int, "unsigned long int")
		EXPRESSION_TYPE(unsigned long long int, "unsigned long long int")
		EXPRESSION_TYPE(float, "float")
		EXPRESSION_TYPE(double, "double")
		EXPRESSION_TYPE(long double, "long double")
		EXPRESSION_TYPE(std::string, "string")
		EXPRESSION_TYPE(std::wstring, "wide string")
	} get_expression_type_visitor;

#undef EXPRESSION_TYPE
}



semantic_graph_serializer::serialize_expression_visitor::serialize_expression_visitor
(
	semantic_graph_serializer& serializer
):
	serializer_(serializer),
	output_(serializer_.output_)
{
}

template<typename T>
void
semantic_graph_serializer::serialize_expression_visitor::operator()(const T t)
{
	serializer_.writer_.write_key_value_pair("value", t);
}

template<int Tag>
void
semantic_graph_serializer::serialize_expression_visitor::operator()(const unary_expression<Tag>& operation)
{
	serializer_.writer_.open_object("operand");
	serializer_.serialize_expression(operation.operand());
	serializer_.writer_.close_object();
}

template<int Tag>
void
semantic_graph_serializer::serialize_expression_visitor::operator()(const binary_expression<Tag>& operation)
{
	serializer_.writer_.open_object("left operand");
	serializer_.serialize_expression(operation.left_operand());
	serializer_.writer_.close_object();
	serializer_.writer_.open_object("right operand");
	serializer_.serialize_expression(operation.right_operand());
	serializer_.writer_.close_object();
}

void
semantic_graph_serializer::serialize_expression_visitor::operator()(const conditional_expression& operation)
{
	serializer_.writer_.open_object("condition operand");
	serializer_.serialize_expression(operation.condition_operand());
	serializer_.writer_.close_object();
	serializer_.writer_.open_object("true operand");
	serializer_.serialize_expression(operation.true_operand());
	serializer_.writer_.close_object();
	serializer_.writer_.open_object("false operand");
	serializer_.serialize_expression(operation.false_operand());
	serializer_.writer_.close_object();
}

template<int Tag>
void
semantic_graph_serializer::serialize_expression_visitor::operator()(const conversion<Tag>& conv)
{
	serializer_.writer_.open_object("source value");
	serializer_.serialize_expression(conv.source_value());
	serializer_.writer_.close_object();
}

void
semantic_graph_serializer::serialize_expression_visitor::operator()(variable* const& v)
{
	serializer_.writer_.write_key_value_pair("id", serializer_.get_id(*v));
}

template<typename T>
void
semantic_graph_serializer::serialize_expression_visitor::operator()(enum_constant<T>* const constant)
{
	serializer_.writer_.write_key_value_pair("id", serializer_.get_id(*constant));
}

void
semantic_graph_serializer::serialize_expression_visitor::operator()(const char c)
{
	serializer_.writer_.write_key_value_pair("value", static_cast<int>(c));
}

void
semantic_graph_serializer::serialize_expression_visitor::operator()(const std::string& str)
{
	serializer_.writer_.open_array("bytes");
	for(char c: str)
		serializer_.writer_.write_array_value(static_cast<int>(c) & 0xff);
	serializer_.writer_.close_array();
}

void
semantic_graph_serializer::serialize_expression_visitor::operator()(const std::wstring& str)
{
	serializer_.writer_.open_array("bytes");
	for(wchar_t c: str)
		serializer_.writer_.write_array_value(static_cast<int>(c));
	serializer_.writer_.close_array();
}



void
semantic_graph_serializer::serialize_expression
(
	const semantic_entities::expression_t& entity
)
{
	writer_.write_key_value_pair("type", apply_visitor(get_expression_type_visitor, entity));

	serialize_expression_visitor visitor(*this);
	apply_visitor(visitor, entity);
}



#define SERIALIZE_MEMBER(TYPE, FUNCTION) \
template<> \
void \
semantic_graph_serializer::serialize_member<semantic_entities::TYPE> \
( \
	const semantic_entities::TYPE& entity \
) \
{ \
	FUNCTION(entity); \
}

SERIALIZE_MEMBER(namespace_alias, serialize_namespace_alias)
SERIALIZE_MEMBER(namespace_, serialize_namespace)
SERIALIZE_MEMBER(linked_namespace, serialize_namespace)
SERIALIZE_MEMBER(unnamed_namespace, serialize_unnamed_namespace)
SERIALIZE_MEMBER(linked_unnamed_namespace, serialize_unnamed_namespace)
SERIALIZE_MEMBER(class_, serialize_class)
SERIALIZE_MEMBER(member_class, serialize_class)
SERIALIZE_MEMBER(union_, serialize_class)
SERIALIZE_MEMBER(member_union, serialize_class)
SERIALIZE_MEMBER(anonymous_union, serialize_class)
SERIALIZE_MEMBER(anonymous_member_union, serialize_class)
SERIALIZE_MEMBER(enum_t, serialize_enum)
SERIALIZE_MEMBER(member_enum_t, serialize_enum)
SERIALIZE_MEMBER(typedef_, serialize_typedef)
SERIALIZE_MEMBER(member_typedef, serialize_typedef)
SERIALIZE_MEMBER(constructor, serialize_constructor)
SERIALIZE_MEMBER(destructor, serialize_destructor)
SERIALIZE_MEMBER(operator_member_function, serialize_operator_member_function)
SERIALIZE_MEMBER(conversion_function, serialize_conversion_function)
SERIALIZE_MEMBER(simple_member_function, serialize_simple_member_function)
SERIALIZE_MEMBER(operator_function, serialize_operator_function)
SERIALIZE_MEMBER(simple_function, serialize_simple_function)
SERIALIZE_MEMBER(variable, serialize_variable)
SERIALIZE_MEMBER(member_variable, serialize_variable)
SERIALIZE_MEMBER(static_member_variable, serialize_variable)
SERIALIZE_MEMBER(bit_field, serialize_variable)

#undef SERIALIZE_MEMBER



std::string
semantic_graph_serializer::overloadable_operator_to_string(const semantic_entities::overloadable_operator op)
{
	switch(op)
	{
		case semantic_entities::overloadable_operator::NEW:
			return "new";
		case semantic_entities::overloadable_operator::NEW_ARRAY:
			return "new[]";
		case semantic_entities::overloadable_operator::DELETE:
			return "delete";
		case semantic_entities::overloadable_operator::DELETE_ARRAY:
			return "delete[]";
		case semantic_entities::overloadable_operator::DOUBLE_RIGHT_ANGLE_BRACKET_EQUAL:
			return ">>=";
		case semantic_entities::overloadable_operator::DOUBLE_LEFT_ANGLE_BRACKET_EQUAL:
			return "<<=";
		case semantic_entities::overloadable_operator::ARROW_ASTERISK:
			return "->*";
		case semantic_entities::overloadable_operator::PLUS_EQUAL:
			return "+=";
		case semantic_entities::overloadable_operator::MINUS_EQUAL:
			return "-=";
		case semantic_entities::overloadable_operator::ASTERISK_EQUAL:
			return "*=";
		case semantic_entities::overloadable_operator::SLASH_EQUAL:
			return "/=";
		case semantic_entities::overloadable_operator::PERCENT_EQUAL:
			return "%=";
		case semantic_entities::overloadable_operator::CIRCUMFLEX_EQUAL:
			return "^=";
		case semantic_entities::overloadable_operator::AMPERSAND_EQUAL:
			return "&=";
		case semantic_entities::overloadable_operator::PIPE_EQUAL:
			return "|=";
		case semantic_entities::overloadable_operator::DOUBLE_LEFT_ANGLE_BRACKET:
			return "<<";
		case semantic_entities::overloadable_operator::DOUBLE_RIGHT_ANGLE_BRACKET:
			return ">>";
		case semantic_entities::overloadable_operator::DOUBLE_EQUAL:
			return "==";
		case semantic_entities::overloadable_operator::EXCLAMATION_EQUAL:
			return "!=";
		case semantic_entities::overloadable_operator::LEFT_ANGLE_BRACKET_EQUAL:
			return "<=";
		case semantic_entities::overloadable_operator::RIGHT_ANGLE_BRACKET_EQUAL:
			return ">=";
		case semantic_entities::overloadable_operator::DOUBLE_AMPERSAND:
			return "&&";
		case semantic_entities::overloadable_operator::DOUBLE_PIPE:
			return "||";
		case semantic_entities::overloadable_operator::DOUBLE_PLUS:
			return "++";
		case semantic_entities::overloadable_operator::DOUBLE_MINUS:
			return "--";
		case semantic_entities::overloadable_operator::ARROW:
			return "->";
		case semantic_entities::overloadable_operator::ROUND_BRACKETS:
			return "()";
		case semantic_entities::overloadable_operator::SQUARE_BRACKETS:
			return "[]";
		case semantic_entities::overloadable_operator::COMMA:
			return ",";
		case semantic_entities::overloadable_operator::PLUS:
			return "+";
		case semantic_entities::overloadable_operator::MINUS:
			return "-";
		case semantic_entities::overloadable_operator::ASTERISK:
			return "*";
		case semantic_entities::overloadable_operator::SLASH:
			return "/";
		case semantic_entities::overloadable_operator::PERCENT:
			return "%";
		case semantic_entities::overloadable_operator::CIRCUMFLEX:
			return "^";
		case semantic_entities::overloadable_operator::AMPERSAND:
			return "&";
		case semantic_entities::overloadable_operator::PIPE:
			return "|";
		case semantic_entities::overloadable_operator::TILDE:
			return "~";
		case semantic_entities::overloadable_operator::EXCLAMATION:
			return "!";
		case semantic_entities::overloadable_operator::EQUAL:
			return "=";
		case semantic_entities::overloadable_operator::LEFT_ANGLE_BRACKET:
			return "<";
		case semantic_entities::overloadable_operator::RIGHT_ANGLE_BRACKET:
			return ">";
	}

	assert(false);
}

void
semantic_graph_serializer::serialize_class_id_attribute
(
	const scalpel::cpp::semantic_entities::class_ptr_variant& entity
)
{
	if(const class_* const* opt = scalpel::utility::get<class_*>(&entity))
		writer_.write_key_value_pair("class id", get_id(**opt));
	else if(const member_class* const* opt = scalpel::utility::get<member_class*>(&entity))
		writer_.write_key_value_pair("member class id", get_id(**opt));
}



#define ENTITY_ID_MAP_OF_TYPE(ENTITY_TYPE, VARIABLE) \
template<> \
typename entity_id_map<ENTITY_TYPE>::type& \
semantic_graph_serializer::entity_id_map_of_type<ENTITY_TYPE>() \
{ \
	return VARIABLE; \
} \
 \
template<> \
const typename entity_id_map<ENTITY_TYPE>::type& \
semantic_graph_serializer::entity_id_map_of_type<ENTITY_TYPE>() const \
{ \
	return VARIABLE; \
}

ENTITY_ID_MAP_OF_TYPE(namespace_, namespace_id_map_)
ENTITY_ID_MAP_OF_TYPE(linked_namespace, linked_namespace_id_map_)
ENTITY_ID_MAP_OF_TYPE(unnamed_namespace, unnamed_namespace_id_map_)
ENTITY_ID_MAP_OF_TYPE(linked_unnamed_namespace, linked_unnamed_namespace_id_map_)
ENTITY_ID_MAP_OF_TYPE(class_, class_id_map_)
ENTITY_ID_MAP_OF_TYPE(member_class, member_class_id_map_)
ENTITY_ID_MAP_OF_TYPE(union_, union_id_map_)
ENTITY_ID_MAP_OF_TYPE(member_union, member_union_id_map_)
ENTITY_ID_MAP_OF_TYPE(anonymous_union, anonymous_union_id_map_)
ENTITY_ID_MAP_OF_TYPE(anonymous_member_union, anonymous_member_union_id_map_)
ENTITY_ID_MAP_OF_TYPE(enum_t, enum_id_map_)
ENTITY_ID_MAP_OF_TYPE(member_enum_t, member_enum_id_map_)
ENTITY_ID_MAP_OF_TYPE(typedef_, typedef_id_map_)
ENTITY_ID_MAP_OF_TYPE(member_typedef, member_typedef_id_map_)
ENTITY_ID_MAP_OF_TYPE(operator_member_function, operator_member_function_id_map_)
ENTITY_ID_MAP_OF_TYPE(conversion_function, conversion_function_id_map_)
ENTITY_ID_MAP_OF_TYPE(simple_member_function, simple_member_function_id_map_)
ENTITY_ID_MAP_OF_TYPE(operator_function, operator_function_id_map_)
ENTITY_ID_MAP_OF_TYPE(simple_function, simple_function_id_map_)
ENTITY_ID_MAP_OF_TYPE(variable, variable_id_map_)
ENTITY_ID_MAP_OF_TYPE(member_variable, member_variable_id_map_)
ENTITY_ID_MAP_OF_TYPE(static_member_variable, static_member_variable_id_map_)
ENTITY_ID_MAP_OF_TYPE(bit_field, bit_field_id_map_)
ENTITY_ID_MAP_OF_TYPE(enum_constant<int>, int_enum_constant_id_map_)
ENTITY_ID_MAP_OF_TYPE(enum_constant<unsigned int>, unsigned_int_enum_constant_id_map_)
ENTITY_ID_MAP_OF_TYPE(enum_constant<long int>, long_int_enum_constant_id_map_)
ENTITY_ID_MAP_OF_TYPE(enum_constant<unsigned long int>, unsigned_long_int_enum_constant_id_map_)

#undef ENTITY_ID_MAP_OF_TYPE



void
serialize_semantic_graph
(
	const semantic_graph& graph,
	std::ostream& output
)
{
	semantic_graph_serializer serializer(output);
	serializer(graph);
}

void
serialize_semantic_graph
(
	const linked_semantic_graph& graph,
	std::ostream& output
)
{
	semantic_graph_serializer serializer(output);
	serializer(graph);
}

} //namespace cpp2xml

