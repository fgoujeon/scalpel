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

#include "test_case_2.hpp"
#include <scalpel/cpp/detail/semantic_analysis/name_lookup2.hpp>
#include <scalpel/cpp/semantic_graph.hpp>
#include <boost/test/unit_test.hpp>

namespace name_lookup
{

void
test_case_2()
{
	//
	//construction of the semantic graph of the following source code:
	/*
	struct c0
	{
		void f();
	};

	struct c1base
	{
		void f();
		void g();
	};

	struct c1: public c1base
	{
		void g();
	};

	struct c: public c0, public c1
	{
		void test()
		{
			//look from here
			f();
		}
	};
	*/
	auto semantic_graph = std::make_shared<scalpel::cpp::semantic_graph>();
	auto struct_c0 = std::make_shared<scalpel::cpp::semantic_entities::class_>("c0");
	auto function_c0_f = std::make_shared<scalpel::cpp::semantic_entities::simple_function>
	(
		"f",
		scalpel::cpp::semantic_entities::built_in_type_shared_ptrs::void_
	);
	auto struct_c1base = std::make_shared<scalpel::cpp::semantic_entities::class_>("c1base");
	auto function_c1base_f = std::make_shared<scalpel::cpp::semantic_entities::simple_function>
	(
		"f",
		scalpel::cpp::semantic_entities::built_in_type_shared_ptrs::void_
	);
	auto function_c1base_g = std::make_shared<scalpel::cpp::semantic_entities::simple_function>
	(
		"g",
		scalpel::cpp::semantic_entities::built_in_type_shared_ptrs::void_
	);
	auto struct_c1 = std::make_shared<scalpel::cpp::semantic_entities::class_>("c1");
	auto function_c1_g = std::make_shared<scalpel::cpp::semantic_entities::simple_function>
	(
		"g",
		scalpel::cpp::semantic_entities::built_in_type_shared_ptrs::void_
	);
	auto struct_c = std::make_shared<scalpel::cpp::semantic_entities::class_>("c");
	auto function_g_test = std::make_shared<scalpel::cpp::semantic_entities::simple_function>
	(
		"test",
		scalpel::cpp::semantic_entities::built_in_type_shared_ptrs::void_
	);

	semantic_graph->add(struct_c0);
	struct_c0->add(function_c0_f);
	semantic_graph->add(struct_c1base);
	struct_c1base->add(function_c1base_f);
	struct_c1base->add(function_c1base_g);
	semantic_graph->add(struct_c1);
	struct_c1->add_base_class(struct_c1base);
	struct_c1->add(function_c1_g);
	semantic_graph->add(struct_c);
	struct_c->add_base_class(struct_c0);
	struct_c->add_base_class(struct_c1);
	struct_c->add(function_g_test);



	//
	//declarative region path construction
	//
	scalpel::utility::shared_ptr_vector<scalpel::cpp::semantic_entities::declarative_region> declarative_region_path;
	declarative_region_path.push_back(semantic_graph);
	declarative_region_path.push_back(struct_c);
	declarative_region_path.push_back(function_g_test);



	//
	//name lookup test
	//
	{
		auto found_entities = scalpel::cpp::detail::semantic_analysis::name_lookup2::find_entities(declarative_region_path, "f");
		BOOST_CHECK_EQUAL(found_entities.size(), 2);
		BOOST_CHECK_EQUAL(found_entities.front(), function_c0_f);
		BOOST_CHECK_EQUAL(found_entities.back(), function_c1base_f);
	}

	{
		auto found_entities = scalpel::cpp::detail::semantic_analysis::name_lookup2::find_entities(declarative_region_path, "g");
		BOOST_CHECK_EQUAL(found_entities.size(), 1);
		BOOST_CHECK_EQUAL(found_entities.front(), function_c1_g);
	}
}

} //namespace name_lookup

