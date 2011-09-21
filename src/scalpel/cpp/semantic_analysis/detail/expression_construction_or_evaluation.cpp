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

#include "expression_construction_or_evaluation.hpp"
#include "conversion_construction.hpp"
#include "value_construction.hpp"
#include "semantic_entity_analysis/expression_information.hpp"
#include <limits>

namespace scalpel { namespace cpp { namespace semantic_analysis { namespace detail
{

using namespace syntax_nodes;
using namespace semantic_entities;
using namespace semantic_entity_analysis;

semantic_entities::expression_t
expression_creation_or_evaluation_policies::negation::create
(
	semantic_entities::expression_t operand
)
{
	//TODO

	return semantic_entities::negation_expression
	(
		operand
	);
}

semantic_entities::expression_t
expression_creation_or_evaluation_policies::logical_negation::create
(
	semantic_entities::expression_t operand
)
{
	//TODO

	return semantic_entities::logical_negation_expression
	(
		operand
	);
}

semantic_entities::expression_t
expression_creation_or_evaluation_policies::complement::create
(
	semantic_entities::expression_t operand
)
{
	//TODO

	return semantic_entities::complement_expression
	(
		operand
	);
}

semantic_entities::expression_t
expression_creation_or_evaluation_policies::addition::create
(
	semantic_entities::expression_t left_operand,
	semantic_entities::expression_t right_operand
)
{
	const expression_information left_operand_info(left_operand);
	const expression_information right_operand_info(right_operand);

	//For addition, either both operands shall have arithmetic or enumeration
	//type, or one operand shall be a pointer to a completely defined object
	//type and the other shall have integral or enumeration type.
	if(left_operand_info.has_arithmetic_or_enumeration_type() && right_operand_info.has_arithmetic_or_enumeration_type())
	{
		create_usual_arithmetic_conversions
		(
			left_operand,
			right_operand,
			false,
			left_operand_info,
			right_operand_info
		);
	}
	else if(left_operand_info.has_pointer_to_defined_type_type() && right_operand_info.has_integral_or_enumeration_type())
	{
		//TODO
	}
	else if(left_operand_info.has_integral_or_enumeration_type() && right_operand_info.has_pointer_to_defined_type_type())
	{
		//TODO
	}
	else
	{
		throw std::runtime_error("create_addition_expression error");
	}

	return semantic_entities::addition_expression
	(
		left_operand,
		right_operand
	);
}

semantic_entities::expression_t
expression_creation_or_evaluation_policies::subtraction::create
(
	semantic_entities::expression_t left_operand,
	semantic_entities::expression_t right_operand
)
{
	const expression_information left_operand_info(left_operand);
	const expression_information right_operand_info(right_operand);

	//For subtraction, one of the following shall hold:
	//- both operands have arithmetic or enumeration type; or
	//- both operands are pointers to cv-qualified or cv-unqualified versions of the same completely defined
	//object type; or
	//- the left operand is a pointer to a completely defined object type and the right operand has integral or
	//enumeration type.
	if(left_operand_info.has_arithmetic_or_enumeration_type() && right_operand_info.has_arithmetic_or_enumeration_type())
	{
		create_usual_arithmetic_conversions
		(
			left_operand,
			right_operand,
			false,
			left_operand_info,
			right_operand_info
		);
	}
	else
	{
		throw std::runtime_error("create_subtraction_expression error");
	}

	return semantic_entities::subtraction_expression
	(
		left_operand,
		right_operand
	);
}

semantic_entities::expression_t
expression_creation_or_evaluation_policies::multiplication::create
(
	semantic_entities::expression_t left_operand,
	semantic_entities::expression_t right_operand
)
{
	const expression_information left_operand_info(left_operand);
	const expression_information right_operand_info(right_operand);

	//the operands of * shall have arithmetic or enumeration type
	if(left_operand_info.has_arithmetic_or_enumeration_type() && right_operand_info.has_arithmetic_or_enumeration_type())
	{
		create_usual_arithmetic_conversions
		(
			left_operand,
			right_operand,
			false,
			left_operand_info,
			right_operand_info
		);
	}
	else
	{
		throw std::runtime_error("create_multiplication_expression error");
	}

	return semantic_entities::multiplication_expression
	(
		left_operand,
		right_operand
	);
}

semantic_entities::expression_t
expression_creation_or_evaluation_policies::division::create
(
	semantic_entities::expression_t left_operand,
	semantic_entities::expression_t right_operand
)
{
	const expression_information left_operand_info(left_operand);
	const expression_information right_operand_info(right_operand);

	//the operands of / shall have arithmetic or enumeration type
	if(left_operand_info.has_arithmetic_or_enumeration_type() && right_operand_info.has_arithmetic_or_enumeration_type())
	{
		create_usual_arithmetic_conversions
		(
			left_operand,
			right_operand,
			false,
			left_operand_info,
			right_operand_info
		);
	}
	else
	{
		throw std::runtime_error("create_division_expression error");
	}

	return semantic_entities::division_expression
	(
		left_operand,
		right_operand
	);
}

semantic_entities::expression_t
expression_creation_or_evaluation_policies::modulo::create
(
	semantic_entities::expression_t left_operand,
	semantic_entities::expression_t right_operand
)
{
	const expression_information left_operand_info(left_operand);
	const expression_information right_operand_info(right_operand);

	//the operands of % shall have integral or enumeration type
	if(left_operand_info.has_integral_or_enumeration_type() && right_operand_info.has_integral_or_enumeration_type())
	{
		create_usual_arithmetic_conversions
		(
			left_operand,
			right_operand,
			false,
			left_operand_info,
			right_operand_info
		);
	}
	else
	{
		throw std::runtime_error("create_modulo_expression error");
	}

	return semantic_entities::modulo_expression
	(
		left_operand,
		right_operand
	);
}

semantic_entities::expression_t
expression_creation_or_evaluation_policies::left_shift::create
(
	semantic_entities::expression_t left_operand,
	semantic_entities::expression_t right_operand
)
{
	const expression_information left_operand_info(left_operand);
	const expression_information right_operand_info(right_operand);

	//The operands shall be of integral or enumeration type and integral promotions are performed.
	if(left_operand_info.has_integral_or_enumeration_type() && right_operand_info.has_integral_or_enumeration_type())
	{
		create_usual_arithmetic_conversions
		(
			left_operand,
			right_operand,
			false,
			left_operand_info,
			right_operand_info
		);
	}
	else
	{
		throw std::runtime_error("create_left_shift_expression error");
	}

	return semantic_entities::left_shift_expression
	(
		left_operand,
		right_operand
	);
}

semantic_entities::expression_t
expression_creation_or_evaluation_policies::right_shift::create
(
	semantic_entities::expression_t left_operand,
	semantic_entities::expression_t right_operand
)
{
	const expression_information left_operand_info(left_operand);
	const expression_information right_operand_info(right_operand);

	//The operands shall be of integral or enumeration type and integral promotions are performed.
	if(left_operand_info.has_integral_or_enumeration_type() && right_operand_info.has_integral_or_enumeration_type())
	{
		create_usual_arithmetic_conversions
		(
			left_operand,
			right_operand,
			false,
			left_operand_info,
			right_operand_info
		);
	}
	else
	{
		throw std::runtime_error("create_right_shift_expression error");
	}

	return semantic_entities::right_shift_expression
	(
		left_operand,
		right_operand
	);
}

semantic_entities::expression_t
expression_creation_or_evaluation_policies::less_than_or_equal_to::create
(
	semantic_entities::expression_t left_operand,
	semantic_entities::expression_t right_operand
)
{
	//const expression_information left_operand_info(left_operand);
	//const expression_information right_operand_info(right_operand);

	//The operands shall have arithmetic, enumeration or pointer type
	//TODO

	return semantic_entities::less_than_or_equal_to_expression
	(
		left_operand,
		right_operand
	);
}

semantic_entities::expression_t
expression_creation_or_evaluation_policies::less_than::create
(
	semantic_entities::expression_t left_operand,
	semantic_entities::expression_t right_operand
)
{
	//const expression_information left_operand_info(left_operand);
	//const expression_information right_operand_info(right_operand);

	//The operands shall have arithmetic, enumeration or pointer type
	//TODO

	return semantic_entities::less_than_expression
	(
		left_operand,
		right_operand
	);
}

semantic_entities::expression_t
expression_creation_or_evaluation_policies::greater_than::create
(
	semantic_entities::expression_t left_operand,
	semantic_entities::expression_t right_operand
)
{
	//const expression_information left_operand_info(left_operand);
	//const expression_information right_operand_info(right_operand);

	//The operands shall have arithmetic, enumeration or pointer type
	//TODO

	return semantic_entities::greater_than_expression
	(
		left_operand,
		right_operand
	);
}

semantic_entities::expression_t
expression_creation_or_evaluation_policies::greater_than_or_equal_to::create
(
	semantic_entities::expression_t left_operand,
	semantic_entities::expression_t right_operand
)
{
	//const expression_information left_operand_info(left_operand);
	//const expression_information right_operand_info(right_operand);

	//The operands shall have arithmetic, enumeration or pointer type
	//TODO

	return semantic_entities::greater_than_or_equal_to_expression
	(
		left_operand,
		right_operand
	);
}

semantic_entities::expression_t
expression_creation_or_evaluation_policies::equal_to::create
(
	semantic_entities::expression_t left_operand,
	semantic_entities::expression_t right_operand
)
{
	//TODO

	return semantic_entities::equal_to_expression
	(
		left_operand,
		right_operand
	);
}

semantic_entities::expression_t
expression_creation_or_evaluation_policies::not_equal_to::create
(
	semantic_entities::expression_t left_operand,
	semantic_entities::expression_t right_operand
)
{
	//TODO

	return semantic_entities::not_equal_to_expression
	(
		left_operand,
		right_operand
	);
}

semantic_entities::expression_t
expression_creation_or_evaluation_policies::bitwise_and::create
(
	semantic_entities::expression_t left_operand,
	semantic_entities::expression_t right_operand
)
{
	//TODO

	return semantic_entities::bitwise_and_expression
	(
		left_operand,
		right_operand
	);
}

semantic_entities::expression_t
expression_creation_or_evaluation_policies::bitwise_exclusive_or::create
(
	semantic_entities::expression_t left_operand,
	semantic_entities::expression_t right_operand
)
{
	//TODO

	return semantic_entities::bitwise_exclusive_or_expression
	(
		left_operand,
		right_operand
	);
}

semantic_entities::expression_t
expression_creation_or_evaluation_policies::bitwise_inclusive_or::create
(
	semantic_entities::expression_t left_operand,
	semantic_entities::expression_t right_operand
)
{
	//TODO

	return semantic_entities::bitwise_inclusive_or_expression
	(
		left_operand,
		right_operand
	);
}

semantic_entities::expression_t
expression_creation_or_evaluation_policies::logical_and::create
(
	semantic_entities::expression_t left_operand,
	semantic_entities::expression_t right_operand
)
{
	//TODO

	return semantic_entities::logical_and_expression
	(
		left_operand,
		right_operand
	);
}

semantic_entities::expression_t
expression_creation_or_evaluation_policies::logical_or::create
(
	semantic_entities::expression_t left_operand,
	semantic_entities::expression_t right_operand
)
{
	//TODO

	return semantic_entities::logical_or_expression
	(
		left_operand,
		right_operand
	);
}

}}}} //namespace scalpel::cpp::semantic_analysis::detail

