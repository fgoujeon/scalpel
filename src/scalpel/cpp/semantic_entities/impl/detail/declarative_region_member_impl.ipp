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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_IMPL_DETAIL_DECLARATIVE_REGION_MEMBER_IMPL_IPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_IMPL_DETAIL_DECLARATIVE_REGION_MEMBER_IMPL_IPP

namespace scalpel { namespace cpp { namespace semantic_entities { namespace impl { namespace detail
{

template<class DeclarativeRegion1, class DeclarativeRegion2, class... DeclarativeRegions>
typename declarative_region_member_impl<DeclarativeRegion1, DeclarativeRegion2, DeclarativeRegions...>::declarative_region_t
declarative_region_member_impl<DeclarativeRegion1, DeclarativeRegion2, DeclarativeRegions...>::enclosing_declarative_region()
{
	if(enclosing_declarative_region_)
		return *enclosing_declarative_region_;
	else
		throw std::runtime_error("The declarative region is not set.");
}

template<class DeclarativeRegion1, class DeclarativeRegion2, class... DeclarativeRegions>
typename declarative_region_member_impl<DeclarativeRegion1, DeclarativeRegion2, DeclarativeRegions...>::const_declarative_region_t
declarative_region_member_impl<DeclarativeRegion1, DeclarativeRegion2, DeclarativeRegions...>::enclosing_declarative_region() const
{
	if(const_enclosing_declarative_region_)
		return *const_enclosing_declarative_region_;
	else
		throw std::runtime_error("The declarative region is not set.");
}

template<class DeclarativeRegion1, class DeclarativeRegion2, class... DeclarativeRegions>
void
declarative_region_member_impl<DeclarativeRegion1, DeclarativeRegion2, DeclarativeRegions...>::enclosing_declarative_region
(
	input_declarative_region_t enclosing_declarative_region
)
{
	if(!enclosing_declarative_region_)
	{
		enclosing_declarative_region_ = enclosing_declarative_region;
		const_enclosing_declarative_region_ = utility::apply_visitor(to_const_variant_visitor, enclosing_declarative_region);
	}
	else
		throw std::runtime_error("The declarative region is already set.");
}



template<class DeclarativeRegion>
declarative_region_member_impl<DeclarativeRegion>::declarative_region_member_impl():
	enclosing_declarative_region_(0)
{
}

template<class DeclarativeRegion>
typename declarative_region_member_impl<DeclarativeRegion>::declarative_region_t
declarative_region_member_impl<DeclarativeRegion>::enclosing_declarative_region()
{
	if(enclosing_declarative_region_)
		return *enclosing_declarative_region_;
	else
		throw std::runtime_error("The declarative region is not set.");
}

template<class DeclarativeRegion>
typename declarative_region_member_impl<DeclarativeRegion>::const_declarative_region_t
declarative_region_member_impl<DeclarativeRegion>::enclosing_declarative_region() const
{
	if(enclosing_declarative_region_)
		return *enclosing_declarative_region_;
	else
		throw std::runtime_error("The declarative region is not set.");
}

template<class DeclarativeRegion>
void
declarative_region_member_impl<DeclarativeRegion>::enclosing_declarative_region(input_declarative_region_t enclosing_declarative_region)
{
	if(!enclosing_declarative_region_)
		enclosing_declarative_region_ = &enclosing_declarative_region;
	else
		throw std::runtime_error("The declarative region is already set.");
}

}}}}} //namespace scalpel::cpp::semantic_entities::impl::detail

#endif

