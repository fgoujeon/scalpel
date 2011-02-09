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

#ifndef SCALPEL_CPP_LINKING_DETAIL_CREATE_UNIQUE_ID_HPP
#define SCALPEL_CPP_LINKING_DETAIL_CREATE_UNIQUE_ID_HPP

#include <scalpel/cpp/semantic_graph.hpp>

namespace scalpel { namespace cpp { namespace linking { namespace detail
{

//Create the unique id of a semantic entity.
//Every entity object in a namespace has its own unique id, but N entity objects
//located in N different semantic graphs (1 semantic graph = 1 translation unit)
//share the same id if they refer to the same actual entity.
//E.g. a free simple function located in a header file included in N
//translation units will be represented by N simple_function objects in N
//semantic graphs. These objects will share the same id.
//
//The method employed by create_unique_id() is somewhat similar to the
//name mangling performed by conventional compilers.

std::string
create_unique_id(const semantic_entities::class_& entity);

std::string
create_unique_id(const semantic_entities::enum_& entity);

std::string
create_unique_id(const semantic_entities::typedef_& entity);

std::string
create_unique_id(const semantic_entities::constructor& entity);

std::string
create_unique_id(const semantic_entities::destructor& entity);

std::string
create_unique_id(const semantic_entities::operator_member_function& entity);

std::string
create_unique_id(const semantic_entities::conversion_function& entity);

std::string
create_unique_id(const semantic_entities::simple_member_function& entity);

std::string
create_unique_id(const semantic_entities::operator_function& entity);

std::string
create_unique_id(const semantic_entities::simple_function& entity);

std::string
create_unique_id(const semantic_entities::variable& entity);

}}}} //namespace scalpel::cpp::linking::detail

#endif

