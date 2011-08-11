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

#ifndef CPP2XML_SEMANTIC_GRAPH_IPP
#define CPP2XML_SEMANTIC_GRAPH_IPP

namespace cpp2json
{

template<class Namespace>
void
semantic_graph_serializer::serialize_namespace
(
	const Namespace& entity
)
{
	writer_.write_key_value_pair("id", get_id_str(entity));
	if(!entity.name().empty())
	{
		writer_.write_key_value_pair("name", entity.name());
	}

	serialize_members(entity);
	serialize_entity_aliases(entity);
}

template<class Namespace>
void
semantic_graph_serializer::serialize_unnamed_namespace
(
	const Namespace& entity
)
{
	serialize_members(entity);
	serialize_entity_aliases(entity);
}

template<class Class>
void
semantic_graph_serializer::serialize_class
(
	const Class& entity
)
{
	writer_.write_key_value_pair("id", get_id_str(entity));
	serialize_name_property(entity);
	serialize_access_property(entity);

	if(!entity.complete())
		writer_.write_key_value_pair("complete", false);

	serialize_base_classes(entity);
	serialize_members(entity);
	serialize_entity_aliases(entity);
}



semantic_graph_serializer::serialize_enum_visitor::serialize_enum_visitor
(
	semantic_graph_serializer& serializer
):
	serializer_(serializer)
{
}

template<typename T>
struct fundamental_type_to_string;

#define FUNDAMENTAL_TYPE_TO_STRING(TYPE, STRING) \
template<> \
struct fundamental_type_to_string<TYPE> \
{ \
	static constexpr const char* value = STRING; \
};

FUNDAMENTAL_TYPE_TO_STRING(int, "int")
FUNDAMENTAL_TYPE_TO_STRING(unsigned int, "unsigned int")
FUNDAMENTAL_TYPE_TO_STRING(long int, "long int")
FUNDAMENTAL_TYPE_TO_STRING(long unsigned int, "long unsigned int")

#undef FUNDAMENTAL_TYPE_TO_STRING

template<typename UnderlyingType>
void
semantic_graph_serializer::serialize_enum_visitor::operator()(const enum_constant_list<UnderlyingType>& constant_list) const
{
	serializer_.writer_.write_key_value_pair("underlying type", fundamental_type_to_string<UnderlyingType>::value);

	serializer_.writer_.open_array("constants");
	for(const enum_constant<UnderlyingType>& constant: constant_list.constants())
	{
		serializer_.writer_.open_object();
		serializer_.writer_.write_key_value_pair("name", constant.name());
		serializer_.writer_.write_key_value_pair("id", serializer_.get_id_str(constant));
		serializer_.writer_.write_key_value_pair("value", constant.value());
		serializer_.writer_.close_object();
	}
	serializer_.writer_.close_array();
}

template<class Enum>
void
semantic_graph_serializer::serialize_enum(const Enum& entity)
{
	writer_.write_key_value_pair("id", get_id_str(entity));
	if(!entity.name().empty())
		writer_.write_key_value_pair("name", entity.name());
	serialize_access_property(entity);

	serialize_enum_visitor visitor(*this);
	apply_visitor(visitor, entity.constants());
}



template<class Variable>
void
semantic_graph_serializer::serialize_variable
(
	const Variable& entity
)
{
	serialize_id_attribute(entity);
	serialize_name_property(entity);
	serialize_bit_field_size_property(entity);
	serialize_access_property(entity);
	serialize_mutable_property(entity);
	serialize_static_property(entity);

	writer_.open_object("type");
	serialize_type(entity.type());
	writer_.close_object();

	if(entity.default_value())
	{
		writer_.open_object("default value");
		serialize_expression(*entity.default_value());
		writer_.close_object();
	}
}

template<class Typedef>
void
semantic_graph_serializer::serialize_typedef
(
	const Typedef& entity
)
{
	serialize_id_attribute(entity);
	serialize_name_property(entity);
	serialize_access_property(entity);

	writer_.open_object("type");
	serialize_type(entity.type());
	writer_.close_object();
}



template<class Entity>
void
semantic_graph_serializer::serialize_base_classes
(
	const Entity& entity,
	typename boost::enable_if<scalpel::cpp::semantic_entities::type_traits::has_base_classes<Entity>>::type*
)
{
	if(!entity.base_classes().empty())
	{
		writer_.open_array("base classes");
		for(auto i = entity.base_classes().begin(); i != entity.base_classes().end(); ++i)
			serialize_base_class(*i);
		writer_.close_array();
	}
}



template<class Entity>
void
semantic_graph_serializer::serialize_id_attribute(const Entity& entity)
{
	writer_.write_key_value_pair("id", get_id_str(entity));
}

template<class Entity>
void
semantic_graph_serializer::serialize_overloaded_operator(const Entity& entity)
{
	writer_.write_key_value_pair("overloaded operator", overloadable_operator_to_string(entity.overloaded_operator()));
}

template<class Entity>
void
semantic_graph_serializer::serialize_name_property
(
	const Entity& entity,
	typename boost::enable_if<scalpel::cpp::semantic_entities::type_traits::has_name<Entity>>::type*
)
{
	if(!entity.name().empty())
		writer_.write_key_value_pair("name", entity.name());
}

template<class Entity>
void
semantic_graph_serializer::serialize_access_property
(
	const Entity& entity,
	typename boost::enable_if<scalpel::cpp::semantic_entities::type_traits::is_member<Entity>>::type*
)
{
	switch(entity.access())
	{
		case member_access::PUBLIC:
			writer_.write_key_value_pair("access", "public");
			break;
		case member_access::PROTECTED:
			writer_.write_key_value_pair("access", "protected");
			break;
		case member_access::PRIVATE:
			writer_.write_key_value_pair("access", "private");
			break;
	}
}

template<class Entity>
void
semantic_graph_serializer::serialize_static_property
(
	const Entity& entity,
	typename boost::enable_if<scalpel::cpp::semantic_entities::type_traits::can_be_static<Entity>>::type*
)
{
	if(entity.is_static())
		writer_.write_key_value_pair("static", "true");
}

template<class Entity>
void
semantic_graph_serializer::serialize_mutable_property
(
	const Entity& entity,
	typename boost::enable_if<scalpel::cpp::semantic_entities::type_traits::can_be_mutable<Entity>>::type*
)
{
	if(entity.is_mutable())
		writer_.write_key_value_pair("mutable", "true");
}

template<class Entity>
void
semantic_graph_serializer::serialize_bit_field_size_property
(
	const Entity& entity,
	typename boost::enable_if<boost::is_same<Entity, bit_field>>::type*
)
{
	writer_.write_key_value_pair("size", entity.size());
}

} //namespace cpp2json

#endif

