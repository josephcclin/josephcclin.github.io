# ============================================================= #
# Project 5: Implementation of a Code Generator                 #
# Author: Chuang-Chieh Lin				        #
# Email: lincc@cs.ccu.edu.tw				        #
# ------------------------------------------------------------  #
# type "make all" or make lotus to generate the code generator  #
# type "make clean" to delete .o files and the code generator   #
# ============================================================= #

OBJS = parser.o scanner.o newtree.o symtab.o 
CC = gcc

all:lotus

lotus:$(OBJS)
	$(CC) -o lotus $(OBJS) -lfl
	
parser.o:lotuser.y
	bison -d lotuser.y
	$(CC) -c -o parser.o lotuser.tab.c

scanner.o:lex.yy.c
	$(CC) -c -o scanner.o lex.yy.c

symtab.o:symtab.c
	$(CC) -c -o symtab.o symtab.c
	
newtree.o:newtree.c
	$(CC) -c newtree.c

lex.yy.c:lotuser.l
	flex lotuser.l

clean:
	rm -f lex.yy.* *.o lotuser.tab.* *.core lotus

