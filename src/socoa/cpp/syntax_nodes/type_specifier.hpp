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

#ifndef SOCOA_CPP_SYNTAX_TREE_TYPE_SPECIFIER_HPP
#define SOCOA_CPP_SYNTAX_TREE_TYPE_SPECIFIER_HPP

#include "simple_type_specifier.hpp"
#include "class_specifier.hpp"
//#include "enum_specifier.hpp"
#include "elaborated_type_specifier.hpp"
#include "cv_qualifier.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
{

typedef
	alternative_node
	<
		simple_type_specifier,
		class_specifier,
//		enum_specifier,
		elaborated_type_specifier,
		cv_qualifier
	>
	type_specifier
;

}}} //namespace socoa::cpp::syntax_nodes

#endif
