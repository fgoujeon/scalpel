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

#ifndef SCALPEL_CPP_SYNTAX_NODES_PTR_OPERATOR_HPP
#define SCALPEL_CPP_SYNTAX_NODES_PTR_OPERATOR_HPP

#include <memory>
#include <boost/optional.hpp>
#include "composite_node.hpp"
#include "nested_name_specifier.hpp"
#include "cv_qualifier_seq.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
\verbatim
ptr_operator
	= ch_p('*') >> !(!s >> cv_qualifier_seq)
	| ch_p('&')
	| !(str_p("::") >> !s) >> nested_name_specifier >> !s >> '*' >> !(!s >> cv_qualifier_seq)
;
\endverbatim
*/
class ptr_operator: public composite_node
{
	public:
		enum type
		{
			ASTERISK,
			AMPERSAND
		};

		ptr_operator
		(
			type a_type,
			bool leading_double_colon,
			boost::optional<space>&& post_leading_double_colon_space_node,
			boost::optional<nested_name_specifier>&& nested_name_specifier_node,
			boost::optional<space>&& post_nested_name_specifier_space_node,
			boost::optional<space>&& pre_cv_qualifier_seq_space_node,
			boost::optional<cv_qualifier_seq>&& cv_qualifier_seq_node
		);

		ptr_operator(const ptr_operator& o);

		ptr_operator(ptr_operator&& o);

		const ptr_operator&
		operator=(const ptr_operator& o);

		inline
		type
		get_type() const;

		inline
		bool
		has_leading_double_colon() const;

		inline
		const boost::optional<const nested_name_specifier&>
		nested_name_specifier_node() const;

		inline
		const boost::optional<const cv_qualifier_seq&>
		cv_qualifier_seq_node() const;

	private:
		void
		update_node_list();

		type type_;
		bool leading_double_colon_;
		boost::optional<space> post_leading_double_colon_space_;
		boost::optional<nested_name_specifier> nested_name_specifier_;
		boost::optional<space> post_nested_name_specifier_space_;
		boost::optional<space> pre_cv_qualifier_seq_space_;
		boost::optional<cv_qualifier_seq> cv_qualifier_seq_;
};

inline
ptr_operator::type
ptr_operator::get_type() const
{
	return type_;
}

inline
bool
ptr_operator::has_leading_double_colon() const
{
	return leading_double_colon_;
}

inline
const boost::optional<const nested_name_specifier&>
ptr_operator::nested_name_specifier_node() const
{
	return boost::optional<const nested_name_specifier&>(nested_name_specifier_);
}

inline
const boost::optional<const cv_qualifier_seq&>
ptr_operator::cv_qualifier_seq_node() const
{
	return boost::optional<const cv_qualifier_seq&>(cv_qualifier_seq_);
}

}}} //namespace scalpel::cpp::syntax_nodes

#endif
