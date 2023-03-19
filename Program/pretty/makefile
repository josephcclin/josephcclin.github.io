# ====================================================== #
# Author: Chuang-Chieh Lin				 #
# Email: lincc@cs.ccu.edu.tw				 #
# ------------------------------------------------------ #
# type "make all" or make parser to generate the parser  #
# type "make clean" to delete .o files and pretty        #
# ====================================================== #

OBJS = parser.o scanner.o tree.o
CC = gcc

all:pretty

pretty:$(OBJS)
	$(CC) -o pretty $(OBJS) -lfl
	
parser.o:lotuser.y
	bison -d lotuser.y
	$(CC) -c -o parser.o lotuser.tab.c

scanner.o:lex.yy.c
	$(CC) -c -o scanner.o lex.yy.c

tree.o:tree.c
	$(CC) -c tree.c

lex.yy.c:lotuser.l
	flex lotuser.l

clean:
	rm -f lex.yy.*
	rm -f *.o
	rm -f lotuser.tab.*
	rm -f pretty 

