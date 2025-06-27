name: CI

on:
  push:
    branches: [ "**" ]
  pull_request:
    branches: [ "**" ]

jobs:
  build-and-test:
    runs-on: ubuntu-latest

    steps:
      - name: 🔄 Checkout do repositório
        uses: actions/checkout@v3

      - name: 🛠️ Instalar dependências
        run: |
          sudo apt-get update
          sudo apt-get install -y flex bison

      - name: 🧱 Compilar projeto
        working-directory: compiler-source
        run: make

      - name: 🧪 Executar testes com cobertura de gramática
        working-directory: compiler-source
        run: bash bash/run_tests_with_coverage.sh

      - name: 📦 Salvar relatório de cobertura como artefato
        uses: actions/upload-artifact@v3
        with:
          name: cobertura-de-gramatica
          path: compiler-source/cobertura.txt
