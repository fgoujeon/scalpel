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

#include "namespace_.hpp"

#include <iostream>
#include <cassert>

namespace scalpel { namespace cpp { namespace semantic_entities
{

namespace_::namespace_()
{
	std::cout << "New anonymous namespace\n";
}

namespace_::namespace_(const std::string& name):
    name_(name)
{
	std::cout << "New namespace " << name << "\n";
}

namespace_::namespace_(namespace_&& n):
	named_scope_impl_(std::move(n.named_scope_impl_)),
	name_(std::move(n.name_)),
	namespaces_(std::move(n.namespaces_)),
	classes_(std::move(n.classes_)),
	functions_(std::move(n.functions_)),
	operator_functions_(std::move(n.operator_functions_)),
	variables_(std::move(n.variables_))
{
}

const namespace_&
namespace_::operator=(namespace_&& n)
{
	named_scope_impl_ = std::move(n.named_scope_impl_);
	name_ = std::move(n.name_);
	namespaces_ = std::move(n.namespaces_);
	classes_ = std::move(n.classes_);
	functions_ = std::move(n.functions_);
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
namespace_::is_a_type() const
{
    return false;
}

named_scope::named_scope_iterator_range
namespace_::named_scopes()
{
	return named_scope_impl_.named_scopes();
}

named_scope::named_scope_const_iterator_range
namespace_::named_scopes() const
{
	return named_scope_impl_.named_scopes();
}

named_scope::named_entity_iterator_range
namespace_::named_entities()
{
	return named_scope_impl_.named_entities();
}

named_scope::named_entity_const_iterator_range
namespace_::named_entities() const
{
	return named_scope_impl_.named_entities();
}

namespace_::namespace_const_iterator_range
namespace_::namespaces() const
{
	return namespaces_;
}

namespace_::class_const_iterator_range
namespace_::classes() const
{
	return classes_;
}

namespace_::function_const_iterator_range
namespace_::functions() const
{
	return functions_;
}

namespace_::operator_function_const_iterator_range
namespace_::operator_functions() const
{
	return operator_functions_;
}

namespace_::variable_const_iterator_range
namespace_::variables() const
{
	return variables_;
}

void
namespace_::add(std::shared_ptr<namespace_> member)
{
    namespaces_.push_back(member);
	named_scope_impl_.add_to_named_scopes(member);
	named_scope_impl_.add_to_named_entities(member);
}

void
namespace_::add(std::shared_ptr<class_> member)
{
    classes_.push_back(member);
	named_scope_impl_.add_to_named_scopes(member);
	named_scope_impl_.add_to_named_entities(member);
}

void
namespace_::add(std::shared_ptr<function> member)
{
    functions_.push_back(member);
	named_scope_impl_.add_to_named_entities(member);
}

void
namespace_::add(std::shared_ptr<operator_function> member)
{
    operator_functions_.push_back(member);
	//named_scope_impl_.add_to_named_entities(member);
}

void
namespace_::add(std::shared_ptr<variable> member)
{
    variables_.push_back(member);
	named_scope_impl_.add_to_named_entities(member);
}

}}} //namespace scalpel::cpp::semantic_entities
