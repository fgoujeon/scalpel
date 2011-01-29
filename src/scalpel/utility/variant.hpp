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

#ifndef SCALPEL_UTILITY_VARIANT_HPP
#define SCALPEL_UTILITY_VARIANT_HPP

#include "basic_variant.hpp"
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <boost/utility/enable_if.hpp>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <memory>
#include <cassert>
#include <iostream>

namespace scalpel { namespace utility
{

template<typename T>
struct replace_reference_by_pointer
{
	typedef T type;
};

template<typename T>
struct replace_reference_by_pointer<T&>
{
	typedef T* type;
};



template<typename T>
struct custom_sizeof
{
	static const unsigned int value = sizeof(T);
};

template<typename T>
struct custom_sizeof<T&>
{
	static const unsigned int value = sizeof(T*);
};



template<typename... Ts>
struct max_size;

template<>
struct max_size<>
{
	static const unsigned int value = 0;
};

template<typename T, typename... Ts>
struct max_size<T, Ts...>
{
	static const unsigned int current_type_size = custom_sizeof<T>::value;
	static const unsigned int next_type_size = max_size<Ts...>::value;
	static const unsigned int value = current_type_size > next_type_size ? current_type_size : next_type_size;
};



template<typename... Ts>
struct type_index_getter;

template<>
struct type_index_getter<>
{
	static const unsigned int index = 0;

	template<typename U>
	static
	unsigned int
	get()
	{
		return 0;
	}
};

template<typename T, typename... Ts>
struct type_index_getter<T, Ts...>
{
	static const unsigned int index = type_index_getter<Ts...>::index + 1;

	template<typename U>
	static
	unsigned int
	get
	(
		typename boost::enable_if
		<
			boost::is_same<T, U>
		>::type* = 0
	)
	{
		return index;
	}

	template<typename U>
	static
	unsigned int
	get
	(
		typename boost::disable_if
		<
			boost::is_same<T, U>
		>::type* = 0
	)
	{
		return type_index_getter<Ts...>::template get<U>();
	}
};



template<typename U, typename... Ts>
struct select_type;

template<typename U>
struct select_type<U>
{
};

//U == T
template<typename T, typename... Ts>
struct select_type<T, T, Ts...>
{
	typedef T type;
};

//U& == T
template<typename T, typename... Ts>
struct select_type<T, T&, Ts...>
{
	typedef T& type;
};

//U == T&
template<typename T, typename... Ts>
struct select_type<T&, T, Ts...>
{
	typedef T type;
};

//const U& == T
template<typename T, typename... Ts>
struct select_type<T, const T&, Ts...>
{
	typedef const T& type;
};

//U == const T&
template<typename T, typename... Ts>
struct select_type<const T&, T, Ts...>
{
	typedef T type;
};

//U == X&
//T == const X&
template<typename T, typename... Ts>
struct select_type<T&, const T&, Ts...>
{
	typedef const T& type;
};

//U != T, let's try to find U among Ts
template<typename U, typename T, typename... Ts>
struct select_type<U, T, Ts...>
{
	typedef typename select_type<U, Ts...>::type type;
};



template<typename U, typename... Ts>
struct strict_select_type;

template<typename U>
struct strict_select_type<U>
{
};

//U == T
template<typename T, typename... Ts>
struct strict_select_type<T, T, Ts...>
{
	typedef T type;
};

//U != T, let's try to find U among Ts
template<typename U, typename T, typename... Ts>
struct strict_select_type<U, T, Ts...>
{
	typedef typename strict_select_type<U, Ts...>::type type;
};



template<unsigned int Size>
class any_container
{
	public:
		template<typename T>
		T&
		get()
		{
			return *reinterpret_cast<T*>(buffer_);
		}

		template<typename T>
		const T&
		get() const
		{
			return *reinterpret_cast<const T*>(buffer_);
		}

		template<typename T>
		void
		set(const T& value)
		{
			new(buffer_) T(value);
		}

		template<typename T>
		void
		clear()
		{
			get<T>().~T();
		}

	private:
		char buffer_[Size];
};



template<bool Cond, bool Const, typename T>
struct get_address_if_impl;

template<typename T>
struct get_address_if_impl<true, false, T>
{
	typedef T* return_type;

	static
	return_type
	result(T& t)
	{
		return &t;
	}
};

template<typename T>
struct get_address_if_impl<false, false, T>
{
	typedef T& return_type;

