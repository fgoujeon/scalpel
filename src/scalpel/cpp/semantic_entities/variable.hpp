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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_VARIABLE_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_VARIABLE_HPP

#include "type_variants.hpp"
#include "declarative_region_member_impl.hpp"
#include <boost/noncopyable.hpp>
#include <string>
#include <memory>

namespace scalpel { namespace cpp { namespace semantic_entities
{

/**
Represents a C++ variable.
*/
class variable
{
	public:
		variable
		(
			const std::string& name,
			const type_shared_ptr_variant& type,
			bool is_is_static = false
		);

		variable(const variable& v);

		variable(variable&& v);

		const variable&
		operator=(variable&& v);

		const type_shared_ptr_variant&
		type() const;

		const std::string&
		name() const;

		bool
		is_static() const;

		bool
		has_declarative_region() const;

		declarative_region_shared_ptr_variant
		declarative_region() const;

		void
		declarative_region(const declarative_region_shared_ptr_variant& declarative_region);

	private:
		type_shared_ptr_variant type_;
		std::string name_;
		bool is_static_;
		declarative_region_member_impl declarative_region_member_impl_;
};

}}} //namespace scalpel::cpp::semantic_entities

#endif
