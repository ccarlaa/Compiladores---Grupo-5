# Testes do Compilador

Esta seção detalha os procedimentos de teste implementados para validar o funcionamento do compilador C em Português.

## Visão Geral

O compilador possui diferentes tipos de testes para validar cada fase do processo de compilação:

- **Testes Léxicos**: Validam o reconhecimento de tokens e a detecção de erros léxicos
- **Testes Sintáticos**: Verificam a correta análise da estrutura gramatical do código
- **Testes Semânticos**: Avaliam a correta interpretação do significado do código

## Modo de Depuração

Foi implementado um modo de depuração no compilador que permite executar apenas o analisador léxico, facilitando a visualização de tokens e mensagens de erro léxico. Este modo é ativado através da flag `-d` ou `--debug` na linha de comando.

```bash
./compilador arquivo.txt -d
```

Quando ativado, o modo de depuração:

1. Executa apenas o analisador léxico (`yylex()`)
2. Exibe cada token reconhecido, incluindo seu código e lexema
3. Mostra mensagens de erro léxico detalhadas
4. Não executa a análise sintática ou semântica

Este modo é especialmente útil para testar e validar o tratamento de erros léxicos.

## Tipos de Testes

O compilador possui diferentes tipos de testes para validar cada aspecto do seu funcionamento:

1. **Testes de Funcionalidades Básicas**: Verificam o funcionamento correto do compilador com código válido
2. **Testes Léxicos**: Validam o reconhecimento de tokens e a detecção de erros léxicos
3. **Testes Sintáticos**: Verificam a correta análise da estrutura gramatical do código
4. **Testes de Estruturas de Controle**: Focam especificamente em laços e estruturas condicionais

## Testes de Funcionalidades Básicas

### Arquivos de Teste

Os testes básicos verificam o funcionamento correto do compilador com código válido em C e C traduzido para português.

#### Arquivos Principais

- **teste1.txt**: Teste básico de operações aritméticas e estruturas condicionais
- **teste2.txt**: Teste de estruturas condicionais simples
- **teste3.txt**: Teste de estruturas de repetição
- **teste4.txt**: Teste de declaração e uso de variáveis
- **teste5.txt**: Teste de funções e chamadas de função

### Execução dos Testes Básicos

Para executar os testes básicos, use o compilador sem a flag de depuração:

```bash
# Na pasta raiz do projeto
make

# Executar testes básicos
./compilador tests/teste1.txt
./compilador tests/teste2.txt
./compilador tests/teste3.txt
./compilador tests/teste4.txt
./compilador tests/teste5.txt
```

Se não houver erros de compilação, o teste foi bem-sucedido. Caso contrário, o compilador exibirá mensagens de erro.

## Testes Léxicos

### Arquivos de Teste

Foram criados testes específicos para verificar as mensagens de erro implementadas. Estes testes estão organizados para demonstrar diferentes tipos de erros léxicos que podem ocorrer durante a compilação.

#### Arquivos Principais

