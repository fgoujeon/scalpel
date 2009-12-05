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

#include "name_lookup.hpp"

#include <algorithm>
#include <functional>
#include <iostream>

namespace scalpel { namespace cpp { namespace detail { namespace semantic_analysis { namespace name_lookup
{

using namespace syntax_nodes;
using namespace semantic_entities;

std::shared_ptr<semantic_entities::named_entity>
find_name
(
	semantic_entities::named_scope& current_scope,
	const std::string& name
)
{
	std::cout << "Try to find " << name << " in " << current_scope.name() << "...\n";

	using namespace semantic_entities;

	auto members = current_scope.named_entities();
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
		std::cout << name << " found in " << current_scope.name() << "\n";
		return *member_it;
	}
	else
	{
		std::cout << name << " not found in " << current_scope.name() << "\n";
		return std::shared_ptr<semantic_entities::named_entity>();
	}
}

std::shared_ptr<semantic_entities::named_scope>
find_scope
(
	named_scope& parent_scope,
	const std::string& scope_name
)
{
	auto scopes = parent_scope.named_scopes();
	auto scope_it = std::find_if
	(
		scopes.begin(),
		scopes.end(),
		std::bind
		(
			std::equal_to<std::string>(),
			std::cref(scope_name),
			std::bind
			(
				&named_scope::name,
				std::placeholders::_1
			)
		)
	);

	if(scope_it != scopes.end())
	{
		std::cout << scope_name << " found in " << parent_scope.name() << "\n";
		return *scope_it;
	}
	else
	{
		std::cout << scope_name << " not found in " << parent_scope.name() << "\n";
		return std::shared_ptr<semantic_entities::named_scope>();
	}
}

}}}}} //namespace scalpel::cpp::detail::semantic_analysis::name_lookup

