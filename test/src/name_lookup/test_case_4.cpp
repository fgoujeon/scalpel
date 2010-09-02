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

#include "test_case_4.hpp"
#include <scalpel/cpp/detail/semantic_analysis/name_lookup.hpp>
#include <scalpel/cpp/semantic_graph.hpp>
#include <scalpel/cpp/syntax_tree.hpp>
#include <boost/test/unit_test.hpp>

namespace name_lookup
{

void
test_case_4()
{
	using namespace scalpel::cpp::syntax_nodes;
	using namespace scalpel::cpp::semantic_entities;
	using namespace scalpel::cpp::detail::semantic_analysis::name_lookup;

	//
	//construction of the semantic graph of the following source code:
	/*
	namespace m
	{
		int i;
	}

	namespace n
	{
		int i;
		using namespace m;
	}

	void f()
	{
		using namespace n;
		i = 7; // error: both m::i and n::i are visible
	}
	*/

	//namespaces
	auto semantic_graph = scalpel::cpp::semantic_graph::make_shared();
	auto namespace_m = namespace_::make_shared("m");
	auto namespace_n = namespace_::make_shared("n");

	//functions
	auto function_f = simple_function::make_shared
	(
		"f",
		fundamental_type_shared_ptrs::void_
	);

	//variables
	auto variable_m_i = std::make_shared<variable>
	(
		"i",
		fundamental_type_shared_ptrs::int_
	);
	auto variable_n_i = std::make_shared<variable>
	(
		"i",
		fundamental_type_shared_ptrs::int_
	);

	//assembling
	semantic_graph->add_member(namespace_m);
	namespace_m->add_member(variable_m_i);
	semantic_graph->add_member(namespace_n);
	namespace_n->add_member(variable_n_i);
	namespace_n->add_using_directive_namespace(namespace_m);
	semantic_graph->add_member(function_f);
	function_f->body(std::make_shared<statement_block>());
	function_f->body()->add_using_directive_namespace(namespace_n);



	//
	//name lookup test
	//

	//look up i from f(), must find m::i and n::i
	{
		auto found_entities = find<variable, false, true>(identifier("i"), function_f->body());
		BOOST_CHECK_EQUAL(found_entities.size(), 2);
		if(found_entities.size() == 2)
		{
			BOOST_CHECK(found_entities.find(variable_m_i) != found_entities.end());
			BOOST_CHECK(found_entities.find(variable_n_i) != found_entities.end());
		}
	}
}

} //namespace name_lookup

