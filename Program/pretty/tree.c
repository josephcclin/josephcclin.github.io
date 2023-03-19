#include <stdio.h>
#include "tree.h"

Tree syntax_tree = NULL;

struct tree {
    int tag;
    int valop;
    char *name;
    struct tree *first;
    struct tree *second;
    struct tree *third;
};

static Tree new_tree_node()
{
    Tree t;

    t = (Tree) malloc(sizeof(struct tree));
    t->tag = 0;
    t->valop = 0;
    t->name = NULL;
    t->first = t->second = t->third = NULL;
    return t;
}

Tree build_id(char *var)
{
    Tree t;

    t = new_tree_node();
    t->tag = TREE_ID;
    t->name = var;
    return t;
}

Tree build_intcon(int value)
{
    Tree t;

    t = new_tree_node();
    t->tag = TREE_INTCON;
    t->valop = value;
    return t;
}

Tree build_expr(int op, Tree left, Tree right)
{
    Tree t;

    t = new_tree_node();
    t->tag = TREE_OP;
    t->valop = op;
    t->first = left;
    t->second = right;
    return t;
}

Tree build_call(char *name, Tree args)
{
    Tree t;

    t = new_tree_node();
    t->tag = TREE_CALL;
    t->name = name;
    t->first = args;
    return t;
}

Tree build_assign(char *var, Tree expr)
{
    Tree t;

    t = new_tree_node();
    t->tag = TREE_ASSIGN;
    t->name = var;
    t->first = expr;
    return t;
}

Tree build_if(Tree expr, Tree thenstmt, Tree elsestmt)
{
    Tree t;

    t = new_tree_node();
    t->tag = TREE_IF;
    t->first = expr;
    t->second = thenstmt;
    t->third = elsestmt;
    return t;
}

Tree build_while(Tree expr, Tree stmt)
{
    Tree t;

    t = new_tree_node();
    t->tag = TREE_WHILE;
    t->first = expr;
    t->second = stmt;
    return t;
}

Tree build_exit()
{
    Tree t;

    t = new_tree_node();
    t->tag = TREE_EXIT;
    return t;
}

Tree build_return(Tree expr)
{
    Tree t;

    t = new_tree_node();
    t->tag = TREE_RETURN;
    t->first = expr;
    return t;
}

Tree build_read(char *var)
{
    Tree t;

    t = new_tree_node();
    t->tag = TREE_READ;
    t->name = var;
    return t;
}

Tree build_write(Tree expr)
{
    Tree t;

    t = new_tree_node();
    t->tag = TREE_WRITE;
    t->first = expr;
    return t;
}

Tree build_list(Tree list, Tree element)
{
    Tree t, l;

    t = new_tree_node();
    t->tag = TREE_LIST;
    t->first = element;
    if (list == NULL) {
        return t;
    } else {
        l = list;
        while (l->second != NULL) l = l->second;
        l->second = t;
        return list;
    }
}

Tree build_body(Tree vars, Tree stmts)
{
    Tree t;

    t = new_tree_node();
    t->tag = TREE_BODY;
    t->first = vars;
    t->second = stmts;
    return t;
}

Tree build_function(char * name, Tree params, Tree body)
{
    Tree t;

    t = new_tree_node();
    t->tag = TREE_FUNC;
    t->name = name;
    t->first = params;
    t->second = body;
    return t;
}

Tree build_program(Tree vars, Tree funcs)
{
    Tree t;

    t = new_tree_node();
    t->tag = TREE_PROG;
    t->first = vars;
    t->second = funcs;
    return t;
}

int get_node_tag(Tree t)
{
    return t->tag;
}

char * get_id_name(Tree t)
{
    return t->name;
}

int get_intcon_value(Tree t)
{
    return t->valop;
}

int get_expr_op(Tree t)
{
    return t->valop;
}

Tree get_expr_left(Tree t)
{
    return t->first;
}

Tree get_expr_right(Tree t)
{
    return t->second;
}

char * get_call_name(Tree t)
{
    return t->name;
}

Tree get_call_args(Tree t)
{
    return t->first;
}

char * get_assign_var(Tree t)
{
    return t->name;
}

Tree get_assign_expr(Tree t)
{
    return t->first;
}

Tree get_if_expr(Tree t)
{
    return t->first;
}

Tree get_if_thenstmt(Tree t)
{
    return t->second;
}

Tree get_if_elsestmt(Tree t)
{
    return t->third;
}

Tree get_while_expr(Tree t)
{
    return t->first;
}

Tree get_while_stmt(Tree t)
{
    return t->second;
}

Tree get_return_expr(Tree t)
{
    return t->first;
}

char * get_read_var(Tree t)
{
    return t->name;
}

Tree get_write_expr(Tree t)
{
    return t->first;
}

int is_list(Tree t)
{
    return t->tag == TREE_LIST;
}

int is_empty_list(Tree t)
{
    return t == NULL;
}

Tree get_list_first(Tree t)
{
    return t->first;
}

Tree get_list_rest(Tree t)
{
    return t->second;
}

char * get_function_name(Tree t)
{
    return t->name;
}

Tree get_function_params(Tree t)
{
    return t->first;
}

Tree get_function_body(Tree t)
{
    return t->second;
}

Tree get_body_vars(Tree t)
{
    return t->first;
}

Tree get_body_stmts(Tree t)
{
    return t->second;
}

Tree get_program_vars(Tree t)
{
    return t->first;
}

Tree get_program_funcs(Tree t)
{
    return t->second;
}

