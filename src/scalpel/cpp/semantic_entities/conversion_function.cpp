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

#include "conversion_function.hpp"
#include "type_variants.hpp"
#include "detail/function_definition_macro_template.hpp"
#include <scalpel/utility/ptr_variant_conversion_functions.hpp>
#include <scalpel/utility/are_pointed_objects_equal.hpp>

namespace scalpel { namespace cpp { namespace semantic_entities
{

GENERATE_FUNCTION_DEFINITION(conversion_function, 0, 0, 1, 0, 0, 1)

}}} //namespace scalpel::cpp::semantic_entities

#include "detail/function_definition_macro_template_undef.hpp"

