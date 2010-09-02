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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_STATEMENT_BLOCK_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_STATEMENT_BLOCK_HPP

#include "variable.hpp"
#include <scalpel/utility/vector.hpp>
#include <string>
#include <memory>

namespace scalpel { namespace cpp { namespace semantic_entities
{

class namespace_;
class class_;

/**
Represents a C++ statement block.
*/
class statement_block
{
    public:
		typedef utility::vector<std::weak_ptr<namespace_>> weak_namespaces_t;
		typedef utility::vector<std::shared_ptr<statement_block>> statement_blocks_t;
		typedef utility::vector<std::shared_ptr<variable>> variables_t;

        statement_block();

		statement_block(const statement_block& o) = delete;

		statement_block(statement_block&& o);

		const statement_block&
		operator=(const statement_block& o) = delete;

		const statement_block&
		operator=(statement_block&& o);

		bool
		has_enclosing_declarative_region() const
		{
			return declarative_region_member_impl_.has_enclosing_declarative_region();
		}

		declarative_region_shared_ptr_variant
		enclosing_declarative_region() const
		{
			return declarative_region_member_impl_.enclosing_declarative_region();
		}

		void
		enclosing_declarative_region(const declarative_region_shared_ptr_variant& decl_region)
		{
			declarative_region_member_impl_.enclosing_declarative_region(decl_region);
		}

		const statement_blocks_t&
		statement_blocks() const;

		const variables_t&
		variables() const;

		const weak_namespaces_t&
		using_directive_namespaces() const;

		void
		add(std::shared_ptr<statement_block> o);

		void
		add(std::shared_ptr<variable> o);

        void
        add_using_directive_namespace(std::shared_ptr<namespace_> n);

    private:
		declarative_region_member_impl declarative_region_member_impl_;

		statement_blocks_t statement_blocks_;
		variables_t variables_;

        weak_namespaces_t using_directive_namespaces_;
};

bool
operator==(const statement_block& lhs, const statement_block& rhs);

bool
operator!=(const statement_block& lhs, const statement_block& rhs);

}}} //namespace scalpel::cpp::semantic_entities

#endif
