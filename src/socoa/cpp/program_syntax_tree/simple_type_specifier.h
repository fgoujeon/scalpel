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

#ifndef SOCOA_CPP_PROGRAM_SYNTAX_TREE_SIMPLE_TYPE_SPECIFIER_H
#define SOCOA_CPP_PROGRAM_SYNTAX_TREE_SIMPLE_TYPE_SPECIFIER_H

#include <memory>
#include "type_specifier.h"

namespace socoa { namespace cpp { namespace program_syntax_tree
{

class nested_name_specifier;
class identifier_or_template_id;
class template_id;

class simple_type_specifier: public type_specifier
{
    public:
        enum type
        {
            CHAR,
            WCHAR_T,
            BOOL,
            SHORT,
            INT,
            LONG,
            SIGNED,
            UNSIGNED,
            FLOAT,
            DOUBLE,
            VOID,
            OTHER
        };

        explicit simple_type_specifier(type a_type);

        simple_type_specifier
        (
            bool leading_double_colon,
            std::shared_ptr<nested_name_specifier> a_nested_name_specifier,
            std::shared_ptr<identifier_or_template_id> an_identifier_or_template_id
        );

        simple_type_specifier
        (
            bool leading_double_colon,
            std::shared_ptr<nested_name_specifier> a_nested_name_specifier,
            std::shared_ptr<template_id> a_template_id
        );

        type
        get_type() const;

        bool
        has_leading_double_colon() const;

        const std::shared_ptr<nested_name_specifier>
        get_nested_name_specifier() const;

        const std::shared_ptr<identifier_or_template_id>
        get_identifier_or_template_id() const;

        const std::shared_ptr<template_id>
        get_template_id() const;

        SOCOA_CPP_DEFINE_VISITABLE()

    private:
        type m_type;
        bool m_leading_double_colon;
        std::shared_ptr<nested_name_specifier> m_nested_name_specifier;
        std::shared_ptr<identifier_or_template_id> m_identifier_or_template_id;
        std::shared_ptr<template_id> m_template_id;
};

}}} //namespace socoa::cpp::program_syntax_tree

#endif
