FROM debian:buster
LABEL maintainer darodrig
RUN apt-get update
RUN apt-get install -y make gcc git vim man gdb file valgrind zsh curl
RUN apt-get install -y binwalk
# RUN apt-get install -y python3 python3-pip poppler-utils
# RUN git clone https://github.com/radareorg/radare2 && radare2/sys/install.sh
# RUN pip3 install norminette
RUN apt-get install -y nasm
# RUN apt-get install -y zlib1g-dev
# RUN curl https://raw.githubusercontent.com/rapid7/metasploit-omnibus/master/config/templates/metasploit-framework-wrappers/msfupdate.erb > msfinstall
# RUN chmod 755 msfinstall && ./msfinstall
RUN sh -c "$(curl -fsSL https://raw.github.com/robbyrussell/oh-my-zsh/master/tools/install.sh)"
RUN chsh root -s /bin/zsh
RUN mkdir -p /root/woody
WORKDIR /root/woody
CMD /bin/zsh
