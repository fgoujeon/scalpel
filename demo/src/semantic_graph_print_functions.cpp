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
print
(
	std::shared_ptr<const type> n,
	const unsigned int indent_level
)
{
	if(std::shared_ptr<const built_in_type> t = std::dynamic_pointer_cast<const built_in_type>(n))
	{
		std::cout << indent(indent_level) << "<built_in_type type=\"";
		print(t);
	   	std::cout << "\"/>\n";
	}
	else if(std::shared_ptr<const const_> t = std::dynamic_pointer_cast<const const_>(n))
	{
		std::cout << indent(indent_level) << "<const>\n";
		print(t->decorated_type(), indent_level + 1);
		std::cout << indent(indent_level) << "</const>\n";
	}
	else if(std::shared_ptr<const volatile_> t = std::dynamic_pointer_cast<const volatile_>(n))
	{
		std::cout << indent(indent_level) << "<volatile>\n";
		print(t->decorated_type(), indent_level + 1);
		std::cout << indent(indent_level) << "</volatile>\n";
	}
	else if(std::shared_ptr<const pointer> t = std::dynamic_pointer_cast<const pointer>(n))
	{
		std::cout << indent(indent_level) << "<pointer>\n";
		print(t->decorated_type(), indent_level + 1);
		std::cout << indent(indent_level) << "</pointer>\n";
	}
	else if(std::shared_ptr<const reference> t = std::dynamic_pointer_cast<const reference>(n))
	{
		std::cout << indent(indent_level) << "<reference>\n";
		print(t->decorated_type(), indent_level + 1);
		std::cout << indent(indent_level) << "</reference>\n";
	}
	else if(std::shared_ptr<const array> t = std::dynamic_pointer_cast<const array>(n))
	{
		std::cout << indent(indent_level) << "<array size=\"" << t->size() << "\">\n";
		print(t->decorated_type(), indent_level + 1);
		std::cout << indent(indent_level) << "</array>\n";
	}
	else if(std::shared_ptr<const class_> t = std::dynamic_pointer_cast<const class_>(n))
	{
		std::cout << indent(indent_level) << "<class id=\"" << t << "\"/>\n";
	}
}

void
print
(
	std::shared_ptr<const built_in_type> built_in_t
)
{
	std::vector<std::pair<std::shared_ptr<const built_in_type>, const char*>> built_in_types_table =
	{
		{built_in_type_shared_ptrs::bool_, "bool"},
		{built_in_type_shared_ptrs::char_, "char"},
		{built_in_type_shared_ptrs::double_, "double"},
		{built_in_type_shared_ptrs::float_, "float"},
		{built_in_type_shared_ptrs::int_, "int"},
		{built_in_type_shared_ptrs::long_double, "long double"},
		{built_in_type_shared_ptrs::long_int, "long int"},
		{built_in_type_shared_ptrs::long_long_int, "long long int"},
		{built_in_type_shared_ptrs::short_int, "short int"},
		{built_in_type_shared_ptrs::unsigned_char, "unsigned char"},
		{built_in_type_shared_ptrs::unsigned_int, "unsigned int"},
		{built_in_type_shared_ptrs::unsigned_long_int, "unsigned long int"},
		{built_in_type_shared_ptrs::unsigned_long_long_int, "unsigned long long int"},
		{built_in_type_shared_ptrs::unsigned_short_int, "unsigned short int"},
		{built_in_type_shared_ptrs::void_, "void"},
		{built_in_type_shared_ptrs::wchar_t_, "wchar_t"}
	};

	for(auto i = built_in_types_table.begin(); i != built_in_types_table.end(); ++i)
	{
		auto pair = *i;
		std::shared_ptr<const built_in_type> t = pair.first;
		const char* type_str = pair.second;

		if(t == built_in_t)
		{
			std::cout << type_str;
			break;
		}
	}
}

void
print
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
	std::cout << ">\n";

	for(auto i = n->namespaces().begin(); i != n->namespaces().end(); ++i)
		print(*i, indent_level + 1);

	for(auto i = n->classes().begin(); i != n->classes().end(); ++i)
		print(*i, indent_level + 1);

	for(auto i = n->simple_functions().begin(); i != n->simple_functions().end(); ++i)
		print(*i, indent_level + 1);

	for(auto i = n->operator_functions().begin(); i != n->operator_functions().end(); ++i)
		print(*i, indent_level + 1);

	for(auto i = n->variables().begin(); i != n->variables().end(); ++i)
		print(*i, indent_level + 1);

	std::cout << indent(indent_level) << "</namespace>\n";
}

