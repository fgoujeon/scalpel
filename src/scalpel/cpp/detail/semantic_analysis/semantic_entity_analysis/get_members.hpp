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

#ifndef SCALPEL_CPP_DETAIL_SEMANTIC_ANALYSIS_SEMANTIC_ENTITY_ANALYSIS_GET_MEMBERS_HPP
#define SCALPEL_CPP_DETAIL_SEMANTIC_ANALYSIS_SEMANTIC_ENTITY_ANALYSIS_GET_MEMBERS_HPP

#include <scalpel/cpp/semantic_graph.hpp>
#include <scalpel/utility/single_object_range.hpp>
#include <scalpel/utility/shared_ptr_vector.hpp>

namespace scalpel { namespace cpp { namespace detail { namespace semantic_analysis { namespace semantic_entity_analysis
{

template<class EntityT>
struct get_members_type_traits;

template<>
struct get_members_type_traits<semantic_entities::open_declarative_region_shared_ptr_variant>
{
	typedef std::vector<semantic_entities::open_declarative_region_shared_ptr_variant> return_type;
};

template<>
struct get_members_type_traits<semantic_entities::namespace_alias>
{
	typedef utility::shared_ptr_vector<semantic_entities::namespace_alias>::range return_type;
};

template<>
struct get_members_type_traits<semantic_entities::namespace_>
{
	typedef utility::shared_ptr_vector<semantic_entities::namespace_>::range return_type;
};

template<>
struct get_members_type_traits<semantic_entities::class_>
{
	typedef utility::shared_ptr_vector<semantic_entities::class_>::range return_type;
};

template<>
struct get_members_type_traits<semantic_entities::typedef_>
{
	typedef utility::shared_ptr_vector<semantic_entities::typedef_>::range return_type;
};

template<>
struct get_members_type_traits<semantic_entities::constructor>
{
	typedef utility::shared_ptr_vector<semantic_entities::constructor>::range return_type;
};

template<>
struct get_members_type_traits<semantic_entities::destructor>
{
	typedef utility::single_object_range<std::shared_ptr<semantic_entities::destructor>> return_type;
};

template<>
struct get_members_type_traits<semantic_entities::operator_function>
{
	typedef utility::shared_ptr_vector<semantic_entities::operator_function>::range return_type;
};

template<>
struct get_members_type_traits<semantic_entities::conversion_function>
{
	typedef utility::shared_ptr_vector<semantic_entities::conversion_function>::range return_type;
};

template<>
struct get_members_type_traits<semantic_entities::simple_function>
{
	typedef utility::shared_ptr_vector<semantic_entities::simple_function>::range return_type;
};

template<>
struct get_members_type_traits<semantic_entities::statement_block>
{
	typedef utility::shared_ptr_vector<semantic_entities::statement_block>::range return_type;
};

template<>
struct get_members_type_traits<semantic_entities::variable>
{
	typedef utility::shared_ptr_vector<semantic_entities::variable>::range return_type;
};



template<class MemberT, class ParentT>
typename get_members_type_traits<MemberT>::return_type
get_members(ParentT parent);

}}}}} //namespace scalpel::cpp::detail::semantic_analysis::semantic_entity_analysis

#endif

