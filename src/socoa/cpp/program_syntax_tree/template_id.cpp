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

#include "template_id.h"

namespace socoa { namespace cpp { namespace program_syntax_tree
{

template_id::template_id
(
    identifier&& an_identifier,
    std::shared_ptr<template_argument_list> a_template_argument_list
):
    identifier_(an_identifier),
    template_argument_list_(a_template_argument_list)
{
}

const identifier&
template_id::get_identifier() const
{
    return identifier_;
}

const std::shared_ptr<template_argument_list>&
template_id::get_template_argument_list() const
{
    return template_argument_list_;
}

}}} //namespace socoa::cpp::program_syntax_tree
