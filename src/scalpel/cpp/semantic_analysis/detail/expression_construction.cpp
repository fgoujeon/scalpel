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

#include "value_construction.hpp"
#include "expression_construction.hpp"
#include <iostream>

namespace scalpel { namespace cpp { namespace semantic_analysis { namespace detail
{

using namespace syntax_nodes;
using namespace semantic_entities;

semantic_entities::expression_t
create_expression(const syntax_nodes::literal& literal_node)
{
	if(const boost::optional<const integer_literal&>& opt_integer_literal_node = get<integer_literal>(&literal_node))
		return create_value(*opt_integer_literal_node);
	if(const boost::optional<const boolean_literal&>& opt_boolean_literal_node = get<boolean_literal>(&literal_node))
		return create_boolean_value(*opt_boolean_literal_node);

	assert(false);

	/*
	character_literal
	string_literal
	floating_literal
	*/
}

}}}} //namespace scalpel::cpp::semantic_analysis::detail

