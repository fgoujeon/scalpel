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

#ifndef SOCOA_CPP_SYNTAX_TREE_PTR_OPERATOR_HPP
#define SOCOA_CPP_SYNTAX_TREE_PTR_OPERATOR_HPP

#include <memory>
#include <boost/optional.hpp>
#include "composite_node.hpp"
#include "../../util/sequence.hpp"
#include "nested_name_specifier.hpp"
#include "cv_qualifier_seq.hpp"

namespace socoa { namespace cpp { namespace syntax_tree
{

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
			boost::optional<nested_name_specifier>&& a_nested_name_specifier,
			boost::optional<cv_qualifier_seq>&& a_cv_qualifier_seq
		);

		ptr_operator(ptr_operator&) = delete;

		ptr_operator(ptr_operator&& o);

		inline
		type
		get_type() const;

		inline
		bool
		has_leading_double_colon() const;

		inline
		const boost::optional<const nested_name_specifier&>
		get_nested_name_specifier() const;

		inline
		const boost::optional<const cv_qualifier_seq&>
		get_cv_qualifier_seq() const;

	private:
		type type_;
		bool leading_double_colon_;
		/*
		boost::optional<nested_name_specifier> nested_name_specifier_;
		boost::optional<cv_qualifier_seq> cv_qualifier_seq_;
		*/
		std::unique_ptr<nested_name_specifier> nested_name_specifier_;
		std::unique_ptr<cv_qualifier_seq> cv_qualifier_seq_;
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
ptr_operator::get_nested_name_specifier() const
{
	if(nested_name_specifier_)
		return boost::optional<const nested_name_specifier&>(*nested_name_specifier_);
	else
		return boost::optional<const nested_name_specifier&>();
}

inline
const boost::optional<const cv_qualifier_seq&>
ptr_operator::get_cv_qualifier_seq() const
{
	if(cv_qualifier_seq_)
		return boost::optional<const cv_qualifier_seq&>(*cv_qualifier_seq_);
	else
		return boost::optional<const cv_qualifier_seq&>();
}

}}} //namespace socoa::cpp::syntax_tree

#endif
