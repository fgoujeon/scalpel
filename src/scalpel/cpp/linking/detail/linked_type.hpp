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

#ifndef SCALPEL_CPP_LINKING_DETAIL_GENERATE_TYPE_TRAITS_HPP
#define SCALPEL_CPP_LINKING_DETAIL_GENERATE_TYPE_TRAITS_HPP

#include <scalpel/cpp/semantic_graph.hpp>

namespace scalpel { namespace cpp { namespace linking { namespace detail
{

template<class Entity>
struct linked_type
{
	typedef Entity type;
};

template<class Entity>
struct nonlinked_type
{
	typedef Entity type;
};

#define GENERATE_TYPE_TRAITS(NONLINKED_TYPE, LINKED_TYPE) \
template<> \
struct linked_type<semantic_entities::NONLINKED_TYPE> \
{ \
	typedef semantic_entities::LINKED_TYPE type; \
}; \
 \
template<> \
struct nonlinked_type<semantic_entities::LINKED_TYPE> \
{ \
	typedef semantic_entities::NONLINKED_TYPE type; \
};

GENERATE_TYPE_TRAITS(namespace_, linked_namespace)
GENERATE_TYPE_TRAITS(unnamed_namespace, linked_unnamed_namespace)

#undef GENERATE_TYPE_TRAITS

}}}} //namespace scalpel::cpp::linking::detail

#endif

