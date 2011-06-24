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
	output_(output)
{
}

void
semantic_graph_serializer::operator()(const namespace_& entity)
{
	set_ids(entity);
	serialize_namespace(entity);
}

void
semantic_graph_serializer::operator()(const linked_namespace& entity)
{
	set_ids(entity);
	serialize_namespace(entity);
}



semantic_graph_serializer::serialize_type_visitor::serialize_type_visitor
(
	semantic_graph_serializer& serializer,
	const unsigned int indent_level
):
	serializer_(serializer),
	output_(serializer_.output_),
	indent_level_(indent_level)
{
}

void
semantic_graph_serializer::serialize_type_visitor::operator()(const fundamental_type& type)
{
	output_ << indent(indent_level_) << "<fundamental_type type=\"";
	serializer_.serialize_fundamental_type(type);
	output_ << "\"/>\n";
}

void
semantic_graph_serializer::serialize_type_visitor::operator()(const function_type& type)
{
	serializer_.serialize_function_type(type, indent_level_);
}

void
semantic_graph_serializer::serialize_type_visitor::operator()(const cv_qualified_type& type)
{
	output_ << indent(indent_level_) << "<cv_qualified_type";
	if(type.const_qualified())
		output_ << " const=\"true\"";
	if(type.volatile_qualified())
		output_ << " volatile=\"true\"";
	output_ << ">\n";
	serializer_.serialize_type((type).qualified_type(), indent_level_ + 1);
	output_ << indent(indent_level_) << "</cv_qualified_type>\n";
}

void
semantic_graph_serializer::serialize_type_visitor::operator()(const pointer& type)
{
	output_ << indent(indent_level_) << "<pointer>\n";
	serializer_.serialize_type((type).qualified_type(), indent_level_ + 1);
	output_ << indent(indent_level_) << "</pointer>\n";
}

void
semantic_graph_serializer::serialize_type_visitor::operator()(const pointer_to_member& type)
{
	output_ << indent(indent_level_) << "<pointer_to_member ";
	serializer_.serialize_class_id_attribute(type.parent_class());
	output_ << ">\n";
	serializer_.serialize_type((type).qualified_type(), indent_level_ + 1);
	output_ << indent(indent_level_) << "</pointer_to_member>\n";
}

void
semantic_graph_serializer::serialize_type_visitor::operator()(const reference& type)
{
	output_ << indent(indent_level_) << "<reference>\n";
	serializer_.serialize_type((type).qualified_type(), indent_level_ + 1);
	output_ << indent(indent_level_) << "</reference>\n";
}

void
semantic_graph_serializer::serialize_type_visitor::operator()(const array& type)
{
	output_ << indent(indent_level_) << "<array size=\"" << type.size() << "\">\n";
	serializer_.serialize_type(type.qualified_type(), indent_level_ + 1);
	output_ << indent(indent_level_) << "</array>\n";
}

void
semantic_graph_serializer::serialize_type_visitor::operator()(const class_* type)
{
	output_ << indent(indent_level_) << "<class id=\"" << serializer_.get_id(*type) << "\"/>\n";
}

void
semantic_graph_serializer::serialize_type_visitor::operator()(const member_class* type)
{
	output_ << indent(indent_level_) << "<member_class id=\"" << serializer_.get_id(*type) << "\"/>\n";
}

void
semantic_graph_serializer::serialize_type_visitor::operator()(const union_* type)
{
	output_ << indent(indent_level_) << "<union id=\"" << serializer_.get_id(*type) << "\"/>\n";
}

void
semantic_graph_serializer::serialize_type_visitor::operator()(const member_union* type)
{
	output_ << indent(indent_level_) << "<member_union id=\"" << serializer_.get_id(*type) << "\"/>\n";
}

void
semantic_graph_serializer::serialize_type_visitor::operator()(const anonymous_union* type)
{
	output_ << indent(indent_level_) << "<anonymous_union id=\"" << serializer_.get_id(*type) << "\"/>\n";
}

void
semantic_graph_serializer::serialize_type_visitor::operator()(const anonymous_member_union* type)
{
	output_ << indent(indent_level_) << "<anonymous_member_union id=\"" << serializer_.get_id(*type) << "\"/>\n";
}

