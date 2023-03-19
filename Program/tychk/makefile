# ============================================================ #
# Project 4: Implementation of a type checker                  #
# Author: Chuang-Chieh Lin				       #
# Email: lincc@cs.ccu.edu.tw				       #
# ------------------------------------------------------------ #
# type "make all" or make parser to generate the type checker  #
# type "make clean" to delete .o files and the type checker    #
# ============================================================ #

OBJS = parser.o scanner.o newtree.o symtab.o 
CC = gcc

all:typecheck

typecheck:$(OBJS)
	$(CC) -o typecheck $(OBJS) -lfl
	
parser.o:lotuser.y
	bison -d lotuser.y
	$(CC) -c -o parser.o lotuser.tab.c

scanner.o:lex.yy.c
	$(CC) -c -o scanner.o lex.yy.c

newtree.o:newtree.c
	$(CC) -c -o newtree.o newtree.c

symtab.o:symtab.c
	$(CC) -c -o symtab.o symtab.c
	
lex.yy.c:lotuser.l
	flex lotuser.l

clean:
	rm -f lex.yy.* *.o *.core lotuser.tab.* typecheck

