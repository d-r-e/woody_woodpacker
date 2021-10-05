#ifndef WOODY_H
#define WOODY_H

#include <stdlib.h>
#include <stdio.h>
#include <elf.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/mman.h>
#include <asm/unistd.h> 
#define RED "\033[31m"
#define GREEN "\033[32m"
#define CYAN "\033[34m"
#define DEFAULT "\033[0m"

#ifndef BASEIMAGE
# define BASEIMAGE 0x1000
#endif

size_t	ft_strlen(const char *s);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, unsigned int n);
void *	ft_memcpy(void *dest, const void *src, size_t n);
void	ft_puts(const char *s);
void    ft_putnbr(long long i);

#endif