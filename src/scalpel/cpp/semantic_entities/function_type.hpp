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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_FUNCTION_TYPE_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_FUNCTION_TYPE_HPP

#include "type_fwd.hpp"
#include <vector>
#include <memory>

namespace scalpel { namespace cpp { namespace semantic_entities
{

class function_type
{
	public:
		typedef std::vector<type_t> parameter_types_t;

		function_type
		(
			const type_t& return_type,
			const parameter_types_t& parameter_types,
			const bool variadic,
			const bool const_qualified,
			const bool volatile_qualified
		);

		function_type(const function_type& rhs);

		function_type&
		operator=(const function_type& rhs);

		const type_t&
		return_type() const;

		const parameter_types_t&
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
		std::unique_ptr<type_t> return_type_;
		parameter_types_t parameter_types_;
		bool variadic_;
		bool const_qualified_;
		bool volatile_qualified_;
};

bool
operator==(const function_type& lhs, const function_type& rhs);

bool
operator!=(const function_type& lhs, const function_type& rhs);

}}} //namespace scalpel::cpp::semantic_entities

#endif

