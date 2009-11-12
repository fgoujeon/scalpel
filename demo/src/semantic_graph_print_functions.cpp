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
	const semantic_graph& g
)
{
	std::cout << "<semantic_graph>\n";
	print(g.global_namespace(), 1);
	print(g.type_pool(), 1);
	std::cout << "</semantic_graph>\n";
}

void
print
(
	const semantic_graph::type_pool_const_iterator_range& p,
	const unsigned int indent_level
)
{
	std::cout << indent(indent_level) << "<type_pool>\n";

	//built in types
	std::vector<std::pair<const built_in_type&, const char*>> built_in_types_table =
	{
		{built_in_type::char_, "char"},
		{built_in_type::wchar_t_, "wchar_t"},
		{built_in_type::bool_, "bool"},
		{built_in_type::short_, "short"},
		{built_in_type::int_, "int"},
		{built_in_type::long_, "long"},
		{built_in_type::signed_, "signed"},
		{built_in_type::unsigned_, "unsigned"},
		{built_in_type::float_, "float"},
		{built_in_type::double_, "double"},
		{built_in_type::void_, "void"}
	};

	std::cout << indent(indent_level + 1) << "<!-- built-in types -->\n";
	for(auto i = built_in_types_table.begin(); i != built_in_types_table.end(); ++i)
	{
		auto pair = *i;
		const type& t = pair.first;
		const char* type_str = pair.second;

		std::cout << indent(indent_level + 1) << "<type id=\"" << &t << "\">";
		std::cout << type_str;
		std::cout << "</type>\n";
	}

	//decorated types
	std::cout << indent(indent_level + 1) << "<!-- decorated types -->\n";
	for(auto i = p.begin(); i != p.end(); ++i)
	{
		const type& t = *i;
		std::cout << indent(indent_level + 1) << "<type id=\"" << &t << "\">";
		print(t);
		std::cout << "</type>\n";
	}

	std::cout << indent(indent_level) << "</type_pool>\n";
}

void
print(const type& n)
{
	if(const const_* t = dynamic_cast<const const_*>(&n))
	{
		std::cout << "<const type_id=\"" << &t->decorated_type() << "\"/>";
	}
	else if(const volatile_* t = dynamic_cast<const volatile_*>(&n))
	{
		std::cout << "<volatile type_id=\"" << &t->decorated_type() << "\"/>";
	}
	else if(const pointer* t = dynamic_cast<const pointer*>(&n))
	{
		std::cout << "<pointer type_id=\"" << &t->decorated_type() << "\"/>";
	}
	else if(const reference* t = dynamic_cast<const reference*>(&n))
	{
		std::cout << "<reference type_id=\"" << &t->decorated_type() << "\"/>";
	}
	else if(const array* t = dynamic_cast<const array*>(&n))
	{
		std::cout << "<array size=\"" << t->size() << "\" type_id=\"" << &t->decorated_type() << "\"/>";
	}
	else if(const class_* t = dynamic_cast<const class_*>(&n))
	{
		std::cout << "<class id=\"" << t << "\"/>";
	}
}

void
print_type_id(const type& t)
{
	if(const class_* ptr = dynamic_cast<const class_*>(&t))
	{
		std::cout << ptr;
	}
	else
	{
		std::cout << &t;
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
	std::cout << " return_type_id=\"" << &f.return_type() << "\"";
	if(access != "")
		std::cout << " access=\"" << access << "\"";
	std::cout << ">\n";

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
	std::cout << " type_id=\"" << &p.get_type() << "\"";
	std::cout << "/>\n";
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
	std::cout << " type_id=\"";
	print_type_id(v.get_type());
	std::cout << "\"";
	if(access != "")
		std::cout << " access=\"" << access << "\"";
	std::cout << "/>\n";
}

} //namespace semantic_graph_print_functions

