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

#include <scalpel/utility/const_shared_ptr_variant.hpp>

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
	utility::const_shared_ptr_variant
	<
		array,
		fundamental_type,
		class_,
		const_,
		pointer,
		reference,
		volatile_
	>::type
	type_shared_ptr_variant
;

typedef
	utility::const_shared_ptr_variant
	<
		fundamental_type,
		class_
	>::type
	unqualified_type_shared_ptr_variant
;

unqualified_type_shared_ptr_variant
get_unqualified_type(const type_shared_ptr_variant& type);

bool
have_same_qualifiers(const type_shared_ptr_variant& lhs, const type_shared_ptr_variant& rhs);

}}} //namespace scalpel::cpp::semantic_entities

#endif

