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

#include "merge.hpp"

namespace scalpel { namespace cpp { namespace linking { namespace detail
{

using namespace semantic_entities;

std::unique_ptr<semantic_entities::namespace_>
create_namespace(const linking_tree::namespace_& tree, const std::string& namespace_name)
{
	std::unique_ptr<namespace_> new_namespace(new namespace_(namespace_name));

	for(auto i = tree.namespaces.begin(); i != tree.namespaces.end(); ++i)
	{
		const std::string& name = i->first;
		const detail::linking_tree::namespace_& subtree = i->second;
		new_namespace->add_member(create_namespace(subtree, name));
	}

	for(auto i = tree.classes.begin(); i != tree.classes.end(); ++i)
	{
		const std::string& name = i->first;
		const detail::linking_tree::class_& subtree = i->second;
		new_namespace->add_member(create_class(subtree, name));
	}

	return new_namespace;
}

std::unique_ptr<semantic_entities::class_>
create_class(const linking_tree::class_&, const std::string& class_name)
{
	std::unique_ptr<class_> new_class(new class_(class_name));
	return new_class;
}

std::unique_ptr<semantic_graph>
merge(const linking_tree::namespace_& tree)
{
	return create_namespace(tree, "");
}

}}}} //namespace scalpel::cpp::linking::detail

