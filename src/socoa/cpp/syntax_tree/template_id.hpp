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
#include "../../util/sequence.hpp"
#include "../../util/extern_strings.hpp"
#include "identifier.hpp"

namespace socoa { namespace cpp { namespace syntax_tree
{

class template_id_impl;
class template_argument;

class template_id
{
	public:
		template_id
		(
			identifier&& an_identifier,
			boost::optional<util::sequence<template_argument, util::extern_strings::comma>> a_template_argument_list
		);

		const identifier&
		get_identifier() const;

		const boost::optional<const util::sequence<template_argument, util::extern_strings::comma>&>
		get_template_argument_list() const;

	private:
		std::shared_ptr<template_id_impl> pimpl_;
};

}}} //namespace socoa::cpp::syntax_tree

#endif
