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

#ifndef SCALPEL_CPP_SYNTAX_NODES_CASE_STATEMENT_HPP
#define SCALPEL_CPP_SYNTAX_NODES_CASE_STATEMENT_HPP

#include "optional_node.hpp"
#include "composite_node.hpp"
#include "space.hpp"
#include "conditional_expression.hpp"
#include "statement_fwd.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
\verbatim
case_statement
	= str_p("case") >> !s >> conditional_expression >> !s >> ':' >> !s >> statement
;
\endverbatim
*/
class case_statement: public composite_node
{
	public:
		case_statement
		(
			optional_node<space>&& post_case_keyword_space_node,
			conditional_expression&& conditional_expression_node,
			optional_node<space>&& post_conditional_expression_space_node,
			optional_node<space>&& post_colon_space_node,
			statement&& statement_node
		);

		case_statement(const case_statement& o);

		case_statement(case_statement&& o);

		const case_statement&
		operator=(const case_statement& o);

	private:
		void
		update_node_list();

		optional_node<space> post_case_keyword_space_;
		conditional_expression conditional_expression_;
		optional_node<space> post_conditional_expression_space_;
		optional_node<space> post_colon_space_;
		std::unique_ptr<statement> statement_;
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
