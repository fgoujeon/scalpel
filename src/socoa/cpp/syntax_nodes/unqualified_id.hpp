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

#ifndef SOCOA_CPP_SYNTAX_NODES_UNQUALIFIED_ID_HPP
#define SOCOA_CPP_SYNTAX_NODES_UNQUALIFIED_ID_HPP

#include "alternative_node.hpp"
#include "operator_function_id.hpp"
#include "conversion_function_id.hpp"
#include "destructor_name.hpp"
#include "template_id.hpp"
#include "identifier.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
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

}}} //namespace socoa::cpp::syntax_nodes

#endif
