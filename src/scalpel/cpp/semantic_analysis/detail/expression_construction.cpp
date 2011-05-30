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

#include "value_construction.hpp"
#include "expression_construction.hpp"
#include <iostream>

namespace scalpel { namespace cpp { namespace semantic_analysis { namespace detail
{

using namespace syntax_nodes;
using namespace semantic_entities;

namespace
{
	struct: public utility::static_visitor<void>
	{
		void
		operator()(const int i)
		{
			std::cout << "type = int, value = " << i << std::endl;
		}

		void
		operator()(const unsigned int i)
		{
			std::cout << "type = unsigned int, value = " << i << std::endl;
		}

		void
		operator()(const unsigned long int i)
		{
			std::cout << "type = unsigned long int, value = " << i << std::endl;
		}

		void
		operator()(const unsigned long long int i)
		{
			std::cout << "type = unsigned long long int, value = " << i << std::endl;
		}

		void
		operator()(const long int i)
		{
			std::cout << "type = long int, value = " << i << std::endl;
		}

		void
		operator()(const long long int i)
		{
			std::cout << "type = long long int, value = " << i << std::endl;
		}
	} print_visitor;
}

void
create_expression(const syntax_nodes::literal& literal_node)
{
	if(const boost::optional<const integer_literal&>& opt_integer_literal_node = get<integer_literal>(&literal_node))
	{
		integer_value_t integer_value = create_value(*opt_integer_literal_node);
		apply_visitor(print_visitor, integer_value);
	}
	else
	{
		assert(false); //TODO
	}

	/*
	boolean_literal
	character_literal
	string_literal
	floating_literal
	integer_literal
	*/
}

}}}} //namespace scalpel::cpp::semantic_analysis::detail

