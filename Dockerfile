FROM ubuntu:21.04
ENV DEBIAN_FRONTEND noninteractive
RUN apt update && \
    apt install -y cmake libopencv-dev build-essential libssl-dev libboost-all-dev tesseract-ocr libtesseract-dev nlohmann-json3-dev && \
    apt autoclean
