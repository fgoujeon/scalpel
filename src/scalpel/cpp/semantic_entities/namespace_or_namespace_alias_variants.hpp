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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_NAMESPACE_OR_NAMESPACE_ALIAS_VARIANTS_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_NAMESPACE_OR_NAMESPACE_ALIAS_VARIANTS_HPP

#include <scalpel/utility/variant.hpp>
#include <memory>

namespace scalpel { namespace cpp { namespace semantic_entities
{

class namespace_;
class namespace_alias;

typedef
	scalpel::utility::variant
	<
		std::shared_ptr<namespace_>,
		std::shared_ptr<namespace_alias>
	>::type
	namespace_or_namespace_alias_shared_ptr_variant
;

const std::string&
get_name(const namespace_or_namespace_alias_shared_ptr_variant var);

std::shared_ptr<namespace_>
get_namespace(const namespace_or_namespace_alias_shared_ptr_variant var);

}}} //namespace scalpel::cpp::semantic_entities

#endif

