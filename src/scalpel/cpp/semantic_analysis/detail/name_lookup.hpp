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

(1) EntityT*
(2) std::set<(1)>
(3) utility::ptr_variant<EntitiesT...>
(4) boost::optional<(3)>
(5) std::set<(3)>
(6) utility::ptr_variant<EntitiesT...>
(7) boost::optional<(6)>
(8) std::set<(6)>
(E) Error
*/

template<bool Optional, bool Multiple, class... EntitiesT>
struct return_type;

//(1)
template<bool Optional, class EntityT>
struct return_type<Optional, false, EntityT>
{
	typedef EntityT* type;
};

//(2)
template<bool Optional, class EntityT>
struct return_type<Optional, true, EntityT>
{
	typedef std::set<EntityT*> type;
};

//(3)
template<class... EntitiesT>
struct return_type<false, false, utility::basic_variant<utility::add_ptr, EntitiesT...>>
{
	typedef typename utility::ptr_variant<EntitiesT...>::type type;
};

//(4)
template<class... EntitiesT>
struct return_type<true, false, utility::basic_variant<utility::add_ptr, EntitiesT...>>
{
	typedef boost::optional<typename utility::ptr_variant<EntitiesT...>::type> type;
};

//(5)
template<bool Optional, class... EntitiesT>
struct return_type<Optional, true, utility::basic_variant<utility::add_ptr, EntitiesT...>>
{
	typedef std::set<typename utility::ptr_variant<EntitiesT...>::type> type;
};

//(6)
template<class EntityT, class EntityT2, class... EntitiesT>
struct return_type<false, false, EntityT, EntityT2, EntitiesT...>
{
	typedef typename utility::ptr_variant<EntityT, EntityT2, EntitiesT...>::type type;
};

//(7)
template<class EntityT, class EntityT2, class... EntitiesT>
struct return_type<true, false, EntityT, EntityT2, EntitiesT...>
{
	typedef boost::optional<typename utility::ptr_variant<EntityT, EntityT2, EntitiesT...>::type> type;
};

//(8)
template<bool Optional, class EntityT, class EntityT2, class... EntitiesT>
struct return_type<Optional, true, EntityT, EntityT2, EntitiesT...>
{
	typedef std::set<typename utility::ptr_variant<EntityT, EntityT2, EntitiesT...>::type> type;
};



/**
Find entities corresponding to the given identifier,
from the given declarative region (unqualified name lookup).
*/
template<class EntityIdentificationPolicy, bool Optional, bool Multiple, class... EntitiesT>
typename return_type<Optional, Multiple, EntitiesT...>::type
find
(
	const typename EntityIdentificationPolicy::identifier_t& identifier,
	semantic_entities::declarative_region_ptr_variant current_declarative_region
);

/**
Find entities corresponding to the given nested identifier,
from the given declarative region (qualified name lookup).
apply_using_directives_for_unqualified_id_part determines whether the name
lookup of the unqualified-id part of the given nested identifier must apply
using directives. It must be set to false when looking up the declaration of a
function we're going to define.
*/
template<class EntityIdentificationPolicy, bool Optional, bool Multiple, class... EntitiesT>
typename return_type<Optional, Multiple, EntitiesT...>::type
find
(
	const bool has_leading_double_colon,
	const syntax_nodes::optional_node<syntax_nodes::nested_name_specifier>& opt_nested_name_specifier_node,
	const typename EntityIdentificationPolicy::identifier_t& identifier,
	const semantic_entities::declarative_region_ptr_variant& current_declarative_region,
	const bool apply_using_directives_for_unqualified_id_part = true
);

/**
Find the declarative region corresponding to the given
nested-identifier syntax node (i.e. Z in the expression "X::Y::Z::"),
from the given declarative region.
If has_leading_double_colon is false, the second argument cannot be omitted.
*/
semantic_entities::open_declarative_region_ptr_variant
find_declarative_region
(
	const bool has_leading_double_colon,
	const syntax_nodes::optional_node<syntax_nodes::nested_name_specifier>& opt_nested_name_specifier_node,
	const semantic_entities::declarative_region_ptr_variant& current_declarative_region
);

/**
Find entities corresponding to the given identifier,
in the given declarative region only.
Using directives are not applied.
*/
template<class EntityIdentificationPolicy, bool Optional, bool Multiple, class... EntitiesT>
typename return_type<Optional, Multiple, EntitiesT...>::type
find_local
(
	const typename EntityIdentificationPolicy::identifier_t& identifier,
	semantic_entities::open_declarative_region_ptr_variant current_declarative_region
);



namespace detail
{
	//used for applying using directives
	typedef
		std::map
		<
			const semantic_entities::namespace_*,
			std::vector<semantic_entities::namespace_*>
		>
		namespace_association_map
	;



