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

#ifndef SCALPEL_CPP_SYNTAX_NODES_INTEGER_LITERAL_HPP
#define SCALPEL_CPP_SYNTAX_NODES_INTEGER_LITERAL_HPP

#include "common.hpp"
#include <string>

namespace scalpel { namespace cpp { namespace syntax_nodes
{

struct decimal_literal: public leaf_node
{
	decimal_literal(std::string&& value):
		leaf_node(value)
	{
	}

	decimal_literal(const decimal_literal& o):
		leaf_node(o)
	{
	}

	decimal_literal(decimal_literal&& o):
		leaf_node(o)
	{
	}
};

struct hexadecimal_literal: public leaf_node
{
	hexadecimal_literal(std::string&& value):
		leaf_node(value)
	{
	}

	hexadecimal_literal(const hexadecimal_literal& o):
		leaf_node(o)
	{
	}

	hexadecimal_literal(hexadecimal_literal&& o):
		leaf_node(o)
	{
	}
};

struct octal_literal: public leaf_node
{
	octal_literal(std::string&& value):
		leaf_node(value)
	{
	}

	octal_literal(const octal_literal& o):
		leaf_node(o)
	{
	}

	octal_literal(octal_literal&& o):
		leaf_node(o)
	{
	}
};

struct unsigned_suffix: public leaf_node
{
	unsigned_suffix(std::string&& value):
		leaf_node(value)
	{
	}

	unsigned_suffix(const unsigned_suffix& o):
		leaf_node(o)
	{
	}

	unsigned_suffix(unsigned_suffix&& o):
		leaf_node(o)
	{
	}
};

struct long_suffix: public leaf_node
{
	long_suffix(std::string&& value):
		leaf_node(value)
	{
	}

	long_suffix(const long_suffix& o):
		leaf_node(o)
	{
	}

	long_suffix(long_suffix&& o):
		leaf_node(o)
	{
	}
};

struct long_long_suffix: public leaf_node
{
	long_long_suffix(std::string&& value):
		leaf_node(value)
	{
	}

	long_long_suffix(const long_long_suffix& o):
		leaf_node(o)
	{
	}

	long_long_suffix(long_long_suffix&& o):
		leaf_node(o)
	{
	}
};

/*
integer_suffix
	= unsigned_suffix >> !(long_long_suffix | long_suffix)
	| (long_long_suffix | long_suffix) >> !unsigned_suffix
;
*/
typedef
	sequence_node
	<
		optional_node<unsigned_suffix>,
		optional_node<long_suffix>,
		optional_node<long_long_suffix>,
		optional_node<unsigned_suffix>
	>
	integer_suffix
;

inline
bool
has_unsigned_suffix(const integer_suffix& o)
{
	return get<0>(o) || get<3>(o);
}

inline
bool
has_long_suffix(const integer_suffix& o)
{
	return get<1>(o);
}

inline
bool
has_long_long_suffix(const integer_suffix& o)
{
	return get<2>(o);
}

/*
integer_literal_no_suffix
	= decimal_literal
	| hexadecimal_literal
	| octal_literal
;
*/
typedef
	alternative_node
	<
		decimal_literal,
		hexadecimal_literal,
		octal_literal
	>
	integer_literal_no_suffix
;

/*
integer_literal
	= integer_literal_no_suffix >> !token_node_d[integer_suffix]
;
*/
typedef
	sequence_node
	<
		integer_literal_no_suffix,
		optional_node<integer_suffix>
	>
	integer_literal
;

inline
const integer_literal_no_suffix&
get_integer_literal_no_suffix(const integer_literal& o)
{
	return get<0>(o);
}

inline
const optional_node<integer_suffix>&
get_integer_suffix(const integer_literal& o)
{
	return get<1>(o);
}

}}} //namespace scalpel::cpp::syntax_nodes

#endif

