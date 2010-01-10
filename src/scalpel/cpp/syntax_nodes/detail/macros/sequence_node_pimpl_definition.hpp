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

#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/seq.hpp>

#define SCALPEL_SEQUENCE_NODE_PIMPL_DEFINITION_CONSTRUCTOR_PARAMETER(r, x, n, node_type) \
(node_type&& o##n)

#define SCALPEL_SEQUENCE_NODE_PIMPL_DEFINITION_TYPE_CONSTRUCTION_ARGUMENT(r, x, n, node_type) \
(std::move(o##n))

#define SCALPEL_SEQUENCE_NODE_PIMPL_DEFINITION(sequence_node_type, type_seq)             \
sequence_node_type::sequence_node_type                                                   \
(                                                                                        \
	BOOST_PP_SEQ_ENUM                                                                    \
	(                                                                                    \
		BOOST_PP_SEQ_FOR_EACH_I                                                          \
		(                                                                                \
			SCALPEL_SEQUENCE_NODE_PIMPL_DEFINITION_CONSTRUCTOR_PARAMETER,                \
			~,                                                                           \
			type_seq                                                                     \
		)                                                                                \
	)                                                                                    \
):                                                                                       \
	impl_                                                                                \
	(                                                                                    \
		new type                                                                         \
		(                                                                                \
			BOOST_PP_SEQ_ENUM                                                            \
			(                                                                            \
				BOOST_PP_SEQ_FOR_EACH_I                                                  \
				(                                                                        \
					SCALPEL_SEQUENCE_NODE_PIMPL_DEFINITION_TYPE_CONSTRUCTION_ARGUMENT,   \
					~,                                                                   \
					type_seq                                                             \
				)                                                                        \
			)                                                                            \
		)                                                                                \
	)                                                                                    \
{                                                                                        \
}                                                                                        \
                                                                                         \
sequence_node_type::sequence_node_type                                                   \
(                                                                                        \
	head_node_t&& head,                                                                  \
	tail_sequence_node_t&& tail                                                          \
):                                                                                       \
	impl_(new type(std::move(head), std::move(tail)))                                    \
{                                                                                        \
}                                                                                        \
                                                                                         \
sequence_node_type::sequence_node_type(const sequence_node_type& o):                     \
	impl_(new type(*o.impl_))                                                            \
{                                                                                        \
}                                                                                        \
                                                                                         \
sequence_node_type::sequence_node_type(sequence_node_type&& o):                          \
	impl_(std::move(o.impl_))                                                            \
{                                                                                        \
}                                                                                        \
                                                                                         \
sequence_node_type::~sequence_node_type()                                                \
{                                                                                        \
}                                                                                        \
                                                                                         \
const sequence_node_type&                                                                \
sequence_node_type::operator=(const sequence_node_type& o)                               \
{                                                                                        \
	*impl_ = *o.impl_;                                                                   \
	return *this;                                                                        \
}                                                                                        \
                                                                                         \
const sequence_node_type::head_node_t&                                                   \
sequence_node_type::head() const                                                         \
{                                                                                        \
	return impl_->head();                                                                \
}                                                                                        \
																				         \
const sequence_node_type::tail_sequence_node_t&                                          \
sequence_node_type::tail() const                                                         \
{                                                                                        \
	return impl_->tail();                                                                \
}

