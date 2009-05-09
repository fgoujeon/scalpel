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

#ifndef SCALPEL_CPP_SYNTAX_NODES_HANDLER_HPP
#define SCALPEL_CPP_SYNTAX_NODES_HANDLER_HPP

#include <boost/optional.hpp>
#include "composite_node.hpp"
#include "compound_statement.hpp"
#include "space.hpp"
#include "exception_declaration.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
handler
	= str_p("catch") >> !s >> '(' >> !s >> exception_declaration >> !s >> ')' >> !s >> compound_statement
;
*/
class handler: public composite_node
{
	public:
		handler
		(
			boost::optional<space>&& post_catch_keyword_space_node,
			boost::optional<space>&& post_opening_bracket_space_node,
			exception_declaration&& exception_declaration_node,
			boost::optional<space>&& post_exception_declaration_space_node,
			boost::optional<space>&& post_closing_bracket_space_node,
			compound_statement&& compound_statement_node
		);

		handler(const handler& o);

		handler(handler&& o);

		const handler&
		operator=(const handler& o);

		inline
		const compound_statement&
		compound_statement_node() const;

	private:
		void
		update_node_list();

		boost::optional<space> post_catch_keyword_space_;
		boost::optional<space> post_opening_bracket_space_;
		exception_declaration exception_declaration_;
		boost::optional<space> post_exception_declaration_space_;
		boost::optional<space> post_closing_bracket_space_;
		compound_statement compound_statement_;
};

inline
const compound_statement&
handler::compound_statement_node() const
{
	return compound_statement_;
}

}}} //namespace scalpel::cpp::syntax_nodes

#endif
