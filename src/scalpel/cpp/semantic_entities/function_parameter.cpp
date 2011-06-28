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

#include "function_parameter.hpp"
#include "type.hpp"

namespace scalpel { namespace cpp { namespace semantic_entities
{

function_parameter::function_parameter(const type_t& type, const std::string& name):
	type_(type),
	name_(name)
{
}

function_parameter::function_parameter(const type_t& type):
	type_(type)
{
}

const type_t&
function_parameter::type() const
{
	return type_;
}

const std::string&
function_parameter::name() const
{
	return name_;
}

}}} //namespace scalpel::cpp::semantic_entities

