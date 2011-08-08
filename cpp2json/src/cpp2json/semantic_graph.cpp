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

namespace cpp2json
{

using namespace detail;

semantic_graph_serializer::semantic_graph_serializer(std::ostream& output):
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
	writer_(serializer_.writer_)
{
}

void
semantic_graph_serializer::serialize_type_visitor::operator()(const fundamental_type& type)
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

	writer_.write_key_value_pair("fundamental type", fundamental_types_map[type]);
}

void
semantic_graph_serializer::serialize_type_visitor::operator()(const function_type& type)
{
	writer_.open_object("function type");

	if(type.variadic())
		writer_.write_key_value_pair("variadic", true);
	if(type.const_qualified())
		writer_.write_key_value_pair("const", true);
	if(type.volatile_qualified())
		writer_.write_key_value_pair("volatile", true);

	writer_.open_object("return type");
	serializer_.serialize_type(type.return_type());
	writer_.close_object();

	writer_.open_array("parameter types");
	const std::vector<type_t>& parameter_types = type.parameter_types();
	for(const type_t& type: parameter_types)
	{
		writer_.open_object();
		serializer_.serialize_type(type);
		writer_.close_object();
	}
	writer_.close_array();

	writer_.close_object();
}

void
semantic_graph_serializer::serialize_type_visitor::operator()(const cv_qualified_type& type)
{
	writer_.open_object("cv-qualified type");

	if(type.const_qualified())
		writer_.write_key_value_pair("const", true);
	if(type.volatile_qualified())
		writer_.write_key_value_pair("volatile", true);

	writer_.open_object("type");
	serializer_.serialize_type(type.qualified_type());
	writer_.close_object();

	writer_.close_object();
}

void
semantic_graph_serializer::serialize_type_visitor::operator()(const pointer& type)
{
	writer_.open_object("pointer");

	writer_.open_object("type");
	serializer_.serialize_type(type.qualified_type());
	writer_.close_object();

	writer_.close_object();
}

void
semantic_graph_serializer::serialize_type_visitor::operator()(const pointer_to_member& type)
{
	writer_.open_object("pointer to member");

	serializer_.serialize_class_id_attribute(type.parent_class());

	writer_.open_object("type");
	serializer_.serialize_type(type.qualified_type());
	writer_.close_object();

	writer_.close_object();
}

void
semantic_graph_serializer::serialize_type_visitor::operator()(const reference& type)
{
	writer_.open_object("reference");

	writer_.open_object("type");
	serializer_.serialize_type(type.qualified_type());
	writer_.close_object();

	writer_.close_object();
}

void
semantic_graph_serializer::serialize_type_visitor::operator()(const array& type)
{
	writer_.open_object("array");

	writer_.write_key_value_pair("size", type.size());

	writer_.open_object("type");
	serializer_.serialize_type(type.qualified_type());
	writer_.close_object();

	writer_.close_object();
}

void
semantic_graph_serializer::serialize_type_visitor::operator()(const class_* type)
{
	writer_.write_key_value_pair("class", serializer_.get_id_str(*type));
}

void
semantic_graph_serializer::serialize_type_visitor::operator()(const member_class* type)
{
	writer_.write_key_value_pair("member class", serializer_.get_id_str(*type));
}

void
semantic_graph_serializer::serialize_type_visitor::operator()(const union_* type)
{
	writer_.write_key_value_pair("union", serializer_.get_id_str(*type));
}

void
semantic_graph_serializer::serialize_type_visitor::operator()(const member_union* type)
{
	writer_.write_key_value_pair("member union", serializer_.get_id_str(*type));
}

void
semantic_graph_serializer::serialize_type_visitor::operator()(const anonymous_union* type)
{
	writer_.write_key_value_pair("anonymous union", serializer_.get_id_str(*type));
}

void
semantic_graph_serializer::serialize_type_visitor::operator()(const anonymous_member_union* type)
{
	writer_.write_key_value_pair("anonymous member union", serializer_.get_id_str(*type));
}

void
semantic_graph_serializer::serialize_type_visitor::operator()(const enum_t* type)
{
	writer_.write_key_value_pair("enum", serializer_.get_id_str(*type));
}

void
semantic_graph_serializer::serialize_type_visitor::operator()(const member_enum_t* type)
{
	writer_.write_key_value_pair("member enum", serializer_.get_id_str(*type));
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
	writer_.write_key_value_pair("namespace id", get_id_str(entity.referred_namespace()));
}

namespace
{
	template<class Expression>
	struct expression_to_string;

#define EXPRESSION_TO_STRING(EXPRESSION, STR) \
template<> \
struct expression_to_string<EXPRESSION> \
{ \
	static constexpr const char* value = STR; \
};

