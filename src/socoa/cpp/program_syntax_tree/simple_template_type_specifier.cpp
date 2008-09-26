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

#include <cassert>
#include "simple_template_type_specifier.h"

namespace socoa { namespace cpp { namespace program_syntax_tree
{

simple_template_type_specifier::simple_template_type_specifier
(
    bool leading_double_colon,
    std::shared_ptr<nested_name_specifier> a_nested_name_specifier,
    std::shared_ptr<template_id> a_template_id
):
    m_leading_double_colon(leading_double_colon),
    m_nested_name_specifier(a_nested_name_specifier),
    m_template_id(a_template_id)
{
    assert(a_nested_name_specifier);
    assert(a_template_id);
}

bool
simple_template_type_specifier::has_leading_double_colon() const
{
    return m_leading_double_colon;
}

const std::shared_ptr<nested_name_specifier>
simple_template_type_specifier::get_nested_name_specifier() const
{
    return m_nested_name_specifier;
}

const std::shared_ptr<template_id>
simple_template_type_specifier::get_template_id() const
{
    return m_template_id;
}

}}} //namespace socoa::cpp::program_syntax_tree