	static
	return_type
	result(T& t)
	{
		return t;
	}
};

template<typename T>
struct get_address_if_impl<true, true, T>
{
	typedef const T* return_type;

	static
	return_type
	result(const T& t)
	{
		return &t;
	}
};

template<typename T>
struct get_address_if_impl<false, true, T>
{
	typedef const T& return_type;

	static
	return_type
	result(const T& t)
	{
		return t;
	}
};

template<bool Cond, typename T>
const typename get_address_if_impl<Cond, false, T>::return_type
get_address_if(T& t)
{
	return get_address_if_impl<Cond, false, T>::result(t);
}

template<bool Cond, typename T>
const typename get_address_if_impl<Cond, true, T>::return_type
get_address_if(const T& t)
{
	return get_address_if_impl<Cond, true, T>::result(t);
}



template<bool Cond, bool Const, typename T>
struct dereference_if_impl;

template<typename T>
struct dereference_if_impl<true, false, T*>
{
	typedef T& return_type;

	static
	return_type
	result(T* t)
	{
		return *t;
	}
};

template<typename T>
struct dereference_if_impl<false, false, T>
{
	typedef T& return_type;

	static
	return_type
	result(T& t)
	{
		return t;
	}
};

template<typename T>
struct dereference_if_impl<true, true, T*>
{
	typedef const T& return_type;

	static
	return_type
	result(const T* t)
	{
		return *t;
	}
};

template<typename T>
struct dereference_if_impl<false, true, T>
{
	typedef const T& return_type;

	static
	return_type
	result(const T& t)
	{
		return t;
	}
};

template<bool Cond, typename T>
typename dereference_if_impl<Cond, false, T>::return_type
dereference_if(T& t)
{
	return dereference_if_impl<Cond, false, T>::result(t);
}

template<bool Cond, typename T>
typename dereference_if_impl<Cond, true, T>::return_type
dereference_if(const T& t)
{
	return dereference_if_impl<Cond, true, T>::result(t);
}



template<typename... Ts>
struct assign_visitor;

template<typename... Ts>
class variant
{
	public:
		static const unsigned int size = max_size<Ts...>::value;

		template<typename... T2s>
		friend struct assign_visitor;

		template<typename U>
		variant
		(
			U& value,
			typename boost::disable_if<boost::is_same<U, variant>>::type* = 0
		)
		{
			//std::cout << "variant ctor 1" << std::endl;
			set<typename select_type<U&, Ts...>::type>(value);
			assert(type_index_ != 0);
		}

		template<typename U>
		variant
		(
			const U& value,
			typename boost::disable_if<boost::is_same<U, variant>>::type* = 0
		)
		{
			//std::cout << "variant ctor 2" << std::endl;
			set<typename select_type<U, Ts...>::type>(value);
			assert(type_index_ != 0);
		}

		variant(const variant& rhs);

		~variant()
		{
			clear();
		}

		variant&
		operator=(const variant& rhs);

		template<typename U>
		typename boost::disable_if<boost::is_same<U, variant>, variant&>::type
		operator=(U& value)
		{
			//std::cout << "variant assign" << std::endl;
			clear();
			set<typename select_type<U&, Ts...>::type>(value);
			return *this;
		}

		template<typename U>
		typename boost::disable_if<boost::is_same<U, variant>, variant&>::type
		operator=(const U& value)
		{
			//std::cout << "variant assign const" << std::endl;
			clear();
			set<typename select_type<U, Ts...>::type>(value);
			return *this;
		}

		template<typename U>
		U&
		get()
		{
			typedef strict_select_type<U, Ts...> ignored_t; //just check whether U is in Ts
			typedef U selected_type_t;
			const bool selected_type_is_reference = boost::is_reference<selected_type_t>::value;
			typedef typename replace_reference_by_pointer<selected_type_t>::type any_container_type_t;

			if(type_index_getter<Ts...>::template get<U>() != type_index_) throw std::runtime_error("bad get");

			any_container_type_t& value = container_.get<any_container_type_t>();
			return dereference_if<selected_type_is_reference>(value);
		}

