CC = gcc
CFLAGS = -Wall -Iinclude -Isrc/semantic -Isrc/ast -Isrc/codegen
FLEX = flex
BISON = bison

SRC = src
OBJ = obj

# Arquivos de origem
LEXER = $(SRC)/lexer/lexer.l
PARSER = $(SRC)/parser/parser.y
MAIN = $(SRC)/main.c
AST = $(SRC)/ast/ast.c
TABELA = $(SRC)/semantic/tabela.c
TIPOS = $(SRC)/semantic/tipos.c
TAC = $(SRC)/codegen/tac.c
CODEGEN = $(SRC)/codegen/codegen.c

# Objetos 
OBJS = $(OBJ)/main.o $(OBJ)/lex.yy.o $(OBJ)/parser.tab.o $(OBJ)/ast.o $(OBJ)/tabela.o $(OBJ)/tipos.o $(OBJ)/tac.o $(OBJ)/codegen.o

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

$(OBJ)/tabela.o: $(TABELA) | $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/tipos.o: $(TIPOS) | $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/tac.o: $(TAC) | $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/codegen.o: $(CODEGEN) | $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/parser.tab.o: parser.tab.c | $(OBJ)
	$(CC) $(CFLAGS) -c parser.tab.c -o $@

$(OBJ)/lex.yy.o: lex.yy.c | $(OBJ)
	$(CC) $(CFLAGS) -c lex.yy.c -o $@

# Geração do parser
parser.tab.c parser.tab.h: $(PARSER)
	$(BISON) -d -o parser.tab.c $<

# Geração do scanner
lex.yy.c: $(LEXER) parser.tab.h
	$(FLEX) -o lex.yy.c $<

# Diretório obj
$(OBJ):
	mkdir -p $(OBJ)

clean:
	rm -f $(OBJ)/*.o
	rm -f $(TARGET)
	rm -f lex.yy.c parser.tab.*

test: $(TARGET)
	./$(TARGET) tests/teste1.txt

codegen-test: $(TARGET)
	./$(TARGET) -t tests/codegen/teste_expressoes.txt

.PHONY: all clean test codegen-test