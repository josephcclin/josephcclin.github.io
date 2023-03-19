/* ================================================ */
/* Here are functions needed in the pretty printer  */
/* Author: Chuang-Chieh Lin      		    */
/* December 3, 2004				    */
/* Compilers project 3				    */
/* ================================================ */

#include "tree.h"

void print_boolprm(Tree);
void print_boolfact(Tree);
void print_boolterm(Tree);
void print_boolexpr(Tree);
void print_ariprm(Tree);
void print_arifact(Tree);
void print_term(Tree);
void print_expr_list(Tree);
void print_ariexprs(Tree);
void print_ariexpr(Tree);
void print_assignstmt(Tree, int);
void print_cmpdstmt(Tree, int);
void print_ifstmt(Tree, int);
void print_whistmt(Tree, int);
void print_retstmt(Tree, int);
void print_exitstmt(Tree, int);
void print_readstmt(Tree, int);
void print_writestmt(Tree, int);
void print_stmt(Tree, int);
void print_stmts(Tree, int);
void print_paralist(Tree);
void print_paras(Tree);
void print_func_body(Tree, int);
void print_var_dec(Tree, int);
void print_vars_decs(Tree, int);
void print_func_def(Tree, int);
void print_funcs_defs(Tree, int);
void lev_space(int);
void pretty(Tree, int);


void print_boolprm(Tree node) // print bool_primary
{
	if (!is_empty_list(node)) {
		if (get_node_tag(node) == TREE_OP) {
			print_ariexpr(get_expr_left(node));
			if (get_expr_op(node) == EQ) {
				fprintf(stdout, " == ");
			} else if (get_expr_op(node) == NEQ) {
				fprintf(stdout, " != ");
			} else if (get_expr_op(node) == '>') {
				fprintf(stdout, " > ");
			} else if (get_expr_op(node) == GE) {
				fprintf(stdout, " >= ");
			} else if (get_expr_op(node) == '<') {
				fprintf(stdout, " < ");
			} else if (get_expr_op(node) == LE) {
				fprintf(stdout, " <= ");
			} 
			print_ariexpr(get_expr_right(node));
		} else if (get_node_tag(node) == TREE_CALL) {
			fprintf(stdout, "(");
			print_boolexpr(get_call_args(node));
			fprintf(stdout, ")");
		}
	} 
}

void print_boolfact(Tree node) // print bool_factor
{
	if (!is_empty_list(node)) {
		if ((get_expr_left(node) == NULL) && (get_expr_op(node) == '!')) {
    			fprintf(stdout, "!");
	        	print_boolprm(get_expr_right(node));
   		} else {
      			print_boolprm(node);
		}
	} 
}

void print_boolterm(Tree node) // print bool_term
{
	if (!is_empty_list(node)) {
		if (get_expr_op(node) == AND) {
			print_boolterm(get_expr_left(node));
			fprintf(stdout, " && ");
			print_boolfact(get_expr_right(node));
		} else {
			print_boolfact(node);
		}
	}
}

void print_boolexpr(Tree node) // print bool_expression
{
	if (!is_empty_list(node)) {
		if (get_expr_op(node) == OR) {
			print_boolexpr(get_expr_left(node));
			fprintf(stdout, " || ");
			print_boolterm(get_expr_right(node));
		} else {
			print_boolterm(node);
		}
	}
}

void print_ariprm(Tree node) // print arith_primary
{
	if (get_node_tag(node) == TREE_INTCON) {
		fprintf(stdout, "%d", get_intcon_value(node));
	} else if (get_node_tag(node) ==  TREE_ID) {
		fprintf(stdout, "%s", get_id_name(node));
	} else if ((get_node_tag(node) == TREE_CALL)) { 
		if (get_call_name(node) != NULL) { 
			fprintf(stdout, "%s(", get_call_name(node)); 
			print_ariexprs(get_call_args(node));
			fprintf(stdout, ")");
		} else {
			fprintf(stdout, "(");
			print_ariexpr(get_call_args(node));
			fprintf(stdout, ")"); 
		}
	} 
}

