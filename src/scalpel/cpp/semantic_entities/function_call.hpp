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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_FUNCTION_CALL_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_FUNCTION_CALL_HPP

#include <vector>

namespace scalpel { namespace cpp { namespace semantic_entities
{

class expression_t;

template<class Function>
class function_call
{
	public:
		function_call
		(
			Function& function,
			const std::vector<expression_t>& arguments
		);

		function_call(const function_call&) = default;

		function_call(function_call&&) = default;

		function_call&
		operator=(const function_call&) = delete;

		function_call&
		operator=(function_call&&) = delete;

		const Function&
		function() const
		{
			return function_;
		}

		const std::vector<expression_t>&
		arguments() const
		{
			return arguments_;
		}

	private:
		Function& function_;
		std::vector<expression_t> arguments_;
};

}}} //namespace scalpel::cpp::semantic_entities

#include "function_call.ipp"

#endif

