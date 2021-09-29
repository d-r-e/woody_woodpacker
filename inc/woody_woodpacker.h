#ifndef WOODY_WOODPACKER_H
# define WOODY_WOODPACKER_H
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
# define WOODY_LEN 16
# define CAVE_SIZE 46
# define COPY_HEADERS
typedef struct s_elf
{
    size_t size;
    char *mem;
    Elf64_Ehdr hdr;
    int woodyfd;
    size_t woodysz;
    char *strtab;
    char *key;
    Elf64_Addr woody_offset;
    Elf64_Addr baseimage;
    Elf64_Shdr  woodyshdr;
} t_elf;

void strerr(const char *s);
int is_elf(const char *file);
const char *get_section_name(int index);
void print_elf_header(Elf64_Ehdr hdr);
void find_caves(Elf64_Shdr shdr, char c, size_t min);
int ft_rand(void);
char *generate_key();
int is_infected(void);
void write_payload();
int write_to_woody(void *mem, size_t size);
void write_woody_section(Elf64_Shdr *shdr);

static char payload[] = {'\x9c','\x50','\x57','\x56','\x54','\x52','\x51','\x41','\x50','\x41','\x51','\x41','\x52','\xb8','\x01','\x00','\x00','\x00','\xbf','\x01','\x00','\x00','\x00','\x48','\xbe','\x3a','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\xba','\x0f','\x00','\x00','\x00','\x0f','\x05','\x41','\x5a','\x41','\x59','\x41','\x58','\x59','\x5a','\x5c','\x5e','\x5f','\x58','\x9d','\xe9','\x08','\x42','\x42','\x00','\x2e','\x2e','\x2e','\x2e','\x57','\x4f','\x4f','\x44','\x59','\x2e','\x2e','\x2e','\x2e','\x2e','\x0a','\x00'};

extern t_elf g_elf;

#endif