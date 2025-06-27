
# Evolução do Compilador

Esta seção apresenta um histórico das principais evoluções técnicas e funcionais do compilador ao longo do desenvolvimento, organizadas por fase. O objetivo é destacar decisões importantes, melhorias incrementais e avanços em cada etapa da construção do projeto.

---

## Sprint 1 – Planejamento e Ambiente

- Definição da linguagem-fonte baseada em um subconjunto de C
- Configuração do ambiente com Flex, Bison, GCC e Git
- Estruturação inicial do repositório
- Criação de um arquivo `lexer.l` com os primeiros tokens simples
- Configuração do `parser.y` com uma produção base (`programa`)

---

## Sprint 2 – Análise Léxica e Sintática

- Expansão do analisador léxico (`lexer.l`) com suporte a:
  - Palavras-chave (`if`, `else`, `while`, `return`, etc.)
  - Tipos primitivos (`int`, `float`, `char`)
  - Literais (inteiros, floats, strings, caracteres)
  - Operadores e delimitadores
- Desenvolvimento das regras gramaticais principais no `parser.y`
- Implementação inicial da árvore sintática abstrata (AST)
- Testes básicos com código mínimo para validar integração Flex/Bison

---

## Sprint 3 – Análise Semântica

- Introdução da tabela de símbolos (`tabela.c/h`)
- Verificações de:
  - Variáveis não declaradas
  - Redeclaração de identificadores
  - Tipos incompatíveis em expressões e atribuições
- Testes negativos para casos semânticos
- Estruturação de escopos e tipos na AST

---

## Sprint 4 – Geração de Código

- Criação do módulo `conversor.c` para conversão da AST em Portugol
- Mapeamento das palavras-chave e estruturas C → Portugol
- Implementação de funções de impressão de código (tradução)
- Primeira versão funcional completa do compilador ponta a ponta
- Ajustes de ordem de nós na AST para refletir blocos e comandos

---

## Sprint 5 – Testes e Cobertura

- Criação da suíte de testes automatizados com scripts bash
- Implementação de `make test` e `make coverage`
- Geração de `cobertura.txt` com análise de regras ativadas
- Inclusão de testes léxicos, sintáticos e semânticos com entrada real
- Validação da tradução correta de funções, laços e condicionais

---

## Sprint 6 – Entrevista, Refino e Documentação

- Organização da documentação do projeto com MkDocs
- Revisão final dos testes

---

O compilador evoluiu de um protótipo com apenas regras léxicas até um sistema funcional que:

- Lê programas em C simplificado
- Gera uma árvore sintática abstrata
- Realiza análise semântica com verificação de tipos e escopo
- Produz código equivalente em Portugol
- Permite testes automatizados com análise de cobertura