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

#include "source_code_completion.hpp"

#include <algorithm>
#include <iostream>

namespace scalpel { namespace cpp { namespace detail { namespace syntax_analysis { namespace source_code_completion
{

/**
Replaces string literal content by white spaces.
*/
void
purify_string_literals(std::string& str);

/**
Check whether the word preceding the character pointed by the given index
*/
bool
check_previous_word(const std::string& str, const std::string& word, int start_index);


/**
Completes source code by cuting off noncompletable declaration fragments and
by closing enclosing ones (such as classes, namespaces, etc.).
*/
unsigned int
complete(std::string& str)
{
	/*
	Replace string literal content by white spaces. That way, if we encounter
	special chars such as brackets, we won't have to check whether they're
	really code-significant brackets or just characters.
	*/
	purify_string_literals(str);

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
		std::string::size_type last_declaration_index = str.find_last_of(";{");
		/*
		std::string::size_type last_declaration_index = std::string::npos;
		std::string::size_type search_from = std::string::npos;
		bool continue_search = true;
		while(continue_search)
		{
			last_declaration_index = str.find_last_of(";:{}", search_from);

			//check whether found char is part of a "::" operator
			if
			(
				last_declaration_index != std::string::npos &&
				last_declaration_index > 1 &&
				str.at(last_declaration_index - 1) == ':'
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
		*/

		str = str.substr(0, last_declaration_index + 1);
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
		if(str.size() > 0 && str.at(str.size() - 1) == ';')
		{
			//search last for statement
			std::string::size_type last_for_statement_index = str.rfind(" for");
			if(last_for_statement_index == std::string::npos)
				last_for_statement_index = str.rfind("\nfor");
			if(last_for_statement_index == std::string::npos)
				last_for_statement_index = str.rfind("\tfor");

			//if a for statement has been found
			if(last_for_statement_index != std::string::npos)
			{
				//count the semicolons
				unsigned int semicolon_count = 0;
				for
				(
					std::string::size_type i = last_for_statement_index;
					i < str.size();
					++i
				)
				{
					if(str.at(i) == ';') ++semicolon_count;
					if(semicolon_count > 2) break;
				}

				//there's nothing to do if there's at least 3 semicolons
				if(semicolon_count <= 2)
				{
					//close the for statement
					for(unsigned int i = semicolon_count; i < 2; ++i)
						str.append(";");
					str.append(");");
				}
			}
		}

		//count opening and closing brackets
		unsigned int opening_bracket_count = std::count(str.begin(), str.end(), '{');
		unsigned int closing_bracket_count = std::count(str.begin(), str.end(), '}');
		unsigned int scope_to_be_closed_count = opening_bracket_count - closing_bracket_count;

		//append closing brackets so there's as many as opening ones
		for(unsigned int i = 0; i < scope_to_be_closed_count; ++i)
		{
			//find the opening brace of the scope we're going to close
			int last_unclosed_brace_index = 0;
			int opening_closing_diff = 0;
			for(int j = str.size() - 1; j > 0; --j)
			{
				if(str.at(j) == '{')
				{
					if(opening_closing_diff == 0)
					{
						last_unclosed_brace_index = j;
						break;
					}
					++opening_closing_diff;
				}
				else if(str.at(j) == '}')
				{
					--opening_closing_diff;
				}
			}

			//check whether the scope we're going to close is a do-while statement
			if(check_previous_word(str, "do", last_unclosed_brace_index))
				str.append("} while(false);");
			else
				str.append("};");
		}

		return scope_to_be_closed_count;
	}
}


void
purify_string_literals(std::string& str)
{
	bool in_string_literal = false;
	bool in_char_literal = false;
	bool previous_char_was_espace_char = false;
	for
	(
		std::string::iterator i = str.begin();
		i != str.end();
		++i
	)
	{
		bool replace_by_white_space = false;

		if(in_string_literal)
		{
			if(*i == '"' && !previous_char_was_espace_char)
			{
				in_string_literal = false;
			}
			else
				replace_by_white_space = true;
		}
		else if(in_char_literal)
		{
			if(*i == '\'' && !previous_char_was_espace_char)
			{
				in_char_literal = false;
			}
			else
				replace_by_white_space = true;
		}
		else
		{
			if(*i == '"') in_string_literal = true;
			else if(*i == '\'') in_char_literal = true;
		}

		previous_char_was_espace_char = (*i == '\\' && !previous_char_was_espace_char);

		if(replace_by_white_space) *i = ' ';
	}
}


bool
check_previous_word(const std::string& str, const std::string& word, int index)
{
	if(index <= 0) return false;

	//skip white spaces
	index -= 1;
	for(; index >= 0; --index)
	{
		char c = str.at(index);
		if
		(
			(c >= 'a' && c <= 'z') ||
			(c >= 'A' && c <= 'Z') ||
			(c >= '0' && c <= '9') ||
			c == '_'
		)
			break;
	}

	if(index <= 0) return false;

	//get the previous word
	std::string previous_word;
	for(; index >= 0; --index)
	{
		char c = str.at(index);
		if
		(
			(c >= 'a' && c <= 'z') ||
			(c >= 'A' && c <= 'Z') ||
			(c >= '0' && c <= '9') ||
			c == '_'
		)
			previous_word = str.at(index) + previous_word;
		else
			break;
	}

	return previous_word == word;
}

}}}}} //namespace scalpel::cpp::detail::syntax_analysis::source_code_completion