void
semantic_graph_serializer::serialize_type_visitor::operator()(const enum_* type)
{
	output_ << indent(indent_level_) << "<enum id=\"" << serializer_.get_id(*type) << "\"/>\n";
}

void
semantic_graph_serializer::serialize_type_visitor::operator()(const member_enum* type)
{
	output_ << indent(indent_level_) << "<member_enum id=\"" << serializer_.get_id(*type) << "\"/>\n";
}

void
semantic_graph_serializer::serialize_type
(
	const semantic_entities::type_variant& n,
	const unsigned int indent_level
)
{
	serialize_type_visitor visitor(*this, indent_level);
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

	output_ << fundamental_types_map[type];
}

void
semantic_graph_serializer::serialize_base_class
(
	const base_class& entity,
	const unsigned int indent_level
)
{
	output_ << indent(indent_level) << "<base_class ";
	serialize_class_id_attribute(entity.base());
	output_ << attribute(entity.access());
	if(entity.is_virtual())
		output_ << " virtual=\"true\"";
	output_ << "/>\n";
}

void
semantic_graph_serializer::serialize_constructor
(
	const constructor& entity,
	const unsigned int indent_level
)
{
	output_ << indent(indent_level) << "<constructor";
	output_ << attribute(entity.access());
	if(entity.variadic())
		output_ << " variadic=\"true\"";
	if(entity.is_inline())
		output_ << " inline=\"true\"";
	if(entity.is_explicit())
		output_ << " explicit=\"true\"";
	if(!entity.defined())
		output_ << " defined=\"false\"";
	output_ << ">\n";

	serialize_function_parameter_list(entity.parameters(), indent_level + 1);

	output_ << indent(indent_level) << "</constructor>\n";
}

void
semantic_graph_serializer::serialize_destructor
(
	const destructor& entity,
	const unsigned int indent_level
)
{
	output_ << indent(indent_level) << "<destructor";
	output_ << attribute(entity.access());
	if(entity.is_inline())
		output_ << " inline=\"true\"";
	if(entity.is_virtual())
		output_ << " virtual=\"true\"";
	if(entity.is_pure())
		output_ << " pure=\"true\"";
	if(!entity.defined())
		output_ << " defined=\"false\"";
	output_ << ">\n";

	output_ << indent(indent_level) << "</destructor>\n";
}

void
semantic_graph_serializer::serialize_operator_member_function
(
	const operator_member_function& entity,
	const unsigned int indent_level
)
{
	output_ << indent(indent_level) << "<operator_member_function";
	output_ << " " << id_attribute_to_string(entity);
	output_ << attribute(entity.overloaded_operator());
	output_ << attribute(entity.access());
	if(entity.is_inline())
		output_ << " inline=\"true\"";
	if(entity.is_const())
		output_ << " const=\"true\"";
	if(entity.is_volatile())
		output_ << " volatile=\"true\"";
	if(entity.is_virtual())
		output_ << " virtual=\"true\"";
	if(entity.is_pure())
		output_ << " pure=\"true\"";
	if(!entity.defined())
		output_ << " defined=\"false\"";
	output_ << ">\n";

	output_ << indent(indent_level + 1) << "<return_type>\n";
	serialize_type(entity.return_type(), indent_level + 2);
	output_ << indent(indent_level + 1) << "</return_type>\n";

	serialize_function_parameter_list(entity.parameters(), indent_level + 1);

	output_ << indent(indent_level) << "</operator_member_function>\n";
}

void
semantic_graph_serializer::serialize_conversion_function
(
	const conversion_function& entity,
	const unsigned int indent_level
)
{
	output_ << indent(indent_level) << "<conversion_function";
	output_ << " " << id_attribute_to_string(entity);
	output_ << attribute(entity.access());
	if(entity.is_inline())
		output_ << " inline=\"true\"";
	if(entity.is_const())
		output_ << " const=\"true\"";
	if(entity.is_volatile())
		output_ << " volatile=\"true\"";
	if(entity.is_virtual())
		output_ << " virtual=\"true\"";
	if(entity.is_pure())
		output_ << " pure=\"true\"";
	if(!entity.defined())
		output_ << " defined=\"false\"";
	output_ << ">\n";

	output_ << indent(indent_level + 1) << "<return_type>\n";
	serialize_type(entity.return_type(), indent_level + 2);
	output_ << indent(indent_level + 1) << "</return_type>\n";

	output_ << indent(indent_level) << "</conversion_function>\n";
}

