/*
Socoa - Source Code Analysis Library
Copyright © 2008  Florian Goujeon

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

#include <stdexcept>
#include "grammar.h"

#include "spirit_launcher.h"

using namespace boost::spirit;

namespace socoa { namespace cpp
{

spirit_launcher::spirit_launcher():
    m_grammar(*new grammar(m_grammar_configuration))
{
    m_grammar_configuration.skip_function_bodies = true;
}

spirit_launcher::~spirit_launcher()
{
    delete &m_grammar;
}

const boost::spirit::tree_match<char const*>::node_t
spirit_launcher::operator()(const std::string& input)
{
    //parse the input with the C++ grammar
    tree_parse_info<> info = pt_parse(input.c_str(), m_grammar, space_p);

    //throw an exception if parsing failed
    if(!info.full)
    {
        std::ostringstream failure_message;
        failure_message << "Parsing stopped at:\n***\n" << info.stop << "\n***";
        throw std::runtime_error(failure_message.str().c_str());
    }

    return *info.trees.begin();
}

}} //namespace socoa::cpp
