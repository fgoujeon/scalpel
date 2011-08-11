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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_ENUM_CONSTANT_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_ENUM_CONSTANT_HPP

#include <string>

namespace scalpel { namespace cpp { namespace semantic_entities
{

template<typename UnderlyingType>
class enum_constant_list;

class enum_t;
class member_enum_t;

template<typename UnderlyingType>
class enum_constant
{
	public:
		typedef
			utility::variant
			<
				enum_t*,
				member_enum_t*
			>
			type_t
		;

        enum_constant(const std::string& name, const UnderlyingType value);

        enum_constant(const enum_constant&) = delete;

        enum_constant&
		operator=(const enum_constant&) = delete;

		const std::string&
		name() const
		{
			return name_;
		}

		UnderlyingType
		value() const
		{
			return value_;
		}

		void
		parent_list(enum_constant_list<UnderlyingType>& list)
		{
			assert(parent_list_ == nullptr);
			parent_list_ = &list;
		}

		type_t
		type() const;

	private:
		std::string name_;
		UnderlyingType value_;
		enum_constant_list<UnderlyingType>* parent_list_;
};

}}} //namespace scalpel::cpp::semantic_entities

#include "enum_constant.ipp"

#endif

