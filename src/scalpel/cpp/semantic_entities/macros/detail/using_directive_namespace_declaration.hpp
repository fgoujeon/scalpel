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

#define USING_DIRECTIVE_NAMESPACE_DECLARATION \
	public: \
		typedef std::vector<namespace_*> namespace_ptrs_t; \
 \
		const namespace_ptrs_t& \
		using_directive_namespaces() const \
		{ \
			return using_directive_namespaces_; \
		} \
 \
		void \
		add_using_directive_namespace(namespace_& n) \
		{ \
			using_directive_namespaces_.push_back(&n); \
		} \
 \
	private: \
		namespace_ptrs_t using_directive_namespaces_;

