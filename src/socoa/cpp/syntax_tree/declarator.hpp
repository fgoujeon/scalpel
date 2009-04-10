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

#ifndef SOCOA_CPP_SYNTAX_TREE_DECLARATOR_HPP
#define SOCOA_CPP_SYNTAX_TREE_DECLARATOR_HPP

#include <memory>
#include <vector>
#include "composite_node.hpp"
#include "ptr_operator.hpp"

namespace socoa { namespace cpp { namespace syntax_tree
{

class direct_declarator;

/**
\verbatim
declarator
	= {ptr_operator}, direct_declarator
;
\endverbatim
*/
class declarator: public composite_node
{
	public:
        declarator
        (
            std::vector<ptr_operator>&& ptr_operators,
            direct_declarator&& a_direct_declarator
        );

		declarator(const declarator&) = delete;

		declarator(declarator&& o);

        inline
        const std::vector<ptr_operator>&
        get_ptr_operators() const;

        inline
        const direct_declarator&
        get_direct_declarator() const;

    private:
        std::vector<ptr_operator> ptr_operators_;
		std::shared_ptr<direct_declarator> direct_declarator_;
};

inline
const std::vector<ptr_operator>&
declarator::get_ptr_operators() const
{
    return ptr_operators_;
}

inline
const direct_declarator&
declarator::get_direct_declarator() const
{
    return *direct_declarator_;
}

}}} //namespace socoa::cpp::syntax_tree

#endif
