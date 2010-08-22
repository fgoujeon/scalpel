/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2010  Florian Goujeon

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

#ifndef SCALPEL_CPP_DETAIL_SEMANTIC_ANALYSIS_NAME_LOOKUP2_HPP
#define SCALPEL_CPP_DETAIL_SEMANTIC_ANALYSIS_NAME_LOOKUP2_HPP

#include "get_members.hpp"
#include "get_name.hpp"
#include <scalpel/cpp/semantic_graph.hpp>
#include <scalpel/cpp/syntax_tree.hpp>
#include <scalpel/utility/is_empty.hpp>
#include <scalpel/utility/variant.hpp>
#include <scalpel/utility/vector.hpp>
#include <boost/optional.hpp>
#include <sstream>
#include <memory>
#include <string>

namespace scalpel { namespace cpp { namespace detail { namespace semantic_analysis { namespace name_lookup2
{

template<bool Optional, bool Multiple, class EntityT>
struct return_type;

template<bool Optional, class EntityT>
struct return_type<Optional, false, EntityT>
{
	typedef std::shared_ptr<EntityT> type;
};

template<class... EntitiesT>
struct return_type<true, false, utility::variant<EntitiesT...>>
{
	typedef boost::optional<utility::variant<EntitiesT...>> type;
};

template<class... EntitiesT>
struct return_type<false, false, utility::variant<EntitiesT...>>
{
	typedef utility::variant<EntitiesT...> type;
};

template<bool Optional, class EntityT>
struct return_type<Optional, true, EntityT>
{
	typedef utility::vector<std::shared_ptr<EntityT>> type;
};

template<bool Optional, class... EntitiesT>
struct return_type<Optional, true, utility::variant<EntitiesT...>>
{
	typedef utility::vector<utility::variant<EntitiesT...>> type;
};



/**
Find entities corresponding to the given nested identifier
(or nested template-id),
from the given declarative region (qualified name lookup)
*/
template<bool Optional, bool Multiple, class EntityT>
typename return_type<Optional, Multiple, EntityT>::type
find_entities
(
	const syntax_nodes::nested_identifier_or_template_id& nested_identifier_or_template_id_node,
	const semantic_entities::declarative_region_shared_ptr_variant& current_declarative_region
);

/**
Find entities corresponding to the given identifier_or_template_id node,
from the given declarative region (unqualified name lookup)
*/
template<bool Optional, bool Multiple, class EntityT>
typename return_type<Optional, Multiple, EntityT>::type
find_entities
(
	const syntax_nodes::identifier_or_template_id& identifier_or_template_id,
	const semantic_entities::declarative_region_shared_ptr_variant& current_declarative_region
);



class impl
{
	template<bool Optional, bool Multiple, class EntityT>
	friend
	typename return_type<Optional, Multiple, EntityT>::type
	find_entities
	(
		const syntax_nodes::nested_identifier_or_template_id& nested_identifier_or_template_id_node,
		const semantic_entities::declarative_region_shared_ptr_variant& current_declarative_region
	);

	template<bool Optional, bool Multiple, class EntityT>
	friend
	typename return_type<Optional, Multiple, EntityT>::type
	find_entities
	(
		const syntax_nodes::identifier_or_template_id& identifier_or_template_id,
		const semantic_entities::declarative_region_shared_ptr_variant& current_declarative_region
	);

	/**
	Find the declarative region corresponding to the given
	nested-identifier-or-template-id syntax node
	(i.e. Z in the expression "X::Y::Z::"),
	from the given declarative region
	*/
	static
	semantic_entities::declarative_region_shared_ptr_variant
	find_declarative_region
	(
		const syntax_nodes::nested_identifier_or_template_id& nested_identifier_or_template_id_node,
		const semantic_entities::declarative_region_shared_ptr_variant& current_declarative_region
	);

