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
#include <scalpel/utility/null_deleter.hpp>
#include <boost/test/unit_test.hpp>

namespace name_lookup
{

void
test_case_1()
{
	//
	//construction of the semantic graph of the following source code:
	/*
	 *
	 *
	struct B0
	{
		int n;
	};

	namespace A
	{
		int i;

		struct B: public B0
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
		n;
	}
	*/
	auto semantic_graph = std::make_shared<scalpel::cpp::semantic_graph>();
	auto struct_b0 = std::make_shared<scalpel::cpp::semantic_entities::class_>("B0");
	auto variable_b0_n = std::make_shared<scalpel::cpp::semantic_entities::variable>
	(
		"n",
		scalpel::cpp::semantic_entities::built_in_type_shared_ptrs::int_
	);
	auto namespace_a = std::make_shared<scalpel::cpp::semantic_entities::namespace_>("A");
	auto variable_a_i = std::make_shared<scalpel::cpp::semantic_entities::variable>
	(
		"i",
		scalpel::cpp::semantic_entities::built_in_type_shared_ptrs::int_
	);
	auto variable_i = std::make_shared<scalpel::cpp::semantic_entities::variable>
	(
		"i",
		scalpel::cpp::semantic_entities::built_in_type_shared_ptrs::int_
	);
	auto variable_j = std::make_shared<scalpel::cpp::semantic_entities::variable>
	(
		"j",
		scalpel::cpp::semantic_entities::built_in_type_shared_ptrs::int_
	);
	auto struct_a_b = std::make_shared<scalpel::cpp::semantic_entities::class_>("B");
	auto function_a_b_f = std::make_shared<scalpel::cpp::semantic_entities::simple_function>
	(
		"f",
		scalpel::cpp::semantic_entities::built_in_type_shared_ptrs::void_
	);
	auto function_g = std::make_shared<scalpel::cpp::semantic_entities::simple_function>
	(
		"g",
		scalpel::cpp::semantic_entities::built_in_type_shared_ptrs::void_
	);
	auto namespace_c = std::make_shared<scalpel::cpp::semantic_entities::namespace_>("C");

	semantic_graph->add(namespace_a);
	semantic_graph->add(struct_b0);
	struct_b0->add
	(
		variable_b0_n,
		scalpel::cpp::semantic_entities::class_::access::PUBLIC
	);
	namespace_a->add(variable_a_i);
	namespace_a->add(struct_a_b);
	struct_a_b->add
	(
		function_a_b_f,
		scalpel::cpp::semantic_entities::class_::access::PUBLIC,
		false,
		false,
		false,
		false
	);
	namespace_a->add(function_g);
	namespace_a->add(namespace_c);
	semantic_graph->add(variable_i);
	semantic_graph->add(variable_j);



	//
	//declarative region path construction
	//
	scalpel::utility::shared_ptr_vector<scalpel::cpp::semantic_entities::declarative_region> declarative_region_path;
	declarative_region_path.push_back(semantic_graph);
	declarative_region_path.push_back(namespace_a);
	declarative_region_path.push_back(struct_a_b);
	declarative_region_path.push_back(function_a_b_f);



	//
	//name lookup test
	//
	{
		auto found_entities = scalpel::cpp::detail::semantic_analysis::name_lookup2::find_entities(declarative_region_path, "i");
		BOOST_CHECK_EQUAL(found_entities.size(), 1);
		BOOST_CHECK_EQUAL(found_entities.front(), variable_a_i);
	}

	{
		auto found_entities = scalpel::cpp::detail::semantic_analysis::name_lookup2::find_entities(declarative_region_path, "j");
		BOOST_CHECK_EQUAL(found_entities.size(), 1);
		BOOST_CHECK_EQUAL(found_entities.front(), variable_j);
	}

	{
		auto found_declarative_region = scalpel::cpp::detail::semantic_analysis::name_lookup2::find_open_declarative_region(declarative_region_path, "C");
		BOOST_CHECK_EQUAL(found_declarative_region, namespace_c);
	}

	{
		auto found_declarative_region = scalpel::cpp::detail::semantic_analysis::name_lookup2::find_open_declarative_region(declarative_region_path, "g");
		BOOST_CHECK(found_declarative_region.get() == 0);
	}
}

} //namespace name_lookup

