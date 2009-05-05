/*
Socoa - Source Code Analysis Library
Copyright © 2008, 2009  Florian Goujeon

This file is part of Socoa.

Socoa is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Socoa is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Socoa.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SOCOA_CPP_SEMANTIC_ENTITIES_VARIABLE_HPP
#define SOCOA_CPP_SEMANTIC_ENTITIES_VARIABLE_HPP

#include <string>
#include <boost/noncopyable.hpp>
#include "scope.hpp"
#include "named_entity.hpp"

namespace socoa { namespace cpp { namespace semantic_entities
{

/**
Represents a C++ variable.
*/
class variable:
	public named_entity,
	public boost::noncopyable
{
	public:
		variable(const std::string& name);

		variable(std::string&& name);

		variable(variable&& v);

		const variable&
		operator=(variable&& v);

		void
		enclosing_scope(scope& s);

		const std::string&
		name() const;

		bool
		is_a_type() const;

	private:
		scope* enclosing_scope_;
		std::string name_;
};

}}} //namespace socoa::cpp::semantic_entities

#endif
