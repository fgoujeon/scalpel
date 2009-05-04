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

#ifndef SOCOA_CPP_SYNTAX_NODES_DEFAULT_STATEMENT_HPP
#define SOCOA_CPP_SYNTAX_NODES_DEFAULT_STATEMENT_HPP

#include <memory>
#include <boost/optional.hpp>
#include "composite_node.hpp"
#include "space.hpp"
#include "statement_fwd.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
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
			boost::optional<space>&& post_default_keyword_space_node,
			boost::optional<space>&& post_colon_space_node,
			statement&& statement_node
		);

		default_statement(const default_statement& o);

		default_statement(default_statement&& o);

		const default_statement&
		operator=(const default_statement& o);

	private:
		void
		update_node_list();

		boost::optional<space> post_default_keyword_space_;
		boost::optional<space> post_colon_space_;
		std::unique_ptr<statement> statement_;
};

}}} //namespace socoa::cpp::syntax_nodes

#endif
