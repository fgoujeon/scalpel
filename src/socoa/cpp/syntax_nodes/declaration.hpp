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

#ifndef SOCOA_CPP_SYNTAX_TREE_DECLARATION_HPP
#define SOCOA_CPP_SYNTAX_TREE_DECLARATION_HPP

#include "alternative_node.hpp"
#include "composite_node.hpp"
#include "block_declaration.hpp"
#include "function_definition.hpp"
#include "template_declaration.hpp"
//#include "explicit_instantiation.hpp"
//#include "explicit_specialization.hpp"
//#include "linkage_specification.hpp"
#include "namespace_definition.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
{

typedef
	alternative_node
	<
		block_declaration,
		function_definition,
		template_declaration,
		//explicit_instantiation,
		//explicit_specialization,
		//linkage_specification,
		namespace_definition
	>
	declaration_t
;

struct declaration: public declaration_t
{
	declaration(block_declaration&& o): declaration_t(o){};
	declaration(function_definition&& o): declaration_t(o){};
	declaration(template_declaration&& o): declaration_t(o){};
	declaration(namespace_definition&& o): declaration_t(o){};

	declaration(const declaration& o): declaration_t(static_cast<const declaration_t&>(o)){};

	declaration(declaration&& o): declaration_t(std::move(static_cast<declaration_t&&>(o))){};

	using declaration_t::operator=;
};

}}} //namespace socoa::cpp::syntax_nodes

#endif
