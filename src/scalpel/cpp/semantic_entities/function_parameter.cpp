/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2010  Florian Goujeon

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
#include "type_variants.hpp"
#include <scalpel/utility/are_pointed_objects_equal.hpp>

namespace scalpel { namespace cpp { namespace semantic_entities
{

function_parameter::function_parameter(const type_variant& t, const std::string& name):
	type_(to_weak_type_variant(t)),
	name_(name)
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
	type_ = o.type_;
	name_ = std::move(o.name_);

	return *this;
}

type_variant
function_parameter::type() const
{
	return to_type_variant(type_);
}

const std::string&
function_parameter::name() const
{
	return name_;
}

bool
operator==(const function_parameter& lhs, const function_parameter& rhs)
{
	return
		lhs.name() == rhs.name() &&
		lhs.type() == rhs.type()
	;
}

bool
operator!=(const function_parameter& lhs, const function_parameter& rhs)
{
	return !operator==(lhs, rhs);
}

}}} //namespace scalpel::cpp::semantic_entities

