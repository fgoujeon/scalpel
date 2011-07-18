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

BOOST_AUTO_TEST_CASE(test_case_1)
{
	using namespace scalpel::cpp::syntax_nodes;
	using namespace scalpel::cpp::semantic_entities;
	using namespace scalpel::cpp::semantic_analysis::detail::name_lookup;
	using namespace scalpel::cpp::semantic_analysis::detail::semantic_entity_analysis;

	//
	//construction of the semantic graph of the following source code:
	/*
	 *
	 *
	namespace A
	{
		int i;

		struct B
		{
			void f();
		};

		void g();

		namespace C
		{
			int n;
		}
	}

	int i, j;

	void A::B::f()
	{
	}
	*/

	scalpel::cpp::semantic_graph semantic_graph;
	auto namespace_a = new namespace_("A");
	auto variable_a_i = new variable
	(
		"i",
		fundamental_type::INT,
		false
	);
	auto struct_a_b = new class_("B");
	auto function_a_b_f = new simple_member_function
	(
		"f",
		fundamental_type::VOID,
		function_parameter_list(),
		false,
		member_access::PUBLIC,
		false,
		false,
		false,
		false,
		false,
		false
	);
	auto function_a_g = new simple_function
	(
		"g",
		fundamental_type::VOID,
		function_parameter_list(),
		false,
		false,
		false
	);
	auto namespace_a_c = new namespace_("C");
	auto variable_a_c_n = new variable
	(
		"n",
		fundamental_type::INT,
		false
	);
	auto variable_i = new variable
	(
		"i",
		fundamental_type::INT,
		false
	);
	auto variable_j = new variable
	(
		"j",
		fundamental_type::INT,
		false
	);

	semantic_graph.add_member(std::unique_ptr<namespace_>(namespace_a));
	namespace_a->add_member(std::unique_ptr<variable>(variable_a_i));
	namespace_a->add_member(std::unique_ptr<class_>(struct_a_b));
	struct_a_b->add_member(std::unique_ptr<simple_member_function>(function_a_b_f));
	namespace_a->add_member(std::unique_ptr<simple_function>(function_a_g));
	namespace_a->add_member(std::unique_ptr<namespace_>(namespace_a_c));
	namespace_a_c->add_member(std::unique_ptr<variable>(variable_a_c_n));
	semantic_graph.add_member(std::unique_ptr<variable>(variable_i));
	semantic_graph.add_member(std::unique_ptr<variable>(variable_j));



	//
	//name lookup test
	//

	//lookup i from function test, must find it
	{
		variable* found_entity = find<identification_policies::by_name, false, false, variable>("i", function_a_b_f);
		BOOST_CHECK_EQUAL(found_entity, variable_a_i);
	}

	//lookup j from function test, must find it
	{
		auto found_entity = find<identification_policies::by_name, false, false, variable>("j", function_a_b_f);
		BOOST_CHECK_EQUAL(found_entity, variable_j);
	}

	//lookup B from itself, must find it
	{
		auto found_entity = find<identification_policies::by_name, false, false, class_>("B", struct_a_b);
		BOOST_CHECK_EQUAL(found_entity, struct_a_b);
	}

	//lookup C::n from function test, must find it
	{
		auto found_entity =
			find<identification_policies::by_name, false, false, variable>
			(
				false,
				nested_name_specifier
				(
					identifier("C"),
					predefined_text_node<str::double_colon>(),
					optional_node<nested_name_specifier_last_part_seq>()
				),
				"n",
				function_a_b_f
			)
		;
		BOOST_CHECK_EQUAL(found_entity, variable_a_c_n);
	}

	//lookup ::A::i from function test, must find it
	{
		auto found_entity =
			find<identification_policies::by_name, false, false, variable>
			(
				true,
				nested_name_specifier
				(
					identifier("A"),
					predefined_text_node<str::double_colon>(),
					optional_node<nested_name_specifier_last_part_seq>()
				),
				"i",
				function_a_b_f
			)
		;
		BOOST_CHECK_EQUAL(found_entity, variable_a_i);
	}

	//lookup ::i from function test, must find it
	{
		auto found_entity =
			find<identification_policies::by_name, false, false, variable>
			(
				true,
				optional_node<nested_name_specifier>(),
				"i",
				function_a_b_f
			)
		;
		BOOST_CHECK_EQUAL(found_entity, variable_i);
	}

	//lookup namespace A::C from function test, must find it
	{
		auto found_entity =
			find<identification_policies::by_name, false, false, namespace_>
			(
				false,
				nested_name_specifier
				(
					identifier("A"),
					predefined_text_node<str::double_colon>(),
					optional_node<nested_name_specifier_last_part_seq>()
				),
				"C",
				function_a_b_f
			)
		;
		BOOST_CHECK_EQUAL(found_entity, namespace_a_c);
	}
}

} //namespace name_lookup

