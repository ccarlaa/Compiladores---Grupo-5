# Uso Básico

Este guia apresenta uma visão geral da estrutura da linguagem compilada, como executar o compilador e como interpretar os resultados. Também detalha os testes disponíveis e as estruturas suportadas.

---

## Estrutura de um Programa

O compilador espera programas escritos em uma linguagem baseada em C. A estrutura mínima de um programa válido é:

```c
int main() {
    // corpo da função principal
}
```

No Portugol traduzido, a saída esperada será:

```portugol
programa
{
    funcao inicio()
    {
        // instruções traduzidas
    }
}
```

---

## Compilando um Programa

Para compilar um programa escrito na linguagem-fonte, utilize o seguinte comando a partir do diretório `compiler-source/`:

```bash
./compilador < caminho/para/seu/arquivo.txt
```

Exemplo:

```bash
./compilador < ../tests/teste1.txt
```

Se preferir, você também pode digitar o código diretamente no terminal usando redirecionamento de entrada:

```bash
./compilador <<EOF
int main() {
    int x = 5;
    return x;
}
EOF
```

---

## Executando Testes

A pasta `bash/` contém scripts organizados por tipo de teste. Eles automatizam a verificação da tradução correta, cobertura da gramática e detecção de erros.

### Testes Léxicos

Verificam o reconhecimento de tokens válidos e tratamento de entradas inválidas. Exemplos:

* `run_lexical_invalid_char_text.sh`: testa caracteres ilegais.
* `run_lexical_unterminated_string_test.sh`: testa strings sem fechamento.

### Testes Sintáticos

Avaliam se a estrutura do código corresponde à gramática definida. Exemplos:

* `run_if_test.sh`: testa estruturas `if/else`.
* `run_while_test.sh`: testa laços `while`.
* `run_nested_while_test.sh`: testa laços aninhados.
* `run_if_while_combination_test.sh`: testa o uso combinado de `if` e `while`.

### Testes Semânticos

Detectam erros como uso de variáveis não declaradas ou conflitos de tipo. Exemplos:

* `run_semantic_undeclared_var_test.sh`: uso de variável não declarada.
* `run_semantic_redeclared_var_test.sh`: declaração duplicada.
* `run_type_check_valid_int_test.sh`: atribuição válida.
* `run_type_check_invalid_string_to_float_test.sh`: atribuição inválida entre tipos incompatíveis.

### Scripts de Automação de Testes

Todos os testes estão automatizados via `Makefile`. Para executá-los:

```bash
make test
```

Isso executa todos os scripts em sequência e mostra o resultado no terminal.

#### Executando com Análise de Cobertura

Você também pode gerar um relatório de cobertura da gramática:

```bash
make coverage
```

O relatório será salvo em `cobertura.txt`, contendo trechos do `stderr` que indicam quais regras da gramática foram ativadas.

---

## Tipos de Dados Suportados

A linguagem-fonte reconhece os seguintes tipos de dados:

- **`int`** — Representa valores inteiros.  
  Traduzido internamente como tipo `inteiro`.

- **`float`** — Representa números de ponto flutuante.  
  Traduzido internamente como tipo `real`.

- **`char`** — Representa um único caractere.  
  Traduzido internamente como tipo `caracter`.

Além desses, outros modificadores e palavras-chave relacionadas a tipos também são reconhecidos:

- **`void`** — Indica ausência de tipo (ex.: funções sem retorno).
- **`const`** — Indica que o valor da variável não pode ser modificado após a inicialização.
- **`unsigned`** — Modificador que restringe o tipo numérico a valores não negativos.

Durante a **análise semântica**, o compilador realiza verificações como:

- Uso de tipos válidos em declarações e expressões.
- Compatibilidade entre tipos em atribuições, operações e chamadas de função.
- Respeito a modificadores como `const` em tentativas de modificação de variáveis.

Essas verificações garantem a coerência semântica do programa antes da geração de código.

---

## Estruturas de Controle

A linguagem implementa diversas estruturas de controle da linguagem C, adaptadas com possíveis traduções para facilitar a leitura. A seguir estão listadas as principais estruturas reconhecidas:

### Condicionais
- **`if`** — Condicional principal  
  Traduzido como `se`
- **`else`** — Alternativa condicional  
  Traduzido como `senao`

### Laços de Repetição
- **`while`** — Laço com teste no início  
  Traduzido como `enquanto`
- **`do ... while`** — Laço com teste no final  
  Traduzido como `faca ... enquanto`
- **`for`** — Laço com inicialização, condição e incremento  
  Traduzido como `para`
- **`break`** — Interrompe o laço atual  
  Traduzido como `pare`
- **`continue`** — Pula para a próxima iteração do laço  
  Traduzido como `continue`

### Funções
- **`return`** — Finaliza uma função e retorna um valor  
  Traduzido como `retorne`

### Entrada e Saída
- **`scanf(...)`** — Leitura de entrada padrão  
  Traduzido como `leia(...)`
- **`printf(...)`** — Impressão na saída padrão  
  Traduzido como `escreva(...)`

Exemplo:

```c
if (x > 10) {
    printf("maior");
} else {
    printf("menor");
}
```

Traduzido para:

```portugol
se (x > 10)
{
    escreva("maior")
}
senao
{
    escreva("menor")
}
```
