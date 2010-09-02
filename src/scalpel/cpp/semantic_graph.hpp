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

#ifndef SCALPEL_CPP_SEMANTIC_GRAPH_HPP
#define SCALPEL_CPP_SEMANTIC_GRAPH_HPP

#include "semantic_entities/array.hpp"
#include "semantic_entities/fundamental_type.hpp"
#include "semantic_entities/fundamental_type_shared_ptrs.hpp"
#include "semantic_entities/class_.hpp"
#include "semantic_entities/const_.hpp"
#include "semantic_entities/declarative_region_variants.hpp"
#include "semantic_entities/namespace_.hpp"
#include "semantic_entities/operator_.hpp"
#include "semantic_entities/operator_function.hpp"
#include "semantic_entities/pointer.hpp"
#include "semantic_entities/reference.hpp"
#include "semantic_entities/simple_function.hpp"
#include "semantic_entities/statement_block.hpp"
#include "semantic_entities/type_variants.hpp"
#include "semantic_entities/variable.hpp"
#include "semantic_entities/volatile_.hpp"

namespace scalpel { namespace cpp
{

typedef semantic_entities::namespace_ semantic_graph;

}} //namespace scalpel::cpp

#endif
