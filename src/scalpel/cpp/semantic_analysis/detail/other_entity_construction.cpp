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

#include "other_entity_construction.hpp"
#include "class_construction.hpp"
#include "function_construction.hpp"
#include "type_construction.hpp"
#include "semantic_entity_analysis/get_namespace.hpp"
#include "semantic_entity_analysis/identification_policies.hpp"
#include "syntax_node_analysis/declarator.hpp"

namespace scalpel { namespace cpp { namespace semantic_analysis { namespace detail
{

using namespace syntax_nodes;
using namespace semantic_entities;


}}}} //namespace scalpel::cpp::semantic_analysis::detail

