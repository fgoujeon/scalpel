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

#include "type_variants.hpp"
#include "array.hpp"
#include "built_in_type.hpp"
#include "class_.hpp"
#include "const_.hpp"
#include "pointer.hpp"
#include "reference.hpp"
#include "volatile_.hpp"

namespace scalpel { namespace cpp { namespace semantic_entities
{

template<class T>
class complete_equals_visitor: public utility::static_visitor<bool>
{
	public:
		complete_equals_visitor(const std::shared_ptr<const T>& rhs):
			rhs_(rhs)
		{
		}

		//rhs' and lhs' types are different
		template<class U>
		bool
		operator()(const std::shared_ptr<const U>&) const
		{
			return false;
		}

		bool
		operator()(const std::shared_ptr<const T>& lhs) const
		{
			const T& lhs_ref = *lhs;
			const T& rhs_ref = *rhs_;
			return lhs_ref == rhs_ref;
		}

	private:
		const std::shared_ptr<const T>& rhs_;
};

class partial_equals_visitor: public utility::static_visitor<bool>
{
	public:
		partial_equals_visitor(const type_shared_ptr_variant& lhs):
			lhs_(lhs)
		{
		}

		template<class T>
		bool
		operator()(const std::shared_ptr<const T>& rhs) const
		{
			complete_equals_visitor<T> equals_visitor_1(rhs);
			return utility::apply_visitor(equals_visitor_1, lhs_);
		}

	private:
		const type_shared_ptr_variant& lhs_;
};

bool
equals(const type_shared_ptr_variant& lhs, const type_shared_ptr_variant& rhs)
{
	partial_equals_visitor equals_visitor_1(lhs);
	return utility::apply_visitor(equals_visitor_1, rhs);
}

/*
/home/florian/Development/Scalpel/src/scalpel/cpp/semantic_entities/type_variants.cpp|46 col 20| error: no match for ‘operator==’ in ‘

((const std::shared_ptr<const scalpel::cpp::semantic_entities::built_in_type>*)lhs)->std::shared_ptr<const scalpel::cpp::semantic_entities::built_in_type>::<anonymous>.std::__shared_ptr<_Tp, _Lp>::operator* [with _Tp = const scalpel::cpp::semantic_entities::built_in_type, __gnu_cxx::_Lock_policy _Lp = (__gnu_cxx::_Lock_policy)2u, typename std::add_lvalue_reference<_Tp>::type = const scalpel::cpp::semantic_entities::built_in_type&]() == ((const std::shared_ptr<const scalpel::cpp::semantic_entities::built_in_type>*)((const scalpel::cpp::semantic_entities::equals_visitor_a<scalpel::cpp::semantic_entities::built_in_type>*)this)->scalpel::cpp::semantic_entities::equals_visitor_a<scalpel::cpp::semantic_entities::built_in_type>::rhs_)->std::shared_ptr<const scalpel::cpp::semantic_entities::built_in_type>::<anonymous>.std::__shared_ptr<_Tp, _Lp>::operator* [with _Tp = const scalp
|| l::cpp::semantic_entities::built_in_type, __gnu_cxx::_Lock_policy _Lp = (__gnu_cxx::_Lock_policy)2u, typename std::add_lvalue_reference<_Tp>::type = const scalpel::cpp::semantic_entities::built_in_type&]()’
*/

}}} //namespace scalpel::cpp::semantic_entities

