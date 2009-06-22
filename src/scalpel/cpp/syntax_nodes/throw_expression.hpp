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

#ifndef SCALPEL_CPP_SYNTAX_NODES_THROW_EXPRESSION_HPP
#define SCALPEL_CPP_SYNTAX_NODES_THROW_EXPRESSION_HPP

#include <memory>
#include "common.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

class assignment_expression;

typedef
	sequence_node
	<
		predefined_text_node<str::throw_>,
		optional_node<space>,
		optional_node<assignment_expression>
	>
	throw_expression_t
;

/**
throw_expression
	= "throw", [assignment_expression]
;
*/
class throw_expression: public composite_node
{
	public:
		typedef throw_expression_t type;
		typedef type::head_node_t head_node_t;
		typedef type::tail_sequence_node_t tail_sequence_node_t;

		throw_expression
		(
			predefined_text_node<str::throw_>&& o0,
			optional_node<space>&& o1,
			optional_node<assignment_expression>&& o2
		);

		throw_expression
		(
			head_node_t&& head,
			tail_sequence_node_t&& tail
		);

		throw_expression(const throw_expression& o);

		throw_expression(throw_expression&& o);

		~throw_expression();

		const throw_expression&
		operator=(const throw_expression& o);

	private:
		std::unique_ptr<type> impl_;
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
