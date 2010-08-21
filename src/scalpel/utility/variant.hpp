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
#include <stdexcept>

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
	//exception safety: ensure the may-throw copy of the rhs variant's content
	//occurs before the erasure of the lhs variant's content
	if(!head_)
	{
		head_ = o.head_; //may throw
		tail_ = o.tail_; //may throw
	}
	else
	{
		tail_ = o.tail_; //may throw
		head_ = o.head_; //erase the lhs variant's content, may not throw
	}

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



template<typename ReturnT, typename... Ts>
boost::optional<const ReturnT&>
get(const variant<Ts...>* var)
{
	boost::optional<const ReturnT&> return_object;
	var->get(return_object);
	return return_object;
}

template<typename ReturnT, typename... Ts>
const ReturnT&
get(const variant<Ts...>& var)
{
	boost::optional<const ReturnT&> return_object;
	var.get(return_object);
	if(!return_object)
		throw std::runtime_error("variant: bad get");
	return *return_object;
}



template<typename ResultTypeT>
class static_visitor
{
	public:
		typedef ResultTypeT result_type;
};



template<typename ResultTypeT, class VariantVisitorT, class FullVariantT, class CurrentVariantT, typename HeadT>
class apply_visitor_impl
{
	template<typename ResultTypeT2, class VariantVisitorT2, class FullVariantT2, class CurrentVariantT2, typename HeadT2>
	friend struct apply_visitor_impl;

	template<class VariantVisitorT2, class VariantT2>
	typename VariantVisitorT2::result_type
	friend apply_visitor
	(
		VariantVisitorT2& variant_visitor,
		const VariantT2& var,
		typename boost::disable_if
		<
			boost::is_same
			<
				typename VariantVisitorT2::result_type,
				void
			>
		>::type* = 0
	);

	typedef typename CurrentVariantT::head_t head_t;
	typedef typename CurrentVariantT::tail_t tail_t;

	static
	typename VariantVisitorT::result_type
	visit
	(
		VariantVisitorT& variant_visitor,
		const FullVariantT& var
	)
	{
		boost::optional<const head_t&> opt_object = get<head_t>(&var);
		if(opt_object)
		{
			return variant_visitor(*opt_object);
		}
		else
		{
			return apply_visitor_impl
			<
				typename VariantVisitorT::result_type,
				VariantVisitorT,
				FullVariantT,
				tail_t,
				typename tail_t::head_t
			>::visit(variant_visitor, var);
		}
	}
};

//specialization for no return visitors
template<class VariantVisitorT, class FullVariantT, class CurrentVariantT, typename HeadT>
class apply_visitor_impl<void, VariantVisitorT, FullVariantT, CurrentVariantT, HeadT>
{
	template<typename ResultTypeT2, class VariantVisitorT2, class FullVariantT2, class CurrentVariantT2, typename HeadT2>
	friend struct apply_visitor_impl;

	template<class VariantVisitorT2, class VariantT2>
	void
	friend apply_visitor
	(
		VariantVisitorT2& variant_visitor,
		const VariantT2& var,
		typename boost::enable_if
		<
			boost::is_same
			<
				typename VariantVisitorT2::result_type,
				void
			>
		>::type* = 0
	);

	typedef typename CurrentVariantT::head_t head_t;
	typedef typename CurrentVariantT::tail_t tail_t;

	static
	void
	visit
	(
		VariantVisitorT& variant_visitor,
		const FullVariantT& var
	)
	{
		boost::optional<const head_t&> opt_object = get<head_t>(&var);
		if(opt_object)
		{
			variant_visitor(*opt_object);
		}
		else
		{
			apply_visitor_impl
			<
				void,
				VariantVisitorT,
				FullVariantT,
				tail_t,
				typename tail_t::head_t
			>::visit(variant_visitor, var);
		}
	}
};

//specialization for end tail recursion
template<typename ResultTypeT, class VariantVisitorT, class FullVariantT, class CurrentVariantT>
class apply_visitor_impl<ResultTypeT, VariantVisitorT, FullVariantT, CurrentVariantT, void>
{
	template<typename ResultTypeT2, class VariantVisitorT2, class FullVariantT2, class CurrentVariantT2, typename HeadT2>
	friend struct apply_visitor_impl;

	static
	typename VariantVisitorT::result_type
	visit
	(
		VariantVisitorT&,
		const FullVariantT&,
		typename boost::disable_if
		<
			boost::is_same
			<
				typename VariantVisitorT::result_type,
				void
			>
		>::type* = 0
	)
	{
		//this code will never be called
		//it has been written for warning-free purpose
		typename VariantVisitorT::result_type* return_value_ptr = 0;
		return *return_value_ptr;
	}
};

//specialization for end tail recursion and no return visitors
template<class VariantVisitorT, class FullVariantT, class CurrentVariantT>
class apply_visitor_impl<void, VariantVisitorT, FullVariantT, CurrentVariantT, void>
{
	template<typename ResultTypeT2, class VariantVisitorT2, class FullVariantT2, class CurrentVariantT2, typename HeadT2>
	friend struct apply_visitor_impl;

	static
	void
	visit
	(
		VariantVisitorT&,
		const FullVariantT&
	)
	{
		//does nothing
	}
};

template<class VariantVisitorT, class VariantT>
typename VariantVisitorT::result_type
apply_visitor
(
	VariantVisitorT& variant_visitor,
	const VariantT& var,
	typename boost::disable_if
	<
		boost::is_same
		<
			typename VariantVisitorT::result_type,
			void
		>
	>::type* = 0
)
{
	return apply_visitor_impl
	<
		typename VariantVisitorT::result_type,
		VariantVisitorT,
		VariantT,
		VariantT,
		typename VariantT::head_t
	>::visit(variant_visitor, var);
}

//overload for no return visitors
template<class VariantVisitorT, class VariantT>
void
apply_visitor
(
	VariantVisitorT& variant_visitor,
	const VariantT& var,
	typename boost::enable_if
	<
		boost::is_same
		<
			typename VariantVisitorT::result_type,
			void
		>
	>::type* = 0
)
{
	apply_visitor_impl
	<
		void,
		VariantVisitorT,
		VariantT,
		VariantT,
		typename VariantT::head_t
	>::visit(variant_visitor, var);
}

}} //namespace scalpel::utility

#endif

