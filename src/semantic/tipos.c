#include "semantic/tipos.h"

TipoSimples verifica_tipo_atribuicao(TipoSimples esperado, TipoSimples recebido) {
    if (esperado == recebido) {
        return esperado;
    }

    // Conversões permitidas: int -> real
    if (esperado == TIPO_REAL_ && recebido == TIPO_INT) {
        return esperado;
    }

    return TIPO_INVALIDO;
}

TipoSimples verifica_tipo_binario(TipoSimples tipo1, TipoSimples tipo2) {
    if (tipo1 == tipo2) {
        return tipo1;
    }

    // Se um dos tipos for real, promover para real
    if ((tipo1 == TIPO_REAL_ && tipo2 == TIPO_INT) ||
        (tipo2 == TIPO_REAL_ && tipo1 == TIPO_INT)) {
        return TIPO_REAL_;
    }

    return TIPO_INVALIDO;
}
