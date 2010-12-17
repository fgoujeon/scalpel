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

#include "template_id.hpp"

namespace scalpel { namespace cpp { namespace detail { namespace semantic_analysis { namespace syntax_node_analysis
{

using namespace syntax_nodes;

syntax_nodes::unqualified_id
get_unqualified_id(const syntax_nodes::template_id& template_id_node)
{
	if(boost::optional<const operator_function_template_id&> opt_operator_function_template_id_node = get<operator_function_template_id>(&template_id_node))
	{
		const operator_function_template_id& operator_function_template_id_node = *opt_operator_function_template_id_node;
		return unqualified_id(get_operator_function_id(operator_function_template_id_node));
	}
	else if(boost::optional<const simple_template_id&> opt_simple_template_id_node = get<simple_template_id>(&template_id_node))
	{
		const simple_template_id& simple_template_id_node = *opt_simple_template_id_node;
		return unqualified_id(get_identifier(simple_template_id_node));
	}
	else
	{
		assert(false);
	}
}

}}}}} //namespace scalpel::cpp::detail::semantic_analysis::syntax_node_analysis

