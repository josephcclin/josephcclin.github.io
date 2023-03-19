/* ================================================ */
/* Here are functions needed in our type checker    */
/* Author: Chuang-Chieh Lin      		    */
/* December 20, 2004				    */
/* Compilers project 4				    */
/* ================================================ */

#include "typecheck.h"

int tycheck = 0;
int paturn = 0;
int lvturn = 0;

void check_boolprm(Tree node, SymTable FunTab) // check bool_primary
{
	if (get_node_tag(node) == TREE_OP) {
		check_ariexpr(get_expr_left(node), FunTab);
		if (get_expr_op(node) == EQ) {
			//" == "
		} else if (get_expr_op(node) == NEQ) {
			//" != "
		} else if (get_expr_op(node) == '>') {
			//" > "
		} else if (get_expr_op(node) == GE) {
			//" >= "
		} else if (get_expr_op(node) == '<') {
			//" < "
		} else if (get_expr_op(node) == LE) {
			//" <= "
		} 
		check_ariexpr(get_expr_right(node), FunTab);
	} else if (get_node_tag(node) == TREE_CALL) {
		check_boolexpr(get_call_args(node), FunTab);
	}
}

void check_boolfact(Tree node, SymTable FunTab) // check bool_factor
{
	if ((get_expr_left(node) == NULL) && (get_expr_op(node) == '!')) {
        	check_boolprm(get_expr_right(node), FunTab);
 	} else {
      		check_boolprm(node, FunTab);
	}
}

void check_boolterm(Tree node, SymTable FunTab) // check bool_term
{
	if (get_expr_op(node) == AND) {
		check_boolterm(get_expr_left(node), FunTab);
		check_boolfact(get_expr_right(node), FunTab);
	} else {
		check_boolfact(node, FunTab);
	}
}

void check_boolexpr(Tree node, SymTable FunTab) // check bool_expression
{
	if (get_expr_op(node) == OR) {
		check_boolexpr(get_expr_left(node), FunTab);
		check_boolterm(get_expr_right(node), FunTab);
	} else {
		check_boolterm(node, FunTab);
	}
}

void check_ariprm(Tree node, SymTable FunTab) // check arith_primary
{
	int callari;
	int arity;
	
	if (get_node_tag(node) ==  TREE_ID) {
		if (!FunTab) {
			if (!lookup(GblTab, get_id_name(node))) { // Can't find id in GblTab
				fprintf(stderr, "type error: line %d: identifier %s is not declared\n",
						get_id_lineno(node), get_id_name(node));
				tycheck = 1; // mark for the type error
			} 
		} else if (!lookup(GblTab, get_id_name(node)) && !lookup(FunTab, get_id_name(node))) { // can't find id 
			fprintf(stderr, "type error: line %d: identifier %s is not declared\n",   
					get_id_lineno(node), get_id_name(node)); 
			tycheck = 1; // mark for the type error
		}
	} else if ((get_node_tag(node) == TREE_CALL)) { 
		if (get_call_name(node) != NULL) { 
			if (!LookFunc(GblTab, get_call_name(node))) { // can't find id in GblTab
				fprintf(stderr, "type error: line %d: identifier %s is not declared\n",  
					get_id_lineno(node), get_call_name(node));
				tycheck = 1; // mark for the type error
				check_ariexprs(get_call_args(node), FunTab);
			} else {
				arity = symbol_get_function_arity(LookFunc(GblTab, get_call_name(node))); 
				callari = check_ariexprs(get_call_args(node), FunTab);
				if (callari != arity) {
					fprintf(stderr, "type error: line %d: the arity of function %s is not matched\n", 
						get_id_lineno(node), get_call_name(node));
					tycheck = 1; // mark for the type error
				}
			}
		} else {
			check_ariexpr(get_call_args(node), FunTab);
		}
	} 
}

void check_arifact(Tree node, SymTable FunTab) // check arith_factor
{
	if(get_node_tag(node) == TREE_OP) {
		check_ariprm(get_expr_right(node), FunTab);
	} else { 
		check_ariprm(node, FunTab);
	}
}

void check_term(Tree node, SymTable FunTab) // check arith_term
{
	if (get_expr_op(node) == '*') {
		check_term(get_expr_left(node), FunTab);
		check_arifact(get_expr_right(node), FunTab);
	} else if (get_expr_op(node) == '/') {
		check_term(get_expr_left(node), FunTab);
		check_arifact(get_expr_right(node), FunTab);
	} else if (get_expr_op(node) == '%') {
		check_term(get_expr_left(node), FunTab);
                check_arifact(get_expr_right(node), FunTab); 
	} else {
		check_arifact(node, FunTab);
	}
}

int check_expr_list(Tree node, SymTable FunTab, int arity) //check arith_expression_list
{
	if (!is_empty_list(node)) {
		if (is_list(node)) { // a list node
			arity = check_expr_list(get_list_first(node), FunTab, arity);
			arity = check_expr_list(get_list_rest(node), FunTab, arity);
		} else { // not a list node
			check_ariexpr(node, FunTab);
			return ++arity;
		}
	} 
	return arity;
}

