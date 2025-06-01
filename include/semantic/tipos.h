#ifndef TIPOS_H
#define TIPOS_H

typedef enum {
    TIPO_INVALIDO,
    TIPO_INT,
    TIPO_REAL_
} TipoSimples;

TipoSimples verifica_tipo_atribuicao(TipoSimples esperado, TipoSimples recebido);
TipoSimples verifica_tipo_binario(TipoSimples tipo1, TipoSimples tipo2);

#endif
