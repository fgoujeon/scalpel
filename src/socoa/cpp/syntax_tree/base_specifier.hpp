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

#ifndef SOCOA_CPP_SYNTAX_TREE_BASE_SPECIFIER_HPP
#define SOCOA_CPP_SYNTAX_TREE_BASE_SPECIFIER_HPP

#include <boost/optional.hpp>
#include "composite_node.hpp"
#include "access_specifier.hpp"
#include "nested_identifier_or_template_id.hpp"

namespace socoa { namespace cpp { namespace syntax_tree
{

/**
\verbatim
base_specifier
	= ["::"], [nested_name_specifier], class_name
	| "virtual", [access_specifier], ["::"], [nested_name_specifier], class_name
	| access_specifier, ["virtual"], ["::"], [nested_name_specifier], class_name
;
\endverbatim
*/
class base_specifier: public composite_node
{
    public:
        base_specifier
        (
            bool virtual_keyword,
//            boost::optional<access_specifier>&& an_access_specifier,
            boost::optional<nested_identifier_or_template_id>&& a_nested_identifier_or_template_id
        );

		base_specifier(base_specifier&) = delete;

		base_specifier(base_specifier&& o);

        inline
        bool
        has_virtual_keyword() const;

        inline
        const boost::optional<const access_specifier&>
        get_access_specifier() const;

        inline
        const boost::optional<const nested_identifier_or_template_id&>
        get_nested_identifier_or_template_id() const;

    private:
        bool virtual_keyword_;
		/*
		boost::optional<access_specifier> access_specifier_;
		boost::optional<nested_identifier_or_template_id> nested_identifier_or_template_id_;
		*/
		std::unique_ptr<access_specifier> access_specifier_;
		std::unique_ptr<nested_identifier_or_template_id> nested_identifier_or_template_id_;
};

inline
bool
base_specifier::has_virtual_keyword() const
{
    return virtual_keyword_;
}

inline
const boost::optional<const access_specifier&>
base_specifier::get_access_specifier() const
{
	if(access_specifier_)
		return boost::optional<const access_specifier&>(*access_specifier_);
	else
		return boost::optional<const access_specifier&>();
}

inline
const boost::optional<const nested_identifier_or_template_id&>
base_specifier::get_nested_identifier_or_template_id() const
{
	if(nested_identifier_or_template_id_)
		return boost::optional<const nested_identifier_or_template_id&>(*nested_identifier_or_template_id_);
	else
		return boost::optional<const nested_identifier_or_template_id&>();
}

}}} //namespace socoa::cpp::syntax_tree

#endif
