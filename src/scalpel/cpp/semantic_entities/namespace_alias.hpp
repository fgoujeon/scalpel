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

	private:
		std::string name_;
		std::weak_ptr<namespace_> referred_namespace_;
};

}}} //namespace scalpel::cpp::semantic_entities

#endif

