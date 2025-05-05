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

## Extensões Futuras

Possíveis melhorias para o analisador léxico incluem:

1. Suporte para mais tipos de dados
2. Reconhecimento de mais operadores
3. Melhor tratamento de erros léxicos
4. Suporte para caracteres acentuados em identificadores
