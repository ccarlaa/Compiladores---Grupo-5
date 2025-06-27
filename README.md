# Compilador - Grupo 5

Este repositório contém o projeto desenvolvido na disciplina **Compiladores**, ministrada pelo professor **Sergio Freitas** na Universidade de Brasília (UnB). O trabalho foi desenvolvido com o objetivo de aplicar na prática os conhecimentos sobre análise léxica, sintática e semântica, utilizando as ferramentas Flex, Bison.

## 1. Apresentação do Projeto

O projeto consiste na implementação de um **compilador funcional** de C para portugol. O compilador é capaz de realizar:

- Análise léxica (identificação de tokens e tratamento de erros)
- Análise sintática (verificação de estruturas gramaticais)
- Análise semântica (verificação de declaração de variáveis e tipos)
- Geração de representação intermediária via árvore sintática abstrata (AST)
- Execução de testes automatizados com foco em validação de funcionalidades e erros

## 2. Definição da Linguagem-Fonte

O compilador desenvolvido neste projeto tem como objetivo traduzir programas escritos na linguagem **C** para uma representação em **Portugol**. A linguagem-fonte aceita uma **subconjunto simplificado da linguagem C**, com suporte às seguintes construções:

- Declaração de variáveis
- Atribuições e expressões aritméticas
- Estruturas condicionais
- Laços de repetição
- Definição e chamada de funções com parâmetros e retorno
- Comandos de entrada e saída

A linguagem-alvo, Portugol, é utilizada como uma representação intermediária legível, com sintaxe mais próxima da linguagem natural, facilitando a compreensão dos programas traduzidos.

A especificação da linguagem-fonte, incluindo tokens e regras gramaticais, está implementada nos arquivos `lexer.l` (analisador léxico) e `parser.y` (analisador sintático), localizados no diretório `compiler-source/`.

## 3. Estrutura do Repositório

```plaintext
.
├── compiler-source/         # Código-fonte do compilador
│   ├── lexer.l              # Regras léxicas (Flex)
│   ├── parser.y             # Gramática e regras sintáticas (Bison)
│   ├── ast.[c|h]            # Estrutura da árvore sintática abstrata
│   ├── tabela.[c|h]         # Implementação da tabela de símbolos
│   ├── main.c               # Ponto de entrada do compilador
│   ├── Makefile             # Automação da compilação
│   └── bash/                # Scripts de testes automatizados
├── docs/                    # Documentação em Markdown (MkDocs)
├── .vscode/                 # Configurações locais do VS Code
├── README.md                # Este arquivo
└── .gitignore               # Arquivos ignorados pelo Git
```

## 4. Acesso ao Projeto

Para clonar este repositório:

```bash
git clone https://github.com/SEU-USUARIO/compiladores-grupo5.git
cd compiladores-grupo5/compiler-source
```

> Substitua `SEU-USUARIO` pela sua conta do GitHub ou do grupo.

## 5. Como Rodar o Projeto

A partir do diretório `compiler-source/`, siga os passos abaixo:

### Compilar o Compilador

```bash
make clean
make
```

Isso irá gerar o executável `compilador`.

### Executar o Compilador com Entrada Padrão

```bash
./compilador < entrada.txt
```

Para encerrar a entrada manual via terminal, pressione `Ctrl+D` (Linux/macOS) ou `Ctrl+Z` (Windows).

### Rodar Testes Automatizados

```bash
cd bash
bash run_if_test.sh
```

Há vários scripts disponíveis para testar diferentes estruturas da linguagem.

## 6. Pré-Requisitos

Este projeto foi desenvolvido e testado com as seguintes versões:

* **Flex**: 2.6.4
* **Bison**: 3.8.2
* **GCC (GNU Compiler Collection)**: Recomendado 9.4 ou superior
* **Make**: utilitário para automação da compilação

Para instalar as dependências em sistemas baseados em Debian (como Ubuntu):

```bash
sudo apt update
sudo apt install flex bison build-essential -y
```

## 👥 Membros do Grupo

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
