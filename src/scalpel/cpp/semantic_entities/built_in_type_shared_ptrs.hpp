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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_BUILT_IN_TYPE_SHARED_PTRS_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_BUILT_IN_TYPE_SHARED_PTRS_HPP

#include "built_in_type.hpp"
#include <memory>

namespace scalpel { namespace cpp { namespace semantic_entities
{

namespace built_in_type_shared_ptrs
{
	extern std::shared_ptr<const built_in_type> bool_;
	extern std::shared_ptr<const built_in_type> char_;
	extern std::shared_ptr<const built_in_type> double_;
	extern std::shared_ptr<const built_in_type> float_;
	extern std::shared_ptr<const built_in_type> int_;
	extern std::shared_ptr<const built_in_type> long_double;
	extern std::shared_ptr<const built_in_type> long_int;
	extern std::shared_ptr<const built_in_type> long_long_int;
	extern std::shared_ptr<const built_in_type> short_int;
	extern std::shared_ptr<const built_in_type> unsigned_char;
	extern std::shared_ptr<const built_in_type> unsigned_int;
	extern std::shared_ptr<const built_in_type> unsigned_long_int;
	extern std::shared_ptr<const built_in_type> unsigned_long_long_int;
	extern std::shared_ptr<const built_in_type> unsigned_short_int;
	extern std::shared_ptr<const built_in_type> void_;
	extern std::shared_ptr<const built_in_type> wchar_t_;
}

}}} //namespace scalpel::cpp::semantic_entities

#endif

