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

#ifndef SOCOA_CPP_PROGRAM_SYNTAX_TREE_SEQUENCE_H
#define SOCOA_CPP_PROGRAM_SYNTAX_TREE_SEQUENCE_H

#include <vector>
#include <memory>

namespace socoa { namespace cpp { namespace program_syntax_tree
{

template <class T>
class sequence
{
    public:
        explicit sequence
        (
            std::vector<std::shared_ptr<T>>&& items
        );

        const std::vector<std::shared_ptr<T>>&
        get_items() const;

    private:
        std::vector<std::shared_ptr<T>> items_;
};

template <class T>
sequence<T>::sequence
(
    std::vector<std::shared_ptr<T>>&& items
):
    items_(items)
{
}

template <class T>
const std::vector<std::shared_ptr<T>>&
sequence<T>::get_items() const
{
    return items_;
}

}}} //namespace socoa::cpp::program_syntax_tree

#endif
