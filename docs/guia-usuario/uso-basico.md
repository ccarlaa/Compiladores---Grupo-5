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

O compilador possui um modo de depuração que exibe informações detalhadas sobre os tokens reconhecidos durante a análise léxica. Para ativar o modo de depuração, use a opção `-d`:

```bash
./compilador.exe -d caminho/para/seu/arquivo.txt
```

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
