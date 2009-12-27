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

#include "preprocessor.hpp"
#include <boost/wave/cpplexer/cpp_lex_iterator.hpp>
#include <boost/wave/cpplexer/cpp_lex_token.hpp>
#include <boost/wave/cpp_context.hpp>
#include <fstream>
#include <sstream>

namespace scalpel { namespace cpp
{

std::string preprocessor::operator()
(
	const std::string& input,
	const std::vector<std::string>& include_paths,
	const std::vector<std::string>& macro_definitions
)
{
    using namespace boost::wave;

    // The template boost::wave::cpplexer::lex_token<> is the
    // token type to be used by the Wave library.
    // This token type is one of the central types throughout
    // the library, because it is a template parameter to some
    // of the public classes and templates and it is returned
    // from the iterators.
    // The template boost::wave::cpplexer::lex_iterator<> is
    // the lexer iterator to use as the token source for the
    // preprocessing engine. In this case this is parametrized
    // with the token type.
    typedef cpplexer::lex_iterator<cpplexer::lex_token<> > lex_iterator_type;
    typedef context<std::string::const_iterator, lex_iterator_type> context_type;
    context_type ctx(input.begin(), input.end());

    ctx.set_language
    (
        language_support
        (
            support_cpp
            | support_option_include_guard_detection
            //| support_option_emit_pragma_directives
            | support_option_long_long
            | support_option_variadics
        )
    );

    // At this point you may want to set the parameters of the
    // preprocessing as include paths and/or predefined macros.
	for(auto i = include_paths.begin(); i != include_paths.end(); ++i)
	{
		ctx.add_sysinclude_path(i->c_str());
	}
	for(auto i = macro_definitions.begin(); i != macro_definitions.end(); ++i)
	{
		ctx.add_macro_definition(i->c_str(), true);
	}

    // The input stream is preprocessed for you during iteration
    // over [first, last)
    std::ostringstream preprocessed_output;
    try
    {
        for(context_type::iterator_type i = ctx.begin(); i != ctx.end(); ++i)
        {
            preprocessed_output << (*i).get_value();
        }
    }
    catch(const preprocess_exception& e)
    {
        std::cout << e.description() << '\n';
        std::cout << "in " << e.file_name() << ", line " << e.line_no() << ", column " << e.column_no();
    }

    return preprocessed_output.str();
}

}} //namespace scalpel::cpp
