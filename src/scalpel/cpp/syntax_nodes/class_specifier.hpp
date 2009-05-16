/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008, 2009  Florian Goujeon

This file is part of Scalpel.

Scalpel is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Scalpel is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Scalpel.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SCALPEL_CPP_SYNTAX_NODES_CLASS_SPECIFIER_HPP
#define SCALPEL_CPP_SYNTAX_NODES_CLASS_SPECIFIER_HPP

#include <memory>
#include "optional_node.hpp"
#include "composite_node.hpp"
#include "class_head.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

//use of forward declarations and pointers to avoid cyclic dependency
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
            class_head&& class_head_node,
			optional_node<space>&& post_class_head_space_node,
			optional_node<space>&& post_opening_brace_space_node,
            optional_node<member_specification>&& member_specification_node,
			optional_node<space>&& post_member_specification_space_node
        );

        class_specifier(const class_specifier& o);

        class_specifier(class_specifier&& o);

        ~class_specifier();

        const class_specifier&
		operator=(const class_specifier& o);

        inline
        const class_head&
        class_head_node() const;

        inline
        const optional_node<member_specification>&
        member_specification_node() const;

    private:
		void
		update_node_list();

		class_head class_head_;
		optional_node<space> post_class_head_space_;
		optional_node<space> post_opening_brace_space_;
		optional_node<member_specification>* member_specification_;
		optional_node<space> post_member_specification_space_;
};

inline
const class_head&
class_specifier::class_head_node() const
{
    return class_head_;
}

inline
const optional_node<member_specification>&
class_specifier::member_specification_node() const
{
	return *member_specification_;
}

}}} //namespace scalpel::cpp::syntax_nodes

#endif
