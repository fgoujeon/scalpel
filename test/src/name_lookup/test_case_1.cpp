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
#include <scalpel/cpp/detail/semantic_analysis/name_lookup2.hpp>
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
	using namespace scalpel::cpp::detail::semantic_analysis;

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
		i;
		j;
		C::n;
		::A::i;
		::i;
	}
	*/
	auto semantic_graph = std::make_shared<scalpel::cpp::semantic_graph>();
	auto namespace_a = std::make_shared<namespace_>("A");
	auto variable_a_i = std::make_shared<variable>
	(
		"i",
		built_in_type_shared_ptrs::int_
	);
	auto struct_a_b = std::make_shared<class_>("B");
	auto function_a_b_f = std::make_shared<simple_function>
	(
		"f",
		built_in_type_shared_ptrs::void_
	);
	auto function_a_g = std::make_shared<simple_function>
	(
		"g",
		built_in_type_shared_ptrs::void_
	);
	auto namespace_a_c = std::make_shared<namespace_>("C");
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

	semantic_graph->add(namespace_a);
	namespace_a->add(variable_a_i);
	namespace_a->add(struct_a_b);
	struct_a_b->add(function_a_b_f);
	namespace_a->add(function_a_g);
	namespace_a->add(namespace_a_c);
	namespace_a_c->add(variable_a_c_n);
	semantic_graph->add(variable_i);
	semantic_graph->add(variable_j);



	//
	//declarative region path construction
	//
	std::vector<declarative_region_variant> declarative_region_path;
	declarative_region_path.push_back(semantic_graph);
	declarative_region_path.push_back(namespace_a);
	declarative_region_path.push_back(struct_a_b);
	declarative_region_path.push_back(function_a_b_f->body());


	//
	//name lookup test
	//
	{
		auto found_entity = name_lookup2::find_entities<false, variable>(identifier("i"), declarative_region_path);
		BOOST_CHECK_EQUAL(found_entity, variable_a_i);
	}

	{
		auto found_entity = name_lookup2::find_entities<false, variable>(identifier("j"), declarative_region_path);
		BOOST_CHECK_EQUAL(found_entity, variable_j);
	}

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
		auto found_entities = name_lookup2::find_entities<variable>(variable_a_c_n_syntax_node, declarative_region_path);
		BOOST_CHECK_EQUAL(found_entities.size(), 1);
		if(found_entities.size() == 1)
		{
			BOOST_CHECK_EQUAL(found_entities.front(), variable_a_c_n);
		}
	}

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
		auto found_entities = name_lookup2::find_entities<variable>(variable_a_i_syntax_node, declarative_region_path);
		BOOST_CHECK_EQUAL(found_entities.size(), 1);
		if(found_entities.size() == 1)
		{
			BOOST_CHECK_EQUAL(found_entities.front(), variable_a_i);
		}
	}

	{
		nested_identifier_or_template_id variable_i_syntax_node
		(
			predefined_text_node<str::double_colon>(),
			space(""),
			optional_node<nested_name_specifier>(),
			space(""),
			identifier("i")
		);
		auto found_entities = name_lookup2::find_entities<variable>(variable_i_syntax_node, declarative_region_path);
		BOOST_CHECK_EQUAL(found_entities.size(), 1);
		if(found_entities.size() == 1)
		{
			BOOST_CHECK_EQUAL(found_entities.front(), variable_i);
		}
	}
}

} //namespace name_lookup

