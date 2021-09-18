FROM debian:bullseye
LABEL maintainer darodrig
RUN apt update && apt upgrade -y
RUN apt install -y make gcc git vim man gdb file valgrind lsof 
RUN apt install -y python3 pip poppler-utils
RUN pip install norminette
RUN apt install -y nasm
RUN mkdir -p /root/woody
WORKDIR /root/woody
CMD /bin/bash