void
semantic_graph_serializer::serialize_simple_member_function
(
	const simple_member_function& entity,
	const unsigned int indent_level
)
{
	output_ << indent(indent_level) << "<simple_member_function";
	output_ << " " << id_attribute_to_string(entity);
	output_ << " name=\"" << entity.name() << "\"";
	output_ << attribute(entity.access());
	if(entity.variadic())
		output_ << " variadic=\"true\"";
	if(entity.is_inline())
		output_ << " inline=\"true\"";
	if(entity.is_static())
		output_ << " static=\"true\"";
	if(entity.is_const())
		output_ << " const=\"true\"";
	if(entity.is_volatile())
		output_ << " volatile=\"true\"";
	if(entity.is_virtual())
		output_ << " virtual=\"true\"";
	if(entity.is_pure())
		output_ << " pure=\"true\"";
	if(!entity.defined())
		output_ << " defined=\"false\"";
	output_ << ">\n";

	output_ << indent(indent_level + 1) << "<return_type>\n";
	serialize_type(entity.return_type(), indent_level + 2);
	output_ << indent(indent_level + 1) << "</return_type>\n";

	serialize_function_parameter_list(entity.parameters(), indent_level + 1);

	output_ << indent(indent_level) << "</simple_member_function>\n";
}

void
semantic_graph_serializer::serialize_operator_function
(
	const operator_function& entity,
	const unsigned int indent_level
)
{
	output_ << indent(indent_level) << "<operator_function";
	output_ << " " << id_attribute_to_string(entity);
	output_ << attribute(entity.overloaded_operator());
	if(entity.is_inline())
		output_ << " inline=\"true\"";
	if(entity.is_static())
		output_ << " static=\"true\"";
	if(!entity.defined())
		output_ << " defined=\"false\"";
	output_ << ">\n";

	output_ << indent(indent_level + 1) << "<return_type>\n";
	serialize_type(entity.return_type(), indent_level + 2);
	output_ << indent(indent_level + 1) << "</return_type>\n";

	serialize_function_parameter_list(entity.parameters(), indent_level + 1);

	output_ << indent(indent_level) << "</operator_function>\n";
}

void
semantic_graph_serializer::serialize_simple_function
(
	const simple_function& entity,
	const unsigned int indent_level
)
{
	output_ << indent(indent_level) << "<simple_function";
	output_ << " " << id_attribute_to_string(entity);
	output_ << " name=\"" << entity.name() << "\"";
	if(entity.variadic())
		output_ << " variadic=\"true\"";
	if(entity.is_static())
		output_ << " static=\"true\"";
	if(entity.is_inline())
		output_ << " inline=\"true\"";
	if(!entity.defined())
		output_ << " defined=\"false\"";
	output_ << ">\n";

	output_ << indent(indent_level + 1) << "<return_type>\n";
	serialize_type(entity.return_type(), indent_level + 2);
	output_ << indent(indent_level + 1) << "</return_type>\n";

	serialize_function_parameter_list(entity.parameters(), indent_level + 1);

	output_ << indent(indent_level) << "</simple_function>\n";
}

void
semantic_graph_serializer::serialize_function_type
(
	const function_type& entity,
	const unsigned int indent_level
)
{
	output_ << indent(indent_level) << "<function_type";
	if(entity.variadic())
		output_ << " variadic=\"true\"";
	if(entity.const_qualified())
		output_ << " const=\"true\"";
	if(entity.volatile_qualified())
		output_ << " volatile=\"true\"";
	output_ << ">\n";

	output_ << indent(indent_level + 1) << "<return_type>\n";
	serialize_type(entity.return_type(), indent_level + 2);
	output_ << indent(indent_level + 1) << "</return_type>\n";

	const std::vector<type_variant>& parameter_types = entity.parameter_types();
	output_ << indent(indent_level + 1) << "<parameter_types>\n";
	for(auto i = parameter_types.begin(); i != parameter_types.end(); ++i)
	{
		const type_variant& type = *i;
		serialize_type(type, indent_level + 2);
	}
	output_ << indent(indent_level + 1) << "</parameter_types>\n";

	output_ << indent(indent_level) << "</function_type>\n";
}

