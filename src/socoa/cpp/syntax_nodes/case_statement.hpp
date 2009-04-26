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

#ifndef SOCOA_CPP_SYNTAX_NODES_CASE_STATEMENT_HPP
#define SOCOA_CPP_SYNTAX_NODES_CASE_STATEMENT_HPP

#include <boost/optional.hpp>
#include "composite_node.hpp"
#include "space.hpp"
#include "conditional_expression.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
{

class statement;

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
			boost::optional<space>&& post_case_keyword_space_node,
			conditional_expression&& conditional_expression_node,
			boost::optional<space>&& post_conditional_expression_space_node,
			boost::optional<space>&& post_colon_space_node,
			statement&& statement_node
		);

		case_statement(const case_statement& o);

		case_statement(case_statement&& o);

		const case_statement&
		operator=(const case_statement& o);

	private:
		void
		update_node_list();

		boost::optional<space> post_case_keyword_space_;
		conditional_expression conditional_expression_;
		boost::optional<space> post_conditional_expression_space_;
		boost::optional<space> post_colon_space_;
		std::unique_ptr<statement> statement_;
};

}}} //namespace socoa::cpp::syntax_nodes

#endif
