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

#include "detail/json_writer.hpp"
#include <scalpel/cpp/semantic_entities/type_traits/has_name.hpp>
#include <scalpel/cpp/semantic_entities/type_traits/has_base_classes.hpp>
#include <scalpel/cpp/semantic_entities/type_traits/has_entity_aliases_of_type.hpp>
#include <scalpel/cpp/semantic_entities/type_traits/has_members_of_type.hpp>
#include <scalpel/cpp/semantic_entities/type_traits/is_member.hpp>
#include <scalpel/cpp/semantic_entities/type_traits/can_be_mutable.hpp>
#include <scalpel/cpp/semantic_entities/type_traits/can_be_static.hpp>
#include <scalpel/cpp/semantic_entities/generic_queries/detail/get_entity_aliases.hpp>
#include <scalpel/cpp/semantic_entities/generic_queries/detail/get_members.hpp>
#include <scalpel/cpp/semantic_graph.hpp>
#include <boost/type_traits/is_same.hpp>
#include <string>
#include <map>
#include <sstream>
#include <ostream>

namespace cpp2json
{

using namespace scalpel;
using namespace scalpel::cpp;
using namespace scalpel::cpp::semantic_entities;

template<class Entity>
struct entity_id_map
{
	typedef std::map<const Entity*, unsigned int> type;
};



template<class Entity>
struct singular_key_of_type;

template<class Entity>
struct plural_key_of_type;

template<class Entity>
struct id_prefix;

#define KEYS_OF_TYPE(TYPE, SINGULAR_KEY, PLURAL_KEY, ID_PREFIX) \
template<> \
struct singular_key_of_type<TYPE> \
{ \
	static constexpr char const* value = SINGULAR_KEY; \
}; \
 \
template<> \
struct plural_key_of_type<TYPE> \
{ \
	static constexpr char const* value = PLURAL_KEY; \
}; \
 \
template<> \
struct id_prefix<TYPE> \
{ \
	static constexpr char const* value = ID_PREFIX; \
};

KEYS_OF_TYPE(namespace_alias, "namespace alias", "namespace aliases", "namespace-alias")
KEYS_OF_TYPE(namespace_, "namespace", "namespaces", "namespace")
KEYS_OF_TYPE(linked_namespace, "namespace", "namespaces", "namespace")
KEYS_OF_TYPE(unnamed_namespace, "unnamed namespace", "unnamed namespaces", "unnamed-namespace")
KEYS_OF_TYPE(linked_unnamed_namespace, "unnamed namespace", "unnamed namespaces", "unnamed-namespace")
KEYS_OF_TYPE(class_, "class", "classes", "class")
KEYS_OF_TYPE(member_class, "class", "classes", "member-class")
KEYS_OF_TYPE(union_, "union", "unions", "union")
KEYS_OF_TYPE(member_union, "union", "unions", "member-union")
KEYS_OF_TYPE(anonymous_union, "anonymous union", "anonymous unions", "anonymous-union")
KEYS_OF_TYPE(anonymous_member_union, "anonymous union", "anonymous unions", "anonymous-member-union")
KEYS_OF_TYPE(enum_, "enum", "enums", "enum")
KEYS_OF_TYPE(member_enum, "enum", "enums", "member-enum")
KEYS_OF_TYPE(typedef_, "typedef", "typedefs", "typedef")
KEYS_OF_TYPE(member_typedef, "typedef", "typedefs", "member-typedef")
KEYS_OF_TYPE(constructor, "constructor", "constructors", "constructor")
KEYS_OF_TYPE(destructor, "destructor", "destructors", "destructor")
KEYS_OF_TYPE(operator_member_function, "operator function", "operator functions", "operator-member-function")
KEYS_OF_TYPE(conversion_function, "conversion function", "conversion functions", "conversion-function")
KEYS_OF_TYPE(simple_member_function, "simple function", "simple functions", "simple-member-function")
KEYS_OF_TYPE(operator_function, "operator function", "operator functions", "operator-function")
KEYS_OF_TYPE(simple_function, "simple function", "simple functions", "simple-function")
KEYS_OF_TYPE(variable, "variable", "variables", "variable")
KEYS_OF_TYPE(member_variable, "variable", "variables", "member-variable")
KEYS_OF_TYPE(static_member_variable, "static variable", "static variables", "static-member-variable")
KEYS_OF_TYPE(bit_field, "bit field", "bit fields", "bit-field")
KEYS_OF_TYPE(enum_constant<int>, "int enum constant", "int enum constants", "int-enum-constant")
KEYS_OF_TYPE(enum_constant<unsigned int>, "unsigned int enum constant", "unsigned int enum constants", "unsigned-int-enum-constant")
KEYS_OF_TYPE(enum_constant<long>, "long enum constant", "long enum constants", "long-enum-constant")
KEYS_OF_TYPE(enum_constant<unsigned long>, "unsigned long enum constant", "unsigned long enum constants", "unsigned-long-enum-constant")

#undef KEYS_OF_TYPE



class semantic_graph_serializer
{
	public:
		semantic_graph_serializer(std::ostream& output);

