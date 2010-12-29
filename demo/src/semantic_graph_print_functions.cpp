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

#include "semantic_graph_print_functions.hpp"
#include <scalpel/utility/variant.hpp>
#include <vector>
#include <sstream>

namespace semantic_graph_print_functions
{

void
print_type
(
	const semantic_entities::type_shared_ptr_variant& n,
	const unsigned int indent_level
)
{
	if(auto opt_type = scalpel::utility::get<fundamental_type>(&n))
	{
		std::cout << indent(indent_level) << "<fundamental_type type=\"";
		print_fundamental_type(*opt_type);
	   	std::cout << "\"/>\n";
	}
	else if(auto opt_type = scalpel::utility::get<const_>(&n))
	{
		std::cout << indent(indent_level) << "<const>\n";
		print_type((*opt_type).qualified_type(), indent_level + 1);
		std::cout << indent(indent_level) << "</const>\n";
	}
	else if(auto opt_type = scalpel::utility::get<volatile_>(&n))
	{
		std::cout << indent(indent_level) << "<volatile>\n";
		print_type((*opt_type).qualified_type(), indent_level + 1);
		std::cout << indent(indent_level) << "</volatile>\n";
	}
	else if(auto opt_type = scalpel::utility::get<pointer>(&n))
	{
		std::cout << indent(indent_level) << "<pointer>\n";
		print_type((*opt_type).qualified_type(), indent_level + 1);
		std::cout << indent(indent_level) << "</pointer>\n";
	}
	else if(auto opt_type = scalpel::utility::get<reference>(&n))
	{
		std::cout << indent(indent_level) << "<reference>\n";
		print_type((*opt_type).qualified_type(), indent_level + 1);
		std::cout << indent(indent_level) << "</reference>\n";
	}
	else if(auto opt_type = scalpel::utility::get<array>(&n))
	{
		std::cout << indent(indent_level) << "<array size=\"" << (*opt_type).size() << "\">\n";
		print_type((*opt_type).qualified_type(), indent_level + 1);
		std::cout << indent(indent_level) << "</array>\n";
	}
	else if(auto opt_type = scalpel::utility::get<std::shared_ptr<const class_>>(&n))
	{
		std::cout << indent(indent_level) << "<class id=\"" << *opt_type << "\"/>\n";
	}
}

void
print_fundamental_type(const fundamental_type type)
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
			std::cout << type_str;
			break;
		}
	}
}

void
print_namespace
(
	std::shared_ptr<const namespace_> n,
	const unsigned int indent_level
)
{
	std::cout << indent(indent_level) << "<namespace";
	if(n->name() != "")
	{
		std::cout << " name=\"" << n->name() << "\"";
	}
	std::cout << " id=\"" << n << "\"";
	std::cout << ">\n";

	for(auto i = n->namespace_aliases().begin(); i != n->namespace_aliases().end(); ++i)
		print_namespace_alias(*i, indent_level + 1);

	for(auto i = n->namespaces().begin(); i != n->namespaces().end(); ++i)
		print_namespace(*i, indent_level + 1);

	for(auto i = n->classes().begin(); i != n->classes().end(); ++i)
		print_class(*i, indent_level + 1);

	for(auto i = n->typedefs().begin(); i != n->typedefs().end(); ++i)
		print_typedef(*i, indent_level + 1);

	for(auto i = n->simple_functions().begin(); i != n->simple_functions().end(); ++i)
		print_simple_function(*i, indent_level + 1);

	for(auto i = n->operator_functions().begin(); i != n->operator_functions().end(); ++i)
		print_operator_function(*i, indent_level + 1);

	for(auto i = n->variables().begin(); i != n->variables().end(); ++i)
		print_variable(*i, indent_level + 1);

	std::cout << indent(indent_level) << "</namespace>\n";
}

