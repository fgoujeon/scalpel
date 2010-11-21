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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_TYPE_VARIANTS_FWD_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_TYPE_VARIANTS_FWD_HPP

#include <scalpel/utility/variant.hpp>

namespace scalpel { namespace cpp { namespace semantic_entities
{

class array;
class class_;
class const_;
class fundamental_type;
class pointer;
class reference;
class typedef_;
class volatile_;

typedef
	utility::variant
	<
		std::shared_ptr<const array>,
		std::shared_ptr<const fundamental_type>,
		std::shared_ptr<const class_>,
		std::shared_ptr<const const_>,
		std::shared_ptr<const pointer>,
		std::shared_ptr<const reference>,
		std::shared_ptr<const typedef_>,
		std::shared_ptr<const volatile_>
	>
	type_shared_ptr_variant
;

//non-fundamental types that can be referred to by a name
typedef
	utility::variant
	<
		std::shared_ptr<class_>,
		std::shared_ptr<typedef_>
	>
	named_compound_type_shared_ptr_variant
;

const std::string&
get_name(const named_compound_type_shared_ptr_variant var);

type_shared_ptr_variant
to_type_shared_ptr_variant(const named_compound_type_shared_ptr_variant var);

}}} //namespace scalpel::cpp::semantic_entities

#endif

