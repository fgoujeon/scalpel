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

#ifndef SOCOA_CPP_SYNTAX_TREE_FUNCTION_DEFINITION_H
#define SOCOA_CPP_SYNTAX_TREE_FUNCTION_DEFINITION_H

#include <memory>
#include "visitor.h"
#include "declaration.h"
#include "declarator.h"
#include "../../util/sequence.h"

namespace socoa { namespace cpp { namespace syntax_tree
{

class decl_specifier;
class ctor_initializer;

class function_definition: public declaration
{
    public:
        function_definition
        (
            std::shared_ptr<util::sequence<decl_specifier>> a_decl_specifier_seq,
            declarator&& a_declarator,
            std::shared_ptr<ctor_initializer> a_ctor_initializer
        );

		inline
		const std::shared_ptr<const util::sequence<decl_specifier>>
		get_decl_specifier_seq() const;

		inline
		const declarator&
		get_declarator() const;

		inline
		const std::shared_ptr<const ctor_initializer> 
		get_ctor_initializer() const;

        SOCOA_CPP_DEFINE_VISITABLE()

    private:
        std::shared_ptr<util::sequence<decl_specifier>> decl_specifier_seq_;
        declarator declarator_;
        std::shared_ptr<ctor_initializer> ctor_initializer_;
};

inline
const std::shared_ptr<const util::sequence<decl_specifier>>
function_definition::get_decl_specifier_seq() const
{
	return decl_specifier_seq_;
}

inline
const declarator&
function_definition::get_declarator() const
{
	return declarator_;
}

inline
const std::shared_ptr<const ctor_initializer> 
function_definition::get_ctor_initializer() const
{
	return ctor_initializer_;
}

}}} //namespace socoa::cpp::syntax_tree

#endif
