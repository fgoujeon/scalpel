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

#include <scalpel/cpp/semantic_graph.hpp>
#include <boost/test/unit_test.hpp>

namespace semantic_graph
{

BOOST_AUTO_TEST_CASE(cycle_proof_equality)
{
	using namespace scalpel::cpp::semantic_entities;

	auto semantic_graph_1 = namespace_::make_shared();
	auto class_test_1 = class_::make_shared("test");
	auto variable_test_ptr_1 =
		std::make_shared<variable>
		(
			"ptr",
			pointer
			(
				std::shared_ptr<const class_>(class_test_1)
			)
		)
	;
	semantic_graph_1->add_member(class_test_1);
	class_test_1->add_member(variable_test_ptr_1);

	auto semantic_graph_2 = namespace_::make_shared();
	auto class_test_2 = class_::make_shared("test");
	auto variable_test_ptr_2 =
		std::make_shared<variable>
		(
			"ptr",
			pointer
			(
				std::shared_ptr<const class_>(class_test_2)
			)
		)
	;
	semantic_graph_2->add_member(class_test_2);
	class_test_2->add_member(variable_test_ptr_2);

	auto semantic_graph_3 = namespace_::make_shared();
	auto class_test_3 = class_::make_shared("test");
	auto variable_test_ptr_3 =
		std::make_shared<variable>
		(
			"ptr",
			pointer
			(
				const_
				(
					std::shared_ptr<const class_>(class_test_3)
				)
			)
		)
	;
	semantic_graph_3->add_member(class_test_3);
	class_test_3->add_member(variable_test_ptr_3);

	auto semantic_graph_4 = namespace_::make_shared();
	auto class_test_4 = class_::make_shared("test");
	auto variable_test_ptr_4 =
		std::make_shared<variable>
		(
			"ptr",
			reference
			(
				std::shared_ptr<const class_>(class_test_4)
			)
		)
	;
	semantic_graph_4->add_member(class_test_4);
	class_test_4->add_member(variable_test_ptr_4);

	BOOST_CHECK(*semantic_graph_1 == *semantic_graph_2);
	BOOST_CHECK(*semantic_graph_1 != *semantic_graph_3);
	BOOST_CHECK(*semantic_graph_1 != *semantic_graph_4);
}

} //namespace semantic_graph

