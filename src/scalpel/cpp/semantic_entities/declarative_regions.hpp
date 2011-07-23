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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_DECLARATIVE_REGIONS_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_DECLARATIVE_REGIONS_HPP

#include <scalpel/utility/variant.hpp>
#include <scalpel/utility/ptr_variant.hpp>
#include <memory>

namespace scalpel { namespace cpp { namespace semantic_entities
{

class namespace_;
class linked_namespace;
class unnamed_namespace;
class linked_unnamed_namespace;
class namespace_alias;
class class_;
class member_class;
class union_;
class member_union;
class anonymous_union;
class anonymous_member_union;
class enum_t;
class member_enum_t;
class constructor;
class destructor;
class operator_function;
class operator_member_function;
class conversion_function;
class simple_function;
class simple_member_function;
class statement_block;
class typedef_;

typedef
	scalpel::utility::ptr_variant
	<
		namespace_,
		linked_namespace,
		unnamed_namespace,
		linked_unnamed_namespace,
		class_,
		member_class,
		union_,
		member_union,
		anonymous_union,
		anonymous_member_union,
		enum_t,
		member_enum_t,
		constructor,
		destructor,
		operator_function,
		operator_member_function,
		conversion_function,
		simple_function,
		simple_member_function,
		statement_block
	>::type
	declarative_region_t
;

//Open declarative regions are those considered during a qualified name lookup.
//E.g. if we look up to "X::Y::Z::name", X, Y and Z refer directly or
//indirectly (through a namespace alias or a typedef) to three open declarative
//regions.
typedef
	scalpel::utility::ptr_variant
	<
		namespace_,
		class_,
		member_class,
		union_,
		member_union,
		enum_t,
		member_enum_t
	>::type
	open_declarative_region_t
;

typedef
	utility::ptr_variant
	<
		namespace_,
		unnamed_namespace,
		class_,
		member_class,
		union_,
		member_union
	>::type
	function_enclosing_declarative_region_t
;

declarative_region_t
get_enclosing_declarative_region(const declarative_region_t& var);

}}} //namespace scalpel::cpp::semantic_entities

#endif

