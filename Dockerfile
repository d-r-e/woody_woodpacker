FROM debian:bullseye
LABEL maintainer darodrig
RUN apt update && apt upgrade -y
RUN apt install -y make gcc git vim man gdb
RUN mkdir -p /root/woody
WORKDIR /root/woody
CMD /bin/bash