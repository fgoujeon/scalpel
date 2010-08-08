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

#include "empty_class_shared_ptr_vector.hpp"
#include "../class_.hpp"
#include <scalpel/utility/shared_ptr_vector.hpp>

namespace scalpel { namespace cpp { namespace semantic_entities { namespace detail
{

utility::shared_ptr_vector<class_> empty_vector;
utility::shared_ptr_vector<class_>::range empty_class_shared_ptr_vector_range(empty_vector.pointers());

}}}} //namespace scalpel::cpp::semantic_entities

