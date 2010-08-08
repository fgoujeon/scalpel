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

#include "../../syntax_tree.hpp"
#include "../../semantic_graph.hpp"
#include <scalpel/utility/shared_ptr_vector.hpp>
#include <memory>
#include <string>

namespace scalpel { namespace cpp { namespace detail { namespace semantic_analysis
{

class name_lookup2
{
	public:
		/**
		Find entities of the given name, from the given declarative region path (unqualified name lookup)
		*/
		static
		utility::shared_ptr_vector<semantic_entities::named_entity>
		find_entities
		(
			utility::shared_ptr_vector<semantic_entities::declarative_region>::range declarative_region_path,
			const std::string& name
		);

	private:
		/**
		Find entities of the given name, in the given declarative region
		*/
		static
		utility::shared_ptr_vector<semantic_entities::named_entity>
		find_entities_in_declarative_region
		(
			std::shared_ptr<semantic_entities::declarative_region> current_declarative_region,
			const std::string& name
		);

		/**
		Find entities of the given name, in the given base classes
		*/
		static
		utility::shared_ptr_vector<semantic_entities::named_entity>
		find_entities_in_base_classes
		(
			utility::shared_ptr_vector<semantic_entities::class_>::range base_classes,
			const std::string& name
		);

	public:
		/**
		Find an open-to-outside declarative region of the given name, from the
		given declarative region path
		@return a pointer to the found declarative region or a null pointer
		*/
		static
		std::shared_ptr<semantic_entities::named_declarative_region>
		find_open_declarative_region
		(
			utility::shared_ptr_vector<semantic_entities::declarative_region>::range declarative_region_path,
			const std::string& name
		);

		/**
		Find an open-to-outside declarative region of the given name, in the
		given declarative region
		@return a pointer to the found declarative region or a null pointer
		*/
		static
		std::shared_ptr<semantic_entities::named_declarative_region>
		find_open_declarative_region
		(
			std::shared_ptr<semantic_entities::declarative_region> current_declarative_region,
			const std::string& name
		);
};

}}}} //namespace scalpel::cpp::detail::semantic_analysis

#endif
