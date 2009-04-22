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

#ifndef SOCOA_CPP_SYNTAX_NODES_GOTO_STATEMENT_HPP
#define SOCOA_CPP_SYNTAX_NODES_GOTO_STATEMENT_HPP

#include <boost/optional.hpp>
#include "composite_node.hpp"
#include "space.hpp"
#include "identifier.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
{

/**
\verbatim
goto_statement
	= "goto", identifier, ";"
;
\endverbatim
*/
class goto_statement: public composite_node
{
	public:
		goto_statement
		(
			boost::optional<space>&& post_return_space_node,
			identifier&& identifier_node,
			boost::optional<space>&& post_identifier_space_node
		);

		goto_statement(const goto_statement& o);

		goto_statement(goto_statement&& o);

		const goto_statement&
		operator=(const goto_statement& o);

	private:
		void
		update_node_list();

		boost::optional<space> post_return_space_;
		identifier identifier_;
		boost::optional<space> post_identifier_space_;
};

}}} //namespace socoa::cpp::syntax_nodes

#endif
