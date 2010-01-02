/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008, 2009  Florian Goujeon

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

#ifndef SCALPEL_CPP_SEMANTIC_ANALYZER_HPP
#define SCALPEL_CPP_SEMANTIC_ANALYZER_HPP

#include "syntax_tree.hpp"
#include "semantic_graph.hpp"
#include "detail/semantic_analysis/scope_cursor.hpp"
#include "syntax_nodes/utility/type_traits.hpp"
#include <memory>

namespace scalpel { namespace cpp
{

/**
@brief Analyses the semantic of the source code of a full C++ program.
*/
class semantic_analyzer
{
	public:
		template<class ParentEntityT>
		class alternative_visitor;

		std::shared_ptr<semantic_graph>
		operator()(const syntax_tree& tree);

	private:
		//overload for alternative nodes
		template<class SyntaxNodeT, class ParentEntityT>
		void
		analyze
		(
			const SyntaxNodeT& syntax_node,
			std::shared_ptr<ParentEntityT> parent_entity,
			typename boost::enable_if<syntax_nodes::utility::is_alternative_node<SyntaxNodeT>>::type* = 0
		);

		//overload for list nodes
		template<class SyntaxNodeT, class ParentEntityT>
		void
		analyze
		(
			const SyntaxNodeT& syntax_node,
			std::shared_ptr<ParentEntityT> parent_entity,
			typename boost::enable_if<syntax_nodes::utility::is_list_node<SyntaxNodeT>>::type* = 0
		);

		template<class ParentEntityT>
		void
		analyze(const syntax_nodes::asm_definition& syntax_node, std::shared_ptr<ParentEntityT> parent_entity);

		template<class ParentEntityT>
		void
		analyze(const syntax_nodes::break_statement& syntax_node, std::shared_ptr<ParentEntityT> parent_entity);

		template<class ParentEntityT>
		void
		analyze(const syntax_nodes::case_statement& syntax_node, std::shared_ptr<ParentEntityT> parent_entity);

		template<class ParentEntityT>
		void
		analyze(const syntax_nodes::class_head& syntax_node, std::shared_ptr<ParentEntityT> parent_entity);

		template<class ParentEntityT>
		void
		analyze(const syntax_nodes::class_specifier& class_specifier_node, std::shared_ptr<ParentEntityT> parent_entity);

		template<class ParentEntityT>
		void
		analyze(const syntax_nodes::classic_labeled_statement& syntax_node, std::shared_ptr<ParentEntityT> parent_entity);

		template<class ParentEntityT>
		void
		analyze(const syntax_nodes::compound_statement& syntax_node, std::shared_ptr<ParentEntityT> parent_entity);

		template<class ParentEntityT>
		void
		analyze(const syntax_nodes::conversion_function_id& syntax_node, std::shared_ptr<ParentEntityT> parent_entity);

		template<class ParentEntityT>
		void
		analyze(const syntax_nodes::continue_statement& syntax_node, std::shared_ptr<ParentEntityT> parent_entity);

		template<class ParentEntityT>
		void
		analyze(const syntax_nodes::ctor_initializer& syntax_node, std::shared_ptr<ParentEntityT> parent_entity);

		template<class ParentEntityT>
		void
		analyze(const syntax_nodes::cv_qualifier& syntax_node, std::shared_ptr<ParentEntityT> parent_entity);

		template<class ParentEntityT>
		void
		analyze(const syntax_nodes::declarator& syntax_node, std::shared_ptr<ParentEntityT> parent_entity);

		template<class ParentEntityT>
		void
		analyze(const syntax_nodes::default_statement& syntax_node, std::shared_ptr<ParentEntityT> parent_entity);

		template<class ParentEntityT>
		void
		analyze(const syntax_nodes::destructor_name& syntax_node, std::shared_ptr<ParentEntityT> parent_entity);

		template<class ParentEntityT>
		void
		analyze(const syntax_nodes::direct_declarator& syntax_node, std::shared_ptr<ParentEntityT> parent_entity);

		template<class ParentEntityT>
		void
		analyze(const syntax_nodes::direct_declarator_array_part& syntax_node, std::shared_ptr<ParentEntityT> parent_entity);

