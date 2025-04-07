CC = gcc
CFLAGS = -Wall -Iinclude
FLEX = flex
BISON = bison

all: compilador.exe

compilador.exe: main.o lexer.o parser.o ast.o
	$(CC) $(CFLAGS) -o compilador.exe main.o lexer.o parser.o ast.o

main.o: src/main.c parser.tab.h
	$(CC) $(CFLAGS) -c src/main.c

lexer.o: lex.yy.c
	$(CC) $(CFLAGS) -c lex.yy.c

parser.o: parser.tab.c
	$(CC) $(CFLAGS) -c parser.tab.c

ast.o: src/ast/ast.c
	$(CC) $(CFLAGS) -c src/ast/ast.c

lex.yy.c: src/lexer/lexer.l parser.tab.h
	$(FLEX) src/lexer/lexer.l

parser.tab.c parser.tab.h: src/parser/parser.y
	$(BISON) -d src/parser/parser.y

clean:
	del *.o
	del *.exe
	del lex.yy.c
	del parser.tab.*

test: compilador.exe
	compilador.exe < tests/teste1.txt

.PHONY: all clean test
