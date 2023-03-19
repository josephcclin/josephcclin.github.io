# ================================== #
# Makefile for the scanner for Lotus #
# Author: Chuang-Chieh Lin	     #
# ================================== #

CC = gcc

all:scanner

scanner:lotuser.l
	flex lotuser.l
	$(CC) -o scanner lex.yy.c

clean:
	rm -f lex.yy.*
	rm -f *.o
	rm -f scanner

