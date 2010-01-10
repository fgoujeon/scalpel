/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2010  Florian Goujeon

This file is part of Scalpel.

Scalpel is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Scalpel is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Scalpel.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "operator_function.hpp"
#include <iostream>

namespace scalpel { namespace cpp { namespace semantic_entities
{

operator_function::operator_function
(
	const operator_ op,
	std::shared_ptr<const type> return_type,
	parameters_t&& parameters,
	const bool is_static_specified
):
    op_(op),
	return_type_(return_type),
	parameters_(std::move(parameters)),
	static_specified_(is_static_specified)
{
	std::cout << "New operator function\n";
}

operator_function::operator_function(operator_function&& f):
    op_(f.op_),
	statement_block_(std::move(f.statement_block_)),
	return_type_(f.return_type_),
	parameters_(std::move(f.parameters_)),
	static_specified_(f.static_specified_)
{
}

const operator_function&
operator_function::operator=(operator_function&& f)
{
    op_ = f.op_;
	statement_block_ = std::move(f.statement_block_);
	return_type_ = f.return_type_;
	parameters_ = std::move(f.parameters_);
	static_specified_ = f.static_specified_;

	return *this;
}

bool
operator_function::operator==(const operator_function& f) const
{
	return
		op_ == f.op_ &&
		statement_block_ == f.statement_block_ &&
		return_type_ == f.return_type_ &&
		parameters_ == f.parameters_ &&
		static_specified_ == f.static_specified_
	;
}

bool
operator_function::has_same_signature(const operator_function& f) const
{
	return
		op_ == f.op_ &&
		return_type_ == f.return_type_ &&
		has_same_parameters(f) &&
		static_specified_ == f.static_specified_
	;
}

bool
operator_function::has_same_parameters(const operator_function& f) const
{
	if(parameters_.size() != f.parameters_.size())
		return false;

	for
	(
		parameters_t::const_iterator i = parameters_.begin(), j = f.parameters_.begin();
		i != parameters_.end();
		++i, ++j
	)
	{
		auto param = *i;
		auto param2 = *j;
		if(param.get_type() != param2.get_type())
			return false;
	}

	return true;
}

operator_
operator_function::get_operator() const
{
	return op_;
}

std::shared_ptr<const type>
operator_function::return_type() const
{
	return return_type_;
}

const std::list<operator_function::parameter>&
operator_function::parameters() const
{
	return parameters_;
}

bool
operator_function::static_specified() const
{
	return static_specified_;
}

bool
operator_function::defined() const
{
	return defined_;
}

void
operator_function::defined(bool d)
{
	defined_ = d;
}

}}} //namespace scalpel::cpp::semantic_entities