		template<class ParentEntityT>
		void
		analyze(const syntax_nodes::direct_declarator_function_part& syntax_node, std::shared_ptr<ParentEntityT> parent_entity);

		template<class ParentEntityT>
		void
		analyze(const syntax_nodes::do_while_statement& syntax_node, std::shared_ptr<ParentEntityT> parent_entity);

		template<class ParentEntityT>
		void
		analyze(const syntax_nodes::elaborated_type_specifier& syntax_node, std::shared_ptr<ParentEntityT> parent_entity);

		template<class ParentEntityT>
		void
		analyze(const syntax_nodes::explicit_instantiation& syntax_node, std::shared_ptr<ParentEntityT> parent_entity);

		template<class ParentEntityT>
		void
		analyze(const syntax_nodes::explicit_specialization& syntax_node, std::shared_ptr<ParentEntityT> parent_entity);

		template<class ParentEntityT>
		void
		analyze(const syntax_nodes::expression_statement& syntax_node, std::shared_ptr<ParentEntityT> parent_entity);

		template<class ParentEntityT>
		void
		analyze(const syntax_nodes::for_statement& syntax_node, std::shared_ptr<ParentEntityT> parent_entity);

		template<class ParentEntityT>
		void
		analyze(const syntax_nodes::function_definition& function_definition_node, std::shared_ptr<ParentEntityT> parent_entity);

		template<class ParentEntityT>
		void
		analyze(const syntax_nodes::goto_statement& syntax_node, std::shared_ptr<ParentEntityT> parent_entity);

		template<class ParentEntityT>
		void
		analyze(const syntax_nodes::handler& syntax_node, std::shared_ptr<ParentEntityT> parent_entity);

		template<class ParentEntityT>
		void
		analyze(const syntax_nodes::identifier& syntax_node, std::shared_ptr<ParentEntityT> parent_entity);

		template<class ParentEntityT>
		void
		analyze(const syntax_nodes::if_statement& syntax_node, std::shared_ptr<ParentEntityT> parent_entity);

		template<class ParentEntityT>
		void
		analyze(const syntax_nodes::init_declarator& syntax_node, std::shared_ptr<ParentEntityT> parent_entity);

		template<class ParentEntityT>
		void
		analyze(const syntax_nodes::linkage_specification& syntax_node, std::shared_ptr<ParentEntityT> parent_entity);

		template<class ParentEntityT>
		void
		analyze(const syntax_nodes::mem_initializer& syntax_node, std::shared_ptr<ParentEntityT> parent_entity);

		template<class ParentEntityT>
		void
		analyze(const syntax_nodes::member_declaration_function_definition& syntax_node, std::shared_ptr<ParentEntityT> parent_entity);

		template<class ParentEntityT>
		void
		analyze(const syntax_nodes::member_declaration_member_declarator_list& syntax_node, std::shared_ptr<ParentEntityT> parent_entity);

		template<class ParentEntityT>
		void
		analyze(const syntax_nodes::member_declaration_unqualified_id& syntax_node, std::shared_ptr<ParentEntityT> parent_entity);

		template<class ParentEntityT>
		void
		analyze(const syntax_nodes::member_declarator_bit_field_member& syntax_node, std::shared_ptr<ParentEntityT> parent_entity);

		template<class ParentEntityT>
		void
		analyze(const syntax_nodes::member_declarator_declarator& syntax_node, std::shared_ptr<ParentEntityT> parent_entity);

		template<class ParentEntityT>
		void
		analyze(const syntax_nodes::member_specification& syntax_node, std::shared_ptr<ParentEntityT> parent_entity);

		template<class ParentEntityT>
		void
		analyze(const syntax_nodes::member_specification_access_specifier& syntax_node, std::shared_ptr<ParentEntityT> parent_entity);

		template<class ParentEntityT>
		void
		analyze(const syntax_nodes::namespace_alias_definition& syntax_node, std::shared_ptr<ParentEntityT> parent_entity);

		template<class ParentEntityT>
		void
		analyze(const syntax_nodes::namespace_definition& syntax_node, std::shared_ptr<ParentEntityT> parent_entity);

