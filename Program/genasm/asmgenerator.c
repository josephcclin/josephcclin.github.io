/* ================================================ */
/* Here are functions needed in our code generator  */
/* Author: Chuang-Chieh Lin      		    */
/* January 10, 2005				    */
/* Compilers project 5				    */
/* ================================================ */

#include "asmgenerator.h"

int Lindex = 0; // for labeling flow controls

void gen_boolprm(Tree node, Frame fsize, SymTable FunTab, LABEL BoolExp) // generate bool_primary
{
	if (get_node_tag(node) == TREE_OP) {
		gen_ariexpr(get_expr_left(node), fsize, FunTab);
		gen_ariexpr(get_expr_right(node), fsize, FunTab);
		
		if (get_expr_op(node) == EQ) {
			fprintf(stdout, "\tbeq\t$t%d, $t%d, L%d\n", ShowReg()-1, ShowReg(), BoolExp.T);
		} else if (get_expr_op(node) == NEQ) {
			fprintf(stdout, "\tbne\t$t%d, $t%d, L%d\n", ShowReg()-1, ShowReg(), BoolExp.T);
		} else if (get_expr_op(node) == '>') {
			fprintf(stdout, "\tbgt\t$t%d, $t%d, L%d\n", ShowReg()-1, ShowReg(), BoolExp.T);
		} else if (get_expr_op(node) == GE) {
			fprintf(stdout, "\tbge\t$t%d, $t%d, L%d\n", ShowReg()-1, ShowReg(), BoolExp.T);
		} else if (get_expr_op(node) == '<') {
			fprintf(stdout, "\tblt\t$t%d, $t%d, L%d\n", ShowReg()-1, ShowReg(), BoolExp.T);
		} else if (get_expr_op(node) == LE) {
			fprintf(stdout, "\tble\t$t%d, $t%d, L%d\n", ShowReg()-1, ShowReg(), BoolExp.T);
		}
		fprintf(stdout, "\tb\tL%d\n", BoolExp.F);
		FreeReg(ShowReg());
		FreeReg(ShowReg());
	} else if (get_node_tag(node) == TREE_CALL) {
		gen_boolexpr(get_call_args(node), fsize, FunTab, BoolExp);
	}
}

void gen_boolfact(Tree node, Frame fsize, SymTable FunTab, LABEL BoolExp) // generate bool_factor
{
	LABEL Exp1;
	
	if ((get_expr_left(node) == NULL) && (get_expr_op(node) == '!')) {
		Exp1.T = BoolExp.F;
		Exp1.F = BoolExp.T;
		gen_boolprm(get_expr_right(node), fsize, FunTab, Exp1);
   	} else {
		
      		gen_boolprm(node, fsize, FunTab, BoolExp);
	}
}

void gen_boolterm(Tree node, Frame fsize, SymTable FunTab, LABEL BoolExp) // generate bool_term
{
	LABEL Exp1, Exp2;
		
	if (get_expr_op(node) == AND) {
		Exp1.T = NewLabel();
		Exp1.F = BoolExp.F;
		Exp2.T = BoolExp.T;
		Exp2.F = BoolExp.F;
		gen_boolterm(get_expr_left(node), fsize, FunTab, Exp1);
		fprintf(stdout, "L%d:\n", Exp1.T);
		gen_boolfact(get_expr_right(node), fsize, FunTab, Exp2);
	} else {
		gen_boolfact(node, fsize, FunTab, BoolExp);
	}
}

void gen_boolexpr(Tree node, Frame fsize, SymTable FunTab, LABEL BoolExp) // generate bool_expression
{
	LABEL Exp1, Exp2;
	
	if (get_expr_op(node) == OR) {
		Exp1.T = BoolExp.T;
		Exp1.F = NewLabel();
		Exp2.T = BoolExp.T;
		Exp2.F = BoolExp.F;
		gen_boolexpr(get_expr_left(node), fsize, FunTab, Exp1);
		fprintf(stdout, "L%d:\n", Exp1.F);
		gen_boolterm(get_expr_right(node), fsize, FunTab, Exp2);
	} else {
		gen_boolterm(node, fsize, FunTab, BoolExp);
	}
}

