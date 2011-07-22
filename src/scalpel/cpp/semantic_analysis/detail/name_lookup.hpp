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

#ifndef SCALPEL_CPP_SEMANTIC_ANALYSIS_DETAIL_NAME_LOOKUP_HPP
#define SCALPEL_CPP_SEMANTIC_ANALYSIS_DETAIL_NAME_LOOKUP_HPP

#include "semantic_entity_analysis/identification_policies.hpp"
#include <scalpel/cpp/semantic_entities/type_traits/has_members_of_type.hpp>
#include <scalpel/cpp/semantic_entities/type_traits/has_entity_aliases_of_type.hpp>
#include <scalpel/cpp/semantic_graph.hpp>
#include <scalpel/cpp/syntax_tree.hpp>
#include <scalpel/utility/is_empty.hpp>
#include <scalpel/utility/ptr_variant.hpp>
#include <scalpel/utility/variant.hpp>
#include <boost/optional.hpp>
#include <string>
#include <set>
#include <vector>
#include <memory>
#include <sstream>

namespace scalpel { namespace cpp { namespace semantic_analysis { namespace detail { namespace name_lookup
{

/*
result_type's truth table:

 --------------------------------------------------------------
| Variadic | Variant | Multiple | Optional | result_type::type |
|----------|---------|----------|----------|-------------------|
|     0    |    0    |     0    |     X    |        (1)        |
|     0    |    0    |     1    |     X    |        (2)        |
|     0    |    1    |     0    |     0    |        (3)        |
|     0    |    1    |     0    |     1    |        (4)        |
|     0    |    1    |     1    |     X    |        (5)        |
|     1    |    0    |     0    |     0    |        (6)        |
|     1    |    0    |     0    |     1    |        (7)        |
|     1    |    0    |     1    |     X    |        (8)        |
|     1    |    1    |     X    |     X    |        (E)        |
 --------------------------------------------------------------

(1) Entity*
(2) std::set<(1)>
(3) utility::variant<Entities...>
(4) boost::optional<(3)>
(5) std::set<(3)>
(6) utility::ptr_variant<Entities...>
(7) boost::optional<(6)>
(8) std::set<(6)>
(E) Error
*/

template<bool Optional, bool Multiple, class... Entities>
struct return_type;

//(1)
template<bool Optional, class Entity>
struct return_type<Optional, false, Entity>
{
	typedef Entity* type;
};

//(2)
template<bool Optional, class Entity>
struct return_type<Optional, true, Entity>
{
	typedef std::set<Entity*> type;
};

//(3)
template<class... Entities>
struct return_type<false, false, utility::variant<Entities...>>
{
	typedef utility::variant<Entities...> type;
};

//(4)
template<class... Entities>
struct return_type<true, false, utility::variant<Entities...>>
{
	typedef boost::optional<utility::variant<Entities...>> type;
};

//(5)
template<bool Optional, class... Entities>
struct return_type<Optional, true, utility::variant<Entities...>>
{
	typedef std::set<utility::variant<Entities...>> type;
};

//(6)
template<class Entity, class Entity2, class... Entities>
struct return_type<false, false, Entity, Entity2, Entities...>
{
	typedef typename utility::ptr_variant<Entity, Entity2, Entities...>::type type;
};

//(7)
template<class Entity, class Entity2, class... Entities>
struct return_type<true, false, Entity, Entity2, Entities...>
{
	typedef boost::optional<typename utility::ptr_variant<Entity, Entity2, Entities...>::type> type;
};

//(8)
template<bool Optional, class Entity, class Entity2, class... Entities>
struct return_type<Optional, true, Entity, Entity2, Entities...>
{
	typedef std::set<typename utility::ptr_variant<Entity, Entity2, Entities...>::type> type;
};



/**
Find entities corresponding to the given identifier,
from the given declarative region (unqualified name lookup).
*/
template<class EntityIdentificationPolicy, bool Optional, bool Multiple, class... Entities>
typename return_type<Optional, Multiple, Entities...>::type
find
(
	const typename EntityIdentificationPolicy::identifier_t& identifier,
	semantic_entities::declarative_region_t current_declarative_region
);

/**
Find entities corresponding to the given nested identifier,
from the given declarative region (qualified name lookup).
apply_using_directives_for_unqualified_id_part determines whether the name
lookup of the unqualified-id part of the given nested identifier must apply
using directives. It must be set to false when looking up the declaration of a
function we're going to define.
*/
template<class EntityIdentificationPolicy, bool Optional, bool Multiple, class... Entities>
typename return_type<Optional, Multiple, Entities...>::type
find
(
	const bool has_leading_double_colon,
	const syntax_nodes::optional_node<syntax_nodes::nested_name_specifier>& opt_nested_name_specifier_node,
	const typename EntityIdentificationPolicy::identifier_t& identifier,
	const semantic_entities::declarative_region_t& current_declarative_region,
	const bool apply_using_directives_for_unqualified_id_part = true
);

/**
Find the declarative region corresponding to the given
nested-identifier syntax node (i.e. Z in the expression "X::Y::Z::"),
from the given declarative region.
If has_leading_double_colon is false, the second argument cannot be omitted.
*/
semantic_entities::open_declarative_region_t
find_declarative_region
(
	const bool has_leading_double_colon,
	const syntax_nodes::optional_node<syntax_nodes::nested_name_specifier>& opt_nested_name_specifier_node,
	const semantic_entities::declarative_region_t& current_declarative_region
);

/**
Find entities corresponding to the given identifier,
in the given declarative region only.
Using directives are not applied.
*/
template<class EntityIdentificationPolicy, class DeclarativeRegion, bool Optional, bool Multiple, class... Entities>
typename return_type<Optional, Multiple, Entities...>::type
find_local
(
	const typename EntityIdentificationPolicy::identifier_t& identifier,
	DeclarativeRegion& current_declarative_region
);



namespace detail
{
	//used for applying using directives
	struct associated_namespaces
	{
		std::vector<semantic_entities::namespace_*> namespaces;
		std::vector<semantic_entities::unnamed_namespace*> unnamed_namespaces;
	};

