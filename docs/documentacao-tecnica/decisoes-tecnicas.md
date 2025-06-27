# Análise Detalhada das Decisões Técnicas

## 1. Requisitos e Escopo do Compilador

A principal decisão técnica foi definir um subconjunto limitado e estruturado da linguagem C como escopo do projeto. A análise dos arquivos da gramática (`parser/parser.y`) e do analisador léxico (`lexer/lexer.l`) revela que o compilador foi projetado para englobar os seguintes requisitos funcionais:

*   **Estrutura de Programa:** Suporte para múltiplas funções, com a função `main` sendo o ponto de entrada, traduzida para `funcao inicio` em Portugol.
*   **Tipos de Dados Primitivos:** O compilador lida com os tipos de dados fundamentais: `int` (inteiro), `float` (real) e `char` (caractere).
*   **Declaração e Atribuição:** Permite a declaração de variáveis, com ou sem inicialização, e comandos de atribuição simples (`=`) e compostos (`+=`, `-=`).
*   **Estruturas de Controle de Fluxo:**
    *   **Condicionais:** Suporte completo para `if`, `else` e `else if`.
    *   **Laços de Repetição:** Implementação do `while` e `do-while`.
*   **Funções:** Suporte para declaração e chamada de funções com parâmetros.
*   **Operadores:** Cobertura de operadores aritméticos (`+`, `-`, `*`, `/`, `%`), relacionais (`==`, `!=`, `<`, `>`, `<=`, `>=`) e lógicos (`&&`, `||`, `!`).
*   **Funções de E/S Básicas:** Conversão de `printf` e `scanf` para as funções `escreva` e `leia` do Portugol, com tratamento da string de formatação no `printf`.

## 2. Justificativa para as Funcionalidades Não Implementadas

A escolha de não implementar certas características avançadas do C foi uma decisão técnica crucial para manter a complexidade do projeto gerenciável, provavelmente alinhada a objetivos acadêmicos ou de prova de conceito.

### Por que não há `for`?

O laço `for` em C é, essencialmente, um "açúcar sintático" para o laço `while`. Um comando `for (A; B; C) { D; }` pode ser reescrito como `A; while (B) { D; C; }`.

A decisão de omitir o `for` simplifica diretamente a gramática no `parser/parser.y` e a lógica de geração de código no `conversor.c`. Em vez de criar um nó `NODE_FOR` na AST com quatro filhos (inicialização, condição, incremento e corpo), o compilador pode se concentrar em uma única estrutura de laço condicional (o `while`), reduzindo a complexidade de implementação sem perder poder computacional essencial.

### Por que não há `struct`?

A implementação de `structs` (estruturas) introduziria uma camada significativamente maior de complexidade, por várias razões:

*   **Gerenciamento de Tipos:** Seria necessário estender a tabela de símbolos para armazenar tipos complexos definidos pelo usuário, incluindo os nomes e tipos de cada um de seus membros.
*   **Alocação de Memória e Acesso a Membros:** A tradução de acesso a membros (`.` ou `->`) exigiria uma lógica mais complexa na AST e no gerador de código. Embora os tokens `T_DOT` e `T_ARROW` existam no analisador léxico, sua implementação na gramática para `structs` não foi concluída.
*   **Correspondência com Portugol:** Muitas implementações de Portugol não têm um equivalente direto e simples para `structs` (o mais próximo seria `registro`). A tradução não seria trivial e poderia poluir o objetivo de gerar um código Portugol claro e idiomático.

A ausência dessas funcionalidades define o compilador como um tradutor de C estruturado e procedural, deixando de fora características de mais baixo nível ou de agregação de dados complexos.

## 3. A Escolha da AST como Único Código Intermediário

A decisão de usar a Árvore Sintática Abstrata (AST) como a única representação intermediária (RI) é uma escolha de design pragmática e eficiente para este tipo de compilador.

### Por que a AST é suficiente?

Este é um compilador de **fonte para fonte** (source-to-source), que traduz de uma linguagem de alto nível (C) para outra (Portugol). As duas linguagens compartilham paradigmas semelhantes (procedural, estruturado).

A AST (`src/ast.c`, `include/ast.h`) preserva a estrutura hierárquica do código-fonte, o que é ideal para este tipo de tradução. A função `generate_portugol` (`src/conversor.c`) pode simplesmente "percorrer" a árvore e traduzir cada nó estrutural (um `if`, um `while`, uma declaração) para seu equivalente direto em Portugol.

### Por que não usar outra RI (como Código de Três Endereços)?

Representações intermediárias mais baixas, como o **Código de Três Endereços (C3E)**, são projetadas para facilitar otimizações e a geração de código de máquina (assembly). Em C3E, uma expressão como `x = a + b * c` é quebrada em:

```
t1 = b * c
x = a + t1
```

Para este compilador, gerar C3E a partir da AST para depois gerar Portugol seria um passo desnecessário e contraproducente:

*   **Perda de Estrutura:** O C3E "achata" as estruturas de controle de alto nível (`if`, `while`) em saltos condicionais e incondicionais (`goto`). Reconstruir a estrutura de um `se` ou `enquanto` a partir de `gotos` para gerar um código Portugol legível seria muito mais complexo do que a tradução direta da AST.
*   **Complexidade Adicional:** Introduziria uma fase inteira de compilação (geração de RI de baixo nível) que não agrega valor, dado que o alvo não é código de máquina e as otimizações complexas estão fora do escopo do projeto.

Portanto, a AST foi a decisão técnica por ser a representação mais simples e direta que atende perfeitamente aos requisitos de um tradutor de C para Portugol com o escopo definido.