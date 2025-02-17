FROM debian:bullseye

RUN apt-get update && apt-get install -y \
    gcc \
    make \
    vim \
    build-essential

WORKDIR /app