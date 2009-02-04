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

#include "type_name.h"

#include <iostream>
#include <algorithm>
#include <cassert>
#include "../name_lookup.h"

namespace socoa { namespace cpp { namespace parsers
{

void
type_name::set_input(const std::string& input)
{
    input_ = &input;
}

std::ptrdiff_t
type_name::operator()(const scanner_t& scan) const
{
    assert(input_);

    std::cout << "Ambiguity found!\n";

    /*
    Create a new string from the beginning of the input to the current
    location of the scanner.
    */
    std::string partial_input(&*(input_->begin()), scan.first);
    std::cout << "Fragment of input succesfully parsed:\n";
    std::cout << "***\n" << partial_input << "\n***\n";

    /*
    Replace string literal content by white spaces. That way, if we encounter
    special chars such as brackets, we won't have to check whether they're
    really code-significant brackets or just characters.
    */
    purify_string_literals(partial_input);

    /*
    Cut off the last fragment of declaration from the parsed input so it is
    composed of a sequence of complete declarations only.
    E.g. this code:
    ***
        class c
        {
            const int
    ***
    gives the following result:
    ***
        class c
        {
    ***
    since "const int" is a fragment of declaration.
    */
    {
        /*
        Search last declaration.
        */
        std::string::size_type last_declaration_index = std::string::npos;
        std::string::size_type search_from = std::string::npos;
        bool continue_search = true;
        while(continue_search)
        {
            last_declaration_index = partial_input.find_last_of(";:{}", search_from);

            //check whether found char is part of a "::" operator
            if
            (
                last_declaration_index != std::string::npos &&
                last_declaration_index > 1 &&
                partial_input.at(last_declaration_index - 1) == ':'
            )
            {
                //if so, continue search
                search_from = last_declaration_index - 2;
            }
            else
            {
                continue_search = false;
            }
        }

        partial_input = partial_input.substr(0, last_declaration_index + 1);
        std::cout << "Interesting part:\n";
        std::cout << "***\n" << partial_input << "\n***\n";
    }

    /*
    Complete input so it's syntactically correct.
    E.g. this code:
    ***
        class c
        {
    ***
    gives the following result:
    ***
        class c
        {
        };
    ***
    */
    {
        //if last char is a semicolon,
        //we have to check whether the last for statement is correctly closed
        if(partial_input.size() > 0 && partial_input.at(partial_input.size() - 1) == ';')
        {
            //search last for statement
            std::string::size_type last_for_statement_index = partial_input.rfind(" for");
            if(last_for_statement_index == std::string::npos)
                last_for_statement_index = partial_input.rfind("\nfor");
            if(last_for_statement_index == std::string::npos)
                last_for_statement_index = partial_input.rfind("\tfor");

            //if a for statement has been found
            if(last_for_statement_index != std::string::npos)
            {
                //count the semicolons
                unsigned int semicolon_count = 0;
                for
                (
                    std::string::size_type i = last_for_statement_index;
                    i < partial_input.size();
                    ++i
                )
                {
                    if(partial_input.at(i) == ';') ++semicolon_count;
                    if(semicolon_count > 2) break;
                }

                //there's nothing to do if there's at least 3 semicolons
                if(semicolon_count <= 2)
                {
                    //close the for statement
                    for(unsigned int i = semicolon_count; i < 2; ++i)
                        partial_input.append(";");
                    partial_input.append(");");
                }
            }
        }

        //count opening and closing brackets
        unsigned int opening_bracket_count = std::count(partial_input.begin(), partial_input.end(), '{');
        unsigned int closing_bracket_count = std::count(partial_input.begin(), partial_input.end(), '}');

        //append closing brackets so there's as many as opening ones
        for(unsigned int i = 0; i < opening_bracket_count - closing_bracket_count; ++i)
        {
            partial_input.append("};");
        }

        std::cout << "Completed input:\n";
        std::cout << "***\n" << partial_input << "\n***\n";
    }

    std::cout << "\n";
    return -1;
}

}}} //namespace socoa::cpp::parsers
