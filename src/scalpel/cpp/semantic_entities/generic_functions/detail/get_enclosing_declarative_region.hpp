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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_GENERIC_FUNCTIONS_DETAIL_GET_ENCLOSING_DECLARATIVE_REGION_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_GENERIC_FUNCTIONS_DETAIL_GET_ENCLOSING_DECLARATIVE_REGION_HPP

#include <scalpel/cpp/semantic_graph.hpp>
#include <scalpel/utility/const_ptr_variant.hpp>

namespace scalpel { namespace cpp { namespace semantic_entities { namespace generic_functions { namespace detail
{

typename utility::const_ptr_variant
<
	namespace_
>::type
get_enclosing_declarative_region(const namespace_& entity)
{
	assert(entity.has_enclosing_declarative_region());
	return entity.enclosing_declarative_region();
}

typename utility::const_ptr_variant
<
	namespace_
>::type
get_enclosing_declarative_region(const class_& entity)
{
	assert(entity.has_enclosing_declarative_region());
	declarative_region_ptr_variant edr = entity.enclosing_declarative_region();
	return static_cast<const namespace_*>(utility::get<namespace_*>(edr));
}

typename utility::const_ptr_variant
<
	class_
>::type
get_enclosing_declarative_region(const member_class& entity)
{
	assert(entity.has_enclosing_declarative_region());
	declarative_region_ptr_variant edr = entity.enclosing_declarative_region();
	return static_cast<const class_*>(utility::get<class_*>(edr));
}

typename utility::const_ptr_variant
<
	namespace_
>::type
get_enclosing_declarative_region(const enum_& entity)
{
	assert(entity.has_enclosing_declarative_region());
	declarative_region_ptr_variant edr = entity.enclosing_declarative_region();
	return static_cast<const namespace_*>(utility::get<namespace_*>(edr));
}

typename utility::const_ptr_variant
<
	class_
>::type
get_enclosing_declarative_region(const member_enum& entity)
{
	assert(entity.has_enclosing_declarative_region());
	declarative_region_ptr_variant edr = entity.enclosing_declarative_region();
	return static_cast<const class_*>(utility::get<class_*>(edr));
}

typename utility::const_ptr_variant
<
	namespace_
>::type
get_enclosing_declarative_region(const typedef_& entity)
{
	assert(entity.has_enclosing_declarative_region());
	declarative_region_ptr_variant edr = entity.enclosing_declarative_region();
	return static_cast<const namespace_*>(utility::get<namespace_*>(edr));
}

typename utility::const_ptr_variant
<
	class_
>::type
get_enclosing_declarative_region(const member_typedef& entity)
{
	assert(entity.has_enclosing_declarative_region());
	declarative_region_ptr_variant edr = entity.enclosing_declarative_region();
	return static_cast<const class_*>(utility::get<class_*>(edr));
}

typename utility::const_ptr_variant
<
	class_
>::type
get_enclosing_declarative_region(const constructor& entity)
{
	assert(entity.has_enclosing_declarative_region());
	declarative_region_ptr_variant edr = entity.enclosing_declarative_region();
	return static_cast<const class_*>(utility::get<class_*>(edr));
}

typename utility::const_ptr_variant
<
	class_
>::type
get_enclosing_declarative_region(const destructor& entity)
{
	assert(entity.has_enclosing_declarative_region());
	declarative_region_ptr_variant edr = entity.enclosing_declarative_region();
	return static_cast<const class_*>(utility::get<class_*>(edr));
}

typename utility::const_ptr_variant
<
	class_
>::type
get_enclosing_declarative_region(const operator_member_function& entity)
{
	assert(entity.has_enclosing_declarative_region());
	declarative_region_ptr_variant edr = entity.enclosing_declarative_region();
	return static_cast<const class_*>(utility::get<class_*>(edr));
}

typename utility::const_ptr_variant
<
	class_
>::type
get_enclosing_declarative_region(const conversion_function& entity)
{
	assert(entity.has_enclosing_declarative_region());
	declarative_region_ptr_variant edr = entity.enclosing_declarative_region();
	return static_cast<const class_*>(utility::get<class_*>(edr));
}

typename utility::const_ptr_variant
<
	class_
>::type
get_enclosing_declarative_region(const simple_member_function& entity)
{
	assert(entity.has_enclosing_declarative_region());
	declarative_region_ptr_variant edr = entity.enclosing_declarative_region();
	return static_cast<const class_*>(utility::get<class_*>(edr));
}

typename utility::const_ptr_variant
<
	namespace_
>::type
get_enclosing_declarative_region(const operator_function& entity)
{
	assert(entity.has_enclosing_declarative_region());
	declarative_region_ptr_variant edr = entity.enclosing_declarative_region();
	return static_cast<const namespace_*>(utility::get<namespace_*>(edr));
}

typename utility::const_ptr_variant
<
	namespace_
>::type
get_enclosing_declarative_region(const simple_function& entity)
{
	assert(entity.has_enclosing_declarative_region());
	declarative_region_ptr_variant edr = entity.enclosing_declarative_region();
	return static_cast<const namespace_*>(utility::get<namespace_*>(edr));
}

typename utility::const_ptr_variant
<
	namespace_
>::type
get_enclosing_declarative_region(const variable& entity)
{
	assert(entity.has_enclosing_declarative_region());
	declarative_region_ptr_variant edr = entity.enclosing_declarative_region();
	return static_cast<const namespace_*>(utility::get<namespace_*>(edr));
}

typename utility::const_ptr_variant
<
	class_
>::type
get_enclosing_declarative_region(const member_variable& entity)
{
	assert(entity.has_enclosing_declarative_region());
	declarative_region_ptr_variant edr = entity.enclosing_declarative_region();
	return static_cast<const class_*>(utility::get<class_*>(edr));
}

}}}}} //namespace scalpel::cpp::semantic_entities::generic_functions::detail

#endif