void
print_class
(
	std::shared_ptr<const class_> c,
	const unsigned int indent_level
)
{
	std::cout << indent(indent_level) << "<class";
	std::cout << " name=\"" << c->name() << "\"";
	std::cout << " id=\"" << c << "\"";
	//extra attributes if the class is a nested class
	if(c->has_enclosing_declarative_region())
	{
		declarative_region_shared_ptr_variant enclosing_declarative_region = c->enclosing_declarative_region();
		if(auto opt_class = utility::get<class_>(&enclosing_declarative_region))
		{
			std::shared_ptr<class_> enclosing_declarative_region = *opt_class;

			class_::access acc = enclosing_declarative_region->member_access(c);
			std::cout << attribute(acc);
		}
	}
	std::cout << ">\n";

	if(!c->base_classes().empty())
	{
		std::cout << indent(indent_level + 1) << "<base_classes>\n";
		for(auto i = c->base_classes().begin(); i != c->base_classes().end(); ++i)
			print_base_class
			(
				*i,
				c->base_class_access(*i),
				c->is_virtual_base_class(*i),
				indent_level + 2
			);
		std::cout << indent(indent_level + 1) << "</base_classes>\n";
	}

	for(auto i = c->nested_classes().begin(); i != c->nested_classes().end(); ++i)
		print_class(*i, indent_level + 1);

	for(auto i = c->constructors().begin(); i != c->constructors().end(); ++i)
		print_constructor(*i, indent_level + 1);

	print_destructor(c->get_destructor(), indent_level + 1);

	for(auto i = c->operator_functions().begin(); i != c->operator_functions().end(); ++i)
		print_operator_member_function(*i, indent_level + 1);

	for(auto i = c->conversion_functions().begin(); i != c->conversion_functions().end(); ++i)
		print_conversion_function(*i, indent_level + 1);

	for(auto i = c->simple_functions().begin(); i != c->simple_functions().end(); ++i)
		print_simple_member_function(*i, indent_level + 1);

	for(auto i = c->variables().begin(); i != c->variables().end(); ++i)
		print_variable(*i, indent_level + 1);

	std::cout << indent(indent_level) << "</class>\n";
}

void
print_base_class
(
	std::shared_ptr<const class_> c,
	const class_::access acc,
	const bool is_virtual,
	const unsigned int indent_level
)
{
	std::cout << indent(indent_level) << "<base_class";
	std::cout << " id=\"" << c << "\"";
	std::cout << attribute(acc);
	if(is_virtual)
		std::cout << " virtual=\"true\"";
	std::cout << "/>\n";
}

void
print_constructor
(
	std::shared_ptr<const constructor> entity,
	const unsigned int indent_level
)
{
	std::cout << indent(indent_level) << "<constructor";
	if(entity->has_enclosing_declarative_region())
	{
		std::shared_ptr<class_> enclosing_declarative_region = utility::get<class_>(entity->enclosing_declarative_region());

		class_::access acc = enclosing_declarative_region->member_access(entity);
		std::cout << attribute(acc);
	}
	if(entity->is_inline())
		std::cout << " inline=\"true\"";
	if(entity->is_explicit())
		std::cout << " explicit=\"true\"";
	if(!entity->defined())
		std::cout << " defined=\"false\"";
	std::cout << ">\n";

	print_function_parameter_list(entity->parameters(), indent_level + 1);

	std::cout << indent(indent_level) << "</constructor>\n";
}

void
print_destructor
(
	std::shared_ptr<const destructor> entity,
	const unsigned int indent_level
)
{
	std::cout << indent(indent_level) << "<destructor";

	assert(entity->has_enclosing_declarative_region());
	declarative_region_shared_ptr_variant enclosing_declarative_region = entity->enclosing_declarative_region();
	std::shared_ptr<class_> enclosing_class = utility::get<class_>(enclosing_declarative_region);

	class_::access acc = enclosing_class->member_access(entity);
	std::cout << attribute(acc);
	if(entity->is_inline())
		std::cout << " inline=\"true\"";
	if(entity->is_virtual())
		std::cout << " virtual=\"true\"";
	if(entity->is_pure())
		std::cout << " pure=\"true\"";
	if(!entity->defined())
		std::cout << " defined=\"false\"";
	std::cout << ">\n";

	std::cout << indent(indent_level) << "</destructor>\n";
}

