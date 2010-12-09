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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_DETAIL_CLASS_MEMBER_IMPL_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_DETAIL_CLASS_MEMBER_IMPL_HPP

#include "../declarative_region_variants.hpp"
#include <memory>

namespace scalpel { namespace cpp { namespace semantic_entities
{

class class_;

namespace detail
{

class class_member_impl
{
    public:
		bool
		has_enclosing_declarative_region() const;

		std::shared_ptr<class_>
		enclosing_class() const;

		declarative_region_shared_ptr_variant
		enclosing_declarative_region() const;

		void
		enclosing_declarative_region(const std::shared_ptr<class_>& enclosing_declarative_region);

    private:
		std::weak_ptr<class_> enclosing_declarative_region_;
};

}}}} //namespace scalpel::cpp::semantic_entities::detail

#endif

