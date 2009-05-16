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

#ifndef SCALPEL_CPP_SYNTAX_NODES_DIRECT_DECLARATOR_HPP
#define SCALPEL_CPP_SYNTAX_NODES_DIRECT_DECLARATOR_HPP

#include <boost/range/iterator_range.hpp>
#include "composite_node.hpp"
#include "declarator_id.hpp"
#include "declarator.hpp"
#include "parameter_declaration_clause.hpp"
#include "cv_qualifier_seq.hpp"
#include "space.hpp"
#include "common_nodes.hpp"
#include "bracketed_declarator.hpp"
#include "exception_specification.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
\verbatim
direct_declarator
	= direct_declarator::first_part, [direct_declarator_last_part_seq]
;

direct_declarator::first_part
	= bracketed_declarator
	| declarator_id
;

direct_declarator::last_part_seq
	= {direct_declarator_last_part}
;

direct_declarator::last_part
	= direct_declarator::function_part
	| direct_declarator::array_part
;

direct_declarator::array_part
	= '[' >> !s >> !(conditional_expression >> !s) >> ']'
;
\endverbatim
*/
class direct_declarator: public composite_node
{
    public:
		class function_part;
		class array_part;

		typedef
			alternative_node
			<
				bracketed_declarator,
				declarator_id
			>
			first_part
		;

		typedef
			alternative_node
			<
				array_part,
				function_part
			>
			last_part
		;

		typedef sequence_node<last_part> last_part_seq;

        direct_declarator
        (
			first_part&& first_part_node,
			optional_node<space>&& pre_last_part_seq_space_node,
			optional_node<sequence_node<last_part>>&& a_last_part_seq
        );

        direct_declarator(const direct_declarator& o);

        direct_declarator(direct_declarator&& o);

		const direct_declarator&
		operator=(const direct_declarator& o);

		inline
		const first_part&
		first_part_node() const;

        inline
		const optional_node<last_part_seq>&
        last_part_seq_node() const;

    private:
		void
		update_node_list();

		first_part first_part_;
		optional_node<space> pre_last_part_seq_space_;
		optional_node<last_part_seq> last_part_seq_;
};

/**
\verbatim
direct_declarator::function_part
	= "(", [parameter_declaration_clause], ")", [cv_qualifier_seq], [exception_specification]
;
\endverbatim
*/
class direct_declarator::function_part: public composite_node
{
	public:
		function_part
		(
			optional_node<space>&& post_opening_bracket_space_node,
			optional_node<parameter_declaration_clause>&& a_parameter_declaration_clause,
			optional_node<space>&& post_parameter_declaration_clause_space_node,
			optional_node<space>&& cv_qualifier_seq_space_node,
			optional_node<cv_qualifier_seq>&& a_cv_qualifier_seq,
			optional_node<space>&& pre_exception_specification_space_node,
			optional_node<exception_specification>&& exception_specification_node
		);

		function_part(const function_part& o);

		function_part(function_part&& o);

		const function_part&
		operator=(const function_part& o);

		inline
		const optional_node<parameter_declaration_clause>&
		parameter_declaration_clause_node() const;

		inline
		const optional_node<cv_qualifier_seq>&
		cv_qualifier_seq_node() const;

	private:
		void
		update_node_list();

		optional_node<space> post_opening_bracket_space_;
		optional_node<parameter_declaration_clause> parameter_declaration_clause_;
		optional_node<space> post_parameter_declaration_clause_space_;
		optional_node<space> cv_qualifier_seq_space_;
		optional_node<cv_qualifier_seq> cv_qualifier_seq_;
		optional_node<space> pre_exception_specification_space_;
		optional_node<exception_specification> exception_specification_;
};

class direct_declarator::array_part: public composite_node
{
	public:
		array_part(){}

		array_part(const array_part&): composite_node(){};

		array_part(array_part&&){}

		const array_part&
		operator=(const array_part&){return *this;};

	private:
};

}}} //namespace scalpel::cpp::syntax_nodes

#include "direct_declarator.ipp"

#endif