		void
		operator()(const namespace_& entity);

		void
		operator()(const linked_namespace& entity);

	private:
		class serialize_type_visitor: public scalpel::utility::static_visitor<void>
		{
			public:
				serialize_type_visitor
				(
					semantic_graph_serializer& serializer
				);

				void
				operator()(const fundamental_type& type);

				void
				operator()(const function_type& type);

				void
				operator()(const cv_qualified_type& type);

				void
				operator()(const pointer& type);

				void
				operator()(const pointer_to_member& type);

				void
				operator()(const reference& type);

				void
				operator()(const array& type);

				void
				operator()(const class_* type);

				void
				operator()(const member_class* type);

				void
				operator()(const union_* type);

				void
				operator()(const member_union* type);

				void
				operator()(const anonymous_union* type);

				void
				operator()(const anonymous_member_union* type);

				void
				operator()(const enum_* type);

				void
				operator()(const member_enum* type);

			private:
				semantic_graph_serializer& serializer_;
				detail::json_writer& writer_;
		};
		friend class serialize_type_visitor;

		class serialize_expression_visitor: public scalpel::utility::static_visitor<void>
		{
			public:
				serialize_expression_visitor
				(
					semantic_graph_serializer& serializer
				);

				template<typename T>
				void
				operator()(const T t);

				template<int Tag>
				void
				operator()(const unary_expression<Tag>& operation);

				template<int Tag>
				void
				operator()(const binary_expression<Tag>& operation);

				void
				operator()(const conditional_expression& operation);

				template<int Tag>
				void
				operator()(const conversion<Tag>& conv);

				void
				operator()(variable* const& v);

				template<typename T>
				void
				operator()(enum_constant<T>* const constant);

				template<class Function>
				void
				operator()(function_call<Function> const& call);

				template<class Member>
				void
				operator()(member_access_expression<Member> const& expr);

				void
				operator()(const char c);

				void
				operator()(const std::string& str);

				void
				operator()(const std::wstring& str);

			private:
				semantic_graph_serializer& serializer_;
		};
		friend class serialize_expression_visitor;

		class serialize_enum_visitor: public utility::static_visitor<void>
		{
			public:
				serialize_enum_visitor(semantic_graph_serializer& serializer);

				template<typename UnderlyingType>
				void
				operator()(const enum_constant_list<UnderlyingType>& constant_list) const;

			private:
				semantic_graph_serializer& serializer_;
		};
		friend class serialize_enum_visitor;

		void
		serialize_type
		(
			const semantic_entities::type_t& entity
		);

		template<class Namespace>
		void
		serialize_namespace
		(
			const Namespace& entity
		);

		template<class Namespace>
		void
		serialize_unnamed_namespace
		(
			const Namespace& entity
		);

		template<class Class>
		void
		serialize_class
		(
			const Class& entity
		);

