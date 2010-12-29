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

namespace scalpel { namespace cpp { namespace semantic_entities
{

namespace
{
	struct: public utility::static_visitor<unqualified_type_shared_ptr_variant>
	{
		template<class T>
		unqualified_type_shared_ptr_variant
		operator()(const std::shared_ptr<const T>& t) const
		{
			return get_unqualified_type(t->qualified_type());
		}

		unqualified_type_shared_ptr_variant
		operator()(const std::shared_ptr<const class_>& t) const
		{
			return t;
		}

		unqualified_type_shared_ptr_variant
		operator()(const std::shared_ptr<const fundamental_type>& t) const
		{
			return t;
		}
	} get_unqualified_type_visitor;
}

unqualified_type_shared_ptr_variant
get_unqualified_type(const type_shared_ptr_variant& type)
{
	return utility::apply_visitor(get_unqualified_type_visitor, type);
}



namespace
{
	//rhs' type is a qualifier
	template<class T>
	class complete_have_same_qualifiers_visitor: public utility::static_visitor<bool>
	{
		public:
			complete_have_same_qualifiers_visitor(const std::shared_ptr<const T>& rhs):
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

			//rhs' and lhs' types are identical
			bool
			operator()(const std::shared_ptr<const T>& lhs) const
			{
				//TODO check equality of current qualifiers (necessary for array)
				return have_same_qualifiers(lhs->qualified_type(), rhs_->qualified_type());
			}

		private:
			const std::shared_ptr<const T>& rhs_;
	};

	//rhs' type is class_
	template<>
	class complete_have_same_qualifiers_visitor<class_>: public utility::static_visitor<bool>
	{
		public:
			complete_have_same_qualifiers_visitor(const std::shared_ptr<const class_>& rhs):
				rhs_(rhs)
			{
			}

			//lhs' type is a qualifier
			template<class U>
			bool
			operator()(const std::shared_ptr<const U>&) const
			{
				return false;
			}

			//lhs' type is class_
			bool
			operator()(const std::shared_ptr<const class_>&) const
			{
				return true;
			}

			//lhs' type is fundamental_type
			bool
			operator()(const std::shared_ptr<const fundamental_type>&) const
			{
				return true;
			}

		private:
			const std::shared_ptr<const class_>& rhs_;
	};

	//rhs' type is fundamental_type
	template<>
	class complete_have_same_qualifiers_visitor<fundamental_type>: public utility::static_visitor<bool>
	{
		public:
			complete_have_same_qualifiers_visitor(const std::shared_ptr<const fundamental_type>& rhs):
				rhs_(rhs)
			{
			}

			//lhs' type is a qualifier
			template<class U>
			bool
			operator()(const std::shared_ptr<const U>&) const
			{
				return false;
			}

			//lhs' type is class_
			bool
			operator()(const std::shared_ptr<const class_>&) const
			{
				return true;
			}

			//lhs' type is fundamental_type
			bool
			operator()(const std::shared_ptr<const fundamental_type>&) const
			{
				return true;
			}

		private:
			const std::shared_ptr<const fundamental_type>& rhs_;
	};



	class partial_have_same_qualifiers_visitor: public utility::static_visitor<bool>
	{
		public:
			partial_have_same_qualifiers_visitor(const type_shared_ptr_variant& lhs):
				lhs_(lhs)
			{
			}

			template<class T>
			bool
			operator()(const std::shared_ptr<const T>& rhs) const
			{
				complete_have_same_qualifiers_visitor<T> visitor(rhs);
				return utility::apply_visitor(visitor, lhs_);
			}

		private:
			const type_shared_ptr_variant& lhs_;
	};
}

bool
have_same_qualifiers(const type_shared_ptr_variant& lhs, const type_shared_ptr_variant& rhs)
{
	partial_have_same_qualifiers_visitor visitor(lhs);
	return utility::apply_visitor(visitor, rhs);
}

}}} //namespace scalpel::cpp::semantic_entities

