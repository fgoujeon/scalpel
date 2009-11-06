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

#include "variable.hpp"

#include <iostream>

namespace scalpel { namespace cpp { namespace semantic_entities
{

variable::variable(std::unique_ptr<type> t, const std::string& name):
	type_(std::move(t)),
	name_(name)
{
	std::cout << "New variable " << name << "\n";
}

variable::variable(std::unique_ptr<type> t, std::string&& name):
	type_(std::move(t)),
	name_(std::move(name))
{
	std::cout << "New variable " << name << "\n";
}

variable::variable(variable&& v):
	type_(std::move(v.type_)),
	name_(std::move(v.name_))
{
}

const variable&
variable::operator=(variable&& v)
{
	name_ = std::move(v.name_);

	return *this;
}

const type&
variable::get_type() const
{
	return *type_;
}

const std::string&
variable::name() const
{
	return name_;
}

bool
variable::is_a_type() const
{
	return false;
}

}}} //namespace scalpel::cpp::semantic_entities

