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

#ifndef SOCOA_CPP_PROGRAM_SYNTAX_TREE_NAMESPACE_DEFINITION_H
#define SOCOA_CPP_PROGRAM_SYNTAX_TREE_NAMESPACE_DEFINITION_H

#include <memory>
#include <string>
#include "declaration.h"
#include "sequence.h"

namespace socoa { namespace cpp { namespace program_syntax_tree
{

class identifier;

class namespace_definition: public declaration
{
    public:
        namespace_definition
        (
            std::shared_ptr<identifier> an_identifier,
            std::shared_ptr<sequence<declaration>> a_declaration_seq
        );

        const std::shared_ptr<identifier>
        get_identifier() const;

        const std::shared_ptr<sequence<declaration>>
        get_declaration_seq() const;

        SOCOA_CPP_DEFINE_VISITABLE()

    private:
        std::shared_ptr<identifier> identifier_;
        std::shared_ptr<sequence<declaration>> m_declaration_seq;
};

}}} //namespace socoa::cpp::program_syntax_tree

#endif
