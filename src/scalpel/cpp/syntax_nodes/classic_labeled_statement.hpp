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

#ifndef SCALPEL_CPP_SYNTAX_NODES_CLASSIC_LABELED_STATEMENT_HPP
#define SCALPEL_CPP_SYNTAX_NODES_CLASSIC_LABELED_STATEMENT_HPP

#include "common.hpp"
#include "identifier.hpp"
#include "statement.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
classic_labeled_statement
	= identifier, ':', statement
;
*/
typedef
	sequence_node
	<
		identifier,
		optional_node<space>,
		simple_text_node<str::colon>,
		optional_node<space>,
		statement
	>
	classic_labeled_statement_t
;

struct classic_labeled_statement: public classic_labeled_statement_t
{
	typedef classic_labeled_statement_t type;

	classic_labeled_statement
	(
		identifier&& o1,
		optional_node<space>&& o2,
		simple_text_node<str::colon>&& o3,
		optional_node<space>&& o4,
		statement&& o5
	):
		classic_labeled_statement_t(o1, o2, o3, o4, o5)
	{
	}

	classic_labeled_statement
	(
		const classic_labeled_statement& o
	):
		classic_labeled_statement_t(o)
	{
	}

	classic_labeled_statement
	(
		classic_labeled_statement&& o
	):
		classic_labeled_statement_t(o)
	{
	}

	classic_labeled_statement
	(
		const classic_labeled_statement_t& o
	):
		classic_labeled_statement_t(o)
	{
	}

	using classic_labeled_statement_t::operator=;
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
