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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_NAMESPACE_ALIAS_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_NAMESPACE_ALIAS_HPP

#include <string>

namespace scalpel { namespace cpp { namespace semantic_entities
{

class namespace_;

/**
Represents a C++ namespace alias.
*/
class namespace_alias
{
	public:
		namespace_alias
		(
			const std::string name,
			namespace_& referred_namespace
		);

		const std::string&
		name() const
		{
			return name_;
		}

		namespace_&
		referred_namespace()
		{
			return referred_namespace_;
		}

		const namespace_&
		referred_namespace() const
		{
			return referred_namespace_;
		}

	private:
		std::string name_;
		namespace_& referred_namespace_;
};

}}} //namespace scalpel::cpp::semantic_entities

#endif

