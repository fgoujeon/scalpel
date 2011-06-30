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

#ifndef SCALPEL_CPP_SEMANTIC_ANALYSIS_DETAIL_NAME_LOOKUP_IPP
#define SCALPEL_CPP_SEMANTIC_ANALYSIS_DETAIL_NAME_LOOKUP_IPP

#include "semantic_entity_analysis/get_global_namespace.hpp"
#include "semantic_entity_analysis/get_name.hpp"
#include <scalpel/cpp/semantic_entities/generic_queries/detail/has_enclosing_declarative_region.hpp>
#include <scalpel/cpp/semantic_entities/generic_queries/detail/enclosing_declarative_region.hpp>
#include <scalpel/cpp/semantic_entities/generic_queries/detail/get_members.hpp>
#include <scalpel/cpp/semantic_entities/generic_queries/detail/get_entity_aliases.hpp>

namespace scalpel { namespace cpp { namespace semantic_analysis { namespace detail { namespace name_lookup
{

template<class EntityIdentificationPolicy, bool Optional, bool Multiple, class... Entities>
typename return_type<Optional, Multiple, Entities...>::type
find
(
	const typename EntityIdentificationPolicy::identifier_t& identifier,
	semantic_entities::declarative_region_t current_declarative_region
)
{
	using namespace detail;
	using namespace semantic_entities;

	//used for applying using directives
	namespace_association_map namespace_associations;

	//indirectly returned object
	typename return_type<true, true, Entities...>::type found_entities;

	//find entities from current to outermost declarative region
	//(i.e. the global namespace)
	while(true)
	{
		//apply using directives (only for namespaces and statement blocks)
		if(namespace_** opt_namespace_ptr = utility::get<namespace_*>(&current_declarative_region))
			apply_using_directives
			(
				**opt_namespace_ptr,
				(*opt_namespace_ptr)->using_directive_namespaces(),
				(*opt_namespace_ptr)->get_unnamed_namespace(),
				namespace_associations
			);
		else if(unnamed_namespace** opt_namespace_ptr = utility::get<unnamed_namespace*>(&current_declarative_region))
			apply_using_directives
			(
				**opt_namespace_ptr,
				(*opt_namespace_ptr)->using_directive_namespaces(),
				(*opt_namespace_ptr)->get_unnamed_namespace(),
				namespace_associations
			);
		else if(statement_block** opt_statement_block_ptr = utility::get<statement_block*>(&current_declarative_region))
			apply_using_directives
			(
				**opt_statement_block_ptr,
				(*opt_statement_block_ptr)->using_directive_namespaces(),
				0,
				namespace_associations
			);

		//find entities in this declarative region only
		add_to_result
		(
			found_entities,
			find_local_entities
			<
				EntityIdentificationPolicy,
				declarative_region_t,
				true,
				Multiple,
				Entities...
			>(identifier, current_declarative_region)
		);

		//find entities in the associated namespaces (only for namespaces)
		//and add them to the previously found entities
		if(namespace_** opt_namespace_ptr = utility::get<namespace_*>(&current_declarative_region))
		{
			auto associated_namespaces_it = namespace_associations.find(*opt_namespace_ptr);
			if(associated_namespaces_it != namespace_associations.end())
			{
				//for each associated namespace
				const std::vector<namespace_*>& associated_namespaces =
					associated_namespaces_it->second.namespaces
				;
				for(auto i = associated_namespaces.begin(); i != associated_namespaces.end(); ++i)
				{
					namespace_& associated_namespace = **i;

					add_to_result
					(
						found_entities,
						find_local_entities
						<
							EntityIdentificationPolicy,
							namespace_,
							true,
							Multiple,
							Entities...
						>(identifier, associated_namespace)
					);
				}

				//for each associated unnamed namespace
				const std::vector<unnamed_namespace*>& associated_unnamed_namespaces =
					associated_namespaces_it->second.unnamed_namespaces
				;
				for(auto i = associated_unnamed_namespaces.begin(); i != associated_unnamed_namespaces.end(); ++i)
				{
					unnamed_namespace& associated_unnamed_namespace = **i;

					add_to_result
					(
						found_entities,
						find_local_entities
						<
							EntityIdentificationPolicy,
							unnamed_namespace,
							true,
							Multiple,
							Entities...
						>(identifier, associated_unnamed_namespace)
					);
				}
			}
		}

		//stop lookup if entities have been found
		if(!utility::is_empty(found_entities)) break;

		//find entities in the base classes (only for classes)
		if(class_** opt_class_ptr = utility::get<class_*>(&current_declarative_region))
		{
			class_& class_entity = **opt_class_ptr;

			add_to_result
			(
				found_entities,
				find_entities_in_base_classes
				<
					EntityIdentificationPolicy,
					class_,
					true,
					Multiple,
					Entities...
				>(identifier, class_entity)
			);

			//stop lookup if entities have been found
			if(!utility::is_empty(found_entities)) break;
		}
		else if(member_class** opt_class_ptr = utility::get<member_class*>(&current_declarative_region))
		{
			member_class& class_entity = **opt_class_ptr;

			add_to_result
			(
				found_entities,
				find_entities_in_base_classes
				<
					EntityIdentificationPolicy,
					member_class,
					true,
					Multiple,
					Entities...
				>(identifier, class_entity)
			);

			//stop lookup if entities have been found
			if(!utility::is_empty(found_entities)) break;
		}

		//iterate to the enclosing declarative region
		if(!has_enclosing_declarative_region(current_declarative_region)) break;
		current_declarative_region = get_enclosing_declarative_region(current_declarative_region);
	}

	return std::move(return_result<Optional, Multiple, Entities...>::result(found_entities));
}

template<class EntityIdentificationPolicy, bool Optional, bool Multiple, class... Entities>
typename return_type<Optional, Multiple, Entities...>::type
find
(
	const bool has_leading_double_colon,
	const syntax_nodes::optional_node<syntax_nodes::nested_name_specifier>& opt_nested_name_specifier_node,
	const typename EntityIdentificationPolicy::identifier_t& identifier,
	const semantic_entities::declarative_region_t& current_declarative_region,
	const bool apply_using_directives_for_unqualified_id_part
)
{
	using namespace detail;
	using namespace semantic_entities;

	//Check whether the given qualified identifier is really qualified.
	//If not, perform a simple unqualified name lookup.
	if
	(
		!has_leading_double_colon &&
		!opt_nested_name_specifier_node
	)
	{
		return
			find
			<
				EntityIdentificationPolicy,
				Optional,
				Multiple,
				Entities...
			>(identifier, current_declarative_region)
		;
	}

	//Find the last declarative region of the nested identifier specifier
	//(i.e. Z in "[::]X::Y::Z::").
	open_declarative_region_t last_declarative_region =
		find_declarative_region
		(
			has_leading_double_colon,
			opt_nested_name_specifier_node,
			current_declarative_region
		)
	;

	//find entities in the last declarative region
	if(apply_using_directives_for_unqualified_id_part)
	{
		if(namespace_** opt_namespace_ptr = utility::get<namespace_*>(&last_declarative_region))
		{
			return
				find_in_namespace
				<
					EntityIdentificationPolicy,
					Optional,
					Multiple,
					Entities...
				>(identifier, **opt_namespace_ptr)
			;
		}
	}

	//find entities in the last declarative region
	typename return_type<true, Multiple, Entities...>::type found_entities =
		find_local_entities
		<
			EntityIdentificationPolicy,
			open_declarative_region_t,
			true,
			Multiple,
			Entities...
		>(identifier, last_declarative_region)
	;
	//stop lookup if entities have been found
	if(!utility::is_empty(found_entities))
		return return_result<Optional, Multiple, Entities...>::result(found_entities);

	//find entities in the base classes of the last declarative region (if any)
	if(class_** opt_class_ptr = utility::get<class_*>(&last_declarative_region))
	{
		class_& class_entity = **opt_class_ptr;

		return
			find_entities_in_base_classes
			<
				EntityIdentificationPolicy,
				class_,
				Optional,
				Multiple,
				Entities...
			>(identifier, class_entity)
		;
	}
	else if(member_class** opt_class_ptr = utility::get<member_class*>(&last_declarative_region))
	{
		member_class& class_entity = **opt_class_ptr;

		return
			find_entities_in_base_classes
			<
				EntityIdentificationPolicy,
				member_class,
				Optional,
				Multiple,
				Entities...
			>(identifier, class_entity)
		;
	}

	return return_result<Optional, Multiple, Entities...>::result(found_entities);
}

template<class EntityIdentificationPolicy, class DeclarativeRegion, bool Optional, bool Multiple, class... Entities>
typename return_type<Optional, Multiple, Entities...>::type
find_local
(
	const typename EntityIdentificationPolicy::identifier_t& identifier,
	DeclarativeRegion& current_declarative_region
)
{
	return
		detail::find_local_entities
		<
			EntityIdentificationPolicy,
			DeclarativeRegion,
			Optional,
			Multiple,
			Entities...
		>(identifier, current_declarative_region)
	;
}



namespace detail
{

template<class EntityIdentificationPolicy, bool Optional, bool Multiple, class... Entities, class Namespace>
typename return_type<Optional, Multiple, Entities...>::type
find_in_namespace
(
	const typename EntityIdentificationPolicy::identifier_t& identifier,
	Namespace& current_namespace
)
{
	std::vector<semantic_entities::namespace_*> already_searched_namespaces;
	return
		find_in_namespace
		<
			EntityIdentificationPolicy,
			Optional,
			Multiple,
			Entities...
		>
		(
			identifier,
			current_namespace,
			already_searched_namespaces
		)
	;
}

inline
void
add_to_if_namespace
(
	std::vector<semantic_entities::namespace_*>& namespaces,
	semantic_entities::namespace_& n
)
{
	namespaces.push_back(&n);
}

inline
void
add_to_if_namespace
(
	std::vector<semantic_entities::namespace_*>&,
	semantic_entities::unnamed_namespace&
)
{
}

template<class EntityIdentificationPolicy, bool Optional, bool Multiple, class... Entities, class Namespace>
typename return_type<Optional, Multiple, Entities...>::type
find_in_namespace
(
	const typename EntityIdentificationPolicy::identifier_t& identifier,
	Namespace& current_namespace,
	std::vector<semantic_entities::namespace_*>& already_searched_namespaces
)
{
	using namespace semantic_entities;

	typename return_type<true, true, Entities...>::type found_entities;

	//search in the current namespace
	{
		add_to_if_namespace(already_searched_namespaces, current_namespace);

		typename return_type<true, Multiple, Entities...>::type found_entities =
			find_local_entities
			<
				EntityIdentificationPolicy,
				Namespace,
				true,
				Multiple,
				Entities...
			>(identifier, current_namespace)
		;

		//if entities have been found, return them
		if(!utility::is_empty(found_entities))
			return std::move(return_result<Optional, Multiple, Entities...>::result(found_entities));
	}

	//search in the unnamed namespace of the current namespace
	if(unnamed_namespace* opt_unnamed_namespace = current_namespace.get_unnamed_namespace())
	{
		add_to_result
		(
			found_entities,
			find_in_namespace<EntityIdentificationPolicy, true, Multiple, Entities...>
			(
				identifier,
				*opt_unnamed_namespace,
				already_searched_namespaces
			)
		);
	}

	//if no entity is found, search in the using directive namespaces of the current namespace
	for
	(
		auto i = current_namespace.using_directive_namespaces().begin();
		i != current_namespace.using_directive_namespaces().end();
		++i
	)
	{
		semantic_entities::namespace_& using_directive_namespace = **i;

		//make sure the namespace has not been already searched
		if
		(
			std::find
			(
				already_searched_namespaces.begin(),
				already_searched_namespaces.end(),
				&using_directive_namespace
			) == already_searched_namespaces.end()
		)
		{
			add_to_result
			(
				found_entities,
				find_in_namespace<EntityIdentificationPolicy, true, Multiple, Entities...>
				(
					identifier,
					using_directive_namespace,
					already_searched_namespaces
				)
			);
		}
	}

	return std::move(return_result<Optional, Multiple, Entities...>::result(found_entities));
}



template<class EntityIdentificationPolicy, class DeclarativeRegion, bool Optional, bool Multiple, class Entity, class Entity2, class... Entities>
typename return_type<Optional, Multiple, Entity, Entity2, Entities...>::type
find_local_entities
(
	const typename EntityIdentificationPolicy::identifier_t& identifier,
	DeclarativeRegion& current_declarative_region
)
{
	typename return_type<true, Multiple, Entity, Entity2, Entities...>::type found_entities;

	find_variadic_local_entities
	<
		EntityIdentificationPolicy,
		DeclarativeRegion,
		Optional,
		Multiple,
		typename return_type<true, Multiple, Entity, Entity2, Entities...>::type,
		Entity,
		Entity2,
		Entities...
	>::find(identifier, current_declarative_region, found_entities);

	return return_result<Optional, Multiple, Entity, Entity2, Entities...>::result(found_entities);
}

template<class EntityIdentificationPolicy, class DeclarativeRegion, bool Optional, bool Multiple, class Entity>
typename return_type<Optional, Multiple, Entity>::type
find_local_entities
(
	const typename EntityIdentificationPolicy::identifier_t& identifier,
	DeclarativeRegion& current_declarative_region
)
{
	return
		find_single_type_local_entities
		<
			EntityIdentificationPolicy,
			DeclarativeRegion,
			Optional,
			Multiple,
			Entity
		>::find(identifier, current_declarative_region)
	;
}

template<class EntityIdentificationPolicy, class DeclarativeRegion, bool Optional, bool Multiple, class ReturnT>
void
find_variadic_local_entities<EntityIdentificationPolicy, DeclarativeRegion, Optional, Multiple, ReturnT>::find
(
	const typename EntityIdentificationPolicy::identifier_t&,
	DeclarativeRegion&,
	ReturnT&
)
{
	//does nothing
}

template<class EntityIdentificationPolicy, class DeclarativeRegion, bool Optional, bool Multiple, class ReturnT, class Entity, class... Entities>
void
find_variadic_local_entities<EntityIdentificationPolicy, DeclarativeRegion, Optional, Multiple, ReturnT, Entity, Entities...>::find
(
	const typename EntityIdentificationPolicy::identifier_t& identifier,
	DeclarativeRegion& current_declarative_region,
	ReturnT& found_entities
)
{
	//find entities of type Entity in the current declarative region
	typename return_type<Optional, Multiple, Entity>::type entities =
		find_local_entities
		<
			EntityIdentificationPolicy,
			DeclarativeRegion,
			true,
			Multiple,
			Entity
		>(identifier, current_declarative_region)
	;

	//if entities have been found...
	if(!utility::is_empty(entities))
	{
		//... add them to the list...
		add_to_result(found_entities, entities);

		//and stop if we want a single entity
		if(!Multiple) return;
	}

	//recursive call for other types of Entities
	find_variadic_local_entities
	<
		EntityIdentificationPolicy,
		DeclarativeRegion,
		true,
		Multiple,
		ReturnT,
		Entities...
	>::find(identifier, current_declarative_region, found_entities);
}

template<class EntityIdentificationPolicy, class DeclarativeRegion, bool Optional, bool Multiple>
typename return_type<Optional, Multiple, semantic_entities::open_declarative_region_t>::type
find_single_type_local_entities<EntityIdentificationPolicy, DeclarativeRegion, Optional, Multiple, semantic_entities::open_declarative_region_t>::find
(
	const typename EntityIdentificationPolicy::identifier_t& identifier,
	DeclarativeRegion& current_declarative_region
)
{
	using namespace semantic_entities;

	return
		find_local_entities
		<
			EntityIdentificationPolicy,
			DeclarativeRegion,
			Optional,
			Multiple,

			//open_declarative_region_t types
			//TODO: this is redundant, it might be possible to fix this
			//redundance using template aliases
			namespace_,
			namespace_alias,
			class_,
			member_class,
			union_,
			member_union,
			typedef_
		>
		(
			identifier,
			current_declarative_region
		)
	;
}

template<class EntityIdentificationPolicy, class DeclarativeRegion, bool Optional, bool Multiple, class Entity>
typename return_type<Optional, Multiple, Entity>::type
find_single_type_local_entities<EntityIdentificationPolicy, DeclarativeRegion, Optional, Multiple, Entity>::find
(
	const typename EntityIdentificationPolicy::identifier_t& identifier,
	DeclarativeRegion& current_declarative_region
)
{
	using namespace semantic_entity_analysis;
	using namespace semantic_entities;

	typename return_type<true, Multiple, Entity>::type found_entities;
	initialize<typename return_type<true, Multiple, Entity>::type>::init(found_entities);

	find_local_entities2
	<
		EntityIdentificationPolicy,
		Optional,
		Multiple,
		Entity,
		DeclarativeRegion
	>::find
	(
		identifier,
		current_declarative_region,
		found_entities
	);

	return std::move(return_result<Optional, Multiple, Entity>::result(found_entities));
}



template<class EntityIdentificationPolicy, bool Optional, bool Multiple, class Entity>
class find_local_entities2_visitor: public utility::static_visitor<void>
{
	public:
		find_local_entities2_visitor
		(
			const typename EntityIdentificationPolicy::identifier_t& identifier,
			typename return_type<Optional, Multiple, Entity>::type& found_entities
		):
			identifier_(identifier),
			found_entities_(found_entities)
		{
		}