int check_ariexprs(Tree node, SymTable FunTab) // check arith_expressions
{
	int ari = 0;
	
	if (!is_empty_list(node)) {
		return check_expr_list(node, FunTab, ari);
	} else {
		return ari; 
	}
}

void check_ariexpr(Tree node, SymTable FunTab) // check arith_expression
{
	if (get_expr_op(node) == '+') {
		check_ariexpr(get_expr_left(node), FunTab);
	 	check_term(get_expr_right(node), FunTab);
	} else if ((get_expr_op(node) == '-') && (get_expr_left(node) != NULL)) { 
		check_ariexpr(get_expr_left(node), FunTab);
		check_term(get_expr_right(node), FunTab);
	} else { 
		check_term(node, FunTab);
	}
}

void check_assignstmt(Tree node, SymTable FunTab) // check assignment_statement
{
	if (!FunTab) {
		if (!lookup(GblTab, get_assign_var(node))) { // can't find id in GblTab
			fprintf(stderr, "type error: line %d: identifier %s is not declared\n", 
				get_id_lineno(node), get_assign_var(node));
			tycheck = 1; // mark for the type error
		}
	} else if (!lookup(GblTab, get_assign_var(node)) && !lookup(FunTab, get_assign_var(node))) {
			fprintf(stderr, "type error: line %d: identifier %s is not declared\n",
                        	get_id_lineno(node), get_assign_var(node));
			tycheck = 1; // mark for the type error
	}
	check_ariexpr(get_assign_expr(node), FunTab);
}

void check_cmpdstmt(Tree node, SymTable FunTab) //check compound_statement
{
	check_stmts(get_body_stmts(node), FunTab);
}

void check_ifstmt(Tree node, SymTable FunTab) // check if_statement
{
	check_boolexpr(get_if_expr(node), FunTab);
	check_stmt(get_if_thenstmt(node), FunTab);
	
	if (get_if_elsestmt(node) != NULL) {
		check_stmt(get_if_elsestmt(node), FunTab);
	} 
}

void check_whistmt(Tree node, SymTable FunTab) // check while_statement
{
	check_boolexpr(get_while_expr(node), FunTab);
	check_stmt(get_while_stmt(node), FunTab);
}

void check_retstmt(Tree node, SymTable FunTab) // check return_statement
{
	check_ariexpr(get_return_expr(node), FunTab);
}

void check_exitstmt(Tree node, SymTable FunTab) // check exit_statement
{
	// Don't do anything
}

void check_readstmt(Tree node, SymTable FunTab) // check read_statement
{
	Symbol symptr;
	
	if (!FunTab) {
		if (!lookup(GblTab, get_read_var(node))) { // can't find id in GblTab
			fprintf(stderr, "type error: line %d: identifier %s is not declared\n",
				get_id_lineno(node), get_read_var(node));
			tycheck = 1; // mark for the type error
		} 
	} else if (!lookup(GblTab, get_read_var(node)) && !lookup(FunTab, get_read_var(node))) { // can't find id
		fprintf(stderr, "type error: line %d: identifier %s is not declared\n",
				get_id_lineno(node), get_read_var(node));
		tycheck = 1; // mark for the type error
	}
}

void check_writestmt(Tree node, SymTable FunTab) // check write_statement
{
	check_ariexpr(get_write_expr(node), FunTab);
}

void check_stmt(Tree node, SymTable FunTab) // check statement
{
	switch (get_node_tag(node))
	{
		case TREE_ASSIGN:
			check_assignstmt(node, FunTab);
			break;
		case TREE_IF:
			check_ifstmt(node, FunTab);
			break;
		case TREE_WHILE:
			check_whistmt(node, FunTab);
			break;
		case TREE_RETURN:
			check_retstmt(node, FunTab);
			break;
		case TREE_EXIT:
			check_exitstmt(node, FunTab);
			break;
		case TREE_READ:
			check_readstmt(node, FunTab);
			break;
		case TREE_WRITE:
			check_writestmt(node, FunTab);
			break;
		case TREE_BODY:
			check_cmpdstmt(node, FunTab);
			break;
		default:
			//empty statement
			break;
	}
}

void check_stmts(Tree node, SymTable FunTab) // check statements
{
	if (!is_empty_list(node))
	{
        	if (is_list(node)) { 
			check_stmts(get_list_first(node), FunTab);
			check_stmts(get_list_rest(node), FunTab);
             	} else {
			check_stmt(node, FunTab);
		}
	} 
}

