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

BOOST_AUTO_TEST_CASE(test_case_13)
{
	using namespace scalpel::cpp::syntax_nodes;
	using namespace scalpel::cpp::semantic_entities;
	using namespace scalpel::cpp::semantic_analysis::detail::name_lookup;
	using namespace scalpel::cpp::semantic_analysis::detail::semantic_entity_analysis;

	//
	//construction of the semantic graph of the following source code:
	/*
		namespace a
		{
			int i;
		}

		using namespace a;

		int i;

		void f()
		{
			i++;
		}
	*/

	//namespaces
	scalpel::cpp::semantic_graph semantic_graph;
	auto namespace_a = new namespace_("a");

	//functions
	auto function_f = new simple_function
	(
		"f",
		fundamental_type::VOID
	);

	//variables
	auto variable_a_i = new variable
	(
		"i",
		fundamental_type::INT
	);
	auto variable_i = new variable
	(
		"i",
		fundamental_type::INT
	);

	//assembling
	semantic_graph.add_member(std::unique_ptr<namespace_>(namespace_a));
	namespace_a->add_member(std::unique_ptr<variable>(variable_a_i));
	semantic_graph.add_using_directive_namespace(*namespace_a);
	semantic_graph.add_member(std::unique_ptr<variable>(variable_i));
	semantic_graph.add_member(std::unique_ptr<simple_function>(function_f));



	//
	//name lookup test
	//

	//look up i from function f(), must find i and a::i
	{
		auto found_entities =
			find<identification_policies::by_name, false, true, variable>
			(
				"i",
				function_f
			)
		;

		BOOST_CHECK(found_entities.size() == 2);
		if(found_entities.size() == 2)
		{
			BOOST_CHECK(found_entities.find(variable_i) != found_entities.end());
			BOOST_CHECK(found_entities.find(variable_a_i) != found_entities.end());
		}
	}
}

} //namespace name_lookup

