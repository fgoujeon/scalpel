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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_ENUM_CONSTANT_IPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_ENUM_CONSTANT_IPP

namespace scalpel { namespace cpp { namespace semantic_entities
{

template<typename UnderlyingType>
enum_constant<UnderlyingType>::enum_constant(const std::string& name, const UnderlyingType value):
	name_(name),
	value_(value)
{
}



template<typename UnderlyingType, class ReturnType>
struct get_enum_constant_type_visitor: utility::static_visitor<ReturnType>
{
	template<template<typename> class BasicEnum>
	ReturnType
	operator()(BasicEnum<UnderlyingType>* e)
	{
		return &e->variant_enum();
	}
};

template<typename UnderlyingType>
typename enum_constant<UnderlyingType>::type_t
enum_constant<UnderlyingType>::type()
{
	assert(parent_enum_);
	get_enum_constant_type_visitor<UnderlyingType, typename enum_constant<UnderlyingType>::type_t> visitor;
	return apply_visitor(visitor, *parent_enum_);
}

template<typename UnderlyingType>
typename enum_constant<UnderlyingType>::const_type_t
enum_constant<UnderlyingType>::type() const
{
	assert(parent_enum_);
	get_enum_constant_type_visitor<UnderlyingType, typename enum_constant<UnderlyingType>::const_type_t> visitor;
	return apply_visitor(visitor, *parent_enum_);
}

}}} //namespace scalpel::cpp::semantic_entities

#endif

