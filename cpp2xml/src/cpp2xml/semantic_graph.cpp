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

#include "semantic_graph.hpp"
#include "detail/basic_print_functions.hpp"
#include <scalpel/utility/variant.hpp>
#include <vector>
#include <sstream>

namespace cpp2xml
{

using namespace detail;

semantic_graph_serializer::semantic_graph_serializer():
	namespace_id_counter_(0),
	class_id_counter_(0)
{
}

void
semantic_graph_serializer::serialize_type
(
	std::ostream& output,
	const semantic_entities::type_variant& n,
	const unsigned int indent_level
)
{
	if(auto opt_type = scalpel::utility::get<fundamental_type>(&n))
	{
		output << indent(indent_level) << "<fundamental_type type=\"";
		serialize_fundamental_type(output, *opt_type);
	   	output << "\"/>\n";
	}
	else if(auto opt_type = scalpel::utility::get<cv_qualified_type>(&n))
	{
		output << indent(indent_level) << "<cv_qualified_type";
		if(opt_type->const_qualified())
			output << " const=\"true\"";
		if(opt_type->volatile_qualified())
			output << " volatile=\"true\"";
		output << ">\n";
		serialize_type(output, (*opt_type).qualified_type(), indent_level + 1);
		output << indent(indent_level) << "</cv_qualified_type>\n";
	}
	else if(auto opt_type = scalpel::utility::get<pointer>(&n))
	{
		output << indent(indent_level) << "<pointer>\n";
		serialize_type(output, (*opt_type).qualified_type(), indent_level + 1);
		output << indent(indent_level) << "</pointer>\n";
	}
	else if(auto opt_type = scalpel::utility::get<reference>(&n))
	{
		output << indent(indent_level) << "<reference>\n";
		serialize_type(output, (*opt_type).qualified_type(), indent_level + 1);
		output << indent(indent_level) << "</reference>\n";
	}
	else if(auto opt_type = scalpel::utility::get<array>(&n))
	{
		output << indent(indent_level) << "<array size=\"" << (*opt_type).size() << "\">\n";
		serialize_type(output, (*opt_type).qualified_type(), indent_level + 1);
		output << indent(indent_level) << "</array>\n";
	}
	else if(auto opt_type = scalpel::utility::get<const class_*>(&n))
	{
		output << indent(indent_level) << "<class id=\"c" << class_ids_[*opt_type] << "\"/>\n";
	}
}

void
semantic_graph_serializer::serialize_fundamental_type
(
	std::ostream& output,
	const fundamental_type type
)
{
	std::vector<std::pair<fundamental_type, const char*>> fundamental_types_table =
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

	for(auto i = fundamental_types_table.begin(); i != fundamental_types_table.end(); ++i)
	{
		auto pair = *i;
		const fundamental_type t = pair.first;
		const char* type_str = pair.second;

		if(t == type)
		{
			output << type_str;
			break;
		}
	}
}

void
semantic_graph_serializer::serialize_namespace
(
	std::ostream& output,
	std::shared_ptr<const namespace_> n,
	const unsigned int indent_level
)
{
	output << indent(indent_level) << "<namespace";
	if(n->name() != "")
	{
		output << " name=\"" << n->name() << "\"";
	}
	output << " id=\"n" << namespace_id_counter_ << "\"";
	output << ">\n";

	namespace_ids_[n.get()] = namespace_id_counter_;
	++namespace_id_counter_;

	for(auto i = n->namespace_aliases().begin(); i != n->namespace_aliases().end(); ++i)
		serialize_namespace_alias(output, *i, indent_level + 1);

	for(auto i = n->namespaces().begin(); i != n->namespaces().end(); ++i)
		serialize_namespace(output, *i, indent_level + 1);

	for(auto i = n->classes().begin(); i != n->classes().end(); ++i)
		serialize_class(output, *i, indent_level + 1);

	for(auto i = n->typedefs().begin(); i != n->typedefs().end(); ++i)
		serialize_typedef(output, *i, indent_level + 1);

	for(auto i = n->simple_functions().begin(); i != n->simple_functions().end(); ++i)
		serialize_simple_function(output, *i, indent_level + 1);

	for(auto i = n->operator_functions().begin(); i != n->operator_functions().end(); ++i)
		serialize_operator_function(output, *i, indent_level + 1);

	for(auto i = n->variables().begin(); i != n->variables().end(); ++i)
		serialize_variable(output, *i, indent_level + 1);

	output << indent(indent_level) << "</namespace>\n";
}

void
semantic_graph_serializer::serialize_class
(
	std::ostream& output,
	std::shared_ptr<const class_> c,
	const unsigned int indent_level
)
{
	output << indent(indent_level) << "<class";
	output << " name=\"" << c->name() << "\"";
	output << " id=\"c" << class_id_counter_ << "\"";
	//extra attributes if the class is a nested class
	if(c->has_enclosing_declarative_region())
	{
		declarative_region_shared_ptr_variant enclosing_declarative_region = c->enclosing_declarative_region();
		if(auto opt_class = utility::get<class_>(&enclosing_declarative_region))
		{
			std::shared_ptr<class_> enclosing_declarative_region = *opt_class;

			class_::access acc = enclosing_declarative_region->member_access(c);
			output << attribute(acc);
		}
	}
	if(!c->complete())
		output << " complete=\"false\"";
	output << ">\n";

	class_ids_[c.get()] = class_id_counter_;
	++class_id_counter_;

	if(!c->base_classes().empty())
	{
		output << indent(indent_level + 1) << "<base_classes>\n";
		for(auto i = c->base_classes().begin(); i != c->base_classes().end(); ++i)
			serialize_base_class
			(
				output,
				*i,
				c->base_class_access(*i),
				c->is_virtual_base_class(*i),
				indent_level + 2
			);
		output << indent(indent_level + 1) << "</base_classes>\n";
	}

	for(auto i = c->nested_classes().begin(); i != c->nested_classes().end(); ++i)
		serialize_class(output, *i, indent_level + 1);

	for(auto i = c->constructors().begin(); i != c->constructors().end(); ++i)
		serialize_constructor(output, *i, indent_level + 1);

	serialize_destructor(output, c->get_destructor(), indent_level + 1);

	for(auto i = c->operator_functions().begin(); i != c->operator_functions().end(); ++i)
		serialize_operator_member_function(output, *i, indent_level + 1);

	for(auto i = c->conversion_functions().begin(); i != c->conversion_functions().end(); ++i)
		serialize_conversion_function(output, *i, indent_level + 1);

	for(auto i = c->simple_functions().begin(); i != c->simple_functions().end(); ++i)
		serialize_simple_member_function(output, *i, indent_level + 1);

	for(auto i = c->variables().begin(); i != c->variables().end(); ++i)
		serialize_variable(output, *i, indent_level + 1);

	output << indent(indent_level) << "</class>\n";
}

void
semantic_graph_serializer::serialize_base_class
(
	std::ostream& output,
	std::shared_ptr<const class_> c,
	const class_::access acc,
	const bool is_virtual,
	const unsigned int indent_level
)
{
	output << indent(indent_level) << "<base_class";
	output << " id=\"c" << class_ids_[c.get()] << "\"";
	output << attribute(acc);
	if(is_virtual)
		output << " virtual=\"true\"";
	output << "/>\n";
}

void
semantic_graph_serializer::serialize_constructor
(
	std::ostream& output,
	std::shared_ptr<const constructor> entity,
	const unsigned int indent_level
)
{
	output << indent(indent_level) << "<constructor";
	if(entity->has_enclosing_declarative_region())
	{
		std::shared_ptr<class_> enclosing_declarative_region = utility::get<class_>(entity->enclosing_declarative_region());

		class_::access acc = enclosing_declarative_region->member_access(entity);
		output << attribute(acc);
	}
	if(entity->is_inline())
		output << " inline=\"true\"";
	if(entity->is_explicit())
		output << " explicit=\"true\"";
	if(!entity->defined())
		output << " defined=\"false\"";
	output << ">\n";

	serialize_function_parameter_list(output, entity->parameters(), indent_level + 1);

	output << indent(indent_level) << "</constructor>\n";
}

void
semantic_graph_serializer::serialize_destructor
(
	std::ostream& output,
	std::shared_ptr<const destructor> entity,
	const unsigned int indent_level
)
{
	output << indent(indent_level) << "<destructor";

	assert(entity->has_enclosing_declarative_region());
	declarative_region_shared_ptr_variant enclosing_declarative_region = entity->enclosing_declarative_region();
	std::shared_ptr<class_> enclosing_class = utility::get<class_>(enclosing_declarative_region);

	class_::access acc = enclosing_class->member_access(entity);
	output << attribute(acc);
	if(entity->is_inline())
		output << " inline=\"true\"";
	if(entity->is_virtual())
		output << " virtual=\"true\"";
	if(entity->is_pure())
		output << " pure=\"true\"";
	if(!entity->defined())
		output << " defined=\"false\"";
	output << ">\n";

	output << indent(indent_level) << "</destructor>\n";
}

void
semantic_graph_serializer::serialize_operator_member_function
(
	std::ostream& output,
	std::shared_ptr<const operator_member_function> entity,
	const unsigned int indent_level
)
{
	output << indent(indent_level) << "<operator_function";
	output << attribute(entity->overloaded_operator());

	assert(entity->has_enclosing_declarative_region());
	declarative_region_shared_ptr_variant enclosing_declarative_region = entity->enclosing_declarative_region();
	std::shared_ptr<class_> enclosing_class = utility::get<class_>(enclosing_declarative_region);

	class_::access acc = enclosing_class->member_access(entity);
	output << attribute(acc);
	if(entity->is_inline())
		output << " inline=\"true\"";
	if(entity->is_const())
		output << " const=\"true\"";
	if(entity->is_volatile())
		output << " volatile=\"true\"";
	if(entity->is_virtual())
		output << " virtual=\"true\"";
	if(entity->is_pure())
		output << " pure=\"true\"";
	if(!entity->defined())
		output << " defined=\"false\"";
	output << ">\n";

	output << indent(indent_level + 1) << "<return_type>\n";
	serialize_type(output, entity->return_type(), indent_level + 2);
	output << indent(indent_level + 1) << "</return_type>\n";

	serialize_function_parameter_list(output, entity->parameters(), indent_level + 1);

	output << indent(indent_level) << "</operator_function>\n";
}

void
semantic_graph_serializer::serialize_conversion_function
(
	std::ostream& output,
	std::shared_ptr<const conversion_function> entity,
	const unsigned int indent_level
)
{
	output << indent(indent_level) << "<conversion_function";

	assert(entity->has_enclosing_declarative_region());
	declarative_region_shared_ptr_variant enclosing_declarative_region = entity->enclosing_declarative_region();
	std::shared_ptr<class_> enclosing_class = utility::get<class_>(enclosing_declarative_region);

	class_::access acc = enclosing_class->member_access(entity);
	output << attribute(acc);
	if(entity->is_inline())
		output << " inline=\"true\"";
	if(entity->is_const())
		output << " const=\"true\"";
	if(entity->is_volatile())
		output << " volatile=\"true\"";
	if(entity->is_virtual())
		output << " virtual=\"true\"";
	if(entity->is_pure())
		output << " pure=\"true\"";
	if(!entity->defined())
		output << " defined=\"false\"";
	output << ">\n";

	output << indent(indent_level + 1) << "<return_type>\n";
	serialize_type(output, entity->return_type(), indent_level + 2);
	output << indent(indent_level + 1) << "</return_type>\n";

	output << indent(indent_level) << "</conversion_function>\n";
}

void
semantic_graph_serializer::serialize_simple_member_function
(
	std::ostream& output,
	std::shared_ptr<const simple_member_function> entity,
	const unsigned int indent_level
)
{
	output << indent(indent_level) << "<simple_function";
	output << " name=\"" << entity->name() << "\"";

	assert(entity->has_enclosing_declarative_region());
	declarative_region_shared_ptr_variant enclosing_declarative_region = entity->enclosing_declarative_region();
	std::shared_ptr<class_> enclosing_class = utility::get<class_>(enclosing_declarative_region);

	class_::access acc = enclosing_class->member_access(entity);
	output << attribute(acc);
	if(entity->is_inline())
		output << " inline=\"true\"";
	if(entity->is_static())
		output << " static=\"true\"";
	if(entity->is_const())
		output << " const=\"true\"";
	if(entity->is_volatile())
		output << " volatile=\"true\"";
	if(entity->is_virtual())
		output << " virtual=\"true\"";
	if(entity->is_pure())
		output << " pure=\"true\"";
	if(!entity->defined())
		output << " defined=\"false\"";
	output << ">\n";

	output << indent(indent_level + 1) << "<return_type>\n";
	serialize_type(output, entity->return_type(), indent_level + 2);
	output << indent(indent_level + 1) << "</return_type>\n";

	serialize_function_parameter_list(output, entity->parameters(), indent_level + 1);

	output << indent(indent_level) << "</simple_function>\n";
}

void
semantic_graph_serializer::serialize_operator_function
(
	std::ostream& output,
	std::shared_ptr<const operator_function> entity,
	const unsigned int indent_level
)
{
	output << indent(indent_level) << "<operator_function";
	output << attribute(entity->overloaded_operator());
	if(entity->is_inline())
		output << " inline=\"true\"";
	if(entity->is_static())
		output << " static=\"true\"";
	if(!entity->defined())
		output << " defined=\"false\"";
	output << ">\n";

	output << indent(indent_level + 1) << "<return_type>\n";
	serialize_type(output, entity->return_type(), indent_level + 2);
	output << indent(indent_level + 1) << "</return_type>\n";

	serialize_function_parameter_list(output, entity->parameters(), indent_level + 1);

	output << indent(indent_level) << "</operator_function>\n";
}

void
semantic_graph_serializer::serialize_simple_function
(
	std::ostream& output,
	std::shared_ptr<const simple_function> entity,
	const unsigned int indent_level
)
{
	output << indent(indent_level) << "<simple_function";
	output << " name=\"" << entity->name() << "\"";
	if(entity->is_static())
		output << " static=\"true\"";
	if(entity->is_inline())
		output << " inline=\"true\"";
	if(!entity->defined())
		output << " defined=\"false\"";
	output << ">\n";

	output << indent(indent_level + 1) << "<return_type>\n";
	serialize_type(output, entity->return_type(), indent_level + 2);
	output << indent(indent_level + 1) << "</return_type>\n";

	serialize_function_parameter_list(output, entity->parameters(), indent_level + 1);

	output << indent(indent_level) << "</simple_function>\n";
}

void
semantic_graph_serializer::serialize_function_parameter_list
(
	std::ostream& output,
	const function_parameter_list& entity,
	const unsigned int indent_level
)
{
	if(!entity.empty())
	{
		output << indent(indent_level) << "<parameters>\n";
		for(auto i = entity.begin(); i != entity.end(); ++i)
		{
			serialize_function_parameter(output, *i, indent_level + 1);
		}
		output << indent(indent_level) << "</parameters>\n";
	}
}

void
semantic_graph_serializer::serialize_function_parameter
(
	std::ostream& output,
	const std::shared_ptr<const function_parameter> p,
	const unsigned int indent_level
)
{
	output << indent(indent_level) << "<parameter";
	if(!p->name().empty())
		output << " name=\"" << p->name() << "\"";
	output << ">\n";
	output << indent(indent_level + 1) << "<type>\n";
	serialize_type(output, p->type(), indent_level + 2);
	output << indent(indent_level + 1) << "</type>\n";
	output << indent(indent_level) << "</parameter>\n";
}

void
semantic_graph_serializer::serialize_variable
(
	std::ostream& output,
	std::shared_ptr<const variable> entity,
	const unsigned int indent_level
)
{
	output << indent(indent_level) << "<variable";
	output << " name=\"" << entity->name() << "\"";
	//extra attributes if the function is a class member function
	if(entity->has_enclosing_declarative_region())
	{
		declarative_region_shared_ptr_variant enclosing_declarative_region = entity->enclosing_declarative_region();
		if(auto opt_class = utility::get<class_>(&enclosing_declarative_region))
		{
			std::shared_ptr<class_> enclosing_declarative_region = *opt_class;

			class_::access acc = enclosing_declarative_region->member_access(entity);
			output << attribute(acc);
			if(enclosing_declarative_region->is_mutable_member_variable(entity))
				output << " mutable=\"true\"";
		}
	}
	if(entity->is_static())
		output << " static=\"true\"";
	output << ">\n";
	output << indent(indent_level + 1) << "<type>\n";
	serialize_type(output, entity->type(), indent_level + 2);
	output << indent(indent_level + 1) << "</type>\n";
	output << indent(indent_level) << "</variable>\n";
}

void
semantic_graph_serializer::serialize_typedef
(
	std::ostream& output,
	std::shared_ptr<const typedef_> entity,
	const unsigned int indent_level
)
{
	output << indent(indent_level) << "<typedef";
	output << " name=\"" << entity->name() << "\"";
	//extra attributes if the typedef is member of a class
	if(entity->has_enclosing_declarative_region())
	{
		declarative_region_shared_ptr_variant enclosing_declarative_region = entity->enclosing_declarative_region();
		if(auto opt_class = utility::get<class_>(&enclosing_declarative_region))
		{
			std::shared_ptr<class_> enclosing_declarative_region = *opt_class;

			class_::access acc = enclosing_declarative_region->member_access(entity);
			output << attribute(acc);
		}
	}
	output << ">\n";
	output << indent(indent_level + 1) << "<type>\n";
	serialize_type(output, entity->type(), indent_level + 2);
	output << indent(indent_level + 1) << "</type>\n";
	output << indent(indent_level) << "</typedef>\n";
}

void
semantic_graph_serializer::serialize_namespace_alias
(
	std::ostream& output,
	std::shared_ptr<const namespace_alias> entity,
	const unsigned int indent_level
)
{
	output << indent(indent_level) << "<namespace_alias";
	output << " name=\"" << entity->name() << "\"";
	output << " id=\"n" << namespace_ids_[entity->referred_namespace().get()] << "\"";
	output << "/>\n";
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
serialize_semantic_graph
(
	std::shared_ptr<const semantic_graph> graph,
	std::ostream& output
)
{
	semantic_graph_serializer serializer;
	serializer.serialize_namespace(output, graph);
}

} //namespace cpp2xml

