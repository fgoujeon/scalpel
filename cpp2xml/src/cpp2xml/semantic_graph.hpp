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

#ifndef CPP2XML_SEMANTIC_GRAPH_HPP
#define CPP2XML_SEMANTIC_GRAPH_HPP

#include <scalpel/cpp/semantic_entities/type_traits/has_members_of_type.hpp>
#include <scalpel/cpp/semantic_entities/generic_queries/detail/get_members.hpp>
#include <scalpel/cpp/semantic_graph.hpp>
#include <string>
#include <map>
#include <sstream>
#include <ostream>

namespace cpp2xml
{

using namespace scalpel;
using namespace scalpel::cpp;
using namespace scalpel::cpp::semantic_entities;

template<class Entity>
struct entity_id_map
{
	typedef std::map<const Entity*, unsigned int> type;
};

class semantic_graph_serializer
{
	public:
		typedef std::map<const scalpel::cpp::semantic_entities::namespace_*, unsigned int> namespace_ids_t;
		typedef std::map<const scalpel::cpp::semantic_entities::linked_namespace*, unsigned int> linked_namespace_ids_t;
		typedef std::map<const scalpel::cpp::semantic_entities::class_*, unsigned int> class_ids_t;
		typedef std::map<const scalpel::cpp::semantic_entities::member_class*, unsigned int> member_class_ids_t;
		typedef std::map<const scalpel::cpp::semantic_entities::enum_*, unsigned int> enum_ids_t;
		typedef std::map<const scalpel::cpp::semantic_entities::member_enum*, unsigned int> member_enum_ids_t;

		semantic_graph_serializer(std::ostream& output);

		void
		operator()(const namespace_& entity);

		void
		operator()(const linked_namespace& entity);

	private:
		void
		serialize_type
		(
			const semantic_entities::type_variant& entity,
			const unsigned int indent_level
		);

		void
		serialize_fundamental_type
		(
			const fundamental_type type
		);

		void
		serialize_namespace
		(
			const namespace_& entity,
			const unsigned int indent_level = 0
		);

		void
		serialize_namespace
		(
			const linked_namespace& entity,
			const unsigned int indent_level = 0
		);

		void
		serialize_unnamed_namespace
		(
			const unnamed_namespace& entity,
			const unsigned int indent_level = 0
		);

		void
		serialize_unnamed_namespace
		(
			const linked_unnamed_namespace& entity,
			const unsigned int indent_level = 0
		);

		void
		serialize_class
		(
			const class_& entity,
			const unsigned int indent_level
		);

		void
		serialize_class
		(
			const member_class& entity,
			const unsigned int indent_level
		);

		void
		serialize_base_class
		(
			const base_class& entity,
			const unsigned int indent_level
		);

		void
		serialize_enum
		(
			const enum_& entity,
			const unsigned int indent_level
		);

		void
		serialize_enum
		(
			const member_enum& entity,
			const unsigned int indent_level
		);

		void
		serialize_constructor
		(
			const constructor& entity,
			const unsigned int indent_level
		);

		void
		serialize_destructor
		(
			const destructor& entity,
			const unsigned int indent_level
		);

		void
		serialize_operator_member_function
		(
			const operator_member_function& entity,
			const unsigned int indent_level
		);

		void
		serialize_conversion_function
		(
			const conversion_function& entity,
			const unsigned int indent_level
		);

		void
		serialize_simple_member_function
		(
			const simple_member_function& entity,
			const unsigned int indent_level
		);

		void
		serialize_operator_function
		(
			const operator_function& entity,
			const unsigned int indent_level
		);

		void
		serialize_simple_function
		(
			const simple_function& entity,
			const unsigned int indent_level
		);

		void
		serialize_function_type
		(
			const function_type& entity,
			const unsigned int indent_level
		);

		void
		serialize_function_parameter_list
		(
			const function_parameter_list& entity,
			const unsigned int indent_level
		);

		void
		serialize_function_parameter
		(
			const function_parameter& entity,
			const unsigned int indent_level
		);

		void
		serialize_variable
		(
			const variable& entity,
			const unsigned int indent_level
		);

		void
		serialize_variable
		(
			const member_variable& entity,
			const unsigned int indent_level
		);

		void
		serialize_bit_field
		(
			const bit_field& entity,
			const unsigned int indent_level
		);

		void
		serialize_namespace_alias
		(
			const namespace_alias& entity,
			const unsigned int indent_level
		);

		void
		serialize_typedef
		(
			const typedef_& entity,
			const unsigned int indent_level
		);

		void
		serialize_typedef
		(
			const member_typedef& entity,
			const unsigned int indent_level
		);

		void
		serialize_class_alias
		(
			const entity_alias<class_>& entity,
			const unsigned int indent_level
		);



		std::string
		attribute(const member_access& a);

		std::string
		attribute(const semantic_entities::overloadable_operator op);

		void
		serialize_class_id_attribute
		(
			const scalpel::cpp::semantic_entities::class_ptr_variant& entity
		);



