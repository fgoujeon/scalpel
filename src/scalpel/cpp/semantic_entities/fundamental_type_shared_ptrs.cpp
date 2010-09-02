/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2010  Florian Goujeon

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

#include "fundamental_type_shared_ptrs.hpp"
#include <scalpel/utility/null_deleter.hpp>

namespace scalpel { namespace cpp { namespace semantic_entities
{

namespace fundamental_type_shared_ptrs
{
	std::shared_ptr<const fundamental_type> bool_(&fundamental_type::bool_, utility::null_deleter());
	std::shared_ptr<const fundamental_type> char_(&fundamental_type::char_, utility::null_deleter());
	std::shared_ptr<const fundamental_type> double_(&fundamental_type::double_, utility::null_deleter());
	std::shared_ptr<const fundamental_type> float_(&fundamental_type::float_, utility::null_deleter());
	std::shared_ptr<const fundamental_type> int_(&fundamental_type::int_, utility::null_deleter());
	std::shared_ptr<const fundamental_type> long_double(&fundamental_type::long_double, utility::null_deleter());
	std::shared_ptr<const fundamental_type> long_int(&fundamental_type::long_int, utility::null_deleter());
	std::shared_ptr<const fundamental_type> long_long_int(&fundamental_type::long_long_int, utility::null_deleter());
	std::shared_ptr<const fundamental_type> short_int(&fundamental_type::short_int, utility::null_deleter());
	std::shared_ptr<const fundamental_type> unsigned_char(&fundamental_type::unsigned_char, utility::null_deleter());
	std::shared_ptr<const fundamental_type> unsigned_int(&fundamental_type::unsigned_int, utility::null_deleter());
	std::shared_ptr<const fundamental_type> unsigned_long_int(&fundamental_type::unsigned_long_int, utility::null_deleter());
	std::shared_ptr<const fundamental_type> unsigned_long_long_int(&fundamental_type::unsigned_long_long_int, utility::null_deleter());
	std::shared_ptr<const fundamental_type> unsigned_short_int(&fundamental_type::unsigned_short_int, utility::null_deleter());
	std::shared_ptr<const fundamental_type> void_(&fundamental_type::void_, utility::null_deleter());
	std::shared_ptr<const fundamental_type> wchar_t_(&fundamental_type::wchar_t_, utility::null_deleter());
}

}}} //namespace scalpel::cpp::semantic_entities

