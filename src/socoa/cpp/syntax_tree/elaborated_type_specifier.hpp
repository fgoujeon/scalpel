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

#ifndef SOCOA_CPP_SYNTAX_TREE_ELABORATED_TYPE_SPECIFIER_HPP
#define SOCOA_CPP_SYNTAX_TREE_ELABORATED_TYPE_SPECIFIER_HPP

#include <boost/optional.hpp>
#include "composite_node.hpp"
#include "class_key.hpp"
#include "nested_name_specifier.hpp"
#include "template_id.hpp"
#include "identifier.hpp"

namespace socoa { namespace cpp { namespace syntax_tree
{

class elaborated_type_specifier: public composite_node
{
    public:
		elaborated_type_specifier
		(
			boost::optional<class_key> a_class_key,
			boost::optional<nested_name_specifier> a_nested_name_specifier,
			boost::optional<template_id> a_template_id,
			boost::optional<identifier> an_identifier,
			bool leading_double_colon,
			bool enum_keyword,
			bool typename_keyword,
			bool template_keyword
		);

		const boost::optional<const class_key&>
		get_class_key() const;

		const boost::optional<const nested_name_specifier&>
		get_nested_name_specifier() const;

		const boost::optional<const template_id&>
		get_template_id() const;

		const boost::optional<const identifier&>
		get_identifier() const;

		bool
		has_leading_double_colon() const;

		bool
		has_enum_keyword() const;

		bool
		has_typename_keyword() const;

		bool
		has_template_keyword() const;

    private:
		boost::optional<class_key> class_key_;
		boost::optional<nested_name_specifier> nested_name_specifier_;
		boost::optional<template_id> template_id_;
		boost::optional<identifier> identifier_;
		bool leading_double_colon_;
		bool enum_keyword_;
		bool typename_keyword_;
		bool template_keyword_;
};

}}} //namespace socoa::cpp::syntax_tree

#endif
