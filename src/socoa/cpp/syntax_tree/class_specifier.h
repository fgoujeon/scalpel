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

#ifndef SOCOA_CPP_SYNTAX_TREE_CLASS_SPECIFIER_H
#define SOCOA_CPP_SYNTAX_TREE_CLASS_SPECIFIER_H

#include <string>
#include <boost/optional.hpp>
#include "visitor.h"
#include "type_specifier.h"
#include "class_head.h"
#include "member_specification.h"

namespace socoa { namespace cpp { namespace syntax_tree
{

class class_specifier: public type_specifier
{
    public:
        class_specifier
        (
            class_head&& head,
            std::shared_ptr<member_specification> a_member_specification
        );

        inline
        const class_head&
        get_class_head() const;

        inline
        const boost::optional<const member_specification&>
        get_member_specification() const;

        SOCOA_CPP_DEFINE_VISITABLE()

    private:
        class_head class_head_;
		boost::optional<member_specification> member_specification_;
};

inline
const class_head&
class_specifier::get_class_head() const
{
    return class_head_;
}

inline
const boost::optional<const member_specification&>
class_specifier::get_member_specification() const
{
    return boost::optional<const member_specification&>(member_specification_);
}

}}} //namespace socoa::cpp::syntax_tree

#endif
