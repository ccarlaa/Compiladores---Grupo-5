# Compiladores - Grupo 5

## 📝 Sobre

**C em Português: Derrubando barreiras linguísticas na programação**

Este projeto implementa um compilador que permite escrever código na linguagem C utilizando sintaxe e palavras-chave em português. Nosso objetivo é democratizar o acesso à programação, permitindo que estudantes brasileiros sem fluência em inglês possam aprender conceitos fundamentais de programação sem a barreira linguística adicional.

O compilador é desenvolvido utilizando as ferramentas clássicas de construção de compiladores: **Flex** para análise léxica e **Bison** para análise sintática, com implementação em C. O sistema traduz código-fonte escrito com comandos em português para C padrão, permitindo que o programa seja executado normalmente em qualquer ambiente que suporte C.

## 📂 Estrutura do Repositório

```
.
├── build/                  # Diretório para arquivos compilados
├── docs/                   # Documentação do projeto
│   ├── CONTRIBUTING.md     # Guia de contribuição
│   ├── design/             # Documentos de design do compilador
│   └── grammar/            # Definição formal da gramática
├── include/                # Arquivos de cabeçalho
│   ├── ast/                # Estruturas da Árvore Sintática Abstrata (AST)
│   └── tokens/             # Definições de tokens
├── src/                    # Código-fonte
│   ├── codegen/            # Geração de código
│   ├── lexer/              # Analisador léxico (Flex)
│   │   └── lexer.l         # Arquivo Flex para análise léxica
│   ├── main.c              # Ponto de entrada da aplicação
│   ├── parser/             # Analisador sintático (Bison)
│   │   └── parser.y        # Arquivo Bison para análise sintática
│   └── semantic/           # Análise semântica
├── tests/                  # Testes do compilador
│   └── teste1.txt          # Exemplo de arquivo de teste
├── .gitignore              # Arquivos ignorados pelo Git
├── Makefile                # Regras de compilação do projeto
└── README.md               # Este arquivo
```

## 📁 Acesso ao projeto

Você pode [acessar o código fonte do projeto](https://github.com/ccarlaa/Compiladores---Grupo-5) ou [baixá-lo](https://github.com/ccarlaa/Compiladores---Grupo-5/archive/refs/heads/main.zip).

## 🛠️ Abrir e rodar o projeto

Após baixar o projeto, você pode abri-lo com o Visual Studio Code. Para isso, na tela de launcher clique em:

1. File > Open Folder
2. Procure o local onde o projeto está e o selecione (Caso o projeto seja baixado via zip, é necessário extraí-lo antes de procurá-lo)
3. Por fim clique em Abrir

### Pré-requisitos

Certifique-se de ter os seguintes pré-requisitos instalados:

```bash
# Ubuntu/Debian
sudo apt-get install flex bison build-essential

# Fedora
sudo dnf install flex bison gcc make

# Arch Linux
sudo pacman -S flex bison gcc make

# macOS (usando Homebrew)
brew install flex bison gcc

# Windows (usando MSYS2/MinGW)
pacman -S flex bison gcc make
```

### Compilando e Executando no Linux

Para compilar e executar no Linux, você pode usar o script incluído:

```bash
# Tornar o script executável
chmod +x compilar-linux.sh

# Executar o script
./compilar-linux.sh
```

O script irá:
1. Verificar e instalar as dependências necessárias
2. Compilar o projeto
3. Oferecer a opção de executar o teste padrão

### Compilando e Executando no macOS

Para compilar e executar no macOS, você pode usar o script incluído:

```bash
# Tornar o script executável
chmod +x compilar-macos.sh

# Executar o script
./compilar-macos.sh
```

O script irá:
1. Verificar e instalar as dependências necessárias usando Homebrew
2. Compilar o projeto
3. Oferecer a opção de executar o teste padrão

### Instalação do Flex e Bison no Windows

Para instalar o Flex e o Bison no Windows, você pode usar o MSYS2:

1. Baixe e instale o [MSYS2](https://www.msys2.org/)
2. Abra o terminal do MSYS2 MinGW64
3. Execute os seguintes comandos:

```bash
pacman -Syu
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-flex mingw-w64-x86_64-bison make
```

4. Adicione o diretório `C:\msys64\mingw64\bin` ao PATH do Windows:
   - Clique com o botão direito em "Este Computador" > Propriedades
   - Clique em "Configurações avançadas do sistema"
   - Clique em "Variáveis de ambiente"
   - Edite a variável "Path" e adicione o diretório

5. Para compilar o projeto, execute:

```bash
make
```

6. Para executar um teste com um arquivo de entrada:

```bash
# Executa o teste padrão (teste1.txt)
make test

# Executa um teste específico
make run TEST=seu_arquivo_de_teste.txt

# Ou diretamente
./build/compilador < tests/seu_arquivo_de_teste.txt
```

7. Outras opções de compilação e execução:

```bash
# Compilar em modo debug (com informações para depuração)
make DEBUG=1

# Limpar arquivos gerados
make clean

# Limpar completamente (remove diretório build)
make distclean

# Gerar documentação (quando implementado)
make docs
```

### Compilando no Windows

Para facilitar a compilação no Windows, você pode usar o script batch fornecido:

```batch
compilar.bat
```

Este script irá:

1. Verificar se o Flex e o Bison estão instalados
2. Compilar os arquivos fonte
3. Gerar o executável `compilador.exe`
4. Oferecer a opção de executar o teste padrão

### Usando Docker

O projeto inclui suporte para Docker, permitindo que você compile e execute o compilador em qualquer plataforma que suporte Docker, sem a necessidade de instalar dependências localmente.

```bash
# Tornar o script executável (Linux/macOS)
chmod +x docker-run.sh

# Executar o script
./docker-run.sh
```

Para Windows, você pode construir e executar a imagem Docker diretamente:

```bash
# Construir a imagem
docker build -t c-em-portugues .

# Executar um teste
docker run --rm -it c-em-portugues /bin/bash -c "cd /app && ./build/compilador < tests/teste1.txt"

# Ou iniciar um shell interativo
docker run --rm -it c-em-portugues
```

## Opções de Compilação e Execução

```bash
# Executa o teste padrão (teste1.txt)
make test

# Executa um teste específico
make run TEST=seu_arquivo_de_teste.txt

# Ou diretamente
./build/compilador < tests/seu_arquivo_de_teste.txt

# Compilar em modo debug (com informações para depuração)
make DEBUG=1

# Limpar arquivos gerados
make clean

# Limpar completamente (remove diretório build)
make distclean

# Gerar documentação (quando implementado)
make docs
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
