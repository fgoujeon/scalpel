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

#ifndef SOCOA_CPP_PROGRAM_SYNTAX_TREE_CLASS_HEAD_H
#define SOCOA_CPP_PROGRAM_SYNTAX_TREE_CLASS_HEAD_H

#include <memory>
#include "class_key.h"

namespace socoa { namespace cpp { namespace program_syntax_tree
{

class nested_name_specifier;
class template_id;
class identifier;
class base_clause;

struct class_head
{
    const class_key key_;
    const std::shared_ptr<nested_name_specifier> nested_name_specifier_;
    const std::shared_ptr<template_id> template_id_;
    const std::shared_ptr<identifier> identifier_;
    const std::shared_ptr<base_clause> base_clause_;
};

}}} //namespace socoa::cpp::program_syntax_tree

#endif