- **teste_erros_lexicos.txt**: Arquivo abrangente que demonstra todos os tipos de erros léxicos possíveis, incluindo:
  - Símbolos especiais não permitidos (@, #, $)
  - Sequências de escape inválidas (\z, \y, \p)
  - Strings e caracteres não fechados
  - Palavras-chave em inglês em vez de português
  - Operadores não implementados

- **teste_lacos.txt**: Foca especificamente em erros relacionados a estruturas de controle de fluxo:
  - Uso de palavras-chave em inglês (while, for, do) em vez de português (enquanto, para, faca)
  - Combinações de palavras-chave em inglês e português
  - Estruturas de controle aninhadas com erros

- **teste_pontuacao.txt**: Concentra-se em erros relacionados a operadores e pontuação:
  - Operadores bit a bit não implementados (|, &, ^, ~)
  - Operadores de deslocamento não implementados (<<, >>)
  - Símbolos de pontuação inválidos (<=>)
  - Combinações inválidas de operadores

### Execução Manual dos Testes Léxicos

Para testar as mensagens de erro léxico usando o compilador completo:

```bash
# Na pasta raiz do projeto
make

# Teste geral de erros léxicos
./compilador tests/testes_lexicos/teste_erros_lexicos.txt -d

# Teste específico para erros em laços
./compilador tests/testes_lexicos/teste_lacos.txt -d

# Teste específico para erros de pontuação
./compilador tests/testes_lexicos/teste_pontuacao.txt -d
```

### Script de Automação de Testes Léxicos

Para facilitar a execução regular dos testes léxicos, foi criado um script de automação que executa todos os testes de uma vez:

```bash
# Na pasta raiz do projeto
./tests/testes_lexicos/executar_testes.sh
```

O script:
1. Compila o projeto automaticamente
2. Executa cada arquivo de teste com o modo de depuração ativado
3. Exibe os resultados formatados para fácil visualização

## Testes Sintáticos

Os testes sintáticos verificam a capacidade do compilador de analisar corretamente a estrutura gramatical do código. Eles são executados automaticamente quando o compilador é usado sem a flag de depuração.

### Execução dos Testes Sintáticos

Para executar os testes sintáticos, use o compilador sem a flag de depuração:

```bash
# Na pasta raiz do projeto
make

# Executar testes sintáticos
./compilador tests/teste6.txt
```

Se houver erros sintáticos no código, o compilador exibirá mensagens de erro indicando o tipo de erro e a linha onde ocorreu.

## Testes de Estruturas de Controle

Os testes de estruturas de controle verificam especificamente o funcionamento correto de laços, condicionais e outras estruturas de controle de fluxo.

### Execução dos Testes de Estruturas de Controle

```bash
# Na pasta raiz do projeto
make

# Executar testes de estruturas de controle
./compilador tests/teste_lacos.txt
```

## Executando Todos os Testes

Para executar todos os tipos de testes disponíveis no projeto, você pode criar um script personalizado ou executar os comandos manualmente:

```bash
#!/bin/bash

# Compilar o projeto
make

# Testes básicos
echo "Executando testes básicos..."
for i in {1..5}; do
    echo "\nTeste $i:"
    ./compilador tests/teste$i.txt
done

# Testes léxicos
echo "\nExecutando testes léxicos..."
./tests/testes_lexicos/executar_testes.sh

# Testes sintáticos
echo "\nExecutando testes sintáticos..."
./compilador tests/teste6.txt

# Testes de estruturas de controle
echo "\nExecutando testes de estruturas de controle..."
./compilador tests/teste_lacos.txt
```

Salve este script como `executar_todos_testes.sh` na pasta raiz do projeto, torne-o executável com `chmod +x executar_todos_testes.sh` e execute-o com `./executar_todos_testes.sh`.

## Mensagens de Erro Implementadas

O analisador léxico foi aprimorado para fornecer mensagens de erro detalhadas e úteis quando encontra tokens inválidos ou mal formados. Estas melhorias ajudam os usuários a identificar e corrigir problemas em seus códigos mais facilmente.

### Tipos de Erros Detectados

1. **Símbolos especiais não permitidos**:
   ```
   Erro léxico (linha X): Símbolo especial '@' não permitido. A linguagem não suporta estes caracteres.
   ```

2. **Sequências de escape inválidas**:
   ```
   Erro léxico (linha X): Sequência de escape inválida '\z'. Sequências válidas: \n, \t, \r, \0.
   ```

3. **Strings não fechadas**:
   ```
   Erro léxico (linha X): String não fechada "texto...". Falta aspas duplas de fechamento.
   ```

4. **Caracteres não fechados**:
   ```
   Erro léxico (linha X): Caractere não fechado 'a...'. Falta aspas simples de fechamento.
   ```

5. **Caracteres não reconhecidos**:
   ```
   Erro léxico (linha X): Caractere não reconhecido '|'. Verifique se há símbolos inválidos no seu código.
   ```

6. **Pontuação não implementada**:
   ```
   Erro léxico (linha X): Pontuação '<=>' não implementada. Considere usar ';' para finalizar comandos.
   ```

## Extensões Futuras

Para o futuro, planeja-se expandir o sistema de testes para incluir:

1. Testes automatizados com verificação de resultados esperados
2. Testes de integração para validar o compilador completo