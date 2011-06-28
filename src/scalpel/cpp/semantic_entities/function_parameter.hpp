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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_FUNCTION_PARAMETER_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_FUNCTION_PARAMETER_HPP

#include "type.hpp"
#include <string>

namespace scalpel { namespace cpp { namespace semantic_entities
{

class function_parameter
{
	public:
		function_parameter(const type_t& type, const std::string& name);

		explicit
		function_parameter(const type_t& type);

		function_parameter(const function_parameter&) = delete;

		function_parameter&
		operator=(const function_parameter& o) = delete;

		const type_t&
		type() const;

		const std::string&
		name() const;

	private:
		type_t type_;
		std::string name_;
};

}}} //namespace scalpel::cpp::semantic_entities

#endif