	typedef
		std::map
		<
			semantic_entities::namespace_ptr_variant,
			associated_namespaces
		>
		namespace_association_map
	;



	/**
	Find the declarative region corresponding to the given
	nested-identifier syntax node (i.e. Z in the expression "X::Y::Z::"),
	from the given declarative region (where X must be declared).
	*/
	semantic_entities::open_declarative_region_t
	find_declarative_region
	(
		const syntax_nodes::nested_name_specifier& nested_name_specifier_node,
		const semantic_entities::open_declarative_region_t& current_declarative_region
	);



	/**
	Find entities corresponding to the given identifier,
	in the given namespace, applying using directives as defined in the
	qualified name lookup section of the C++ standard.
	*/
	template<class EntityIdentificationPolicy, bool Optional, bool Multiple, class... Entities, class Namespace>
	typename return_type<Optional, Multiple, Entities...>::type
	find_in_namespace
	(
		const typename EntityIdentificationPolicy::identifier_t& identifier,
		Namespace& current_namespace
	);

	/**
	Recursive part of the above function.
	*/
	template<class EntityIdentificationPolicy, bool Optional, bool Multiple, class... Entities, class Namespace>
	typename return_type<Optional, Multiple, Entities...>::type
	find_in_namespace
	(
		const typename EntityIdentificationPolicy::identifier_t& identifier,
		Namespace& current_namespace,
		std::vector<semantic_entities::namespace_*>& already_seached_namespaces
	);



	/**
	Find entities of the given identifier, in the given declarative region only (variadic version).
	*/
	template<class EntityIdentificationPolicy, class DeclarativeRegion, bool Optional, bool Multiple, class Entity, class Entity2, class... Entities>
	typename return_type<Optional, Multiple, Entity, Entity2, Entities...>::type
	find_local_entities
	(
		const typename EntityIdentificationPolicy::identifier_t& identifier,
		DeclarativeRegion& current_declarative_region
	);

