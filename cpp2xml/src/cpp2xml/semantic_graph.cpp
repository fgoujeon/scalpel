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
#include "detail/basic_print_functions.hpp"
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
semantic_graph_serializer::operator()(std::shared_ptr<const namespace_> entity)
{
	initialize_ids(entity);
	serialize_namespace(entity);
}

void
semantic_graph_serializer::initialize_ids(const std::shared_ptr<const namespace_>& entity)
{
	namespace_id_counter_ = 0;
	class_id_counter_ = 0;
	enum_id_counter_ = 0;
	define_ids(entity);
}

void
semantic_graph_serializer::serialize_type
(
	const semantic_entities::type_variant& n,
	const unsigned int indent_level
)
{
	if(auto opt_type = scalpel::utility::get<fundamental_type>(&n))
	{
		output_ << indent(indent_level) << "<fundamental_type type=\"";
		serialize_fundamental_type(*opt_type);
	   	output_ << "\"/>\n";
	}
	else if(const function_type* opt_type = scalpel::utility::get<function_type>(&n))
	{
		serialize_function_type(*opt_type, indent_level);
	}
	else if(auto opt_type = scalpel::utility::get<cv_qualified_type>(&n))
	{
		output_ << indent(indent_level) << "<cv_qualified_type";
		if(opt_type->const_qualified())
			output_ << " const=\"true\"";
		if(opt_type->volatile_qualified())
			output_ << " volatile=\"true\"";
		output_ << ">\n";
		serialize_type((*opt_type).qualified_type(), indent_level + 1);
		output_ << indent(indent_level) << "</cv_qualified_type>\n";
	}
	else if(auto opt_type = scalpel::utility::get<pointer>(&n))
	{
		output_ << indent(indent_level) << "<pointer>\n";
		serialize_type((*opt_type).qualified_type(), indent_level + 1);
		output_ << indent(indent_level) << "</pointer>\n";
	}
	else if(auto opt_type = scalpel::utility::get<pointer_to_member>(&n))
	{
		output_ << indent(indent_level) << "<pointer_to_member";
		output_ << " class_id=\"c" << class_id(opt_type->member_class().get()) << "\"";
		output_ << ">\n";
		serialize_type((*opt_type).qualified_type(), indent_level + 1);
		output_ << indent(indent_level) << "</pointer_to_member>\n";
	}
	else if(auto opt_type = scalpel::utility::get<reference>(&n))
	{
		output_ << indent(indent_level) << "<reference>\n";
		serialize_type((*opt_type).qualified_type(), indent_level + 1);
		output_ << indent(indent_level) << "</reference>\n";
	}
	else if(auto opt_type = scalpel::utility::get<array>(&n))
	{
		output_ << indent(indent_level) << "<array size=\"" << (*opt_type).size() << "\">\n";
		serialize_type((*opt_type).qualified_type(), indent_level + 1);
		output_ << indent(indent_level) << "</array>\n";
	}
	else if(auto opt_type = scalpel::utility::get<const class_*>(&n))
	{
		output_ << indent(indent_level) << "<class id=\"c" << class_id(*opt_type) << "\"/>\n";
	}
	else if(auto opt_type = scalpel::utility::get<const enum_*>(&n))
	{
		output_ << indent(indent_level) << "<enum id=\"e" << enum_id(*opt_type) << "\"/>\n";
	}
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
semantic_graph_serializer::serialize_namespace
(
	std::shared_ptr<const namespace_> entity,
	const unsigned int indent_level
)
{
	output_ << indent(indent_level) << "<namespace";
	if(entity->name() != "")
	{
		output_ << " name=\"" << entity->name() << "\"";
	}
	output_ << " id=\"n" << namespace_id(entity.get()) << "\"";
	output_ << ">\n";

	for(auto i = entity->namespace_aliases().begin(); i != entity->namespace_aliases().end(); ++i)
		serialize_namespace_alias(*i, indent_level + 1);

	for(auto i = entity->namespaces().begin(); i != entity->namespaces().end(); ++i)
		serialize_namespace(*i, indent_level + 1);

	for(auto i = entity->classes().begin(); i != entity->classes().end(); ++i)
		serialize_class(*i, indent_level + 1);

	for(auto i = entity->enums().begin(); i != entity->enums().end(); ++i)
		serialize_enum(*i, indent_level + 1);

	for(auto i = entity->typedefs().begin(); i != entity->typedefs().end(); ++i)
		serialize_typedef(*i, indent_level + 1);

	for(auto i = entity->simple_functions().begin(); i != entity->simple_functions().end(); ++i)
		serialize_simple_function(*i, indent_level + 1);

	for(auto i = entity->operator_functions().begin(); i != entity->operator_functions().end(); ++i)
		serialize_operator_function(*i, indent_level + 1);

	for(auto i = entity->variables().begin(); i != entity->variables().end(); ++i)
		serialize_variable(*i, indent_level + 1);

	output_ << indent(indent_level) << "</namespace>\n";
}

void
semantic_graph_serializer::serialize_class
(
	std::shared_ptr<const class_> entity,
	const unsigned int indent_level
)
{
	output_ << indent(indent_level) << "<class";
	if(!entity->name().empty())
		output_ << " name=\"" << entity->name() << "\"";
	output_ << " id=\"c" << class_id(entity.get()) << "\"";
	//extra attributes if the class is a nested class
	if(entity->has_enclosing_declarative_region())
	{
		declarative_region_shared_ptr_variant enclosing_declarative_region = entity->enclosing_declarative_region();
		if(auto opt_class = utility::get<class_>(&enclosing_declarative_region))
		{
			std::shared_ptr<class_> enclosing_declarative_region = *opt_class;

			class_::access acc = enclosing_declarative_region->member_access(entity);
			output_ << attribute(acc);
		}
	}
	if(!entity->complete())
		output_ << " complete=\"false\"";
	output_ << ">\n";

	if(!entity->base_classes().empty())
	{
		output_ << indent(indent_level + 1) << "<base_classes>\n";
		for(auto i = entity->base_classes().begin(); i != entity->base_classes().end(); ++i)
			serialize_base_class
			(
				*i,
				entity->base_class_access(*i),
				entity->is_virtual_base_class(*i),
				indent_level + 2
			);
		output_ << indent(indent_level + 1) << "</base_classes>\n";
	}

	for(auto i = entity->nested_classes().begin(); i != entity->nested_classes().end(); ++i)
		serialize_class(*i, indent_level + 1);

	for(auto i = entity->enums().begin(); i != entity->enums().end(); ++i)
		serialize_enum(*i, indent_level + 1);

	for(auto i = entity->typedefs().begin(); i != entity->typedefs().end(); ++i)
		serialize_typedef(*i, indent_level + 1);

	for(auto i = entity->constructors().begin(); i != entity->constructors().end(); ++i)
		serialize_constructor(*i, indent_level + 1);

	serialize_destructor(entity->get_destructor(), indent_level + 1);

	for(auto i = entity->operator_functions().begin(); i != entity->operator_functions().end(); ++i)
		serialize_operator_member_function(*i, indent_level + 1);

	for(auto i = entity->conversion_functions().begin(); i != entity->conversion_functions().end(); ++i)
		serialize_conversion_function(*i, indent_level + 1);

	for(auto i = entity->simple_functions().begin(); i != entity->simple_functions().end(); ++i)
		serialize_simple_member_function(*i, indent_level + 1);

	for(auto i = entity->variables().begin(); i != entity->variables().end(); ++i)
		serialize_variable(*i, indent_level + 1);

	output_ << indent(indent_level) << "</class>\n";
}

void
semantic_graph_serializer::serialize_base_class
(
	std::shared_ptr<const class_> entity,
	const class_::access acc,
	const bool is_virtual,
	const unsigned int indent_level
)
{
	output_ << indent(indent_level) << "<base_class";
	output_ << " id=\"c" << class_id(entity.get()) << "\"";
	output_ << attribute(acc);
	if(is_virtual)
		output_ << " virtual=\"true\"";
	output_ << "/>\n";
}

void
semantic_graph_serializer::serialize_enum
(
	std::shared_ptr<const enum_> entity,
	const unsigned int indent_level
)
{
	output_ << indent(indent_level) << "<enum";
	if(!entity->name().empty())
		output_ << " name=\"" << entity->name() << "\"";
	output_ << " id=\"e" << enum_id(entity.get()) << "\"";
	output_ << ">\n";

	for(auto i = entity->constants().begin(); i != entity->constants().end(); ++i)
	{
		const std::shared_ptr<const enum_::constant> constant = *i;
		output_ << indent(indent_level + 1) << "<constant";
		output_ << " name=\"" << constant->name() << "\"";
		output_ << " value=\"" << constant->value() << "\"";
		output_ << ">\n";
	}

	output_ << indent(indent_level) << "</enum>\n";
}

void
semantic_graph_serializer::serialize_constructor
(
	std::shared_ptr<const constructor> entity,
	const unsigned int indent_level
)
{
	output_ << indent(indent_level) << "<constructor";
	if(entity->has_enclosing_declarative_region())
	{
		std::shared_ptr<class_> enclosing_declarative_region = utility::get<class_>(entity->enclosing_declarative_region());

		class_::access acc = enclosing_declarative_region->member_access(entity);
		output_ << attribute(acc);
	}
	if(entity->variadic())
		output_ << " variadic=\"true\"";
	if(entity->is_inline())
		output_ << " inline=\"true\"";
	if(entity->is_explicit())
		output_ << " explicit=\"true\"";
	if(!entity->defined())
		output_ << " defined=\"false\"";
	output_ << ">\n";

	serialize_function_parameter_list(entity->parameters(), indent_level + 1);

	output_ << indent(indent_level) << "</constructor>\n";
}

void
semantic_graph_serializer::serialize_destructor
(
	std::shared_ptr<const destructor> entity,
	const unsigned int indent_level
)
{
	output_ << indent(indent_level) << "<destructor";

	assert(entity->has_enclosing_declarative_region());
	declarative_region_shared_ptr_variant enclosing_declarative_region = entity->enclosing_declarative_region();
	std::shared_ptr<class_> enclosing_class = utility::get<class_>(enclosing_declarative_region);

	class_::access acc = enclosing_class->member_access(entity);
	output_ << attribute(acc);
	if(entity->is_inline())
		output_ << " inline=\"true\"";
	if(entity->is_virtual())
		output_ << " virtual=\"true\"";
	if(entity->is_pure())
		output_ << " pure=\"true\"";
	if(!entity->defined())
		output_ << " defined=\"false\"";
	output_ << ">\n";

	output_ << indent(indent_level) << "</destructor>\n";
}

void
semantic_graph_serializer::serialize_operator_member_function
(
	std::shared_ptr<const operator_member_function> entity,
	const unsigned int indent_level
)
{
	output_ << indent(indent_level) << "<operator_function";
	output_ << attribute(entity->overloaded_operator());

	assert(entity->has_enclosing_declarative_region());
	declarative_region_shared_ptr_variant enclosing_declarative_region = entity->enclosing_declarative_region();
	std::shared_ptr<class_> enclosing_class = utility::get<class_>(enclosing_declarative_region);

	class_::access acc = enclosing_class->member_access(entity);
	output_ << attribute(acc);
	if(entity->is_inline())
		output_ << " inline=\"true\"";
	if(entity->is_const())
		output_ << " const=\"true\"";
	if(entity->is_volatile())
		output_ << " volatile=\"true\"";
	if(entity->is_virtual())
		output_ << " virtual=\"true\"";
	if(entity->is_pure())
		output_ << " pure=\"true\"";
	if(!entity->defined())
		output_ << " defined=\"false\"";
	output_ << ">\n";

	output_ << indent(indent_level + 1) << "<return_type>\n";
	serialize_type(entity->return_type(), indent_level + 2);
	output_ << indent(indent_level + 1) << "</return_type>\n";

	serialize_function_parameter_list(entity->parameters(), indent_level + 1);

	output_ << indent(indent_level) << "</operator_function>\n";
}

void
semantic_graph_serializer::serialize_conversion_function
(
	std::shared_ptr<const conversion_function> entity,
	const unsigned int indent_level
)
{
	output_ << indent(indent_level) << "<conversion_function";

	assert(entity->has_enclosing_declarative_region());
	declarative_region_shared_ptr_variant enclosing_declarative_region = entity->enclosing_declarative_region();
	std::shared_ptr<class_> enclosing_class = utility::get<class_>(enclosing_declarative_region);

	class_::access acc = enclosing_class->member_access(entity);
	output_ << attribute(acc);
	if(entity->is_inline())
		output_ << " inline=\"true\"";
	if(entity->is_const())
		output_ << " const=\"true\"";
	if(entity->is_volatile())
		output_ << " volatile=\"true\"";
	if(entity->is_virtual())
		output_ << " virtual=\"true\"";
	if(entity->is_pure())
		output_ << " pure=\"true\"";
	if(!entity->defined())
		output_ << " defined=\"false\"";
	output_ << ">\n";

	output_ << indent(indent_level + 1) << "<return_type>\n";
	serialize_type(entity->return_type(), indent_level + 2);
	output_ << indent(indent_level + 1) << "</return_type>\n";

	output_ << indent(indent_level) << "</conversion_function>\n";
}

void
semantic_graph_serializer::serialize_simple_member_function
(
	std::shared_ptr<const simple_member_function> entity,
	const unsigned int indent_level
)
{
	output_ << indent(indent_level) << "<simple_function";
	output_ << " name=\"" << entity->name() << "\"";

	assert(entity->has_enclosing_declarative_region());
	declarative_region_shared_ptr_variant enclosing_declarative_region = entity->enclosing_declarative_region();
	std::shared_ptr<class_> enclosing_class = utility::get<class_>(enclosing_declarative_region);

	class_::access acc = enclosing_class->member_access(entity);
	output_ << attribute(acc);
	if(entity->variadic())
		output_ << " variadic=\"true\"";
	if(entity->is_inline())
		output_ << " inline=\"true\"";
	if(entity->is_static())
		output_ << " static=\"true\"";
	if(entity->is_const())
		output_ << " const=\"true\"";
	if(entity->is_volatile())
		output_ << " volatile=\"true\"";
	if(entity->is_virtual())
		output_ << " virtual=\"true\"";
	if(entity->is_pure())
		output_ << " pure=\"true\"";
	if(!entity->defined())
		output_ << " defined=\"false\"";
	output_ << ">\n";

	output_ << indent(indent_level + 1) << "<return_type>\n";
	serialize_type(entity->return_type(), indent_level + 2);
	output_ << indent(indent_level + 1) << "</return_type>\n";

	serialize_function_parameter_list(entity->parameters(), indent_level + 1);

	output_ << indent(indent_level) << "</simple_function>\n";
}

void
semantic_graph_serializer::serialize_operator_function
(
	std::shared_ptr<const operator_function> entity,
	const unsigned int indent_level
)
{
	output_ << indent(indent_level) << "<operator_function";
	output_ << attribute(entity->overloaded_operator());
	if(entity->is_inline())
		output_ << " inline=\"true\"";
	if(entity->is_static())
		output_ << " static=\"true\"";
	if(!entity->defined())
		output_ << " defined=\"false\"";
	output_ << ">\n";

	output_ << indent(indent_level + 1) << "<return_type>\n";
	serialize_type(entity->return_type(), indent_level + 2);
	output_ << indent(indent_level + 1) << "</return_type>\n";

	serialize_function_parameter_list(entity->parameters(), indent_level + 1);

	output_ << indent(indent_level) << "</operator_function>\n";
}

void
semantic_graph_serializer::serialize_simple_function
(
	std::shared_ptr<const simple_function> entity,
	const unsigned int indent_level
)
{
	output_ << indent(indent_level) << "<simple_function";
	output_ << " name=\"" << entity->name() << "\"";
	if(entity->variadic())
		output_ << " variadic=\"true\"";
	if(entity->is_static())
		output_ << " static=\"true\"";
	if(entity->is_inline())
		output_ << " inline=\"true\"";
	if(!entity->defined())
		output_ << " defined=\"false\"";
	output_ << ">\n";

	output_ << indent(indent_level + 1) << "<return_type>\n";
	serialize_type(entity->return_type(), indent_level + 2);
	output_ << indent(indent_level + 1) << "</return_type>\n";

	serialize_function_parameter_list(entity->parameters(), indent_level + 1);

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
	const std::shared_ptr<const function_parameter> p,
	const unsigned int indent_level
)
{
	output_ << indent(indent_level) << "<parameter";
	if(!p->name().empty())
		output_ << " name=\"" << p->name() << "\"";
	output_ << ">\n";
	output_ << indent(indent_level + 1) << "<type>\n";
	serialize_type(p->type(), indent_level + 2);
	output_ << indent(indent_level + 1) << "</type>\n";
	output_ << indent(indent_level) << "</parameter>\n";
}

void
semantic_graph_serializer::serialize_variable
(
	std::shared_ptr<const variable> entity,
	const unsigned int indent_level
)
{
	output_ << indent(indent_level) << "<variable";
	output_ << " name=\"" << entity->name() << "\"";
	//extra attributes if the function is a class member function
	if(entity->has_enclosing_declarative_region())
	{
		declarative_region_shared_ptr_variant enclosing_declarative_region = entity->enclosing_declarative_region();
		if(auto opt_class = utility::get<class_>(&enclosing_declarative_region))
		{
			std::shared_ptr<class_> enclosing_declarative_region = *opt_class;

			class_::access acc = enclosing_declarative_region->member_access(entity);
			output_ << attribute(acc);
			if(enclosing_declarative_region->is_mutable_member_variable(entity))
				output_ << " mutable=\"true\"";
		}
	}
	if(entity->is_static())
		output_ << " static=\"true\"";
	output_ << ">\n";
	output_ << indent(indent_level + 1) << "<type>\n";
	serialize_type(entity->type(), indent_level + 2);
	output_ << indent(indent_level + 1) << "</type>\n";
	output_ << indent(indent_level) << "</variable>\n";
}

void
semantic_graph_serializer::serialize_typedef
(
	std::shared_ptr<const typedef_> entity,
	const unsigned int indent_level
)
{
	output_ << indent(indent_level) << "<typedef";
	output_ << " name=\"" << entity->name() << "\"";
	//extra attributes if the typedef is member of a class
	if(entity->has_enclosing_declarative_region())
	{
		declarative_region_shared_ptr_variant enclosing_declarative_region = entity->enclosing_declarative_region();
		if(auto opt_class = utility::get<class_>(&enclosing_declarative_region))
		{
			std::shared_ptr<class_> enclosing_declarative_region = *opt_class;

			class_::access acc = enclosing_declarative_region->member_access(entity);
			output_ << attribute(acc);
		}
	}
	output_ << ">\n";
	output_ << indent(indent_level + 1) << "<type>\n";
	serialize_type(entity->type(), indent_level + 2);
	output_ << indent(indent_level + 1) << "</type>\n";
	output_ << indent(indent_level) << "</typedef>\n";
}

void
semantic_graph_serializer::serialize_namespace_alias
(
	std::shared_ptr<const namespace_alias> entity,
	const unsigned int indent_level
)
{
	output_ << indent(indent_level) << "<namespace_alias";
	output_ << " name=\"" << entity->name() << "\"";
	output_ << " id=\"n" << namespace_id(entity->referred_namespace().get()) << "\"";
	output_ << "/>\n";
}

std::string
semantic_graph_serializer::attribute(const class_::access& a)
{
	std::ostringstream oss;

	oss << " access=\"";
	switch(a)
	{
		case class_::access::PUBLIC:
			oss << "public";
			break;
		case class_::access::PROTECTED:
			oss << "protected";
			break;
		case class_::access::PRIVATE:
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
semantic_graph_serializer::define_ids(const std::shared_ptr<const namespace_>& entity)
{
	namespace_ids_[entity.get()] = namespace_id_counter_;
	++namespace_id_counter_;

	for(auto i = entity->namespaces().begin(); i != entity->namespaces().end(); ++i)
		define_ids(*i);
	for(auto i = entity->classes().begin(); i != entity->classes().end(); ++i)
		define_ids(*i);
	for(auto i = entity->enums().begin(); i != entity->enums().end(); ++i)
		define_ids(*i);
}

void
semantic_graph_serializer::define_ids(const std::shared_ptr<const class_>& entity)
{
	class_ids_[entity.get()] = class_id_counter_;
	++class_id_counter_;

	for(auto i = entity->nested_classes().begin(); i != entity->nested_classes().end(); ++i)
		define_ids(*i);
	for(auto i = entity->enums().begin(); i != entity->enums().end(); ++i)
		define_ids(*i);
}

void
semantic_graph_serializer::define_ids(const std::shared_ptr<const enum_>& entity)
{
	enum_ids_[entity.get()] = enum_id_counter_;
	++enum_id_counter_;
}

unsigned int
semantic_graph_serializer::namespace_id(const scalpel::cpp::semantic_entities::namespace_* namespace_entity) const
{
	namespace_ids_t::const_iterator it = namespace_ids_.find(namespace_entity);
	if(it != namespace_ids_.end())
		return it->second;
	else
		assert(false);
}

unsigned int
semantic_graph_serializer::class_id(const scalpel::cpp::semantic_entities::class_* class_entity) const
{
	class_ids_t::const_iterator it = class_ids_.find(class_entity);
	if(it != class_ids_.end())
		return it->second;
	else
		assert(false);
}

unsigned int
semantic_graph_serializer::enum_id(const scalpel::cpp::semantic_entities::enum_* enum_entity) const
{
	enum_ids_t::const_iterator it = enum_ids_.find(enum_entity);
	if(it != enum_ids_.end())
		return it->second;
	else
		assert(false);
}



void
serialize_semantic_graph
(
	std::shared_ptr<const semantic_graph> graph,
	std::ostream& output
)
{
	semantic_graph_serializer serializer(output);
	serializer(graph);
}

} //namespace cpp2xml

