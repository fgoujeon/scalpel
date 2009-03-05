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
#include "../../util/sequence.hpp"

namespace socoa { namespace cpp { namespace syntax_tree
{

class function_definition_impl;
class decl_specifier;
class declarator;
class ctor_initializer;

/**
\verbatim
function_definition
	= [decl_specifier_seq], declarator, [ctor_initializer], function_body
	| [decl_specifier_seq], declarator, [function_try_block]
;
\endverbatim
*/
class function_definition
{
    public:
        function_definition
        (
            boost::optional<util::sequence<decl_specifier>> a_decl_specifier_seq,
            declarator&& a_declarator,
            boost::optional<ctor_initializer> a_ctor_initializer
        );

		const boost::optional<const util::sequence<decl_specifier>&>
		get_decl_specifier_seq() const;

		const declarator&
		get_declarator() const;

		const boost::optional<const ctor_initializer&>
		get_ctor_initializer() const;

    private:
		std::shared_ptr<function_definition_impl> pimpl_;
};

}}} //namespace socoa::cpp::syntax_tree

#endif
