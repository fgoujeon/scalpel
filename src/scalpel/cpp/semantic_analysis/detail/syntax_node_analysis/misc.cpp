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

#include "misc.hpp"

namespace scalpel { namespace cpp { namespace semantic_analysis { namespace detail { namespace syntax_node_analysis
{

using namespace syntax_nodes;
using namespace semantic_entities;

member_accessibility
get_access(const syntax_nodes::access_specifier access_specifier_node)
{
	if(get<predefined_text_node<str::public_>>(&access_specifier_node))
	{
		return member_accessibility::PUBLIC;
	}
	else if(get<predefined_text_node<str::protected_>>(&access_specifier_node))
	{
		return member_accessibility::PROTECTED;
	}
	else if(get<predefined_text_node<str::private_>>(&access_specifier_node))
	{
		return member_accessibility::PRIVATE;
	}
	else
	{
		assert(false);
	}

	return member_accessibility::PRIVATE;
}

bool
has_pure_specifier(const syntax_nodes::member_declarator_declarator& member_declarator_declarator_node)
{
	if(auto opt_constant_initializer_node = get_constant_initializer(member_declarator_declarator_node))
	{
		//auto constant_initializer_node = *opt_constant_initializer_node;
		//if(get<pure_specifier>(&constant_initializer_node))
		{
			return true;
		}
	}

	return false;
}

}}}}} //namespace scalpel::cpp::semantic_analysis::detail::syntax_node_analysis

