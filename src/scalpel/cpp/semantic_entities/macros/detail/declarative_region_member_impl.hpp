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

#define DECLARATIVE_REGION_MEMBER_IMPL(IMPL) \
private: \
	typedef IMPL declarative_region_member_impl_t; \
 \
public: \
	typedef declarative_region_member_impl_t::declarative_region_t enclosing_declarative_region_t; \
	typedef declarative_region_member_impl_t::const_declarative_region_t const_enclosing_declarative_region_t; \
 \
	bool \
	has_enclosing_declarative_region() const \
	{ \
		return declarative_region_member_impl_.has_enclosing_declarative_region(); \
	} \
 \
	declarative_region_member_impl_t::declarative_region_t \
	enclosing_declarative_region() \
	{ \
		return declarative_region_member_impl_.enclosing_declarative_region(); \
	} \
 \
	declarative_region_member_impl_t::const_declarative_region_t \
	enclosing_declarative_region() const \
	{ \
		return declarative_region_member_impl_.enclosing_declarative_region(); \
	} \
 \
	void \
	enclosing_declarative_region(declarative_region_member_impl_t::input_declarative_region_t enclosing_declarative_region) \
	{ \
		declarative_region_member_impl_.enclosing_declarative_region(enclosing_declarative_region); \
	} \
 \
private: \
	declarative_region_member_impl_t declarative_region_member_impl_;

