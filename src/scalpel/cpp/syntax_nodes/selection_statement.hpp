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

#ifndef SCALPEL_CPP_SYNTAX_NODES_SELECTION_STATEMENT_HPP
#define SCALPEL_CPP_SYNTAX_NODES_SELECTION_STATEMENT_HPP

#include "composite_node.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

class selection_statement_impl;
class selection_statement_tail;
class switch_statement;
class if_statement;

class selection_statement: public composite_node
{
	public:
		typedef if_statement head_node_t;
		typedef selection_statement_tail tail_alternative_node_t;

		selection_statement(if_statement&& o);

		selection_statement(switch_statement&& o);

		selection_statement(const selection_statement& o);

		selection_statement(selection_statement&& o);

		~selection_statement();

		const selection_statement&
		operator=(const selection_statement& o);

	private:
		selection_statement_impl* impl_;
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
