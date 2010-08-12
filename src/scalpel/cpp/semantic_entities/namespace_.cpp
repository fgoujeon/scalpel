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

#include "namespace_.hpp"

namespace scalpel { namespace cpp { namespace semantic_entities
{

namespace_::namespace_()
{
}

namespace_::namespace_(const std::string& name):
    name_(name)
{
}

namespace_::namespace_(namespace_&& n):
	name_(std::move(n.name_)),
	named_entities_(std::move(n.named_entities_)),
	named_declarative_regions_(std::move(n.named_declarative_regions_)),
	namespaces_(std::move(n.namespaces_)),
	classes_(std::move(n.classes_)),
	simple_functions_(std::move(n.simple_functions_)),
	operator_functions_(std::move(n.operator_functions_)),
	variables_(std::move(n.variables_))
{
}

const namespace_&
namespace_::operator=(namespace_&& n)
{
	name_ = std::move(n.name_);
	named_entities_ = std::move(n.named_entities_);
	named_declarative_regions_ = std::move(n.named_declarative_regions_);
	namespaces_ = std::move(n.namespaces_);
	classes_ = std::move(n.classes_);
	simple_functions_ = std::move(n.simple_functions_);
	operator_functions_ = std::move(n.operator_functions_);
	variables_ = std::move(n.variables_);

	return *this;
}

const std::string&
namespace_::name() const
{
    return name_;
}

bool
namespace_::is_open_to_outside() const
{
	return true;
}

namespace_::named_entities_t::range
namespace_::named_entities()
{
	return named_entities_;
}

const namespace_::named_entities_t&
namespace_::named_entities() const
{
	return named_entities_;
}

namespace_::named_declarative_regions_t::range
namespace_::named_declarative_regions()
{
	return named_declarative_regions_;
}

const namespace_::named_declarative_regions_t&
namespace_::named_declarative_regions() const
{
	return named_declarative_regions_;
}

namespace_::namespaces_t::range
namespace_::namespaces()
{
	return namespaces_;
}

const namespace_::namespaces_t&
namespace_::namespaces() const
{
	return namespaces_;
}

namespace_::classes_t::range
namespace_::classes()
{
	return classes_;
}

const namespace_::classes_t&
namespace_::classes() const
{
	return classes_;
}

namespace_::simple_functions_t::range
namespace_::simple_functions()
{
	return simple_functions_;
}

const namespace_::simple_functions_t&
namespace_::simple_functions() const
{
	return simple_functions_;
}

namespace_::operator_functions_t::range
namespace_::operator_functions()
{
	return operator_functions_;
}

const namespace_::operator_functions_t&
namespace_::operator_functions() const
{
	return operator_functions_;
}

namespace_::variables_t::range
namespace_::variables()
{
	return variables_;
}

const namespace_::variables_t&
namespace_::variables() const
{
	return variables_;
}

void
namespace_::add(std::shared_ptr<namespace_> member)
{
    namespaces_.push_back(member);
	named_declarative_regions_.push_back(member);
	named_entities_.push_back(member);
}

void
namespace_::add(std::shared_ptr<class_> member)
{
    classes_.push_back(member);
	named_declarative_regions_.push_back(member);
	named_entities_.push_back(member);
}

void
namespace_::add(std::shared_ptr<simple_function> member)
{
    simple_functions_.push_back(member);
	named_declarative_regions_.push_back(member);
	named_entities_.push_back(member);
}

void
namespace_::add(std::shared_ptr<operator_function> member)
{
    operator_functions_.push_back(member);
	//named_entities_.push_back(member);
}

void
namespace_::add(std::shared_ptr<variable> member)
{
    variables_.push_back(member);
	named_entities_.push_back(member);
}

}}} //namespace scalpel::cpp::semantic_entities

