# Reunião 1 - Planejamento Inicial

**Data e Hora:** 13/04/2025, 20:00   
**Local:** Google Meets   
**Participantes:** Todos os membros do Grupo 5

## Pauta

1. Apresentação do projeto de compilador C em português
2. Definição do escopo inicial
3. Divisão de tarefas
4. Cronograma de desenvolvimento

## Discussões e Decisões

### 1. Apresentação do Projeto

O projeto consiste em desenvolver um compilador para a linguagem C com palavras-chave traduzidas para português. O objetivo é criar uma ferramenta que facilite o aprendizado de programação para falantes de português, mantendo a compatibilidade com a sintaxe e semântica da linguagem C.

### 2. Escopo Inicial

Decidimos implementar o compilador em fases:

- **Fase 1:** Analisador léxico (reconhecimento de tokens)
- **Fase 2:** Analisador sintático (gramática básica)
- **Fase 3:** Expansão da gramática (estruturas, funções, etc.)
- **Fase 4:** Testes e correções
- **Fase 5:** Documentação e finalização

Para a primeira versão, decidimos focar nas seguintes funcionalidades:
- Tipos básicos (inteiro, real, caractere, etc.)
- Estruturas de controle (se, senao, enquanto, para)
- Declarações de variáveis e funções
- Função principal (equivalente à main)

### 3. Divisão de Tarefas

Ficou acordado que na primeira semana o grupo irá desenvolver o analisador léxico, dividido da seguinte forma:

- **Carla:** Tipos de variáveis (lexico_variavel.l)
- **Kauan:** Laços de repetição (lexico_lacos.l)
- **Kallyne:** Condicionais (lexico_condicionais.l)
- **Leonardo:** Switch Case (lexico_switchcase.l)
- **João:** Operadores (lexico_operadores.l)
- **Clara:** Pontuação e Comentários (lexico_pontuacao.l)

Na segunda semana, o grupo irá focar no desenvolvimento do analisador sintático (parser.y), integrando os componentes do analisador léxico desenvolvidos na primeira semana.

### 4. Cronograma

- **Semana 1:** Desenvolvimento do analisador léxico (dividido entre os membros conforme especificado acima)
- **Semana 2:** Implementação do analisador sintático, expansão da gramática, testes e correções
- **Semana 3:** Atualização da documentação e preparação para apresentação

## Tarefas Atribuídas

1. **Todos os membros:** Estudar a documentação do Flex e Bison
2. **Carla:** Implementar o reconhecimento de tipos de variáveis no analisador léxico
3. **Kauan:** Implementar o reconhecimento de laços de repetição no analisador léxico
4. **Kallyne:** Implementar o reconhecimento de condicionais no analisador léxico
5. **Leonardo:** Implementar o reconhecimento de switch case no analisador léxico
6. **João:** Implementar o reconhecimento de operadores no analisador léxico
7. **Clara:** Implementar o reconhecimento de pontuação e comentários no analisador léxico
8. **Todos os membros:** Preparar a estrutura do projeto e ambiente de desenvolvimento

## Próxima Reunião

A próxima reunião ficou agendada para o domingo seguinte (20/04/25), com o objetivo de acompanhar a evolução das tarefas.