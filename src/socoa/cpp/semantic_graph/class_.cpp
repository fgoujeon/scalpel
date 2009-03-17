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
    std::cout << "new class " << get_full_name() << std::endl;
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
    std::string full_name;

//    if(has_enclosing_scope() && !get_enclosing_scope()->is_global()) //don't add a leading "::"
//    {
//        full_name = get_enclosing_scope()->get_full_name() + "::";
//    }
//    full_name += name_;

    return full_name;
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
    members_.push_back(nested_class);

	class_& member_ref = boost::get<class_&>(*members_.rbegin());

	scopes_.push_back(&member_ref);
	named_items_.push_back(&member_ref);
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
