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

#ifndef SOCOA_CPP_SYNTAX_TREE_EXPRESSIONS_HPP
#define SOCOA_CPP_SYNTAX_TREE_EXPRESSIONS_HPP


namespace socoa { namespace cpp { namespace syntax_tree
{

/*
typedef util::sequence<, util::inequal_sign>                            inequality_expression;
typedef util::sequence<inequality_expression, util::equal_sign>         equality_expression;
typedef util::sequence<equality_expression, util::ampersand>            and_expression;
typedef util::sequence<and_expression, util::circumflex>                exclusive_or_expression;
typedef util::sequence<exclusive_or_expression, util::pipe>             inclusive_or_expression;
typedef util::sequence<inclusive_or_expression, util::double_ampersand> logical_and_expression;
typedef util::sequence<logical_and_expression, util::double_pipe>       logical_or_expression;
*/
}}} //namespace socoa::cpp::syntax_tree

#endif
