/*
 * Header file for symbol table management routines.
 */

#ifndef _SYMTAB_H_
#define _SYMTAB_H_

typedef enum {FUNCTION, VARIABLE, PARAMETER} Class;
typedef struct symentry *Symbol;
typedef Symbol *SymTable;

SymTable GblTab;

SymTable new_symtab();
Symbol lookup(SymTable, char *);
Symbol LookFunc(SymTable, char *);
Class symbol_get_class(Symbol);
int symbol_get_function_arity(Symbol);
int symbol_get_function_vars(Symbol);
int symbol_get_lvturn(Symbol);
int symbol_get_paturn(Symbol);
SymTable symbol_get_function_table(Symbol);
Symbol install(SymTable, char *, Class);
void symbol_set_function_arity(Symbol, int);
void symbol_set_function_vars(Symbol, int);
void symbol_set_lvturn(Symbol, int);
void symbol_set_paturn(Symbol, int);
void symbol_set_function_table(Symbol, SymTable);
void print_symtab(SymTable);

#endif
