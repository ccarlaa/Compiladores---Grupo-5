#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabela.h"

static Simbolo* tabela[TAMANHO_TABELA];
static int escopo_atual = 0;

static int hash(char* nome) {
    int h = 0;
    for (int i = 0; nome[i] != '\0'; i++) {
        h = (h * 31 + nome[i]) % TAMANHO_TABELA;
    }
    return h;
}

void inicializa_tabela() {
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        tabela[i] = NULL;
    }
    escopo_atual = 0;
}

void entra_escopo() {
    escopo_atual++;
}

void sai_escopo() {
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        Simbolo* atual = tabela[i];
        Simbolo* anterior = NULL;
        while (atual) {
            if (atual->escopo == escopo_atual) {
                if (anterior == NULL) {
                    tabela[i] = atual->proximo;
                } else {
                    anterior->proximo = atual->proximo;
                }
                Simbolo* temp = atual;
                atual = atual->proximo;
                free(temp->nome);
                free(temp);
            } else {
                anterior = atual;
                atual = atual->proximo;
            }
        }
    }
    escopo_atual--;
}

Simbolo* insere_simbolo(char* nome, Tipo tipo, CategoriaSimbolo categoria) {
    int indice = hash(nome);
    Simbolo* novo = (Simbolo*)malloc(sizeof(Simbolo));
    novo->nome = strdup(nome);
    novo->tipo = tipo;
    novo->categoria = categoria;
    novo->escopo = escopo_atual;
    novo->proximo = tabela[indice];
    tabela[indice] = novo;
    return novo;
}

Simbolo* busca_simbolo(char* nome) {
    int indice = hash(nome);
    Simbolo* atual = tabela[indice];
    while (atual) {
        if (strcmp(atual->nome, nome) == 0) {
            return atual;
        }
        atual = atual->proximo;
    }
    return NULL;
}

void imprime_tabela() {
    printf("Tabela de símbolos:\n");
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        Simbolo* atual = tabela[i];
        while (atual) {
            printf("Nome: %s, Tipo: %d, Escopo: %d, Categoria: %d\n",
                   atual->nome, atual->tipo, atual->escopo, atual->categoria);
            atual = atual->proximo;
        }
    }
}
