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

#ifndef SOCOA_CPP_SYNTAX_NODES_CLASS_SPECIFIER_HPP
#define SOCOA_CPP_SYNTAX_NODES_CLASS_SPECIFIER_HPP

#include <memory>
#include <boost/optional.hpp>
#include "composite_node.hpp"
#include "class_head.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
{

//use of forward declarations and pointers to avoid cyclic dependency
class member_specification;

class class_specifier: public composite_node
{
    public:
        class_specifier
        (
            class_head&& head,
            boost::optional<member_specification>&& a_member_specification
        );

        class_specifier(const class_specifier& o);

        class_specifier(class_specifier&& o);

        const class_specifier&
		operator=(const class_specifier& o);

        inline
        const class_head&
        get_class_head() const;

        inline
        const boost::optional<const member_specification&>
        get_member_specification() const;

    private:
		void
		update_node_list();

		class_head class_head_;
		std::shared_ptr<member_specification> member_specification_;
};

inline
const class_head&
class_specifier::get_class_head() const
{
    return class_head_;
}

inline
const boost::optional<const member_specification&>
class_specifier::get_member_specification() const
{
	if(member_specification_)
		return boost::optional<const member_specification&>(*member_specification_);
	else
		return boost::optional<const member_specification&>();
}

}}} //namespace socoa::cpp::syntax_nodes

#endif
