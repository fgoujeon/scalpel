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

#include <vector>
#include <sstream>

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
		std::cout << indent(indent_level) << "<built_in_type type=\"";
		print(*t);
	   	std::cout << "\"/>\n";
	}
	else if(const const_* t = dynamic_cast<const const_*>(&n))
	{
		std::cout << indent(indent_level) << "<const>\n";
		print(*t->decorated_type(), indent_level + 1);
		std::cout << indent(indent_level) << "</const>\n";
	}
	else if(const volatile_* t = dynamic_cast<const volatile_*>(&n))
	{
		std::cout << indent(indent_level) << "<volatile>\n";
		print(*t->decorated_type(), indent_level + 1);
		std::cout << indent(indent_level) << "</volatile>\n";
	}
	else if(const pointer* t = dynamic_cast<const pointer*>(&n))
	{
		std::cout << indent(indent_level) << "<pointer>\n";
		print(*t->decorated_type(), indent_level + 1);
		std::cout << indent(indent_level) << "</pointer>\n";
	}
	else if(const reference* t = dynamic_cast<const reference*>(&n))
	{
		std::cout << indent(indent_level) << "<reference>\n";
		print(*t->decorated_type(), indent_level + 1);
		std::cout << indent(indent_level) << "</reference>\n";
	}
	else if(const array* t = dynamic_cast<const array*>(&n))
	{
		std::cout << indent(indent_level) << "<array size=\"" << t->size() << "\">\n";
		print(*t->decorated_type(), indent_level + 1);
		std::cout << indent(indent_level) << "</array>\n";
	}
	else if(const class_* t = dynamic_cast<const class_*>(&n))
	{
		std::cout << indent(indent_level) << "<class id=\"" << t << "\"/>\n";
	}
}

void
print
(
	const built_in_type& built_in_t
)
{
	std::vector<std::pair<const built_in_type&, const char*>> built_in_types_table =
	{
		{built_in_type::bool_, "bool"},
		{built_in_type::char_, "char"},
		{built_in_type::double_, "double"},
		{built_in_type::float_, "float"},
		{built_in_type::int_, "int"},
		{built_in_type::long_double, "long double"},
		{built_in_type::long_int, "long int"},
		{built_in_type::long_long_int, "long long int"},
		{built_in_type::short_int, "short int"},
		{built_in_type::unsigned_char, "unsigned char"},
		{built_in_type::unsigned_int, "unsigned int"},
		{built_in_type::unsigned_long_int, "unsigned long int"},
		{built_in_type::unsigned_long_long_int, "unsigned long long int"},
		{built_in_type::unsigned_short_int, "unsigned short int"},
		{built_in_type::void_, "void"},
		{built_in_type::wchar_t_, "wchar_t"}
	};

	for(auto i = built_in_types_table.begin(); i != built_in_types_table.end(); ++i)
	{
		auto pair = *i;
		const built_in_type& t = pair.first;
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
		print(**i, indent_level + 1);

	for(auto i = n.classes().begin(); i != n.classes().end(); ++i)
		print(**i, indent_level + 1);

	for(auto i = n.functions().begin(); i != n.functions().end(); ++i)
		print(**i, indent_level + 1);

	for(auto i = n.variables().begin(); i != n.variables().end(); ++i)
		print(**i, indent_level + 1);

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

	for(auto i = c.base_classes().begin(); i != c.base_classes().end(); ++i)
	{
		const class_::base_class& base = **i;

		std::cout << indent(indent_level + 1) << "<base_class";
		std::cout << " id=\"" << base.base().get() << "\"";
		print(base.access());
		if(base.virtual_specified())
			std::cout << " virtual=\"true\"";
		std::cout << "/>\n";
	}

	for(auto i = c.nested_classes().begin(); i != c.nested_classes().end(); ++i)
		print(**i, indent_level + 1);

	for(auto i = c.constructors().begin(); i != c.constructors().end(); ++i)
		print(**i, indent_level + 1);

	print(*c.get_destructor(), indent_level + 1);

	for(auto i = c.functions().begin(); i != c.functions().end(); ++i)
		print(**i, indent_level + 1);

	for(auto i = c.variables().begin(); i != c.variables().end(); ++i)
		print(**i, indent_level + 1);

	std::cout << indent(indent_level) << "</class>\n";
}

template<>
void
print
(
	const class_::member<function>& f,
	const unsigned int indent_level
)
{
	std::cout << indent(indent_level) << "<function";
	std::cout << " name=\"" << f.entity()->name() << "\"";
	print(f.access());
	if(f.entity()->static_specified())
		std::cout << " static=\"true\"";
	if(f.const_qualified())
		std::cout << " const=\"true\"";
	if(f.volatile_qualified())
		std::cout << " volatile=\"true\"";
	if(f.inline_specified())
		std::cout << " inline=\"true\"";
	if(f.virtual_specified())
		std::cout << " virtual=\"true\"";
	if(f.pure_specified())
		std::cout << " pure=\"true\"";
	std::cout << ">\n";

	std::cout << indent(indent_level + 1) << "<return_type>\n";
	print(*f.entity()->return_type(), indent_level + 2);
	std::cout << indent(indent_level + 1) << "</return_type>\n";

	std::cout << indent(indent_level + 1) << "<parameters>\n";
	const std::list<function::parameter>& parameters = f.entity()->parameters();
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
	if(c.inline_specified())
		std::cout << " inline=\"true\"";
	if(c.explicit_specified())
		std::cout << " explicit=\"true\"";
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
	const class_::destructor& d,
	const unsigned int indent_level
)
{
	std::cout << indent(indent_level) << "<destructor";
	print(d.access());
	if(d.inline_specified())
		std::cout << " inline=\"true\"";
	if(d.virtual_specified())
		std::cout << " virtual=\"true\"";
	if(d.pure_specified())
		std::cout << " pure=\"true\"";
	if(d.implicitly_declared())
		std::cout << " implicitly_declared=\"true\"";
	std::cout << ">\n";

	std::cout << indent(indent_level) << "</destructor>\n";
}

void
print
(
	const function& f,
	const unsigned int indent_level
)
{
	std::cout << indent(indent_level) << "<function";
	std::cout << " name=\"" << f.name() << "\"";
	if(f.static_specified())
		std::cout << " static=\"true\"";
	std::cout << ">\n";

	std::cout << indent(indent_level + 1) << "<return_type>\n";
	print(*f.return_type(), indent_level + 2);
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
	print(*p.get_type(), indent_level + 2);
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
	if(v.static_specified())
		std::cout << " static=\"true\"";
	std::cout << ">\n";
	std::cout << indent(indent_level + 1) << "<type>\n";
	print(*v.get_type(), indent_level + 2);
	std::cout << indent(indent_level + 1) << "</type>\n";
	std::cout << indent(indent_level) << "</variable>\n";
}

} //namespace semantic_graph_print_functions

