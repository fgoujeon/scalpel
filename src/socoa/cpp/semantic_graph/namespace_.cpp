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

#include "namespace_.hpp"

#include <iostream>
#include <cassert>

namespace socoa { namespace cpp { namespace semantic_graph
{

namespace_::namespace_()
{
}

namespace_::namespace_(const std::string& name):
    name_(name)
{
}

/*
namespace_::namespace_(namespace_&& n)
{
}
*/

const std::string&
namespace_::get_name() const
{
    return name_;
}

bool
namespace_::has_that_name(const std::string& name) const
{
    return name_ == name;
}

const std::string
namespace_::get_full_name() const
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
namespace_::is_a_type() const
{
    return false;
}

//bool
//namespace_::is_global() const
//{
//    return !has_enclosing_scope();
//}
//
//bool
//namespace_::has_enclosing_scope() const
//{
//    return !enclosing_scope_.expired();
//}
//
//std::shared_ptr<name_tree_composite>
//namespace_::get_enclosing_scope()
//{
//    return enclosing_scope_.lock();
//}
//
//const std::shared_ptr<name_tree_composite>
//namespace_::get_enclosing_scope() const
//{
//    return enclosing_scope_.lock();
//}
//
//void
//namespace_::set_enclosing_scope(std::shared_ptr<namespace_> enclosing_scope)
//{
//    assert(enclosing_scope_.expired()); //assert that member doesn't have any enclosing scope yet
//    enclosing_scope_ = enclosing_scope;
//}

const std::vector<namespace_::member_t>&
namespace_::get_members() const
{
    return members_;
}

const std::vector<scope*>&
namespace_::get_scopes() const
{
	return scopes_;
}

const std::vector<named_item*>&
namespace_::get_named_items() const
{
	return named_items_;
}

void
namespace_::add(namespace_&& member)
{
    members_.push_back(member);

	namespace_& member_ref = boost::get<namespace_&>(*members_.rbegin());

	scopes_.push_back(&member_ref);
	named_items_.push_back(&member_ref);
}

void
namespace_::add(class_&& member)
{
    members_.push_back(member);

	class_& member_ref = boost::get<class_&>(*members_.rbegin());

	scopes_.push_back(&member_ref);
	named_items_.push_back(&member_ref);
}

void
namespace_::clear()
{
    members_.clear();
	scopes_.clear();
	named_items_.clear();
}

}}} //namespace socoa::cpp::semantic_graph
