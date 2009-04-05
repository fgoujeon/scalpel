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

#ifndef SOCOA_CPP_SYNTAX_TREE_CLASS_SPECIFIER_HPP
#define SOCOA_CPP_SYNTAX_TREE_CLASS_SPECIFIER_HPP

#include <memory>
#include <boost/optional.hpp>
#include "composite_node.hpp"

namespace socoa { namespace cpp { namespace syntax_tree
{

class class_specifier_impl;
class class_head;
class member_specification;

/**
\verbatim
class_specifier
	= class_head, "{", [member_specification], "}"
;
\endverbatim
*/
class class_specifier: public composite_node
{
    public:
        class_specifier
        (
            class_head&& head,
            boost::optional<member_specification> a_member_specification
        );

        const class_head&
        get_class_head() const;

        const boost::optional<const member_specification&>
        get_member_specification() const;

    private:
		std::shared_ptr<class_specifier_impl> pimpl_;
};

}}} //namespace socoa::cpp::syntax_tree

#endif
