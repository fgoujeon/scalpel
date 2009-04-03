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

#include "variable.hpp"

#include <iostream>

namespace socoa { namespace cpp { namespace semantic_graph
{

variable::variable(std::string&& name):
	enclosing_scope_(0),
	name_(std::move(name))
{
	std::cout << "New variable " << name << "\n";
}

variable::variable(variable&& v):
	enclosing_scope_(0),
	name_(std::move(v.name_))
{
	assert(v.enclosing_scope_ == 0);
}

const variable&
variable::operator=(variable&& v)
{
	assert(v.enclosing_scope_ == 0);
	name_ = std::move(v.name_);

	return *this;
}

void
variable::set_enclosing_scope(scope& s)
{
	enclosing_scope_ = &s;
}

const std::string&
variable::get_name() const
{
	return name_;
}

bool
variable::has_that_name(const std::string& name) const
{
	return name == name_;
}

bool
variable::is_a_type() const
{
	return false;
}

}}} //namespace socoa::cpp::semantic_graph

