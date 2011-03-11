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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_STATEMENT_BLOCK_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_STATEMENT_BLOCK_HPP

#include "variable.hpp"
#include "namespace_alias.hpp"
#include <scalpel/utility/unique_ptr_vector.hpp>
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
		typedef std::vector<open_declarative_region_ptr_variant> open_declarative_region_ptr_variants_t;

		typedef std::vector<namespace_*> namespace_ptrs_t;
		typedef utility::unique_ptr_vector<statement_block> statement_blocks_t;
		typedef utility::unique_ptr_vector<variable> variables_t;
		typedef utility::unique_ptr_vector<namespace_alias> namespace_aliases_t;

        statement_block();

		statement_block(const statement_block&) = delete;

		const statement_block&
		operator=(const statement_block&) = delete;

		const open_declarative_region_ptr_variants_t&
		open_declarative_regions();

		const statement_blocks_t&
		statement_blocks() const;

		const variables_t&
		variables() const;

		const namespace_aliases_t&
		namespace_aliases() const;

		const namespace_ptrs_t&
		using_directive_namespaces() const;

		void
		add_member(std::unique_ptr<statement_block>&& member);

		void
		add_member(std::unique_ptr<variable>&& member);

		void
		add_member(std::unique_ptr<namespace_alias>&& member);

        void
        add_using_directive_namespace(namespace_& n);

    private:
		//polymorphic containers
		open_declarative_region_ptr_variants_t open_declarative_regions_;

		//members
		statement_blocks_t statement_blocks_;
		variables_t variables_;
		namespace_aliases_t namespace_aliases_;

        namespace_ptrs_t using_directive_namespaces_;

		typedef
			detail::declarative_region_member_impl
			<
				constructor,
				destructor,
				operator_member_function,
				conversion_function,
				simple_member_function,
				operator_function,
				simple_function
			>
			declarative_region_member_impl_type
		;
		DECLARATIVE_REGION_MEMBER_IMPL(declarative_region_member_impl_type)
};

}}} //namespace scalpel::cpp::semantic_entities

#endif

