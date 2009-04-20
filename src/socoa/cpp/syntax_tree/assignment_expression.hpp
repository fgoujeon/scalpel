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

#ifndef SOCOA_CPP_SYNTAX_TREE_ASSIGNMENT_EXPRESSION_HPP
#define SOCOA_CPP_SYNTAX_TREE_ASSIGNMENT_EXPRESSION_HPP

#include "composite_node.hpp"
#include "alternative_node.hpp"
#include "sequence_node.hpp"
#include "assignment_operator.hpp"
#include "conditional_expression.hpp"
#include "expressions.hpp"
//#include "throw_expression.hpp"
#include "space.hpp"

namespace socoa { namespace cpp { namespace syntax_tree
{

/**
\verbatim
assignment_expression
	= [assignment_expression_first_part_seq], (conditional_expression | throw_expression)
;
assignment_expression::first_part_seq
	= {assignment_expression::first_part}
;
assignment_expression::first_part
	= logical_or_expression, assignment_operator
;
\endverbatim
*/
class assignment_expression: public composite_node
{
    public:
		class first_part;

		typedef sequence_node<first_part> first_part_seq;

		typedef
			alternative_node<conditional_expression/*, throw_expression*/>
			conditional_or_throw_expression
		;

        assignment_expression
        (
			boost::optional<first_part_seq>&& first_part_seq_node,
			boost::optional<space>&& space_node,
			conditional_or_throw_expression&& conditional_or_throw_expression_node
        );

		assignment_expression(const assignment_expression& o);

		assignment_expression(assignment_expression&& o);

		const assignment_expression&
		operator=(const assignment_expression& o);

    private:
		void
		update_node_list();

		boost::optional<first_part_seq> first_part_seq_;
		boost::optional<space> space_;
		conditional_or_throw_expression conditional_or_throw_expression_;
};

class assignment_expression::first_part: public composite_node
{
	public:
        first_part
        (
			logical_or_expression&& logical_or_expression_node,
			boost::optional<space>&& space_node,
            assignment_operator&& assignment_operator_node
        );

		first_part(const first_part& o);

		first_part(first_part&& o);

		const first_part&
		operator=(const first_part& o);

        inline
        const assignment_operator&
        assignment_operator_node() const;

	private:
		void
		update_node_list();

        logical_or_expression logical_or_expression_;
		boost::optional<space> space_;
        assignment_operator assignment_operator_;
};

inline
const assignment_operator&
assignment_expression::first_part::assignment_operator_node() const
{
    return assignment_operator_;
}

}}} //namespace socoa::cpp::syntax_tree

#endif