	/**
	Find the declarative region corresponding to the given nested-name-specifier
	syntax node (i.e. Z in the expression "X::Y::Z::"),
	from the given declarative region (where X must be declared)
	*/
	static
	semantic_entities::declarative_region_shared_ptr_variant
	find_declarative_region
	(
		const syntax_nodes::nested_name_specifier& nested_name_specifier_node,
		const semantic_entities::declarative_region_shared_ptr_variant& current_declarative_region
	);

	/**
	Find entities corresponding to the given name,
	from the given declarative region (unqualified name lookup)
	*/
	template<bool Optional, bool Multiple, class EntityT>
	static
	typename return_type<Optional, Multiple, EntityT>::type
	find_entities_from_identifier
	(
		const std::string& name,
		semantic_entities::declarative_region_shared_ptr_variant current_declarative_region
	);

	/**
	Find entities corresponding to the given identifier_or_template_id node,
	in the given declarative region only
	*/
	template<bool Optional, bool Multiple, class EntityT, class DeclarativeRegionT>
	static
	typename return_type<Optional, Multiple, EntityT>::type
	find_entities_in_declarative_region
	(
		const syntax_nodes::identifier_or_template_id& identifier_or_template_id,
		DeclarativeRegionT& current_declarative_region
	);

	/**
	Find entities of the given name, in the given declarative region only
	*/
	template<bool Optional, bool Multiple, class EntityT, class DeclarativeRegionT>
	static
	typename return_type<Optional, Multiple, EntityT>::type
	find_entities_from_identifier_in_declarative_region
	(
		const std::string& name,
		DeclarativeRegionT& current_declarative_region
	);

	/**
	Find entities of the given name, in the given base classes
	*/
	template<bool Optional, bool Multiple, class EntityT>
	static
	typename return_type<Optional, Multiple, EntityT>::type
	find_entities_in_base_classes
	(
		const std::string& name,
		utility::vector<std::shared_ptr<semantic_entities::class_>>::range base_classes
	);



	//result = entity
	template<class T, class T2>
	inline
	static
	void
	add_to_result(T& result, T2& entity);

	//add entity to result if entity isn't empty
	template<class T, class T2>
	inline
	static
	void
	add_to_result(utility::vector<T>& result, T2& entity);

	//add entity to result if entity isn't empty
	template<class T, class T2>
	inline
	static
	void
	add_to_result(utility::vector<T>& result, boost::optional<T2>& entity);

	//append entities to result
	template<class T, class T2>
	inline
	static
	void
	add_to_result(utility::vector<T>& result, utility::vector<T2>& entities);



	template<bool Optional, bool Multiple, class EntityT>
	struct return_result;

	template<class EntityT>
	struct return_result<true, false, EntityT>
	{
		//return the only one element of the vector
		//throw an exception if there's more than one element in the vector
		static
		typename return_type<true, false, EntityT>::type
		result(typename return_type<true, true, EntityT>::type& result);

		//return result;
		static
		typename return_type<true, false, EntityT>::type
		result(typename return_type<true, false, EntityT>::type& result);
	};

	template<class EntityT>
	struct return_result<false, false, EntityT>
	{
		//return the only one element of the vector
		//throw an exception if there's zero or more than one element in
		//the vector
		static
		typename return_type<false, false, EntityT>::type
		result(typename return_type<false, true, EntityT>::type& result);

		//return *result;
		//throw an exception if the result is empty
		static
		typename return_type<false, false, EntityT>::type
		result(typename return_type<true, false, EntityT>::type& result);
	};

	template<class EntityT>
	struct return_result<true, true, EntityT>
	{
		//return result;
		static
		utility::vector<std::shared_ptr<EntityT>>&
		result(utility::vector<std::shared_ptr<EntityT>>& result);
	};

	template<class EntityT>
	struct return_result<false, true, EntityT>
	{
		//return result;
		//throw an exception if the result is empty
		static
		utility::vector<std::shared_ptr<EntityT>>&
		result(utility::vector<std::shared_ptr<EntityT>>& result);
	};
};

}}}}} //namespace scalpel::cpp::detail::semantic_analysis::name_lookup2

#include "name_lookup2.ipp"

#endif

