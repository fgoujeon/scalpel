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

#ifndef SCALPEL_CPP_DETAIL_SEMANTIC_ANALYSIS_NAME_LOOKUP_HPP
#define SCALPEL_CPP_DETAIL_SEMANTIC_ANALYSIS_NAME_LOOKUP_HPP

#include "../../syntax_tree.hpp"
#include "../../semantic_graph.hpp"
#include <string>
#include <list>
#include <stdexcept>

namespace scalpel { namespace cpp { namespace detail { namespace semantic_analysis
{

class name_lookup
{
	public:
		/**
		Find qualified name following standard C++ name-lookup rules.
		*/
		template<class RangeT>
		static
		std::shared_ptr<semantic_entities::named_entity>
		find_name
		(
			RangeT declarative_region_stack,
			const syntax_nodes::nested_identifier_or_template_id& nested_identifier_or_template_id_node
		);

		/**
		Find unqualified name following standard C++ name-lookup rules.
		*/
		template<class RangeT>
		static
		std::shared_ptr<semantic_entities::named_entity>
		find_name
		(
			RangeT declarative_region_stack,
			const std::string& name
		);

		/**
		Find nested declarative_region following standard C++ name-lookup rules.
		*/
		template<class RangeT>
		static
		std::shared_ptr<semantic_entities::declarative_region>
		find_declarative_region
		(
			RangeT declarative_region_stack,
			const syntax_nodes::nested_name_specifier& nested_name_specifier
		);

		/**
		Find declarative_region following standard C++ name-lookup rules.
		*/
		template<class RangeT>
		static
		std::shared_ptr<semantic_entities::declarative_region>
		find_declarative_region
		(
			RangeT declarative_region_stack,
			const std::string& declarative_region_name
		);

	private:
		template<class RangeT>
		static
		std::shared_ptr<semantic_entities::named_entity>
		find_name
		(
			RangeT declarative_region_stack,
			const std::string& name,
			bool recursive_ascent
		);

		/**
		Find unqualified name in the given named_declarative_region, not recursively.
		*/
		static
		std::shared_ptr<semantic_entities::named_entity>
		find_name
		(
			semantic_entities::declarative_region& current_declarative_region,
			const std::string& name
		);

		/**
		Find named_declarative_region in the given parent named_declarative_region, not recursively.
		*/
		static
		std::shared_ptr<semantic_entities::declarative_region>
		find_declarative_region
		(
			semantic_entities::declarative_region& parent_declarative_region,
			const std::string& declarative_region_name
		);
};

}}}} //namespace scalpel::cpp::detail::semantic_analysis

#include "name_lookup.ipp"

#endif
