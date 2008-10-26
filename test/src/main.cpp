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

#define BOOST_TEST_ALTERNATIVE_INIT_API

#include <functional>
#include <boost/test/included/unit_test.hpp>
#include <boost/test/parameterized_test.hpp>
#include <boost/bind.hpp>
#include "single_file_test.h"

using namespace boost::unit_test;

single_file_test t;

bool
init_unit_test()
{
    const std::vector<std::string> directories
    {
        "basic",
        "name_lookup"
    };

    boost::unit_test::callback1<std::string> tm = std::bind(&single_file_test::parse_files, &t, std::placeholders::_1);

    framework::master_test_suite().add
    (
        boost::unit_test::ut_detail::param_test_case_generator
        <
            std::string,
            std::vector<std::string>::const_iterator
        >(tm, "Single file tests", directories.begin(), directories.end())
    );

    return true;
}