	/**
	Find entities of the given identifier, in the given declarative region only.
	*/
	template<class EntityIdentificationPolicy, class DeclarativeRegion, bool Optional, bool Multiple, class Entity>
	typename return_type<Optional, Multiple, Entity>::type
	find_local_entities
	(
		const typename EntityIdentificationPolicy::identifier_t& identifier,
		DeclarativeRegion& current_declarative_region
	);

	//Implementation of variadic find_local_entities()
	template<class EntityIdentificationPolicy, class DeclarativeRegion, bool Optional, bool Multiple, class ReturnT, class... Entities>
	struct find_variadic_local_entities;

	//Implementation of variadic find_local_entities()
	template<class EntityIdentificationPolicy, class DeclarativeRegion, bool Optional, bool Multiple, class ReturnT>
	struct find_variadic_local_entities<EntityIdentificationPolicy, DeclarativeRegion, Optional, Multiple, ReturnT>
	{
		static
		void
		find
		(
			const typename EntityIdentificationPolicy::identifier_t& identifier,
			DeclarativeRegion& current_declarative_region,
			ReturnT& found_entities
		);
	};

	//Implementation of variadic find_local_entities()
	template<class EntityIdentificationPolicy, class DeclarativeRegion, bool Optional, bool Multiple, class ReturnT, class Entity, class... Entities>
	struct find_variadic_local_entities<EntityIdentificationPolicy, DeclarativeRegion, Optional, Multiple, ReturnT, Entity, Entities...>
	{
		static
		void
		find
		(
			const typename EntityIdentificationPolicy::identifier_t& identifier,
			DeclarativeRegion& current_declarative_region,
			ReturnT& found_entities
		);
	};

	//Implementation of non-variadic find_local_entities(), general case
	template<class EntityIdentificationPolicy, class DeclarativeRegion, bool Optional, bool Multiple, class Entity>
	struct find_single_type_local_entities
	{
		static
		typename return_type<Optional, Multiple, Entity>::type
		find
		(
			const typename EntityIdentificationPolicy::identifier_t& identifier,
			DeclarativeRegion& current_declarative_region
		);
	};

	//Implementation of non-variadic find_local_entities(), with Entity = open_declarative_region_t
	template<class EntityIdentificationPolicy, class DeclarativeRegion, bool Optional, bool Multiple>
	struct find_single_type_local_entities<EntityIdentificationPolicy, DeclarativeRegion, Optional, Multiple, semantic_entities::open_declarative_region_t>
	{
		static
		typename return_type<Optional, Multiple, semantic_entities::open_declarative_region_t>::type
		find
		(
			const typename EntityIdentificationPolicy::identifier_t& identifier,
			DeclarativeRegion& current_declarative_region
		);
	};



	/*
	Stage 2: Dispatch special declarative region types (variants, typedefs, etc.)
	*/
	template<class EntityIdentificationPolicy, bool Optional, bool Multiple, class Entity, class DeclarativeRegion>
	struct find_local_entities2
	{
		static
		void
		find
		(
			const typename EntityIdentificationPolicy::identifier_t& identifier,
			DeclarativeRegion& current_declarative_region,
			typename return_type<Optional, Multiple, Entity>::type& found_entities
		);
	};

	template<class EntityIdentificationPolicy, bool Optional, bool Multiple, class Entity, class... DeclarativeRegions>
	struct find_local_entities2<EntityIdentificationPolicy, Optional, Multiple, Entity, utility::variant<DeclarativeRegions...>>
	{
		static
		void
		find
		(
			const typename EntityIdentificationPolicy::identifier_t& identifier,
			utility::variant<DeclarativeRegions...>& current_declarative_region,
			typename return_type<Optional, Multiple, Entity>::type& found_entities
		);
	};

	template<class EntityIdentificationPolicy, bool Optional, bool Multiple, class Entity>
	struct find_local_entities2<EntityIdentificationPolicy, Optional, Multiple, Entity, semantic_entities::typedef_>
	{
		static
		void
		find
		(
			const typename EntityIdentificationPolicy::identifier_t& identifier,
			semantic_entities::typedef_& current_declarative_region,
			typename return_type<Optional, Multiple, Entity>::type& found_entities
		);
	};

