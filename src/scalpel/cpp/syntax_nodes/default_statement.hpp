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

#ifndef SCALPEL_CPP_SYNTAX_NODES_DEFAULT_STATEMENT_HPP
#define SCALPEL_CPP_SYNTAX_NODES_DEFAULT_STATEMENT_HPP

#include <memory>
#include "optional_node.hpp"
#include "composite_node.hpp"
#include "space.hpp"
#include "statement.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
\verbatim
default_statement
	= str_p("default") >> !s >> ':' >> !s >> statement
;
\endverbatim
*/
class default_statement: public composite_node
{
	public:
		default_statement
		(
			optional_node<space>&& post_default_keyword_space_node,
			optional_node<space>&& post_colon_space_node,
			statement&& statement_node
		);

		default_statement(const default_statement& o);

		default_statement(default_statement&& o);

		const default_statement&
		operator=(const default_statement& o);

	private:
		void
		update_node_list();

		optional_node<space> post_default_keyword_space_;
		optional_node<space> post_colon_space_;
		std::unique_ptr<statement> statement_;
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
