FROM debian:buster
LABEL maintainer darodrig
RUN apt-get update && \
apt-get install -y make gcc git vim man gdb file valgrind zsh curl binwalk nasm \
 && apt-get clean \
 && rm -rf /var/lib/apt/lists/* \
 && sh -c "$(curl -fsSL https://raw.github.com/robbyrussell/oh-my-zsh/master/tools/install.sh)" \
 && chsh root -s /bin/zsh 
WORKDIR /root/woody
RUN mkdir -p /root/woody
CMD /bin/zsh
