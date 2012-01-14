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

#define MEMBER_DEFINITION(CLASS_NAME, TYPE, NAME, SET_ENCLOSING_DECLARATIVE_REGION) \
utility::unique_ptr_vector_range<TYPE>::type \
CLASS_NAME::NAME() \
{ \
	return utility::make_unique_ptr_vector_range(NAME##_); \
} \
 \
utility::unique_ptr_vector_const_range<TYPE>::type \
CLASS_NAME::NAME() const \
{ \
	return utility::make_unique_ptr_vector_const_range(NAME##_); \
} \
 \
void \
CLASS_NAME::add_member(std::unique_ptr<TYPE>&& member) \
{ \
	BOOST_PP_IIF(SET_ENCLOSING_DECLARATIVE_REGION, generic_queries::detail::set_enclosing_declarative_region(*member, this);,) \
    NAME##_.push_back(std::move(member)); \
}

