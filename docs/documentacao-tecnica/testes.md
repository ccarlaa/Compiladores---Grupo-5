
# Testes do Compilador

Esta seção documenta o sistema de testes automatizados desenvolvido para garantir a robustez, correção e cobertura da gramática do compilador de C para Portugol.

Os testes abrangem aspectos léxicos, sintáticos e semânticos da linguagem-fonte, bem como a qualidade da saída gerada. Todos os testes são executados por meio de **scripts shell localizados na pasta `compiler-source/bash/`**.

---

## Objetivos dos Testes

- Verificar se o compilador aceita e traduz corretamente entradas válidas
- Identificar se o compilador rejeita e trata adequadamente entradas inválidas
- Validar regras de escopo, tipos, estruturas de controle e expressões
- Garantir cobertura das principais produções gramaticais
- Automatizar a execução e facilitar a regressão

---

## Organização dos Testes

Os testes estão organizados por categoria e nomeados com clareza para indicar o foco de cada caso de teste:

- **Léxicos**: testam caracteres inválidos, strings malformadas, comentários, etc.
- **Sintáticos**: verificam combinações de estruturas (if, while, funções aninhadas)
- **Semânticos**: avaliam declaração de variáveis, tipos, escopos, redeclarações
- **Geração de código**: comparam a saída traduzida com a esperada
- **Cobertura de gramática**: extraem trechos da execução com os caminhos percorridos

---

## Como Executar os Testes

Dentro da pasta `compiler-source/`, você pode executar todos os testes com:

```bash
make test
```

Isso percorre todos os scripts da pasta `bash/` e exibe um resumo no terminal.

---

## Análise de Cobertura

Para gerar um relatório de cobertura da gramática:

```bash
make coverage
```

Esse comando executa os mesmos testes, mas captura as produções gramaticais ativadas, salvando o relatório em:

```
build/cobertura.txt
```

---

## Organização dos Scripts

Cada script `.sh`:

- Executa um teste isolado com entrada padrão ou arquivo
- Valida se a saída foi gerada corretamente
- Retorna `0` em caso de sucesso ou `1` em caso de falha
- Pode ser rodado individualmente:

```bash
bash bash/run_if_test.sh
```

---


## Testes Implementados

Esta seção descreve individualmente cada teste automatizado implementado na pasta `compiler-source/bash/`. Os testes foram desenvolvidos para validar funcionalidades específicas do compilador, cobrindo diferentes aspectos da linguagem.

---

### `run_else_test.sh`

**Descrição:** Testa a tradução e o comportamento de comandos `if` com cláusula `else`.

**Entrada**
```bash
int main()
{
    int x = 10;
    if (x > 5)
    {
        printf("maior");
    }
    else
    {
        printf("menor ou igual");
    }
    return 0;
}

```

**Saída esperada**
```bash
programa
{
    funcao inicio()
    {
        inteiro x = 10

        se (x > 5)
        {
            escreva("maior")
        }
        senao
        {
            escreva("menor ou igual")
        }
        retorne 0
    }
}

```

![Teste1](../assets/images/terminal-teste-1.png)

---

### `run_function_call_test.sh`

**Descrição:** Verifica chamadas de funções definidas pelo usuário.

**Entrada**
```bash
int calculate(int a, int b)
{
    int sum = a + b;
    printf("The sum of %d and %d is: %d\n", a, b, sum);
}

int main()
{
    calculate(15, 25);
    calculate(7, 3);
    return 0;
}

```

**Saída esperada**
```bash
programa
{
    funcao inteiro calculate(inteiro a, inteiro b)
    {
        inteiro sum = a + b
        escreva("The sum of ", a, " and ", b, " is: ", sum, "\n")
    }

    funcao inicio()
    {
        calculate(15, 25)
        calculate(7, 3)
        retorne 0
    }

}

```

![Teste1](../assets/images/terminal-teste-1.png)

---

### `run_function_parameter_test.sh`

