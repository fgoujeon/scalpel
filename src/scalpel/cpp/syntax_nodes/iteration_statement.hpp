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

#ifndef SCALPEL_CPP_SYNTAX_NODES_ITERATION_STATEMENT_HPP
#define SCALPEL_CPP_SYNTAX_NODES_ITERATION_STATEMENT_HPP

#include "alternative_node.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

class while_statement;
class do_while_statement;
class for_statement;

class iteration_statement_impl;

class iteration_statement: public composite_node
{
	public:
		explicit
		iteration_statement(while_statement&& o);

		explicit
		iteration_statement(do_while_statement&& o);

		explicit
		iteration_statement(for_statement&& o);

		iteration_statement(const iteration_statement& o);

		iteration_statement(iteration_statement&& o);

		~iteration_statement();

		const iteration_statement&
		operator=(const iteration_statement& o);

	private:
		iteration_statement_impl* impl_;
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
