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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_FUNCTION_CALL_IPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_FUNCTION_CALL_IPP

namespace scalpel { namespace cpp { namespace semantic_entities
{

template<class Function>
function_call<Function>::function_call
(
	Function& function,
	const std::vector<expression_t>& arguments
):
	function_(function),
	arguments_(arguments)
{
}

}}} //namespace scalpel::cpp::semantic_entities

#endif

