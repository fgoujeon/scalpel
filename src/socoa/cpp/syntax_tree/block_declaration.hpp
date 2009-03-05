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

#ifndef SOCOA_CPP_SYNTAX_TREE_BLOCK_DECLARATION_HPP
#define SOCOA_CPP_SYNTAX_TREE_BLOCK_DECLARATION_HPP

#include <boost/variant.hpp>
#include "simple_declaration.hpp"
//#include "asm_definition.hpp"
//#include "namespace_alias_definition.hpp"
#include "using_declaration.hpp"
#include "using_directive.hpp"

namespace socoa { namespace cpp { namespace syntax_tree
{

typedef
	boost::variant
	<
		simple_declaration,
//		asm_definition,
//		namespace_alias_definition,
		using_declaration,
		using_directive
	>
	block_declaration
;

}}} //namespace socoa::cpp::syntax_tree

#endif
