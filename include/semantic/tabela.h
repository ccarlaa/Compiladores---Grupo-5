#ifndef TABELA_H
#define TABELA_H

#include "tipos.h"

void inicializa_tabela();
int insere_simbolo(const char* nome, TipoSimples tipo);
TipoSimples busca_simbolo(const char* nome);

#endif
