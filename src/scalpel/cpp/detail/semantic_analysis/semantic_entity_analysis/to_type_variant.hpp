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

#ifndef SCALPEL_CPP_DETAIL_SEMANTIC_ANALYSIS_SEMANTIC_ENTITY_ANALYSIS_TO_TYPE_SHARED_PTR_VARIANT_HPP
#define SCALPEL_CPP_DETAIL_SEMANTIC_ANALYSIS_SEMANTIC_ENTITY_ANALYSIS_TO_TYPE_SHARED_PTR_VARIANT_HPP

#include <scalpel/cpp/semantic_entities/class_.hpp>
#include <scalpel/cpp/semantic_entities/typedef_.hpp>
#include <scalpel/cpp/semantic_entities/type_variant.hpp>
#include <scalpel/utility/shared_ptr_variant.hpp>
#include <memory>

namespace scalpel { namespace cpp { namespace detail { namespace semantic_analysis { namespace semantic_entity_analysis
{

semantic_entities::type_variant
to_type_variant(const utility::shared_ptr_variant<semantic_entities::class_, semantic_entities::typedef_>::type& var);

}}}}} //namespace scalpel::cpp::detail::semantic_analysis::semantic_entity_analysis

#endif