	EXPRESSION_TO_STRING(prefix_increment_expression, "prefix increment")
	EXPRESSION_TO_STRING(prefix_decrement_expression, "prefix decrement")
	EXPRESSION_TO_STRING(indirection_expression, "indirection")
	EXPRESSION_TO_STRING(pointer_expression, "pointer")
	EXPRESSION_TO_STRING(negation_expression, "negation")
	EXPRESSION_TO_STRING(logical_negation_expression, "logical negation")
	EXPRESSION_TO_STRING(complement_expression, "complement")
	EXPRESSION_TO_STRING(multiplication_expression, "multiplication")
	EXPRESSION_TO_STRING(division_expression, "division")
	EXPRESSION_TO_STRING(modulo_expression, "modulo")
	EXPRESSION_TO_STRING(addition_expression, "addition")
	EXPRESSION_TO_STRING(subtraction_expression, "subtraction")
	EXPRESSION_TO_STRING(left_shift_expression, "left shift")
	EXPRESSION_TO_STRING(right_shift_expression, "right shift")
	EXPRESSION_TO_STRING(less_than_expression, "less than")
	EXPRESSION_TO_STRING(less_than_or_equal_to_expression, "less than or equal to")
	EXPRESSION_TO_STRING(greater_than_expression, "greater than")
	EXPRESSION_TO_STRING(greater_than_or_equal_to_expression, "greater than or equal to")
	EXPRESSION_TO_STRING(equal_to_expression, "equal to")
	EXPRESSION_TO_STRING(not_equal_to_expression, "not equal to")
	EXPRESSION_TO_STRING(bitwise_and_expression, "bitwise and")
	EXPRESSION_TO_STRING(bitwise_exclusive_or_expression, "bitwise exclusive or")
	EXPRESSION_TO_STRING(bitwise_inclusive_or_expression, "bitwise inclusive or")
	EXPRESSION_TO_STRING(logical_and_expression, "logical and")
	EXPRESSION_TO_STRING(logical_or_expression, "logical or")
	EXPRESSION_TO_STRING(conditional_expression, "conditional")
	EXPRESSION_TO_STRING(assignment_expression, "assignment")
	EXPRESSION_TO_STRING(multiplication_assignment_expression, "multiplication assignment")
	EXPRESSION_TO_STRING(division_assignment_expression, "division assignment")
	EXPRESSION_TO_STRING(modulo_assignment_expression, "modulo assignment")
	EXPRESSION_TO_STRING(addition_assignment_expression, "addition assignment")
	EXPRESSION_TO_STRING(subtraction_assignment_expression, "subtraction assignment")
	EXPRESSION_TO_STRING(left_shift_assignment_expression, "left shift assignment")
	EXPRESSION_TO_STRING(right_shift_assignment_expression, "right shift assignment")
	EXPRESSION_TO_STRING(bitwise_and_assignment_expression, "bitwise and assignment")
	EXPRESSION_TO_STRING(bitwise_exclusive_or_assignment_expression, "bitwise exclusive or assignment")
	EXPRESSION_TO_STRING(bitwise_inclusive_or_assignment_expression, "bitwise inclusive or assignment")

	EXPRESSION_TO_STRING(conversion_to_bool, "conversion to bool")
	EXPRESSION_TO_STRING(conversion_to_int, "conversion to int")
	EXPRESSION_TO_STRING(conversion_to_long_int, "conversion to long int")
	EXPRESSION_TO_STRING(conversion_to_unsigned_int, "conversion to unsigned int")
	EXPRESSION_TO_STRING(conversion_to_unsigned_long_int, "conversion to unsigned long int")
	EXPRESSION_TO_STRING(conversion_to_float, "conversion to float")
	EXPRESSION_TO_STRING(conversion_to_double, "conversion to double")
	EXPRESSION_TO_STRING(conversion_to_long_double, "conversion to long double")

	EXPRESSION_TO_STRING(variable*, "variable")
	EXPRESSION_TO_STRING(enum_constant<int>*, "int enum constant")
	EXPRESSION_TO_STRING(enum_constant<unsigned int>*, "unsigned int enum constant")
	EXPRESSION_TO_STRING(enum_constant<long int>*, "long int enum constant")
	EXPRESSION_TO_STRING(enum_constant<unsigned long int>*, "unsigned long int enum constant")

