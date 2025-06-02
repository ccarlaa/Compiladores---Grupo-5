# Uso Básico

Este guia explica como usar o Compilador C em Português para compilar e executar programas escritos em C com palavras-chave em português.

## Estrutura de um Programa

Um programa básico em C traduzido para português tem a seguinte estrutura:

```c
// Exemplo de programa simples
inteiro principal() {
    // Código aqui
    retorne 0;
}
```

## Compilando um Programa

Para compilar um programa, use o seguinte comando:

```bash
./compilador.exe caminho/para/seu/arquivo.txt
```

Por exemplo:

```bash
./compilador.exe tests/teste1.txt
```

## Modo de Depuração

O compilador possui um modo de depuração que exibe informações detalhadas sobre os tokens reconhecidos durante a análise léxica. Este modo é especialmente útil para identificar erros léxicos no código.

### Ativando o Modo de Depuração

Para ativar o modo de depuração, use a opção `-d` ou `--debug`:

```bash
./compilador.exe -d caminho/para/seu/arquivo.txt
```

Ou

```bash
./compilador.exe --debug caminho/para/seu/arquivo.txt
```

### O que o Modo de Depuração Mostra

Quando ativado, o modo de depuração exibe:

1. Uma mensagem indicando que o modo de depuração foi ativado
2. Cada token reconhecido pelo analisador léxico, incluindo:
   - Código do token (número identificador)
   - Tipo do token (ex: IDENTIFICADOR, NUMERO, etc.)
   - Lexema (o texto original no código fonte)
3. Mensagens de erro léxico detalhadas, incluindo:
   - Número da linha onde o erro ocorreu
   - Descrição do erro
   - Sugestões para correção quando aplicável

Exemplo de saída:

```
Modo de depuração ativado - mostrando tokens e erros léxicos
Token: 318 (IDENTIFICADOR) - Lexema: 'inteiro'
Token: 286 (PRINCIPAL) - Lexema: 'principal'
Token: 308 (ABRE_PAREN) - Lexema: '('
Token: 309 (FECHA_PAREN) - Lexema: ')'
Token: 310 (ABRE_CHAVE) - Lexema: '{'
Erro léxico (linha 6): Símbolo especial '@' não permitido. A linguagem não suporta estes caracteres.
```

## Executando Testes

O compilador inclui um conjunto de testes para validar seu funcionamento, especialmente para verificar o tratamento de erros léxicos.

### Testes Léxicos

Para executar os testes léxicos manualmente:

```bash
# Teste geral de erros léxicos
./compilador.exe tests/testes_lexicos/teste_erros_lexicos.txt -d

# Teste específico para erros em laços
./compilador.exe tests/testes_lexicos/teste_lacos.txt -d

# Teste específico para erros de pontuação
./compilador.exe tests/testes_lexicos/teste_pontuacao.txt -d
```

### Scripts de Automação de Testes

#### Executando Apenas Testes Léxicos

Para executar todos os testes léxicos de uma vez, use o script de automação específico:

```bash
./tests/testes_lexicos/executar_testes.sh
```

Este script:
1. Compila o projeto automaticamente
2. Executa cada arquivo de teste léxico com o modo de depuração ativado
3. Exibe os resultados formatados para fácil visualização

#### Executando Todos os Tipos de Testes

Para executar todos os tipos de testes disponíveis no projeto (básicos, léxicos, sintáticos e de estruturas de controle), use o script de automação completo:

```bash
./executar_todos_testes.sh
```

Este script:
1. Compila o projeto automaticamente
2. Executa os testes básicos (teste1.txt até teste5.txt)
3. Executa os testes léxicos com o modo de depuração ativado
4. Executa os testes sintáticos
5. Executa os testes de estruturas de controle
6. Exibe os resultados formatados com cores para melhor visualização

## Tipos de Dados Suportados

O compilador suporta os seguintes tipos de dados em português:

| Português | C Original |
|-----------|------------|
| inteiro   | int        |
| real      | float      |
| duplo     | double     |
| caractere | char       |
| vazio     | void       |
| longo     | long       |
| curto     | short      |

## Estruturas de Controle

As estruturas de controle em português seguem a mesma lógica das estruturas em C:

### Condicional (if/else)

```c
se (condicao) {
    // código se verdadeiro
} senao {
    // código se falso
}
```

### Loop While

```c
enquanto (condicao) {
    // código a ser repetido
}
```

### Loop For

```c
para (inteiro i = 0; i < 10; i++) {
    // código a ser repetido
}
```

## Definindo Estruturas

Você pode definir estruturas usando a palavra-chave `estrutura`:

```c
estrutura Pessoa {
    caractere nome[50];
    inteiro idade;
    real altura;
};
```

## Declarando Funções

As funções são declaradas de forma semelhante ao C padrão, mas com palavras-chave em português:

```c
inteiro soma(inteiro a, inteiro b) {
    retorne a + b;
}
```
