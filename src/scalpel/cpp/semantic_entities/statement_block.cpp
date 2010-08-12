/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2010  Florian Goujeon

This file is part of Scalpel.

Scalpel is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Scalpel is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Scalpel.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "statement_block.hpp"

namespace scalpel { namespace cpp { namespace semantic_entities
{

statement_block::statement_block()
{
}

statement_block::statement_block(statement_block&& o):
	statement_blocks_(std::move(o.statement_blocks_)),
	variables_(std::move(o.variables_))
{
}

const statement_block&
statement_block::operator=(statement_block&& o)
{
	statement_blocks_ = std::move(o.statement_blocks_);
	variables_ = std::move(o.variables_);

	return *this;
}

bool
statement_block::operator==(const statement_block& o) const
{
	return true;
}

void
statement_block::add(std::shared_ptr<statement_block> o)
{
	statement_blocks_.push_back(o);
}

void
statement_block::add(std::shared_ptr<variable> o)
{
	variables_.push_back(o);
}

}}} //namespace scalpel::cpp::semantic_entities