		template<class DeclarativeRegion>
		void
		operator()(DeclarativeRegion* current_declarative_region)
		{
			find_local_entities2
			<
				EntityIdentificationPolicy,
				Optional,
				Multiple,
				Entity,
				DeclarativeRegion
			>::find
			(
				identifier_,
				*current_declarative_region,
				found_entities_
			);
		}

		void
		operator()(const semantic_entities::cv_qualified_type& current_declarative_region)
		{
			apply_visitor(*this, current_declarative_region.qualified_type());
		}

		//non-declarative-region types
		template<class DeclarativeRegion>
		void
		operator()(const DeclarativeRegion&)
		{
			assert(false);
		}

	private:
		const typename EntityIdentificationPolicy::identifier_t& identifier_;
		typename return_type<Optional, Multiple, Entity>::type& found_entities_;
};

template<class EntityIdentificationPolicy, bool Optional, bool Multiple, class Entity, class... DeclarativeRegions>
void
find_local_entities2<EntityIdentificationPolicy, Optional, Multiple, Entity, utility::variant<DeclarativeRegions...>>::find
(
	const typename EntityIdentificationPolicy::identifier_t& identifier,
	utility::variant<DeclarativeRegions...>& current_declarative_region,
	typename return_type<Optional, Multiple, Entity>::type& found_entities
)
{
	find_local_entities2_visitor
	<
		EntityIdentificationPolicy,
		Optional,
		Multiple,
		Entity
	> visitor(identifier, found_entities);
	apply_visitor(visitor, current_declarative_region);
}

template<class EntityIdentificationPolicy, bool Optional, bool Multiple, class Entity>
void
find_local_entities2<EntityIdentificationPolicy, Optional, Multiple, Entity, semantic_entities::typedef_>::find
(
	const typename EntityIdentificationPolicy::identifier_t& identifier,
	semantic_entities::typedef_& current_declarative_region,
	typename return_type<Optional, Multiple, Entity>::type& found_entities
)
{
	find_local_entities2_visitor
	<
		EntityIdentificationPolicy,
		Optional,
		Multiple,
		Entity
	> visitor(identifier, found_entities);
	apply_visitor(visitor, current_declarative_region.type());
}

template<class EntityIdentificationPolicy, bool Optional, bool Multiple, class Entity>
void
find_local_entities2<EntityIdentificationPolicy, Optional, Multiple, Entity, semantic_entities::member_typedef>::find
(
	const typename EntityIdentificationPolicy::identifier_t& identifier,
	semantic_entities::member_typedef& current_declarative_region,
	typename return_type<Optional, Multiple, Entity>::type& found_entities
)
{
	find_local_entities2_visitor
	<
		EntityIdentificationPolicy,
		Optional,
		Multiple,
		Entity
	> visitor(identifier, found_entities);
	apply_visitor(visitor, current_declarative_region.type());
}

template<class EntityIdentificationPolicy, bool Optional, bool Multiple, class Entity>
void
find_local_entities2<EntityIdentificationPolicy, Optional, Multiple, Entity, semantic_entities::namespace_alias>::find
(
	const typename EntityIdentificationPolicy::identifier_t& identifier,
	semantic_entities::namespace_alias& current_declarative_region,
	typename return_type<Optional, Multiple, Entity>::type& found_entities
)
{
	find_in_declarative_region_members
	<
		EntityIdentificationPolicy,
		Optional,
		Multiple,
		Entity,
		semantic_entities::namespace_
	>
	(
		identifier,
		current_declarative_region.referred_namespace(),
		found_entities
	);
}

template<class EntityIdentificationPolicy, bool Optional, bool Multiple, class Entity, class DeclarativeRegion>
void
find_local_entities2<EntityIdentificationPolicy, Optional, Multiple, Entity, DeclarativeRegion>::find
(
	const typename EntityIdentificationPolicy::identifier_t& identifier,
	DeclarativeRegion& current_declarative_region,
	typename return_type<Optional, Multiple, Entity>::type& found_entities
)
{
	find_in_declarative_region_members
	<
		EntityIdentificationPolicy,
		Optional,
		Multiple,
		Entity,
		DeclarativeRegion
	>
	(
		identifier,
		current_declarative_region,
		found_entities
	);

	if(!Multiple && !utility::is_empty(found_entities))
		return;

	find_in_declarative_region_entity_aliases
	<
		EntityIdentificationPolicy,
		Optional,
		Multiple,
		Entity,
		DeclarativeRegion
	>
	(
		identifier,
		current_declarative_region,
		found_entities
	);
}



template<class EntityIdentificationPolicy, bool Optional, bool Multiple, class Entity, class DeclarativeRegion>
void
find_in_declarative_region_members
(
	const typename EntityIdentificationPolicy::identifier_t& identifier,
	DeclarativeRegion& current_declarative_region,
	typename return_type<Optional, Multiple, Entity>::type& found_entities,
	typename boost::enable_if<semantic_entities::type_traits::has_members_of_type<DeclarativeRegion, Entity>>::type*
)
{
	typename semantic_entities::generic_queries::detail::get_members_return_type<DeclarativeRegion, Entity, false>::type members =
		semantic_entities::generic_queries::detail::get_members<Entity>(current_declarative_region)
	;
	for(auto i = members.begin(); i != members.end(); ++i)
	{
		Entity& current_entity = *i;
		if(EntityIdentificationPolicy::are_identifiers_equal(current_entity, identifier))
		{
			add_to_result(found_entities, current_entity);
			if(!Multiple) break;
		}
	}
}

template<class EntityIdentificationPolicy, bool Optional, bool Multiple, class Entity, class DeclarativeRegion>
void
find_in_declarative_region_members
(
	const typename EntityIdentificationPolicy::identifier_t&,
	DeclarativeRegion&,
	typename return_type<Optional, Multiple, Entity>::type&,
	typename boost::disable_if<semantic_entities::type_traits::has_members_of_type<DeclarativeRegion, Entity>>::type*
)
{
	//does nothing
}



template<class EntityIdentificationPolicy, bool Optional, bool Multiple, class Entity, class DeclarativeRegion>
void
find_in_declarative_region_entity_aliases
(
	const typename EntityIdentificationPolicy::identifier_t& identifier,
	DeclarativeRegion& current_declarative_region,
	typename return_type<Optional, Multiple, Entity>::type& found_entities,
	typename boost::enable_if<semantic_entities::type_traits::has_entity_aliases_of_type<DeclarativeRegion, Entity>>::type*
)
{
	typename semantic_entities::generic_queries::detail::get_entity_aliases_return_type<DeclarativeRegion, Entity, false>::type members =
		semantic_entities::generic_queries::detail::get_entity_aliases<Entity>(current_declarative_region)
	;
	for(auto i = members.begin(); i != members.end(); ++i)
	{
		Entity& current_entity = i->referred_entity();
		if(EntityIdentificationPolicy::are_identifiers_equal(current_entity, identifier))
		{
			add_to_result(found_entities, current_entity);
			if(!Multiple) break;
		}
	}
}

template<class EntityIdentificationPolicy, bool Optional, bool Multiple, class Entity, class DeclarativeRegion>
void
find_in_declarative_region_entity_aliases
(
	const typename EntityIdentificationPolicy::identifier_t&,
	DeclarativeRegion&,
	typename return_type<Optional, Multiple, Entity>::type&,
	typename boost::disable_if<semantic_entities::type_traits::has_entity_aliases_of_type<DeclarativeRegion, Entity>>::type*
)
{
	//does nothing
}



template<class EntityIdentificationPolicy, class Class, bool Optional, bool Multiple, class... Entities>
typename return_type<Optional, Multiple, Entities...>::type
find_entities_in_base_classes
(
	const typename EntityIdentificationPolicy::identifier_t& identifier,
	Class& class_entity
)
{
	using namespace semantic_entity_analysis;
	using namespace semantic_entities;

	typename return_type<Optional, true, Entities...>::type found_entities;

	const std::vector<semantic_entities::base_class>& base_classes =
		class_entity.base_classes()
	;
	for(auto i = base_classes.begin(); i != base_classes.end(); ++i)
	{
		const class_ptr_variant& current_class = i->base();

		if(class_* const* opt = utility::get<class_*>(&current_class))
		{
			class_& current_class = **opt;

			//find entities in the current declarative region (i.e. current class)
			typename return_type<Optional, Multiple, Entities...>::type current_class_found_entities =
				find_local_entities
				<
					EntityIdentificationPolicy,
					semantic_entities::class_,
					Optional,
					Multiple,
					Entities...
				>(identifier, current_class)
			;

			//entities found?
			if(!utility::is_empty(current_class_found_entities))
			{
				//add them to the list
				add_to_result(found_entities, current_class_found_entities);
			}
			else
			{
				//find entities in the base classes of the current declarative region
				typename return_type<Optional, Multiple, Entities...>::type current_class_base_classes_found_entities =
					find_entities_in_base_classes
					<
						EntityIdentificationPolicy,
						class_,
						Optional,
						Multiple,
						Entities...
					>(identifier, current_class)
				;

				//add them to the list
				add_to_result(found_entities, current_class_base_classes_found_entities);
			}
		}
		else if(member_class* const* opt = utility::get<member_class*>(&current_class))
		{
			member_class& current_class = **opt;

			//find entities in the current declarative region (i.e. current class)
			typename return_type<Optional, Multiple, Entities...>::type current_class_found_entities =
				find_local_entities
				<
					EntityIdentificationPolicy,
					semantic_entities::member_class,
					Optional,
					Multiple,
					Entities...
				>(identifier, current_class)
			;

			//entities found?
			if(!utility::is_empty(current_class_found_entities))
			{
				//add them to the list
				add_to_result(found_entities, current_class_found_entities);
			}
			else
			{
				//find entities in the current declarative region's base classes
				typename return_type<Optional, Multiple, Entities...>::type current_class_base_classes_found_entities =
					find_entities_in_base_classes
					<
						EntityIdentificationPolicy,
						member_class,
						Optional,
						Multiple,
						Entities...
					>(identifier, current_class)
				;

				//add them to the list
				add_to_result(found_entities, current_class_base_classes_found_entities);
			}
		}
	}

	//If Multiple, return the full list.
	//If not Multiple, return the only one element of the list.
	return std::move(return_result<Optional, Multiple, Entities...>::result(found_entities));
}

template<class DeclarativeRegion>
void
apply_using_directives
(
	DeclarativeRegion& declarative_region,
	const std::vector<semantic_entities::namespace_*>& using_directive_namespaces,
	semantic_entities::unnamed_namespace* opt_unnamed_namespace,
	namespace_association_map& namespace_associations
)
{
	using namespace semantic_entities;

	//for each using directive's namespace...
	for
	(
		auto i = using_directive_namespaces.begin();
		i != using_directive_namespaces.end();
		++i
	)
	{
		semantic_entities::namespace_& current_using_directive_namespace = **i;

		//find the common enclosing namespace
		namespace_ptr_variant common_enclosing_namespace =
			find_common_enclosing_namespace(declarative_region, &current_using_directive_namespace)
		;

		//associate the using directive's namespace to the common enclosing namespace
		namespace_associations[common_enclosing_namespace].namespaces.push_back(&current_using_directive_namespace);

		//process recursively with the using directive's namespaces of the using directive's namespace
		apply_using_directives
		(
			declarative_region,
			current_using_directive_namespace.using_directive_namespaces(),
			current_using_directive_namespace.get_unnamed_namespace(),
			namespace_associations
		);
	}

	//unnamed namespace
	if(opt_unnamed_namespace)
	{
		//find the common enclosing namespace
		namespace_ptr_variant common_enclosing_namespace =
			find_common_enclosing_namespace(declarative_region, opt_unnamed_namespace)
		;

		//associate the using directive's namespace to the common enclosing namespace
		namespace_associations[common_enclosing_namespace].unnamed_namespaces.push_back(opt_unnamed_namespace);

		//process recursively with the child unnamed namespace and the using directive's namespaces
		apply_using_directives
		(
			declarative_region,
			opt_unnamed_namespace->using_directive_namespaces(),
			opt_unnamed_namespace->get_unnamed_namespace(),
			namespace_associations
		);
	}
}

template<class DeclarativeRegion>
semantic_entities::namespace_ptr_variant
find_common_enclosing_namespace
(
	DeclarativeRegion& a,
	const semantic_entities::namespace_ptr_variant& b
)
{
	using namespace semantic_entities;

	declarative_region_t current_declarative_region_a = &a;
	while(true) //from a to outermost declarative region...
	{
		namespace_** opt_namespace_ptr_a = utility::get<namespace_*>(&current_declarative_region_a);
		unnamed_namespace** opt_unnamed_namespace_ptr_a = utility::get<unnamed_namespace*>(&current_declarative_region_a);

		if(opt_namespace_ptr_a || opt_unnamed_namespace_ptr_a) //if the current enclosing declarative region of a is a namespace...
		{
			namespace_ptr_variant current_namespace_a =
				opt_namespace_ptr_a ?
				namespace_ptr_variant(*opt_namespace_ptr_a) :
				namespace_ptr_variant(*opt_unnamed_namespace_ptr_a)
			;
			namespace_ptr_variant current_namespace_b = b;
			while(true) //from b to outermost namespace...
			{
				if(current_namespace_a == current_namespace_b)
					return current_namespace_a;

				//iterate to the enclosing namespace
				if(!generic_queries::detail::has_enclosing_declarative_region(current_namespace_b)) break;
				current_namespace_b = generic_queries::detail::enclosing_declarative_region(current_namespace_b);
			}
		}

		//iterate to the enclosing declarative region
		if(!has_enclosing_declarative_region(current_declarative_region_a)) break;
		current_declarative_region_a = get_enclosing_declarative_region(current_declarative_region_a);
	}

	throw std::runtime_error("find_common_enclosing_namespace() error: the given declarative regions don't have a common namespace");
}



template<class T>
void
add_to_result(T*& result, T& entity)
{
	result = &entity;
}

template<class T>
void
add_to_result(std::set<T*>& result, T* entity)
{
	if(entity) result.insert(entity);
}

template<class T>
void
add_to_result(std::set<T*>& result, T& entity)
{
	result.insert(&entity);
}

template<class T>
void
add_to_result(std::set<T*>& result, const std::set<T*>& entities)
{
	std::copy
	(
		entities.begin(),
		entities.end(),
		std::insert_iterator<std::set<T*>>(result, result.end())
	);
}

template<class T>
void
add_to_result(std::set<T>& result, const boost::optional<T>& entity)
{
	if(entity) result.insert(*entity);
}

template<class T>
inline
void
add_to_result(std::set<T>& result, const T& entity)
{
	result.insert(entity);
}

template<class T>
void
add_to_result(boost::optional<T>& result, const T& entity)
{
	result = entity;
}

template<class T, class... Ts>
void
add_to_result
(
	boost::optional<utility::variant<Ts...>>& result,
	T* entity
)
{
	result = utility::variant<Ts...>(entity);
}



template<class... Entities>
typename return_type<true, false, Entities...>::type
return_result<true, false, Entities...>::result(typename return_type<true, true, Entities...>::type& result)
{
	if(result.empty())
	{
		return typename return_type<true, false, Entities...>::type(); //empty result
	}
	else if(result.size() == 1)
	{
		return *result.begin();
	}
	else
	{
		throw std::runtime_error("more than one entities found");
	}
}

template<class... Entities>
typename return_type<true, false, Entities...>::type
return_result<true, false, Entities...>::result(typename return_type<true, false, Entities...>::type& result)
{
	return result;
}

template<class... Entities>
typename return_type<false, false, Entities...>::type
return_result<false, false, Entities...>::result(typename return_type<false, true, Entities...>::type& result)
{
	if(result.empty())
	{
		throw std::runtime_error("no entity found");
	}
	else if(result.size() == 1)
	{
		return *result.begin();
	}
	else
	{
		throw std::runtime_error("more than one entities found");
	}
}

template<class... Entities>
typename return_type<false, false, Entities...>::type
return_result<false, false, Entities...>::result(typename return_type<true, false, Entities...>::type& result)
{
	if(!result)
		throw std::runtime_error("no entity found");
	return result;
}

template<class... Entities>
typename return_type<false, false, utility::variant<Entities...>>::type
return_result<false, false, utility::variant<Entities...>>::result
(
	typename return_type<false, true, utility::variant<Entities...>>::type& result
)
{
	if(result.empty())
	{
		throw std::runtime_error("no entity found");
	}
	else if(result.size() == 1)
	{
		return *result.begin();
	}
	else
	{
		throw std::runtime_error("more than one entities found");
	}
}

template<class... Entities>
typename return_type<false, false, utility::variant<Entities...>>::type
return_result<false, false, utility::variant<Entities...>>::result
(
	typename return_type<true, false, utility::variant<Entities...>>::type& result
)
{
	if(!result)
		throw std::runtime_error("no entity found");
	return *result;
}


template<class Entity, class Entity2, class... Entities>
typename return_type<false, false, Entity, Entity2, Entities...>::type
return_result<false, false, Entity, Entity2, Entities...>::result
(
	typename return_type<false, true, Entity, Entity2, Entities...>::type& result
)
{
	if(result.empty())
	{
		throw std::runtime_error("no entity found");
	}
	else if(result.size() == 1)
	{
		return *result.begin();
	}
	else
	{
		throw std::runtime_error("more than one entities found");
	}
}

template<class Entity, class Entity2, class... Entities>
typename return_type<false, false, Entity, Entity2, Entities...>::type
return_result<false, false, Entity, Entity2, Entities...>::result
(
	typename return_type<true, false, Entity, Entity2, Entities...>::type& result
)
{
	if(!result)
		throw std::runtime_error("no entity found");
	return *result;
}

template<class... Entities>
typename return_type<true, true, Entities...>::type&
return_result<true, true, Entities...>::result(typename return_type<true, true, Entities...>::type& result)
{
	return result;
}

template<class... Entities>
typename return_type<false, true, Entities...>::type&
return_result<false, true, Entities...>::result(typename return_type<true, true, Entities...>::type& result)
{
	if(result.empty())
		throw std::runtime_error("no entity found");
	return result;
}

} //namespace detail

}}}}} //namespace scalpel::cpp::semantic_analysis::detail::name_lookup

#endif