		template<class Enum>
		void
		serialize_enum
		(
			const Enum& entity
		);

		void
		serialize_base_class
		(
			const base_class& entity
		);

		void
		serialize_constructor
		(
			const constructor& entity
		);

		void
		serialize_destructor
		(
			const destructor& entity
		);

		void
		serialize_operator_member_function
		(
			const operator_member_function& entity
		);

		void
		serialize_conversion_function
		(
			const conversion_function& entity
		);

		void
		serialize_simple_member_function
		(
			const simple_member_function& entity
		);

		void
		serialize_operator_function
		(
			const operator_function& entity
		);

		void
		serialize_simple_function
		(
			const simple_function& entity
		);

		void
		serialize_function_parameter_list
		(
			const function_parameter_list& entity
		);

		void
		serialize_function_parameter
		(
			const function_parameter& entity
		);

		template<class Variable>
		void
		serialize_variable
		(
			const Variable& entity
		);

		void
		serialize_namespace_alias
		(
			const namespace_alias& entity
		);

		template<class Typedef>
		void
		serialize_typedef
		(
			const Typedef& entity
		);

		void
		serialize_expression
		(
			const semantic_entities::expression_t& entity
		);



		template<class Entity>
		void
		serialize_base_classes
		(
			const Entity& entity,
			typename boost::enable_if<scalpel::cpp::semantic_entities::type_traits::has_base_classes<Entity>>::type* = 0
		);

		template<class Entity>
		void
		serialize_base_classes
		(
			const Entity&,
			typename boost::disable_if<scalpel::cpp::semantic_entities::type_traits::has_base_classes<Entity>>::type* = 0
		)
		{
			//does nothing
		}



		template<class DeclarativeRegion>
		void
		serialize_members
		(
			const DeclarativeRegion& declarative_region
		)
		{
			serialize_members_of_type<namespace_alias>(declarative_region);
			serialize_members_of_type<namespace_>(declarative_region);
			serialize_members_of_type<linked_namespace>(declarative_region);
			serialize_members_of_type<unnamed_namespace>(declarative_region);
			serialize_members_of_type<linked_unnamed_namespace>(declarative_region);
			serialize_members_of_type<class_>(declarative_region);
			serialize_members_of_type<member_class>(declarative_region);
			serialize_members_of_type<union_>(declarative_region);
			serialize_members_of_type<member_union>(declarative_region);
			serialize_members_of_type<anonymous_union>(declarative_region);
			serialize_members_of_type<anonymous_member_union>(declarative_region);
			serialize_members_of_type<enum_>(declarative_region);
			serialize_members_of_type<member_enum>(declarative_region);
			serialize_members_of_type<typedef_>(declarative_region);
			serialize_members_of_type<member_typedef>(declarative_region);
			serialize_members_of_type<constructor>(declarative_region);
			serialize_members_of_type<destructor>(declarative_region);
			serialize_members_of_type<operator_member_function>(declarative_region);
			serialize_members_of_type<conversion_function>(declarative_region);
			serialize_members_of_type<simple_member_function>(declarative_region);
			serialize_members_of_type<operator_function>(declarative_region);
			serialize_members_of_type<simple_function>(declarative_region);
			serialize_members_of_type<variable>(declarative_region);
			serialize_members_of_type<member_variable>(declarative_region);
			serialize_members_of_type<static_member_variable>(declarative_region);
			serialize_members_of_type<bit_field>(declarative_region);
		}

		template<class Entity, class DeclarativeRegion>
		void
		serialize_members_of_type
		(
			const DeclarativeRegion& declarative_region,
			typename boost::enable_if<scalpel::cpp::semantic_entities::type_traits::has_members_of_type<DeclarativeRegion, Entity>>::type* = 0
		)
		{
			using namespace scalpel::cpp::semantic_entities::generic_queries::detail;

			typename get_members_return_type<DeclarativeRegion, Entity, true>::type members =
				get_members<Entity>(declarative_region)
			;

			serialize_entities(members);
		}