void gen_ariprm(Tree node, Frame fsize, SymTable FunTab) // generate arith_primary
{
	int reg, position;
	Symbol symptr;
	
	if (get_node_tag(node) == TREE_INTCON) {
		reg = GetReg(); // get a new register
		fprintf(stdout, "\tli\t$t%d, %d\n", reg, get_intcon_value(node));
	} else if (get_node_tag(node) == TREE_ID) {
		reg = GetReg(); // get a new register
		symptr = lookup(GblTab, get_id_name(node));
		
		if (symptr != NULL) { // global variable
			fprintf(stdout, "\tla\t$t%d, %s\n", reg, get_id_name(node));
			fprintf(stdout, "\tlw\t$t%d, 0($t%d)\n", reg, reg);
		} else { // a local variable or a function parameter
			symptr = lookup(FunTab, get_id_name(node)); 
			
			if (symbol_get_class(symptr) == VARIABLE) { // local variable
				position = -4*(fsize.paras+2+symbol_get_lvturn(symptr)-1);
				fprintf(stdout, "\tlw\t$t%d, %d($fp)\n", reg, position); 
			} else if (symbol_get_class(symptr) == PARAMETER) { // function parameter
				position = -4*(fsize.paras-symbol_get_paturn(symptr));
				fprintf(stdout, "\tlw\t$t%d, %d($fp)\n", reg, position);
			}
		}
			
	} else if ((get_node_tag(node) == TREE_CALL)) { 
		if (get_call_name(node) != NULL) { // a function call
			position = SetParas(get_call_name(node), GblTab);
			gen_ariexprs(get_call_args(node), fsize, FunTab, position);
			reg = GetReg();
			fprintf(stdout, "\tjal\t%s\n", get_call_name(node));
			fprintf(stdout, "\tmove\t$t%d, $v0\n", reg);
		} else {
			gen_ariexpr(get_call_args(node), fsize, FunTab);
		}
	} 
}

void gen_arifact(Tree node, Frame fsize, SymTable FunTab) // generate arith_factor
{
	int reg;
		
	if(get_node_tag(node) == TREE_OP) {
		gen_ariprm(get_expr_right(node), fsize, FunTab);
		reg = ShowReg();
		fprintf(stdout, "\tneg\t$t%d, $t%d\n", reg, reg);
	} else { 
		gen_ariprm(node, fsize, FunTab);
	}
}

void gen_term(Tree node, Frame fsize, SymTable FunTab) // generate arith_term
{
	int reg;
		
	if (get_expr_op(node) == '*') {
		gen_term(get_expr_left(node), fsize, FunTab);
		gen_arifact(get_expr_right(node), fsize, FunTab);
		fprintf(stdout, "\tmul\t$t%d, $t%d, $t%d\n", ShowReg()-1, ShowReg()-1, ShowReg());
		FreeReg(ShowReg());
	} else if (get_expr_op(node) == '/') {
		gen_term(get_expr_left(node), fsize, FunTab);
		gen_arifact(get_expr_right(node), fsize, FunTab);
		fprintf(stdout, "\tdiv\t$t%d, $t%d, $t%d\n", ShowReg()-1, ShowReg()-1, ShowReg());
		FreeReg(ShowReg());
	} else if (get_expr_op(node) == '%') {
		gen_term(get_expr_left(node), fsize, FunTab);
		gen_arifact(get_expr_right(node), fsize, FunTab);
		fprintf(stdout, "\trem\t$t%d, $t%d, $t%d\n", ShowReg()-1, ShowReg()-1, ShowReg());
		FreeReg(ShowReg());
	} else {
		gen_arifact(node, fsize, FunTab);
	}
}

void gen_expr_list(Tree node, Frame fsize, SymTable FunTab, int pos) //generate arith_expression_list
{
	if (!is_empty_list(node)) {
		if (is_list(node)) { // a list node
			gen_expr_list(get_list_first(node), fsize, FunTab, pos);
			gen_expr_list(get_list_rest(node), fsize, FunTab, pos-1);
			
		} else { // not a list node
			gen_ariexpr(node, fsize, FunTab);
			fprintf(stdout, "\tsw\t$t%d, %d($sp)\n", ShowReg(), -4*pos);
			FreeReg(ShowReg());
		}
	}
}

void gen_ariexprs(Tree node, Frame fsize, SymTable FunTab, int pos) // generate arith_expressions
{
	if (!is_empty_list(node)) {
		gen_expr_list(node, fsize, FunTab, pos);
	} 
}