	EXPRESSION_TO_STRING(bool, "bool")
	EXPRESSION_TO_STRING(char, "char")
	EXPRESSION_TO_STRING(wchar_t, "wchar_t")
	EXPRESSION_TO_STRING(int, "int")
	EXPRESSION_TO_STRING(long int, "long int")
	EXPRESSION_TO_STRING(long long int, "long long int")
	EXPRESSION_TO_STRING(unsigned int, "unsigned int")
	EXPRESSION_TO_STRING(unsigned long int, "unsigned long int")
	EXPRESSION_TO_STRING(unsigned long long int, "unsigned long long int")
	EXPRESSION_TO_STRING(float, "float")
	EXPRESSION_TO_STRING(double, "double")
	EXPRESSION_TO_STRING(long double, "long double")
	EXPRESSION_TO_STRING(std::string, "string")
	EXPRESSION_TO_STRING(std::wstring, "wide string")

#undef EXPRESSION_TO_STRING
}



semantic_graph_serializer::serialize_expression_visitor::serialize_expression_visitor
(
	semantic_graph_serializer& serializer
):
	serializer_(serializer)
{
}

template<typename T>
void
semantic_graph_serializer::serialize_expression_visitor::operator()(const T expr)
{
	serializer_.writer_.write_key_value_pair(expression_to_string<T>::value, expr);
}

template<int Tag>
void
semantic_graph_serializer::serialize_expression_visitor::operator()(const unary_expression<Tag>& operation)
{
	serializer_.writer_.open_object(expression_to_string<unary_expression<Tag>>::value);

	serializer_.writer_.open_object("operand");
	serializer_.serialize_expression(operation.operand());
	serializer_.writer_.close_object();

	serializer_.writer_.close_object();
}

template<int Tag>
void
semantic_graph_serializer::serialize_expression_visitor::operator()(const binary_expression<Tag>& operation)
{
	serializer_.writer_.open_object(expression_to_string<binary_expression<Tag>>::value);

	serializer_.writer_.open_object("left operand");
	serializer_.serialize_expression(operation.left_operand());
	serializer_.writer_.close_object();
	serializer_.writer_.open_object("right operand");
	serializer_.serialize_expression(operation.right_operand());
	serializer_.writer_.close_object();

	serializer_.writer_.close_object();
}

void
semantic_graph_serializer::serialize_expression_visitor::operator()(const conditional_expression& operation)
{
	serializer_.writer_.open_object(expression_to_string<conditional_expression>::value);

	serializer_.writer_.open_object("condition operand");
	serializer_.serialize_expression(operation.condition_operand());
	serializer_.writer_.close_object();
	serializer_.writer_.open_object("true operand");
	serializer_.serialize_expression(operation.true_operand());
	serializer_.writer_.close_object();
	serializer_.writer_.open_object("false operand");
	serializer_.serialize_expression(operation.false_operand());
	serializer_.writer_.close_object();

	serializer_.writer_.close_object();
}

template<int Tag>
void
semantic_graph_serializer::serialize_expression_visitor::operator()(const conversion<Tag>& conv)
{
	serializer_.writer_.open_object(expression_to_string<conversion<Tag>>::value);

	serializer_.writer_.open_object("source value");
	serializer_.serialize_expression(conv.source_value());
	serializer_.writer_.close_object();

	serializer_.writer_.close_object();
}

void
semantic_graph_serializer::serialize_expression_visitor::operator()(variable* const& v)
{
	serializer_.writer_.write_key_value_pair(expression_to_string<variable*>::value, serializer_.get_id_str(*v));
}

template<typename T>
void
semantic_graph_serializer::serialize_expression_visitor::operator()(enum_constant<T>* const constant)
{
	serializer_.writer_.write_key_value_pair(expression_to_string<enum_constant<T>*>::value, serializer_.get_id_str(*constant));
}

void
semantic_graph_serializer::serialize_expression_visitor::operator()(const char c)
{
	serializer_.writer_.write_key_value_pair(expression_to_string<char>::value, static_cast<int>(c));
}

void
semantic_graph_serializer::serialize_expression_visitor::operator()(const std::string& str)
{
	serializer_.writer_.open_object(expression_to_string<std::string>::value);

	for(char c: str)
		serializer_.writer_.write_array_value(static_cast<int>(c) & 0xff);

	serializer_.writer_.close_object();
}

void
semantic_graph_serializer::serialize_expression_visitor::operator()(const std::wstring& str)
{
	serializer_.writer_.open_object(expression_to_string<std::wstring>::value);

	for(wchar_t c: str)
		serializer_.writer_.write_array_value(static_cast<int>(c));

	serializer_.writer_.close_object();
}



void
semantic_graph_serializer::serialize_expression
(
	const semantic_entities::expression_t& entity
)
{
	//writer_.write_key_value_pair("type", apply_visitor(get_expression_type_visitor, entity));

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
		writer_.write_key_value_pair("class id", get_id_str(**opt));
	else if(const member_class* const* opt = scalpel::utility::get<member_class*>(&entity))
		writer_.write_key_value_pair("member class id", get_id_str(**opt));
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

} //namespace cpp2json

