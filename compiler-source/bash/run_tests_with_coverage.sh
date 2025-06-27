name: CI

on:
  pull_request:
  push:

jobs:
  build-and-test:
    runs-on: ubuntu-latest
    steps:
      - name: 📥 Checkout do repositório
        uses: actions/checkout@v4

      - name: 🧰 Instalar dependências
        run: sudo apt-get update && sudo apt-get install -y flex bison

      - name: 🛠️ Compilar o projeto
        working-directory: compiler-source
        run: make

      - name: 🧪 Rodar testes e gerar cobertura
        run: bash compiler-source/bash/run_tests_with_coverage.sh

      - name: 📤 Upload da cobertura como artefato
        uses: actions/upload-artifact@v4
        with:
          name: cobertura-gramatica
          path: compiler-source/cobertura.txt
