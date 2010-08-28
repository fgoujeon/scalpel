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

#ifndef SCALPEL_UTILITY_ARE_POINTED_OBJECTS_EQUAL_HPP
#define SCALPEL_UTILITY_ARE_POINTED_OBJECTS_EQUAL_HPP

namespace scalpel { namespace utility
{

/**
 * Test contained pointed objects for equality.
 */
template<typename PointerT, template<typename> class ContainerT>
bool
are_pointed_objects_equal
(
	const ContainerT<PointerT>& lhs,
	const ContainerT<PointerT>& rhs
)
{
	if(lhs.size() == rhs.size())
	{
		for(unsigned int i = 0; i < lhs.size(); ++i)
		{
			if(*lhs[i] != *rhs[i])
				return false;
		}

		return true;
	}
	else
	{
		return false;
	}
}



//
//overload for variant
//

namespace are_pointed_objects_equal_impl
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

	template<class VariantT>
	class partial_equals_visitor: public utility::static_visitor<bool>
	{
		public:
			partial_equals_visitor(const VariantT& lhs):
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
			const VariantT& lhs_;
	};
}

/**
 * Test contained pointed objects for equality
 */
template<class VariantT>
bool
are_pointed_objects_equal(const VariantT& lhs, const VariantT& rhs)
{
	are_pointed_objects_equal_impl::partial_equals_visitor<VariantT> equals_visitor_1(lhs);
	return utility::apply_visitor(equals_visitor_1, rhs);
}

}} //namespace scalpel::utility

#endif

