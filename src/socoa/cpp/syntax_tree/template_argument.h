/*
Socoa _ Source Code Analysis Library
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

#ifndef SOCOA_CPP_SYNTAX_TREE_TEMPLATE_ARGUMENT_H
#define SOCOA_CPP_SYNTAX_TREE_TEMPLATE_ARGUMENT_H

#include <boost/variant.hpp>
#include "assignment_expression.h"
#include "type_id.h"
#include "id_expression.h"

namespace socoa { namespace cpp { namespace syntax_tree
{

typedef
	boost::variant
	<
//		assignment_expression,
//		type_id,
		id_expression
	>
	template_argument_t
;

class template_argument:
	public boost::variant
	<
//		assignment_expression,
//		type_id,
		id_expression
	>
{
	public:
		template_argument(const id_expression& o): template_argument_t(o){}
};

}}} //namespace socoa::cpp::syntax_tree

#endif
