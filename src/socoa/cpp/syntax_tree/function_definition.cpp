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

#include "function_definition.h"

#include "function_definition_impl.h"

namespace socoa { namespace cpp { namespace syntax_tree
{

function_definition::function_definition
(
    boost::optional<util::sequence<decl_specifier>> a_decl_specifier_seq,
    declarator&& a_declarator,
    boost::optional<ctor_initializer> a_ctor_initializer
):
	pimpl_
	(
		std::make_shared<function_definition_impl>
		(
			a_decl_specifier_seq,
			a_declarator,
			a_ctor_initializer
		)
	)
{
}

const boost::optional<const util::sequence<decl_specifier>&>
function_definition::get_decl_specifier_seq() const
{
	return pimpl_->get_decl_specifier_seq();
}

const declarator&
function_definition::get_declarator() const
{
	return pimpl_->get_declarator();
}

const boost::optional<const ctor_initializer&>
function_definition::get_ctor_initializer() const
{
	return pimpl_->get_ctor_initializer();
}

}}} //namespace socoa::cpp::syntax_tree
