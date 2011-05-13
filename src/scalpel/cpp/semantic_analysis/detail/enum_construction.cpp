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

#include "enum_construction.hpp"
#include "syntax_node_analysis/enum_specifier.hpp"

namespace scalpel { namespace cpp { namespace semantic_analysis { namespace detail
{

using namespace syntax_nodes;
using namespace semantic_entities;

std::unique_ptr<enum_>
create_enum(const enum_specifier& enum_specifier_node)
{
	return std::unique_ptr<enum_>(new enum_(syntax_node_analysis::get_identifier(enum_specifier_node)));
}

std::unique_ptr<member_enum>
create_member_enum(const enum_specifier& enum_specifier_node, const member_access access)
{
	return std::unique_ptr<member_enum>(new member_enum(syntax_node_analysis::get_identifier(enum_specifier_node), access));
}

}}}} //namespace scalpel::cpp::semantic_analysis::detail

