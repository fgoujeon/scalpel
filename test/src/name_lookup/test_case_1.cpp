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
	int find_me;

	namespace A
	{
		int find_me;

		namespace B
		{
			void f();
		}
	}

	void A::N::f()
	{
		//look from here
	}
	*/
	auto semantic_graph = std::make_shared<scalpel::cpp::semantic_graph>();
	auto variable_find_me = std::make_shared<scalpel::cpp::semantic_entities::variable>
	(
		"find_me",
		scalpel::cpp::semantic_entities::built_in_type_shared_ptrs::int_
	);
	auto namespace_a = std::make_shared<scalpel::cpp::semantic_entities::namespace_>("A");
	auto variable_find_me2 = std::make_shared<scalpel::cpp::semantic_entities::variable>
	(
		"find_me",
		scalpel::cpp::semantic_entities::built_in_type_shared_ptrs::int_
	);
	auto namespace_n = std::make_shared<scalpel::cpp::semantic_entities::namespace_>("N");
	auto function_f = std::make_shared<scalpel::cpp::semantic_entities::simple_function>
	(
		"f",
		scalpel::cpp::semantic_entities::built_in_type_shared_ptrs::void_
	);

	semantic_graph->add(namespace_a);
	semantic_graph->add(variable_find_me2);
	namespace_a->add(variable_find_me);
	namespace_a->add(namespace_n);
	namespace_n->add(function_f);



	//
	//scope path construction
	//
	scalpel::utility::shared_ptr_vector<scalpel::cpp::semantic_entities::scope> scope_path;
	scope_path.push_back(semantic_graph);
	scope_path.push_back(namespace_a);
	scope_path.push_back(namespace_n);
	scope_path.push_back(function_f);



	//
	//name lookup test
	//
	auto found_entities = scalpel::cpp::detail::semantic_analysis::name_lookup2::find_entities(scope_path, "find_me");
	BOOST_CHECK_EQUAL(found_entities.size(), 1);
	BOOST_CHECK_EQUAL(found_entities.front(), variable_find_me);
}

} //namespace name_lookup

