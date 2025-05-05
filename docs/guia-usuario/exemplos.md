# Exemplos

Esta seção contém exemplos de programas escritos em C com palavras-chave em português, demonstrando as diferentes funcionalidades do compilador.

## Exemplo Básico

Um programa simples que imprime "Olá, Mundo!":

```c
inteiro principal() {
    imprimir("Olá, Mundo!");
    retorne 0;
}
```

## Estruturas Condicionais

Exemplo de uso de estruturas condicionais:

```c
inteiro principal() {
    inteiro a = 10;
    
    se (a > 5) {
        imprimir("a é maior que 5");
    } senao se (a == 5) {
        imprimir("a é igual a 5");
    } senao {
        imprimir("a é menor que 5");
    }
    
    retorne 0;
}
```

## Loops

Exemplo de uso de loops:

```c
inteiro principal() {
    // Loop enquanto
    inteiro i = 0;
    enquanto (i < 5) {
        imprimir(i);
        i++;
    }
    
    // Loop para
    para (inteiro j = 0; j < 5; j++) {
        imprimir(j);
    }
    
    // Loop faca-enquanto
    inteiro k = 0;
    faca {
        imprimir(k);
        k++;
    } enquanto (k < 5);
    
    retorne 0;
}
```

## Estruturas e Campos

Exemplo de definição e uso de estruturas:

```c
estrutura Pessoa {
    caractere nome[50];
    inteiro idade;
    real altura;
    duplo peso;
};

inteiro principal() {
    estrutura Pessoa p;
    
    // Atribuição de valores aos campos
    atribuir(p.nome, "João");
    p.idade = 30;
    p.altura = 1.75;
    p.peso = 70.5;
    
    // Acesso aos campos
    imprimir(p.nome);
    imprimir(p.idade);
    imprimir(p.altura);
    imprimir(p.peso);
    
    retorne 0;
}
```

## Funções

Exemplo de definição e uso de funções:

```c
// Função que calcula o fatorial de um número
inteiro fatorial(inteiro n) {
    se (n <= 1) {
        retorne 1;
    }
    retorne n * fatorial(n - 1);
}

// Função que verifica se um número é par
inteiro eh_par(inteiro n) {
    inteiro resto = n;
    resto = resto - ((resto / 2) * 2);
    retorne (resto == 0);
}

inteiro principal() {
    inteiro num = 5;
    
    imprimir("Fatorial de 5:");
    imprimir(fatorial(num));
    
    imprimir("5 é par?");
    se (eh_par(num)) {
        imprimir("Sim");
    } senao {
        imprimir("Não");
    }
    
    retorne 0;
}
```

## Exemplo Completo

Este exemplo demonstra várias funcionalidades do compilador, incluindo estruturas, funções, loops e condicionais:

```c
// Definição de constantes
constante inteiro MAX = 100;
estatico real PI = 3.14159;

// Definição de estrutura
estrutura Pessoa {
    caractere nome[50];
    inteiro idade;
    real altura;
    duplo peso;
};

// Função para calcular a área de um círculo
duplo area_circulo(duplo raio) {
    retorne PI * raio * raio;
}

// Função para verificar se um número é par
inteiro eh_par(inteiro n) {
    inteiro resto = n;
    resto = resto - ((resto / 2) * 2);
    retorne (resto == 0);
}

// Função principal
inteiro principal() {
    // Declaração de variáveis
    inteiro i;
    duplo raio = 5.0;
    estrutura Pessoa pessoas[3];
    
    // Inicialização da estrutura
    atribuir(pessoas[0].nome, "João");
    pessoas[0].idade = 30;
    pessoas[0].altura = 1.75;
    pessoas[0].peso = 70.5;
    
    atribuir(pessoas[1].nome, "Maria");
    pessoas[1].idade = 25;
    pessoas[1].altura = 1.65;
    pessoas[1].peso = 60.0;
    
    atribuir(pessoas[2].nome, "Pedro");
    pessoas[2].idade = 40;
    pessoas[2].altura = 1.80;
    pessoas[2].peso = 80.0;
    
    // Loop para processar pessoas
    para (i = 0; i < 3; i++) {
        imprimir(pessoas[i].nome);
        
        se (eh_par(pessoas[i].idade)) {
            imprimir("Idade par");
        } senao {
            imprimir("Idade ímpar");
        }
    }
    
    // Cálculo da área do círculo
    duplo area = area_circulo(raio);
    imprimir("Área do círculo:");
    imprimir(area);
    
    retorne 0;
}
```

Estes exemplos demonstram as principais funcionalidades do compilador C em português e podem ser usados como referência para escrever seus próprios programas.