**Descrição:** Testa funções com parâmetros e passagem de argumentos.

**Entrada**
```bash
int main()
{
    parameterTest(5, 10);
    return 0;
}

int parameterTest(int a, int b)
{
    int x;
    x = a + b;

    printf("\n--- TESTE DOS PARÂMETROS ---\n");
    printf("Valor de a: %d\n", a);
    printf("Valor de b: %d\n", b);
    printf("Soma (a + b): %d\n", x);
    printf("Os parâmetros estão funcionando corretamente!\n");
}
```

**Saída esperada**
```bash
programa
{
    funcao inicio()
    {
        parameterTest(5, 10)
        retorne 0
    }
    
    funcao inteiro parameterTest(inteiro a, inteiro b)
    {
        inteiro x
        x = a + b

        escreva("\n", "--- TESTE DOS PARÂMETROS ---", "\n")
        escreva("Valor de a: ", a, "\n")
        escreva("Valor de b: ", b, "\n")
        escreva("Soma (a + b): ", x, "\n")
        escreva("Os parâmetros estão funcionando corretamente!", "\n")
    }
}
```

![Teste1](../assets/images/terminal-teste-1.png)

---

### `run_if_test.sh`

**Descrição:** Valida a estrutura `if` isoladamente com expressões condicionais simples.

**Entrada**
```bash
int main() {
    float pi = 3.14;
    char letra = 'a';

    if (pi > 3) {
        return 1;
    }
    return 0;
}

```

**Saída esperada**
```bash
programa
{
    funcao inicio()
    {
        real pi = 3.14
        caracter letra = 'a'

        se (pi > 3)
        {
            retorne 1
        }
        retorne 0
    }
}

```

![Teste1](../assets/images/terminal-teste-1.png)

---

### `run_if_while_combination_test.sh`

**Descrição:** Testa o uso combinado de `if` e `while` dentro do mesmo bloco.

**Entrada**
```bash
int main() {
    int count = 0;
    while (count < 5) {
        if (count % 2 == 0) {
            printf("Even: ");
            printf(count);
        } else {
            printf("Odd: ");
            printf(count);
        }
        count = count + 1;
    }
    return 0;
}
```

**Saída esperada**
```bash
programa
{
    funcao inicio()
    {
        inteiro count = 0
        enquanto (count < 5)
        {
            se (count % 2 == 0)
            {
                escreva("Even: ")
                escreva(count)
            }
            senao
            {
                escreva("Odd: ")
                escreva(count)
            }
            count = count + 1
        }
        retorne 0
    }
}
```

![Teste1](../assets/images/terminal-teste-1.png)

---

### `run_lexical_invalid_char_text.sh`

**Descrição:** Verifica se caracteres ilegais são corretamente rejeitados pelo analisador léxico.

**Entrada**
```bash
int main() {
    @
    return 0;
}

```

**Saída esperada**
```bash
Erro lexico na linha 2: Caractere inesperado '@'
```

![Teste1](../assets/images/terminal-teste-1.png)

---

### `run_lexical_unterminated_string_test.sh`

**Descrição:** Testa o tratamento de strings sem aspas de fechamento.

**Entrada**
```bash
int main() {
    printf("string without end);
    return 0;
}

```

**Saída esperada**
```bash
Erro lexico na linha 4: string não terminada
```

![Teste1](../assets/images/terminal-teste-1.png)

---

### `run_logical_operators_test.sh`

**Descrição:** Verifica operadores lógicos (`&&`, `||`, `!`) em expressões booleanas.

**Entrada**
```bash
int main() {
    int x = 10;
    int y = 5;
    int z = 15;

    if (x > y && z > x) {
        printf("Both conditions are true");
    }

    if (x < y || z > y) {
        printf("At least one condition is true");
    }

    if (!(x == y)) {
        printf("x is not equal to y");
    }
    return 0;
}
```