		template<class Entity, class DeclarativeRegion>
		void
		serialize_members_of_type
		(
			const DeclarativeRegion&,
			typename boost::disable_if<scalpel::cpp::semantic_entities::type_traits::has_members_of_type<DeclarativeRegion, Entity>>::type* = 0
		)
		{
			//does nothing
		}

		template<class Entity>
		void
		serialize_entities
		(
			const scalpel::utility::unique_ptr_vector<Entity>& entities
		)
		{
			if(!entities.empty())
			{
				writer_.open_array(plural_key_of_type<Entity>::value);
				for(auto i = entities.begin(); i != entities.end(); ++i)
				{
					writer_.open_object();
					serialize_member(*i);
					writer_.close_object();
				}
				writer_.close_array();
			}
		}

		template<class Entity>
		void
		serialize_entities
		(
			scalpel::utility::single_object_const_range<Entity>& entities
		)
		{
			if(!entities.empty())
			{
				writer_.open_object(singular_key_of_type<Entity>::value);
				for(auto i = entities.begin(); i != entities.end(); ++i)
					serialize_member(*i);
				writer_.close_object();
			}
		}

		template<class Entity>
		void
		serialize_member
		(
			const Entity& entity
		);



		template<class DeclarativeRegion>
		void
		serialize_entity_aliases
		(
			const DeclarativeRegion& declarative_region
		)
		{
			serialize_entity_aliases_of_type<namespace_>(declarative_region);
			serialize_entity_aliases_of_type<linked_namespace>(declarative_region);
			serialize_entity_aliases_of_type<unnamed_namespace>(declarative_region);
			serialize_entity_aliases_of_type<linked_unnamed_namespace>(declarative_region);
			serialize_entity_aliases_of_type<class_>(declarative_region);
			serialize_entity_aliases_of_type<member_class>(declarative_region);
			serialize_entity_aliases_of_type<union_>(declarative_region);
			serialize_entity_aliases_of_type<member_union>(declarative_region);
			serialize_entity_aliases_of_type<enum_>(declarative_region);
			serialize_entity_aliases_of_type<member_enum>(declarative_region);
			serialize_entity_aliases_of_type<typedef_>(declarative_region);
			serialize_entity_aliases_of_type<member_typedef>(declarative_region);
			serialize_entity_aliases_of_type<constructor>(declarative_region);
			serialize_entity_aliases_of_type<destructor>(declarative_region);
			serialize_entity_aliases_of_type<operator_member_function>(declarative_region);
			serialize_entity_aliases_of_type<conversion_function>(declarative_region);
			serialize_entity_aliases_of_type<simple_member_function>(declarative_region);
			serialize_entity_aliases_of_type<operator_function>(declarative_region);
			serialize_entity_aliases_of_type<simple_function>(declarative_region);
			serialize_entity_aliases_of_type<variable>(declarative_region);
			serialize_entity_aliases_of_type<member_variable>(declarative_region);
			serialize_entity_aliases_of_type<static_member_variable>(declarative_region);
			serialize_entity_aliases_of_type<bit_field>(declarative_region);
		}

		template<class Entity, class DeclarativeRegion>
		void
		serialize_entity_aliases_of_type
		(
			const DeclarativeRegion& declarative_region,
			typename boost::enable_if<scalpel::cpp::semantic_entities::type_traits::has_entity_aliases_of_type<DeclarativeRegion, Entity>>::type* = 0
		)
		{
			using namespace scalpel::cpp::semantic_entities::generic_queries::detail;

			typename get_entity_aliases_return_type<DeclarativeRegion, Entity, true>::type entity_aliases =
				get_entity_aliases<Entity>(declarative_region)
			;

			if(!entity_aliases.empty())
			{
				writer_.open_array(singular_key_of_type<Entity>::value + std::string(" aliases"));
				for(auto i = entity_aliases.begin(); i != entity_aliases.end(); ++i)
				{
					writer_.open_object();
					serialize_entity_alias(*i);
					writer_.close_object();
				}
				writer_.close_array();
			}
		}

