/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2010  Florian Goujeon

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

#include "test_case_1.hpp"
#include <scalpel/cpp/detail/semantic_analysis/name_lookup.hpp>
#include <scalpel/cpp/semantic_graph.hpp>
#include <scalpel/cpp/syntax_tree.hpp>
#include <boost/test/unit_test.hpp>

namespace name_lookup
{

void
test_case_1()
{
	using namespace scalpel::cpp::syntax_nodes;
	using namespace scalpel::cpp::semantic_entities;
	using namespace scalpel::cpp::detail::semantic_analysis::name_lookup;
	using namespace scalpel::cpp::detail::semantic_analysis::semantic_entity_analysis;

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

	auto semantic_graph = scalpel::cpp::semantic_graph::make_shared();
	auto namespace_a = namespace_::make_shared("A");
	auto variable_a_i = std::make_shared<variable>
	(
		"i",
		fundamental_type_shared_ptrs::int_
	);
	auto struct_a_b = class_::make_shared("B");
	auto function_a_b_f = std::make_shared<simple_member_function>
	(
		"f",
		fundamental_type_shared_ptrs::void_
	);
	auto function_a_g = std::make_shared<simple_function>
	(
		"g",
		fundamental_type_shared_ptrs::void_
	);
	auto namespace_a_c = namespace_::make_shared("C");
	auto variable_a_c_n = std::make_shared<variable>
	(
		"n",
		fundamental_type_shared_ptrs::int_
	);
	auto variable_i = std::make_shared<variable>
	(
		"i",
		fundamental_type_shared_ptrs::int_
	);
	auto variable_j = std::make_shared<variable>
	(
		"j",
		fundamental_type_shared_ptrs::int_
	);

	semantic_graph->add_member(namespace_a);
	namespace_a->add_member(variable_a_i);
	namespace_a->add_member(struct_a_b);
	struct_a_b->add_member(function_a_b_f);
	namespace_a->add_member(function_a_g);
	namespace_a->add_member(namespace_a_c);
	namespace_a_c->add_member(variable_a_c_n);
	semantic_graph->add_member(variable_i);
	semantic_graph->add_member(variable_j);



	//
	//name lookup test
	//

	//lookup i from function test, must find it
	{
		auto found_entity = find<identifier_getting_policies::get_name, false, false, variable>("i", function_a_b_f);
		BOOST_CHECK_EQUAL(found_entity, variable_a_i);
	}

	//lookup j from function test, must find it
	{
		auto found_entity = find<identifier_getting_policies::get_name, false, false, variable>("j", function_a_b_f);
		BOOST_CHECK_EQUAL(found_entity, variable_j);
	}

	//lookup B from itself, must find it
	{
		auto found_entity = find<identifier_getting_policies::get_name, false, false, class_>("B", struct_a_b);
		BOOST_CHECK_EQUAL(found_entity, struct_a_b);
	}

	//lookup C::n from function test, must find it
	{
		auto found_entity =
			find<identifier_getting_policies::get_name, false, false, variable>
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
				function_a_b_f
			)
		;
		BOOST_CHECK_EQUAL(found_entity, variable_a_c_n);
	}

	//lookup ::A::i from function test, must find it
	{
		auto found_entity =
			find<identifier_getting_policies::get_name, false, false, variable>
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
				function_a_b_f
			)
		;
		BOOST_CHECK_EQUAL(found_entity, variable_a_i);
	}

	//lookup ::i from function test, must find it
	{
		auto found_entity =
			find<identifier_getting_policies::get_name, false, false, variable>
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
			find<identifier_getting_policies::get_name, false, false, namespace_>
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
				function_a_b_f
			)
		;
		BOOST_CHECK_EQUAL(found_entity, namespace_a_c);
	}
}

} //namespace name_lookup