void print_arifact(Tree node) // print arith_factor
{
	if (!is_empty_list(node)) { 
		if(get_node_tag(node) == TREE_OP) {
			fprintf(stdout, "-");
			print_ariprm(get_expr_right(node));
		} else { 
			print_ariprm(node);
		}
	} 
}

void print_term(Tree node) // print arith_term
{
	if (!is_empty_list(node)) {
		if (get_expr_op(node) == '*') {
			print_term(get_expr_left(node));
			fprintf(stdout, " * ");
			print_arifact(get_expr_right(node));
		} else if (get_expr_op(node) == '/') {
			print_term(get_expr_left(node));
	 		fprintf(stdout, " / ");
			print_arifact(get_expr_right(node));
		} else if (get_expr_op(node) == '%') {
			print_term(get_expr_left(node));
                	fprintf(stdout, " %c ", get_expr_op(node));
	                print_arifact(get_expr_right(node)); 
		} else {
			print_arifact(node);
		}
	} 
}

void print_expr_list(Tree node) //print arith_expression_list
{
	if (!is_empty_list(node)) {
		if (is_list(node)) {
			print_expr_list(get_list_first(node));
			if (get_list_rest(node)) {
				fprintf(stdout, ", ");
			}
			print_expr_list(get_list_rest(node));
		} else {
			print_ariexpr(node);
		}
	} 
}

void print_ariexprs(Tree node) // print arith_expressions
{
	if (!is_empty_list(node)) {
		print_expr_list(node);
	} 
}

void print_ariexpr(Tree node) // print arith_expression
{
	if (!is_empty_list(node)) {
		if (get_expr_op(node) == '+') {
			print_ariexpr(get_expr_left(node));
		 	fprintf(stdout, " + ");
		 	print_term(get_expr_right(node));
		} else if ((get_expr_op(node) == '-') && (get_expr_left(node) != NULL)) { 
			print_ariexpr(get_expr_left(node));
			fprintf(stdout, " - ");
			print_term(get_expr_right(node));
		
		} else { 
			print_term(node);
		}
	} 
}

void print_assignstmt(Tree node, int level) // print assignment_statement
{
	lev_space(level);
	fprintf(stdout, "%s = ", get_assign_var(node));
	print_ariexpr(get_assign_expr(node));
	fprintf(stdout, ";\n");
}

void print_cmpdstmt(Tree node, int level) //print compound_statement
{
	print_stmts(get_body_stmts(node), level+1);
}

void print_ifstmt(Tree node, int level) // print if_statement
{
	lev_space(level);
	fprintf(stdout, "if (");
	print_boolexpr(get_if_expr(node));
	fprintf(stdout, ") {\n");
	print_stmt(get_if_thenstmt(node), level);
	lev_space(level);
	fprintf(stdout, "}");
	if (get_if_elsestmt(node) != NULL) {
		fprintf(stdout, " else {\n");
		print_stmt(get_if_elsestmt(node), level);
		lev_space(level);
		fprintf(stdout, "}\n");
	} else { 
		fprintf(stdout, "\n");
	}
}

void print_whistmt(Tree node, int level) // print while_statement
{
	lev_space(level);
	fprintf(stdout, "while (");
	print_boolexpr(get_while_expr(node));
	fprintf(stdout, ") {\n");
	print_stmt(get_while_stmt(node), level);
	lev_space(level);
	fprintf(stdout, "}\n");
}

void print_retstmt(Tree node, int level) // print return_statement
{
	lev_space(level);
	fprintf(stdout, "return ");
	print_ariexpr(get_return_expr(node));
	fprintf(stdout, ";\n");
}

void print_exitstmt(Tree node, int level) // print exit_statement
{
	lev_space(level);
	fprintf(stdout, "exit;\n");
}

void print_readstmt(Tree node, int level) // print read_statement
{
	lev_space(level);
	fprintf(stdout, "read ");
	fprintf(stdout, "%s", get_read_var(node));
	fprintf(stdout, ";\n");
}

