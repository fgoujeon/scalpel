/*
Socoa - Source Code Analysis Library
Copyright © 2008  Florian Goujeon

This file is part of Socoa.

Socoa is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, version 3 of the License.

Socoa is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Socoa.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SOCOA_CPP_spirit_launcher_H
#define SOCOA_CPP_spirit_launcher_H

#include <string>
#include <memory>
#include <boost/spirit.hpp>
#include <boost/spirit/include/classic_parse_tree.hpp>
#include "grammar_configuration.h"
#include "program_syntax_tree/declaration_seq.h"
#include "program_syntax_tree/simple_declaration.h"
#include "program_syntax_tree/type_specifier.h"

namespace socoa { namespace cpp
{

class grammar;

class spirit_launcher
{
    public:
        spirit_launcher();

        ~spirit_launcher();

        const boost::spirit::tree_match<const char*>::node_t
        operator()(const std::string& input);

    private:
        grammar_configuration m_grammar_configuration;
        grammar& m_grammar;
};

}} //namespace socoa::cpp

#endif
