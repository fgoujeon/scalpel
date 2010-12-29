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

BOOST_AUTO_TEST_CASE(cycle_proof_equality3)
{
	using namespace scalpel::cpp::semantic_entities;

	//struct a;
	//
	//struct b
	//{
	//	a* ptr;
	//};
	//
	//struct a: b
	//{
	//};

	auto semantic_graph_1 = namespace_::make_shared();
	auto class_a_1 = class_::make_shared("a");
	auto class_b_1 = class_::make_shared("b");
	auto variable_b_ptr_1 =
		std::make_shared<variable>
		(
			"ptr",
			pointer
			(
				std::shared_ptr<const class_>(class_a_1)
			)
		)
	;
	semantic_graph_1->add_member(class_a_1);
	semantic_graph_1->add_member(class_b_1);
	class_b_1->add_member(variable_b_ptr_1);
	class_a_1->add_base_class(class_b_1);

	auto semantic_graph_2 = namespace_::make_shared();
	auto class_a_2 = class_::make_shared("a");
	auto class_b_2 = class_::make_shared("b");
	auto variable_b_ptr_2 =
		std::make_shared<variable>
		(
			"ptr",
			pointer
			(
				std::shared_ptr<const class_>(class_a_2)
			)
		)
	;
	semantic_graph_2->add_member(class_a_2);
	semantic_graph_2->add_member(class_b_2);
	class_b_2->add_member(variable_b_ptr_2);
	class_a_2->add_base_class(class_b_2);

	BOOST_CHECK(false); //the test below currently causes a segmentation fault
	//BOOST_CHECK(*semantic_graph_1 == *semantic_graph_2);
}

} //namespace semantic_graph

