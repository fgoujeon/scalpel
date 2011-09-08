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

#ifndef SCALPEL_CPP_SEMANTIC_ANALYSIS_DETAIL_SEMANTIC_ENTITY_ANALYSIS_GET_MEMBERS_IPP
#define SCALPEL_CPP_SEMANTIC_ANALYSIS_DETAIL_SEMANTIC_ENTITY_ANALYSIS_GET_MEMBERS_IPP

namespace scalpel { namespace cpp { namespace semantic_entities { namespace generic_queries { namespace detail
{

template<typename UnderlyingType>
class empty_constant_list
{
	private:
		static std::vector<std::unique_ptr<enum_constant<UnderlyingType>>> list;

	public:
		static typename utility::unique_ptr_vector_range<enum_constant<UnderlyingType>>::type range;
		static typename utility::unique_ptr_vector_const_range<enum_constant<UnderlyingType>>::type const_range;
};

template<typename UnderlyingType>
std::vector<std::unique_ptr<enum_constant<UnderlyingType>>>
empty_constant_list<UnderlyingType>::list;

template<typename UnderlyingType>
typename utility::unique_ptr_vector_range<enum_constant<UnderlyingType>>::type
empty_constant_list<UnderlyingType>::range(utility::make_unique_ptr_vector_range(list));

template<typename UnderlyingType>
typename utility::unique_ptr_vector_const_range<enum_constant<UnderlyingType>>::type
empty_constant_list<UnderlyingType>::const_range(utility::make_unique_ptr_vector_const_range(list));



template<typename UnderlyingType>
struct get_enum_constant_visitor: utility::static_visitor<typename utility::unique_ptr_vector_range<enum_constant<UnderlyingType>>::type>
{
	typename utility::unique_ptr_vector_range<enum_constant<UnderlyingType>>::type
	operator()(enum_constant_list<UnderlyingType>& list) const
	{
		return list.constants();
	}

	template<typename DifferentUnderlyingType>
	typename utility::unique_ptr_vector_range<enum_constant<UnderlyingType>>::type
	operator()(enum_constant_list<DifferentUnderlyingType>&) const
	{
		return empty_constant_list<UnderlyingType>::range;
	}
};

template<typename UnderlyingType>
struct get_const_enum_constant_visitor: utility::static_visitor<typename utility::unique_ptr_vector_const_range<enum_constant<UnderlyingType>>::type>
{
	typename utility::unique_ptr_vector_const_range<enum_constant<UnderlyingType>>::type
	operator()(const enum_constant_list<UnderlyingType>& list) const
	{
		return list.constants();
	}

	template<typename DifferentUnderlyingType>
	typename utility::unique_ptr_vector_const_range<enum_constant<UnderlyingType>>::type
	operator()(const enum_constant_list<DifferentUnderlyingType>&) const
	{
		return empty_constant_list<UnderlyingType>::const_range;
	}
};

template<class Enum, class Member>
struct get_enum_members_impl;

template<class Enum, typename UnderlyingType>
struct get_enum_members_impl<Enum, enum_constant<UnderlyingType>>
{
	static
	typename get_members_return_type<Enum, enum_constant<UnderlyingType>, false>::type
	get(Enum& parent)
	{
		get_enum_constant_visitor<UnderlyingType> visitor;
		return apply_visitor(visitor, parent.constants());
	}

	static
	typename get_members_return_type<Enum, enum_constant<UnderlyingType>, true>::type
	get(const Enum& parent)
	{
		get_const_enum_constant_visitor<UnderlyingType> visitor;
		return apply_visitor(visitor, parent.constants());
	}
};

template<class Member>
typename get_members_return_type<enum_, Member, false>::type
get_members(semantic_entities::enum_& parent)
{
	return get_enum_members_impl<enum_, Member>::get(parent);
}

template<class Member>
typename get_members_return_type<enum_, Member, true>::type
get_members(const semantic_entities::enum_& parent)
{
	return get_enum_members_impl<enum_, Member>::get(parent);
}

template<class Member>
typename get_members_return_type<member_enum, Member, false>::type
get_members(semantic_entities::member_enum& parent)
{
	return get_enum_members_impl<member_enum, Member>::get(parent);
}

template<class Member>
typename get_members_return_type<member_enum, Member, true>::type
get_members(const semantic_entities::member_enum& parent)
{
	return get_enum_members_impl<member_enum, Member>::get(parent);
}

}}}}} //namespace scalpel::cpp::semantic_entities::generic_queries::detail

#endif

