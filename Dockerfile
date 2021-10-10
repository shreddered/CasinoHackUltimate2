FROM ubuntu:21.04 AS base

ENV DEBIAN_FRONTEND noninteractive

RUN set -ex;                \
    apt update;             \
    apt install -y          \
        libboost-all-dev    \
        libssl-dev          \
        libopencv-dev       \
        nlohmann-json3-dev  \
        tesseract-ocr       \
        libtesseract-dev

FROM base AS builder

RUN set -ex;   \
    apt install -y g++ cmake

COPY . /usr/src

WORKDIR /usr/src

RUN set -ex;                                                                 \
    cmake -B build -D CMAKE_BUILD_TYPE=Release -D CMAKE_INSTALL_PREFIX=/usr; \
    cmake --build build --parallel 4;                                        \
    cmake --build build --target install

FROM base AS runtime

COPY --from=builder /usr/bin /usr/bin

ENTRYPOINT bot --token=$TOKEN
