
# Melhorias Futuras

Este documento apresenta as principais limitações do compilador desenvolvido e sugere direções para evoluções futuras.

---

## Possíveis Melhorias Futuras

### 1. Suporte a Funções Personalizadas

- Permitir múltiplas definições de função com parâmetros
- Controlar escopo local e retorno por tipo

### 2. Expansão de Tipos e Modificadores

- Adicionar suporte a `double`, `long`, arrays e ponteiros
- Implementar análise de conversões automáticas entre tipos

### 3. Análise de Escopo Avançada

- Suporte a blocos internos com escopo local
- Implementação de pilha de escopos na tabela de símbolos

### 4. Geração de Código Intermediário

- Produzir uma representação em código de três endereços
- Basear-se em uma AST para posterior otimização

### 5. Geração de Código Executável

- Integração com back-end (LLVM ou Assembly)
- Geração de código de máquina simples

### 6. Validação Estática e Otimizações

- Verificação de inicialização de variáveis
- Otimização de expressões constantes