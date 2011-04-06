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

#include "get_using_declaration_members.hpp"

namespace scalpel { namespace cpp { namespace semantic_entities { namespace generic_queries { namespace detail
{

const std::vector<namespace_*> empty_namespace_ptr_vector;
const std::vector<namespace_alias*> empty_namespace_alias_ptr_vector;
const std::vector<class_*> empty_class_ptr_vector;
const std::vector<member_class*> empty_member_class_ptr_vector;
const std::vector<enum_*> empty_enum_ptr_vector;
const std::vector<member_enum*> empty_member_enum_ptr_vector;
const std::vector<typedef_*> empty_typedef_ptr_vector;
const std::vector<member_typedef*> empty_member_typedef_ptr_vector;
const std::vector<constructor*> empty_constructor_ptr_vector;
const std::vector<destructor*> empty_destructor_ptr_vector;
const std::vector<operator_member_function*> empty_operator_member_function_ptr_vector;
const std::vector<conversion_function*> empty_conversion_function_ptr_vector;
const std::vector<simple_member_function*> empty_simple_member_function_ptr_vector;
const std::vector<operator_function*> empty_operator_function_ptr_vector;
const std::vector<simple_function*> empty_simple_function_ptr_vector;
const std::vector<variable*> empty_variable_ptr_vector;
const std::vector<member_variable*> empty_member_variable_ptr_vector;
const std::vector<bit_field*> empty_bit_field_ptr_vector;

}}}}} //namespace scalpel::cpp::semantic_entities::generic_queries::detail

