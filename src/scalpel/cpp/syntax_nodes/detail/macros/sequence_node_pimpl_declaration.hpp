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

#include "../../common.hpp"
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/seq.hpp>
#include <memory>

#define SCALPEL_SEQUENCE_NODE_PIMPL_DECLARATION_CONSTRUCTOR_PARAMETER(r, x, n, node_type) \
(node_type&& o##n)

#define SCALPEL_SEQUENCE_NODE_PIMPL_DECLARATION(sequence_node_type, type_seq)          \
class sequence_node_type                                                               \
{                                                                                      \
	public:                                                                            \
		typedef                                                                        \
			sequence_node                                                              \
			<                                                                          \
				BOOST_PP_SEQ_ENUM(type_seq)                                            \
			>                                                                          \
			type                                                                       \
		;                                                                              \
		typedef BOOST_PP_SEQ_HEAD(type_seq) head_node_t;                               \
		typedef                                                                        \
			sequence_node                                                              \
			<                                                                          \
				BOOST_PP_SEQ_ENUM(BOOST_PP_SEQ_TAIL(type_seq))                         \
			>                                                                          \
			tail_sequence_node_t                                                       \
		;                                                                              \
                                                                                       \
		sequence_node_type                                                             \
		(                                                                              \
			BOOST_PP_SEQ_ENUM                                                          \
			(                                                                          \
				BOOST_PP_SEQ_FOR_EACH_I                                                \
				(                                                                      \
					SCALPEL_SEQUENCE_NODE_PIMPL_DECLARATION_CONSTRUCTOR_PARAMETER,     \
					~,                                                                 \
					type_seq                                                           \
				)                                                                      \
			)                                                                          \
		);                                                                             \
                                                                                       \
		sequence_node_type                                                             \
		(                                                                              \
			const head_node_t& head,                                                   \
			const tail_sequence_node_t& tail                                           \
		);                                                                             \
                                                                                       \
		sequence_node_type(const sequence_node_type& o);                               \
                                                                                       \
		sequence_node_type(sequence_node_type&& o);                                    \
                                                                                       \
		~sequence_node_type();                                                         \
                                                                                       \
		const sequence_node_type&                                                      \
		operator=(const sequence_node_type& o);                                        \
                                                                                       \
		const head_node_t&                                                             \
		head() const;                                                                  \
                                                                                       \
		const tail_sequence_node_t&                                                    \
		tail() const;                                                                  \
                                                                                       \
	private:                                                                           \
		std::unique_ptr<type> impl_;                                                   \
};