		template<class Entity, class DeclarativeRegion>
		void
		serialize_entity_aliases_of_type
		(
			const DeclarativeRegion&,
			typename boost::disable_if<scalpel::cpp::semantic_entities::type_traits::has_entity_aliases_of_type<DeclarativeRegion, Entity>>::type* = 0
		)
		{
			//does nothing
		}

		template<class Entity>
		void
		serialize_entity_alias
		(
			const entity_alias<Entity>& entity
		)
		{
			writer_.write_key_value_pair("id", get_id_str(entity.referred_entity()));
		}

		template<class Entity>
		void
		serialize_entity_alias
		(
			const member_entity_alias<Entity>& entity
		)
		{
			writer_.write_key_value_pair("id", get_id_str(entity.referred_entity()));
			serialize_access_property(entity);
		}



		//
		//conversions to string
		//

		std::string
		overloadable_operator_to_string(const semantic_entities::overloadable_operator op);



		//
		//attributes
		//

		void
		serialize_class_id_attribute
		(
			const scalpel::cpp::semantic_entities::class_ptr_variant& entity
		);

		template<class Entity>
		void
		serialize_id_attribute(const Entity& entity);

		template<class Entity>
		void
		serialize_overloaded_operator(const Entity& entity);

		template<class Entity>
		void
		serialize_name_property
		(
			const Entity& entity,
			typename boost::enable_if<scalpel::cpp::semantic_entities::type_traits::has_name<Entity>>::type* = 0
		);

		template<class Entity>
		void
		serialize_name_property
		(
			const Entity&,
			typename boost::disable_if<scalpel::cpp::semantic_entities::type_traits::has_name<Entity>>::type* = 0
		)
		{
			//does nothing
		}

		template<class Entity>
		void
		serialize_access_property
		(
			const Entity& entity,
			typename boost::enable_if<scalpel::cpp::semantic_entities::type_traits::is_member<Entity>>::type* = 0
		);

		template<class Entity>
		void
		serialize_access_property
		(
			const Entity&,
			typename boost::disable_if<scalpel::cpp::semantic_entities::type_traits::is_member<Entity>>::type* = 0
		)
		{
			//does nothing
		}

		template<class Entity>
		void
		serialize_static_property
		(
			const Entity& entity,
			typename boost::enable_if<scalpel::cpp::semantic_entities::type_traits::can_be_static<Entity>>::type* = 0
		);

		template<class Entity>
		void
		serialize_static_property
		(
			const Entity&,
			typename boost::disable_if<scalpel::cpp::semantic_entities::type_traits::can_be_static<Entity>>::type* = 0
		)
		{
			//does nothing
		}

		template<class Entity>
		void
		serialize_mutable_property
		(
			const Entity& entity,
			typename boost::enable_if<scalpel::cpp::semantic_entities::type_traits::can_be_mutable<Entity>>::type* = 0
		);

		template<class Entity>
		void
		serialize_mutable_property
		(
			const Entity&,
			typename boost::disable_if<scalpel::cpp::semantic_entities::type_traits::can_be_mutable<Entity>>::type* = 0
		)
		{
			//does nothing
		}

		template<class Entity>
		void
		serialize_bit_field_size_property
		(
			const Entity& entity,
			typename boost::enable_if<boost::is_same<Entity, bit_field>>::type* = 0
		);

		template<class Entity>
		void
		serialize_bit_field_size_property
		(
			const Entity&,
			typename boost::disable_if<boost::is_same<Entity, bit_field>>::type* = 0
		)
		{
			//does nothing
		}



