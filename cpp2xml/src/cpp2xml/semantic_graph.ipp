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

namespace cpp2xml
{

template<class Namespace>
void
semantic_graph_serializer::serialize_namespace
(
	const Namespace& entity,
	const unsigned int indent_level
)
{
	output_ << detail::indent(indent_level) << "<namespace";
	output_ << " " << id_attribute_to_string(entity);
	if(entity.name() != "")
	{
		output_ << " name=\"" << entity.name() << "\"";
	}
	output_ << ">\n";

	serialize_members(entity, indent_level + 1);
	serialize_entity_aliases(entity, indent_level + 1);

	output_ << detail::indent(indent_level) << "</namespace>\n";
}

template<class Namespace>
void
semantic_graph_serializer::serialize_unnamed_namespace
(
	const Namespace& entity,
	const unsigned int indent_level
)
{
	output_ << detail::indent(indent_level) << "<unnamed_namespace>\n";
	serialize_members(entity, indent_level + 1);
	serialize_entity_aliases(entity, indent_level + 1);
	output_ << detail::indent(indent_level) << "</unnamed_namespace>\n";
}

template<class Class>
void
semantic_graph_serializer::serialize_class
(
	const Class& entity,
	const unsigned int indent_level
)
{
	output_ << detail::indent(indent_level) << "<" << markup_name<Class>::value;
	output_ << " " << id_attribute_to_string(entity);
	serialize_name_property(entity);
	serialize_access_property(entity);
	if(!entity.complete())
		output_ << " complete=\"false\"";
	output_ << ">\n";

	serialize_base_classes(entity, indent_level + 1);
	serialize_members(entity, indent_level + 1);
	serialize_entity_aliases(entity, indent_level + 1);

	output_ << detail::indent(indent_level) << "</" << markup_name<Class>::value << ">\n";
}

template<class Enum>
void
semantic_graph_serializer::serialize_enum
(
	const Enum& entity,
	const unsigned int indent_level
)
{
	output_ << detail::indent(indent_level) << "<enum";
	output_ << " " << id_attribute_to_string(entity);
	if(!entity.name().empty())
		output_ << " name=\"" << entity.name() << "\"";
	serialize_access_property(entity);
	output_ << ">\n";

	for(auto i = entity.constants().begin(); i != entity.constants().end(); ++i)
	{
		const enum_constant& constant = *i;
		output_ << detail::indent(indent_level + 1) << "<constant";
		output_ << " name=\"" << constant.name() << "\"";
		output_ << " value=\"" << constant.value() << "\"";
		output_ << ">\n";
	}

	output_ << detail::indent(indent_level) << "</enum>\n";
}

template<class Variable>
void
semantic_graph_serializer::serialize_variable
(
	const Variable& entity,
	const unsigned int indent_level
)
{
	output_ << detail::indent(indent_level) << "<" << markup_name<Variable>::value;
	output_ << " " << id_attribute_to_string(entity);
	if(!entity.name().empty())
		output_ << " name=\"" << entity.name() << "\"";
	serialize_bit_field_size_property(entity);
	serialize_access_property(entity);
	serialize_mutable_property(entity);
	serialize_static_property(entity);
	output_ << ">\n";
	output_ << detail::indent(indent_level + 1) << "<type>\n";
	serialize_type(entity.type(), indent_level + 2);
	output_ << detail::indent(indent_level + 1) << "</type>\n";
	output_ << detail::indent(indent_level) << "</" << markup_name<Variable>::value << ">\n";
}

template<class Typedef>
void
semantic_graph_serializer::serialize_typedef
(
	const Typedef& entity,
	const unsigned int indent_level
)
{
	output_ << detail::indent(indent_level) << "<typedef";
	output_ << " " << id_attribute_to_string(entity);
	output_ << " name=\"" << entity.name() << "\"";
	serialize_access_property(entity);
	output_ << ">\n";
	output_ << detail::indent(indent_level + 1) << "<type>\n";
	serialize_type(entity.type(), indent_level + 2);
	output_ << detail::indent(indent_level + 1) << "</type>\n";
	output_ << detail::indent(indent_level) << "</typedef>\n";
}



template<class Entity>
void
semantic_graph_serializer::serialize_base_classes
(
	const Entity& entity,
	const unsigned int indent_level,
	typename boost::enable_if<scalpel::cpp::semantic_entities::type_traits::has_base_classes<Entity>>::type*
)
{
	if(!entity.base_classes().empty())
	{
		output_ << detail::indent(indent_level) << "<base_classes>\n";
		for(auto i = entity.base_classes().begin(); i != entity.base_classes().end(); ++i)
			serialize_base_class(*i, indent_level + 1);
		output_ << detail::indent(indent_level) << "</base_classes>\n";
	}
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
		output_ << " name=\"" << entity.name() << "\"";
}

template<class Entity>
void
semantic_graph_serializer::serialize_access_property
(
	const Entity& entity,
	typename boost::enable_if<scalpel::cpp::semantic_entities::type_traits::is_member<Entity>>::type*
)
{
	output_ << " access=\"";
	switch(entity.access())
	{
		case member_access::PUBLIC:
			output_ << "public";
			break;
		case member_access::PROTECTED:
			output_ << "protected";
			break;
		case member_access::PRIVATE:
			output_ << "private";
			break;
	}
	output_ << "\"";
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
		output_ << " static=\"true\"";
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
		output_ << " mutable=\"true\"";
}

template<class Entity>
void
semantic_graph_serializer::serialize_bit_field_size_property
(
	const Entity& entity,
	typename boost::enable_if<boost::is_same<Entity, bit_field>>::type*
)
{
	output_ << " size=\"" << entity.size() << "\"";
}

} //namespace cpp2xml

#endif

