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

#include "name_lookup2.hpp"
#include <algorithm>
#include <functional>
#include <iostream>

namespace scalpel { namespace cpp { namespace detail { namespace semantic_analysis
{

utility::shared_ptr_vector<semantic_entities::named_entity>
name_lookup2::find_entities
(
	utility::shared_ptr_vector<semantic_entities::declarative_region>::range declarative_region_path,
	const std::string& name
)
{
	//find entities from current to outermost declarative regions (until global namespace)
	std::reverse(declarative_region_path.begin(), declarative_region_path.end()); //TODO it would be faster if declarative_region_path could provide a bidirectional iterator
	for(auto i = declarative_region_path.begin(); i != declarative_region_path.end(); ++i)
	{
		std::shared_ptr<semantic_entities::declarative_region> current_declarative_region = *i;

		//find entities in current declarative region
		utility::shared_ptr_vector<semantic_entities::named_entity> found_entities = find_entities(current_declarative_region, name);
		if(!found_entities.empty()) return found_entities;
	}

	throw std::runtime_error("No entity found");
}

utility::shared_ptr_vector<semantic_entities::named_entity>
name_lookup2::find_entities
(
	std::shared_ptr<semantic_entities::declarative_region> current_declarative_region,
	const std::string& name
)
{
	utility::shared_ptr_vector<semantic_entities::named_entity> found_entities;

	for(auto i = current_declarative_region->named_entities().begin(); i != current_declarative_region->named_entities().end(); ++i)
	{
		std::shared_ptr<semantic_entities::named_entity> current_entity = *i;
		if(current_entity->name() == name)
		{
			found_entities.push_back(current_entity);
		}
	}

	return found_entities;
}

std::shared_ptr<semantic_entities::named_declarative_region>
name_lookup2::find_open_declarative_region
(
	utility::shared_ptr_vector<semantic_entities::declarative_region>::range declarative_region_path,
	const std::string& name
)
{
	std::shared_ptr<semantic_entities::named_declarative_region> found_declarative_region;

	//find a declarative region from current to outermost declarative regions
	//(until global namespace)
	std::reverse(declarative_region_path.begin(), declarative_region_path.end()); //TODO it would be faster if declarative_region_path could provide a bidirectional iterator
	for(auto i = declarative_region_path.begin(); i != declarative_region_path.end(); ++i) //from current to outermost declarative regions (until global namespace)
	{
		std::shared_ptr<semantic_entities::declarative_region> current_declarative_region = *i;

		//find declarative region in current declarative region
		std::shared_ptr<semantic_entities::named_declarative_region> maybe_found_declarative_region =
			find_open_declarative_region(current_declarative_region, name)
		;
		if(maybe_found_declarative_region)
		{
			found_declarative_region = maybe_found_declarative_region;
			break;
		}
	}

	return found_declarative_region;
}

std::shared_ptr<semantic_entities::named_declarative_region>
name_lookup2::find_open_declarative_region
(
	std::shared_ptr<semantic_entities::declarative_region> current_declarative_region,
	const std::string& name
)
{
	std::shared_ptr<semantic_entities::named_declarative_region> found_declarative_region;

	for
	(
		auto i = current_declarative_region->named_declarative_regions().begin();
		i != current_declarative_region->named_declarative_regions().end();
		++i
	)
	{
		std::shared_ptr<semantic_entities::named_declarative_region> current_declarative_region = *i;
		if(current_declarative_region->is_open_to_outside() && current_declarative_region->name() == name)
		{
			found_declarative_region = current_declarative_region;
			break;
		}
	}

	return found_declarative_region;
}

}}}} //namespace scalpel::cpp::detail::semantic_analysis