void
print_operator_member_function
(
	std::shared_ptr<const operator_member_function> entity,
	const unsigned int indent_level
)
{
	std::cout << indent(indent_level) << "<operator_function";
	std::cout << attribute(entity->overloaded_operator());

	assert(entity->has_enclosing_declarative_region());
	declarative_region_shared_ptr_variant enclosing_declarative_region = entity->enclosing_declarative_region();
	std::shared_ptr<class_> enclosing_class = utility::get<class_>(enclosing_declarative_region);

	class_::access acc = enclosing_class->member_access(entity);
	std::cout << attribute(acc);
	if(entity->is_inline())
		std::cout << " inline=\"true\"";
	if(entity->is_const())
		std::cout << " const=\"true\"";
	if(entity->is_volatile())
		std::cout << " volatile=\"true\"";
	if(entity->is_virtual())
		std::cout << " virtual=\"true\"";
	if(entity->is_pure())
		std::cout << " pure=\"true\"";
	if(!entity->defined())
		std::cout << " defined=\"false\"";
	std::cout << ">\n";

	std::cout << indent(indent_level + 1) << "<return_type>\n";
	print_type(entity->return_type(), indent_level + 2);
	std::cout << indent(indent_level + 1) << "</return_type>\n";

	print_function_parameter_list(entity->parameters(), indent_level + 1);

	std::cout << indent(indent_level) << "</operator_function>\n";
}

void
print_conversion_function
(
	std::shared_ptr<const conversion_function> entity,
	const unsigned int indent_level
)
{
	std::cout << indent(indent_level) << "<conversion_function";

	assert(entity->has_enclosing_declarative_region());
	declarative_region_shared_ptr_variant enclosing_declarative_region = entity->enclosing_declarative_region();
	std::shared_ptr<class_> enclosing_class = utility::get<class_>(enclosing_declarative_region);

	class_::access acc = enclosing_class->member_access(entity);
	std::cout << attribute(acc);
	if(entity->is_inline())
		std::cout << " inline=\"true\"";
	if(entity->is_const())
		std::cout << " const=\"true\"";
	if(entity->is_volatile())
		std::cout << " volatile=\"true\"";
	if(entity->is_virtual())
		std::cout << " virtual=\"true\"";
	if(entity->is_pure())
		std::cout << " pure=\"true\"";
	if(!entity->defined())
		std::cout << " defined=\"false\"";
	std::cout << ">\n";

	std::cout << indent(indent_level + 1) << "<return_type>\n";
	print_type(entity->return_type(), indent_level + 2);
	std::cout << indent(indent_level + 1) << "</return_type>\n";

	std::cout << indent(indent_level) << "</conversion_function>\n";
}

void
print_simple_member_function
(
	std::shared_ptr<const simple_member_function> entity,
	const unsigned int indent_level
)
{
	std::cout << indent(indent_level) << "<simple_function";
	std::cout << " name=\"" << entity->name() << "\"";

	assert(entity->has_enclosing_declarative_region());
	declarative_region_shared_ptr_variant enclosing_declarative_region = entity->enclosing_declarative_region();
	std::shared_ptr<class_> enclosing_class = utility::get<class_>(enclosing_declarative_region);

	class_::access acc = enclosing_class->member_access(entity);
	std::cout << attribute(acc);
	if(entity->is_inline())
		std::cout << " inline=\"true\"";
	if(entity->is_static())
		std::cout << " static=\"true\"";
	if(entity->is_const())
		std::cout << " const=\"true\"";
	if(entity->is_volatile())
		std::cout << " volatile=\"true\"";
	if(entity->is_virtual())
		std::cout << " virtual=\"true\"";
	if(entity->is_pure())
		std::cout << " pure=\"true\"";
	if(!entity->defined())
		std::cout << " defined=\"false\"";
	std::cout << ">\n";

	std::cout << indent(indent_level + 1) << "<return_type>\n";
	print_type(entity->return_type(), indent_level + 2);
	std::cout << indent(indent_level + 1) << "</return_type>\n";

	print_function_parameter_list(entity->parameters(), indent_level + 1);

	std::cout << indent(indent_level) << "</simple_function>\n";
}

void
print_operator_function
(
	std::shared_ptr<const operator_function> entity,
	const unsigned int indent_level
)
{
	std::cout << indent(indent_level) << "<operator_function";
	std::cout << attribute(entity->overloaded_operator());
	if(entity->is_inline())
		std::cout << " inline=\"true\"";
	if(entity->is_static())
		std::cout << " static=\"true\"";
	if(!entity->defined())
		std::cout << " defined=\"false\"";
	std::cout << ">\n";

	std::cout << indent(indent_level + 1) << "<return_type>\n";
	print_type(entity->return_type(), indent_level + 2);
	std::cout << indent(indent_level + 1) << "</return_type>\n";

	print_function_parameter_list(entity->parameters(), indent_level + 1);

	std::cout << indent(indent_level) << "</operator_function>\n";
}

