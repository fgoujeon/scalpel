/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2012  Florian Goujeon

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
#include "macros/detail/declarative_region_member_impl.hpp"
#include <scalpel/utility/unique_ptr_vector_range.hpp>
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
		typedef std::vector<namespace_*> namespace_ptrs_t;
		typedef std::vector<std::unique_ptr<statement_block>> statement_blocks_t;
		typedef std::vector<std::unique_ptr<variable>> variables_t;
		typedef std::vector<std::unique_ptr<namespace_alias>> namespace_aliases_t;

        statement_block();

		statement_block(const statement_block&) = delete;

		const statement_block&
		operator=(const statement_block&) = delete;

		utility::unique_ptr_vector_const_range<statement_block>::type
		statement_blocks() const;

		utility::unique_ptr_vector_const_range<variable>::type
		variables() const;

		utility::unique_ptr_vector_range<namespace_alias>::type
		namespace_aliases();

		utility::unique_ptr_vector_const_range<namespace_alias>::type
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
		//members
		statement_blocks_t statement_blocks_;
		variables_t variables_;
		namespace_aliases_t namespace_aliases_;

        namespace_ptrs_t using_directive_namespaces_;

		typedef
			impl::detail::declarative_region_member_impl
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

#include "macros/detail/declarative_region_member_impl_undef.hpp"

#endif

