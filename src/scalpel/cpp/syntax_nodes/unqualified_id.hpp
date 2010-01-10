/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2010  Florian Goujeon

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

#ifndef SCALPEL_CPP_SYNTAX_NODES_UNQUALIFIED_ID_HPP
#define SCALPEL_CPP_SYNTAX_NODES_UNQUALIFIED_ID_HPP

#include "operator_function_id.hpp"
#include "conversion_function_id.hpp"
#include "destructor_name.hpp"
#include "template_id.hpp"
#include "identifier.hpp"
#include "common.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

typedef
	alternative_node
	<
        operator_function_id,
        conversion_function_id,
        destructor_name,
        template_id,
        identifier
	>
	unqualified_id
;

}}} //namespace scalpel::cpp::syntax_nodes

#endif
