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

#include "labeled_statement_impl.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

labeled_statement_impl::labeled_statement_impl(case_statement&& o):
	labeled_statement_t(std::move(o))
{
}

labeled_statement_impl::labeled_statement_impl(default_statement&& o):
	labeled_statement_t(std::move(o))
{
}

labeled_statement_impl::labeled_statement_impl(classic_labeled_statement&& o):
	labeled_statement_t(std::move(o))
{
}

labeled_statement_impl::labeled_statement_impl(const labeled_statement_impl& o):
	labeled_statement_t(static_cast<const labeled_statement_t&>(o))
{
}

labeled_statement_impl::labeled_statement_impl(labeled_statement_impl&& o):
	labeled_statement_t(static_cast<labeled_statement_t&&>(o))
{
}

}}} //namespace scalpel::cpp::syntax_nodes

