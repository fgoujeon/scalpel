/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2011  Florian Goujeon

This file is part of Scalpel.

Scalpel is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Scalpel is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Scalpel.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <scalpel/utility/variant.hpp>
#include <boost/test/unit_test.hpp>
#include <stdexcept>

namespace variant
{

struct throw_on_second_copy
{
	throw_on_second_copy():
		must_throw(false)
	{
	}

	throw_on_second_copy(const throw_on_second_copy& o):
		must_throw(o.must_throw)
	{
		if(must_throw)
			throw std::runtime_error("error");
		must_throw = true;
	}

	bool
	operator==(const throw_on_second_copy& o) const
	{
		return must_throw == o.must_throw;
	}

	bool must_throw;
};

struct throw_on_second_copy2: public throw_on_second_copy{};

BOOST_AUTO_TEST_CASE(exception_safety_test_case)
{
	typedef
		scalpel::utility::basic_variant
		<
			scalpel::utility::identity,
			int,
			throw_on_second_copy,
			std::string,
			throw_on_second_copy2
		>
		variant
	;

	variant int_var = 42;
	variant throw_var = throw_on_second_copy();
	variant string_var = std::string("test");
	variant throw2_var = throw_on_second_copy2();

	BOOST_REQUIRE_THROW(int_var = throw_var, std::runtime_error)
	BOOST_REQUIRE_THROW(int_var = throw2_var, std::runtime_error)
	BOOST_REQUIRE_THROW(string_var = throw_var, std::runtime_error)
	BOOST_REQUIRE_THROW(string_var = throw2_var, std::runtime_error)
	BOOST_REQUIRE_THROW(throw_var = throw_var, std::runtime_error)
	BOOST_REQUIRE_THROW(throw_var = throw2_var, std::runtime_error)
	BOOST_REQUIRE_THROW(throw2_var = throw_var, std::runtime_error)
	BOOST_REQUIRE_THROW(throw2_var = throw2_var, std::runtime_error)

	int_var = 54;

	int* opt_int;
	BOOST_CHECK(opt_int = scalpel::utility::get<int>(&int_var));
	BOOST_CHECK(*opt_int == 54);

	std::string* opt_string;
	BOOST_CHECK(opt_string = scalpel::utility::get<std::string>(&string_var));
	BOOST_CHECK(*opt_string == "test");

	throw_on_second_copy* opt_throw;
	BOOST_CHECK(opt_throw = scalpel::utility::get<throw_on_second_copy>(&throw_var));

	throw_on_second_copy* opt_throw2;
	BOOST_CHECK(opt_throw2 = scalpel::utility::get<throw_on_second_copy2>(&throw2_var));
}

} //namespace variant

