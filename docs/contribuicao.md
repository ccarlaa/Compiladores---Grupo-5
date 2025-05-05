# Guia de Contribuição

Este documento descreve os padrões e processos para contribuir com o projeto.

## Padrão de Commits

Seguimos o padrão [Conventional Commits](https://www.conventionalcommits.org/). Cada commit deve seguir o formato:

```
<tipo>:<escopo opcional><descrição>
```

### Tipos de Commits

- `feat`: Nova funcionalidade
- `update`: Atualizar funcionalidade
- `fix`: Correção de bug
- `docs`: Alterações na documentação
- `style`: Alterações que não afetam o código (espaços em branco, formatação, etc)
- `refactor`: Refatoração de código
- `test`: Adição ou correção de testes
- `chore`: Atualizações de build, configurações, etc

### Exemplos

```
feat(lexer): adiciona suporte a números decimais
fix(parser): corrige precedência de operadores
docs(readme): atualiza instruções de instalação
style(ast): formata código seguindo padrão do projeto
refactor(codegen): melhora geração de código assembly
test(optimizer): adiciona testes para dead code elimination
chore(docker): atualiza versão do ubuntu no Dockerfile
```

## Padrão de Branches

### Nomenclatura

- `main`: Branch principal do projeto
- `feat/*`: Novas funcionalidades
- `fix/*`: Correções de bugs

### Exemplos

```
feat/add-floating-point
fix/parser-memory-leak
```

## Processo de Pull Request

1. **Criar Branch**
   ```bash
   git checkout -b feat/nome-da-feature
   ```

2. **Desenvolver**
   - Faça commits seguindo o padrão
   - Mantenha commits pequenos e focados
   - Atualize a documentação quando necessário

3. **Testar**
   ```bash
   make clean
   make
   make test
   ```

4. **Atualizar Branch**
   ```bash
   git fetch origin
   git rebase origin/develop
   ```

5. **Criar Pull Request**
   - Título: Use o mesmo padrão dos commits
   - Descrição: Detalhe as mudanças e seu impacto
   - Checklist:
     - [ ] Código segue os padrões do projeto
     - [ ] Testes foram adicionados/atualizados
     - [ ] Documentação foi atualizada
     - [ ] Build passa sem erros
     - [ ] Testes passam