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

#include "class_head.h"

namespace socoa { namespace cpp { namespace syntax_tree
{

class_head::class_head
(
    class_key&& a_class_key,
    std::shared_ptr<nested_name_specifier> a_nested_name_specifier,
    std::shared_ptr<template_id> a_template_id,
    std::shared_ptr<identifier> an_identifier,
    std::shared_ptr<base_clause> a_base_clause
):
    class_key_(a_class_key),
    nested_name_specifier_(a_nested_name_specifier),
    template_id_(a_template_id),
    identifier_(an_identifier),
    base_clause_(a_base_clause)
{
}


}}} //namespace socoa::cpp::syntax_tree
