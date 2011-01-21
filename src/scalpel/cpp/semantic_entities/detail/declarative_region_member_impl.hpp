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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_DETAIL_DECLARATIVE_REGION_MEMBER_IMPL_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_DETAIL_DECLARATIVE_REGION_MEMBER_IMPL_HPP

#include "../declarative_region_variants.hpp"
#include <boost/optional.hpp>

namespace scalpel { namespace cpp { namespace semantic_entities { namespace detail
{

class declarative_region_member_impl
{
    public:
		bool
		has_enclosing_declarative_region() const;

		declarative_region_ptr_variant
		enclosing_declarative_region() const;

		void
		enclosing_declarative_region(const declarative_region_ptr_variant& enclosing_declarative_region);

    private:
		boost::optional<declarative_region_ptr_variant> enclosing_declarative_region_;
};

}}}} //namespace scalpel::cpp::semantic_entities::detail

#endif

