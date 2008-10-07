/*
Socoa - Source Code Analysis Library
Copyright © 2008  Florian Goujeon

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

#ifndef SOCOA_CPP_PROGRAM_TREE_CLASS_H
#define SOCOA_CPP_PROGRAM_TREE_CLASS_H

#include "type.h"
#include "namespace_member.h"

namespace socoa { namespace cpp { namespace program_tree
{

class class_: public type, public namespace_member, public std::enable_shared_from_this<class_>
{
    public:
        enum key
        {
            CLASS,
            STRUCT
        };

        /**
        Creates a named class.
        @param name the class' name
        */
        explicit class_(const std::string& name, key class_key);

    private:
        key key_;
};

}}} //namespace socoa::cpp::program_tree

#endif
