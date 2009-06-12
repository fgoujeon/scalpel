/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008, 2009  Florian Goujeon

This file is part of Scalpel.

Scalpel is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Scalpel is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Scalpel.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SCALPEL_CPP_SYNTAX_NODES_DECLARATION_HPP
#define SCALPEL_CPP_SYNTAX_NODES_DECLARATION_HPP

#include <memory>
#include "common.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

class block_declaration;
class function_definition;
class template_declaration;
class explicit_instantiation;
class explicit_specialization;
class linkage_specification;
class namespace_definition;

typedef
	alternative_node
	<
		block_declaration,
		function_definition,
		template_declaration,
		explicit_instantiation,
		explicit_specialization,
		linkage_specification,
		namespace_definition
	>
	declaration_t
;

typedef
	alternative_node
	<
		function_definition,
		template_declaration,
		explicit_instantiation,
		explicit_specialization,
		linkage_specification,
		namespace_definition
	>
	declaration_tail_t
;

class declaration: public composite_node
{
	public:
		typedef declaration_t type;
		//typedef type::head_node_t head_node_t;
		//typedef type::tail_alternative_node_t tail_alternative_node_t;
		typedef block_declaration head_node_t;
		typedef declaration_tail_t tail_alternative_node_t;

		declaration(block_declaration&& o);

		declaration(function_definition&& o);

		declaration(template_declaration&& o);

		declaration(explicit_instantiation&& o);

		declaration(explicit_specialization&& o);

		declaration(linkage_specification&& o);

		declaration(namespace_definition&& o);

		declaration(const declaration& o);

		declaration(declaration&& o);

		~declaration();

		const declaration&
		operator=(const declaration& o);

		void
		get(boost::optional<const block_declaration&>& o) const;

		void
		get(boost::optional<const function_definition&>& o) const;

		void
		get(boost::optional<const template_declaration&>& o) const;

		void
		get(boost::optional<const explicit_instantiation&>& o) const;

		void
		get(boost::optional<const explicit_specialization&>& o) const;

		void
		get(boost::optional<const linkage_specification&>& o) const;

		void
		get(boost::optional<const namespace_definition&>& o) const;

	private:
		std::unique_ptr<type> impl_;
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
