# Exemplos

Esta página apresenta exemplos representativos de programas válidos aceitos pelo compilador, com suas respectivas traduções geradas em Portugol. Os exemplos ajudam a compreender a sintaxe da linguagem-fonte e a saída esperada.

---

## Exemplo Básico

**Entrada (C):**

```c
int main() {
    int x = 5;
    return x;
}
```

**Saída (Portugol):**

```portugol
programa
{
    funcao inicio()
    {
        inteiro x = 5
        retorne x
    }

}
```

---

## Estruturas Condicionais

**Entrada (C):**

```c
int main() {
    int nota = 7;

    if (nota >= 6) {
        printf("Aprovado");
    } else {
        printf("Reprovado");
    }

    return 0;
}
```

**Saída (Portugol):**

```portugol
programa
{
    funcao inicio()
    {
        inteiro nota = 7
        se (nota >= 6)
        {
            escreva("Aprovado")
        }
        senao
        {
            escreva("Reprovado")
        }
        retorne 0
    }

}

```

---

## Loops

**Entrada (C):**

```c
int main() {
    int i = 0;

    while (i < 3) {
        printf("%d", i);
        i = i + 1;
    }

    return 0;
}
```

**Saída (Portugol):**

```portugol
programa
{
    funcao inicio()
    {
        inteiro i = 0
        enquanto (i < 3)
        {
            escreva(i)
            i = i + 1
        }
        retorne 0
    }

}

```

---

## Funções

**Entrada (C):**

```c
int quadrado(int x) {
    return x * x;
}

int main() {
    int resultado = quadrado(4);
    printf("%d", resultado);
    return 0;
}
```

**Saída (Portugol):**

```portugol
programa
{
    funcao inteiro quadrado(inteiro x)
    {
        retorne x * x
    }

    funcao inicio()
    {
        inteiro resultado =         quadrado(4)

        escreva(resultado)
        retorne 0
    }

}

```

---

## Exemplo Completo

**Entrada (C):**

```c
int main() {
    float pi = 3.14;
    char letra = 'a';

    if (pi > 3) {
        return 1;
    }
    return 0;
}
```

**Saída (Portugol):**

```portugol
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

---

## Como Executar os Exemplos

Você pode executar os exemplos acima diretamente no terminal utilizando o compilador:

### Usando entrada direta via terminal

```bash
./compilador <<EOF
int main() {
    int x = 5;
    return x;
}
EOF
```

A saída será exibida em Portugol no terminal.

### Usando echo para exemplos simples

```bash
echo "int main() { return 0; }" | ./compilador
```

### Usando um arquivo com código-fonte

1. Crie um arquivo `exemplo.c` com o conteúdo desejado.
2. Execute o compilador:

```bash
./compilador < exemplo.c
```

Ou, para salvar a saída em um arquivo `.por`:

```bash
./compilador < exemplo.c > exemplo.por
```

O arquivo gerado pode ser aberto diretamente no Portugol Studio.
