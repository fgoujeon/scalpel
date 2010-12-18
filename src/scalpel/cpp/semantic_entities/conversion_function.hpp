/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2010  Florian Goujeon

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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_CONVERSION_FUNCTION_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_CONVERSION_FUNCTION_HPP

#include "statement_block.hpp"
#include "type_variants_fwd.hpp"
#include "declarative_region_variants.hpp"
#include "detail/declarative_region_member_impl.hpp"
#include "detail/function_declaration_macro_template.hpp"

namespace scalpel { namespace cpp { namespace semantic_entities
{

GENERATE_FUNCTION_DECLARATION(conversion_function, 0, 0, 1, 0, 0, 1)

}}} //namespace scalpel::cpp::semantic_entities

#include "detail/function_declaration_macro_template_undef.hpp"

#endif

