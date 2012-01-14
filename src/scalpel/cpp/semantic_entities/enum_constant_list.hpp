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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_ENUM_CONSTANT_LIST_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_ENUM_CONSTANT_LIST_HPP

#include "enum_constant.hpp"
#include <scalpel/utility/unique_ptr_vector_range.hpp>

namespace scalpel { namespace cpp { namespace semantic_entities
{

class enum_;
class member_enum;

template<typename UnderlyingType>
class enum_constant_list
{
	public:
		typedef enum_constant<UnderlyingType> constant;
		typedef std::vector<std::unique_ptr<constant>> constants_t;

		typedef
			utility::variant
			<
				enum_*,
				member_enum*
			>
			parent_enum_t
		;

		template<class Enum>
		enum_constant_list(Enum& parent):
			parent_enum_(&parent)
		{
		}

		enum_constant_list(const enum_constant_list&) = delete;

		enum_constant_list(enum_constant_list&& rhs):
			parent_enum_(rhs.parent_enum_),
			constants_(std::move(rhs.constants_))
		{
		}

		enum_constant_list&
		operator=(const enum_constant_list&) = delete;

		enum_constant_list&
		operator=(enum_constant_list&& rhs)
		{
			parent_enum_ = rhs.parent_enum_;
			constants_ = std::move(rhs.constants_);
		}

		typename utility::unique_ptr_vector_range<constant>::type
		constants()
		{
			return utility::make_unique_ptr_vector_range(constants_);
		}

		typename utility::unique_ptr_vector_const_range<constant>::type
		constants() const
		{
			return utility::make_unique_ptr_vector_const_range(constants_);
		}

		void
		add(std::unique_ptr<constant>&& c)
		{
			c->enclosing_declarative_region(parent_enum_);
			constants_.push_back(std::move(c));
		}

	private:
		parent_enum_t parent_enum_;
		constants_t constants_;
};

}}} //namespace scalpel::cpp::semantic_entities

#endif

