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

#ifndef SCALPEL_UTILITY_BASIC_VARIANT_HPP
#define SCALPEL_UTILITY_BASIC_VARIANT_HPP

#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/utility/enable_if.hpp>
#include <memory>
#include <stdexcept>
#include <cassert>

namespace scalpel { namespace utility
{

template<template<typename> class TypeTraitT, typename... Ts>
class basic_variant;

template<template<typename> class TypeTraitT>
class basic_variant<TypeTraitT>
{
	public:
		typedef void head_t;
		typedef void tail_t;

		bool
		operator==(const basic_variant&) const
		{
			return false; //or whatever, won't be called
		}

		bool
		operator<(const basic_variant&) const
		{
			return false; //or whatever, won't be called
		}
};

template<template<typename> class TypeTraitT, typename T, typename... Ts>
class basic_variant<TypeTraitT, T, Ts...>
{
	public:
		typedef T raw_head_t;
		typedef typename TypeTraitT<T>::type head_t;
		typedef basic_variant<TypeTraitT, Ts...> tail_t;

		template<template<typename> class TypeTraitT2, typename... T2s>
		friend class basic_variant;

	private:
		/**
		 * Default constructor which does nothing (useful for internal use).
		 */
		basic_variant();

	public:
		/**
		 * Constructor.
		 */
		basic_variant(const head_t& rhs);

		/**
		 * Constructor.
		 */
		basic_variant(head_t& rhs);

		/**
		 * Constructor.
		 */
		basic_variant(head_t&& rhs);

		/**
		 * Constructor.
		 */
		template<typename T2>
		basic_variant
		(
			const T2& rhs,
			typename boost::disable_if
			<
				boost::is_same
				<
					typename boost::remove_const<T2>::type,
					basic_variant
				>
			>::type* = 0 //avoid conflict with copy and move constructors
		);

		/**
		 * Constructor.
		 */
		template<typename T2>
		basic_variant
		(
			T2&& rhs,
			typename boost::disable_if
			<
				boost::is_same
				<
					typename boost::remove_const<T2>::type,
					basic_variant
				>
			>::type* = 0 //avoid conflict with copy and move constructors
		);

		/**
		 * Copy constructor.
		 */
		basic_variant(const basic_variant& rhs);

		/**
		 * Copy constructor.
		 */
		basic_variant(basic_variant& rhs);

		/**
		 * Move constructor.
		 */
		basic_variant(basic_variant&& rhs);

		const basic_variant&
		operator=(const basic_variant& rhs);

	private:
		const basic_variant&
		assign(const basic_variant& rhs);

		template<typename T2>
		const basic_variant&
		assign
		(
			const T2& rhs,
			typename boost::disable_if
			<
				boost::is_same
				<
					typename boost::remove_const<T2>::type,
					basic_variant
				>
			>::type* = 0 //avoid conflict with primary assign()
		);

	public:
		//Return true if *this and rhs contain the same type and
		//content_this == content_rhs.
		bool
		operator==(const basic_variant& rhs) const;

		//this overload exists only to prohibit implicit conversion of the RHS
		//to basic_variant
		template<typename U>
		void
		operator==(const U&) const = delete;

		//Return true if *this and rhs contain the same type and
		//content_this < content_rhs.
		//Otherwise, return this_type_index < rhs_type_index.
		bool
		operator<(const basic_variant& rhs) const;

		//this overload exists only to prohibit implicit conversion of the RHS
		//to basic_variant
		template<typename U>
		void
		operator<(const U&) const = delete;

		void
		get(head_t*&);

		void
		get(const head_t*&) const;

		//T2 is one of the tail's types
		template<typename T2>
		void
		get(T2*&);

		//T2 is one of the tail's types
		template<typename T2>
		void
		get(const T2*&) const;

