FROM debian:stable-slim

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        build-essential make gcc git && \
    apt-get clean && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY . /app

RUN make linux

# ENTRYPOINT removed to allow docker-compose command to run directly
# ENTRYPOINT ["/bin/bash"]