/*
Socoa - Source Code Analysis Library
Copyright © 2008, 2009  Florian Goujeon

This file is part of Socoa.

Socoa is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Socoa is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Socoa.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SOCOA_CPP_SYNTAX_TREE_NESTED_NAME_SPECIFIER_H
#define SOCOA_CPP_SYNTAX_TREE_NESTED_NAME_SPECIFIER_H

#include <vector>
#include <boost/optional.hpp>
#include "identifier_or_template_id.h"
#include "nested_name_specifier_part.h"

namespace socoa { namespace cpp { namespace syntax_tree
{

class nested_name_specifier
{
	public:
		nested_name_specifier
		(
			boost::optional<identifier_or_template_id> an_identifier_or_template_id,
			std::vector<nested_name_specifier_part> parts
		);

		inline
		const boost::optional<const identifier_or_template_id&>
		get_identifier_or_template_id() const;

		inline
		const std::vector<nested_name_specifier_part>
		get_parts() const;

	private:
		boost::optional<identifier_or_template_id> identifier_or_template_id_;
		std::vector<nested_name_specifier_part> parts_;
};

inline
const boost::optional<const identifier_or_template_id&>
nested_name_specifier::get_identifier_or_template_id() const
{
	return boost::optional<const identifier_or_template_id&>(identifier_or_template_id_);
}

inline
const std::vector<nested_name_specifier_part>
nested_name_specifier::get_parts() const
{
	return parts_;
}

}}} //namespace socoa::cpp::syntax_tree

#endif
