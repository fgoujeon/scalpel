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

const statement_block::open_declarative_region_shared_ptr_variants_t&
statement_block::open_declarative_regions()
{
	return open_declarative_regions_;
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

const statement_block::namespace_aliases_t&
statement_block::namespace_aliases() const
{
	return namespace_aliases_;
}

const statement_block::weak_namespaces_t&
statement_block::using_directive_namespaces() const
{
	return using_directive_namespaces_;
}

void
statement_block::add_member(std::shared_ptr<statement_block> member)
{
	statement_blocks_.push_back(member);
}

void
statement_block::add_member(std::shared_ptr<variable> member)
{
	variables_.push_back(member);
}

void
statement_block::add_member(std::shared_ptr<namespace_alias> member)
{
    namespace_aliases_.push_back(member);
	open_declarative_regions_.push_back(member);
}

void
statement_block::add_using_directive_namespace(std::shared_ptr<namespace_> n)
{
	using_directive_namespaces_.push_back(n);
}

bool
operator==(const statement_block& lhs, const statement_block& rhs)
{
	return
		utility::are_pointed_objects_equal(lhs.statement_blocks(), rhs.statement_blocks()) &&
		utility::are_pointed_objects_equal(lhs.variables(), rhs.variables())
	;
}

bool
operator!=(const statement_block& lhs, const statement_block& rhs)
{
	return !operator==(lhs, rhs);
}

}}} //namespace scalpel::cpp::semantic_entities

