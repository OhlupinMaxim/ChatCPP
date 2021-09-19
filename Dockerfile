FROM ubuntu:latest

WORKDIR build/

COPY ../ .

RUN apt-get update && apt-get install -y build-essential cmake libpoco-dev && cmake .

