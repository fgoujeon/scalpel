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

#ifndef SCALPEL_CPP_SEMANTIC_ANALYSIS_DETAIL_SEMANTIC_ENTITY_ANALYSIS_TO_TYPE_HPP
#define SCALPEL_CPP_SEMANTIC_ANALYSIS_DETAIL_SEMANTIC_ENTITY_ANALYSIS_TO_TYPE_HPP

#include <scalpel/cpp/semantic_entities/type.hpp>
#include <scalpel/cpp/semantic_entities/typedef_.hpp>
#include <scalpel/utility/ptr_variant.hpp>

namespace scalpel { namespace cpp { namespace semantic_analysis { namespace detail { namespace semantic_entity_analysis
{

semantic_entities::type_t
to_type
(
	const typename utility::ptr_variant
	<
		semantic_entities::class_,
		semantic_entities::member_class,
		semantic_entities::union_,
		semantic_entities::member_union,
		semantic_entities::typedef_,
		semantic_entities::member_typedef,
		semantic_entities::enum_,
		semantic_entities::member_enum
	>::type& var
);

}}}}} //namespace scalpel::cpp::semantic_analysis::detail::semantic_entity_analysis

#endif

