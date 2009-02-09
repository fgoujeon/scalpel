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

#ifndef SOCOA_CPP_PROGRAM_TREE_BASE_SPECIFIER_H
#define SOCOA_CPP_PROGRAM_TREE_BASE_SPECIFIER_H

#include <memory>
#include "../syntax_tree/access_specifier.h"

namespace socoa { namespace cpp { namespace semantic_graph
{

class class_;

class base_specifier
{
    public:
        base_specifier
        (
            std::shared_ptr<class_> a_class,
            syntax_tree::access_specifier access_specifier,
            bool is_virtual = false
        );

        const std::shared_ptr<class_>
        get_class() const
        {
            return base_class_;
        }

        const syntax_tree::access_specifier&
        get_access_specifier() const
        {
            return access_specifier_;
        }

        bool
        is_virtual() const
        {
            return virtual_;
        }

    private:
        std::shared_ptr<class_> base_class_;
        syntax_tree::access_specifier access_specifier_;
        bool virtual_;
};

}}} //namespace socoa::cpp::semantic_graph

#endif