	template<class EntityIdentificationPolicy, bool Optional, bool Multiple, class Entity>
	struct find_local_entities2<EntityIdentificationPolicy, Optional, Multiple, Entity, semantic_entities::member_typedef>
	{
		static
		void
		find
		(
			const typename EntityIdentificationPolicy::identifier_t& identifier,
			semantic_entities::member_typedef& current_declarative_region,
			typename return_type<Optional, Multiple, Entity>::type& found_entities
		);
	};

	template<class EntityIdentificationPolicy, bool Optional, bool Multiple, class Entity>
	struct find_local_entities2<EntityIdentificationPolicy, Optional, Multiple, Entity, semantic_entities::namespace_alias>
	{
		static
		void
		find
		(
			const typename EntityIdentificationPolicy::identifier_t& identifier,
			semantic_entities::namespace_alias& current_declarative_region,
			typename return_type<Optional, Multiple, Entity>::type& found_entities
		);
	};



	/**
	Find entities of the given identifier, in the given declarative region's members.
	*/
	template<class EntityIdentificationPolicy, bool Optional, bool Multiple, class Entity, class DeclarativeRegion>
	void
	find_in_declarative_region_members
	(
		const typename EntityIdentificationPolicy::identifier_t& identifier,
		DeclarativeRegion& current_declarative_region,
		typename return_type<Optional, Multiple, Entity>::type& found_entities,
		typename boost::enable_if<semantic_entities::type_traits::has_members_of_type<DeclarativeRegion, Entity>>::type* = 0
	);

	template<class EntityIdentificationPolicy, bool Optional, bool Multiple, class Entity, class DeclarativeRegion>
	void
	find_in_declarative_region_members
	(
		const typename EntityIdentificationPolicy::identifier_t& identifier,
		DeclarativeRegion& current_declarative_region,
		typename return_type<Optional, Multiple, Entity>::type& found_entities,
		typename boost::disable_if<semantic_entities::type_traits::has_members_of_type<DeclarativeRegion, Entity>>::type* = 0
	);



	/**
	Find entities of the given identifier, in the given declarative region's members.
	*/
	template<class EntityIdentificationPolicy, bool Optional, bool Multiple, class Entity, class DeclarativeRegion>
	void
	find_in_declarative_region_entity_aliases
	(
		const typename EntityIdentificationPolicy::identifier_t& identifier,
		DeclarativeRegion& current_declarative_region,
		typename return_type<Optional, Multiple, Entity>::type& found_entities,
		typename boost::enable_if<semantic_entities::type_traits::has_entity_aliases_of_type<DeclarativeRegion, Entity>>::type* = 0
	);

	template<class EntityIdentificationPolicy, bool Optional, bool Multiple, class Entity, class DeclarativeRegion>
	void
	find_in_declarative_region_entity_aliases
	(
		const typename EntityIdentificationPolicy::identifier_t& identifier,
		DeclarativeRegion& current_declarative_region,
		typename return_type<Optional, Multiple, Entity>::type& found_entities,
		typename boost::disable_if<semantic_entities::type_traits::has_entity_aliases_of_type<DeclarativeRegion, Entity>>::type* = 0
	);



	/**
	Find entities of the given identifier, in the given base classes
	*/
	template<class EntityIdentificationPolicy, class Class, bool Optional, bool Multiple, class... Entities>
	typename return_type<Optional, Multiple, Entities...>::type
	find_entities_in_base_classes
	(
		const typename EntityIdentificationPolicy::identifier_t& identifier,
		Class& class_entity
	);

	template<class DeclarativeRegion>
	void
	apply_using_directives
	(
		DeclarativeRegion& declarative_region,
		const std::vector<semantic_entities::namespace_*>& using_directive_namespaces,
		semantic_entities::unnamed_namespace* opt_unnamed_namespace,
		namespace_association_map& namespace_associations
	);

	/**
	Find the nearest enclosing namespace containing both a and b.
	*/
	template<class DeclarativeRegion>
	semantic_entities::namespace_ptr_variant
	find_common_enclosing_namespace
	(
		DeclarativeRegion& a,
		const semantic_entities::namespace_ptr_variant& b
	);