		template<class Entity>
		void
		set_ids(const Entity& entity)
		{
			using namespace scalpel::cpp::semantic_entities;
			set_id(entity);

			set_id_of_members_of_type<namespace_>(entity);
			set_id_of_members_of_type<linked_namespace>(entity);
			set_id_of_members_of_type<unnamed_namespace>(entity);
			set_id_of_members_of_type<linked_unnamed_namespace>(entity);
			set_id_of_members_of_type<class_>(entity);
			set_id_of_members_of_type<member_class>(entity);
			set_id_of_members_of_type<enum_>(entity);
			set_id_of_members_of_type<member_enum>(entity);
			set_id_of_members_of_type<typedef_>(entity);
			set_id_of_members_of_type<member_typedef>(entity);
			set_id_of_members_of_type<constructor>(entity);
			set_id_of_members_of_type<destructor>(entity);
			set_id_of_members_of_type<operator_member_function>(entity);
			set_id_of_members_of_type<conversion_function>(entity);
			set_id_of_members_of_type<simple_member_function>(entity);
			set_id_of_members_of_type<operator_function>(entity);
			set_id_of_members_of_type<simple_function>(entity);
			set_id_of_members_of_type<variable>(entity);
			set_id_of_members_of_type<member_variable>(entity);
			set_id_of_members_of_type<bit_field>(entity);
		}

		template<class Entity, class DeclarativeRegion>
		void
		set_id_of_members_of_type
		(
			const DeclarativeRegion& declarative_region,
			typename boost::enable_if<scalpel::cpp::semantic_entities::type_traits::has_members_of_type<DeclarativeRegion, Entity>>::type* = 0
		)
		{
			using namespace scalpel::cpp::semantic_entities::generic_queries::detail;

			typename get_members_return_type<DeclarativeRegion, Entity, true>::type members = get_members<Entity>(declarative_region);
			for(auto i = members.begin(); i != members.end(); ++i)
				set_ids(*i);
		}

		template<class Entity, class DeclarativeRegion>
		void
		set_id_of_members_of_type
		(
			const DeclarativeRegion&,
			typename boost::disable_if<scalpel::cpp::semantic_entities::type_traits::has_members_of_type<DeclarativeRegion, Entity>>::type* = 0
		)
		{
			//does nothing
		}

		template<class Entity>
		unsigned int
		get_id(const Entity& entity) const
		{
			auto it = entity_id_map_of_type<Entity>().find(&entity);
			if(it != entity_id_map_of_type<Entity>().end())
				return it->second;
			else
				assert(false);
		}

		template<class Entity>
		void
		set_id(const Entity& entity)
		{
			const unsigned int id = entity_id_map_of_type<Entity>().size();
			entity_id_map_of_type<Entity>()[&entity] = id;
		}

		template<class Entity>
		typename entity_id_map<Entity>::type&
		entity_id_map_of_type();

		template<class Entity>
		const typename entity_id_map<Entity>::type&
		entity_id_map_of_type() const;



		std::ostream& output_;
		typename entity_id_map<semantic_entities::namespace_>::type namespace_id_map_;
		typename entity_id_map<semantic_entities::linked_namespace>::type linked_namespace_id_map_;
		typename entity_id_map<semantic_entities::unnamed_namespace>::type unnamed_namespace_id_map_;
		typename entity_id_map<semantic_entities::linked_unnamed_namespace>::type linked_unnamed_namespace_id_map_;
		typename entity_id_map<semantic_entities::class_>::type class_id_map_;
		typename entity_id_map<semantic_entities::member_class>::type member_class_id_map_;
		typename entity_id_map<semantic_entities::enum_>::type enum_id_map_;
		typename entity_id_map<semantic_entities::member_enum>::type member_enum_id_map_;
		typename entity_id_map<semantic_entities::typedef_>::type typedef_id_map_;
		typename entity_id_map<semantic_entities::member_typedef>::type member_typedef_id_map_;
		typename entity_id_map<semantic_entities::constructor>::type constructor_id_map_;
		typename entity_id_map<semantic_entities::destructor>::type destructor_id_map_;
		typename entity_id_map<semantic_entities::operator_member_function>::type operator_member_function_id_map_;
		typename entity_id_map<semantic_entities::conversion_function>::type conversion_function_id_map_;
		typename entity_id_map<semantic_entities::simple_member_function>::type simple_member_function_id_map_;
		typename entity_id_map<semantic_entities::operator_function>::type operator_function_id_map_;
		typename entity_id_map<semantic_entities::simple_function>::type simple_function_id_map_;
		typename entity_id_map<semantic_entities::variable>::type variable_id_map_;
		typename entity_id_map<semantic_entities::member_variable>::type member_variable_id_map_;
		typename entity_id_map<semantic_entities::bit_field>::type bit_field_id_map_;
};



void
serialize_semantic_graph
(
	const semantic_graph& graph,
	std::ostream& output
);

void
serialize_semantic_graph
(
	const linked_semantic_graph& graph,
	std::ostream& output
);

} //namespace cpp2xml

#endif

