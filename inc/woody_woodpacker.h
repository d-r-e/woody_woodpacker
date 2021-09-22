#ifndef WOODY_H
# define WOODY_H
# include <stdlib.h>
# include <stdio.h>
# include <elf.h>
# include <fcntl.h>
# include <sys/types.h>
# include <unistd.h>
# include <sys/mman.h>
# include "../libft/libft.h"
# define BIN "woody_woodpacker"
//# define DEBUG 1

typedef struct s_elf
{
    size_t      size;
    char        *mem;
    Elf64_Ehdr  hdr;
    int         woodyfd;
    size_t      woodysz;
    char        *strtab;
}   t_elf;


void strerr(const char *s);
int is_elf(const char *file);

#endif