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

#ifndef SOCOA_CPP_SYNTAX_TREE_CLASS_HEAD_H
#define SOCOA_CPP_SYNTAX_TREE_CLASS_HEAD_H

#include <memory>
#include "class_key.h"

namespace socoa { namespace cpp { namespace syntax_tree
{

class nested_name_specifier;
class template_id;
class identifier;
class base_clause;

class class_head
{
    public:
        class_head
        (
            class_key&& a_class_key,
            std::shared_ptr<nested_name_specifier> a_nested_name_specifier,
            std::shared_ptr<template_id> a_template_id,
            std::shared_ptr<identifier> an_identifier,
            std::shared_ptr<base_clause> a_base_clause
        );

        inline
        const class_key&
        get_class_key() const;

        inline
        const std::shared_ptr<const nested_name_specifier>
        get_nested_name_specifier() const;

        inline
        const std::shared_ptr<const template_id>
        get_template_id() const;

        inline
        const std::shared_ptr<const identifier>
        get_identifier() const;

        inline
        const std::shared_ptr<const base_clause>
        get_base_clause() const;

    private:
        class_key class_key_;
        std::shared_ptr<nested_name_specifier> nested_name_specifier_;
        std::shared_ptr<template_id> template_id_;
        std::shared_ptr<identifier> identifier_;
        std::shared_ptr<base_clause> base_clause_;
};

inline
const class_key&
class_head::get_class_key() const
{
    return class_key_;
}

inline
const std::shared_ptr<const nested_name_specifier>
class_head::get_nested_name_specifier() const
{
    return nested_name_specifier_;
}

inline
const std::shared_ptr<const template_id>
class_head::get_template_id() const
{
    return template_id_;
}

inline
const std::shared_ptr<const identifier>
class_head::get_identifier() const
{
    return identifier_;
}

inline
const std::shared_ptr<const base_clause>
class_head::get_base_clause() const
{
    return base_clause_;
}

}}} //namespace socoa::cpp::syntax_tree

#endif
