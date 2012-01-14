/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2012  Florian Goujeon

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

#include "conditional_expression.hpp"
#include "expression.hpp"

namespace scalpel { namespace cpp { namespace semantic_entities
{

conditional_expression::conditional_expression
(
	const expression_t& condition_operand,
	const expression_t& true_operand,
	const expression_t& false_operand
):
	condition_operand_(new expression_t(condition_operand)),
	true_operand_(new expression_t(true_operand)),
	false_operand_(new expression_t(false_operand))
{
}

conditional_expression::conditional_expression(const conditional_expression& rhs):
	condition_operand_(new expression_t(rhs.condition_operand())),
	true_operand_(new expression_t(rhs.true_operand())),
	false_operand_(new expression_t(rhs.false_operand()))
{
}

}}} //namespace scalpel::cpp::semantic_entities

