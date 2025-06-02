# Compilador C em Português

Bem-vindo à documentação oficial do Compilador C em Português, desenvolvido pelo Grupo 5.

## Sobre o Projeto

Este projeto implementa um compilador para a linguagem C traduzida para português, permitindo que programadores escrevam código usando palavras-chave em português em vez das tradicionais palavras-chave em inglês.

## Características Principais

- **Analisador Léxico**: Reconhece tokens em português (inteiro, real, caractere, etc.)
- **Analisador Sintático**: Suporta a gramática completa de C traduzida para português
- **Suporte para Estruturas**: Declaração e uso de estruturas com campos
- **Suporte para Funções**: Declaração e definição de funções com parâmetros
- **Estruturas de Controle**: Suporte para estruturas como `se`, `senao`, `enquanto`, `para`
- **Tratamento de Erros Léxicos**: Mensagens de erro detalhadas para facilitar a identificação de problemas
- **Modo de Depuração**: Permite visualizar tokens e erros léxicos com a flag `-d`
- **Testes Automatizados**: Scripts para validar o funcionamento do compilador

## Como Usar Esta Documentação

- **Guia do Usuário**: Instruções de instalação e uso básico do compilador
- **Documentação Técnica**: Detalhes sobre a implementação e arquitetura do compilador
  - **Análise Léxica**: Detalhes sobre o reconhecimento de tokens e tratamento de erros léxicos
  - **Testes**: Informações sobre como executar e validar os testes do compilador
- **Contribuição**: Como contribuir para o desenvolvimento do projeto

## Exemplos Rápidos

### Código em Português

```c
// Exemplo de código em C traduzido para português
inteiro principal() {
    inteiro a = 10;
    real b = 3.14;
    
    se (a > 5) {
        imprimir("a é maior que 5");
    } senao {
        imprimir("a é menor ou igual a 5");
    }
    
    retorne 0;
}
```

### Usando o Modo de Depuração

```bash
# Compilar o projeto
make

# Executar o compilador no modo de depuração
./compilador meu_programa.txt -d

# Saída de exemplo:
# Modo de depuração ativado - mostrando tokens e erros léxicos
# Token: 318 (IDENTIFICADOR) - Lexema: 'inteiro'
# Token: 286 (PRINCIPAL) - Lexema: 'principal'
# Token: 308 (ABRE_PAREN) - Lexema: '('
# ...
# Erro léxico (linha 5): Símbolo especial '@' não permitido.
```

### Executando Testes Automatizados

```bash
# Executar apenas os testes léxicos
./tests/testes_lexicos/executar_testes.sh

# Executar todos os tipos de testes
./executar_todos_testes.sh
```

## Equipe

Este projeto foi desenvolvido pelo Grupo 5 como parte da disciplina de Compiladores.
