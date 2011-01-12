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

semantic_graph_serializer::semantic_graph_serializer(std::ostream& output):
	output_(output),
	namespace_id_counter_(0),
	class_id_counter_(0)
{
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
		output_ << indent(indent_level) << "<class id=\"c" << class_ids_[*opt_type] << "\"/>\n";
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
	std::shared_ptr<const namespace_> n,
	const unsigned int indent_level
)
{
	output_ << indent(indent_level) << "<namespace";
	if(n->name() != "")
	{
		output_ << " name=\"" << n->name() << "\"";
	}
	output_ << " id=\"n" << namespace_id_counter_ << "\"";
	output_ << ">\n";

	namespace_ids_[n.get()] = namespace_id_counter_;
	++namespace_id_counter_;

	for(auto i = n->namespace_aliases().begin(); i != n->namespace_aliases().end(); ++i)
		serialize_namespace_alias(*i, indent_level + 1);

	for(auto i = n->namespaces().begin(); i != n->namespaces().end(); ++i)
		serialize_namespace(*i, indent_level + 1);

	for(auto i = n->classes().begin(); i != n->classes().end(); ++i)
		serialize_class(*i, indent_level + 1);

	for(auto i = n->typedefs().begin(); i != n->typedefs().end(); ++i)
		serialize_typedef(*i, indent_level + 1);

	for(auto i = n->simple_functions().begin(); i != n->simple_functions().end(); ++i)
		serialize_simple_function(*i, indent_level + 1);

	for(auto i = n->operator_functions().begin(); i != n->operator_functions().end(); ++i)
		serialize_operator_function(*i, indent_level + 1);

	for(auto i = n->variables().begin(); i != n->variables().end(); ++i)
		serialize_variable(*i, indent_level + 1);

	output_ << indent(indent_level) << "</namespace>\n";
}

void
semantic_graph_serializer::serialize_class
(
	std::shared_ptr<const class_> c,
	const unsigned int indent_level
)
{
	output_ << indent(indent_level) << "<class";
	output_ << " name=\"" << c->name() << "\"";
	output_ << " id=\"c" << class_id_counter_ << "\"";
	//extra attributes if the class is a nested class
	if(c->has_enclosing_declarative_region())
	{
		declarative_region_shared_ptr_variant enclosing_declarative_region = c->enclosing_declarative_region();
		if(auto opt_class = utility::get<class_>(&enclosing_declarative_region))
		{
			std::shared_ptr<class_> enclosing_declarative_region = *opt_class;

			class_::access acc = enclosing_declarative_region->member_access(c);
			output_ << attribute(acc);
		}
	}
	if(!c->complete())
		output_ << " complete=\"false\"";
	output_ << ">\n";

	class_ids_[c.get()] = class_id_counter_;
	++class_id_counter_;

	if(!c->base_classes().empty())
	{
		output_ << indent(indent_level + 1) << "<base_classes>\n";
		for(auto i = c->base_classes().begin(); i != c->base_classes().end(); ++i)
			serialize_base_class
			(
				*i,
				c->base_class_access(*i),
				c->is_virtual_base_class(*i),
				indent_level + 2
			);
		output_ << indent(indent_level + 1) << "</base_classes>\n";
	}

	for(auto i = c->nested_classes().begin(); i != c->nested_classes().end(); ++i)
		serialize_class(*i, indent_level + 1);

	for(auto i = c->typedefs().begin(); i != c->typedefs().end(); ++i)
		serialize_typedef(*i, indent_level + 1);

	for(auto i = c->constructors().begin(); i != c->constructors().end(); ++i)
		serialize_constructor(*i, indent_level + 1);

	serialize_destructor(c->get_destructor(), indent_level + 1);

	for(auto i = c->operator_functions().begin(); i != c->operator_functions().end(); ++i)
		serialize_operator_member_function(*i, indent_level + 1);

	for(auto i = c->conversion_functions().begin(); i != c->conversion_functions().end(); ++i)
		serialize_conversion_function(*i, indent_level + 1);

	for(auto i = c->simple_functions().begin(); i != c->simple_functions().end(); ++i)
		serialize_simple_member_function(*i, indent_level + 1);

	for(auto i = c->variables().begin(); i != c->variables().end(); ++i)
		serialize_variable(*i, indent_level + 1);

	output_ << indent(indent_level) << "</class>\n";
}

void
semantic_graph_serializer::serialize_base_class
(
	std::shared_ptr<const class_> c,
	const class_::access acc,
	const bool is_virtual,
	const unsigned int indent_level
)
{
	output_ << indent(indent_level) << "<base_class";
	output_ << " id=\"c" << class_ids_[c.get()] << "\"";
	output_ << attribute(acc);
	if(is_virtual)
		output_ << " virtual=\"true\"";
	output_ << "/>\n";
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
	if(entity.parent_class())
		output_ << " class_id=\"c" << class_ids_[entity.parent_class()] << "\"";
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
	output_ << " id=\"n" << namespace_ids_[entity->referred_namespace().get()] << "\"";
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
serialize_semantic_graph
(
	std::shared_ptr<const semantic_graph> graph,
	std::ostream& output
)
{
	semantic_graph_serializer serializer(output);
	serializer.serialize_namespace(graph);
}

} //namespace cpp2xml

