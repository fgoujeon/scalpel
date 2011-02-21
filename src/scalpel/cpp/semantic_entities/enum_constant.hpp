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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_ENUM_CONSTANT_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_ENUM_CONSTANT_HPP

#include <string>

namespace scalpel { namespace cpp { namespace semantic_entities
{

class enum_constant
{
	public:
        enum_constant(const std::string& name, const int value);

        enum_constant(const enum_constant&) = delete;

        enum_constant&
		operator=(const enum_constant&) = delete;

		const std::string&
		name() const
		{
			return name_;
		}

		int
		value() const
		{
			return value_;
		}

	private:
		std::string name_;
		int value_;
};

}}} //namespace scalpel::cpp::semantic_entities

#endif