void gen_ariexpr(Tree node, Frame fsize, SymTable FunTab) // generate arith_expression
{
	int reg;
		
	if (get_expr_op(node) == '+') {
		gen_ariexpr(get_expr_left(node), fsize, FunTab);
	 	gen_term(get_expr_right(node), fsize, FunTab);
		reg = ShowReg();
		fprintf(stdout, "\tadd\t$t%d, $t%d, $t%d\n", reg-1, reg-1, reg);
		FreeReg(reg);
	} else if ((get_expr_op(node) == '-') && (get_expr_left(node) != NULL)) { 
		gen_ariexpr(get_expr_left(node), fsize, FunTab);
		gen_term(get_expr_right(node), fsize, FunTab);
		reg = ShowReg();
		fprintf(stdout, "\tsub\t$t%d, $t%d, $t%d\n", reg-1, reg-1, reg);
		FreeReg(reg);
	} else { 
		gen_term(node, fsize, FunTab);
	}
}

void gen_assignstmt(Tree node, Frame fsize, SymTable FunTab) // generate assignment_statement
{
	int reg, vars, position = 0;
	char *name;
	Symbol symptr, lvsymptr;
	
	name = get_assign_var(node);
	symptr = lookup(GblTab, name);
	gen_ariexpr(get_assign_expr(node), fsize, FunTab);

	if (symptr != NULL) { // global variable
		reg = GetReg();
		fprintf(stdout, "\tla\t$t%d, %s\n", reg, name);
		fprintf(stdout, "\tsw\t$t%d, 0($t%d)\n", reg-1, reg);
		FreeReg(reg-1);
		FreeReg(reg); 
	} else { // local variable
		reg = ShowReg();
		lvsymptr = lookup(FunTab, name);
		
		if (symbol_get_class(lvsymptr) == VARIABLE) { 
			position = -(fsize.paras+2+symbol_get_lvturn(lvsymptr)-1)*4;
		} else if (symbol_get_class(lvsymptr) == PARAMETER) { // function parameter
			position = -(fsize.paras-symbol_get_paturn(lvsymptr))*4;
		} 
		fprintf(stdout, "\tsw\t$t%d, %d($fp)\n", ShowReg(), position);
		FreeReg(ShowReg());
	}
}

void gen_cmpdstmt(Tree node, Frame fsize, SymTable FunTab) //generate compound_statement
{
	gen_stmts(get_body_stmts(node), fsize, FunTab);
}

void gen_ifstmt(Tree node, Frame fsize, SymTable FunTab) // generate if_statement
{
	int S1next, S2next;
	LABEL BoolExp;
	
	if (get_if_elsestmt(node) == NULL) { // if BoolExp then S1
		BoolExp.T = NewLabel();
		S1next = NewLabel();
		BoolExp.F = S1next;
		gen_boolexpr(get_if_expr(node), fsize, FunTab, BoolExp);
		fprintf(stdout, "L%d:\n", BoolExp.T);
		gen_stmt(get_if_thenstmt(node), fsize, FunTab);
		fprintf(stdout, "L%d:\n", S1next);
	} else { // if BoolExp then S1 else S2
		BoolExp.T = NewLabel();
		BoolExp.F = NewLabel();
		S1next = NewLabel();
		S2next = S1next;
		gen_boolexpr(get_if_expr(node), fsize, FunTab, BoolExp);
		fprintf(stdout, "L%d:\n", BoolExp.T);
		gen_stmt(get_if_thenstmt(node), fsize, FunTab);
		fprintf(stdout, "\tb\tL%d\n", S1next);
		fprintf(stdout, "L%d:\n", BoolExp.F);
		gen_stmt(get_if_elsestmt(node), fsize, FunTab);
		fprintf(stdout, "L%d:\n", S1next);
	}
}
	
void gen_whistmt(Tree node, Frame fsize, SymTable FunTab) // generate while_statement
{
	int Sbegin, Snext, S1next;
	LABEL Exp;
	
	Sbegin = NewLabel();
	Snext = NewLabel();
	Exp.T = NewLabel();
	Exp.F = Snext;
	S1next = Sbegin;
	fprintf(stdout, "L%d:\n", Sbegin);
	gen_boolexpr(get_while_expr(node), fsize, FunTab, Exp);
	fprintf(stdout, "L%d:\n", Exp.T);
	gen_stmt(get_while_stmt(node), fsize, FunTab);
	fprintf(stdout, "\tb\tL%d\n", Sbegin);
	fprintf(stdout, "L%d:\n", Exp.F);
}

