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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_IMPL_DETAIL_DECLARATIVE_REGION_MEMBER_IMPL_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_IMPL_DETAIL_DECLARATIVE_REGION_MEMBER_IMPL_HPP

#include <scalpel/utility/ptr_variant.hpp>
#include <scalpel/utility/const_ptr_variant.hpp>
#include <boost/optional.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/seq.hpp>
#include <boost/preprocessor/punctuation/comma.hpp>

namespace scalpel { namespace cpp { namespace semantic_entities { namespace impl { namespace detail
{

template<class... DeclarativeRegions>
class declarative_region_member_impl;

template<class DeclarativeRegion1, class DeclarativeRegion2, class... DeclarativeRegions>
class declarative_region_member_impl<DeclarativeRegion1, DeclarativeRegion2, DeclarativeRegions...>
{
    private:
		typedef
			typename utility::ptr_variant<DeclarativeRegion1, DeclarativeRegion2, DeclarativeRegions...>::type
			basic_declarative_region_t
		;
		typedef
			typename utility::const_ptr_variant<DeclarativeRegion1, DeclarativeRegion2, DeclarativeRegions...>::type
			basic_const_declarative_region_t
		;

		struct: public utility::static_visitor<basic_const_declarative_region_t>
		{
			template<class T>
			basic_const_declarative_region_t
			operator()(const T* t)
			{
				return t;
			}
		} to_const_variant_visitor;

    public:
		typedef
			const basic_declarative_region_t&
			declarative_region_t
		;
		typedef
			const basic_const_declarative_region_t&
			const_declarative_region_t
		;
		typedef
			const basic_declarative_region_t&
			input_declarative_region_t
		;

		bool
		has_enclosing_declarative_region() const
		{
			return enclosing_declarative_region_;
		}

		declarative_region_t
		enclosing_declarative_region();

		const_declarative_region_t
		enclosing_declarative_region() const;

		void
		enclosing_declarative_region(input_declarative_region_t enclosing_declarative_region);

    private:
		boost::optional<basic_declarative_region_t> enclosing_declarative_region_;
		boost::optional<basic_const_declarative_region_t> const_enclosing_declarative_region_;
};

template<class DeclarativeRegion>
class declarative_region_member_impl<DeclarativeRegion>
{
    public:
		typedef
			DeclarativeRegion&
			declarative_region_t
		;
		typedef
			const DeclarativeRegion&
			const_declarative_region_t
		;
		typedef
			DeclarativeRegion&
			input_declarative_region_t
		;

		declarative_region_member_impl();

		bool
		has_enclosing_declarative_region() const
		{
			return enclosing_declarative_region_;
		}

		declarative_region_t
		enclosing_declarative_region();

		const_declarative_region_t
		enclosing_declarative_region() const;

		void
		enclosing_declarative_region(input_declarative_region_t enclosing_declarative_region);

    private:
		DeclarativeRegion* enclosing_declarative_region_;
};

}}}}} //namespace scalpel::cpp::semantic_entities::impl::detail

#include "declarative_region_member_impl.ipp"

#endif

