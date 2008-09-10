/*
Socoa - Source Code Analysis Library
Copyright © 2008  Florian Goujeon

This file is part of Socoa.

Socoa is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, version 3 of the License.

Socoa is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Socoa.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SOCOA_CPP_PROGRAM_TREE_PROGRAM_H
#define SOCOA_CPP_PROGRAM_TREE_PROGRAM_H

#include <memory>
#include "namespace_.h"

namespace socoa { namespace cpp { namespace program_tree
{

/**
Represents a C++ program.
A program can be either an executable or a library.
*/
class program
{
    public:
        program();

        /**
        @return the global namespace of the program.
        */
        std::shared_ptr<namespace_>
        global_namespace();

    private:
        namespace_ m_global_namespace;
        std::shared_ptr<namespace_> m_global_namespace_ptr;
};

}}} //namespace socoa::cpp::program_tree

#endif