void
print
(
	std::shared_ptr<const class_> c,
	const unsigned int indent_level
)
{
	std::cout << indent(indent_level) << "<class";
	std::cout << " name=\"" << c->name() << "\"";
	std::cout << " id=\"" << c << "\"";
	//extra attributes if the class is a nested class
	if(c->has_declarative_region())
	{
		declarative_region_shared_ptr_variant declarative_region = c->declarative_region();
		if(auto opt_class = utility::get<std::shared_ptr<class_>>(&declarative_region))
		{
			std::shared_ptr<class_> declarative_region = *opt_class;

			class_::access acc = declarative_region->member_access(c);
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
		print(*i, indent_level + 1);

	for(auto i = c->constructors().begin(); i != c->constructors().end(); ++i)
		print(*i, indent_level + 1);

	print(c->get_destructor(), indent_level + 1);

	for(auto i = c->simple_functions().begin(); i != c->simple_functions().end(); ++i)
		print(*i, indent_level + 1);

	for(auto i = c->operator_functions().begin(); i != c->operator_functions().end(); ++i)
		print(*i, indent_level + 1);

	for(auto i = c->conversion_functions().begin(); i != c->conversion_functions().end(); ++i)
		print(*i, indent_level + 1);

	for(auto i = c->variables().begin(); i != c->variables().end(); ++i)
		print(*i, indent_level + 1);

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
print
(
	std::shared_ptr<const class_::constructor> entity,
	const unsigned int indent_level
)
{
	std::cout << indent(indent_level) << "<constructor";
	if(entity->has_declarative_region())
	{
		std::shared_ptr<class_> declarative_region = utility::get<std::shared_ptr<class_>>(entity->declarative_region());

		class_::access acc = declarative_region->member_access(entity);
		std::cout << attribute(acc);
	}
	if(entity->inline_specified())
		std::cout << " inline=\"true\"";
	if(entity->explicit_specified())
		std::cout << " explicit=\"true\"";
	std::cout << ">\n";

	const class_::constructor::parameters_t& parameters = entity->parameters();
	if(!parameters.empty())
	{
		std::cout << indent(indent_level + 1) << "<parameters>\n";
		for(auto i = parameters.begin(); i != parameters.end(); ++i)
		{
			print(*i, indent_level + 2);
		}
		std::cout << indent(indent_level + 1) << "</parameters>\n";
	}

	std::cout << indent(indent_level) << "</constructor>\n";
}

void
print
(
	std::shared_ptr<const class_::destructor> entity,
	const unsigned int indent_level
)
{
	std::cout << indent(indent_level) << "<destructor";
	if(entity->has_declarative_region())
	{
		std::shared_ptr<class_> declarative_region = utility::get<std::shared_ptr<class_>>(entity->declarative_region());

		class_::access acc = declarative_region->member_access(entity);
		std::cout << attribute(acc);
		if(declarative_region->is_virtual_member_function(entity))
			std::cout << " virtual=\"true\"";
		if(declarative_region->is_pure_member_function(entity))
			std::cout << " pure=\"true\"";
	}
	if(entity->inline_specified())
		std::cout << " inline=\"true\"";
	std::cout << ">\n";

	std::cout << indent(indent_level) << "</destructor>\n";
}

void
print
(
	std::shared_ptr<const simple_function> entity,
	const unsigned int indent_level
)
{
	std::cout << indent(indent_level) << "<simple_function";
	std::cout << " name=\"" << entity->name() << "\"";
	//extra attributes if the function is a class member function
	if(entity->has_declarative_region())
	{
		declarative_region_shared_ptr_variant declarative_region = entity->declarative_region();
		if(auto opt_class = utility::get<std::shared_ptr<class_>>(&declarative_region))
		{
			std::shared_ptr<class_> declarative_region = *opt_class;

			class_::access acc = declarative_region->member_access(entity);
			std::cout << attribute(acc);

			if(declarative_region->is_const_member_function(entity))
				std::cout << " const=\"true\"";
			if(declarative_region->is_volatile_member_function(entity))
				std::cout << " volatile=\"true\"";
			if(declarative_region->is_virtual_member_function(entity))
				std::cout << " virtual=\"true\"";
			if(declarative_region->is_pure_member_function(entity))
				std::cout << " pure=\"true\"";
		}
	}
	if(entity->static_specified())
		std::cout << " static=\"true\"";
	if(entity->inline_specified())
		std::cout << " inline=\"true\"";
	if(!entity->defined())
		std::cout << " defined=\"false\"";
	std::cout << ">\n";

	std::cout << indent(indent_level + 1) << "<return_type>\n";
	print(entity->return_type(), indent_level + 2);
	std::cout << indent(indent_level + 1) << "</return_type>\n";

	const std::list<simple_function::parameter>& parameters = entity->parameters();
	if(!parameters.empty())
	{
		std::cout << indent(indent_level + 1) << "<parameters>\n";
		for(auto i = parameters.begin(); i != parameters.end(); ++i)
		{
			print(*i, indent_level + 2);
		}
		std::cout << indent(indent_level + 1) << "</parameters>\n";
	}

	std::cout << indent(indent_level) << "</simple_function>\n";
}

void
print
(
	std::shared_ptr<const operator_function> entity,
	const unsigned int indent_level
)
{
	std::cout << indent(indent_level) << "<operator_function";
	std::cout << attribute(entity->get_operator());
	//extra attributes if the function is a class member function
	if(entity->has_declarative_region())
	{
		declarative_region_shared_ptr_variant declarative_region = entity->declarative_region();
		if(auto opt_class = utility::get<std::shared_ptr<class_>>(&declarative_region))
		{
			std::shared_ptr<class_> declarative_region = *opt_class;

			class_::access acc = declarative_region->member_access(entity);
			std::cout << attribute(acc);

			if(declarative_region->is_const_member_function(entity))
				std::cout << " const=\"true\"";
			if(declarative_region->is_volatile_member_function(entity))
				std::cout << " volatile=\"true\"";
			if(declarative_region->is_virtual_member_function(entity))
				std::cout << " virtual=\"true\"";
			if(declarative_region->is_pure_member_function(entity))
				std::cout << " pure=\"true\"";
		}
	}
	if(entity->inline_specified())
		std::cout << " inline=\"true\"";
	std::cout << ">\n";

	std::cout << indent(indent_level + 1) << "<return_type>\n";
	print(entity->return_type(), indent_level + 2);
	std::cout << indent(indent_level + 1) << "</return_type>\n";

	const std::list<simple_function::parameter>& parameters = entity->parameters();
	if(!parameters.empty())
	{
		std::cout << indent(indent_level + 1) << "<parameters>\n";
		for(auto i = parameters.begin(); i != parameters.end(); ++i)
		{
			print(*i, indent_level + 2);
		}
		std::cout << indent(indent_level + 1) << "</parameters>\n";
	}

	std::cout << indent(indent_level) << "</operator_function>\n";
}

void
print
(
	std::shared_ptr<const class_::conversion_function> entity,
	const unsigned int indent_level
)
{
	std::cout << indent(indent_level) << "<conversion_function";
	if(entity->has_declarative_region())
	{
		std::shared_ptr<class_> declarative_region = utility::get<std::shared_ptr<class_>>(entity->declarative_region());

		class_::access acc = declarative_region->member_access(entity);
		std::cout << attribute(acc);
		if(declarative_region->is_virtual_member_function(entity))
			std::cout << " virtual=\"true\"";
		if(declarative_region->is_pure_member_function(entity))
			std::cout << " pure=\"true\"";
	}
	if(entity->inline_specified())
		std::cout << " inline=\"true\"";
	std::cout << ">\n";

	std::cout << indent(indent_level + 1) << "<return_type>\n";
	print(entity->return_type(), indent_level + 2);
	std::cout << indent(indent_level + 1) << "</return_type>\n";

	std::cout << indent(indent_level) << "</conversion_function>\n";
}

void
print
(
	const simple_function::parameter& p,
	const unsigned int indent_level
)
{
	std::cout << indent(indent_level) << "<parameter";
	if(!p.name().empty())
		std::cout << " name=\"" << p.name() << "\"";
	std::cout << ">\n";
	std::cout << indent(indent_level + 1) << "<type>\n";
	print(p.get_type(), indent_level + 2);
	std::cout << indent(indent_level + 1) << "</type>\n";
	std::cout << indent(indent_level) << "</parameter>\n";
}

void
print
(
	std::shared_ptr<const variable> entity,
	const unsigned int indent_level
)
{
	std::cout << indent(indent_level) << "<variable";
	std::cout << " name=\"" << entity->name() << "\"";
	//extra attributes if the function is a class member function
	if(entity->has_declarative_region())
	{
		declarative_region_shared_ptr_variant declarative_region = entity->declarative_region();
		if(auto opt_class = utility::get<std::shared_ptr<class_>>(&declarative_region))
		{
			std::shared_ptr<class_> declarative_region = *opt_class;

			class_::access acc = declarative_region->member_access(entity);
			std::cout << attribute(acc);
		}
	}
	if(entity->static_specified())
		std::cout << " static=\"true\"";
	std::cout << ">\n";
	std::cout << indent(indent_level + 1) << "<type>\n";
	print(entity->get_type(), indent_level + 2);
	std::cout << indent(indent_level + 1) << "</type>\n";
	std::cout << indent(indent_level) << "</variable>\n";
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
attribute(const semantic_entities::operator_ op)
{
	std::ostringstream oss;

	oss << " operator=\"";
	switch(op)
	{
		case semantic_entities::operator_::NEW:
			oss << "new";
			break;
		case semantic_entities::operator_::NEW_ARRAY:
			oss << "new[]";
			break;
		case semantic_entities::operator_::DELETE:
			oss << "delete";
			break;
		case semantic_entities::operator_::DELETE_ARRAY:
			oss << "delete[]";
			break;
		case semantic_entities::operator_::DOUBLE_RIGHT_ANGLE_BRACKET_EQUAL:
			oss << ">>=";
			break;
		case semantic_entities::operator_::DOUBLE_LEFT_ANGLE_BRACKET_EQUAL:
			oss << "<<=";
			break;
		case semantic_entities::operator_::ARROW_ASTERISK:
			oss << "->*";
			break;
		case semantic_entities::operator_::PLUS_EQUAL:
			oss << "+=";
			break;
		case semantic_entities::operator_::MINUS_EQUAL:
			oss << "-=";
			break;
		case semantic_entities::operator_::ASTERISK_EQUAL:
			oss << "*=";
			break;
		case semantic_entities::operator_::SLASH_EQUAL:
			oss << "/=";
			break;
		case semantic_entities::operator_::PERCENT_EQUAL:
			oss << "%=";
			break;
		case semantic_entities::operator_::CIRCUMFLEX_EQUAL:
			oss << "^=";
			break;
		case semantic_entities::operator_::AMPERSAND_EQUAL:
			oss << "&=";
			break;
		case semantic_entities::operator_::PIPE_EQUAL:
			oss << "|=";
			break;
		case semantic_entities::operator_::DOUBLE_LEFT_ANGLE_BRACKET:
			oss << "<<";
			break;
		case semantic_entities::operator_::DOUBLE_RIGHT_ANGLE_BRACKET:
			oss << ">>";
			break;
		case semantic_entities::operator_::DOUBLE_EQUAL:
			oss << "==";
			break;
		case semantic_entities::operator_::EXCLAMATION_EQUAL:
			oss << "!=";
			break;
		case semantic_entities::operator_::LEFT_ANGLE_BRACKET_EQUAL:
			oss << "<=";
			break;
		case semantic_entities::operator_::RIGHT_ANGLE_BRACKET_EQUAL:
			oss << ">=";
			break;
		case semantic_entities::operator_::DOUBLE_AMPERSAND:
			oss << "&&";
			break;
		case semantic_entities::operator_::DOUBLE_PIPE:
			oss << "||";
			break;
		case semantic_entities::operator_::DOUBLE_PLUS:
			oss << "++";
			break;
		case semantic_entities::operator_::DOUBLE_MINUS:
			oss << "--";
			break;
		case semantic_entities::operator_::ARROW:
			oss << "->";
			break;
		case semantic_entities::operator_::ROUND_BRACKETS:
			oss << "()";
			break;
		case semantic_entities::operator_::SQUARE_BRACKETS:
			oss << "[]";
			break;
		case semantic_entities::operator_::COMMA:
			oss << ",";
			break;
		case semantic_entities::operator_::PLUS:
			oss << "+";
			break;
		case semantic_entities::operator_::MINUS:
			oss << "-";
			break;
		case semantic_entities::operator_::ASTERISK:
			oss << "*";
			break;
		case semantic_entities::operator_::SLASH:
			oss << "/";
			break;
		case semantic_entities::operator_::PERCENT:
			oss << "%";
			break;
		case semantic_entities::operator_::CIRCUMFLEX:
			oss << "^";
			break;
		case semantic_entities::operator_::AMPERSAND:
			oss << "&";
			break;
		case semantic_entities::operator_::PIPE:
			oss << "|";
			break;
		case semantic_entities::operator_::TILDE:
			oss << "~";
			break;
		case semantic_entities::operator_::EXCLAMATION:
			oss << "!";
			break;
		case semantic_entities::operator_::EQUAL:
			oss << "=";
			break;
		case semantic_entities::operator_::LEFT_ANGLE_BRACKET:
			oss << "<";
			break;
		case semantic_entities::operator_::RIGHT_ANGLE_BRACKET:
			oss << ">";
			break;
	}
	oss << "\"";

	return oss.str();
}

} //namespace semantic_graph_print_functions

