#ifndef WOODY_H
# define WOODY_H
# include <stdlib.h>
# include <stdio.h>
# include <linux/elf.h>
# include <fcntl.h>
# include <sys/types.h>
# include <unistd.h>
# include <sys/mman.h>
# include "../libft/libft.h"
# define BIN "woody_woodpacker"

void strerr(const char *s);
int is_elf(const char *file);
#endif