FROM ubuntu:22.04

# Evitar prompts durante a instalação
ENV DEBIAN_FRONTEND=noninteractive

# Instalar dependências
RUN apt-get update && apt-get install -y \
    build-essential \
    flex \
    bison \
    gcc \
    make \
    && rm -rf /var/lib/apt/lists/*

# Definir diretório de trabalho
WORKDIR /app

# Copiar os arquivos do projeto
COPY . .

# Compilar o projeto
RUN make clean && make

# Comando padrão ao executar o container
CMD ["/bin/bash"] 