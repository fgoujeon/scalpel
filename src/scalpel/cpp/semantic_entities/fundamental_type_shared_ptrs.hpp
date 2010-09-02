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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_FUNDAMENTAL_TYPE_SHARED_PTRS_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_FUNDAMENTAL_TYPE_SHARED_PTRS_HPP

#include "fundamental_type.hpp"
#include <memory>

namespace scalpel { namespace cpp { namespace semantic_entities
{

//fundamental_type objects are allocated on the stack and exist in one const
//instance each. Now, the library uses almost exclusively heap allocated
//objects, which are pointed to by std::shared_ptr objects.
//
//Each of the following types is a std::shared_ptr object that points to one of
//the fundamental_type objects. Since they point to stack allocated objects, they
//logically use a null deleter.
namespace fundamental_type_shared_ptrs
{
	extern std::shared_ptr<const fundamental_type> bool_;
	extern std::shared_ptr<const fundamental_type> char_;
	extern std::shared_ptr<const fundamental_type> double_;
	extern std::shared_ptr<const fundamental_type> float_;
	extern std::shared_ptr<const fundamental_type> int_;
	extern std::shared_ptr<const fundamental_type> long_double;
	extern std::shared_ptr<const fundamental_type> long_int;
	extern std::shared_ptr<const fundamental_type> long_long_int;
	extern std::shared_ptr<const fundamental_type> short_int;
	extern std::shared_ptr<const fundamental_type> unsigned_char;
	extern std::shared_ptr<const fundamental_type> unsigned_int;
	extern std::shared_ptr<const fundamental_type> unsigned_long_int;
	extern std::shared_ptr<const fundamental_type> unsigned_long_long_int;
	extern std::shared_ptr<const fundamental_type> unsigned_short_int;
	extern std::shared_ptr<const fundamental_type> void_;
	extern std::shared_ptr<const fundamental_type> wchar_t_;
}

}}} //namespace scalpel::cpp::semantic_entities

#endif

