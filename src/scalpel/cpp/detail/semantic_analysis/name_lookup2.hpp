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
#include <scalpel/utility/variant.hpp>
#include <scalpel/utility/vector.hpp>
#include <memory>
#include <string>

namespace scalpel { namespace cpp { namespace detail { namespace semantic_analysis
{

class name_lookup2
{
	public:
		template<bool Multiple, class EntityT>
		struct return_type;

		template<class EntityT>
		struct return_type<false, EntityT>
		{
			typedef std::shared_ptr<EntityT> type;
		};

		template<class... EntitiesT>
		struct return_type<false, utility::variant<EntitiesT...>>
		{
			typedef utility::variant<EntitiesT...> type;
		};

		template<class EntityT>
		struct return_type<true, EntityT>
		{
			typedef utility::vector<std::shared_ptr<EntityT>> type;
		};

		template<class... EntitiesT>
		struct return_type<true, utility::variant<EntitiesT...>>
		{
			typedef utility::vector<utility::variant<EntitiesT...>> type;
		};

	public:
		/**
		Find entities corresponding to the given nested identifier
		(or nested template-id),
		from the given declarative region path (qualified name lookup)
		*/
		template<bool Multiple, class EntityT>
		static
		typename return_type<Multiple, EntityT>::type
		find_entities
		(
			const syntax_nodes::nested_identifier_or_template_id& nested_identifier_or_template_id_node,
			std::vector<semantic_entities::declarative_region_variant>& declarative_region_path
		);

	private:
		/**
		Find the declarative region corresponding to the given syntax node
		(i.e. Z in the expression "X::Y::Z::"),
		from the given declarative region
		*/
		template<class DeclarativeRegionT, class CurrentDeclarativeRegionT>
		static
		typename return_type<false, DeclarativeRegionT>::type
		find_declarative_region
		(
			const syntax_nodes::nested_name_specifier_last_part_seq& nested_name_specifier_last_part_seq_node,
			std::shared_ptr<CurrentDeclarativeRegionT> current_declarative_region
		);

	public:
		/**
		Find entities corresponding to the given identifier_or_template_id node,
		from the given declarative region path (unqualified name lookup)
		*/
		template<bool Multiple, class EntityT>
		static
		typename return_type<Multiple, EntityT>::type
		find_entities
		(
			const syntax_nodes::identifier_or_template_id& identifier_or_template_id,
			std::vector<semantic_entities::declarative_region_variant>& declarative_region_path
		);

	private:
		/**
		Find entities corresponding to the given name,
		from the given declarative region path (unqualified name lookup)
		*/
		template<bool Multiple, class EntityT>
		static
		typename return_type<Multiple, EntityT>::type
		find_entities_from_identifier
		(
			const std::string& name,
			std::vector<semantic_entities::declarative_region_variant>& declarative_region_path
		);

		/**
		Find entities corresponding to the given identifier_or_template_id node,
		in the given declarative region only
		*/
		template<bool Multiple, class EntityT, class DeclarativeRegionT>
		static
		typename return_type<Multiple, EntityT>::type
		find_entities_in_declarative_region
		(
			const syntax_nodes::identifier_or_template_id& identifier_or_template_id,
			DeclarativeRegionT& current_declarative_region
		);

		/**
		Find entities of the given name, in the given declarative region only
		*/
		template<bool Multiple, class EntityT, class DeclarativeRegionT>
		static
		typename return_type<Multiple, EntityT>::type
		find_entities_from_identifier_in_declarative_region
		(
			const std::string& name,
			DeclarativeRegionT& current_declarative_region
		);

		/**
		Find entities of the given name, in the given base classes
		*/
		template<bool Multiple, class EntityT>
		static
		typename return_type<Multiple, EntityT>::type
		find_entities_in_base_classes
		(
			const std::string& name,
			utility::vector<std::shared_ptr<semantic_entities::class_>>::range base_classes
		);

	private:
		//result = entity
		template<class T, class T2>
		inline
		static
		void
		add_to_result(T& result, T2& entity);

		//add entity to result
		template<class T, class T2>
		inline
		static
		void
		add_to_result(utility::vector<T>& result, T2& entity);

		//append entities to result
		template<class T, class T2>
		inline
		static
		void
		add_to_result(utility::vector<T>& result, utility::vector<T2>& entities);



		template<class EntityT>
		inline
		static
		bool
		is_result_empty(utility::vector<std::shared_ptr<EntityT>>& result);

		template<class EntityT>
		inline
		static
		bool
		is_result_empty(std::shared_ptr<EntityT>& result);

		template<class... EntitiesT>
		inline
		static
		bool
		is_result_empty(utility::variant<EntitiesT...>& result);



		template<bool Multiple, class EntityT>
		struct return_result;

		//return the only one element of the vector
		template<class EntityT>
		struct return_result<false, EntityT>
		{
			static
			typename return_type<false, EntityT>::type
			result(typename return_type<true, EntityT>::type& result);
		};

		//return result;
		template<class EntityT>
		struct return_result<true, EntityT>
		{
			static
			utility::vector<std::shared_ptr<EntityT>>&
			result(utility::vector<std::shared_ptr<EntityT>>& result);
		};
};

}}}} //namespace scalpel::cpp::detail::semantic_analysis

#include "name_lookup2.ipp"

#endif

