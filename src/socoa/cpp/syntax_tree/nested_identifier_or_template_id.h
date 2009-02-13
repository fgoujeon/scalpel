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

#ifndef SOCOA_CPP_SYNTAX_TREE_NESTED_IDENTIFIER_OR_TEMPLATE_ID_H
#define SOCOA_CPP_SYNTAX_TREE_NESTED_IDENTIFIER_OR_TEMPLATE_ID_H

#include <memory>
#include <boost/optional.hpp>
#include "visitor.h"
#include "declarator_id.h"
#include "simple_type_specifier.h"
#include "mem_initializer_id.h"
#include "nested_name_specifier.h"

namespace socoa { namespace cpp { namespace syntax_tree
{

class identifier_or_template_id;

class nested_identifier_or_template_id:
    public declarator_id,
    public simple_type_specifier,
    public mem_initializer_id
{
	public:
		nested_identifier_or_template_id
		(
			bool leading_double_colon,
			std::shared_ptr<nested_name_specifier> a_nested_name_specifier,
			std::shared_ptr<identifier_or_template_id> an_identifier_or_template_id
		);

		inline
		bool
		has_leading_double_colon() const;

		inline
		const boost::optional<const nested_name_specifier&>
		get_nested_name_specifier() const;

		inline
		const std::shared_ptr<const identifier_or_template_id>
		get_identifier_or_template_id() const;

		SOCOA_CPP_DEFINE_VISITABLE()

	private:
		bool leading_double_colon_;
		boost::optional<nested_name_specifier> nested_name_specifier_;
		std::shared_ptr<identifier_or_template_id> identifier_or_template_id_;
};

inline
bool
nested_identifier_or_template_id::has_leading_double_colon() const
{
	return leading_double_colon_;
}

inline
const boost::optional<const nested_name_specifier&>
nested_identifier_or_template_id::get_nested_name_specifier() const
{
	return boost::optional<const nested_name_specifier&>(nested_name_specifier_);
}

inline
const std::shared_ptr<const identifier_or_template_id>
nested_identifier_or_template_id::get_identifier_or_template_id() const
{
	return identifier_or_template_id_;
}

}}} //namespace socoa::cpp::syntax_tree

#endif
