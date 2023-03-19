/*
 * Symbol table management routines.
 */

#include	"stdio.h"
#include	"symtab.h"

/* Define symbol table entry structure and type */
struct symentry {
        char    *lexeme;
        Class   class;
	int paturn; // record the order of the  parameter
	int lvturn; // record the order of the local variable
	int arity;
	int vars;
        SymTable tbl;
        Symbol next;
};

#define		HASHSIZE	11

/*
 * Calculate the starting index of symbol in the symbol table.
 */
static hash(symbol)
char	*symbol;
{
	int 	hashvalue;

	for (hashvalue = 0; *symbol != '\0'; ) {
		hashvalue += *symbol++;
	} /* endfor */

	return (hashvalue % HASHSIZE);

} /* hash */


/*
 * Create a new symbol table.
 */
SymTable new_symtab()
{
	int	i;
	SymTable tbl;

	tbl = (SymTable) malloc(sizeof(Symbol) * HASHSIZE);
	for (i = 0; i < HASHSIZE; i++) {
		tbl[i] = (Symbol) NULL;
	} /* endfor */
	return tbl;
} /* new_symtab */

/*
 * Lookup the symbol table for symbol.
 */
Symbol lookup(table, symbol)
SymTable table;
char	*symbol;
{
	Symbol	pointer;

	for (pointer = table[hash(symbol)]; pointer != NULL;
	     pointer = pointer->next) {
		if ((strcmp(symbol, pointer->lexeme) == 0) && 
		    (pointer->class != FUNCTION)) {
			return pointer; 
		} /* endif */
	} /* endfor */
	return NULL;
} /* lookup */
/*
 * Lookup the symbol table for FunName.
 */
Symbol LookFunc(table, FunName)
SymTable table;
char    *FunName;
{
	Symbol pointer;

	for (pointer = table[hash(FunName)]; pointer != NULL;
	     pointer = pointer->next) {
		if ((strcmp(FunName, pointer->lexeme) == 0) && 
		    (pointer->class == FUNCTION)) {
			return pointer;
		} // endif 
	} // endfor 
	return NULL;
} // LookFunc 

Class symbol_get_class(symbol)
Symbol symbol;
{
	return symbol->class;
}

int symbol_get_function_arity(Symbol symbol)
{
	return symbol->arity;
}

int symbol_get_function_vars(Symbol symbol)
{
	return symbol->vars;
}

int symbol_get_lvturn(Symbol symbol)
{
	return symbol->lvturn;
}

int symbol_get_paturn(Symbol symbol)
{
	return symbol->paturn;
}

SymTable symbol_get_function_table(Symbol symbol)
{
	        return symbol->tbl;
}

/*
 * Install symbol into the symbol table if it is not within the table,
 * and return the symbol pointer of symbol in table. Return NULL if
 * system can not allocate more storage for new symbol.
 */

Symbol install(table, symbol, class)
SymTable table;
char	*symbol;
Class	class;
{
	Symbol	pointer;
	int	hashvalue;

	if (class != FUNCTION) { // PARAMETER or VARIABLE
		if ((pointer = lookup(table, symbol)) == NULL) {
	   		pointer = (Symbol) malloc(sizeof(struct symentry));
	  		pointer->lexeme = symbol;
	   		pointer->class = class;
	   		pointer->arity = 0;
	   		pointer->vars = 0;
			pointer->paturn = 0;
			pointer->lvturn = 0;
	   		pointer->tbl = NULL;
	   		hashvalue = hash(symbol);
	   		pointer->next = table[hashvalue];
	   		table[hashvalue] = pointer;
		} else {
	   		pointer = NULL; // installing failed
		}
	} else { // FUNCTION
		if ((pointer = LookFunc(table, symbol)) == NULL) {
			pointer = (Symbol) malloc(sizeof(struct symentry));
			pointer->lexeme = symbol;
			pointer->class = FUNCTION;
			pointer->arity = 0;
			pointer->vars = 0;
			pointer->paturn = 0;
			pointer->lvturn = 0;
			pointer->tbl = NULL;
			hashvalue = hash(symbol);
			pointer->next = table[hashvalue];
			table[hashvalue] = pointer; 
		} else {
			pointer = NULL; // installing failed
		}
	}
	return pointer;
} /* install */

void symbol_set_function_arity(Symbol symbol, int arity)
{
	symbol->arity = arity;
}

void symbol_set_function_vars(Symbol symbol, int vars)
{
	symbol->vars = vars;
}

void symbol_set_function_table(Symbol symbol, SymTable tbl)
{
	symbol->tbl = tbl;
}

void symbol_set_lvturn(Symbol symbol, int lvturn)
{
	symbol->lvturn = lvturn;
}

void symbol_set_paturn(Symbol symbol, int paturn)
{
	symbol->paturn = paturn;
}

/*
 * Print the symbol tables.
 */
void print_symtab(tbl)
SymTable tbl;
{
	int i;
	Symbol ptr;

	for (i = 0; i < HASHSIZE; i++) {
		ptr = tbl[i];
		while (ptr != NULL) {
		    printf("%s: ", ptr->lexeme);
		    switch (ptr->class) {
		        case FUNCTION: 
				printf("FUNCTION, %d\n", ptr->arity); 
				printf("*** The symbol table for function %s begins ***\n", ptr->lexeme);
				print_symtab(ptr->tbl);
				printf("*** The symbol table for function %s ends ***\n", ptr->lexeme);
				break;
		        case VARIABLE: 
				printf("VARIABLE\n"); 
				break;
		        case PARAMETER: 
				printf("PARAMETER\n"); 
				break;
			default: 
				fprintf(stderr, "compiler error: Illegal Identifier tag %d in symbol table\n", ptr->class); 
				break;
		    }
		    ptr = ptr->next;
		} /* endwhile */
	} /* endfor */
} /* print_symtab */

