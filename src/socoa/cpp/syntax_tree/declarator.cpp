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

#include "declarator.hpp"

#include "declarator_impl.hpp"
#include "ptr_operator.hpp"
#include "direct_declarator.hpp"

namespace socoa { namespace cpp { namespace syntax_tree
{

declarator::declarator
(
	std::vector<ptr_operator>&& ptr_operators,
	direct_declarator&& a_direct_declarator
):
	pimpl_
	(
		std::make_shared<declarator_impl>
		(
			ptr_operators,
			a_direct_declarator
		)
	)
{
}

const std::vector<ptr_operator>&
declarator::get_ptr_operators() const
{
    return pimpl_->get_ptr_operators();
}

const direct_declarator&
declarator::get_direct_declarator() const
{
    return pimpl_->get_direct_declarator();
}

}}} //namespace socoa::cpp::syntax_tree
