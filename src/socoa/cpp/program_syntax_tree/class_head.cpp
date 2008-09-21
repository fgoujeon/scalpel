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

#include "class_head.h"

namespace socoa { namespace cpp { namespace program_syntax_tree
{

class_head::class_head
(
    class_key&& key,
    std::shared_ptr<nested_name_specifier> a_nested_name_specifier,
    std::shared_ptr<template_id> a_template_id,
    std::shared_ptr<identifier> an_identifier/*,
    std::shared_ptr<base_clause> a_base_clause*/
):
    m_key(key),
    m_nested_name_specifier(a_nested_name_specifier),
    m_template_id(a_template_id),
    m_identifier(an_identifier)/*,
    std::shared_ptr<base_clause> a_base_clause;*/
{
}

const class_key&
class_head::get_key() const
{
    return m_key;
}

const std::shared_ptr<nested_name_specifier>
class_head::get_nested_name_specifier() const
{
    return m_nested_name_specifier;
}

const std::shared_ptr<template_id>
class_head::get_template_id() const
{
    return m_template_id;
}

const std::shared_ptr<identifier>
class_head::get_identifier() const
{
    return m_identifier;
}

//const std::shared_ptr<base_clause>
//class_head::get_base_clause() const;

}}} //namespace socoa::cpp::program_syntax_tree
