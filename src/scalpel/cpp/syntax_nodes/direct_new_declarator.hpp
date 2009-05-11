/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008, 2009  Florian Goujeon

This file is part of Scalpel.

Scalpel is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Scalpel is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Scalpel.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SCALPEL_CPP_SYNTAX_NODES_DIRECT_NEW_DECLARATOR_HPP
#define SCALPEL_CPP_SYNTAX_NODES_DIRECT_NEW_DECLARATOR_HPP

#include <boost/optional.hpp>
#include "composite_node.hpp"
#include "space.hpp"
#include "expression.hpp"
#include "conditional_expression.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
direct_new_declarator
	= '[' >> !s >> expression >> !s >> ']' >> !(!s >> '[' >> !s >> conditional_expression >> !s >> ']')
;
*/
class direct_new_declarator: public composite_node
{
	public:
		direct_new_declarator
		(
			boost::optional<space>&& post_first_opening_bracket_space_node,
			expression&& expression_node,
			boost::optional<space>&& post_expression_space_node,
			boost::optional<space>&& post_first_closing_bracket_space_node,
			boost::optional<space>&& post_second_opening_bracket_space_node,
			boost::optional<conditional_expression>&& conditional_expression_node,
			boost::optional<space>&& post_conditional_expression_space_node
		);

		direct_new_declarator(const direct_new_declarator& o);

		direct_new_declarator(direct_new_declarator&& o);

		const direct_new_declarator&
		operator=(const direct_new_declarator& o);

	private:
		void
		update_node_list();

		boost::optional<space> post_first_opening_bracket_space_;
		expression expression_;
		boost::optional<space> post_expression_space_;
		boost::optional<space> post_first_closing_bracket_space_;
		boost::optional<space> post_second_opening_bracket_space_;
		boost::optional<conditional_expression> conditional_expression_;
		boost::optional<space> post_conditional_expression_space_;
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
