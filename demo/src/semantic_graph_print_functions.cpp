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

#include "basic_print_functions.hpp"

namespace semantic_graph_print_functions
{

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
	const unsigned int indent_level
)
{
	std::cout << indent(indent_level) << "<class";
	std::cout << " name=\"" << c.name() << "\"";
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
	const unsigned int indent_level
)
{
	std::cout << indent(indent_level) << "<function";
	std::cout << " name=\"" << f.name() << "\"";
	std::cout << ">\n";

	std::cout << indent(indent_level) << "</function>\n";
}

void
print
(
	const variable& v,
	const unsigned int indent_level
)
{
	std::cout << indent(indent_level) << "<variable";
	std::cout << " name=\"" << v.name() << "\"";
	std::cout << "/>\n";
}

} //namespace semantic_graph_print_functions

