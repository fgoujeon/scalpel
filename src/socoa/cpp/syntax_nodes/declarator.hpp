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

#ifndef SOCOA_CPP_SYNTAX_NODES_DECLARATOR_HPP
#define SOCOA_CPP_SYNTAX_NODES_DECLARATOR_HPP

#include <memory>
#include <vector>
#include "composite_node.hpp"
#include "ptr_operator_seq.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
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
            boost::optional<ptr_operator_seq>&& ptr_operator_seq,
			boost::optional<space>&& post_ptr_operator_seq_space_node,
            direct_declarator&& a_direct_declarator
        );

		declarator(const declarator& o);

		declarator(declarator&& o);

		const declarator&
		operator=(const declarator& o);

        inline
        const boost::optional<const ptr_operator_seq&>
        get_ptr_operator_seq() const;

        inline
        const direct_declarator&
        get_direct_declarator() const;

    private:
		void
		update_node_list();

		boost::optional<ptr_operator_seq> ptr_operator_seq_;
		boost::optional<space> post_ptr_operator_seq_space_node_;
		std::shared_ptr<direct_declarator> direct_declarator_;
};

inline
const boost::optional<const ptr_operator_seq&>
declarator::get_ptr_operator_seq() const
{
	return boost::optional<const ptr_operator_seq&>(ptr_operator_seq_);
}

inline
const direct_declarator&
declarator::get_direct_declarator() const
{
    return *direct_declarator_;
}

}}} //namespace socoa::cpp::syntax_nodes

#endif
