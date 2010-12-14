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

#include "get_global_namespace.hpp"

namespace scalpel { namespace cpp { namespace detail { namespace semantic_analysis { namespace semantic_entity_analysis
{

std::shared_ptr<semantic_entities::namespace_>
get_global_namespace(semantic_entities::declarative_region_shared_ptr_variant current_declarative_region)
{
	//get the outermost declarative region
	while(has_enclosing_declarative_region(current_declarative_region))
	{
		current_declarative_region = get_enclosing_declarative_region(current_declarative_region);
	}

	//try to cast it to a namespace
	try
	{
		return utility::get<semantic_entities::namespace_>(current_declarative_region);
	}
	catch(...)
	{
		throw std::runtime_error("get_global_namespace() error: the outermost declarative region isn't a namespace.");
	}
}

}}}}} //namespace scalpel::cpp::detail::semantic_analysis::semantic_entity_analysis

