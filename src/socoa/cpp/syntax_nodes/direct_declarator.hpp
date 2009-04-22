/*
Socoa - Source Code Analysis Library
Copyright © 2008, 2009  Florian Goujeon

This file is part of Socoa.

Socoa is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Socoa is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Socoa.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SOCOA_CPP_SYNTAX_TREE_DIRECT_DECLARATOR_HPP
#define SOCOA_CPP_SYNTAX_TREE_DIRECT_DECLARATOR_HPP

#include <boost/range/iterator_range.hpp>
#include "composite_node.hpp"
#include "declarator_id.hpp"
#include "declarator.hpp"
#include "parameter_declaration_clause.hpp"
#include "cv_qualifier_seq.hpp"
#include "space.hpp"
#include "common_nodes.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
{

/**
\verbatim
direct_declarator
	=
	(
		declarator_id
		| "(", declarator, ")"
	),
	{
		direct_declarator::function_part
		| direct_declarator::array_part
	}
;
direct_declarator::array_part
	= "[", [constant_expression], "]"
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
				array_part,
				function_part
			>
			next_part
		;

		typedef sequence_node<next_part> next_part_seq;

        direct_declarator
        (
            boost::optional<declarator_id>&& a_declarator_id,
            boost::optional<declarator>&& a_declarator,
			boost::optional<sequence_node<next_part>>&& a_next_part_seq
        );

        direct_declarator(const direct_declarator& o);

        direct_declarator(direct_declarator&& o);

        inline
        const boost::optional<const declarator_id&>
        get_declarator_id() const;

        inline
        const boost::optional<const declarator&>
        get_declarator() const;

        inline
		const boost::optional<const next_part_seq&>
        get_next_part_seq() const;

    private:
		void
		update_node_list();

        boost::optional<declarator_id> declarator_id_;
        boost::optional<declarator> declarator_;
		boost::optional<next_part_seq> next_part_seq_;
};

/**
\verbatim
direct_declarator::function_part
	= "(", [s1], parameter_declaration_clause, [s2], ")", [[s3], cv_qualifier_seq], [[s4], exception_specification]
;
\endverbatim
*/
class direct_declarator::function_part: public composite_node
{
	public:
		function_part
		(
			boost::optional<space>&& space1,
			parameter_declaration_clause&& a_parameter_declaration_clause,
			boost::optional<space>&& space2,
			boost::optional<space>&& space3,
			boost::optional<cv_qualifier_seq>&& a_cv_qualifier_seq
		);

		function_part(const function_part& o);

		function_part(function_part&& o);

		const function_part&
		operator=(const function_part& o);

		inline
		const parameter_declaration_clause&
		get_parameter_declaration_clause() const;

		inline
		const boost::optional<const cv_qualifier_seq&>
		get_cv_qualifier_seq() const;

	private:
		void
		update_node_list();

		boost::optional<space> space1_;
		parameter_declaration_clause parameter_declaration_clause_;
		boost::optional<space> space2_;
		boost::optional<space> space3_;
		boost::optional<cv_qualifier_seq> cv_qualifier_seq_;
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

}}} //namespace socoa::cpp::syntax_nodes

#include "direct_declarator.ipp"

#endif
