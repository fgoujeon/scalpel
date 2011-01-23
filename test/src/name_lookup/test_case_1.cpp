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
	auto variable_a_i = std::make_shared<variable>
	(
		"i",
		fundamental_type::INT
	);
	auto struct_a_b = new class_("B");
	auto function_a_b_f = std::make_shared<simple_member_function>
	(
		"f",
		fundamental_type::VOID
	);
	auto function_a_g = std::make_shared<simple_function>
	(
		"g",
		fundamental_type::VOID
	);
	auto namespace_a_c = new namespace_("C");
	auto variable_a_c_n = std::make_shared<variable>
	(
		"n",
		fundamental_type::INT
	);
	auto variable_i = std::make_shared<variable>
	(
		"i",
		fundamental_type::INT
	);
	auto variable_j = std::make_shared<variable>
	(
		"j",
		fundamental_type::INT
	);

	semantic_graph.add_member(std::unique_ptr<namespace_>(namespace_a));
	namespace_a->add_member(variable_a_i);
	namespace_a->add_member(std::unique_ptr<class_>(struct_a_b));
	struct_a_b->add_member(function_a_b_f);
	namespace_a->add_member(function_a_g);
	namespace_a->add_member(std::unique_ptr<namespace_>(namespace_a_c));
	namespace_a_c->add_member(variable_a_c_n);
	semantic_graph.add_member(variable_i);
	semantic_graph.add_member(variable_j);



	//
	//name lookup test
	//

	//lookup i from function test, must find it
	{
		variable* found_entity = find<identification_policies::by_name, false, false, variable>("i", function_a_b_f.get());
		BOOST_CHECK_EQUAL(found_entity, variable_a_i.get());
	}

	//lookup j from function test, must find it
	{
		auto found_entity = find<identification_policies::by_name, false, false, variable>("j", function_a_b_f.get());
		BOOST_CHECK_EQUAL(found_entity, variable_j.get());
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
					space(""),
					predefined_text_node<str::double_colon>(),
					space(""),
					optional_node<nested_name_specifier_last_part_seq>()
				),
				"n",
				function_a_b_f.get()
			)
		;
		BOOST_CHECK_EQUAL(found_entity, variable_a_c_n.get());
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
					space(""),
					predefined_text_node<str::double_colon>(),
					space(""),
					optional_node<nested_name_specifier_last_part_seq>()
				),
				"i",
				function_a_b_f.get()
			)
		;
		BOOST_CHECK_EQUAL(found_entity, variable_a_i.get());
	}

	//lookup ::i from function test, must find it
	{
		auto found_entity =
			find<identification_policies::by_name, false, false, variable>
			(
				true,
				optional_node<nested_name_specifier>(),
				"i",
				function_a_b_f.get()
			)
		;
		BOOST_CHECK_EQUAL(found_entity, variable_i.get());
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
					space(""),
					predefined_text_node<str::double_colon>(),
					space(""),
					optional_node<nested_name_specifier_last_part_seq>()
				),
				"C",
				function_a_b_f.get()
			)
		;
		BOOST_CHECK_EQUAL(found_entity, namespace_a_c);
	}
}

} //namespace name_lookup

