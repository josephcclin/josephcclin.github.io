/*
 * Header file for syntax tree management routines.
 */

#ifndef _TREE_H_
#define _TREE_H_

/* the following constants define the tags of syntax tree nodes */
#define TREE_ID		1
#define TREE_INTCON	2
#define TREE_OP		3
#define TREE_CALL	4
#define TREE_ASSIGN	5
#define TREE_IF		6
#define TREE_WHILE 	7
#define TREE_EXIT 	8
#define TREE_RETURN 	9
#define TREE_READ 	10
#define TREE_WRITE 	11
#define TREE_LIST 	12
#define TREE_BODY 	13
#define TREE_FUNC 	14
#define TREE_PROG 	15

/* The following defines a type of a pointer to a syntax tree node */ 
typedef struct tree *Tree;

/* The following defines a global variable pointing to the root of the */
/* syntax tree                                                         */ 
extern Tree syntax_tree;

/* The following functions build a particular syntax tree node */

/* Node for an identifier */
Tree build_id(char * var, int position);

/* Node for an integer constant */
Tree build_intcon(int value);

/* Node for an expression */
Tree build_expr(int op, Tree left, Tree right);

/* Node for a function call */
Tree build_call(char *name, Tree args, int position);

/* Node for an assignment statement */
Tree build_assign(char *var, Tree expr, int position);

/* Node for an if statement */
Tree build_if(Tree expr, Tree thenstmt, Tree elsestmt);

/* Node for a while statement */
Tree build_while(Tree expr, Tree stmt);

/* Node for an exit statement */
Tree build_exit();

/* Node for a return statement */
Tree build_return(Tree expr);

/* Node for a read statement */
Tree build_read(char *var, int position);

/* Node for a write statement */
Tree build_write(Tree expr);

/* Node for a list. This function appends the element last at
   the end of the list front. This function can be used to
   construct variable_declarations, function_definitions,
   parameters, statements, arguments
 */
Tree build_list(Tree front, Tree last);

/* Node for a function body. vars is the list of local variable 
   declarations, and stmts is the list of statements
 */
Tree build_body(Tree vars, Tree stmts);

/* Node for a function. name is the function name, params is 
   the list of parameters, body is the function body 
 */
Tree build_function(char * name, Tree params, Tree body, int position);

/* Node for a program. vars is the list of global variable declarations and
   funcs is the list of function definitions
 */
Tree build_program(Tree vars, Tree funcs);

/* The following functions get information from a syntax tree node */

/* Return the tag of the tree node t */
int get_node_tag(Tree t);

/* Return the name of an identifier */
char * get_id_name(Tree t);

/* Return the value of an integer constant */
int get_intcon_value(Tree t);

/* Return the operator of an expression */
int get_expr_op(Tree t);

/* Return the lineno of an identifier */
int get_id_lineno(Tree t);

/* Return the left operand of an expression */
Tree get_expr_left(Tree t);

/* Return the right operand of an expression */
Tree get_expr_right(Tree t);

/* Return the name of a function call */
char * get_call_name(Tree t);

/* Return the list of arguments of a function call */
Tree get_call_args(Tree t);

/* Return the variable of an assignment statement */
char * get_assign_var(Tree t);

/* Return the expression of an assignment statement */
Tree get_assign_expr(Tree t);

/* Return the expression of an if statement */
Tree get_if_expr(Tree t);

/* Return the then statement of an if statement */
Tree get_if_thenstmt(Tree t);

/* Return the else statement of an if statement */
Tree get_if_elsestmt(Tree t);

/* Return the expression of a while statement */
Tree get_while_expr(Tree t);

/* Return the statement of a while statement */
Tree get_while_stmt(Tree t);

/* Return the expression of a return statement */
Tree get_return_expr(Tree t);

/* Return the variable of a read statement */
char * get_read_var(Tree t);

/* Return the expression of a write statement */
Tree get_write_expr(Tree t);

/* Check if a tree is a list */
int is_list(Tree t);

/* Check if a list is an empty list */
int is_empty_list(Tree t);

/* Return the first element of a list */
Tree get_list_first(Tree t);

/* Return the remaining list of removing the first element of a list */
Tree get_list_rest(Tree t);

/* Return the name of a function */
char * get_function_name(Tree t);

/* Return the list of parameters of a function */
Tree get_function_params(Tree t);

/* Return the list of parameters of a function */
Tree get_function_body(Tree t);

/* Return the list of local variable declarations of a function body */
Tree get_body_vars(Tree t);

/* Return the list of statements of a function body */
Tree get_body_stmts(Tree t);

/* Return the list of global variable declarations of a program */
Tree get_program_vars(Tree t);

/* Return the list of functions of a program */
Tree get_program_funcs(Tree t);

#endif
