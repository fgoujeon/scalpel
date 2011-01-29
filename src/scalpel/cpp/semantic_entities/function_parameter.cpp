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
#include "type_variant.hpp"

namespace scalpel { namespace cpp { namespace semantic_entities
{

function_parameter::function_parameter(const type_variant& type, const std::string& name):
	type_(type),
	name_(name)
{
}

function_parameter::function_parameter(const type_variant& type):
	type_(type)
{
}

function_parameter::function_parameter(const function_parameter& o):
	type_(o.type_),
	name_(o.name_)
{
}

function_parameter::function_parameter(function_parameter&& o):
	type_(std::move(o.type_)),
	name_(std::move(o.name_))
{
}

const function_parameter&
function_parameter::operator=(const function_parameter& o)
{
	type_ = o.type_;
	name_ = o.name_;

	return *this;
}

const function_parameter&
function_parameter::operator=(function_parameter&& o)
{
	//type_ = o.type_;
	name_ = std::move(o.name_);

	return *this;
}

const type_variant&
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

