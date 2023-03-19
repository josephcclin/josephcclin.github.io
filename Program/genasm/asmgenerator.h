/* 
 * head file for asmgenerater.c
 */

#ifndef _ASMGENERATOR_H_
#define _ASMGENERATOR_H_

enum {LOCAL, GLOBAL} scope;
static int Reg[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // registers $t0-$t9
struct items {
        int paras;
        int vars;
        int size;
        char *fun_name;
};

typedef struct items Frame;

struct LabelTF {
	int T;
	int F;
};

typedef struct LabelTF LABEL;

int GetReg();
int NewLabel();
int FreeReg(int);
int ShowReg();
int SetVars(char *, SymTable);
int SetParas(char *, SymTable);
int SetFrame(int, int);

void gen_boolprm(Tree, Frame, SymTable, LABEL);
void gen_boolfact(Tree, Frame, SymTable, LABEL);
void gen_boolterm(Tree, Frame, SymTable, LABEL);
void gen_boolexpr(Tree, Frame, SymTable, LABEL);
void gen_ariprm(Tree, Frame, SymTable);
void gen_arifact(Tree, Frame, SymTable);
void gen_term(Tree, Frame, SymTable);
void gen_expr_list(Tree, Frame, SymTable, int);
void gen_ariexprs(Tree, Frame, SymTable, int);
void gen_ariexpr(Tree, Frame, SymTable);
void gen_assignstmt(Tree, Frame, SymTable);
void gen_cmpdstmt(Tree, Frame, SymTable);
void gen_ifstmt(Tree, Frame, SymTable);
void gen_whistmt(Tree, Frame, SymTable);
void gen_retstmt(Tree, Frame, SymTable);
void gen_exitstmt(Tree, Frame, SymTable);
void gen_readstmt(Tree, Frame, SymTable);
void gen_writestmt(Tree, Frame, SymTable);
void gen_stmt(Tree, Frame, SymTable);
void gen_stmts(Tree, Frame, SymTable);
void gen_paralist(Tree);
void gen_paras(Tree);
void gen_func_body(Tree, Frame, SymTable);
void gen_var_dec(Tree, int);
void gen_vars_decs(Tree, int);
void gen_func_def(Tree);
void gen_funcs_defs(Tree);
void GenCode(Tree);

#endif

