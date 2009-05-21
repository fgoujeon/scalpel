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

#include "composite_node.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

class labeled_statement_impl;
class labeled_statement_tail;

class case_statement;
class default_statement;
class classic_labeled_statement;

class labeled_statement: public composite_node
{
	public:
		typedef case_statement head_node_t;
		typedef labeled_statement_tail tail_alternative_node_t;

		labeled_statement(case_statement&& o);

		labeled_statement(default_statement&& o);

		labeled_statement(classic_labeled_statement&& o);

		labeled_statement(const labeled_statement& o);

		labeled_statement(labeled_statement&& o);

		~labeled_statement();

		const labeled_statement&
		operator=(const labeled_statement& o);

	private:
		labeled_statement_impl* impl_;
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