void
semantic_graph_serializer::serialize_function_parameter_list
(
	const function_parameter_list& entity,
	const unsigned int indent_level
)
{
	if(!entity.empty())
	{
		output_ << indent(indent_level) << "<parameters>\n";
		for(auto i = entity.begin(); i != entity.end(); ++i)
		{
			serialize_function_parameter(*i, indent_level + 1);
		}
		output_ << indent(indent_level) << "</parameters>\n";
	}
}

void
semantic_graph_serializer::serialize_function_parameter
(
	const function_parameter& entity,
	const unsigned int indent_level
)
{
	output_ << indent(indent_level) << "<parameter";
	if(!entity.name().empty())
		output_ << " name=\"" << entity.name() << "\"";
	output_ << ">\n";
	output_ << indent(indent_level + 1) << "<type>\n";
	serialize_type(entity.type(), indent_level + 2);
	output_ << indent(indent_level + 1) << "</type>\n";
	output_ << indent(indent_level) << "</parameter>\n";
}

void
semantic_graph_serializer::serialize_namespace_alias
(
	const namespace_alias& entity,
	const unsigned int indent_level
)
{
	output_ << indent(indent_level) << "<namespace_alias";
	output_ << " name=\"" << entity.name() << "\"";
	output_ << " namespace_id=\"" << get_id(entity.referred_namespace()) << "\"";
	output_ << "/>\n";
}

