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

#ifndef SOCOA_CPP_SYNTAX_NODES_CLASS_HEAD_HPP
#define SOCOA_CPP_SYNTAX_NODES_CLASS_HEAD_HPP

#include <memory>
#include <boost/optional.hpp>
#include "composite_node.hpp"
#include "class_key.hpp"
#include "nested_name_specifier.hpp"
#include "template_id.hpp"
#include "identifier.hpp"
#include "base_clause.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
{

/**
\verbatim
class_head
	= class_key, [identifier], [base_clause]
	| class_key, nested_name_specifier, identifier, [base_clause]
	| class_key, [nested_name_specifier], template_id, [base_clause]
;
\endverbatim
*/
class class_head: public composite_node
{
    public:
        class_head
        (
            class_key&& a_class_key,
            boost::optional<nested_name_specifier>&& a_nested_name_specifier,
            boost::optional<template_id>&& a_template_id,
            boost::optional<identifier>&& an_identifier,
            boost::optional<base_clause>&& a_base_clause
        );

		class_head(const class_head& o);

		class_head(class_head&& o);

		const class_head&
		operator=(const class_head& o);

        inline
        const class_key&
        get_class_key() const;

        inline
        const boost::optional<const nested_name_specifier&>
        get_nested_name_specifier() const;

        inline
        const boost::optional<const template_id&>
        get_template_id() const;

        inline
        const boost::optional<const identifier&>
        get_identifier() const;

        inline
        const boost::optional<const base_clause&>
        get_base_clause() const;

    private:
		void
		update_node_list();

        class_key class_key_;
        boost::optional<nested_name_specifier> nested_name_specifier_;
        boost::optional<template_id> template_id_;
        boost::optional<identifier> identifier_;
        boost::optional<base_clause> base_clause_;
};

inline
const class_key&
class_head::get_class_key() const
{
    return class_key_;
}

inline
const boost::optional<const nested_name_specifier&>
class_head::get_nested_name_specifier() const
{
	return boost::optional<const nested_name_specifier&>(nested_name_specifier_);
}

inline
const boost::optional<const template_id&>
class_head::get_template_id() const
{
	return boost::optional<const template_id&>(template_id_);
}

inline
const boost::optional<const identifier&>
class_head::get_identifier() const
{
	return boost::optional<const identifier&>(identifier_);
}

inline
const boost::optional<const base_clause&>
class_head::get_base_clause() const
{
	return boost::optional<const base_clause&>(base_clause_);
}

}}} //namespace socoa::cpp::syntax_nodes

#endif
