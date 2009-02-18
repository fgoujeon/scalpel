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

#ifndef SOCOA_CPP_SYNTAX_TREE_DIRECT_DECLARATOR_FUNCTION_PART_H
#define SOCOA_CPP_SYNTAX_TREE_DIRECT_DECLARATOR_FUNCTION_PART_H

#include <boost/optional.hpp>
#include "parameter_declaration_clause.h"
#include "cv_qualifier_seq.h"

namespace socoa { namespace cpp { namespace syntax_tree
{

class direct_declarator_function_part
{
    public:
        direct_declarator_function_part
        (
            parameter_declaration_clause&& a_parameter_declaration_clause,
            boost::optional<cv_qualifier_seq> a_cv_qualifier_seq
        );

        inline
        const parameter_declaration_clause&
        get_parameter_declaration_clause() const;

        inline
        const boost::optional<const cv_qualifier_seq&>
        get_cv_qualifier_seq() const;

    private:
        parameter_declaration_clause parameter_declaration_clause_;
		boost::optional<cv_qualifier_seq> cv_qualifier_seq_;
};

inline
const parameter_declaration_clause&
direct_declarator_function_part::get_parameter_declaration_clause() const
{
    return parameter_declaration_clause_;
}

inline
const boost::optional<const cv_qualifier_seq&>
direct_declarator_function_part::get_cv_qualifier_seq() const
{
    return boost::optional<const cv_qualifier_seq&>(cv_qualifier_seq_);
}

}}} //namespace socoa::cpp::syntax_tree

#endif