void
print_simple_function
(
	std::shared_ptr<const simple_function> entity,
	const unsigned int indent_level
)
{
	std::cout << indent(indent_level) << "<simple_function";
	std::cout << " name=\"" << entity->name() << "\"";
	if(entity->is_static())
		std::cout << " static=\"true\"";
	if(entity->is_inline())
		std::cout << " inline=\"true\"";
	if(!entity->defined())
		std::cout << " defined=\"false\"";
	std::cout << ">\n";

	std::cout << indent(indent_level + 1) << "<return_type>\n";
	print_type(entity->return_type(), indent_level + 2);
	std::cout << indent(indent_level + 1) << "</return_type>\n";

	print_function_parameter_list(entity->parameters(), indent_level + 1);

	std::cout << indent(indent_level) << "</simple_function>\n";
}

void
print_function_parameter_list
(
	const function_parameter_list& entity,
	const unsigned int indent_level
)
{
	if(!entity.empty())
	{
		std::cout << indent(indent_level) << "<parameters>\n";
		for(auto i = entity.begin(); i != entity.end(); ++i)
		{
			print_function_parameter(*i, indent_level + 1);
		}
		std::cout << indent(indent_level) << "</parameters>\n";
	}
}

void
print_function_parameter
(
	const std::shared_ptr<const function_parameter> p,
	const unsigned int indent_level
)
{
	std::cout << indent(indent_level) << "<parameter";
	if(!p->name().empty())
		std::cout << " name=\"" << p->name() << "\"";
	std::cout << ">\n";
	std::cout << indent(indent_level + 1) << "<type>\n";
	print_type(p->type(), indent_level + 2);
	std::cout << indent(indent_level + 1) << "</type>\n";
	std::cout << indent(indent_level) << "</parameter>\n";
}

void
print_variable
(
	std::shared_ptr<const variable> entity,
	const unsigned int indent_level
)
{
	std::cout << indent(indent_level) << "<variable";
	std::cout << " name=\"" << entity->name() << "\"";
	//extra attributes if the function is a class member function
	if(entity->has_enclosing_declarative_region())
	{
		declarative_region_shared_ptr_variant enclosing_declarative_region = entity->enclosing_declarative_region();
		if(auto opt_class = utility::get<class_>(&enclosing_declarative_region))
		{
			std::shared_ptr<class_> enclosing_declarative_region = *opt_class;

			class_::access acc = enclosing_declarative_region->member_access(entity);
			std::cout << attribute(acc);
			if(enclosing_declarative_region->is_mutable_member_variable(entity))
				std::cout << " mutable=\"true\"";
		}
	}
	if(entity->is_static())
		std::cout << " static=\"true\"";
	std::cout << ">\n";
	std::cout << indent(indent_level + 1) << "<type>\n";
	print_type(entity->type(), indent_level + 2);
	std::cout << indent(indent_level + 1) << "</type>\n";
	std::cout << indent(indent_level) << "</variable>\n";
}

void
print_typedef
(
	std::shared_ptr<const typedef_> entity,
	const unsigned int indent_level
)
{
	std::cout << indent(indent_level) << "<typedef";
	std::cout << " name=\"" << entity->name() << "\"";
	//extra attributes if the typedef is member of a class
	if(entity->has_enclosing_declarative_region())
	{
		declarative_region_shared_ptr_variant enclosing_declarative_region = entity->enclosing_declarative_region();
		if(auto opt_class = utility::get<class_>(&enclosing_declarative_region))
		{
			std::shared_ptr<class_> enclosing_declarative_region = *opt_class;

			class_::access acc = enclosing_declarative_region->member_access(entity);
			std::cout << attribute(acc);
		}
	}
	std::cout << ">\n";
	std::cout << indent(indent_level + 1) << "<type>\n";
	print_type(entity->type(), indent_level + 2);
	std::cout << indent(indent_level + 1) << "</type>\n";
	std::cout << indent(indent_level) << "</typedef>\n";
}

void
print_namespace_alias
(
	std::shared_ptr<const namespace_alias> entity,
	const unsigned int indent_level
)
{
	std::cout << indent(indent_level) << "<namespace_alias";
	std::cout << " name=\"" << entity->name() << "\"";
	std::cout << " id=\"" << entity->referred_namespace() << "\"";
	std::cout << "/>\n";
}

std::string
attribute(const class_::access& a)
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
attribute(const semantic_entities::overloadable_operator op)
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

} //namespace semantic_graph_print_functions

