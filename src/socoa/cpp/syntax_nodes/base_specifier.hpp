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

#ifndef SOCOA_CPP_SYNTAX_NODES_BASE_SPECIFIER_HPP
#define SOCOA_CPP_SYNTAX_NODES_BASE_SPECIFIER_HPP

#include <boost/optional.hpp>
#include "composite_node.hpp"
#include "access_specifier.hpp"
#include "nested_identifier_or_template_id.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
{

/**
\verbatim
base_specifier
	= ["::"], [nested_name_specifier], class_name
	| "virtual", [access_specifier], ["::"], [nested_name_specifier], class_name
	| access_specifier, ["virtual"], ["::"], [nested_name_specifier], class_name
;
\endverbatim

	base_specifier
		= nested_identifier_or_template_id
		| "virtual" >> !s >> !access_specifier >> !s >> nested_identifier_or_template_id
		| access_specifier >> !s >> !str_p("virtual") >> !s >> nested_identifier_or_template_id
	;
*/
class base_specifier: public composite_node
{
    public:
        base_specifier
        (
            bool virtual_keyword,
			bool virtual_keyword_first,
			boost::optional<space>&& post_virtual_keyword_space_node,
            boost::optional<access_specifier>&& an_access_specifier,
			boost::optional<space>&& post_access_specifier_space_node,
            boost::optional<nested_identifier_or_template_id>&& a_nested_identifier_or_template_id
        );

		base_specifier(const base_specifier& o);

		base_specifier(base_specifier&& o);

		const base_specifier&
		operator=(const base_specifier& o);

        inline
        bool
        has_virtual_keyword() const;

        inline
        const boost::optional<const access_specifier&>
        access_specifier_node() const;

        inline
        const boost::optional<const nested_identifier_or_template_id&>
        nested_identifier_or_template_id_node() const;

    private:
		void
		update_node_list();

        bool virtual_keyword_;
        bool virtual_keyword_first_;
		boost::optional<space> post_virtual_keyword_space_;
		boost::optional<access_specifier> access_specifier_;
		boost::optional<space> post_access_specifier_space_;
		boost::optional<nested_identifier_or_template_id> nested_identifier_or_template_id_;
};

inline
bool
base_specifier::has_virtual_keyword() const
{
    return virtual_keyword_;
}

inline
const boost::optional<const access_specifier&>
base_specifier::access_specifier_node() const
{
	return boost::optional<const access_specifier&>(access_specifier_);
}

inline
const boost::optional<const nested_identifier_or_template_id&>
base_specifier::nested_identifier_or_template_id_node() const
{
	return boost::optional<const nested_identifier_or_template_id&>(nested_identifier_or_template_id_);
}

}}} //namespace socoa::cpp::syntax_nodes

#endif
