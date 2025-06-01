# Análise Léxica

Esta seção detalha a implementação do analisador léxico (scanner) do Compilador C em Português.

## Visão Geral

O analisador léxico é implementado usando o Flex (gerador de analisadores léxicos) e é responsável por converter o código-fonte em uma sequência de tokens. Cada token representa uma unidade léxica do programa, como palavras-chave, identificadores, números, operadores e delimitadores.

## Implementação

O arquivo principal do analisador léxico é `src/lexer/lexer.l`, que contém as regras para reconhecer os diferentes tokens da linguagem.

### Estrutura do Arquivo lexer.l

O arquivo `lexer.l` é dividido em três seções:

1. **Definições**: Contém inclusões de arquivos, definições de macros e código C que será copiado para o arquivo gerado.
2. **Regras**: Contém as regras para reconhecer os tokens, especificadas como expressões regulares seguidas por ações em C.
3. **Código do Usuário**: Contém funções auxiliares e código C adicional.

### Tokens Reconhecidos

O analisador léxico reconhece os seguintes tipos de tokens:

#### Palavras-chave

As palavras-chave da linguagem C são traduzidas para português:

```c
"inteiro"       { return TIPO_INTEIRO; }
"real"          { return TIPO_REAL; }
"duplo"         { return TIPO_DUPLO; }
"caractere"     { return TIPO_CARACTERE; }
"vazio"         { return TIPO_VAZIO; }
"longo"         { return TIPO_LONGO; }
"curto"         { return TIPO_CURTO; }
"sem_sinal"     { return TIPO_SEM_SINAL; }
"com_sinal"     { return TIPO_COM_SINAL; }
```

#### Estruturas de Controle

As estruturas de controle também são traduzidas:

```c
"se"            { return SE; }
"senao"         { return SENAO; }
"enquanto"      { return ENQUANTO; }
"para"          { return PARA; }
"faca"          { return FACA; }
"retorne"       { return RETORNE; }
"continue"      { return CONTINUE; }
"quebre"        { return QUEBRE; }
```

#### Outras Palavras-chave

Outras palavras-chave importantes:

```c
"estrutura"     { return ESTRUTURA; }
"uniao"         { return UNIAO; }
"estatico"      { return ESTATICO; }
"constante"     { return CONSTANTE; }
"principal"     { return PRINCIPAL; }
```

#### Delimitadores e Operadores

O analisador reconhece vários delimitadores e operadores:

```c
"{"             { return ABRE_CHAVE; }
"}"             { return FECHA_CHAVE; }
"("             { return ABRE_PAREN; }
")"             { return FECHA_PAREN; }
"["             { return ABRE_COLCHETE; }
"]"             { return FECHA_COLCHETE; }
";"             { return PONTO_E_VIRGULA; }
","             { return VIRGULA; }
"."             { return PONTO; }
```

#### Operadores Aritméticos e Lógicos

```c
"+"             { return MAIS; }
"-"             { return MENOS; }
"*"             { return VEZES; }
"/"             { return DIVIDIDO; }
"%"             { return MODULO; }
"=="            { return IGUAL; }
"!="            { return DIFERENTE; }
">"             { return MAIOR; }
"<"             { return MENOR; }
">="            { return MAIOR_IGUAL; }
"<="            { return MENOR_IGUAL; }
"&&"            { return E_LOGICO; }
"||"            { return OU_LOGICO; }
"!"             { return NAO_LOGICO; }
```

#### Identificadores e Literais

```c
[a-zA-Z_][a-zA-Z0-9_]*  { return IDENTIFICADOR; }
[0-9]+                  { return NUMERO; }
[0-9]+\.[0-9]+          { return NUMERO_REAL; }
\"[^\"]*\"              { return LITERAL_STRING; }
\'[^\']*\'              { return LITERAL_CHAR; }
```

### Tratamento de Comentários

O analisador léxico ignora comentários de linha e de bloco:

```c
"//".*          { /* Ignora comentários de linha */ }
"/*"([^*]|"*"[^/])*"*/" { /* Ignora comentários de bloco */ }
```

### Tratamento de Espaços em Branco

