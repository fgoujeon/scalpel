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

#include "class_specifier.hpp"

namespace scalpel { namespace cpp { namespace semantic_analysis { namespace detail { namespace syntax_node_analysis
{

using namespace syntax_nodes;

std::string
get_identifier(const syntax_nodes::class_specifier& class_specifier_node)
{
	std::string class_name;

	const optional_node<identifier_or_template_id>& opt_id_or_templ = get_identifier_or_template_id(get_class_head(class_specifier_node));
	if(opt_id_or_templ)
	{
		const boost::optional<const identifier&> id = get<identifier>(&*opt_id_or_templ);

		if(id)
		{
			class_name = id->value();
		}
	}

	return class_name;
}

}}}}} //namespace scalpel::cpp::semantic_analysis::detail::syntax_node_analysis

