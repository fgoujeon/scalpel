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

#include "name_lookup.hpp"
#include <stdexcept>

namespace scalpel { namespace cpp { namespace detail { namespace semantic_analysis { namespace name_lookup
{

void
impl::apply_using_directives
(
	const semantic_entities::declarative_region_shared_ptr_variant& current_declarative_region,
	const std::vector<std::weak_ptr<semantic_entities::namespace_>>& using_directive_namespaces,
	namespace_association_map& namespace_associations
)
{
	//for each using directive's namespace...
	for
	(
		auto i = using_directive_namespaces.begin();
		i != using_directive_namespaces.end();
		++i
	)
	{
		std::shared_ptr<semantic_entities::namespace_> current_using_directive_namespace(*i);

		//find the common enclosing namespace
		const std::shared_ptr<semantic_entities::namespace_> common_enclosing_namespace =
			find_common_enclosing_namespace(current_declarative_region, current_using_directive_namespace)
		;

		//associate the using directive's namespace to the common enclosing namespace
		namespace_associations[common_enclosing_namespace].push_back(current_using_directive_namespace);

		//proceed recursively with the using directive's namespaces of the using directive's namespace
		apply_using_directives
		(
			current_declarative_region,
			current_using_directive_namespace->using_directive_namespaces(),
			namespace_associations
		);
	}
}

std::shared_ptr<semantic_entities::namespace_>
impl::find_common_enclosing_namespace
(
	const semantic_entities::declarative_region_shared_ptr_variant& a,
	const std::shared_ptr<semantic_entities::namespace_> b
)
{
	//from a to outermost declarative region...
	semantic_entities::declarative_region_shared_ptr_variant current_declarative_region_a = a;
	while(true)
	{
		if(auto opt_namespace_ptr = utility::get<std::shared_ptr<semantic_entities::namespace_>>(&current_declarative_region_a))
		{
			const std::shared_ptr<semantic_entities::namespace_> current_namespace_a = *opt_namespace_ptr;

			//from b to outermost namespace...
			std::shared_ptr<semantic_entities::namespace_> current_namespace_b = b;
			while(true)
			{
				if(current_namespace_a == current_namespace_b)
					return current_namespace_a;

				//iterate to the enclosing namespace
				if(!current_namespace_b->has_enclosing_declarative_region()) break;
				current_namespace_b = current_namespace_b->enclosing_declarative_region();
			}
		}

		//iterate to the enclosing declarative region
		if(!has_enclosing_declarative_region(current_declarative_region_a)) break;
		current_declarative_region_a = get_enclosing_declarative_region(current_declarative_region_a);
	}

	throw std::runtime_error("find_common_enclosing_namespace() error: the given declarative regions don't have a common namespace");
}

}}}}} //namespace scalpel::cpp::detail::semantic_analysis::name_lookup

