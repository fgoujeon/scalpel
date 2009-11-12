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
		if(*t == built_in_type::char_)
			std::cout << "char";
		else if(*t == built_in_type::wchar_t_)
			std::cout << "wchar_t";
		else if(*t == built_in_type::bool_)
			std::cout << "bool";
		else if(*t == built_in_type::short_)
			std::cout << "short";
		else if(*t == built_in_type::int_)
			std::cout << "int";
		else if(*t == built_in_type::long_)
			std::cout << "long";
		else if(*t == built_in_type::signed_)
			std::cout << "signed";
		else if(*t == built_in_type::unsigned_)
			std::cout << "unsigned";
		else if(*t == built_in_type::float_)
			std::cout << "float";
		else if(*t == built_in_type::double_)
			std::cout << "double";
		else if(*t == built_in_type::void_)
			std::cout << "void";
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
	else if(const class_* t = dynamic_cast<const class_*>(&n))
	{
		std::cout << indent(indent_level) << "<class id=\"" << t << "\"/>";
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
	std::cout << " id=\"" << &c << "\"";
	if(access != "")
		std::cout << " access=\"" << access << "\"";
	std::cout << ">\n";

	for(auto i = c.classes().begin(); i != c.classes().end(); ++i)
		print(*i, indent_level + 1);

	for(auto i = c.constructors().begin(); i != c.constructors().end(); ++i)
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
	const class_::access& a
)
{
	std::cout << " access=\"";
	switch(a)
	{
		case class_::access::PUBLIC:
			std::cout << "public";
			break;
		case class_::access::PROTECTED:
			std::cout << "protected";
			break;
		case class_::access::PRIVATE:
			std::cout << "private";
			break;
	}
	std::cout << "\"";
}

void
print
(
	const class_::constructor& c,
	const unsigned int indent_level
)
{
	std::cout << indent(indent_level) << "<constructor";
	print(c.access());
	std::cout << ">\n";

	std::cout << indent(indent_level + 1) << "<parameters>\n";
	const class_::constructor::parameters_t& parameters = c.parameters();
	for(auto i = parameters.begin(); i != parameters.end(); ++i)
	{
		print(*i, indent_level + 2);
	}
	std::cout << indent(indent_level + 1) << "</parameters>\n";

	std::cout << indent(indent_level) << "</constructor>\n";
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

