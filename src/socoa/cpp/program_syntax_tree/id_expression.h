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

#ifndef SOCOA_CPP_PROGRAM_SYNTAX_TREE_ID_EXPRESSION_H
#define SOCOA_CPP_PROGRAM_SYNTAX_TREE_ID_EXPRESSION_H

#include "declarator_id.h"
#include "template_argument.h"

namespace socoa { namespace cpp { namespace program_syntax_tree
{

class id_expression: public declarator_id, public template_argument
{
    public:
        virtual ~id_expression(){};
};

}}} //namespace socoa::cpp::program_syntax_tree

#endif