	/**
	Find entities corresponding to the given identifier,
	from the given declarative region (unqualified name lookup).
	*/
	template<class EntityIdentificationPolicy, bool Optional, bool Multiple, class... EntitiesT>
	typename return_type<Optional, Multiple, EntitiesT...>::type
	find_entities
	(
		const typename EntityIdentificationPolicy::identifier_t& identifier,
		semantic_entities::declarative_region_ptr_variant current_declarative_region
	);

	/**
	Find entities corresponding to the given nested identifier
	(or nested template-id),
	from the given declarative region (qualified name lookup).
	*/
	template<class EntityIdentificationPolicy, bool Optional, bool Multiple, class... EntitiesT>
	typename return_type<Optional, Multiple, EntitiesT...>::type
	find_entities
	(
		const bool has_leading_double_colon,
		const syntax_nodes::optional_node<syntax_nodes::nested_name_specifier>& opt_nested_name_specifier_node,
		const typename EntityIdentificationPolicy::identifier_t& identifier,
		const semantic_entities::declarative_region_ptr_variant& current_declarative_region,
		const bool apply_using_directives_for_unqualified_id_part
	);

	/**
	Find the declarative region corresponding to the given
	nested-identifier syntax node (i.e. Z in the expression "X::Y::Z::"),
	from the given declarative region (where X must be declared).
	*/
	semantic_entities::open_declarative_region_ptr_variant
	find_declarative_region
	(
		const syntax_nodes::nested_name_specifier& nested_name_specifier_node,
		const semantic_entities::open_declarative_region_ptr_variant& current_declarative_region
	);



	/**
	Find entities corresponding to the given identifier,
	in the given namespace, applying using directives as defined in the
	qualified name lookup section of the C++ standard.
	*/
	template<class EntityIdentificationPolicy, bool Optional, bool Multiple, class... EntitiesT>
	typename return_type<Optional, Multiple, EntitiesT...>::type
	find_in_namespace
	(
		const typename EntityIdentificationPolicy::identifier_t& identifier,
		semantic_entities::namespace_& current_namespace
	);

	/**
	Recursive part of above function.
	*/
	template<class EntityIdentificationPolicy, bool Optional, bool Multiple, class... EntitiesT>
	typename return_type<Optional, Multiple, EntitiesT...>::type
	find_in_namespace
	(
		const typename EntityIdentificationPolicy::identifier_t& identifier,
		semantic_entities::namespace_& current_namespace,
		std::vector<semantic_entities::namespace_*>& already_seached_namespaces
	);



	/**
	Find entities of the given identifier, in the given declarative region only.
	*/
	template<class EntityIdentificationPolicy, class DeclarativeRegionT, bool Optional, bool Multiple, class EntityT, class EntityT2, class... EntitiesT>
	typename return_type<Optional, Multiple, EntityT, EntityT2, EntitiesT...>::type
	find_local_entities
	(
		const typename EntityIdentificationPolicy::identifier_t& identifier,
		DeclarativeRegionT& current_declarative_region
	);

	template<class EntityIdentificationPolicy, class DeclarativeRegionT, bool Optional, bool Multiple, class ReturnT, class... EntitiesT>
	struct find_variadic_local_entities;

	template<class EntityIdentificationPolicy, class DeclarativeRegionT, bool Optional, bool Multiple, class ReturnT>
	struct find_variadic_local_entities<EntityIdentificationPolicy, DeclarativeRegionT, Optional, Multiple, ReturnT>
	{
		static
		void
		find
		(
			const typename EntityIdentificationPolicy::identifier_t& identifier,
			DeclarativeRegionT& current_declarative_region,
			ReturnT& found_entities
		);
	};

	template<class EntityIdentificationPolicy, class DeclarativeRegionT, bool Optional, bool Multiple, class ReturnT, class EntityT, class... EntitiesT>
	struct find_variadic_local_entities<EntityIdentificationPolicy, DeclarativeRegionT, Optional, Multiple, ReturnT, EntityT, EntitiesT...>
	{
		static
		void
		find
		(
			const typename EntityIdentificationPolicy::identifier_t& identifier,
			DeclarativeRegionT& current_declarative_region,
			ReturnT& found_entities
		);
	};

	/**
	Find entities of the given identifier, in the given declarative region only.
	*/
	template<class EntityIdentificationPolicy, class DeclarativeRegionT, bool Optional, bool Multiple, class EntityT>
	typename return_type<Optional, Multiple, EntityT>::type
	find_local_entities
	(
		const typename EntityIdentificationPolicy::identifier_t& identifier,
		DeclarativeRegionT& current_declarative_region
	);



