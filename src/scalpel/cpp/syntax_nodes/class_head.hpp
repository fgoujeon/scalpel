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

#ifndef SCALPEL_CPP_SYNTAX_NODES_CLASS_HEAD_HPP
#define SCALPEL_CPP_SYNTAX_NODES_CLASS_HEAD_HPP

#include <memory>
#include <boost/optional.hpp>
#include "composite_node.hpp"
#include "class_key.hpp"
#include "nested_name_specifier.hpp"
#include "template_id.hpp"
#include "identifier.hpp"
#include "base_clause.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
\verbatim
class_head
	= class_key, [nested_name_specifier], template_id, [base_clause]
	| class_key, nested_name_specifier, identifier, [base_clause]
	| class_key, [identifier], [base_clause]
;

	class_head
		= class_key >> !(!s >> nested_name_specifier) >> !s >> template_id >> !(!s >> base_clause)
		| class_key >> !s >> nested_name_specifier >> !s >> identifier >> !(!s >> base_clause)
		| class_key >> !(!s >> identifier) >> !(!s >> base_clause)
	;
\endverbatim
*/
class class_head: public composite_node
{
    public:
        class_head
        (
            class_key&& class_key_node,
            boost::optional<space>&& pre_nested_name_specifier_space_node,
            boost::optional<nested_name_specifier>&& nested_name_specifier_node,
            boost::optional<space>&& pre_template_id_space_node,
            boost::optional<template_id>&& template_id_node,
            boost::optional<space>&& pre_identifier_space_node,
            boost::optional<identifier>&& identifier_node,
            boost::optional<space>&& pre_base_clause_space_node,
            boost::optional<base_clause>&& base_clause_node
        );

		class_head(const class_head& o);

		class_head(class_head&& o);

		const class_head&
		operator=(const class_head& o);

        inline
        const class_key&
        class_key_node() const;

        inline
        const boost::optional<const nested_name_specifier&>
        nested_name_specifier_node() const;

        inline
        const boost::optional<const template_id&>
        template_id_node() const;

        inline
        const boost::optional<const identifier&>
        identifier_node() const;

        inline
        const boost::optional<const base_clause&>
        base_clause_node() const;

    private:
		void
		update_node_list();

		class_key class_key_;
		boost::optional<space> pre_nested_name_specifier_space_;
		boost::optional<nested_name_specifier> nested_name_specifier_;
		boost::optional<space> pre_template_id_space_;
		boost::optional<template_id> template_id_;
		boost::optional<space> pre_identifier_space_;
		boost::optional<identifier> identifier_;
		boost::optional<space> pre_base_clause_space_;
		boost::optional<base_clause> base_clause_;
};

inline
const class_key&
class_head::class_key_node() const
{
    return class_key_;
}

inline
const boost::optional<const nested_name_specifier&>
class_head::nested_name_specifier_node() const
{
	return boost::optional<const nested_name_specifier&>(nested_name_specifier_);
}

inline
const boost::optional<const template_id&>
class_head::template_id_node() const
{
	return boost::optional<const template_id&>(template_id_);
}

inline
const boost::optional<const identifier&>
class_head::identifier_node() const
{
	return boost::optional<const identifier&>(identifier_);
}

inline
const boost::optional<const base_clause&>
class_head::base_clause_node() const
{
	return boost::optional<const base_clause&>(base_clause_);
}

}}} //namespace scalpel::cpp::syntax_nodes

#endif