namespace
{
#define SIMPLE_TYPE(TYPE) \
std::string \
operator()(const TYPE) \
{ \
	return #TYPE; \
}

#define EXPRESSION_TYPE(TYPE) \
std::string \
operator()(const TYPE##_expression) \
{ \
	return #TYPE; \
}

	struct: scalpel::utility::static_visitor<std::string>
	{
		EXPRESSION_TYPE(multiplication)
		EXPRESSION_TYPE(division)
		EXPRESSION_TYPE(modulo)
		EXPRESSION_TYPE(addition)
		EXPRESSION_TYPE(subtraction)
		EXPRESSION_TYPE(left_shift)
		EXPRESSION_TYPE(right_shift)
		EXPRESSION_TYPE(less_than)
		EXPRESSION_TYPE(less_than_or_equal_to)
		EXPRESSION_TYPE(greater_than)
		EXPRESSION_TYPE(greater_than_or_equal_to)
		EXPRESSION_TYPE(equal_to)
		EXPRESSION_TYPE(not_equal_to)
		EXPRESSION_TYPE(bitwise_and)
		EXPRESSION_TYPE(bitwise_exclusive_or)
		EXPRESSION_TYPE(bitwise_inclusive_or)
		EXPRESSION_TYPE(logical_and)
		EXPRESSION_TYPE(logical_or)
		EXPRESSION_TYPE(conditional)
		EXPRESSION_TYPE(assignment)
		EXPRESSION_TYPE(multiplication_assignment)
		EXPRESSION_TYPE(division_assignment)
		EXPRESSION_TYPE(modulo_assignment)
		EXPRESSION_TYPE(addition_assignment)
		EXPRESSION_TYPE(subtraction_assignment)
		EXPRESSION_TYPE(left_shift_assignment)
		EXPRESSION_TYPE(right_shift_assignment)
		EXPRESSION_TYPE(bitwise_and_assignment)
		EXPRESSION_TYPE(bitwise_exclusive_or_assignment)
		EXPRESSION_TYPE(bitwise_inclusive_or_assignment)
		SIMPLE_TYPE(bool)
		SIMPLE_TYPE(char)
		SIMPLE_TYPE(wchar_t)
		SIMPLE_TYPE(int)
		SIMPLE_TYPE(long int)
		SIMPLE_TYPE(long long int)
		SIMPLE_TYPE(unsigned int)
		SIMPLE_TYPE(unsigned long int)
		SIMPLE_TYPE(unsigned long long int)
		SIMPLE_TYPE(float)
		SIMPLE_TYPE(double)
		SIMPLE_TYPE(long double)

		std::string
		operator()(const std::string&)
		{
			return "string";
		}

		std::string
		operator()(const std::wstring&)
		{
			return "wide string";
		}
	} get_expression_type_visitor;

#undef EXPRESSION_TYPE
#undef SIMPLE_TYPE
}



semantic_graph_serializer::serialize_expression_visitor::serialize_expression_visitor
(
	semantic_graph_serializer& serializer,
	const unsigned int indent_level
):
	serializer_(serializer),
	output_(serializer_.output_),
	indent_level_(indent_level)
{
}

template<typename T>
void
semantic_graph_serializer::serialize_expression_visitor::operator()(const T t)
{
	output_ << indent(indent_level_) << t << '\n';
}

template<int Tag>
void
semantic_graph_serializer::serialize_expression_visitor::operator()(const binary_operation<Tag>& operation)
{
	output_ << indent(indent_level_) << "<left_operand>\n";
	serializer_.serialize_expression(operation.left_operand(), indent_level_ + 1);
	output_ << indent(indent_level_) << "</left_operand>\n";
	output_ << indent(indent_level_) << "<right_operand>\n";
	serializer_.serialize_expression(operation.right_operand(), indent_level_ + 1);
	output_ << indent(indent_level_) << "</right_operand>\n";
}

void
semantic_graph_serializer::serialize_expression_visitor::operator()(const conditional_expression& operation)
{
	output_ << indent(indent_level_) << "<condition_operand>\n";
	serializer_.serialize_expression(operation.condition_operand(), indent_level_ + 1);
	output_ << indent(indent_level_) << "</condition_operand>\n";
	output_ << indent(indent_level_) << "<true_operand>\n";
	serializer_.serialize_expression(operation.true_operand(), indent_level_ + 1);
	output_ << indent(indent_level_) << "</true_operand>\n";
	output_ << indent(indent_level_) << "<false_operand>\n";
	serializer_.serialize_expression(operation.false_operand(), indent_level_ + 1);
	output_ << indent(indent_level_) << "</false_operand>\n";
}

void
semantic_graph_serializer::serialize_expression_visitor::operator()(const char c)
{
	output_ << indent(indent_level_) << static_cast<int>(c) << '\n';
}

void
semantic_graph_serializer::serialize_expression_visitor::operator()(const bool b)
{
	output_ << indent(indent_level_) << (b ? "true" : "false") << '\n';
}

void
semantic_graph_serializer::serialize_expression_visitor::operator()(const std::string& str)
{
	output_ << indent(indent_level_);
	output_ << std::hex;
	for(char c: str)
		output_ << (static_cast<int>(c) & 0xff) << ' ';
	output_ << std::dec;
	output_ << '\n';
}

void
semantic_graph_serializer::serialize_expression_visitor::operator()(const std::wstring& str)
{
	output_ << indent(indent_level_);
	output_ << std::hex;
	for(wchar_t c: str)
		output_ << static_cast<int>(c) << ' ';
	output_ << std::dec;
	output_ << '\n';
}



void
semantic_graph_serializer::serialize_expression
(
	const semantic_entities::expression_t& entity,
	const unsigned int indent_level
)
{
	output_ << indent(indent_level) << "<expression";
	output_ << " type=\"" << apply_visitor(get_expression_type_visitor, entity) << "\"";
	output_ << ">\n";

	serialize_expression_visitor visitor(*this, indent_level + 1);
	apply_visitor(visitor, entity);

	output_ << indent(indent_level) << "</expression>\n";
}



#define serialize_member(TYPE, FUNCTION) \
template<> \
void \
semantic_graph_serializer::serialize_member<semantic_entities::TYPE> \
( \
	const semantic_entities::TYPE& entity, \
	const unsigned int indent_level \
) \
{ \
	FUNCTION(entity, indent_level); \
}

serialize_member(namespace_alias, serialize_namespace_alias)
serialize_member(namespace_, serialize_namespace)
serialize_member(linked_namespace, serialize_namespace)
serialize_member(unnamed_namespace, serialize_unnamed_namespace)
serialize_member(linked_unnamed_namespace, serialize_unnamed_namespace)
serialize_member(class_, serialize_class)
serialize_member(member_class, serialize_class)
serialize_member(union_, serialize_class)
serialize_member(member_union, serialize_class)
serialize_member(anonymous_union, serialize_class)
serialize_member(anonymous_member_union, serialize_class)
serialize_member(enum_, serialize_enum)
serialize_member(member_enum, serialize_enum)
serialize_member(typedef_, serialize_typedef)
serialize_member(member_typedef, serialize_typedef)
serialize_member(constructor, serialize_constructor)
serialize_member(destructor, serialize_destructor)
serialize_member(operator_member_function, serialize_operator_member_function)
serialize_member(conversion_function, serialize_conversion_function)
serialize_member(simple_member_function, serialize_simple_member_function)
serialize_member(operator_function, serialize_operator_function)
serialize_member(simple_function, serialize_simple_function)
serialize_member(variable, serialize_variable)
serialize_member(member_variable, serialize_variable)
serialize_member(bit_field, serialize_variable)

#undef serialize_member



std::string
semantic_graph_serializer::attribute(const member_access& a)
{
	std::ostringstream oss;

	oss << " access=\"";
	switch(a)
	{
		case member_access::PUBLIC:
			oss << "public";
			break;
		case member_access::PROTECTED:
			oss << "protected";
			break;
		case member_access::PRIVATE:
			oss << "private";
			break;
	}
	oss << "\"";

	return oss.str();
}

std::string
semantic_graph_serializer::attribute(const semantic_entities::overloadable_operator op)
{
	std::ostringstream oss;

	oss << " operator=\"";
	switch(op)
	{
		case semantic_entities::overloadable_operator::NEW:
			oss << "new";
			break;
		case semantic_entities::overloadable_operator::NEW_ARRAY:
			oss << "new[]";
			break;
		case semantic_entities::overloadable_operator::DELETE:
			oss << "delete";
			break;
		case semantic_entities::overloadable_operator::DELETE_ARRAY:
			oss << "delete[]";
			break;
		case semantic_entities::overloadable_operator::DOUBLE_RIGHT_ANGLE_BRACKET_EQUAL:
			oss << ">>=";
			break;
		case semantic_entities::overloadable_operator::DOUBLE_LEFT_ANGLE_BRACKET_EQUAL:
			oss << "<<=";
			break;
		case semantic_entities::overloadable_operator::ARROW_ASTERISK:
			oss << "->*";
			break;
		case semantic_entities::overloadable_operator::PLUS_EQUAL:
			oss << "+=";
			break;
		case semantic_entities::overloadable_operator::MINUS_EQUAL:
			oss << "-=";
			break;
		case semantic_entities::overloadable_operator::ASTERISK_EQUAL:
			oss << "*=";
			break;
		case semantic_entities::overloadable_operator::SLASH_EQUAL:
			oss << "/=";
			break;
		case semantic_entities::overloadable_operator::PERCENT_EQUAL:
			oss << "%=";
			break;
		case semantic_entities::overloadable_operator::CIRCUMFLEX_EQUAL:
			oss << "^=";
			break;
		case semantic_entities::overloadable_operator::AMPERSAND_EQUAL:
			oss << "&=";
			break;
		case semantic_entities::overloadable_operator::PIPE_EQUAL:
			oss << "|=";
			break;
		case semantic_entities::overloadable_operator::DOUBLE_LEFT_ANGLE_BRACKET:
			oss << "<<";
			break;
		case semantic_entities::overloadable_operator::DOUBLE_RIGHT_ANGLE_BRACKET:
			oss << ">>";
			break;
		case semantic_entities::overloadable_operator::DOUBLE_EQUAL:
			oss << "==";
			break;
		case semantic_entities::overloadable_operator::EXCLAMATION_EQUAL:
			oss << "!=";
			break;
		case semantic_entities::overloadable_operator::LEFT_ANGLE_BRACKET_EQUAL:
			oss << "<=";
			break;
		case semantic_entities::overloadable_operator::RIGHT_ANGLE_BRACKET_EQUAL:
			oss << ">=";
			break;
		case semantic_entities::overloadable_operator::DOUBLE_AMPERSAND:
			oss << "&&";
			break;
		case semantic_entities::overloadable_operator::DOUBLE_PIPE:
			oss << "||";
			break;
		case semantic_entities::overloadable_operator::DOUBLE_PLUS:
			oss << "++";
			break;
		case semantic_entities::overloadable_operator::DOUBLE_MINUS:
			oss << "--";
			break;
		case semantic_entities::overloadable_operator::ARROW:
			oss << "->";
			break;
		case semantic_entities::overloadable_operator::ROUND_BRACKETS:
			oss << "()";
			break;
		case semantic_entities::overloadable_operator::SQUARE_BRACKETS:
			oss << "[]";
			break;
		case semantic_entities::overloadable_operator::COMMA:
			oss << ",";
			break;
		case semantic_entities::overloadable_operator::PLUS:
			oss << "+";
			break;
		case semantic_entities::overloadable_operator::MINUS:
			oss << "-";
			break;
		case semantic_entities::overloadable_operator::ASTERISK:
			oss << "*";
			break;
		case semantic_entities::overloadable_operator::SLASH:
			oss << "/";
			break;
		case semantic_entities::overloadable_operator::PERCENT:
			oss << "%";
			break;
		case semantic_entities::overloadable_operator::CIRCUMFLEX:
			oss << "^";
			break;
		case semantic_entities::overloadable_operator::AMPERSAND:
			oss << "&";
			break;
		case semantic_entities::overloadable_operator::PIPE:
			oss << "|";
			break;
		case semantic_entities::overloadable_operator::TILDE:
			oss << "~";
			break;
		case semantic_entities::overloadable_operator::EXCLAMATION:
			oss << "!";
			break;
		case semantic_entities::overloadable_operator::EQUAL:
			oss << "=";
			break;
		case semantic_entities::overloadable_operator::LEFT_ANGLE_BRACKET:
			oss << "<";
			break;
		case semantic_entities::overloadable_operator::RIGHT_ANGLE_BRACKET:
			oss << ">";
			break;
	}
	oss << "\"";

	return oss.str();
}

void
semantic_graph_serializer::serialize_class_id_attribute
(
	const scalpel::cpp::semantic_entities::class_ptr_variant& entity
)
{
	if(const class_* const* opt = scalpel::utility::get<class_*>(&entity))
		output_ << " class_id=\"" << get_id(**opt) << "\"";
	else if(const member_class* const* opt = scalpel::utility::get<member_class*>(&entity))
		output_ << " member_class_id=\"" << get_id(**opt) << "\"";
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
ENTITY_ID_MAP_OF_TYPE(enum_, enum_id_map_)
ENTITY_ID_MAP_OF_TYPE(member_enum, member_enum_id_map_)
ENTITY_ID_MAP_OF_TYPE(typedef_, typedef_id_map_)
ENTITY_ID_MAP_OF_TYPE(member_typedef, member_typedef_id_map_)
ENTITY_ID_MAP_OF_TYPE(operator_member_function, operator_member_function_id_map_)
ENTITY_ID_MAP_OF_TYPE(conversion_function, conversion_function_id_map_)
ENTITY_ID_MAP_OF_TYPE(simple_member_function, simple_member_function_id_map_)
ENTITY_ID_MAP_OF_TYPE(operator_function, operator_function_id_map_)
ENTITY_ID_MAP_OF_TYPE(simple_function, simple_function_id_map_)
ENTITY_ID_MAP_OF_TYPE(variable, variable_id_map_)
ENTITY_ID_MAP_OF_TYPE(member_variable, member_variable_id_map_)
ENTITY_ID_MAP_OF_TYPE(bit_field, bit_field_id_map_)

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