		template<typename U>
		const U&
		get() const
		{
			typedef strict_select_type<U, Ts...> ignored_t; //just check whether U is in Ts
			typedef U selected_type_t;
			const bool selected_type_is_reference = boost::is_reference<selected_type_t>::value;
			typedef typename replace_reference_by_pointer<selected_type_t>::type any_container_type_t;

			if(type_index_getter<Ts...>::template get<U>() != type_index_) throw std::runtime_error("bad get");

			const any_container_type_t& value = container_.get<any_container_type_t>();
			return dereference_if<selected_type_is_reference>(value);
		}

		template<typename U>
		U*
		get_optional()
		{
			typedef strict_select_type<U, Ts...> ignored_t; //just check whether U is in Ts
			typedef U selected_type_t;
			const bool selected_type_is_reference = boost::is_reference<selected_type_t>::value;
			typedef typename replace_reference_by_pointer<selected_type_t>::type any_container_type_t;

			if(type_index_getter<Ts...>::template get<U>() != type_index_) return 0;

			any_container_type_t& value = container_.get<any_container_type_t>();
			return &dereference_if<selected_type_is_reference>(value);
		}

		template<typename U>
		const U*
		get_optional() const
		{
			typedef strict_select_type<U, Ts...> ignored_t; //just check whether U is in Ts
			typedef U selected_type_t;
			const bool selected_type_is_reference = boost::is_reference<selected_type_t>::value;
			typedef typename replace_reference_by_pointer<selected_type_t>::type any_container_type_t;

			if(type_index_getter<Ts...>::template get<U>() != type_index_) return 0;

			const any_container_type_t& value = container_.get<any_container_type_t>();
			return &dereference_if<selected_type_is_reference>(value);
		}

	private:
		template<typename U>
		void
		set(const U& value)
		{
			typedef typename select_type<U, Ts...>::type selected_type_t;
			const bool selected_type_is_reference = boost::is_reference<selected_type_t>::value;
			typedef typename replace_reference_by_pointer<selected_type_t>::type any_container_type_t;

			any_container_type_t any_container_value = get_address_if<selected_type_is_reference>(value);
			container_.set<any_container_type_t>(any_container_value);

			type_index_ = type_index_getter<Ts...>::template get<U>();
		}

		void
		clear();

	public:
		unsigned int
		type_index() const
		{
			return type_index_;
		}

	private:
		any_container<size> container_;
		unsigned int type_index_;
};

//forward declaration
template<class Visitor, typename... Ts>
void
apply_visitor
(
	Visitor& visitor,
	const variant<Ts...>& var,
	typename boost::enable_if
	<
		boost::is_same<typename Visitor::return_type, void>
	>::type* = 0
);

//forward declaration
template<class Visitor, typename... Ts>
typename Visitor::return_type
apply_visitor
(
	Visitor& visitor,
	const variant<Ts...>& var,
	typename boost::disable_if
	<
		boost::is_same<typename Visitor::return_type, void>
	>::type* = 0
);

template<typename... Ts>
struct assign_visitor
{
	public:
		typedef void return_type;

		assign_visitor(variant<Ts...>& lhs):
			lhs_(lhs)
		{
		}

		template<typename T>
		void
		operator()(const T& rhs) const
		{
			lhs_.template set<T>(rhs);
		}

	private:
		variant<Ts...>& lhs_;
};

template<typename... Ts>
variant<Ts...>::variant(const variant& rhs)
{
	//std::cout << "variant copy ctor" << std::endl;
	assign_visitor<Ts...> visitor(*this);
	apply_visitor(visitor, rhs);
	assert(type_index_ != 0);
}

template<typename... Ts>
variant<Ts...>&
variant<Ts...>::operator=(const variant& rhs)
{
	//std::cout << "variant copy assign" << std::endl;
	clear();
	assign_visitor<Ts...> visitor(*this);
	apply_visitor(visitor, rhs);
	assert(type_index_ != 0);
	return *this;
}

template<unsigned int Size, typename... Ts>
struct clear_visitor
{
	public:
		typedef void return_type;

		clear_visitor(any_container<Size>& container):
			container_(container)
		{
		}

		template<typename T>
		void
		operator()(const T&) const
		{
			container_.template clear<T>();
		}

	private:
		any_container<Size>& container_;
};

template<typename... Ts>
void
variant<Ts...>::clear()
{
	assert(type_index_ != 0);
	clear_visitor<size, Ts...> visitor(container_);
	apply_visitor(visitor, *this);
}



template<typename T>
struct complete_equal_visitor
{
	public:
		typedef bool return_type;

		complete_equal_visitor(const T& rhs):
			rhs_(rhs)
		{
		}