**Saída esperada**
```bash
programa
{
    funcao inicio()
    {
        inteiro x = 10
        inteiro y = 5
        inteiro z = 15

        se (x > y e z > x)
        {
            escreva("Both conditions are true")
        }

        se (x < y ou z > y)
        {
            escreva("At least one condition is true")
        }

        se (nao (x == y))
        {
            escreva("x is not equal to y")
        }
        retorne 0
    }
}
```

![Teste1](../assets/images/terminal-teste-1.png)

---

### `run_multiple_vars_test.sh`

**Descrição:** Testa declarações múltiplas de variáveis do mesmo tipo.

**Entrada**
```bash
int main() {
    int num1 = 10;
    float num2 = 20.5;
    char grade = 'A';
    int sum = num1 + 5;
    float product = num2 * 2.0;

    printf(sum);
    printf(product);
    printf(grade);
    return 0;
}
```

**Saída esperada**
```bash
programa
{
    funcao inicio()
    {
        inteiro num1 = 10
        real num2 = 20.50
        caracter grade = 'A'
        inteiro sum = num1 + 5
        real product = num2 * 2.00
        escreva(sum)
        escreva(product)
        escreva(grade)
        retorne 0
    }
}
```

![Teste1](../assets/images/terminal-teste-1.png)

---

### `run_nested_conditionals_test.sh`

**Descrição:** Avalia `if` aninhados com múltiplos blocos.

**Entrada**
```bash
int main() {
    int a = 10;
    int b = 5;

    if (a > b) {
        printf("a is greater than b");
        if (a > 15) {
            printf(" and a is greater than 15");
        } else {
            printf(" and a is not greater than 15");
        }
    } else if (b > a) {
        printf("b is greater than a");
    } else {
        printf("a and b are equal");
    }
    return 0;
}
```

**Saída esperada**
```bash
programa
{
    funcao inicio()
    {
        inteiro a = 10
        inteiro b = 5

        se (a > b)
        {
            escreva("a is greater than b")
            se (a > 15)
            {
                escreva(" and a is greater than 15")
            }
            senao
            {
                escreva(" and a is not greater than 15")
            }
        }
        senao se (b > a)
        {
            escreva("b is greater than a")
        }
        senao
        {
            escreva("a and b are equal")
        }
        retorne 0
    }
}
```

![Teste1](../assets/images/terminal-teste-1.png)

---

### `run_nested_while_test.sh`

**Descrição:** Verifica laços `while` dentro de outros laços `while`.

**Entrada**
```bash
int main() {
    int i = 0;
    while (i < 3) {
        int j = 0;
        while (j < 2) {
            printf(i);
            printf(j);
            j = j + 1;
        }
        i = i + 1;
    }
    return 0;
}
```

**Saída esperada**
```bash
programa
{
    funcao inicio()
    {
        inteiro i = 0
        enquanto (i < 3)
        {
            inteiro j = 0
            enquanto (j < 2)
            {
                escreva(i)
                escreva(j)
                j = j + 1
            }
            i = i + 1
        }
        retorne 0
    }
}
```

![Teste1](../assets/images/terminal-teste-1.png)

---

### `run_printf_test.sh`

**Descrição:** Testa o uso do comando `printf` com argumentos simples e múltiplos.

**Entrada**
```bash
int main() {
    int x = 10;
    x = x + 3;
    printf(x);
}

```

**Saída esperada**
```bash
programa
{
    funcao inicio()
    {
        inteiro x = 10

        x = x + 3
        escreva(x)
    }
}
```

![Teste1](../assets/images/terminal-teste-1.png)

---

### `run_return_test.sh`

**Descrição:** Verifica instruções `return` e seu impacto na tradução.

**Entrada**
```bash
int obterNumeroCurto()
{
    int x = 10;
    int y = 20;
    int z = x + y;
    return z;
}

int main()
{
    int meuNumero = obterNumeroCurto();

    printf(meuNumero);

    return 0;
}
```

