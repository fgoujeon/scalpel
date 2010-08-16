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

#ifndef SCALPEL_UTILITY_VARIANT_HPP
#define SCALPEL_UTILITY_VARIANT_HPP

#include <boost/optional.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/utility/enable_if.hpp>

namespace scalpel { namespace utility
{

template<typename... Ts>
class variant;

template<>
class variant<>
{
	public:
		typedef void head_t;
		typedef void tail_t;

		bool
		empty() const
		{
			return true;
		}
};

template<typename T, typename... Ts>
class variant<T, Ts...>
{
	public:
		typedef T head_t;
		typedef variant<Ts...> tail_t;

		/**
		 * Default constructor which does nothing (useful for internal use).
		 */
		variant();

		/**
		 * Constructor.
		 */
		variant(const T& o);

		/**
		 * Constructor.
		 */
		variant(T& o);

		/**
		 * Constructor.
		 */
		variant(T&& o);

		/**
		 * Constructor.
		 */
		template<typename T2>
		variant
		(
			const T2& o,
			typename boost::disable_if
			<
				boost::is_same
				<
					typename boost::remove_const<T2>::type,
					variant
				>
			>::type* = 0 //avoid conflict with copy and move constructors
		);

		/**
		 * Constructor.
		 */
		template<typename T2>
		variant
		(
			T2&& o,
			typename boost::disable_if
			<
				boost::is_same
				<
					typename boost::remove_const<T2>::type,
					variant
				>
			>::type* = 0 //avoid conflict with copy and move constructors
		);

		/**
		 * Copy constructor.
		 */
		variant(const variant& o);

		/**
		 * Copy constructor.
		 */
		variant(variant& o);

		/**
		 * Move constructor.
		 */
		variant(variant&& o);

		const variant&
		operator=(const variant& o);

		inline
		bool
		empty() const;

		const tail_t&
		tail() const;

		//same type
		void
		get(boost::optional<const T&>&) const;

		//different types
		template<typename T2>
		void
		get(boost::optional<const T2&>&) const;

		//same type
		void
		set(const T&);

		//different types
		template<typename T2>
		void
		set(const T2&);

	private:
		boost::optional<head_t> head_;
		tail_t tail_;
};

template<typename T, typename... Ts>
variant<T, Ts...>::variant()
{
	//does nothing
}

template<typename T, typename... Ts>
variant<T, Ts...>::variant(const T& o):
	head_(o)
{
}

template<typename T, typename... Ts>
variant<T, Ts...>::variant(T& o):
	head_(o)
{
}

template<typename T, typename... Ts>
variant<T, Ts...>::variant(T&& o):
	head_(std::move(o))
{
}

template<typename T, typename... Ts>
template<typename T2>
variant<T, Ts...>::variant
(
	const T2& o,
	typename boost::disable_if
	<
		boost::is_same
		<
			typename boost::remove_const<T2>::type,
			variant
		>
	>::type*
):
	tail_(o)
{
}

template<typename T, typename... Ts>
template<typename T2>
variant<T, Ts...>::variant
(
	T2&& o,
	typename boost::disable_if
	<
		boost::is_same
		<
			typename boost::remove_const<T2>::type,
			variant
		>
	>::type*
):
	tail_(std::move(o))
{
}

template<typename T, typename... Ts>
variant<T, Ts...>::variant(const variant<T, Ts...>& o):
	head_(o.head_),
	tail_(o.tail_)
{
}

template<typename T, typename... Ts>
variant<T, Ts...>::variant(variant<T, Ts...>& o):
	head_(o.head_),
	tail_(o.tail_)
{
}

template<typename T, typename... Ts>
variant<T, Ts...>::variant(variant<T, Ts...>&& o):
	head_(std::move(o.head_)),
	tail_(std::move(o.tail_))
{
}

template<typename T, typename... Ts>
const variant<T, Ts...>&
variant<T, Ts...>::operator=(const variant<T, Ts...>& o)
{
	head_ = o.head_;
	tail_ = o.tail_;
	return *this;
}

template<typename T, typename... Ts>
bool
variant<T, Ts...>::empty() const
{
	return !head_ && tail_.empty();
}

template<typename T, typename... Ts>
const typename variant<T, Ts...>::tail_t&
variant<T, Ts...>::tail() const
{
	return tail_;
}

template<typename T, typename... Ts>
void
variant<T, Ts...>::get(boost::optional<const T&>& object) const
{
	object = head_;
}

template<typename T, typename... Ts>
template<typename T2>
void
variant<T, Ts...>::get(boost::optional<const T2&>& object) const
{
	tail_.get(object);
}

template<typename T, typename... Ts>
void
variant<T, Ts...>::set(const T& object)
{
	head_ = object;
}

template<typename T, typename... Ts>
template<typename T2>
void
variant<T, Ts...>::set(const T2& object)
{
	tail_.set(object);
}



template<class ReturnT, class VariantT>
boost::optional<const ReturnT&>
get(const VariantT* var)
{
	boost::optional<const ReturnT&> return_object;
	var->get(return_object);
	return return_object;
}



template<class VariantVisitorT, class FullVariantT, class CurrentVariantT, typename HeadT>
struct private_visitor
{
	typedef typename CurrentVariantT::head_t head_t;
	typedef typename CurrentVariantT::tail_t tail_t;

	static
	void
	visit(const VariantVisitorT& variant_visitor, const FullVariantT& var)
	{
		boost::optional<const head_t&> opt_object = get<head_t>(&var);
		if(opt_object)
		{
			variant_visitor(*opt_object);
		}
		else
		{
			private_visitor
			<
				VariantVisitorT,
				FullVariantT,
				tail_t,
				typename tail_t::head_t
			>::visit(variant_visitor, var);
		}
	}
};

template<class VariantVisitorT, class FullVariantT, class CurrentVariantT>
struct private_visitor<VariantVisitorT, FullVariantT, CurrentVariantT, void>
{
	static
	void
	visit(const VariantVisitorT&, const FullVariantT&)
	{
		//does nothing
	}
};

template<class VariantVisitorT, class VariantT>
void
apply_visitor(const VariantVisitorT& variant_visitor, const VariantT& var)
{
	private_visitor
	<
		VariantVisitorT,
		VariantT,
		VariantT,
		typename VariantT::head_t
	>::visit(variant_visitor, var);
}

}} //namespace scalpel::utility

#endif

