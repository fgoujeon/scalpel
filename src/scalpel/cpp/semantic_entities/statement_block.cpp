/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2011  Florian Goujeon

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

utility::unique_ptr_vector_const_range<statement_block>::type
statement_block::statement_blocks() const
{
	return utility::make_unique_ptr_vector_const_range(statement_blocks_);
}

utility::unique_ptr_vector_const_range<variable>::type
statement_block::variables() const
{
	return utility::make_unique_ptr_vector_const_range(variables_);
}

utility::unique_ptr_vector_range<namespace_alias>::type
statement_block::namespace_aliases()
{
	return utility::make_unique_ptr_vector_range(namespace_aliases_);
}

utility::unique_ptr_vector_const_range<namespace_alias>::type
statement_block::namespace_aliases() const
{
	return utility::make_unique_ptr_vector_const_range(namespace_aliases_);
}

const statement_block::namespace_ptrs_t&
statement_block::using_directive_namespaces() const
{
	return using_directive_namespaces_;
}

void
statement_block::add_member(std::unique_ptr<statement_block>&& member)
{
	statement_blocks_.push_back(std::move(member));
}

void
statement_block::add_member(std::unique_ptr<variable>&& member)
{
	variables_.push_back(std::move(member));
}

void
statement_block::add_member(std::unique_ptr<namespace_alias>&& member)
{
    namespace_aliases_.push_back(std::move(member));
}

void
statement_block::add_using_directive_namespace(namespace_& n)
{
	using_directive_namespaces_.push_back(&n);
}

}}} //namespace scalpel::cpp::semantic_entities

