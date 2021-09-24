FROM debian:bullseye
LABEL maintainer darodrig
RUN apt update && apt upgrade -y
RUN apt install -y make gcc git vim man gdb file valgrind lsof zsh
RUN apt install -y curl
RUN apt install -y binwalk
RUN apt install -y python3 pip poppler-utils
RUN git clone https://github.com/radareorg/radare2 && radare2/sys/install.sh
RUN pip install norminette
RUN apt install -y nasm
RUN sh -c "$(curl -fsSL https://raw.github.com/robbyrussell/oh-my-zsh/master/tools/install.sh)"
RUN chsh root -s /bin/zsh
CMD /bin/zsh