**Saída esperada**
```bash
programa 
{
    funcao inteiro obterNumeroCurto()
    {
        inteiro x = 10
        inteiro y = 20
        inteiro z = x + y
        retorne z
    }

    funcao inicio()
    {
        inteiro meuNumero = obterNumeroCurto()
        escreva(meuNumero)

        retorne 0
}
}
```

![Teste1](../assets/images/terminal-teste-1.png)

---

### `run_scanf_test.sh`

**Descrição:** Testa o reconhecimento e tradução de comandos `scanf`.

**Entrada**
```bash
int main() {
    int idade;
    scanf("%d", &idade);
    if (idade >= 18) {
        printf("maior de idade");
    }
    return 0;
}

```

**Saída esperada**
```bash
programa
{
    funcao inicio()
    {
        inteiro idade

        leia(idade)
        se (idade >= 18)
        {
            escreva("maior de idade")
        }
        retorne 0
    }
}

```

![Teste1](../assets/images/terminal-teste-1.png)

---

### `run_semantic_redeclared_var_test.sh`

**Descrição:** Verifica erro ao redeclarar uma variável no mesmo escopo.

**Entrada**
```bash
int main() {
    int x;
    int x;
    return 0;
}
```

**Saída esperada**
```bash
Erro semântico na linha 3: Variável 'x' já declarada.
```

![Teste1](../assets/images/terminal-teste-1.png)

---

### `run_semantic_undeclared_var_test.sh`

**Descrição:** Testa o uso de variáveis não declaradas (erro semântico).

**Entrada**
```bash
int main() {
    x = 5;
    return 0;
}

```

**Saída esperada**
```bash
Erro semântico na linha 2: Variável 'x' não declarada.
```

![Teste1](../assets/images/terminal-teste-1.png)

---

### `run_type_check_invalid_char_to_int_test.sh`

**Descrição:** Testa atribuição incorreta de `char` em variável `int`.

**Entrada**
```bash
int main() {
    int x;
    x = 'a';
    return 0;
}

```

**Saída esperada**
```bash
Erro de tipo na linha 3: não é possível atribuir caracter a variável do tipo inteiro.

```

![Teste1](../assets/images/terminal-teste-1.png)

---

### `run_type_check_invalid_float_to_int_test.sh`

**Descrição:** Testa conversão implícita incorreta de `float` para `int`.

**Entrada**
```bash
int main() {
    int x;
    x = 3.14;
    return 0;
}

```

**Saída esperada**
```bash
Erro de tipo na linha 3: não é possível atribuir real a variável do tipo inteiro.

```

![Teste1](../assets/images/terminal-teste-1.png)

---

### `run_type_check_invalid_string_to_float_test.sh`

**Descrição:** Verifica erro ao atribuir `string` a `float`.

**Entrada**
```bash
int main() {
    float y;
    y = "texto";
    return 0;
}

```

**Saída esperada**
```bash
Erro de tipo na linha 3: não é possível atribuir string a variável do tipo real.

```

![Teste1](../assets/images/terminal-teste-1.png)

---

### `run_type_check_valid_int_test.sh`

**Descrição:** Confirma atribuição correta entre variáveis do tipo `int`.

**Entrada**
```bash
int main() {
    int x;
    x = 10;
    return 0;
}

```

**Saída esperada**
```bash
[Compilação sem erros]
```

![Teste1](../assets/images/terminal-teste-1.png)

---

### `run_while_test.sh`

**Descrição:** Testa laços simples `while` com condição e corpo válido.

**Entrada**
```bash
int main() {
    int i = 0;
    while (i < 5) {
        printf(i);
        i = i + 1;
    }
    return 0;
}

```

**Saída esperada**
```bash
programa
{
    funcao inicio()
    {
        inteiro i = 0

        enquanto (i < 5)
        {
            escreva(i)
            i = i + 1
        }
        retorne 0
    }
}

```

![Teste1](../assets/images/terminal-teste-1.png)
