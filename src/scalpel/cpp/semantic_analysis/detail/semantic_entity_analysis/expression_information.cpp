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

#include "expression_information.hpp"
#include <scalpel/cpp/semantic_entities/fundamental_type.hpp>

namespace scalpel { namespace cpp { namespace semantic_analysis { namespace detail { namespace semantic_entity_analysis
{

using namespace semantic_entities;

const expression_information::get_category_visitor_t expression_information::get_category_visitor;
const expression_information::is_bit_field_visitor_t expression_information::is_bit_field_visitor;

expression_information::type_category
expression_information::get_category_visitor_t::operator()(const semantic_entities::cv_qualified_type& type) const
{
	return apply_visitor(*this, type.qualified_type());
}

expression_information::type_category
expression_information::get_category_visitor_t::operator()(const semantic_entities::fundamental_type type) const
{
	switch(type)
	{
		case fundamental_type::BOOL:
			return type_category::BOOL;
		case fundamental_type::CHAR:
			return type_category::CHAR;
		case fundamental_type::WCHAR_T:
			return type_category::WCHAR_T;
		case fundamental_type::FLOAT:
			return type_category::FLOAT;
		case fundamental_type::DOUBLE:
			return type_category::DOUBLE;
		case fundamental_type::LONG_DOUBLE:
			return type_category::LONG_DOUBLE;
		case fundamental_type::INT:
			return type_category::INT;
		case fundamental_type::LONG_INT:
			return type_category::LONG_INT;
		case fundamental_type::LONG_LONG_INT:
			return type_category::LONG_LONG_INT;
		case fundamental_type::SHORT_INT:
			return type_category::SHORT_INT;
		case fundamental_type::SIGNED_CHAR:
			return type_category::SIGNED_CHAR;
		case fundamental_type::UNSIGNED_CHAR:
			return type_category::UNSIGNED_CHAR;
		case fundamental_type::UNSIGNED_INT:
			return type_category::UNSIGNED_INT;
		case fundamental_type::UNSIGNED_LONG_INT:
			return type_category::UNSIGNED_LONG_INT;
		case fundamental_type::UNSIGNED_LONG_LONG_INT:
			return type_category::UNSIGNED_LONG_LONG_INT;
		case fundamental_type::UNSIGNED_SHORT_INT:
			return type_category::UNSIGNED_SHORT_INT;
		default:
			assert(false);
	}
}

expression_information::expression_information(const expression_t& expr):
	type_category_(apply_visitor(get_category_visitor, get_type(expr))),
	is_bit_field_(apply_visitor(is_bit_field_visitor, expr))
{
}

}}}}} //namespace scalpel::cpp::semantic_analysis::detail::semantic_entity_analysis