		bool
		operator()(const T& lhs) const
		{
			return lhs == rhs_;
		}

		template<typename U>
		bool
		operator()(const U&) const
		{
			return false;
		}

	private:
		const T& rhs_;
};

template<typename... Ts>
struct partial_equal_visitor
{
	public:
		typedef bool return_type;

		partial_equal_visitor(const variant<Ts...>& lhs):
			lhs_(lhs)
		{
		}

		template<typename T>
		bool
		operator()(const T& rhs) const
		{
			complete_equal_visitor<T> visitor(rhs);
			return apply_visitor(visitor, lhs_);
		}

	private:
		const variant<Ts...>& lhs_;
};

template<typename... Ts>
bool
operator==(const variant<Ts...>& lhs, const variant<Ts...>& rhs)
{
	partial_equal_visitor<Ts...> visitor(lhs);
	return apply_visitor(visitor, rhs);
}

template<typename... Ts>
bool
operator!=(const variant<Ts...>& lhs, const variant<Ts...>& rhs)
{
	return !(lhs == rhs);
}

template<typename U, typename... Ts>
U&
get(variant<Ts...>& var)
{
	return var.template get<U>();
}

template<typename U, typename... Ts>
const U&
get(const variant<Ts...>& var)
{
	return var.template get<U>();
}

template<typename U, typename... Ts>
U*
get(variant<Ts...>* var)
{
	return var->template get_optional<U>();
}

template<typename U, typename... Ts>
const U*
get(const variant<Ts...>* var)
{
	return var->template get_optional<U>();
}



template<class Visitor, class Variant, typename... Ts>
struct apply_void_visitor_impl;

template<class Visitor, class Variant>
struct apply_void_visitor_impl<Visitor, Variant>
{
	static const unsigned int index = 0;

	static
	void
	visit
	(
		Visitor&,
		const Variant& var
	)
	{
		//won't be called
		std::cout << var.type_index() << std::endl;
		assert(false);
		throw "";
	}
};

template<class Visitor, class Variant, typename T, typename... Ts>
struct apply_void_visitor_impl<Visitor, Variant, T, Ts...>
{
	static const unsigned int index = apply_void_visitor_impl<Visitor, Variant, Ts...>::index + 1;

	static
	void
	visit
	(
		Visitor& visitor,
		const Variant& var
	)
	{
		if(var.type_index() == index)
		{
			visitor(var.template get<T>());
		}
		else
		{
			apply_void_visitor_impl<Visitor, Variant, Ts...>::visit(visitor, var);
		}
	}
};



template<class Visitor, class Variant, typename... Ts>
struct apply_return_visitor_impl;

template<class Visitor, class Variant>
struct apply_return_visitor_impl<Visitor, Variant>
{
	static const unsigned int index = 0;

	static
	typename Visitor::return_type
	visit
	(
		Visitor&,
		const Variant&
	)
	{
		//won't be called
		assert(false);
		throw "";
	}
};

template<class Visitor, class Variant, typename T, typename... Ts>
struct apply_return_visitor_impl<Visitor, Variant, T, Ts...>
{
	static const unsigned int index = apply_return_visitor_impl<Visitor, Variant, Ts...>::index + 1;

	static
	typename Visitor::return_type
	visit
	(
		Visitor& visitor,
		const Variant& var
	)
	{
		if(var.type_index() == index)
		{
			return visitor(var.template get<T>());
		}
		else
		{
			return apply_return_visitor_impl<Visitor, Variant, Ts...>::visit(visitor, var);
		}
	}
};



template<class Visitor, typename... Ts>
void
apply_visitor
(
	Visitor& visitor,
	const variant<Ts...>& var,
	typename boost::enable_if
	<
		boost::is_same<typename Visitor::return_type, void>
	>::type* = 0
)
{
	apply_void_visitor_impl<Visitor, variant<Ts...>, Ts...>::visit(visitor, var);
}

template<class Visitor, typename... Ts>
typename Visitor::return_type
apply_visitor
(
	Visitor& visitor,
	const variant<Ts...>& var,
	typename boost::disable_if
	<
		boost::is_same<typename Visitor::return_type, void>
	>::type* = 0
)
{
	return apply_return_visitor_impl<Visitor, variant<Ts...>, Ts...>::visit(visitor, var);
}

}} //namespace scalpel::utility

#endif

