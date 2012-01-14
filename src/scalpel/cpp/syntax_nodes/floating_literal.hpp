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

#ifndef SCALPEL_CPP_SYNTAX_NODES_FLOATING_LITERAL_HPP
#define SCALPEL_CPP_SYNTAX_NODES_FLOATING_LITERAL_HPP

#include "leaf_node.hpp"
#include <string>

namespace scalpel { namespace cpp { namespace syntax_nodes
{

struct digit_sequence: public leaf_node
{
	digit_sequence(std::string&& value):
		leaf_node(value)
	{
	}

	digit_sequence(const digit_sequence& o):
		leaf_node(o)
	{
	}

	digit_sequence(digit_sequence&& o):
		leaf_node(o)
	{
	}
};

struct sign: public leaf_node
{
	sign(std::string&& value):
		leaf_node(value)
	{
	}

	sign(const sign& o):
		leaf_node(o)
	{
	}

	sign(sign&& o):
		leaf_node(o)
	{
	}
};



typedef
	sequence_node
	<
		optional_node<sign>,
		digit_sequence
	>
	exponent_part
;

inline
const optional_node<sign>&
get_sign(const exponent_part& o)
{
	return get<0>(o);
}

inline
const digit_sequence&
get_digit_sequence(const exponent_part& o)
{
	return get<1>(o);
}



struct float_floating_suffix: public leaf_node
{
	float_floating_suffix(std::string&& value):
		leaf_node(value)
	{
	}

	float_floating_suffix(const float_floating_suffix& o):
		leaf_node(o)
	{
	}

	float_floating_suffix(float_floating_suffix&& o):
		leaf_node(o)
	{
	}
};

struct long_floating_suffix: public leaf_node
{
	long_floating_suffix(std::string&& value):
		leaf_node(value)
	{
	}

	long_floating_suffix(const long_floating_suffix& o):
		leaf_node(o)
	{
	}

	long_floating_suffix(long_floating_suffix&& o):
		leaf_node(o)
	{
	}
};

typedef
	alternative_node
	<
		float_floating_suffix,
		long_floating_suffix
	>
	floating_suffix
;



/*
floating_literal
	= !digit_sequence >> no_node_d[ch_p('.')] >> digit_sequence >> !exponent_part >> !floating_suffix
	| digit_sequence >> no_node_d[ch_p('.')] >> !exponent_part >> !floating_suffix
	| digit_sequence >> exponent_part >> !floating_suffix
;
*/
typedef
	sequence_node
	<
		optional_node<digit_sequence>,
		optional_node<digit_sequence>,
		optional_node<exponent_part>,
		optional_node<floating_suffix>
	>
	floating_literal
;

inline
const optional_node<digit_sequence>&
get_integer_part(const floating_literal& o)
{
	return get<0>(o);
}

inline
const optional_node<digit_sequence>&
get_fractional_part(const floating_literal& o)
{
	return get<1>(o);
}

inline
const optional_node<exponent_part>&
get_exponent_part(const floating_literal& o)
{
	return get<2>(o);
}

inline
const optional_node<floating_suffix>&
get_floating_suffix(const floating_literal& o)
{
	return get<3>(o);
}

}}} //namespace scalpel::cpp::syntax_nodes

#endif

