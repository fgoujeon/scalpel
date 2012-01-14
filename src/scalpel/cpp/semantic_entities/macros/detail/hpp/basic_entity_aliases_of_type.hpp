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

#define BASIC_ENTITY_ALIASES_OF_TYPE(TYPE, NAME, ENTITY_ALIAS_CLASS) \
	public: \
		typedef std::vector<ENTITY_ALIAS_CLASS<TYPE>> NAME##_aliases_t; \
 \
		typename utility::vector_range<ENTITY_ALIAS_CLASS<TYPE>>::type \
		NAME##_aliases() \
		{ \
			return NAME##_aliases_; \
		} \
 \
		const NAME##_aliases_t& \
		NAME##_aliases() const \
		{ \
			return NAME##_aliases_; \
		} \
 \
		void \
		add_member(const ENTITY_ALIAS_CLASS<TYPE>& member) \
		{ \
			NAME##_aliases_.push_back(member); \
		} \
 \
	private: \
		NAME##_aliases_t NAME##_aliases_;

