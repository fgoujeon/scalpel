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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_NAMESPACE_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_NAMESPACE_HPP

#include "declarative_region_variants.hpp"
#include "namespace_or_namespace_alias_variants.hpp"
#include "namespace_alias.hpp"
#include "class_.hpp"
#include "operator_function.hpp"
#include "simple_function.hpp"
#include "typedef_.hpp"
#include "variable.hpp"
#include <boost/noncopyable.hpp>
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
class namespace_:
	public std::enable_shared_from_this<namespace_>,
	public boost::noncopyable
{
	public:
		typedef std::vector<open_declarative_region_shared_ptr_variant> open_declarative_region_shared_ptr_variants_t;
		typedef std::vector<namespace_or_namespace_alias_shared_ptr_variant> namespace_or_namespace_alias_shared_ptr_variants_t;
		typedef std::vector<named_compound_type_shared_ptr_variant> named_compound_type_shared_ptr_variants_t;

		typedef std::vector<std::weak_ptr<namespace_>> weak_namespaces_t;
		typedef utility::shared_ptr_vector<namespace_alias> namespace_aliases_t;
		typedef utility::shared_ptr_vector<namespace_> namespaces_t;
		typedef utility::shared_ptr_vector<class_> classes_t;
		typedef utility::shared_ptr_vector<typedef_> typedefs_t;
		typedef utility::shared_ptr_vector<simple_function> simple_functions_t;
		typedef utility::shared_ptr_vector<operator_function> operator_functions_t;
		typedef utility::shared_ptr_vector<variable> variables_t;

	private:
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

	public:
		/**
		Creates an anonymous namespace. Equivalent to make_shared("").
		*/
		static
		std::shared_ptr<namespace_>
		make_shared();

		/**
		Creates a named namespace.
		@param name the namespace's name
		*/
		static
		std::shared_ptr<namespace_>
		make_shared(const std::string& name);

		/**
		@return the name of the namespace
		Anonymous namespaces return an empty string.
		*/
		const std::string&
		name() const;

		bool
		has_enclosing_declarative_region() const;

		std::shared_ptr<namespace_>
		enclosing_declarative_region();

		std::shared_ptr<const namespace_>
		enclosing_declarative_region() const;

		void
		enclosing_declarative_region(std::shared_ptr<namespace_> enclosing_declarative_region);

		const open_declarative_region_shared_ptr_variants_t&
		open_declarative_regions();

		const namespace_or_namespace_alias_shared_ptr_variants_t&
		namespaces_and_namespace_aliases();

		const named_compound_type_shared_ptr_variants_t&
		named_compound_types();

		namespaces_t::range
		namespaces();

		const namespaces_t&
		namespaces() const;

		classes_t::range
		classes();

		const classes_t&
		classes() const;

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

		const weak_namespaces_t&
		using_directive_namespaces() const;

		void
		add_member(std::shared_ptr<namespace_alias> member);

		void
		add_member(std::shared_ptr<namespace_or_namespace_alias_shared_ptr_variant> member);

		void
		add_member(std::shared_ptr<namespace_> member);

		void
		add_member(std::shared_ptr<class_> member);

		void
		add_member(std::shared_ptr<typedef_> member);

		void
		add_member(std::shared_ptr<simple_function> member);

		void
		add_member(std::shared_ptr<operator_function> member);

		void
		add_member(std::shared_ptr<variable> member);

		void
		add_using_directive_namespace(std::shared_ptr<namespace_> n);

	private:
		std::string name_;
		std::weak_ptr<namespace_> enclosing_declarative_region_;

		//polymorphic containers
		open_declarative_region_shared_ptr_variants_t open_declarative_regions_;
		namespace_or_namespace_alias_shared_ptr_variants_t namespaces_and_namespace_aliases_;
		named_compound_type_shared_ptr_variants_t named_compound_types_;

		//members
		namespace_aliases_t namespace_aliases_;
		namespaces_t namespaces_;
		classes_t classes_;
		typedefs_t typedefs_;
		simple_functions_t simple_functions_;
		operator_functions_t operator_functions_;
		variables_t variables_;

		weak_namespaces_t using_directive_namespaces_;
};

bool
operator==(const namespace_& lhs, const namespace_& rhs);

bool
operator!=(const namespace_& lhs, const namespace_& rhs);

}}} //namespace scalpel::cpp::semantic_entities

#endif

