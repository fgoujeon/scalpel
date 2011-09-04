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

#ifndef SCALPEL_CPP_SEMANTIC_ANALYSIS_DETAIL_MEMBER_ACCESS_EXPRESSION_CONSTRUCTION_HPP
#define SCALPEL_CPP_SEMANTIC_ANALYSIS_DETAIL_MEMBER_ACCESS_EXPRESSION_CONSTRUCTION_HPP

#include <scalpel/cpp/semantic_graph.hpp>
#include <scalpel/utility/variant.hpp>

namespace scalpel { namespace cpp { namespace semantic_analysis { namespace detail
{

class create_member_access_expression_visitor: public utility::static_visitor<semantic_entities::expression_t>
{
	public:
		create_member_access_expression_visitor(const semantic_entities::expression_t& object):
			object_(object)
		{
		}

		template<class Member>
		semantic_entities::expression_t
		operator()(Member* const member)
		{
			return semantic_entities::member_access_expression<Member>
			(
				object_,
				*member
			);
		}

	private:
		semantic_entities::expression_t object_;
};

template<class MemberVariant>
semantic_entities::expression_t
create_member_access_expression
(
	const semantic_entities::expression_t& object,
	const MemberVariant& member
)
{
	create_member_access_expression_visitor visitor(object);
	return apply_visitor(visitor, member);
}

}}}} //namespace scalpel::cpp::semantic_analysis::detail

#endif

