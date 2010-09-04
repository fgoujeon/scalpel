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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_NAMESPACE_ALIAS_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_NAMESPACE_ALIAS_HPP

#include "namespace_.hpp"
#include <string>
#include <memory>

namespace scalpel { namespace cpp { namespace semantic_entities
{

/**
Represents a C++ namespace alias.
*/
class namespace_alias
{
	public:
		namespace_alias
		(
			const std::string name,
			std::shared_ptr<namespace_> referred_namespace
		);

		const std::string&
		name() const
		{
			return name_;
		}

		std::shared_ptr<namespace_>
		referred_namespace() const
		{
			return std::shared_ptr<namespace_>(referred_namespace_);
		}

		bool
		has_enclosing_declarative_region() const
		{
			return referred_namespace_.lock()->has_enclosing_declarative_region();
		}

		std::shared_ptr<namespace_>
		enclosing_declarative_region()
		{
			return referred_namespace_.lock()->enclosing_declarative_region();
		}

		std::shared_ptr<const namespace_>
		enclosing_declarative_region() const
		{
			return referred_namespace_.lock()->enclosing_declarative_region();
		}

		void
		enclosing_declarative_region(std::shared_ptr<namespace_> enclosing_declarative_region)
		{
			referred_namespace_.lock()->enclosing_declarative_region(enclosing_declarative_region);
		}

		const namespace_::open_declarative_region_shared_ptr_variants_t&
		open_declarative_regions()
		{
			return referred_namespace_.lock()->open_declarative_regions();
		}

		namespace_::namespaces_t::range
		namespaces()
		{
			return referred_namespace_.lock()->namespaces();
		}

		const namespace_::namespaces_t&
		namespaces() const
		{
			std::shared_ptr<const namespace_> const_referred_namespace = referred_namespace_.lock();
			return const_referred_namespace->namespaces();
		}

		namespace_::classes_t::range
		classes()
		{
			return referred_namespace_.lock()->classes();
		}

		const namespace_::classes_t&
		classes() const
		{
			std::shared_ptr<const namespace_> const_referred_namespace = referred_namespace_.lock();
			return const_referred_namespace->classes();
		}

		namespace_::simple_functions_t::range
		simple_functions()
		{
			return referred_namespace_.lock()->simple_functions();
		}

		const namespace_::simple_functions_t&
		simple_functions() const
		{
			std::shared_ptr<const namespace_> const_referred_namespace = referred_namespace_.lock();
			return const_referred_namespace->simple_functions();
		}

		namespace_::operator_functions_t::range
		operator_functions()
		{
			return referred_namespace_.lock()->operator_functions();
		}

		const namespace_::operator_functions_t&
		operator_functions() const
		{
			std::shared_ptr<const namespace_> const_referred_namespace = referred_namespace_.lock();
			return const_referred_namespace->operator_functions();
		}

		namespace_::variables_t::range
		variables()
		{
			return referred_namespace_.lock()->variables();
		}

		const namespace_::variables_t&
		variables() const
		{
			std::shared_ptr<const namespace_> const_referred_namespace = referred_namespace_.lock();
			return const_referred_namespace->variables();
		}

		const namespace_::namespace_aliases_t&
		namespace_aliases() const
		{
			std::shared_ptr<const namespace_> const_referred_namespace = referred_namespace_.lock();
			return const_referred_namespace->namespace_aliases();
		}

		const namespace_::weak_namespaces_t&
		using_directive_namespaces() const
		{
			std::shared_ptr<const namespace_> const_referred_namespace = referred_namespace_.lock();
			return const_referred_namespace->using_directive_namespaces();
		}

		void
		add_member(std::shared_ptr<namespace_> member)
		{
			referred_namespace_.lock()->add_member(member);
		}

		void
		add_member(std::shared_ptr<class_> member)
		{
			referred_namespace_.lock()->add_member(member);
		}

		void
		add_member(std::shared_ptr<simple_function> member)
		{
			referred_namespace_.lock()->add_member(member);
		}

		void
		add_member(std::shared_ptr<operator_function> member)
		{
			referred_namespace_.lock()->add_member(member);
		}

		void
		add_member(std::shared_ptr<variable> member)
		{
			referred_namespace_.lock()->add_member(member);
		}

		void
		add_member(std::shared_ptr<namespace_alias> member)
		{
			referred_namespace_.lock()->add_member(member);
		}

		void
		add_using_directive_namespace(std::shared_ptr<namespace_> n)
		{
			referred_namespace_.lock()->add_using_directive_namespace(n);
		}

	private:
		std::string name_;
		std::weak_ptr<namespace_> referred_namespace_;
};

}}} //namespace scalpel::cpp::semantic_entities

#endif

