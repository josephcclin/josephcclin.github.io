#type "make all" or make parser to generate the parser
#type "make clean" to remove the temporary object files

OBJS = scanner.o parser.o
CC = gcc

all:parser

parser:$(OBJS)
	$(CC) -o parser $(OBJS) -lfl
	
parser.o:lotuser.y scanner.o
	$(CC) -c -o parser.o lotuser.tab.c	
	
scanner.o:lotuser.l lotuser.y
	bison -d lotuser.y
	flex lotuser.l
	$(CC) -c -o scanner.o lex.yy.c
	
clean:
	rm -f lex.yy.*
	rm -f *.o
	rm -f lotuser.tab.*
	rm -f parser
