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

#include <boost/preprocessor/control/iif.hpp>

#define SINGLE_MEMBER_DECLARATION(TYPE, NAME, OPTIONAL) \
	public: \
		TYPE BOOST_PP_IIF(OPTIONAL, *, &) \
		get_##NAME() \
		{ \
			BOOST_PP_IIF \
			( \
				OPTIONAL, \
				return NAME##_.get();, \
				return *NAME##_; \
			) \
		} \
 \
		const TYPE BOOST_PP_IIF(OPTIONAL, *, &) \
		get_##NAME() const \
		{ \
			BOOST_PP_IIF \
			( \
				OPTIONAL, \
				return NAME##_.get();, \
				return *NAME##_; \
			) \
		} \
 \
		void \
		set_##NAME(std::unique_ptr<TYPE>&& member); \
 \
	private: \
		std::unique_ptr<TYPE> NAME##_;

