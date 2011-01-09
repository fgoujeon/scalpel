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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_CV_QUALIFIED_TYPE_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_CV_QUALIFIED_TYPE_HPP

#include "type_variants_fwd.hpp"

namespace scalpel { namespace cpp { namespace semantic_entities
{

/**
Represents the const and volatile qualifiers.
*/
class cv_qualified_type
{
	public:
		enum class qualification_type
		{
			CONST,
			VOLATILE,
			CONST_AND_VOLATILE
		};

		cv_qualified_type(const type_variant& qualified_type, const qualification_type qualification);

		const type_variant&
		qualified_type() const
		{
			return qualified_type_;
		}

		qualification_type
		qualification() const
		{
			return qualification_;
		}

		bool
		const_qualified() const
		{
			return
				qualification_ == qualification_type::CONST ||
				qualification_ == qualification_type::CONST_AND_VOLATILE
			;
		}

		bool
		volatile_qualified() const
		{
			return
				qualification_ == qualification_type::VOLATILE ||
				qualification_ == qualification_type::CONST_AND_VOLATILE
			;
		}

	private:
		type_variant qualified_type_;
		qualification_type qualification_;
};

bool
operator==(const cv_qualified_type& lhs, const cv_qualified_type& rhs);

bool
operator!=(const cv_qualified_type& lhs, const cv_qualified_type& rhs);

}}} //namespace scalpel::cpp::semantic_entities

#endif

