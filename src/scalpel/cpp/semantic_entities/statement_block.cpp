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
#include <scalpel/utility/are_pointed_objects_equal.hpp>

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

const statement_block::statement_blocks_t&
statement_block::statement_blocks() const
{
	return statement_blocks_;
}

const statement_block::variables_t&
statement_block::variables() const
{
	return variables_;
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

bool
operator==(const statement_block& lhs, const statement_block& rhs)
{
	return
		are_pointed_objects_equal(lhs.statement_blocks(), rhs.statement_blocks()) &&
		are_pointed_objects_equal(lhs.variables(), rhs.variables())
	;
}

bool
operator!=(const statement_block& lhs, const statement_block& rhs)
{
	return !operator==(lhs, rhs);
}

}}} //namespace scalpel::cpp::semantic_entities

