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

#include "namespace_definition.hpp"

#include "namespace_definition_impl.hpp"

namespace socoa { namespace cpp { namespace syntax_tree
{

namespace_definition::namespace_definition
(
    boost::optional<identifier> an_identifier,
    boost::optional<util::sequence<declaration>> a_declaration_seq
):
	pimpl_
	(
		std::make_shared<namespace_definition_impl>
		(
			an_identifier,
			a_declaration_seq
		)
	)
{
}

const boost::optional<const identifier&>
namespace_definition::get_identifier() const
{
	return pimpl_->get_identifier();
}

const boost::optional<const util::sequence<declaration>&>
namespace_definition::get_declaration_seq() const
{
	return pimpl_->get_declaration_seq();
}

}}} //namespace socoa::cpp::syntax_tree
