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

#include "function_parameter_list.hpp"
#include "type_variants.hpp"
#include <scalpel/utility/are_pointed_objects_equal.hpp>

namespace scalpel { namespace cpp { namespace semantic_entities
{

bool
operator==(const function_parameter_list& lhs, const function_parameter_list& rhs)
{
	return utility::are_pointed_objects_equal(lhs, rhs);
}

bool
operator!=(const function_parameter_list& lhs, const function_parameter_list& rhs)
{
	return !operator==(lhs, rhs);
}

bool
have_same_types(const function_parameter_list& lhs, const function_parameter_list& rhs)
{
	if(lhs.size() != rhs.size())
		return false;

	for(auto i = lhs.begin(), j = rhs.begin(); i != lhs.end(); ++i, ++j)
	{
		const std::shared_ptr<const function_parameter>& lhs_param = *i;
		const std::shared_ptr<const function_parameter>& rhs_param = *j;

		if(!utility::are_pointed_objects_equal(lhs_param->type(), rhs_param->type()))
			return false;
	}

	return true;
}

}}} //namespace scalpel::cpp::semantic_entities

