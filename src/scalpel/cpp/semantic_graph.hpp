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

#ifndef SCALPEL_CPP_SEMANTIC_GRAPH_HPP
#define SCALPEL_CPP_SEMANTIC_GRAPH_HPP

#include "semantic_entities/array.hpp"
#include "semantic_entities/base_class.hpp"
#include "semantic_entities/class_.hpp"
#include "semantic_entities/cv_qualified_type.hpp"
#include "semantic_entities/declarative_regions.hpp"
#include "semantic_entities/enum.hpp"
#include "semantic_entities/enum_constant.hpp"
#include "semantic_entities/expression.hpp"
#include "semantic_entities/expressions.hpp"
#include "semantic_entities/function_type.hpp"
#include "semantic_entities/functions.hpp"
#include "semantic_entities/fundamental_type.hpp"
#include "semantic_entities/member_access.hpp"
#include "semantic_entities/namespace_.hpp"
#include "semantic_entities/namespace_alias.hpp"
#include "semantic_entities/namespace_variant_fwd.hpp"
#include "semantic_entities/overloadable_operator.hpp"
#include "semantic_entities/pointer.hpp"
#include "semantic_entities/pointer_to_member.hpp"
#include "semantic_entities/reference.hpp"
#include "semantic_entities/statement_block.hpp"
#include "semantic_entities/type.hpp"
#include "semantic_entities/typedef_.hpp"
#include "semantic_entities/variable.hpp"

namespace scalpel { namespace cpp
{

typedef semantic_entities::namespace_ semantic_graph;
typedef semantic_entities::linked_namespace linked_semantic_graph;

}} //namespace scalpel::cpp

#endif

