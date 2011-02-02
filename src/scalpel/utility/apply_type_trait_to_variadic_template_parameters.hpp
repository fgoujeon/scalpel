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

#ifndef SCALPEL_UTILITY_APPLY_TYPE_TRAIT_TO_VARIADIC_TEMPLATE_PARAMETERS_HPP
#define SCALPEL_UTILITY_APPLY_TYPE_TRAIT_TO_VARIADIC_TEMPLATE_PARAMETERS_HPP

#include "prepend_type.hpp"

namespace scalpel { namespace utility
{

template<template<typename> class TypeTrait, template<typename...> class VariadicTemplate, typename... Ts>
struct apply_type_trait_to_variadic_template_parameters;

template<template<typename> class TypeTrait, template<typename...> class VariadicTemplate>
struct apply_type_trait_to_variadic_template_parameters<TypeTrait, VariadicTemplate>
{
	typedef VariadicTemplate<> type;
};

template<template<typename> class TypeTrait, template<typename...> class VariadicTemplate, typename T, typename... Ts>
struct apply_type_trait_to_variadic_template_parameters<TypeTrait, VariadicTemplate, T, Ts...>
{
	typedef
		typename prepend_type
		<
			typename TypeTrait<T>::type,
			typename apply_type_trait_to_variadic_template_parameters<TypeTrait, VariadicTemplate, Ts...>::type
		>::type
	type;
};

}} //namespace scalpel::utility

#endif