	/**
	Find entities of the given identifier, in the given base classes
	*/
	template<class EntityIdentificationPolicy, bool Optional, bool Multiple, class... EntitiesT>
	typename return_type<Optional, Multiple, EntitiesT...>::type
	find_entities_in_base_classes
	(
		const typename EntityIdentificationPolicy::identifier_t& identifier,
		const std::vector<semantic_entities::class_*>& base_classes
	);

	void
	apply_using_directives
	(
		const semantic_entities::declarative_region_ptr_variant& current_declarative_region,
		const std::vector<semantic_entities::namespace_*>& using_directive_namespaces,
		namespace_association_map& namespace_associations
	);

	/**
	Find the nearest enclosing namespace containing both a and b.
	*/
	semantic_entities::namespace_&
	find_common_enclosing_namespace
	(
		const semantic_entities::declarative_region_ptr_variant& a,
		semantic_entities::namespace_& b
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
	add_to_result(T*& result, const std::shared_ptr<T>& entity);

	template<class T>
	inline
	void
	add_to_result(std::set<T*>& result, T* entity);

	template<class T>
	inline
	void
	add_to_result(std::set<T*>& result, const std::shared_ptr<T>& entity);

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
	add_to_result(boost::optional<T>& result, const T& entity);

	template<class T, class... Ts>
	inline
	void
	add_to_result
	(
		boost::optional<utility::basic_variant<utility::add_ptr, Ts...>>& result,
		T* entity
	);



	template<bool Optional, bool Multiple, class... EntitiesT>
	struct return_result;

	template<class... EntitiesT>
	struct return_result<true, false, EntitiesT...>
	{
		//(2) -> (1)
		//or
		//(5) -> (7)
		//
		//return the only one element of the set
		//throw an exception if there's more than one element in the set
		static
		typename return_type<true, false, EntitiesT...>::type
		result(typename return_type<true, true, EntitiesT...>::type& result);

		//(1) -> (1)
		//or
		//(7) -> (7)
		//
		//return result;
		static
		typename return_type<true, false, EntitiesT...>::type
		result(typename return_type<true, false, EntitiesT...>::type& result);
	};

	template<class... EntitiesT>
	struct return_result<false, false, EntitiesT...>
	{
		//(2) -> (1)
		//or
		//(8) -> (6)
		//
		//return the only one element of the set
		//throw an exception if there's zero or more than one element in
		//the set
		static
		typename return_type<false, false, EntitiesT...>::type
		result(typename return_type<false, true, EntitiesT...>::type& result);

		//(1) -> (1)
		//or
		//(7) -> (6)
		//
		//return result;
		//throw an exception if the result is empty
		static
		typename return_type<false, false, EntitiesT...>::type
		result(typename return_type<true, false, EntitiesT...>::type& result);
	};

	template<class... EntitiesT>
	struct return_result<false, false, utility::basic_variant<utility::add_ptr, EntitiesT...>>
	{
		//return the only one element of the set
		//throw an exception if there's zero or more than one element in
		//the set
		static
		typename return_type<false, false, utility::basic_variant<utility::add_ptr, EntitiesT...>>::type
		result(typename return_type<false, true, utility::basic_variant<utility::add_ptr, EntitiesT...>>::type& result);

		//return *result;
		//throw an exception if the result is empty
		static
		typename return_type<false, false, utility::basic_variant<utility::add_ptr, EntitiesT...>>::type
		result(typename return_type<true, false, utility::basic_variant<utility::add_ptr, EntitiesT...>>::type& result);
	};

	template<class EntityT, class EntityT2, class... EntitiesT>
	struct return_result<false, false, EntityT, EntityT2, EntitiesT...>
	{
		//return the only one element of the set
		//throw an exception if there's zero or more than one element in
		//the set
		static
		typename return_type<false, false, EntityT, EntityT2, EntitiesT...>::type
		result(typename return_type<false, true, EntityT, EntityT2, EntitiesT...>::type& result);

		//return *result;
		//throw an exception if the result is empty
		static
		typename return_type<false, false, EntityT, EntityT2, EntitiesT...>::type
		result(typename return_type<true, false, EntityT, EntityT2, EntitiesT...>::type& result);
	};

	template<class... EntitiesT>
	struct return_result<true, true, EntitiesT...>
	{
		//return result;
		static
		typename return_type<true, true, EntitiesT...>::type&
		result(typename return_type<true, true, EntitiesT...>::type& result);
	};

	template<class... EntitiesT>
	struct return_result<false, true, EntitiesT...>
	{
		//return result;
		//throw an exception if the result is empty
		static
		typename return_type<false, true, EntitiesT...>::type&
		result(typename return_type<true, true, EntitiesT...>::type& result);
	};
}

}}}}} //namespace scalpel::cpp::semantic_analysis::detail::name_lookup

#include "name_lookup.ipp"

#endif

