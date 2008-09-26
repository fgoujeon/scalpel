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

#ifndef SOCOA_CPP_PROGRAM_SYNTAX_TREE_SIMPLE_TEMPLATE_TYPE_SPECIFIER_H
#define SOCOA_CPP_PROGRAM_SYNTAX_TREE_SIMPLE_TEMPLATE_TYPE_SPECIFIER_H

#include <memory>
#include "simple_type_specifier.h"

namespace socoa { namespace cpp { namespace program_syntax_tree
{

class nested_name_specifier;
class template_id;

class simple_template_type_specifier: public simple_type_specifier
{
    public:
        simple_template_type_specifier
        (
            bool leading_double_colon,
            std::shared_ptr<nested_name_specifier> a_nested_name_specifier,
            std::shared_ptr<template_id> a_template_id
        );

        bool
        has_leading_double_colon() const;

        const std::shared_ptr<nested_name_specifier>
        get_nested_name_specifier() const;

        const std::shared_ptr<template_id>
        get_template_id() const;

        SOCOA_CPP_DEFINE_VISITABLE()

    private:
        bool m_leading_double_colon;
        std::shared_ptr<nested_name_specifier> m_nested_name_specifier;
        std::shared_ptr<template_id> m_template_id;
};

}}} //namespace socoa::cpp::program_syntax_tree

#endif
