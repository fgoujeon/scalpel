/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2011  Florian Goujeon

This file is part of Scalpel.

Scalpel is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Scalpel is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Scalpel.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "make_expression.hpp"
#include "../../expression.hpp"

namespace scalpel { namespace cpp { namespace semantic_entities { namespace utility_functions { namespace detail
{

std::unique_ptr<expression_t>
make_expression(const expression_t& exp)
{
	return std::unique_ptr<expression_t>(new expression_t(exp));
}

}}}}} //namespace scalpel::cpp::semantic_entities::utility_functions::detail

