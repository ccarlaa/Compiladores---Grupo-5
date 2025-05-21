CC = gcc
CFLAGS = -Wall -Iinclude
FLEX = flex
BISON = bison

SRC = src
OBJ = obj

# Arquivos de origem
LEXER = $(SRC)/lexer/lexer.l
PARSER = $(SRC)/parser/parser.y
MAIN = $(SRC)/main.c
AST = $(SRC)/ast/ast.c

# Objetos
OBJS = $(OBJ)/main.o $(OBJ)/lex.yy.o $(OBJ)/parser.tab.o $(OBJ)/ast.o

# Executável
TARGET = compilador.exe

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compilar arquivos .o com dependência de headers
$(OBJ)/main.o: $(MAIN) parser.tab.h | $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/ast.o: $(AST) | $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/parser.tab.o: parser.tab.c | $(OBJ)
	$(CC) $(CFLAGS) -c parser.tab.c -o $@

$(OBJ)/lex.yy.o: lex.yy.c | $(OBJ)
	$(CC) $(CFLAGS) -c lex.yy.c -o $@

# Geração do parser
parser.tab.c parser.tab.h: $(PARSER)
	$(BISON) -d $<

# Geração do scanner
lex.yy.c: $(LEXER) parser.tab.h
	$(FLEX) $<

# Diretório obj
$(OBJ):
	mkdir -p $(OBJ)

clean:
	rm -f $(OBJ)/*.o
	rm -f $(TARGET)
	rm -f lex.yy.c parser.tab.*

test: $(TARGET)
	./$(TARGET) < tests/teste1.txt

.PHONY: all clean test
