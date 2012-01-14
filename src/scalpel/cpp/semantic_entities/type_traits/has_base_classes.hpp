/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2012  Florian Goujeon

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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_HAS_BASE_CLASSES_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_HAS_BASE_CLASSES_HPP

#include <scalpel/cpp/semantic_graph.hpp>

namespace scalpel { namespace cpp { namespace semantic_entities { namespace type_traits
{

template<class Entity>
struct has_base_classes
{
	static const bool value = false;
};

template<>
struct has_base_classes<class_>
{
	static const bool value = true;
};

template<>
struct has_base_classes<member_class>
{
	static const bool value = true;
};

}}}} //namespace scalpel::cpp::semantic_entities::type_traits

#endif

