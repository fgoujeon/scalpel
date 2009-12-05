/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008, 2009  Florian Goujeon

This file is part of Scalpel.

Scalpel is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Scalpel is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Scalpel.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_VARIABLE_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_VARIABLE_HPP

#include <string>
#include <memory>
#include <boost/noncopyable.hpp>
#include "type.hpp"
#include "named_scope.hpp"
#include "named_entity.hpp"

namespace scalpel { namespace cpp { namespace semantic_entities
{

/**
Represents a C++ variable.
*/
class variable:
	public named_entity
{
	public:
		variable(std::shared_ptr<const type> t, const std::string& name, bool is_static_specified);

		variable(const variable& v);

		variable(variable&& v);

		const variable&
		operator=(variable&& v);

		std::shared_ptr<const type>
		get_type() const;

		const std::string&
		name() const;

		bool
		static_specified() const;

		bool
		is_a_type() const;

	private:
		std::shared_ptr<const type> type_;
		std::string name_;
		bool static_specified_;
};

}}} //namespace scalpel::cpp::semantic_entities

#endif
