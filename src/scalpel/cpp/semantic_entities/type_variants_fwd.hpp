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

#include "fundamental_type.hpp"
#include <scalpel/utility/const_shared_ptr_variant.hpp>
#include <scalpel/utility/variant.hpp>

namespace scalpel { namespace cpp { namespace semantic_entities
{

class array;
class class_;
class const_;
class pointer;
class reference;
class typedef_;
class volatile_;

typedef
	utility::variant
	<
		array,
		fundamental_type,
		std::shared_ptr<const class_>,
		const_,
		pointer,
		reference,
		volatile_
	>::type
	type_variant
;

typedef
	utility::variant
	<
		array,
		fundamental_type,
		std::weak_ptr<const class_>,
		const_,
		pointer,
		reference,
		volatile_
	>::type
	weak_type_variant
;

typedef
	utility::variant
	<
		fundamental_type,
		std::weak_ptr<const class_>
	>::type
	unqualified_type_variant
;

//perform a recursive value comparison for qualifier instances,
//a value comparison for fundamental_type instances and a pointer
//comparison for class_ instances
//TODO find a more expressive name
bool
equals(const type_variant& lhs, const type_variant& rhs);

bool
equals(const weak_type_variant& lhs, const weak_type_variant& rhs);

bool
have_same_qualifiers(const type_variant& lhs, const type_variant& rhs);

unqualified_type_variant
get_unqualified_type(const weak_type_variant& type);

weak_type_variant
to_weak_type_variant(const type_variant& type);

type_variant
to_type_variant(const weak_type_variant& type);

}}} //namespace scalpel::cpp::semantic_entities

#endif

