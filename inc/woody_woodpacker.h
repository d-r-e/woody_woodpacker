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
# define DEBUG 1
# define MAX_BUFF_SIZE 40
# define PASS_LENGTH 16
# define CAVE_SIZE 53
typedef struct s_elf
{
    size_t      size;
    char        *mem;
    Elf64_Ehdr  hdr;
    int         woodyfd;
    size_t      woodysz;
    char        *strtab;
    char        *key;
    Elf64_Addr  cave_offset;
}   t_elf;


void            strerr(const char *s);
int             is_elf(const char *file);
const char      *get_section_name(int index);
void    find_caves(Elf64_Shdr shdr, char c, size_t min);
int     ft_rand(void);
char    *generate_key();
int     is_infected(void);
void write_payload();


extern t_elf g_elf;

#endif