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

#include "declarator_id.hpp"
#include "declarator.hpp"
#include "parameter_declaration_clause.hpp"
#include "cv_qualifier_seq.hpp"

namespace socoa { namespace cpp { namespace syntax_tree
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
direct_declarator::function_part
	= "(", parameter_declaration_clause, ")", [cv_qualifier_seq], [exception_specification]
;
direct_declarator::array_part
	= "[", [constant_expression], "]"
;
\endverbatim
*/
class direct_declarator
{
    public:
		class function_part
		{
			public:
				function_part
				(
					parameter_declaration_clause&& a_parameter_declaration_clause,
					boost::optional<cv_qualifier_seq> a_cv_qualifier_seq
				);

				inline
				const parameter_declaration_clause&
				get_parameter_declaration_clause() const;

				inline
				const boost::optional<const cv_qualifier_seq&>
				get_cv_qualifier_seq() const;

			private:
				parameter_declaration_clause parameter_declaration_clause_;
				boost::optional<cv_qualifier_seq> cv_qualifier_seq_;
		};

		class array_part
		{
			public:


			private:
		};

		typedef
			boost::variant
			<
				array_part,
				function_part
			>
			other_part
		;

        direct_declarator
        (
            boost::optional<declarator_id> a_declarator_id,
            boost::optional<declarator> a_declarator,
            std::vector<other_part>&& other_parts
        );

        inline
        const boost::optional<const declarator_id&>
        get_declarator_id() const;

        inline
        const boost::optional<const declarator&>
        get_declarator() const;

        inline
        const std::vector<other_part>&
        get_other_parts() const;

    private:
        boost::optional<declarator_id> declarator_id_;
        boost::optional<declarator> declarator_;
        std::vector<other_part> other_parts_;
};

inline
const boost::optional<const declarator_id&>
direct_declarator::get_declarator_id() const
{
    return boost::optional<const declarator_id&>(declarator_id_);
}

inline
const boost::optional<const declarator&>
direct_declarator::get_declarator() const
{
    return boost::optional<const declarator&>(declarator_);
}

inline
const std::vector<direct_declarator::other_part>&
direct_declarator::get_other_parts() const
{
    return other_parts_;
}


inline
const parameter_declaration_clause&
direct_declarator::function_part::get_parameter_declaration_clause() const
{
    return parameter_declaration_clause_;
}

inline
const boost::optional<const cv_qualifier_seq&>
direct_declarator::function_part::get_cv_qualifier_seq() const
{
    return boost::optional<const cv_qualifier_seq&>(cv_qualifier_seq_);
}

}}} //namespace socoa::cpp::syntax_tree

#endif
