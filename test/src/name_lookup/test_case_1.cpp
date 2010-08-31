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
		//look from here
	}
	*/

	auto semantic_graph = scalpel::cpp::semantic_graph::make_shared();
	auto namespace_a = namespace_::make_shared("A");
	auto variable_a_i = std::make_shared<variable>
	(
		"i",
		built_in_type_shared_ptrs::int_
	);
	auto struct_a_b = class_::make_shared("B");
	auto function_a_b_f = simple_function::make_shared
	(
		"f",
		built_in_type_shared_ptrs::void_
	);
	auto function_a_g = simple_function::make_shared
	(
		"g",
		built_in_type_shared_ptrs::void_
	);
	auto namespace_a_c = namespace_::make_shared("C");
	auto variable_a_c_n = std::make_shared<variable>
	(
		"n",
		built_in_type_shared_ptrs::int_
	);
	auto variable_i = std::make_shared<variable>
	(
		"i",
		built_in_type_shared_ptrs::int_
	);
	auto variable_j = std::make_shared<variable>
	(
		"j",
		built_in_type_shared_ptrs::int_
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

	//find i
	{
		auto found_entity = find_entities<false, false, variable>(identifier("i"), function_a_b_f);
		BOOST_CHECK_EQUAL(found_entity, variable_a_i);
	}

	//find j
	{
		auto found_entity = find_entities<false, false, variable>(identifier("j"), function_a_b_f);
		BOOST_CHECK_EQUAL(found_entity, variable_j);
	}

	//find C::n
	{
		nested_identifier_or_template_id variable_a_c_n_syntax_node
		(
			optional_node<predefined_text_node<str::double_colon>>(),
			space(""),
			nested_name_specifier
			(
				identifier("C"),
				space(""),
				predefined_text_node<str::double_colon>(),
				space(""),
				optional_node<nested_name_specifier_last_part_seq>()
			),
			space(""),
			identifier("n")
		);
		auto found_entity = find_entities<false, false, variable>(variable_a_c_n_syntax_node, function_a_b_f);
		BOOST_CHECK_EQUAL(found_entity, variable_a_c_n);
	}

	//find ::A::i
	{
		nested_identifier_or_template_id variable_a_i_syntax_node
		(
			predefined_text_node<str::double_colon>(),
			space(""),
			nested_name_specifier
			(
				identifier("A"),
				space(""),
				predefined_text_node<str::double_colon>(),
				space(""),
				optional_node<nested_name_specifier_last_part_seq>()
			),
			space(""),
			identifier("i")
		);
		auto found_entity = find_entities<false, false, variable>(variable_a_i_syntax_node, function_a_b_f);
		BOOST_CHECK_EQUAL(found_entity, variable_a_i);
	}

	//find ::i
	{
		nested_identifier_or_template_id variable_i_syntax_node
		(
			predefined_text_node<str::double_colon>(),
			space(""),
			optional_node<nested_name_specifier>(),
			space(""),
			identifier("i")
		);
		auto found_entity = find_entities<false, false, variable>(variable_i_syntax_node, function_a_b_f);
		BOOST_CHECK_EQUAL(found_entity, variable_i);
	}

	//find namespace A::C
	{
		nested_identifier_or_template_id a_c_syntax_node
		(
			optional_node<predefined_text_node<str::double_colon>>(),
			space(""),
			nested_name_specifier
			(
				identifier("A"),
				space(""),
				predefined_text_node<str::double_colon>(),
				space(""),
				optional_node<nested_name_specifier_last_part_seq>()
			),
			space(""),
			identifier("C")
		);
		auto found_entity = find_entities<false, false, namespace_>(a_c_syntax_node, function_a_b_f);
		BOOST_CHECK_EQUAL(found_entity, namespace_a_c);
	}
}

} //namespace name_lookup

