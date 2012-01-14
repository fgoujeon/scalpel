/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2012  Florian Goujeon

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

#include "enum_specifier.hpp"

namespace scalpel { namespace cpp { namespace semantic_analysis { namespace detail { namespace syntax_node_analysis
{

using namespace syntax_nodes;

std::string
get_identifier(const syntax_nodes::enum_specifier& enum_specifier_node)
{
	if(const optional_node<identifier>& opt_identifier = syntax_nodes::get_identifier(enum_specifier_node))
	{
		return opt_identifier->value();
	}

	return std::string();
}

}}}}} //namespace scalpel::cpp::semantic_analysis::detail::syntax_node_analysis

