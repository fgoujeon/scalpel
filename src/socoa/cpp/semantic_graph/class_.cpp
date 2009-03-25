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

#include "class_.hpp"

#include <iostream>
#include <cassert>
#include "namespace_.hpp"

namespace socoa { namespace cpp { namespace semantic_graph
{

class_::class_(const std::string& name):
    name_(name)
{
	std::cout << "Construction of class " << name_ << std::endl;
}

class_::class_(const class_& c):
	name_(c.name_),
	classes_(c.classes_)
{
	//members_, scopes_ and named_items_ pointers must point to the copied
	//objects.
	for
	(
		std::vector<class_>::iterator i = classes_.begin();
		i != classes_.end();
		++i
	)
	{
		class_* c = &*i;
		members_.push_back(c);
		scopes_.push_back(c);
		named_items_.push_back(c);
	}
}

class_&
class_::operator=(const class_& c)
{
	class_ temp(c);
	std::swap(*this, temp);
	return *this;
}

class_::~class_()
{
	std::cout << "Destruction of class " << name_ << std::endl;
}

const std::string&
class_::get_name() const
{
    return name_;
}

bool
class_::has_that_name(const std::string& name) const
{
    return name_ == name;
}

const std::string
class_::get_full_name() const
{
//    std::string full_name;
//
//    if(has_enclosing_scope() && !get_enclosing_scope()->is_global()) //don't add a leading "::"
//    {
//        full_name = get_enclosing_scope()->get_full_name() + "::";
//    }
//    full_name += name_;
//
//    return full_name;
	return name_;
}

bool
class_::is_a_type() const
{
    return true;
}

bool
class_::is_global() const
{
    return false;
}
/*
bool
class_::has_enclosing_scope() const
{
    return !enclosing_scope_.expired();
}

std::shared_ptr<name_tree_composite>
class_::get_enclosing_scope()
{
    return enclosing_scope_.lock();
}

const std::shared_ptr<name_tree_composite>
class_::get_enclosing_scope() const
{
    return enclosing_scope_.lock();
}

void
class_::set_enclosing_scope(std::shared_ptr<class_> enclosing_scope)
{
    assert(enclosing_scope_.expired()); //assert that member doesn't have any enclosing scope yet
    enclosing_scope_ = enclosing_scope;
}

void
class_::set_enclosing_scope(std::shared_ptr<namespace_> enclosing_scope)
{
    assert(enclosing_scope_.expired()); //assert that member doesn't have any enclosing scope yet
    enclosing_scope_ = enclosing_scope;
}
*/
const std::vector<class_::member_t>&
class_::get_members() const
{
    return members_;
}

const std::vector<scope*>&
class_::get_scopes() const
{
	return scopes_;
}

const std::vector<named_item*>&
class_::get_named_items() const
{
	return named_items_;
}
/*
const std::vector<std::shared_ptr<class_>>&
class_::get_classes() const
{
    return nested_classes_;
}
*/

void
class_::add(class_&& nested_class)
{
	classes_.push_back(nested_class);

	class_* member_ptr = &classes_.back();

	members_.push_back(member_ptr);
	scopes_.push_back(member_ptr);
	named_items_.push_back(member_ptr);
}

/*
const std::vector<base_specifier>&
class_::get_base_specifiers() const
{
    return base_specifiers_;
}

void
class_::add(const base_specifier& specifier)
{
    base_specifiers_.push_back(specifier);
}
*/

}}} //namespace socoa::cpp::semantic_graph
