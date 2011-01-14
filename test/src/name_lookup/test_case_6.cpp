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

#include <scalpel/cpp/semantic_analysis/detail/name_lookup.hpp>
#include <scalpel/cpp/semantic_graph.hpp>
#include <scalpel/cpp/syntax_tree.hpp>
#include <boost/test/unit_test.hpp>

namespace name_lookup
{

BOOST_AUTO_TEST_CASE(test_case_6)
{
	using namespace scalpel::cpp::syntax_nodes;
	using namespace scalpel::cpp::semantic_entities;
	using namespace scalpel::cpp::semantic_analysis::detail::name_lookup;
	using namespace scalpel::cpp::semantic_analysis::detail::semantic_entity_analysis;

	//
	//construction of the semantic graph of the following source code:
	/*
	int x;

	namespace y
	{
		void f(float);
		void h(int);
	}

	namespace z
	{
		void h(double);
	}

	namespace a
	{
		using namespace y;
		void f(int);
		void g(int);
		int i;
	}

	namespace b
	{
		using namespace z;
		void f(char);
		int i;
	}

	namespace ab
	{
		using namespace a;
		using namespace b;
		void g();
	}

	void test()
	{
	}
	*/

	//namespaces
	auto semantic_graph = scalpel::cpp::semantic_graph::make_shared();
	auto namespace_y = namespace_::make_shared("y");
	auto namespace_z = namespace_::make_shared("z");
	auto namespace_a = namespace_::make_shared("a");
	auto namespace_b = namespace_::make_shared("b");
	auto namespace_ab = namespace_::make_shared("ab");

	//functions
	auto function_y_f = std::make_shared<simple_function>
	(
		"f",
		fundamental_type::VOID
	);
	auto function_y_h = std::make_shared<simple_function>
	(
		"h",
		fundamental_type::VOID
	);
	auto function_z_h = std::make_shared<simple_function>
	(
		"h",
		fundamental_type::VOID
	);
	auto function_a_f = std::make_shared<simple_function>
	(
		"f",
		fundamental_type::VOID
	);
	auto function_a_g = std::make_shared<simple_function>
	(
		"g",
		fundamental_type::VOID
	);
	auto function_b_f = std::make_shared<simple_function>
	(
		"f",
		fundamental_type::VOID
	);
	auto function_ab_g = std::make_shared<simple_function>
	(
		"g",
		fundamental_type::VOID
	);
	auto function_test = std::make_shared<simple_function>
	(
		"test",
		fundamental_type::VOID
	);

	//variables
	auto variable_x = std::make_shared<variable>
	(
		"x",
		fundamental_type::INT
	);
	auto variable_a_i = std::make_shared<variable>
	(
		"i",
		fundamental_type::INT
	);
	auto variable_b_i = std::make_shared<variable>
	(
		"i",
		fundamental_type::INT
	);

	//assembling
	semantic_graph->add_member(variable_x);
	semantic_graph->add_member(namespace_y);
	namespace_y->add_member(function_y_f);
	namespace_y->add_member(function_y_h);
	semantic_graph->add_member(namespace_z);
	namespace_z->add_member(function_z_h);
	semantic_graph->add_member(namespace_a);
	namespace_a->add_using_directive_namespace(namespace_y);
	namespace_a->add_member(function_a_f);
	namespace_a->add_member(function_a_g);
	namespace_a->add_member(variable_a_i);
	semantic_graph->add_member(namespace_b);
	namespace_b->add_using_directive_namespace(namespace_z);
	namespace_b->add_member(function_b_f);
	namespace_b->add_member(variable_b_i);
	semantic_graph->add_member(namespace_ab);
	namespace_ab->add_using_directive_namespace(namespace_a);
	namespace_ab->add_using_directive_namespace(namespace_b);
	namespace_ab->add_member(function_ab_g);
	semantic_graph->add_member(function_test);



	//
	//name lookup test
	//

	//look up ab::g() from function test, must find ab::g()
	{
		auto found_entity =
			find<identification_policies::by_name, false, false, simple_function>
			(
				false,
				nested_name_specifier
				(
					identifier("ab"),
					space(""),
					predefined_text_node<str::double_colon>(),
					space(""),
					optional_node<nested_name_specifier_last_part_seq>()
				),
				"g",
				function_test
			)
		;

		BOOST_CHECK_EQUAL(found_entity, function_ab_g);
	}

	//look up ab::f() from function test, must find a::f() and b::f()
	{
		auto found_entities =
			find<identification_policies::by_name, false, true, simple_function>
			(
				false,
				nested_name_specifier
				(
					identifier("ab"),
					space(""),
					predefined_text_node<str::double_colon>(),
					space(""),
					optional_node<nested_name_specifier_last_part_seq>()
				),
				"f",
				function_test
			)
		;

		BOOST_CHECK_EQUAL(found_entities.size(), 2);
		if(found_entities.size() == 2)
		{
			BOOST_CHECK
			(
				std::find(found_entities.begin(), found_entities.end(), function_a_f) != found_entities.end()
			);
			BOOST_CHECK
			(
				std::find(found_entities.begin(), found_entities.end(), function_b_f) != found_entities.end()
			);
		}
	}

	//look up ab::x from function test, must find nothing
	{
		auto found_entity =
			find<identification_policies::by_name, true, false, variable>
			(
				false,
				nested_name_specifier
				(
					identifier("ab"),
					space(""),
					predefined_text_node<str::double_colon>(),
					space(""),
					optional_node<nested_name_specifier_last_part_seq>()
				),
				"x",
				function_test
			)
		;
		BOOST_CHECK(!found_entity.get());
	}

	//look up ab::i from function test, must find a::i and b::i
	{
		auto found_entities =
			find<identification_policies::by_name, false, true, variable>
			(
				false,
				nested_name_specifier
				(
					identifier("ab"),
					space(""),
					predefined_text_node<str::double_colon>(),
					space(""),
					optional_node<nested_name_specifier_last_part_seq>()
				),
				"i",
				function_test
			)
		;

		BOOST_CHECK_EQUAL(found_entities.size(), 2);
		if(found_entities.size() == 2)
		{
			BOOST_CHECK
			(
				std::find(found_entities.begin(), found_entities.end(), variable_a_i) != found_entities.end()
			);
			BOOST_CHECK
			(
				std::find(found_entities.begin(), found_entities.end(), variable_b_i) != found_entities.end()
			);
		}
	}

	//look up ab::h() from function test, must find y::h() and z::h()
	{
		auto found_entities =
			find<identification_policies::by_name, false, true, simple_function>
			(
				false,
				nested_name_specifier
				(
					identifier("ab"),
					space(""),
					predefined_text_node<str::double_colon>(),
					space(""),
					optional_node<nested_name_specifier_last_part_seq>()
				),
				"h",
				function_test
			)
		;

		BOOST_CHECK_EQUAL(found_entities.size(), 2);
		if(found_entities.size() == 2)
		{
			BOOST_CHECK(found_entities.find(function_y_h) != found_entities.end());
			BOOST_CHECK(found_entities.find(function_z_h) != found_entities.end());
		}
	}
}

} //namespace name_lookup

