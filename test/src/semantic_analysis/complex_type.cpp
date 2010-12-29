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

BOOST_AUTO_TEST_CASE(complex_type)
{
	using namespace scalpel::cpp::semantic_entities;

	std::shared_ptr<scalpel::cpp::semantic_graph> semantic_graph = analyze
	(
		"const int unsigned long* const volatile** const**** i, j;"
	);

	auto expected_semantic_graph = namespace_::make_shared();
	auto variable_i = std::make_shared<variable>
	(
		"i",
		std::make_shared<const pointer>
		(
			std::make_shared<const pointer>
			(
				std::make_shared<const pointer>
				(
					std::make_shared<const pointer>
					(
						std::make_shared<const const_>
						(
							std::make_shared<const pointer>
							(
								std::make_shared<const pointer>
								(
									std::make_shared<const volatile_>
									(
										std::make_shared<const const_>
										(
											std::make_shared<const pointer>
											(
												std::make_shared<const const_>
												(
													fundamental_type::UNSIGNED_LONG_INT
												)
											)
										)
									)
								)
							)
						)
					)
				)
			)
		)
	);
	auto variable_j = std::make_shared<variable>
	(
		"j",
		std::make_shared<const const_>
		(
			fundamental_type::UNSIGNED_LONG_INT
		)
	);

	expected_semantic_graph->add_member(variable_i);
	expected_semantic_graph->add_member(variable_j);

	BOOST_CHECK(*semantic_graph == *expected_semantic_graph);
}

} //namespace semantic_analysis

