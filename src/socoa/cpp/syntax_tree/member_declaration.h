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

#ifndef SOCOA_CPP_SYNTAX_TREE_MEMBER_DECLARATION_H
#define SOCOA_CPP_SYNTAX_TREE_MEMBER_DECLARATION_H

#include <boost/variant.hpp>
#include "member_declaration_function_definition.h"
//#include "member_declaration_member_declarator_list.h"
#include "member_declaration_unqualified_id.h"
#include "using_declaration.h"
#include "template_declaration.h"

namespace socoa { namespace cpp { namespace syntax_tree
{

typedef
	boost::variant
	<
		member_declaration_function_definition,
		//member_declaration_member_declarator_list,
		member_declaration_unqualified_id,
		using_declaration,
		template_declaration
	>
	member_declaration
;

}}} //namespace socoa::cpp::syntax_tree

#endif
