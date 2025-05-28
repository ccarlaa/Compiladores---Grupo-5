#ifndef TABELA_H
#define TABELA_H

#include "tipos.h"

#define TAMANHO_TABELA 211

typedef enum { ESCALAR, FUNCAO, VETOR } CategoriaSimbolo;

typedef struct Simbolo {
    char* nome;
    Tipo tipo;
    CategoriaSimbolo categoria;
    int escopo;
    struct Simbolo* proximo; // encadeamento para tratar colisões
} Simbolo;

void inicializa_tabela();
void entra_escopo();
void sai_escopo();

Simbolo* insere_simbolo(char* nome, Tipo tipo, CategoriaSimbolo categoria);
Simbolo* busca_simbolo(char* nome);
void imprime_tabela();

#endif
