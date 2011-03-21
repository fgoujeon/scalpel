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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_NAMESPACE_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_NAMESPACE_HPP

#include "declarative_region_variants.hpp"
#include "namespace_alias.hpp"
#include "class_.hpp"
#include "enum_.hpp"
#include "functions.hpp"
#include "typedef_.hpp"
#include "variable.hpp"
#include "macros/detail/declarative_region_member_impl.hpp"
#include <scalpel/utility/unique_ptr_vector.hpp>
#include <boost/optional.hpp>
#include <string>
#include <list>
#include <vector>
#include <memory>

namespace scalpel { namespace cpp { namespace semantic_entities
{

/**
Represents a C++ namespace.
*/
class namespace_
{
	public:
		typedef std::vector<open_declarative_region_ptr_variant> open_declarative_region_ptr_variants_t;

		typedef std::vector<namespace_*> namespace_ptrs_t;
		typedef utility::unique_ptr_vector<namespace_> namespaces_t;
		typedef utility::unique_ptr_vector<namespace_alias> namespace_aliases_t;
		typedef utility::unique_ptr_vector<class_> classes_t;
		typedef utility::unique_ptr_vector<enum_> enums_t;
		typedef utility::unique_ptr_vector<typedef_> typedefs_t;
		typedef utility::unique_ptr_vector<simple_function> simple_functions_t;
		typedef utility::unique_ptr_vector<operator_function> operator_functions_t;
		typedef utility::unique_ptr_vector<variable> variables_t;

	public:
		/**
		Creates an anonymous namespace. Equivalent to namespace_("").
		*/
		namespace_();

		/**
		Creates a named namespace.
		@param name the namespace's name
		*/
		explicit
		namespace_(const std::string& name);

		namespace_(const namespace_&) = delete;

		const namespace_&
		operator=(const namespace_&) = delete;

		/**
		@return the name of the namespace
		Anonymous namespaces return an empty string.
		*/
		const std::string&
		name() const;

		const open_declarative_region_ptr_variants_t&
		open_declarative_regions();

		namespaces_t::range
		namespaces();

		const namespaces_t&
		namespaces() const;

		classes_t::range
		classes();

		const classes_t&
		classes() const;

		enums_t::range
		enums();

		const enums_t&
		enums() const;

		typedefs_t::range
		typedefs();

		const typedefs_t&
		typedefs() const;

		simple_functions_t::range
		simple_functions();

		const simple_functions_t&
		simple_functions() const;

		operator_functions_t::range
		operator_functions();

		const operator_functions_t&
		operator_functions() const;

		variables_t::range
		variables();

		const variables_t&
		variables() const;

		namespace_aliases_t::range
		namespace_aliases();

		const namespace_aliases_t&
		namespace_aliases() const;

		const namespace_ptrs_t&
		using_directive_namespaces() const;

		void
		add_member(std::unique_ptr<namespace_alias>&& member);

		void
		add_member(std::unique_ptr<namespace_>&& member);

		void
		add_member(std::unique_ptr<class_>&& member);

		void
		add_member(std::unique_ptr<enum_>&& member);

		void
		add_member(std::unique_ptr<typedef_>&& member);

		void
		add_member(std::unique_ptr<simple_function>&& member);

		void
		add_member(std::unique_ptr<operator_function>&& member);

		void
		add_member(std::unique_ptr<variable>&& member);

		void
		add_using_directive_namespace(namespace_& n);

	private:
		std::string name_;

		//polymorphic containers
		open_declarative_region_ptr_variants_t open_declarative_regions_;

		//members
		namespace_aliases_t namespace_aliases_;
		namespaces_t namespaces_;
		classes_t classes_;
		enums_t enums_;
		typedefs_t typedefs_;
		simple_functions_t simple_functions_;
		operator_functions_t operator_functions_;
		variables_t variables_;

		namespace_ptrs_t using_directive_namespaces_;

		DECLARATIVE_REGION_MEMBER_IMPL(impl::detail::declarative_region_member_impl<namespace_>)
};

}}} //namespace scalpel::cpp::semantic_entities

#include "macros/detail/declarative_region_member_impl_undef.hpp"

#endif

