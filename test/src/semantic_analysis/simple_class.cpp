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

#include "analyzer.hpp"
#include <boost/test/unit_test.hpp>

namespace semantic_analysis
{

BOOST_AUTO_TEST_CASE(simple_class)
{
	using namespace scalpel::cpp::semantic_entities;

	std::shared_ptr<scalpel::cpp::semantic_graph> semantic_graph = analyze
	(
		"class square "
		"{ "
		"	public: "
		"		square(const unsigned int size); "
		" "
		"		unsigned int "
		"		size() const; "
		" "
		"		void "
		"		size(const unsigned int size); "
		" "
		"	private: "
		"		unsigned int size_; "
		"}; "
		" "
		"square::square(const unsigned int size): "
		"	size_(size) "
		"{ "
		"} "
		" "
		"void "
		"square::size(const unsigned int size) "
		"{ "
		"	size_ = size; "
		"} "
		" "
		"unsigned int "
		"square::size() const "
		"{ "
		"	return size_; "
		"} "
	);

	auto expected_semantic_graph = namespace_::make_shared();
	auto class_square = class_::make_shared("square");
	auto constructor_square = std::make_shared<constructor>
	(
		function_parameter_list
		(
			{
				std::make_shared<function_parameter>
				(
					const_
					(
						fundamental_type::UNSIGNED_INT
					),
					"size"
				)
			}
		)
	);
	auto function_square_get_size =
		std::make_shared<simple_member_function>
		(
			"size",
			fundamental_type::UNSIGNED_INT,
			function_parameter_list(),
			false,
			false,
			true
		)
	;
	auto function_square_set_size =
		std::make_shared<simple_member_function>
		(
			"size",
			fundamental_type::VOID,
			function_parameter_list
			(
				{
					std::make_shared<function_parameter>
					(
						const_
						(
							fundamental_type::UNSIGNED_INT
						),
						"size"
					)
				}
			)
		)
	;
	auto variable_square_size = std::make_shared<variable>("size_", fundamental_type::UNSIGNED_INT);

	expected_semantic_graph->add_member(class_square);
	class_square->add_member(constructor_square, class_::access::PUBLIC);
	class_square->add_member(function_square_get_size, class_::access::PUBLIC);
	class_square->add_member(function_square_set_size, class_::access::PUBLIC);
	class_square->add_member(variable_square_size, class_::access::PRIVATE);
	constructor_square->body(std::make_shared<statement_block>());
	function_square_get_size->body(std::make_shared<statement_block>());
	function_square_set_size->body(std::make_shared<statement_block>());

	BOOST_CHECK(*semantic_graph == *expected_semantic_graph);
}

} //namespace semantic_analysis

