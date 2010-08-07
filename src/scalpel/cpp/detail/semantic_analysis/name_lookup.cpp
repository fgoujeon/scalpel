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
#include <algorithm>
#include <functional>
#include <iostream>

namespace scalpel { namespace cpp { namespace detail { namespace semantic_analysis
{

using namespace syntax_nodes;
using namespace semantic_entities;

std::shared_ptr<semantic_entities::named_entity>
name_lookup::find_name
(
	semantic_entities::declarative_region& current_declarative_region,
	const std::string& name
)
{
	using namespace semantic_entities;

	auto members = current_declarative_region.named_entities();
	auto member_it = std::find_if
	(
		members.begin(),
		members.end(),
		std::bind
		(
			std::equal_to<std::string>(),
			std::cref(name),
			std::bind
			(
				&named_entity::name,
				std::placeholders::_1
			)
		)
	);

	if(member_it != members.end()) //if a name has been found
	{
		return *member_it;
	}
	else
	{
		return std::shared_ptr<semantic_entities::named_entity>();
	}
}

std::shared_ptr<semantic_entities::declarative_region>
name_lookup::find_declarative_region
(
	declarative_region& parent_declarative_region,
	const std::string& declarative_region_name
)
{
	auto declarative_regions = parent_declarative_region.named_declarative_regions();
	auto declarative_region_it = std::find_if
	(
		declarative_regions.begin(),
		declarative_regions.end(),
		std::bind
		(
			std::equal_to<std::string>(),
			std::cref(declarative_region_name),
			std::bind
			(
				&named_declarative_region::name,
				std::placeholders::_1
			)
		)
	);

	if(declarative_region_it != declarative_regions.end())
	{
		return *declarative_region_it;
	}
	else
	{
		return std::shared_ptr<semantic_entities::named_declarative_region>();
	}
}

}}}} //namespace scalpel::cpp::detail::semantic_analysis

