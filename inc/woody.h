#ifndef WOODY_H
# define WOODY_H

# include <stdlib.h>
# include <stdio.h>
# include "elf.h"
# include <fcntl.h>
# include <string.h>
# include <sys/types.h>
# include <unistd.h>
# include <sys/mman.h>
# include <stdarg.h>
# include "libft.h"

# define KEYLEN 8 // 8 bytes -> 64 bit key length

# define RED "\033[31m"
# define GREEN "\033[32m"
# define CYAN "\033[34m"
# define DEFAULT "\033[0m"

# ifndef BASEIMAGE
#  define BASEIMAGE 0x1000
# endif

typedef struct s_payload
{
	char	*data;
	size_t	len;
}	t_payload;

void	patch_payload(Elf64_Addr new, Elf64_Addr orig, t_payload *p, void *m);
int		encrypt_text_section(char *mem, int text_sect, uint size);
void	print_woody(int argc, char **argv);

#endif
