/*
Socoa - Source Code Analysis Library
Copyright © 2008, 2009  Florian Goujeon

This file is part of Socoa.

Socoa is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Socoa is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Socoa.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SOCOA_CPP_SEMANTIC_GRAPH_SCOPE_HPP
#define SOCOA_CPP_SEMANTIC_GRAPH_SCOPE_HPP

#include <vector>
#include "named_item.hpp"

namespace socoa { namespace cpp { namespace semantic_graph
{

struct scope
{
	virtual
	~scope(){}

	virtual
	const std::vector<scope*>&
	get_scopes() const = 0;

	virtual
	const std::vector<named_item*>&
	get_named_items() const = 0;
};

}}} //namespace socoa::cpp::semantic_graph

#endif
