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

#define SCALPEL_ALTERNATIVE_NODE_PIMPL_DECLARATION_CONSTRUCTOR(r, alternative_node_type, type) \
alternative_node_type(type&& o);

#define SCALPEL_ALTERNATIVE_NODE_PIMPL_DECLARATION_GET_FUNCTION(r, x, type) \
void                                           \
get(boost::optional<const type&>& node) const; \

#define SCALPEL_ALTERNATIVE_NODE_PIMPL_DECLARATION(alternative_node_type, type_seq) \
class alternative_node_type                                                         \
{                                                                                   \
	public:                                                                         \
		typedef                                                                     \
			alternative_node                                                        \
			<                                                                       \
				BOOST_PP_SEQ_ENUM(type_seq)                                         \
			>                                                                       \
			type                                                                    \
		;                                                                           \
		typedef BOOST_PP_SEQ_HEAD(type_seq) head_node_t;                            \
		typedef                                                                     \
			alternative_node                                                        \
			<                                                                       \
				BOOST_PP_SEQ_ENUM(BOOST_PP_SEQ_TAIL(type_seq))                      \
			>                                                                       \
			tail_alternative_node_t                                                 \
		;                                                                           \
                                                                                    \
		BOOST_PP_SEQ_FOR_EACH                                                       \
		(                                                                           \
			SCALPEL_ALTERNATIVE_NODE_PIMPL_DECLARATION_CONSTRUCTOR,                 \
			alternative_node_type,                                                  \
			type_seq                                                                \
		)                                                                           \
                                                                                    \
		alternative_node_type(const alternative_node_type& o);                      \
                                                                                    \
		alternative_node_type(alternative_node_type&& o);                           \
                                                                                    \
		~alternative_node_type();                                                   \
                                                                                    \
		const alternative_node_type&                                                \
		operator=(const alternative_node_type& o);                                  \
                                                                                    \
		const tail_alternative_node_t&                                              \
		tail() const;                                                               \
                                                                                    \
		BOOST_PP_SEQ_FOR_EACH                                                       \
		(                                                                           \
			SCALPEL_ALTERNATIVE_NODE_PIMPL_DECLARATION_GET_FUNCTION,                \
			~,                                                                      \
			type_seq                                                                \
		)                                                                           \
                                                                                    \
	private:                                                                        \
		std::unique_ptr<type> impl_;                                                \
};

