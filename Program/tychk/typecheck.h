/*
 * Header file for typecker routines.
 */

#ifndef _TYPECHECK_H_
#define _TYPECHECK_H_

void check_boolprm(Tree, SymTable);
void check_boolfact(Tree, SymTable);
void check_boolterm(Tree, SymTable);
void check_boolexpr(Tree, SymTable);
void check_ariprm(Tree, SymTable);
void check_arifact(Tree, SymTable);
void check_term(Tree, SymTable);
int check_expr_list(Tree, SymTable, int);
int check_ariexprs(Tree, SymTable);
void check_ariexpr(Tree, SymTable);
void check_assignstmt(Tree, SymTable);
void check_cmpdstmt(Tree, SymTable);
void check_ifstmt(Tree, SymTable);
void check_whistmt(Tree, SymTable);
void check_retstmt(Tree, SymTable);
void check_exitstmt(Tree, SymTable);
void check_readstmt(Tree, SymTable);
void check_writestmt(Tree, SymTable);
void check_stmt(Tree, SymTable);
void check_stmts(Tree, SymTable);
int check_paralist(Tree, SymTable, int);
int check_paras(Tree, SymTable);
void check_func_body(Tree, Symbol);
int check_var_dec(Tree, SymTable, int);
int check_vars_decs(Tree, SymTable, int);
void check_func_def(Tree);
void check_funcs_defs(Tree);
int chktype(Tree);

#endif