		template<class ParentEntityT>
		void
		analyze(const syntax_nodes::nested_identifier_or_template_id& syntax_node, std::shared_ptr<ParentEntityT> parent_entity);

		template<class ParentEntityT>
		void
		analyze(const syntax_nodes::nested_name_specifier& syntax_node, std::shared_ptr<ParentEntityT> parent_entity);

		template<class ParentEntityT>
		void
		analyze(const syntax_nodes::nested_name_specifier_last_part& syntax_node, std::shared_ptr<ParentEntityT> parent_entity);

		template<class ParentEntityT>
		void
		analyze(const syntax_nodes::operator_function_id& syntax_node, std::shared_ptr<ParentEntityT> parent_entity);

		template<class ParentEntityT>
		void
		analyze(const syntax_nodes::parameter_declaration& syntax_node, std::shared_ptr<ParentEntityT> parent_entity);

		template<class ParentEntityT>
		void
		analyze(const syntax_nodes::parameter_declaration_clause& syntax_node, std::shared_ptr<ParentEntityT> parent_entity);

		template<class ParentEntityT>
		void
		analyze(const syntax_nodes::ptr_operator& syntax_node, std::shared_ptr<ParentEntityT> parent_entity);

		template<class ParentEntityT>
		void
		analyze(const syntax_nodes::qualified_identifier& syntax_node, std::shared_ptr<ParentEntityT> parent_entity);

		template<class ParentEntityT>
		void
		analyze(const syntax_nodes::qualified_nested_id& syntax_node, std::shared_ptr<ParentEntityT> parent_entity);

		template<class ParentEntityT>
		void
		analyze(const syntax_nodes::qualified_operator_function_id& syntax_node, std::shared_ptr<ParentEntityT> parent_entity);

		template<class ParentEntityT>
		void
		analyze(const syntax_nodes::qualified_template_id& syntax_node, std::shared_ptr<ParentEntityT> parent_entity);

		template<class ParentEntityT>
		void
		analyze(const syntax_nodes::return_statement& syntax_node, std::shared_ptr<ParentEntityT> parent_entity);

		template<class ParentEntityT>
		void
		analyze(const syntax_nodes::simple_declaration& syntax_node, std::shared_ptr<ParentEntityT> parent_entity);

		template<class ParentEntityT>
		void
		analyze(const syntax_nodes::simple_template_type_specifier& syntax_node, std::shared_ptr<ParentEntityT> parent_entity);

		template<class ParentEntityT>
		void
		analyze(const syntax_nodes::switch_statement& syntax_node, std::shared_ptr<ParentEntityT> parent_entity);

		template<class ParentEntityT>
		void
		analyze(const syntax_nodes::template_declaration& syntax_node, std::shared_ptr<ParentEntityT> parent_entity);

		template<class ParentEntityT>
		void
		analyze(const syntax_nodes::template_id& syntax_node, std::shared_ptr<ParentEntityT> parent_entity);

		template<class ParentEntityT>
		void
		analyze(const syntax_nodes::try_block& syntax_node, std::shared_ptr<ParentEntityT> parent_entity);

		template<class ParentEntityT>
		void
		analyze(const syntax_nodes::type_id_sizeof_expression& syntax_node, std::shared_ptr<ParentEntityT> parent_entity);

		template<class ParentEntityT>
		void
		analyze(const syntax_nodes::unary_sizeof_expression& syntax_node, std::shared_ptr<ParentEntityT> parent_entity);

		template<class ParentEntityT>
		void
		analyze(const syntax_nodes::using_declaration& syntax_node, std::shared_ptr<ParentEntityT> parent_entity);

		template<class ParentEntityT>
		void
		analyze(const syntax_nodes::using_directive& syntax_node, std::shared_ptr<ParentEntityT> parent_entity);

		template<class ParentEntityT>
		void
		analyze(const syntax_nodes::while_statement& syntax_node, std::shared_ptr<ParentEntityT> parent_entity);

		std::shared_ptr<semantic_entities::class_>
		create_class(const syntax_nodes::class_specifier& syntax_node);

