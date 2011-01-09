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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_CV_QUALIFIERS_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_CV_QUALIFIERS_HPP

#include "type_variants_fwd.hpp"

namespace scalpel { namespace cpp { namespace semantic_entities
{

enum class cv_qualification
{
	CONST,
	VOLATILE,
	CONST_AND_VOLATILE
};

/**
Represents the const and volatile qualifiers.
*/
class cv_qualifiers
{
	public:
		cv_qualifiers(const type_variant& qualified_type, const cv_qualification qualification);

		const type_variant&
		qualified_type() const
		{
			return qualified_type_;
		}

		cv_qualification
		qualification() const
		{
			return qualification_;
		}

		bool
		const_qualified() const
		{
			return
				qualification_ == cv_qualification::CONST ||
				qualification_ == cv_qualification::CONST_AND_VOLATILE
			;
		}

		bool
		volatile_qualified() const
		{
			return
				qualification_ == cv_qualification::VOLATILE ||
				qualification_ == cv_qualification::CONST_AND_VOLATILE
			;
		}

	private:
		type_variant qualified_type_;
		cv_qualification qualification_;
};

bool
operator==(const cv_qualifiers& lhs, const cv_qualifiers& rhs);

bool
operator!=(const cv_qualifiers& lhs, const cv_qualifiers& rhs);

}}} //namespace scalpel::cpp::semantic_entities

#endif