void gen_retstmt(Tree node, Frame fsize, SymTable FunTab) // generate return_statement
{
	gen_ariexpr(get_return_expr(node), fsize, FunTab);
	fprintf(stdout, "\tmove\t$v0, $t%d\n", ShowReg());
	fprintf(stdout, "\tb\t__%s_EXIT\n", fsize.fun_name);
	FreeReg(ShowReg());
}

void gen_exitstmt(Tree node, Frame fsize, SymTable FunTab) // generate exit_statement
{
	fprintf(stdout, "\tli\t$v0, 10\n");
	fprintf(stdout, "\tsyscall\n");
}

void gen_readstmt(Tree node, Frame fsize, SymTable FunTab) // generate read_statement
{
	int position;
	char *name;
	Symbol symptr;
	
	name = get_read_var(node);
	symptr = lookup(GblTab, name);
	fprintf(stdout, "\tli\t$v0, 5\n");
	fprintf(stdout, "\tsyscall\n");
	
	if (symptr != NULL) { // global variable
		fprintf(stdout, "\tla\t$t%d, %s\n", GetReg(), name);
		fprintf(stdout, "\tsw\t$v0, 0($t%d)\n", ShowReg());
		FreeReg(ShowReg());
	} else { // local variable
		symptr = lookup(FunTab, name);
		position = -4*(fsize.paras+2+symbol_get_lvturn(symptr)-1);
		fprintf(stdout, "\tsw\t$v0, %d($fp)\n", position);
	}
}

void gen_writestmt(Tree node, Frame fsize, SymTable FunTab) // generate write_statement
{
	gen_ariexpr(get_write_expr(node), fsize, FunTab);
	fprintf(stdout, "\tmove\t$a0, $t%d\n", ShowReg());
	FreeReg(ShowReg());
	fprintf(stdout, "\tli\t$v0, 1\n");
	fprintf(stdout, "\tsyscall\n");
}

void gen_stmt(Tree node, Frame fsize, SymTable FunTab) // generate statement
{
	switch (get_node_tag(node))
	{
		case TREE_ASSIGN:
			gen_assignstmt(node, fsize, FunTab);
			break;
		case TREE_IF:
			gen_ifstmt(node, fsize, FunTab);
			break;
		case TREE_WHILE:
			gen_whistmt(node, fsize, FunTab);
			break;
		case TREE_RETURN:
			gen_retstmt(node, fsize, FunTab);
			break;
		case TREE_EXIT:
			gen_exitstmt(node, fsize, FunTab);
			break;
		case TREE_READ:
			gen_readstmt(node, fsize, FunTab);
			break;
		case TREE_WRITE:
			gen_writestmt(node, fsize, FunTab);
			break;
		case TREE_BODY:
			gen_cmpdstmt(node, fsize, FunTab);
			break;
		default:
			//empty statement
			break;
	}
}

void gen_stmts(Tree node, Frame fsize, SymTable FunTab) // generate statements
{
	if (!is_empty_list(node))
	{
        	if (is_list(node)) { 
			gen_stmts(get_list_first(node), fsize, FunTab);
			gen_stmts(get_list_rest(node), fsize, FunTab);
             	} else {
			gen_stmt(node, fsize, FunTab);
		}
	} 
}

void gen_paralist(Tree node) // generate parameter_list
{
	if (!is_empty_list(node)) {
		if (is_list(node)) { // a list node
			gen_paralist(get_list_first(node));
			gen_paralist(get_list_rest(node));
		} 
	} 
}

void gen_paras(Tree node) // generate parameters
{
	if (!is_empty_list(node)) {
		gen_paralist(node);
	} 
}

void gen_func_body(Tree node, Frame fsize, SymTable FunTab) // generate function_body
{
	gen_vars_decs(get_function_params(node), LOCAL);
	gen_stmts(get_function_body(node), fsize, FunTab);
}

void gen_var_dec(Tree node, int scope) // generate variable_declaration
{
	if (scope == GLOBAL) {
		fprintf(stdout, "%s:\n\t.word\t0\n", get_id_name(node));
	} else {
		// local variable declaration
	}
}

void gen_vars_decs(Tree node, int scope) // generate variable_declarations
{
	if (!is_empty_list(node)) {
		if (is_list(node)) { 
			gen_vars_decs(get_list_first(node), scope);
			gen_vars_decs(get_list_rest(node), scope);
		}
		else {
			gen_var_dec(node, scope);
		}
	} 
}

