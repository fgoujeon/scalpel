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
	namespace A
	{
		namespace find_me{}

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
	auto namespace_a = std::make_shared<scalpel::cpp::semantic_entities::namespace_>("A");
	auto namespace_n = std::make_shared<scalpel::cpp::semantic_entities::namespace_>("N");
	auto function_f = std::make_shared<scalpel::cpp::semantic_entities::simple_function>
	(
		"f",
		std::shared_ptr<const scalpel::cpp::semantic_entities::built_in_type>(&scalpel::cpp::semantic_entities::built_in_type::void_, scalpel::utility::null_deleter()),
		std::list<scalpel::cpp::semantic_entities::simple_function::parameter>(),
		false
	);
	auto namespace_find_me = std::make_shared<scalpel::cpp::semantic_entities::namespace_>("find_me");

	semantic_graph->add(namespace_a);
	namespace_a->add(namespace_find_me);
	namespace_a->add(namespace_n);
	namespace_n->add(function_f);



	//
	//scope path construction
	//
	std::vector<std::shared_ptr<scalpel::cpp::semantic_entities::named_scope>> scope_path;
	scope_path.push_back(semantic_graph);
	scope_path.push_back(namespace_a);
	scope_path.push_back(namespace_n);
	//scope_path.push_back(function_f);



	//
	//name lookup test
	//
	std::shared_ptr<scalpel::cpp::semantic_entities::named_entity> found_entity = scalpel::cpp::detail::semantic_analysis::name_lookup::find_name(scope_path, "find_me");
	BOOST_CHECK_EQUAL(found_entity, namespace_find_me);
}

} //namespace name_lookup

