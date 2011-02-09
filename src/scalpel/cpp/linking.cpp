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

#include "linking.hpp"
#include "linking/detail/merge.hpp"
#include "linking/detail/create_unique_id.hpp"
#include "linking/detail/entity_tree.hpp"
#include "linking/detail/list_entities.hpp"
#include <iostream>

namespace scalpel { namespace cpp
{

namespace linking
{

std::string
indent(const unsigned int count)
{
	std::string str;
	for(unsigned int i = 0; i < count; ++i) str += ' ';
	return str;
}

template<class Entity>
void
print(const std::string& title, const detail::entity_list<Entity>& list, const unsigned int indent_count = 0)
{
	const unsigned int entity_count = list.list.size();
	if(entity_count > 0)
	{
		std::cout << indent(indent_count) << title << ":\n";
		for(auto i = list.list.begin(); i != list.list.end(); ++i)
			std::cout << indent(indent_count + 1) << i->first << " (x" << i->second.size() << ")\n";
	}
}

void
print(const detail::entity_tree& tree, const unsigned int indent_count = 0)
{
	for(auto i = tree.subtrees.begin(); i != tree.subtrees.end(); ++i)
	{
		const std::string& name = i->first;
		const detail::entity_tree& subtree = i->second;

		std::cout << indent(indent_count) << "namespace " << name << ":\n";
		print(subtree, indent_count + 1);
	}

	print("classes", tree.classes, indent_count);
	print("enums", tree.enums, indent_count);
	print("typedefs", tree.typedefs, indent_count);
	print("constructors", tree.constructors, indent_count);
	print("destructors", tree.destructors, indent_count);
	print("operator_member_functions", tree.operator_member_functions, indent_count);
	print("conversion_functions", tree.conversion_functions, indent_count);
	print("simple_member_functions", tree.simple_member_functions, indent_count);
	print("operator_functions", tree.operator_functions, indent_count);
	print("simple_functions", tree.simple_functions, indent_count);
	print("variables", tree.variables, indent_count);
}

std::unique_ptr<semantic_graph>
link(const utility::unique_ptr_vector<semantic_graph>& semantic_graphs)
{
	detail::entity_tree entity_tree = detail::list_entities(semantic_graphs);
	//print(entity_tree);
	return detail::merge(semantic_graphs, entity_tree);
}

} //namespace semantic_analysis

}} //namespace scalpel::cpp


