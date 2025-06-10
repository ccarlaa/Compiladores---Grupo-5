# Tradutor C para Portugol - Grupo 5

[![CI Status](https://github.com/ccarlaa/Compiladores---Grupo-5/actions/workflows/ci.yml/badge.svg)](https://github.com/ccarlaa/Compiladores---Grupo-5/actions/workflows/ci.yml)
![Platform](https://img.shields.io/badge/platform-Windows%20%7C%20Linux%20%7C%20macOS-blue)
![Language](https://img.shields.io/badge/language-C-orange)

## Sobre

**Tradutor C para Portugol: Convertendo código C para sintaxe em português**

Este projeto implementa um tradutor que converte código-fonte C padrão para código em Portugol (português estruturado). O objetivo é facilitar o ensino de programação em português, permitindo que estudantes visualizem conceitos de programação usando palavras-chave em sua língua nativa.

O tradutor funciona em **modo manual**, realizando substituição inteligente de palavras-chave C por seus equivalentes em português, preservando a estrutura e lógica do código original.

## Funcionalidades

- **Tradução de tipos de dados**: `int` → `inteiro`, `float` → `real`, `char` → `caractere`
- **Tradução de estruturas de controle**: `if` → `se`, `else` → `senao`, `while` → `enquanto`
- **Tradução de palavras-chave**: `main` → `principal`, `return` → `retorne`, `for` → `para`
- **Preservação de sintaxe**: Operadores, parênteses e estrutura mantidos
- **Processamento de comentários**: Comentários preservados integralmente
- **Modo standalone**: Funciona sem dependências externas
- **Multiplataforma**: Funciona em Windows, Linux e macOS

## Instalação e Compilação

### Pré-requisitos

O projeto requer apenas um compilador C (GCC ou similar). Não há dependências externas.

#### Windows
```cmd
# Instalar MinGW-w64 ou usar Visual Studio
# Download: https://www.mingw-w64.org/downloads/
# Ou usar chocolatey:
choco install mingw

# Verificar instalação
gcc --version
```

#### Linux (Ubuntu/Debian)
```bash
sudo apt update
sudo apt install build-essential

# Verificar instalação
gcc --version
```

#### Linux (Fedora/CentOS)
```bash
sudo dnf install gcc make
# ou para CentOS mais antigo:
sudo yum install gcc make

# Verificar instalação
gcc --version
```

#### macOS
```bash
# Instalar Xcode Command Line Tools
xcode-select --install

# Ou usar Homebrew
brew install gcc

# Verificar instalação
gcc --version
```

### Compilação

#### Método 1: Usando Make (Recomendado)

**Windows:**
```cmd
make
```

**Linux/macOS:**
```bash
make
```

#### Método 2: Compilação Direta

**Windows:**
```cmd
gcc -std=c99 -Wall -Wextra -DMANUAL_MODE -o compilador.exe src\main.c
```

**Linux/macOS:**
```bash
gcc -std=c99 -Wall -Wextra -DMANUAL_MODE -o compilador src/main.c
```

#### Método 3: Scripts de Compilação

**Windows:**
```cmd
compilar_simples.bat
```

**Linux:**
```bash
chmod +x compilar-linux.sh
./compilar-linux.sh
```

**macOS:**
```bash
chmod +x compilar-macos.sh
./compilar-macos.sh
```

## Uso

### Sintaxe Básica

```bash
# Traduzir arquivo e exibir no terminal
./compilador programa.c                    # Linux/Mac
compilador.exe programa.c                  # Windows

# Traduzir arquivo e salvar em arquivo
./compilador programa.c -o programa.ptg    # Linux/Mac  
compilador.exe programa.c -o programa.ptg  # Windows

# Ver ajuda
./compilador --help                        # Linux/Mac
compilador.exe --help                      # Windows
```

### Comandos Make Disponíveis

```bash
make              # Compila o tradutor
make test         # Executa teste básico  
make test-all     # Executa todos os testes
make clean        # Remove arquivos compilados
make help         # Mostra ajuda completa

# Específicos por sistema
make windows      # Compila para Windows (.exe)
make linux        # Compila para Linux
make macos        # Compila para macOS
```

### Exemplo de Tradução

**Entrada (C):**
```c
#include <stdio.h>

int main() {
    int x = 10;
    float y = 3.14;
    
    if (x > 5) {
        printf("Maior que 5");
        return 1;
    }
    
    while (x > 0) {
        x = x - 1;
    }
    
    return 0;
}
```

**Saída (Portugol):**
```portugol
#inclua <stdio.h>

inteiro principal() {
    inteiro x = 10;
    real y = 3.14;
    
    se (x > 5) {
        escreva("Maior que 5");
        retorne 1;
    }
    
    enquanto (x > 0) {
        x = x - 1;
    }
    
    retorne 0;
}
```

## Testes

O projeto inclui uma suite de testes para validar as traduções:

### Executar Testes

```bash
# Teste básico
make test

# Todos os testes
make test-all

# Teste individual (exemplo)
./compilador tests/test_01_basic.c           # Linux/Mac
compilador.exe tests\test_01_basic.c         # Windows
```

### Arquivos de Teste Incluídos

- `test_01_basic.c` - Declarações básicas de variáveis
- `test_02_conditionals.c` - Estruturas condicionais (if/else)
- `test_03_loops.c` - Estruturas de repetição (while/for)
- `test_04_functions.c` - Funções e parâmetros
- `test_05_expressions.c` - Expressões complexas

## Estrutura do Projeto

```
Compiladores---Grupo-5/
├── src/
│   └── main.c              # Código principal do tradutor
├── tests/                  # Arquivos de teste
│   ├── test_01_basic.c
│   ├── test_02_conditionals.c
│   ├── test_03_loops.c
│   ├── test_04_functions.c
│   └── test_05_expressions.c
├── .github/
│   └── workflows/
│       └── ci.yml          # GitHub Actions para CI/CD
├── compilador.exe          # Executável (Windows)
├── compilador              # Executável (Linux/Mac)
├── Makefile                # Build system multiplataforma
├── compilar_simples.bat    # Script de compilação Windows
├── compilar-linux.sh       # Script de compilação Linux
├── compilar-macos.sh       # Script de compilação macOS
└── README.md               # Esta documentação
```

## Acesso ao Projeto

- **Repositório GitHub**: [Compiladores---Grupo-5](https://github.com/ccarlaa/Compiladores---Grupo-5)
- **Download ZIP**: [Baixar projeto](https://github.com/ccarlaa/Compiladores---Grupo-5/archive/refs/heads/main.zip)

## Integração Contínua

O projeto utiliza GitHub Actions para automatizar testes em múltiplas plataformas:

- **Windows**: Testa com MinGW-w64
- **Linux**: Testa com GCC em Ubuntu
- **macOS**: Testa com GCC via Homebrew

Os testes são executados automaticamente a cada push e pull request.

## Solução de Problemas

### Erro: "gcc não encontrado"
**Windows**: Instale MinGW-w64 ou Visual Studio Build Tools  
**Linux**: `sudo apt install build-essential` (Ubuntu/Debian)  
**macOS**: `xcode-select --install` ou `brew install gcc`

### Erro: "make não encontrado" 
**Windows**: Use Git Bash ou instale via MSYS2  
**Linux**: `sudo apt install make` (Ubuntu/Debian)  
**macOS**: Incluído no Xcode Command Line Tools

### Compilação falhando
1. Verifique se o GCC está instalado: `gcc --version`
2. Compile diretamente: `gcc -std=c99 -DMANUAL_MODE -o compilador src/main.c`
3. Verifique se o arquivo `src/main.c` existe

## Membros do Grupo

| Nome | GitHub |
|------|--------|
| Carla A. C. Ribeiro | [@ccarlaa](https://github.com/ccarlaa) |
| Clara Marcelino Ribeiro de Sousa | [@clara-ribeiro](https://github.com/clara-ribeiro) |
| Kallyne Macedo Passos | [@kalipassos](https://github.com/kalipassos) |
| Kauan de Torres Eiras | [@kauaneiras](https://github.com/kauaneiras) |
| Leonardo Sobrinho de Aguiar | [@Leonardo0o0](https://github.com/Leonardo0o0) |
| João Paulo Barros de Cristo | [@joaopb1-xps](https://github.com/joaopb1-xps) |

---

**Universidade de Brasília (UnB)**  
**Disciplina**: Compiladores  
**Projeto**: Tradutor C para Portugol
