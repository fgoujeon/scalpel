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

#ifndef SCALPEL_CPP_SYNTAX_NODES_LABELED_STATEMENT_HPP
#define SCALPEL_CPP_SYNTAX_NODES_LABELED_STATEMENT_HPP

#include <boost/optional.hpp>
#include "composite_node.hpp"
#include "default_statement.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

class case_statement;
class classic_labeled_statement;

typedef
	alternative_node
	<
		case_statement,
		default_statement,
		classic_labeled_statement
	>
	labeled_statement_t
;

typedef
	alternative_node
	<
		default_statement,
		classic_labeled_statement
	>
	labeled_statement_tail_t
;

class labeled_statement: public composite_node
{
	public:
		typedef labeled_statement_t type;
		typedef case_statement head_node_t;
		typedef labeled_statement_tail_t tail_alternative_node_t;

		labeled_statement(case_statement&& o);

		labeled_statement(default_statement&& o);

		labeled_statement(classic_labeled_statement&& o);

		labeled_statement(const labeled_statement& o);

		labeled_statement(labeled_statement&& o);

		~labeled_statement();

		const labeled_statement&
		operator=(const labeled_statement& o);

		void
		get(boost::optional<const case_statement&>& node) const;

		void
		get(boost::optional<const default_statement&>& node) const;

		void
		get(boost::optional<const classic_labeled_statement&>& node) const;

	private:
		type* impl_;
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