void gen_func_def(Tree node) // generate function_definition
{
	Frame fsize;
	Symbol stbptr;
	SymTable FunTab;
	
	if (get_node_tag(node) == TREE_FUNC) {
		stbptr = LookFunc(GblTab, get_function_name(node));
		FunTab = symbol_get_function_table(stbptr); // get function symbol table
		fsize.vars = SetVars(get_function_name(node), GblTab);
		fsize.paras = SetParas(get_function_name(node), GblTab);
		fsize.size = SetFrame(fsize.vars, fsize.paras);
		fsize.fun_name = get_function_name(node);
		fprintf(stdout, "%s:\n", get_function_name(node));
		fprintf(stdout, "\tli\t$t%d, %d\n", GetReg(), fsize.size);
		fprintf(stdout, "\tsub\t$sp, $sp, $t%d\n", ShowReg());
		FreeReg(ShowReg());
		fprintf(stdout, "\tsw\t$ra, %d($sp)\n", fsize.size-4*fsize.paras-4);
		fprintf(stdout, "\tsw\t$fp, %d($sp)\n", fsize.size-4*fsize.paras-8);
		fprintf(stdout, "\tli\t$t%d, %d\n", GetReg(), fsize.size-4);
		fprintf(stdout, "\tadd\t$fp, $sp, $t%d\n", ShowReg());
		FreeReg(ShowReg());
		gen_paras(get_function_params(node));
		gen_func_body(get_function_body(node), fsize, FunTab);
		fprintf(stdout, "__%s_EXIT:\n", get_function_name(node));
		fprintf(stdout, "\tlw\t$ra, %d($sp)\n", fsize.size-4*fsize.paras-4);
		fprintf(stdout, "\tlw\t$fp, %d($sp)\n", fsize.size-4*fsize.paras-8);
		fprintf(stdout, "\tli\t$t%d, %d\n", GetReg(), fsize.size);
		fprintf(stdout, "\tadd\t$sp, $sp, $t%d\n", ShowReg());
		FreeReg(ShowReg());
		fprintf(stdout, "\tjr\t$ra\n");
	}
}

void gen_funcs_defs(Tree node) // generate function_definitions
{
	if (!is_empty_list(node)) {
		if (is_list(node)) { // a list node
			gen_funcs_defs(get_list_first(node));
			gen_funcs_defs(get_list_rest(node));
		} else { // not a list node
			gen_func_def(node);
		}
	} 
}

void GenCode(Tree root)// the starting function of our type checker
{
	Tree program_vars, program_funcs;
	
	program_vars = get_program_vars(root); 
	program_funcs = get_program_funcs(root); 
	
	if (program_vars != NULL) {
		fprintf(stdout, "\t.data\n");
		gen_vars_decs(program_vars, GLOBAL); // generate variable_declarations of the program
	}
	fprintf(stdout, "\t.text\n");
	gen_funcs_defs(program_funcs); // generate function_declarations of the program
}

int FreeReg(int i) // // Free a used register to be unused
{
	int index;
	if (Reg[i] == 1) {
		Reg[i] = 0;
	} else {
		fprintf(stderr, "Free Register Error: Register t%d is free\n", i);
		return -1;
	}
	return i;
}

int GetReg() // get an empty register to use 
{
	int index;

	for (index = 0; index < 10; index++) {	// allocate a free register
		if (Reg[index] == 0) {
			break; 
		}
	}
	if (index == 10) {
		fprintf(stderr, "Used out of the registers\n");
	} else {
		Reg[index] = 1;
		return index; 
	}
}

int ShowReg() // show the latest used register
{
	int index;

	for (index = 0; index < 10; index++) {
		if (Reg[index] == 0) {
			break; 
		}
	}
	return --index; 
}

int NewLabel()
{
	return ++Lindex;
}

int ShowLabel()
{
	return Lindex;
}

int SetVars(char *name, SymTable stb)
{
	int vars = 0;
	Symbol stbptr;
	stbptr = LookFunc(stb, name);
	
	if (stbptr != NULL) {
		vars = symbol_get_function_vars(stbptr); 
	}
	return vars;
}

int SetParas(char *name, SymTable stb) 
{ 
	int paras = 0;
	Symbol stbptr;
	stbptr = LookFunc(stb, name);

	if (stbptr != NULL) {
		paras =  symbol_get_function_arity(stbptr);
		
		if (paras < 4) {
			paras = 4;
		}
		return paras; 
	}
}

int SetFrame(int vars, int paras) // setup the frame size of a function
{
	int frame;
	
	frame = paras + vars + 2;

	if (frame%2 != 0) {
		++frame; 
	}
	return frame*4;
}