	template<class T>
	struct initialize
	{
		static
		void
		init(T&)
		{
		}
	};

	template<class T>
	struct initialize<T*>
	{
		static
		void
		init(T*& result)
		{
			result = 0;
		}
	};



	template<class T>
	inline
	void
	add_to_result(T*& result, T& entity);

	template<class T>
	inline
	void
	add_to_result(std::set<T*>& result, T* entity);

	template<class T>
	void
	add_to_result(std::set<T*>& result, T& entity);

	template<class T>
	inline
	void
	add_to_result(std::set<T*>& result, const std::set<T*>& entity);

	//add entity to result if entity isn't empty
	template<class T>
	inline
	void
	add_to_result(std::set<T>& result, const boost::optional<T>& entity);

	template<class T>
	inline
	void
	add_to_result(std::set<T>& result, const T& entity);

	template<class T>
	inline
	void
	add_to_result(boost::optional<T>& result, const T& entity);

	template<class T, class... Ts>
	inline
	void
	add_to_result
	(
		boost::optional<utility::variant<Ts...>>& result,
		T* entity
	);



	template<bool Optional, bool Multiple, class... Entities>
	struct return_result;

	template<class... Entities>
	struct return_result<true, false, Entities...>
	{
		//(2) -> (1)
		//or
		//(5) -> (7)
		//
		//return the only one element of the set
		//throw an exception if there's more than one element in the set
		static
		typename return_type<true, false, Entities...>::type
		result(typename return_type<true, true, Entities...>::type& result);

		//(1) -> (1)
		//or
		//(7) -> (7)
		//
		//return result;
		static
		typename return_type<true, false, Entities...>::type
		result(typename return_type<true, false, Entities...>::type& result);
	};

	template<class... Entities>
	struct return_result<false, false, Entities...>
	{
		//(2) -> (1)
		//or
		//(8) -> (6)
		//
		//return the only one element of the set
		//throw an exception if there's zero or more than one element in
		//the set
		static
		typename return_type<false, false, Entities...>::type
		result(typename return_type<false, true, Entities...>::type& result);

		//(1) -> (1)
		//or
		//(7) -> (6)
		//
		//return result;
		//throw an exception if the result is empty
		static
		typename return_type<false, false, Entities...>::type
		result(typename return_type<true, false, Entities...>::type& result);
	};

	template<class... Entities>
	struct return_result<false, false, utility::variant<Entities...>>
	{
		//return the only one element of the set
		//throw an exception if there's zero or more than one element in
		//the set
		static
		typename return_type<false, false, utility::variant<Entities...>>::type
		result(typename return_type<false, true, utility::variant<Entities...>>::type& result);

		//return *result;
		//throw an exception if the result is empty
		static
		typename return_type<false, false, utility::variant<Entities...>>::type
		result(typename return_type<true, false, utility::variant<Entities...>>::type& result);
	};

	template<class Entity, class Entity2, class... Entities>
	struct return_result<false, false, Entity, Entity2, Entities...>
	{
		//return the only one element of the set
		//throw an exception if there's zero or more than one element in
		//the set
		static
		typename return_type<false, false, Entity, Entity2, Entities...>::type
		result(typename return_type<false, true, Entity, Entity2, Entities...>::type& result);

		//return *result;
		//throw an exception if the result is empty
		static
		typename return_type<false, false, Entity, Entity2, Entities...>::type
		result(typename return_type<true, false, Entity, Entity2, Entities...>::type& result);
	};

	template<class... Entities>
	struct return_result<true, true, Entities...>
	{
		//return result;
		static
		typename return_type<true, true, Entities...>::type&
		result(typename return_type<true, true, Entities...>::type& result);
	};

	template<class... Entities>
	struct return_result<false, true, Entities...>
	{
		//return result;
		//throw an exception if the result is empty
		static
		typename return_type<false, true, Entities...>::type&
		result(typename return_type<true, true, Entities...>::type& result);
	};
}

}}}}} //namespace scalpel::cpp::semantic_analysis::detail::name_lookup

#include "name_lookup.ipp"

#endif