	private:
		std::unique_ptr<head_t> head_;
		tail_t tail_;
};

template<template<typename> class TypeTraitT, typename T, typename... Ts>
basic_variant<TypeTraitT, T, Ts...>::basic_variant()
{
	//does nothing
}

template<template<typename> class TypeTraitT, typename T, typename... Ts>
basic_variant<TypeTraitT, T, Ts...>::basic_variant(const head_t& rhs):
	head_(new head_t(rhs))
{
}

template<template<typename> class TypeTraitT, typename T, typename... Ts>
basic_variant<TypeTraitT, T, Ts...>::basic_variant(head_t& rhs):
	head_(new head_t(rhs))
{
}

template<template<typename> class TypeTraitT, typename T, typename... Ts>
basic_variant<TypeTraitT, T, Ts...>::basic_variant(head_t&& rhs):
	head_(new head_t(rhs))
{
}

template<template<typename> class TypeTraitT, typename T, typename... Ts>
template<typename T2>
basic_variant<TypeTraitT, T, Ts...>::basic_variant
(
	const T2& rhs,
	typename boost::disable_if
	<
		boost::is_same
		<
			typename boost::remove_const<T2>::type,
			basic_variant
		>
	>::type*
):
	tail_(rhs)
{
}

template<template<typename> class TypeTraitT, typename T, typename... Ts>
template<typename T2>
basic_variant<TypeTraitT, T, Ts...>::basic_variant
(
	T2&& rhs,
	typename boost::disable_if
	<
		boost::is_same
		<
			typename boost::remove_const<T2>::type,
			basic_variant
		>
	>::type*
):
	tail_(std::move(rhs))
{
}

template<template<typename> class TypeTraitT, typename T, typename... Ts>
basic_variant<TypeTraitT, T, Ts...>::basic_variant(const basic_variant<TypeTraitT, T, Ts...>& rhs):
	head_(rhs.head_ ? std::unique_ptr<head_t>(new head_t(*rhs.head_)) : std::unique_ptr<head_t>()),
	tail_(rhs.tail_)
{
}

template<template<typename> class TypeTraitT, typename T, typename... Ts>
basic_variant<TypeTraitT, T, Ts...>::basic_variant(basic_variant<TypeTraitT, T, Ts...>& rhs):
	head_(rhs.head_ ? std::unique_ptr<head_t>(new head_t(*rhs.head_)) : std::unique_ptr<head_t>()),
	tail_(rhs.tail_)
{
}

template<template<typename> class TypeTraitT, typename T, typename... Ts>
basic_variant<TypeTraitT, T, Ts...>::basic_variant(basic_variant<TypeTraitT, T, Ts...>&& rhs):
	head_(std::move(rhs.head_)),
	tail_(std::move(rhs.tail_))
{
}

template<template<typename> class TypeTraitT, typename T, typename... Ts>
const basic_variant<TypeTraitT, T, Ts...>&
basic_variant<TypeTraitT, T, Ts...>::operator=(const basic_variant<TypeTraitT, T, Ts...>& rhs)
{
	return assign(rhs);
}

template<template<typename> class TypeTraitT, typename T, typename... Ts>
const basic_variant<TypeTraitT, T, Ts...>&
basic_variant<TypeTraitT, T, Ts...>::assign(const basic_variant& rhs)
{
	//exception safety: ensure the may-throw copy of the rhs basic_variant's content
	//occurs before the erasure of the lhs basic_variant's content
	if(!head_)
	{
		if(rhs.head_)
			head_ = std::unique_ptr<head_t>(new head_t(*rhs.head_));

		tail_ = rhs.tail_;
	}
	else
	{
		tail_ = rhs.tail_;

		//erase the lhs basic_variant's content
		if(rhs.head_)
			head_ = std::unique_ptr<head_t>(new head_t(*rhs.head_));
		else
			head_.reset();
	}

	return *this;
}

template<template<typename> class TypeTraitT, typename T, typename... Ts>
template<typename T2>
const basic_variant<TypeTraitT, T, Ts...>&
basic_variant<TypeTraitT, T, Ts...>::assign
(
	const T2& rhs,
	typename boost::disable_if
	<
		boost::is_same
		<
			typename boost::remove_const<T2>::type,
			basic_variant
		>
	>::type*
)
{
	return basic_variant(rhs);
}

template<template<typename> class TypeTraitT, typename T, typename... Ts>
bool
basic_variant<TypeTraitT, T, Ts...>::operator==(const basic_variant& rhs) const
{
	if(head_ && rhs.head_)
		return *head_ == *rhs.head_;
	else if(head_ || rhs.head_)
		return false;
	else
		return tail_ == rhs.tail_;
}

template<template<typename> class TypeTraitT, typename T, typename... Ts>
bool
basic_variant<TypeTraitT, T, Ts...>::operator<(const basic_variant& rhs) const
{
	if(head_ && rhs.head_)
		return *head_ < *rhs.head_;
	else if(head_)
		return true;
	else if(rhs.head_)
		return false;
	else
		return tail_ < rhs.tail_;
}

template<template<typename> class TypeTraitT, typename T, typename... Ts>
void
basic_variant<TypeTraitT, T, Ts...>::get(head_t*& object)
{
	if(head_)
		object = head_.get();
	else
		object = 0;
}

template<template<typename> class TypeTraitT, typename T, typename... Ts>
void
basic_variant<TypeTraitT, T, Ts...>::get(const head_t*& object) const
{
	if(head_)
		object = head_.get();
	else
		object = 0;
}

template<template<typename> class TypeTraitT, typename T, typename... Ts>
template<typename T2>
void
basic_variant<TypeTraitT, T, Ts...>::get(T2*& object)
{
	tail_.get(object);
}

template<template<typename> class TypeTraitT, typename T, typename... Ts>
template<typename T2>
void
basic_variant<TypeTraitT, T, Ts...>::get(const T2*& object) const
{
	tail_.get(object);
}



template<template<typename> class TypeTraitT, typename... Ts>
bool
operator!=(const basic_variant<TypeTraitT, Ts...>& lhs, const basic_variant<TypeTraitT, Ts...>& rhs)
{
	return !(lhs == rhs);
}

template<typename ReturnT, template<typename> class TypeTraitT, typename... Ts>
typename TypeTraitT<ReturnT>::type*
get(basic_variant<TypeTraitT, Ts...>* var)
{
	typename TypeTraitT<ReturnT>::type* return_object = 0;
	var->get(return_object);

	if(return_object)
		return return_object;
	else
		return 0;
}

template<typename ReturnT, template<typename> class TypeTraitT, typename... Ts>
const typename TypeTraitT<ReturnT>::type*
get(const basic_variant<TypeTraitT, Ts...>* var)
{
	const typename TypeTraitT<ReturnT>::type* return_object = 0;
	var->get(return_object);

	if(return_object)
		return return_object;
	else
		return 0;
}

template<typename ReturnT, template<typename> class TypeTraitT, typename... Ts>
typename TypeTraitT<ReturnT>::type&
get(basic_variant<TypeTraitT, Ts...>& var)
{
	typename TypeTraitT<ReturnT>::type* return_object = 0;
	var.get(return_object);

	if(!return_object)
		throw std::runtime_error("basic_variant: bad get");
	return *return_object;
}

template<typename ReturnT, template<typename> class TypeTraitT, typename... Ts>
const typename TypeTraitT<ReturnT>::type&
get(const basic_variant<TypeTraitT, Ts...>& var)
{
	const typename TypeTraitT<ReturnT>::type* return_object = 0;
	var.get(return_object);

	if(!return_object)
		throw std::runtime_error("basic_variant: bad get");
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

	typedef typename CurrentVariantT::raw_head_t raw_head_t;
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
		const head_t* opt_object = get<raw_head_t>(&var);
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

	typedef typename CurrentVariantT::raw_head_t raw_head_t;
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
		const head_t* opt_object = get<raw_head_t>(&var);
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
		assert(false);
		throw "";
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

