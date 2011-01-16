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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_FUNCTION_TYPE_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_FUNCTION_TYPE_HPP

#include "type_variant_fwd.hpp"
#include <vector>
#include <memory>

namespace scalpel { namespace cpp { namespace semantic_entities
{

class class_;

class function_type
{
	public:
		function_type
		(
			const class_* parent_class,
			const type_variant& return_type,
			const std::vector<type_variant>& parameter_types,
			const bool variadic,
			const bool const_qualified,
			const bool volatile_qualified
		);

		function_type(const function_type& rhs);

		const class_*
		parent_class() const
		{
			return parent_class_;
		}

		const type_variant&
		return_type() const
		{
			return return_type_;
		}

		const std::vector<type_variant>&
		parameter_types() const
		{
			return parameter_types_;
		}

		bool
		variadic() const
		{
			return variadic_;
		}

		bool
		const_qualified() const
		{
			return const_qualified_;
		}

		bool
		volatile_qualified() const
		{
			return volatile_qualified_;
		}

	private:
		const class_* parent_class_;
		const type_variant return_type_;
		const std::vector<type_variant> parameter_types_;
		const bool variadic_;
		const bool const_qualified_;
		const bool volatile_qualified_;
};

bool
operator==(const function_type& lhs, const function_type& rhs);

}}} //namespace scalpel::cpp::semantic_entities

#endif

