/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008, 2009  Florian Goujeon

This file is part of Scalpel.

Scalpel is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Scalpel is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Scalpel.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "semantic_graph_print_functions.hpp"

namespace semantic_graph_print_functions
{

void
print
(
	const type& n,
	const unsigned int indent_level
)
{
	if(const built_in_type* t = dynamic_cast<const built_in_type*>(&n))
	{
		std::cout << indent(indent_level);
		switch(t->get_type())
		{
			case built_in_type::type_enum::CHAR:
				std::cout << "char";
				break;
			case built_in_type::type_enum::WCHAR_T:
				std::cout << "wchar_t";
				break;
			case built_in_type::type_enum::BOOL:
				std::cout << "bool";
				break;
			case built_in_type::type_enum::SHORT:
				std::cout << "short";
				break;
			case built_in_type::type_enum::INT:
				std::cout << "int";
				break;
			case built_in_type::type_enum::LONG:
				std::cout << "long";
				break;
			case built_in_type::type_enum::SIGNED:
				std::cout << "signed";
				break;
			case built_in_type::type_enum::UNSIGNED:
				std::cout << "unsigned";
				break;
			case built_in_type::type_enum::FLOAT:
				std::cout << "float";
				break;
			case built_in_type::type_enum::DOUBLE:
				std::cout << "double";
				break;
			case built_in_type::type_enum::VOID:
				std::cout << "void";
				break;
		}
	}
	else if(const const_* t = dynamic_cast<const const_*>(&n))
	{
		std::cout << indent(indent_level) << "<const>\n";
		print(t->decorated_type(), indent_level + 1);
		std::cout << indent(indent_level) << "</const>";
	}
	else if(const volatile_* t = dynamic_cast<const volatile_*>(&n))
	{
		std::cout << indent(indent_level) << "<volatile>\n";
		print(t->decorated_type(), indent_level + 1);
		std::cout << indent(indent_level) << "</volatile>";
	}
	else if(const pointer* t = dynamic_cast<const pointer*>(&n))
	{
		std::cout << indent(indent_level) << "<pointer>\n";
		print(t->decorated_type(), indent_level + 1);
		std::cout << indent(indent_level) << "</pointer>";
	}
	else if(const reference* t = dynamic_cast<const reference*>(&n))
	{
		std::cout << indent(indent_level) << "<reference>\n";
		print(t->decorated_type(), indent_level + 1);
		std::cout << indent(indent_level) << "</reference>";
	}
	else if(const array* t = dynamic_cast<const array*>(&n))
	{
		std::cout << indent(indent_level) << "<array size=\"" << t->size() << "\">\n";
		print(t->decorated_type(), indent_level + 1);
		std::cout << indent(indent_level) << "</array>";
	}
	std::cout << '\n';
}

void
print
(
	const namespace_& n,
	const unsigned int indent_level
)
{
	std::cout << indent(indent_level) << "<namespace";
	if(n.name() != "")
	{
		std::cout << " name=\"" << n.name() << "\"";
	}
	std::cout << ">\n";

	for(auto i = n.namespaces().begin(); i != n.namespaces().end(); ++i)
		print(*i, indent_level + 1);

	for(auto i = n.classes().begin(); i != n.classes().end(); ++i)
		print(*i, indent_level + 1);

	for(auto i = n.functions().begin(); i != n.functions().end(); ++i)
		print(*i, indent_level + 1);

	for(auto i = n.variables().begin(); i != n.variables().end(); ++i)
		print(*i, indent_level + 1);

	std::cout << indent(indent_level) << "</namespace>\n";
}

void
print
(
	const class_& c,
	const unsigned int indent_level,
	const std::string& access
)
{
	std::cout << indent(indent_level) << "<class";
	std::cout << " name=\"" << c.name() << "\"";
	if(access != "")
		std::cout << " access=\"" << access << "\"";
	std::cout << ">\n";

	for(auto i = c.classes().begin(); i != c.classes().end(); ++i)
		print(*i, indent_level + 1);

	for(auto i = c.functions().begin(); i != c.functions().end(); ++i)
		print(*i, indent_level + 1);

	for(auto i = c.variables().begin(); i != c.variables().end(); ++i)
		print(*i, indent_level + 1);

	std::cout << indent(indent_level) << "</class>\n";
}

void
print
(
	const function& f,
	const unsigned int indent_level,
	const std::string& access
)
{
	std::cout << indent(indent_level) << "<function";
	std::cout << " name=\"" << f.name() << "\"";
	if(access != "")
		std::cout << " access=\"" << access << "\"";
	std::cout << ">\n";

	std::cout << indent(indent_level + 1) << "<return_type>\n";
	print(f.return_type(), indent_level + 2);
	std::cout << indent(indent_level + 1) << "</return_type>\n";

	std::cout << indent(indent_level + 1) << "<parameters>\n";
	const std::list<function::parameter>& parameters = f.parameters();
	for(auto i = parameters.begin(); i != parameters.end(); ++i)
	{
		print(*i, indent_level + 2);
	}
	std::cout << indent(indent_level + 1) << "</parameters>\n";

	std::cout << indent(indent_level) << "</function>\n";
}

void
print
(
	const function::parameter& p,
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
	const variable& v,
	const unsigned int indent_level,
	const std::string& access
)
{
	std::cout << indent(indent_level) << "<variable";
	std::cout << " name=\"" << v.name() << "\"";
	if(access != "")
		std::cout << " access=\"" << access << "\"";
	std::cout << ">\n";
	std::cout << indent(indent_level + 1) << "<type>\n";
	print(v.get_type(), indent_level + 2);
	std::cout << indent(indent_level + 1) << "</type>\n";
	std::cout << indent(indent_level) << "</variable>\n";
}

} //namespace semantic_graph_print_functions