int check_paralist(Tree node, SymTable FunTab, int arity) // check parameter_list
{
 	Symbol symptr;
	
	if (!is_empty_list(node)) {
		if (is_list(node)) { // a list node
			arity = check_paralist(get_list_first(node), FunTab, arity);
			arity = check_paralist(get_list_rest(node), FunTab, arity);
		} else { // not a list node
			if (!lookup(GblTab, get_id_name(node))) { // we can't find id in GblTab
				symptr = install(FunTab, get_id_name(node), PARAMETER);
				if (!symptr) { // installing failed
					fprintf(stderr, "type error: line %d: identifier %s is redeclared\n",
			 			get_id_lineno(node), get_id_name(node));
					tycheck = 1; // mark for the type error
				} else { // install succeeded
					symbol_set_paturn(symptr, ++paturn);
					return ++arity;
				}
			} else { // id has been installed in stb
				fprintf(stderr, "type error: line %d: identifier %s is redeclared\n", 
					get_id_lineno(node), get_id_name(node));
				tycheck = 1; // mark for the type error
			}
		}
	} 
	return arity; 
}

int check_paras(Tree node, SymTable FunTab) // check parameters
{
	int arity = 0;
	
	if (!is_empty_list(node)) {
		return check_paralist(node, FunTab, arity);
	} else {
		return arity; 
	}
}

void check_func_body(Tree node, Symbol symptr) // check function_body
{
	int vars = 0;
	SymTable FunTab;

	FunTab = symbol_get_function_table(symptr);
	vars = check_vars_decs(get_function_params(node), FunTab, vars);
	
	if (FunTab != NULL) {
		symbol_set_function_vars(symptr, vars);
		//fprintf(stdout, "**** function vars = %d ****\n", symbol_get_function_vars(symptr));
	}
	check_stmts(get_function_body(node), FunTab);
}

int check_var_dec(Tree node, SymTable FunTab, int vars) // check variable_declaration
{
	Symbol symptr;
	
	if (!FunTab) { // try to install a global variables
		if (!lookup(GblTab, get_id_name(node))) { // can't find id in GblTab
				symptr = install(GblTab, get_id_name(node), VARIABLE);
		} else {
			fprintf(stderr, "type error: line %d: identifier %s is redeclared\n",
				 get_id_lineno(node), get_id_name(node));
			tycheck = 1; // mark for the type error
		}
	} else if (!lookup(GblTab, get_id_name(node))) { // FunTab is not a NULL and can't find id in GblTab
		if (!lookup(FunTab, get_id_name(node))) { // can't find id in FunTab; then install it
			symptr = install(FunTab, get_id_name(node), VARIABLE);
			symbol_set_lvturn(symptr, ++vars);
		} else { 
			fprintf(stderr, "type error: line %d: identifier %s is redeclared\n",
					get_id_lineno(node), get_id_name(node));
			tycheck = 1; // mark for the type error
		}
	} else {
		fprintf(stderr, "type error: line %d: identifier %s is redeclared\n", 
				get_id_lineno(node), get_id_name(node));
		tycheck = 1; // mark for the type error
	}
	return vars;
}

int check_vars_decs(Tree node, SymTable FunTab, int vars) // check variable_declarations
{
	if (!is_empty_list(node)) {
		if (is_list(node)) { 
			vars = check_vars_decs(get_list_first(node), FunTab, vars);
			vars = check_vars_decs(get_list_rest(node), FunTab, vars);
		}
		else {
			vars = check_var_dec(node, FunTab, vars);
		}
	}
	return vars;
}

void check_func_def(Tree node) // check function_definition
{
	Symbol symptr;
	SymTable FunTab;
	int arity = 0;
	
	if (get_node_tag(node) == TREE_FUNC) {
		symptr = install(GblTab, get_function_name(node), FUNCTION); // try installing function name
		//symptr = LookFunc(GblTab, get_function_name(node)); // try installing function name
		if (!symptr) { // install failed
			fprintf(stderr, "type error: line %d: Identifier %s is redeclared\n",
				get_id_lineno(node), get_function_name(node));
			tycheck = 1; // mark for the type error
			
		} else {
			FunTab = new_symtab();
			symbol_set_function_table(symptr, FunTab); // set FunTab for symptr
			arity = check_paras(get_function_params(node), FunTab);
			symbol_set_function_arity(symptr, arity); // set arity of symptr
			check_func_body(get_function_body(node), symptr); 
		}
	}
}

void check_funcs_defs(Tree node) // check function_definitions
{
	if (!is_empty_list(node)) {
		if (is_list(node)) {
			check_funcs_defs(get_list_first(node));
			check_funcs_defs(get_list_rest(node));
		} else {
			check_func_def(node);
			lvturn = 0; // reset lvturn and paturn
			paturn = 0; // reset lvturn paturn
		}
	} 
}

int chktype(Tree root) // the starting function of our type checker
{
	Tree program_vars, program_funcs;
	GblTab = new_symtab();
	
	program_vars = get_program_vars(root); 
	program_funcs = get_program_funcs(root); 
	check_vars_decs(program_vars, NULL, 0); // check variable_declarations of the program
	check_funcs_defs(program_funcs); // check function_declarations of the program
	
	return tycheck;
}