		void
		fill_class(std::shared_ptr<semantic_entities::class_> c, const syntax_nodes::class_specifier& syntax_node);



		//
		//function definition functions
		//

		/**
		Define the given function. It may also create the function if any.
		*/
		template<class FunctionT, class ParentEntityT>
		void
		define_function
		(
			const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node,
			const syntax_nodes::declarator& declarator_node,
			std::shared_ptr<ParentEntityT> parent_entity
		);



		//
		//function creation functions
		//

		template<class FunctionT>
		std::shared_ptr<FunctionT>
		create_function
		(
			const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node,
			const syntax_nodes::declarator& declarator_node
		);

		std::shared_ptr<semantic_entities::simple_function>
		create_simple_function
		(
			const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node,
			const syntax_nodes::declarator& declarator_node
		);

		std::shared_ptr<semantic_entities::operator_function>
		create_operator_function
		(
			const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node,
			const syntax_nodes::declarator& declarator_node
		);

		semantic_entities::simple_function::parameters_t
		create_parameters(const syntax_nodes::declarator& declarator_node);



		std::shared_ptr<const semantic_entities::type>
		create_type
		(
			const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node,
			const syntax_nodes::declarator& declarator_node
		);

		std::shared_ptr<const semantic_entities::type>
		create_type
		(
			const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node,
			const syntax_nodes::abstract_declarator& abstract_declarator_node
		);

		std::shared_ptr<const semantic_entities::type>
		create_type
		(
			const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node
		);

		std::shared_ptr<const semantic_entities::type>
		get_conversion_function_type
		(
			const syntax_nodes::declarator& declarator_node
		);

		std::shared_ptr<const semantic_entities::type>
		decorate_type
		(
			std::shared_ptr<const semantic_entities::type> return_type,
			const bool const_qualified,
			const bool volatile_qualified
		);

		std::shared_ptr<const semantic_entities::type>
		decorate_type
		(
			std::shared_ptr<const semantic_entities::type> return_type,
			const syntax_nodes::ptr_operator_seq& ptr_operator_seq_node
		);

		void
		get_type_info
		(
			const syntax_nodes::type_specifier& type_specifier_node,
			std::shared_ptr<const semantic_entities::type>& t,
			bool& bool_type,
			bool& char_type,
			bool& double_type,
			bool& float_type,
			bool& int_type,
			bool& long_long_type,
			bool& long_type,
			bool& short_type,
			bool& signed_type,
			bool& unsigned_type,
			bool& void_type,
			bool& wchar_t_type,
			bool& const_qualified,
			bool& volatile_qualified
		);

		std::shared_ptr<const semantic_entities::built_in_type>
		get_built_in_type
		(
			const bool bool_type,
			const bool char_type,
			const bool double_type,
			const bool float_type,
			const bool int_type,
			const bool long_long_type,
			const bool long_type,
			const bool short_type,
			const bool signed_type,
			const bool unsigned_type,
			const bool void_type,
			const bool wchar_t_type
		);

		std::shared_ptr<semantic_entities::class_>
		find_class
		(
			const syntax_nodes::nested_identifier_or_template_id& nested_identifier_or_template_id_node
		);

		std::vector<std::shared_ptr<semantic_entities::variable>>
		create_variables
		(
			const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node,
			const syntax_nodes::init_declarator_list& init_declarator_list_node
		);

		std::shared_ptr<semantic_entities::variable>
		create_variable
		(
			const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node,
			const syntax_nodes::declarator& declarator_node
		);

		detail::semantic_analysis::scope_cursor scope_cursor_;
};

template<class ParentEntityT>
class semantic_analyzer::alternative_visitor
{
	public:
		alternative_visitor(semantic_analyzer& analyzer, std::shared_ptr<ParentEntityT> parent_entity);

		template<class T>
		inline
		void
		operator()(const T& syntax_node) const;

	private:
		semantic_analyzer& analyzer_;
		std::shared_ptr<ParentEntityT> parent_entity_;
};

}} //namespace scalpel::cpp

#include "semantic_analyzer.ipp"

#endif

