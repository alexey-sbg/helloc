FROM ubuntu:14.04

RUN apt-get update && apt-get install -y build-essential

# Compile

RUN mkdir /code

WORKDIR /code

ADD hello.c .

RUN gcc hello.c -o hello

ENV PATH $PATH:/code
