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

#include "template_argument_list.h"

namespace socoa { namespace cpp { namespace program_syntax_tree
{

template_argument_list::template_argument_list
(
    std::vector<std::shared_ptr<template_argument>>&& arguments
):
    arguments_(arguments)
{
}

const std::vector<std::shared_ptr<template_argument>>&
template_argument_list::get_arguments() const
{
    return arguments_;
}

}}} //namespace socoa::cpp::program_syntax_tree
