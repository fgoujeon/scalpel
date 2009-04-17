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

#ifndef SOCOA_CPP_SYNTAX_TREE_FUNCTION_DEFINITION_HPP
#define SOCOA_CPP_SYNTAX_TREE_FUNCTION_DEFINITION_HPP

#include <memory>
#include <boost/optional.hpp>
#include "composite_node.hpp"
#include "decl_specifier_seq.hpp"
#include "ctor_initializer.hpp"

namespace socoa { namespace cpp { namespace syntax_tree
{

class declarator;

/**
\verbatim
function_definition
	= [decl_specifier_seq], declarator, [ctor_initializer], function_body
	| [decl_specifier_seq], declarator, [function_try_block]
;
\endverbatim
*/
class function_definition: public composite_node
{
	public:
        function_definition
        (
            boost::optional<decl_specifier_seq>&& a_decl_specifier_seq,
            declarator&& a_declarator,
            boost::optional<ctor_initializer>&& a_ctor_initializer
        );

		function_definition(const function_definition& o);

		function_definition(function_definition&& o);

		const function_definition&
		operator=(const function_definition& o);

		inline
		const boost::optional<const decl_specifier_seq&>
		get_decl_specifier_seq() const;

		inline
		const declarator&
		get_declarator() const;

		inline
		const boost::optional<const ctor_initializer&>
		get_ctor_initializer() const;

    private:
		void
		update_node_list();

		boost::optional<decl_specifier_seq> decl_specifier_seq_;
		std::shared_ptr<declarator> declarator_;
		boost::optional<ctor_initializer> ctor_initializer_;
};

inline
const boost::optional<const decl_specifier_seq&>
function_definition::get_decl_specifier_seq() const
{
	return boost::optional<const decl_specifier_seq&>(*decl_specifier_seq_);
}

inline
const declarator&
function_definition::get_declarator() const
{
	return *declarator_;
}

inline
const boost::optional<const ctor_initializer&>
function_definition::get_ctor_initializer() const
{
	return boost::optional<const ctor_initializer&>(*ctor_initializer_);
}

}}} //namespace socoa::cpp::syntax_tree

#endif