void print_writestmt(Tree node, int level) // print write_statement
{
	lev_space(level);
	fprintf(stdout, "write ");
	print_ariexpr(get_write_expr(node));
	fprintf(stdout, ";\n");
}

void print_stmt(Tree node, int level) // print statement
{
	switch (get_node_tag(node))
	{
		case TREE_ASSIGN:
			print_assignstmt(node, level);
			break;
		case TREE_IF:
			print_ifstmt(node, level);
			break;
		case TREE_WHILE:
			print_whistmt(node, level);
			break;
		case TREE_RETURN:
			print_retstmt(node, level);
			break;
		case TREE_EXIT:
			print_exitstmt(node, level);
			break;
		case TREE_READ:
			print_readstmt(node, level);
			break;
		case TREE_WRITE:
			print_writestmt(node, level);
			break;
		case TREE_BODY:
			print_cmpdstmt(node, level);
			break;
		default:
			//empty statement
			break;
	}
}

void print_stmts(Tree node, int level) // print statements
{
	if (!is_empty_list(node))
	{
        	if (is_list(node)) { 
			print_stmts(get_list_first(node), level);
			print_stmts(get_list_rest(node), level);
             	} else {
			print_stmt(node, level);
		}
	} 
}

void print_paralist(Tree node) // print parameter_list
{
	if (!is_empty_list(node)) {
		if (is_list(node)) {
			print_paralist(get_list_first(node));
			if (get_list_rest(node) != NULL) {
				fprintf(stdout, ", ");
			}
			print_paralist(get_list_rest(node));
		} else {
			fprintf(stdout, "int %s", get_id_name(node));
		}
	}
}

void print_paras(Tree node) // print parameters
{
	if (!is_empty_list(node)) {
		print_paralist(node);
	} 
}

void print_func_body(Tree node, int level) // print function_body
{
	fprintf(stdout, "{\n");
	print_vars_decs(get_function_params(node), level);
	fprintf(stdout, "\n");
	print_stmts(get_function_body(node), level);
	lev_space(0);
	fprintf(stdout, "}\n");
}

void print_var_dec(Tree node, int level) // print variable_declaration
{
	if (!is_empty_list(node)) {
		lev_space(level);
		fprintf(stdout, "int %s;\n", get_id_name(node));
	} 
}

void print_vars_decs(Tree node, int level) // print variable_declarations
{
	if (!is_empty_list(node)) {
		if (is_list(node)) { 
			print_vars_decs(get_list_first(node), level);
			print_vars_decs(get_list_rest(node), level);
		}
		else {
			print_var_dec(node, level);
		}
	}
}

void print_func_def(Tree node, int level) // print function_definition
{
	if (!is_empty_list(node)) {
		if (get_node_tag(node) == TREE_FUNC) {
			fprintf(stdout, "int %s(", get_function_name(node));
			print_paras(get_function_params(node));
			fprintf(stdout, ")\n");
			print_func_body(get_function_body(node), level+1);
			fprintf(stdout, "\n");
		}
	} 
}

void print_funcs_defs(Tree node, int level) // print function_definitions
{
	if (!is_empty_list(node)) {
		if (is_list(node)) {
			print_funcs_defs(get_list_first(node), level);
			print_funcs_defs(get_list_rest(node), level);
		} else {
			print_func_def(node, level);
		}
	} 
}

void lev_space(int lev) // print indentations
{
	int i;
	for (i=0; i<lev; i++)
		fprintf(stdout, "    ");
}

void pretty(Tree root, int level) // the start function of our pretty printer
{
	Tree program_vars, program_funcs;
	level = 0; 
	
	program_vars = get_program_vars(root); 
	program_funcs = get_program_funcs(root); 
	if (program_vars != NULL) {
		print_vars_decs(program_vars, 0); // print variable_declarations of the program
	}
	print_funcs_defs(program_funcs, 0); // print function_declarations of the program
}