Espaços em branco, tabulações e quebras de linha são ignorados:

```c
[ \t\n]+        { /* Ignora espaços em branco */ }
```

## Modo de Depuração

O compilador possui um modo de depuração que exibe informações detalhadas sobre os tokens reconhecidos. Isso é útil para identificar problemas no analisador léxico.

Para ativar o modo de depuração, use a opção `-d` ao executar o compilador:

```bash
./compilador.exe -d caminho/para/seu/arquivo.txt
```

## Problemas Comuns e Soluções

### Caracteres Acentuados em Comentários

Para evitar problemas com caracteres acentuados em comentários, implementamos uma regra específica para ignorar completamente os comentários de linha:

```c
"//".*          { /* Ignora comentários de linha */ }
```

### Conflito no Token "principal"

Resolvemos um conflito nas regras do analisador léxico relacionado ao token "principal" mantendo apenas a regra específica:

```c
"principal"     { return PRINCIPAL; }
```

## Tratamento de Erros Léxicos

O analisador léxico foi aprimorado para fornecer mensagens de erro detalhadas e úteis quando encontra tokens inválidos ou mal formados. Estas melhorias ajudam os usuários a identificar e corrigir problemas em seus códigos mais facilmente.

### Mensagens de Erro Implementadas

#### No Analisador Léxico Principal (`lexer.l`)

- **Caracteres não reconhecidos**: Mensagens específicas para diferentes tipos de caracteres inválidos
  ```c
  if (yytext[0] == '@' || yytext[0] == '#' || yytext[0] == '$') {
      fprintf(stderr, "Erro léxico (linha %d): Símbolo especial '%s' não permitido. A linguagem não suporta estes caracteres.\n", linha_atual, yytext);
  } else {
      fprintf(stderr, "Erro léxico (linha %d): Caractere inesperado '%s'.\n", linha_atual, yytext);
  }
  ```

- **Sequências de escape inválidas**: Detecção de sequências de escape não suportadas em strings e caracteres
  ```c
  fprintf(stderr, "Erro léxico (linha %d): Sequência de escape inválida '%s'. Sequências válidas: \\n, \\t, \\r, \\0.\n", linha_atual, yytext);
  ```

- **Strings e caracteres não fechados**: Detecção de aspas não fechadas
  ```c
  fprintf(stderr, "Erro léxico (linha %d): String não fechada '%s'. Falta aspas duplas de fechamento.\n", linha_atual, yytext);
  ```

#### No Analisador de Laços (`lexico_lacos.l`)

- **Palavras-chave em inglês**: Detecção de uso de palavras-chave em inglês com sugestões para suas equivalentes em português
  ```c
  fprintf(stderr, "Erro léxico na linha %d: Palavra-chave em inglês 'while' detectada. Use 'enquanto' em vez de 'while'.\n", linha_atual);
  ```

#### No Analisador de Pontuação (`lexico_pontuacao.l`)

- **Símbolos de pontuação inválidos**: Mensagens específicas para símbolos de pontuação não suportados
  ```c
  fprintf(stderr, "Erro léxico (linha %d): Símbolo de pontuação inválido '%s'. Este símbolo não é suportado na linguagem.\n", linha_atual, yytext);
  ```

- **Pontuação não implementada**: Sugestões para pontuações alternativas
  ```c
  fprintf(stderr, "Erro léxico (linha %d): Pontuação '%s' não implementada. Considere usar ';' para finalizar comandos.\n", linha_atual, yytext);
  ```

### Testes de Erros Léxicos

Foram criados testes específicos para verificar as mensagens de erro implementadas. Estes testes estão organizados para demonstrar diferentes tipos de erros léxicos que podem ocorrer durante a compilação.

#### Arquivos de Teste

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

#### Como Executar os Testes

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

A flag `-d` ativa o modo de depuração, que exibirá as mensagens de erro léxico detalhadas. O compilador irá mostrar os erros léxicos encontrados durante a análise do código, permitindo verificar se as mensagens de erro estão sendo exibidas corretamente.

## Extensões Futuras

Possíveis melhorias para o analisador léxico incluem:

1. Suporte para mais tipos de dados
2. Reconhecimento de mais operadores
