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

#ifndef SOCOA_CPP_SYNTAX_TREE_TEMPLATE_ID_HPP
#define SOCOA_CPP_SYNTAX_TREE_TEMPLATE_ID_HPP

#include <memory>
#include <boost/optional.hpp>
#include "../../util/extern_strings.hpp"
#include "composite_node.hpp"
#include "sequence_node.hpp"
#include "identifier.hpp"

namespace socoa { namespace cpp { namespace syntax_tree
{

class template_argument;

class template_id: public composite_node
{
	public:
		template_id
		(
			identifier&& an_identifier,
			boost::optional<sequence_node<template_argument, util::extern_strings::comma>> a_template_argument_list
		);

		inline
		const identifier&
		get_identifier() const;

		inline
		const boost::optional<const sequence_node<template_argument, util::extern_strings::comma>&>
		get_template_argument_list() const;

	private:
		identifier identifier_;
		std::shared_ptr<sequence_node<template_argument, util::extern_strings::comma>> template_argument_list_;
};

inline
const identifier&
template_id::get_identifier() const
{
	return identifier_;
}

inline
const boost::optional<const sequence_node<template_argument, util::extern_strings::comma>&>
template_id::get_template_argument_list() const
{
	if(template_argument_list_)
		return boost::optional<const sequence_node<template_argument, util::extern_strings::comma>&>(*template_argument_list_);
	else
		return boost::optional<const sequence_node<template_argument, util::extern_strings::comma>&>();
}

}}} //namespace socoa::cpp::syntax_tree

#endif
