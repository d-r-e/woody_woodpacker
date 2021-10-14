#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

size_t		ft_strlen(const char *s);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strncmp(const char *s1, const char *s2, unsigned int n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		ft_puts(const char *s);
void		ft_putnbr(long long i);
char		*ft_calloc(uint n, uint size);
long long	ft_abs(long long val);
int         ft_isalnum(int c);
#endif