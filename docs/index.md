# Compilador de C para Portugol

Bem-vindo à documentação do projeto **Compilador de C para Portugol**, desenvolvido na disciplina *Compiladores (2025/1)* da Universidade de Brasília (UnB), sob orientação do professor Sergio Freitas.

Este compilador é capaz de processar programas escritos em uma linguagem simplificada de C e traduzí-los para Portugol, uma linguagem algorítmica didática, facilitando o entendimento de fluxos de controle e estruturas de programação.

---

## Sobre o Projeto

Este projeto foi construído com base nos conceitos fundamentais de construção de compiladores, abordando as principais fases: análise léxica, sintática e semântica, geração de árvore sintática abstrata (AST), e tradução para a linguagem-alvo.

A linguagem-fonte aceita um subconjunto de C, e a saída gerada corresponde a um equivalente funcional em Portugol. O projeto inclui também uma suíte de testes automatizados para validar a robustez do compilador.

---

## Características Principais

- Reconhecimento de estruturas básicas da linguagem C:
  - Declaração e uso de variáveis (`int`, `float`, `char`)
  - Expressões aritméticas e relacionais
  - Condicionais (`if`, `else`)
  - Laços de repetição (`while`)
  - Funções definidas pelo usuário
  - Entrada e saída com `scanf` e `printf`

- Detecção de erros léxicos, sintáticos e semânticos
- Geração de árvore sintática abstrata (AST)
- Tradução para Portugol
- Testes automatizados via shell scripts
- Modularidade com uso de Flex, Bison e C

---

## Como Usar Esta Documentação

Esta documentação está organizada em seções para facilitar a consulta conforme o objetivo do usuário:

- **Guia do Usuário:** explica como instalar, compilar, executar e interpretar a saída do compilador.
- **Documentação Técnica:** detalha o funcionamento interno, desde a análise léxica até a geração de código.
- **Testes:** lista os testes implementados e explica como executá-los.
- **Sprints:** apresenta o histórico de desenvolvimento da equipe com base na metodologia Scrum.
- **Atas de Reunião:** registra decisões e alinhamentos feitos durante o semestre.

---

## Exemplos Rápidos

### Compilando e Executando o Compilador

Para compilar o compilador, acesse o diretório `compiler-source/` e execute:

```bash
make
```

Em seguida, utilize o executável gerado para processar arquivos `.c` e gerar sua tradução para Portugol:

```bash
./compilador < entrada.c > saida.por
```

O conteúdo de `saida.por` poderá ser aberto no **Portugol Studio** para execução e visualização do programa traduzido.

---

### Exemplo de Entrada e Saída

Considere o seguinte arquivo `entrada.c`:

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

Ao executar:

```bash
./compilador < entrada.c > saida.por
```

A saída `saida.por` será:

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

Esse código pode ser **copiado e colado diretamente no Portugol Studio** para ser executado e testado.

---

### Dica: Visualizar diretamente no terminal

Se preferir visualizar a saída traduzida diretamente no terminal, sem redirecionar para arquivo, basta executar:

```bash
./compilador < entrada.c
```

O código traduzido será exibido no console.

---

### Executando Testes Automatizados

O projeto conta com uma bateria de testes automatizados organizados em scripts localizados no diretório `compiler-source/bash/`.

Esses testes cobrem diferentes aspectos do compilador, como:

- Reconhecimento de estruturas da linguagem
- Verificação semântica de variáveis e tipos
- Testes negativos com entradas inválidas
- Tradução correta de códigos para Portugol

---

#### Rodando todos os testes

Você pode executar todos os testes de uma só vez com o comando:

```bash
make test
```

O resultado de cada script será exibido no terminal, com uma mensagem final indicando o sucesso ou falha geral da bateria.

---

#### Análise de Cobertura da Gramática

Para obter um relatório da cobertura das regras da gramática (útil para verificar quais construções foram testadas), execute:

```bash
make coverage
```

Esse comando:

* Executa todos os scripts de teste
* Captura saídas específicas relacionadas à cobertura
* Salva o resultado no arquivo `cobertura.txt`, na raiz do projeto

Você pode visualizar o conteúdo com:

```bash
cat cobertura.txt
```

Esse relatório é especialmente útil durante o desenvolvimento da gramática no Bison, ajudando a identificar regras não exercitadas pelos testes.

---

#### Limpando arquivos gerados

Para remover arquivos de build e compilações anteriores:

```bash
make clean
```

Isso ajuda a manter o ambiente de desenvolvimento organizado e evitar conflitos de versões antigas.

---

## Membros do Grupo

<div align="center">
    <table>
    <tr>
        <th>Nome</th>
        <th>GitHub</th>
    </tr>
    <tr>
        <td>Carla A. C. Ribeiro</td>
        <td><a href="https://github.com/ccarlaa">@ccarlaa</a></td>
    </tr>
    <tr>
        <td>Clara Marcelino Ribeiro de Sousa </td>
        <td><a href="https://github.com/clara-ribeiro">@clara-ribeiro</a></td>
    </tr>
    <tr>
        <td>Kallyne Macedo Passos</td>
        <td><a href="https://github.com/kalipassos">@kalipassos</a></td>
    </tr>
    <tr>
        <td>Kauan de Torres Eiras</td>
       <td><a href="https://github.com/kauaneiras">@kauaneiras</a></td>
    </tr>
    <tr>
        <td>Leonardo Sobrinho de Aguiar</td>
        <td><a href="github.com/Leonardo0o0">@leonardo0o0</a></td>
    </tr>
        <tr>
        <td>João Paulo Barros de Cristo</td>
        <td><a href="github.com/joaopb1-xps">@joaopb1-xps</a></td>
    </tr>
    </table>
</div>