		//
		//ids
		//

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
			set_id_of_members_of_type<union_>(entity);
			set_id_of_members_of_type<member_union>(entity);
			set_id_of_members_of_type<anonymous_union>(entity);
			set_id_of_members_of_type<anonymous_member_union>(entity);
			set_id_of_members_of_type<enum_>(entity);
			set_id_of_members_of_type<member_enum>(entity);
			set_id_of_members_of_type<typedef_>(entity);
			set_id_of_members_of_type<member_typedef>(entity);
			set_id_of_members_of_type<operator_member_function>(entity);
			set_id_of_members_of_type<conversion_function>(entity);
			set_id_of_members_of_type<simple_member_function>(entity);
			set_id_of_members_of_type<operator_function>(entity);
			set_id_of_members_of_type<simple_function>(entity);
			set_id_of_members_of_type<variable>(entity);
			set_id_of_members_of_type<member_variable>(entity);
			set_id_of_members_of_type<static_member_variable>(entity);
			set_id_of_members_of_type<bit_field>(entity);
			set_id_of_members_of_type<enum_constant<int>>(entity);
			set_id_of_members_of_type<enum_constant<unsigned int>>(entity);
			set_id_of_members_of_type<enum_constant<long int>>(entity);
			set_id_of_members_of_type<enum_constant<unsigned long int>>(entity);
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

		//return prefix-#id (e.g. "variable-12")
		template<class Entity>
		std::string
		get_id_str(const Entity& entity) const
		{
			std::ostringstream oss;
			oss << id_prefix<Entity>::value << '-' << get_id(entity);
			return oss.str();
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



		detail::json_writer writer_;
		typename entity_id_map<semantic_entities::namespace_>::type namespace_id_map_;
		typename entity_id_map<semantic_entities::linked_namespace>::type linked_namespace_id_map_;
		typename entity_id_map<semantic_entities::unnamed_namespace>::type unnamed_namespace_id_map_;
		typename entity_id_map<semantic_entities::linked_unnamed_namespace>::type linked_unnamed_namespace_id_map_;
		typename entity_id_map<semantic_entities::class_>::type class_id_map_;
		typename entity_id_map<semantic_entities::member_class>::type member_class_id_map_;
		typename entity_id_map<semantic_entities::union_>::type union_id_map_;
		typename entity_id_map<semantic_entities::member_union>::type member_union_id_map_;
		typename entity_id_map<semantic_entities::anonymous_union>::type anonymous_union_id_map_;
		typename entity_id_map<semantic_entities::anonymous_member_union>::type anonymous_member_union_id_map_;
		typename entity_id_map<semantic_entities::enum_>::type enum_id_map_;
		typename entity_id_map<semantic_entities::member_enum>::type member_enum_id_map_;
		typename entity_id_map<semantic_entities::typedef_>::type typedef_id_map_;
		typename entity_id_map<semantic_entities::member_typedef>::type member_typedef_id_map_;
		typename entity_id_map<semantic_entities::operator_member_function>::type operator_member_function_id_map_;
		typename entity_id_map<semantic_entities::conversion_function>::type conversion_function_id_map_;
		typename entity_id_map<semantic_entities::simple_member_function>::type simple_member_function_id_map_;
		typename entity_id_map<semantic_entities::operator_function>::type operator_function_id_map_;
		typename entity_id_map<semantic_entities::simple_function>::type simple_function_id_map_;
		typename entity_id_map<semantic_entities::variable>::type variable_id_map_;
		typename entity_id_map<semantic_entities::member_variable>::type member_variable_id_map_;
		typename entity_id_map<semantic_entities::static_member_variable>::type static_member_variable_id_map_;
		typename entity_id_map<semantic_entities::bit_field>::type bit_field_id_map_;
		typename entity_id_map<semantic_entities::enum_constant<int>>::type int_enum_constant_id_map_;
		typename entity_id_map<semantic_entities::enum_constant<unsigned int>>::type unsigned_int_enum_constant_id_map_;
		typename entity_id_map<semantic_entities::enum_constant<long int>>::type long_int_enum_constant_id_map_;
		typename entity_id_map<semantic_entities::enum_constant<unsigned long int>>::type unsigned_long_int_enum_constant_id_map_;
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

} //namespace cpp2json

#include "semantic_graph.ipp"

#endif

