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

class semantic_graph_serializer
{
	public:
		typedef std::map<const scalpel::cpp::semantic_entities::namespace_*, unsigned int> namespace_ids_t;
		typedef std::map<const scalpel::cpp::semantic_entities::class_*, unsigned int> class_ids_t;
		typedef std::map<const scalpel::cpp::semantic_entities::enum_*, unsigned int> enum_ids_t;

		semantic_graph_serializer(std::ostream& output);

		void
		operator()(std::shared_ptr<const namespace_> entity);

	private:
		void
		initialize_ids(const std::shared_ptr<const namespace_>& entity);

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
			std::shared_ptr<const namespace_> entity,
			const unsigned int indent_level = 0
		);

		void
		serialize_class
		(
			std::shared_ptr<const class_> entity,
			const unsigned int indent_level
		);

		void
		serialize_base_class
		(
			std::shared_ptr<const class_> entity,
			const class_::access acc,
			const bool is_virtual,
			const unsigned int indent_level
		);

		void
		serialize_enum
		(
			std::shared_ptr<const enum_> entity,
			const unsigned int indent_level
		);

		void
		serialize_constructor
		(
			std::shared_ptr<const constructor> entity,
			const unsigned int indent_level
		);

		void
		serialize_destructor
		(
			std::shared_ptr<const destructor> entity,
			const unsigned int indent_level
		);

		void
		serialize_operator_member_function
		(
			std::shared_ptr<const operator_member_function> entity,
			const unsigned int indent_level
		);

		void
		serialize_conversion_function
		(
			std::shared_ptr<const conversion_function> entity,
			const unsigned int indent_level
		);

		void
		serialize_simple_member_function
		(
			std::shared_ptr<const simple_member_function> entity,
			const unsigned int indent_level
		);

		void
		serialize_operator_function
		(
			std::shared_ptr<const operator_function> entity,
			const unsigned int indent_level
		);

		void
		serialize_simple_function
		(
			std::shared_ptr<const simple_function> entity,
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
			const std::shared_ptr<const function_parameter> entity,
			const unsigned int indent_level
		);

		void
		serialize_variable
		(
			std::shared_ptr<const variable> entity,
			const unsigned int indent_level
		);

		void
		serialize_namespace_alias
		(
			std::shared_ptr<const namespace_alias> entity,
			const unsigned int indent_level
		);

		void
		serialize_typedef
		(
			std::shared_ptr<const typedef_> entity,
			const unsigned int indent_level
		);

		std::string
		attribute(const class_::access& a);

		std::string
		attribute(const semantic_entities::overloadable_operator op);

		void
		define_ids(const std::shared_ptr<const namespace_>& entity);

		void
		define_ids(const std::shared_ptr<const class_>& entity);

		void
		define_ids(const std::shared_ptr<const enum_>& entity);

		unsigned int
		namespace_id(const scalpel::cpp::semantic_entities::namespace_*) const;

		unsigned int
		class_id(const scalpel::cpp::semantic_entities::class_*) const;

		unsigned int
		enum_id(const scalpel::cpp::semantic_entities::enum_*) const;

		std::ostream& output_;
		unsigned int namespace_id_counter_;
		unsigned int class_id_counter_;
		unsigned int enum_id_counter_;
		namespace_ids_t namespace_ids_;
		class_ids_t class_ids_;
		enum_ids_t enum_ids_;
};

void
serialize_semantic_graph
(
	std::shared_ptr<const semantic_graph> graph,
	std::ostream& output
);

} //namespace cpp2xml

#endif

